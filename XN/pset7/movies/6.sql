SELECT AVG(rating) 
FROM movies 
JOIN ratings on id = movie_id 
WHERE year = 2012