SELECT name 
FROM people 
WHERE id IN (
SELECT DISTINCT directors.person_id                     -- Again DISTINCT by id
FROM directors 
JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE rating >= 9.0)