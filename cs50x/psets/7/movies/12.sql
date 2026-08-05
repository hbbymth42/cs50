-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT DISTINCT m.title
FROM movies m
JOIN (SELECT s.movie_id FROM people p JOIN stars s ON p.id = s.person_id WHERE name = 'Bradley Cooper') bradley
  ON m.id = bradley.movie_id
JOIN (SELECT s.movie_id FROM people p JOIN stars s ON p.id = s.person_id WHERE name = 'Jennifer Lawrence') jennifer
  ON m.id = jennifer.movie_id;
