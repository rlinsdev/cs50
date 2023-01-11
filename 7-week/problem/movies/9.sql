SELECT DISTINCT(p.name)
  FROM movies m
 INNER JOIN stars s ON s.movie_id = m.id
 INNER JOIN people p ON p.id = s.person_id
 WHERE m.year = '2004'
 ORDER BY p.birth
