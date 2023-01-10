from cs50 import get_float


def main():
    cents = get_cents() * 100

    quarters = calc_quarters(cents)
    cents = cents - quarters * 25

    dimes = calc_dimes(cents)
    cents = cents - dimes * 10

    nickels = calc_nickels(cents)
    cents = cents - nickels * 5

    pennies = calc_pennies(cents)
    cents = cents - pennies * 1

    coins = quarters + dimes + nickels + pennies

    print(coins)


def get_cents():
    while True:
        cents = get_float("Change owed: ")
        if cents > 0:
            return cents


def calc_quarters(cents):
    return handle_coins(cents, 25)


def calc_dimes(cents):
    return handle_coins(cents, 10)


def calc_nickels(cents):
    return handle_coins(cents, 5)


def calc_pennies(cents):
    return handle_coins(cents, 1)


def handle_coins(cents, base):
    i = 0
    while (cents > 0 and int(cents / base) > 0):
        cents = cents - base
        i += 1
    return i


if __name__ == "__main__":
    main()
