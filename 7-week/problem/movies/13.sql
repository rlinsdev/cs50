SELECT DISTINCT(p.name) from movies m
 INNER JOIN stars s ON m.id = s.movie_id
 INNER JOIN people p ON p.id = s.person_id
--  WHERE m.id = 100814
 WHERE m.id IN(
    SELECT m.id from movies m
     INNER JOIN stars s ON m.id = s.movie_id
     INNER JOIN people p ON p.id = s.person_id
     WHERE p.name = 'Kevin Bacon' AND p.birth = 1958
       --AND m.id = 100814 -- Tremors
     ORDER BY m.year desc
 )
  AND p.name NOT IN ('Kevin Bacon')
