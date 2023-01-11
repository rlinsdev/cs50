SELECT m.title FROM movies m
 INNER JOIN stars s ON m.id = s.movie_id
 INNER JOIN people p ON p.id = s.person_id
 WHERE p.id in (
    SELECT id from people p
     WHERE p.name IN('Johnny Depp', 'Helena Bonham Carter'))
 group by m.title
 having count(m.id)> 1;
