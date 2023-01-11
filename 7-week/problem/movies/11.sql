SELECT m.title
  FROM movies m
 INNER JOIN stars s ON m.id = s.movie_id
 INNER JOIN people p ON p.id = s.person_id
 INNER JOIN ratings r ON r.movie_id = m.id
 WHERE p.name = 'Chadwick Boseman'
ORDER BY r.rating DESC
LIMIT 5
