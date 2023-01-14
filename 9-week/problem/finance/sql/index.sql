-- -- Query1
-- SELECT Symbol, symbol_name, shares, price, total
--   FROM transactions t
--  WHERE t.user_id = 1;


SELECT DISTINCT symbol FROM transactions WHERE user_id = 1;
