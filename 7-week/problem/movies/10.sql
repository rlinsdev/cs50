SELECT DISTINCT(p.name)
  FROM movies m
 INNER JOIN directors d on d.movie_id = m.id
 INNER JOIN people p ON p.id = d.person_id
 INNER JOIN ratings r ON r.movie_id = m.id
 WHERE r.rating >= 9.0
