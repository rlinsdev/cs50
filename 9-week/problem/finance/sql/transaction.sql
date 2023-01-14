-- Table to register all trasactions (buy call)
CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id integer,
    symbol text,
    symbol_name text,
    shares integer,
    price real,
    total real,
    data TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY(user_id) REFERENCES users(id));
