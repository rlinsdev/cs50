SELECT m.title, r.rating
  FROM movies m
 INNER JOIN ratings r
    ON r.movie_id = m.id
 WHERE year = 2010
 ORDER BY rating DESC, title
