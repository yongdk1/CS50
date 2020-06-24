SELECT name                                 -- Cannot use DISTINCT here as some people share the same names
FROM people 
WHERE id IN (
SELECT DISTINCT person_id                   -- Differentiate people by their id
FROM stars 
JOIN movies ON stars.movie_id = movies.id
WHERE year = 2004)
ORDER BY birth