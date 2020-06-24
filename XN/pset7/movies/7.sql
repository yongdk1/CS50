SELECT title, rating 
FROM movies 
JOIN ratings on id = movie_id 
WHERE year = 2010 
ORDER BY rating DESC, title 