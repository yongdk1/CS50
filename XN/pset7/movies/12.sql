SELECT title 
FROM movies 
JOIN stars ON movies.id = stars.movie_id 
JOIN people ON stars.person_id = people.id 
WHERE name = "Johnny Depp"
INTERSECT                                   --Intersect of 2 sets of titles 
SELECT title 
FROM movies 
JOIN stars ON movies.id = stars.movie_id 
JOIN people ON stars.person_id = people.id 
WHERE name = "Helena Bonham Carter"