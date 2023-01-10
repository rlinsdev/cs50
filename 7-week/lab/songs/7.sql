SELECT AVG(S.energy)
  FROM artists A
 INNER JOIN songs s ON S.artist_id = A.id
 WHERE A.name = 'Drake'
