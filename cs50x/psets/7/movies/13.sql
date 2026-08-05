-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT p.name
FROM people p
JOIN stars s
  ON p.id = s.person_id
JOIN (SELECT s.movie_id FROM people p JOIN stars s ON p.id = s.person_id WHERE p.name = 'Kevin Bacon' AND birth = 1958) bacon
  ON s.movie_id = bacon.movie_id
WHERE p.name <> 'Kevin Bacon';


