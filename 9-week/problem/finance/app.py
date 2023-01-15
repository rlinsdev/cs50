import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
#TODO:Lins - não está recuperando
# if not os.environ.get("API_KEY"):
#     raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    trans = get_transactions_by_session_id('')

    # Gel total value of all transactions
    total = 0
    for x in trans:
        total += x["price"] * x["shares"]

    # Get User by session
    user_row = get_user_by_session()

    if len(trans) > 0:
        return render_template("index.html", transactions=trans,
            cash=round(user_row[0]["cash"], 2), total=round(total, 2))

    return render_template("index.html")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Check Symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol invalid", 400)
        symbol = symbol.upper()

        # Get actual price and if symbol exist
        res_quoted = lookup(symbol)

        # Symbol exist?
        if not res_quoted:
            return apology("Symbol invalid", 400)

        # Get Shares (integer)
        shares = int(request.form.get("shares"))
        if not shares or shares < 0:
            return apology("Shares required positive number", 400)

        # Get User by session
        user_row = get_user_by_session()

        # Verify if the transaction is enabled
        if user_row[0]["cash"] < (res_quoted["price"] * shares):
            return apology("Insufficient budget", 400)

        # Get Total value
        total = res_quoted["price"] * shares

        # Submit the user’s input Transaction via POST to /buy.
        insert_transactions(user_row[0]["id"], symbol, res_quoted["name"], shares, res_quoted["price"], total)

        budget = user_row[0]["cash"] - total

        # Update user - Cash value remaining
        update_user_cash(user_row[0]["id"], budget)

        # Return Home
        return redirect("/")

    # just open the html
    return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    trans = get_transactions_by_session_id('')

    if len(trans) > 0:
        return render_template("history.html", transactions=trans)
    return redirect("/")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = get_user_by_username(request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol invalid", 400)
        symbol = symbol.upper()

        # Get values from that symbol - Call External API
        quoted = lookup(symbol)

        return render_template("quote.html", quoted=quoted)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":

        # I put HTML required, but I'll validate here too
        if not request.form.get("username"):
            return apology("username required", 403)
        else:
            username = request.form.get("username")

        if not request.form.get("password"):
            return apology("password required", 403)
        else:
            password = request.form.get("password")

        if not request.form.get("confirmation"):
            return apology("confirmation required", 403)
        else:
            confirmation = request.form.get("confirmation")

        # Validate username
        row = get_user_by_username(username)

        if len(row) > 0:
            return apology("invalid username and/or password", 403)

        # Validate same password and confirmation
        if password != confirmation:
            return apology("Password and confirmation is not the same!", 404)

        # Generate Hash
        # TODO:Lins - Cara, este método está certo?
        hash = generate_password_hash(password, )

        # Insert the user
        db.execute("INSERT INTO users (username, hash, cash) VALUES (?, ?, ?)", username, hash, 10000)

        row_user_inserted = get_user_by_username(username)

        # Remember which user has logged in
        session["user_id"] = row_user_inserted[0]["id"]

        # Redirect user to home page
        # return redirect("/")
        return render_template("index.html", first_access='true')



        # return redirect("/")
        # Remember which user has logged in




    else :
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":

        # retrieve symbols from transactions, of logged user
        ddl_shares = get_symbols_by_user()

        # Return Shares from user in session
        return render_template("sell.html", shares=ddl_shares)
    else:
        # get Symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol invalid", 400)

        # get Shares
        shares_form = int(request.form.get("shares"))

        # Check negative one
        if not shares_form or shares_form < 0:
            return apology("Shares required positive number", 400)

        # Get Quotation from a symbol
        re_quoted = lookup(symbol)

        # Get transactions from user
        tran_bd = get_transactions_by_session_id(symbol)

        # Get all shares (Positives and negatives)
        shares_bd = 0
        for x in tran_bd:
            shares_bd += x["shares"]

        # Check shares positive
        if shares_form > shares_bd:
            return apology("Invalid Shares", 400)

        total = re_quoted["price"] * shares_form
        # Every thing is OK with this seller action. Let's do it!
        insert_transactions(session["user_id"], symbol, re_quoted["name"], (shares_form * -1), re_quoted["price"], total)

        #Get user in Session
        user_row = get_user_by_session()

        # Update user - Add cash back to account
        budget = user_row[0]["cash"] + total
        update_user_cash(user_row[0]["id"], budget)

        # Return Home
        return redirect("/")

# Get transaction by suserId and symbol
def get_transactions_by_session_id(symbol):
    if not symbol:
        return db.execute("SELECT * FROM transactions t WHERE t.user_id = (?)", session["user_id"])
    else:
        return db.execute("SELECT * FROM transactions t WHERE t.user_id = (?) AND symbol = (?)", session["user_id"], symbol)

def get_user_by_username(username):
    return db.execute("SELECT * FROM users WHERE username = ?", username)

def get_user_by_id(id):
    return db.execute("SELECT * FROM users WHERE id = ?", id)

def get_user_by_session():
    return db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

def update_user_cash(user_id, budget):
    query = "UPDATE users SET cash = (?) WHERE id = (?)"
    db.execute(query, budget, user_id)

def get_symbols_by_user():
    return db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ?", session["user_id"])

def insert_transactions(user_id, symbol, symbol_name, shares, price, total):
    db.execute("INSERT INTO transactions (user_id, symbol, symbol_name, shares, price, total) values (?,?,?,?,?,?)", user_id, symbol, symbol_name, shares, price, total)
