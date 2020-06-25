/*
In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
Your query should output a table with a single column for the title of each movie.
You may assume that there is only one person in the database with the name Chadwick Boseman.
*/

SELECT m.title FROM movies m, stars s, people p, ratings r WHERE m.id=s.movie_id AND p.id=s.person_id AND m.id=r.movie_id AND p.name='Chadwick Boseman' ORDER BY r.rating DESC LIMIT 5;