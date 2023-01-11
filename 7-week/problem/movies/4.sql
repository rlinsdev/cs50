SELECT COUNT(*) AS qtd_movies
  FROM  movies m
 INNER JOIN ratings r ON m.id = r.movie_id
 WHERE r.rating = 10.0
