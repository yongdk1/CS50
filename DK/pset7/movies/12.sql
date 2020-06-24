/*
In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
Your query should output a table with a single column for the title of each movie.
You may assume that there is only one person in the database with the name Johnny Depp.
You may assume that there is only one person in the database with the name Helena Bonham Carter.
*/

SELECT title FROM movies m, stars s, people p WHERE m.id=s.movie_id AND p.id=s.person_id AND p.name = 'Johnny Depp' AND m.title IN (SELECT title FROM movies m, stars s, people p WHERE m.id=s.movie_id AND p.id=s.person_id AND p.name = 'Helena Bonham Carter')