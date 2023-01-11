SELECT p.name
  FROM movies m
 INNER JOIN stars s ON s.movie_id = m.id
 INNER JOIN people p ON p.id = s.person_id
 WHERE title = 'Toy Story'
