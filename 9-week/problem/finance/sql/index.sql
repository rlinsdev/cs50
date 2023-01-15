-- Query1
SELECT Symbol, symbol_name, shares, price, total
  FROM transactions t
 WHERE t.user_id = 1;


SELECT DISTINCT symbol FROM transactions WHERE user_id = 1;

select SUM(shares) from transactions WHERE user_Id = 1 AND symbol = 'TSLA';

select * from transactions WHERE symbol = 'NFLX';

select * from users;

SELECT symbol, symbol_name, SUM(shares) shares, price, SUM(shares * price) total
  FROM transactions
 WHERE user_id = 22
 Group By symbol, symbol_name, price;
