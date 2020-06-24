/*
In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
Your query should output a table with a single column for the name of each person.
There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
Kevin Bacon himself should not be included in the resulting list.
*/

SELECT DISTINCT p.name FROM movies m, stars s, people p WHERE m.id=s.movie_id AND p.id=s.person_id AND NOT name='Kevin Bacon'  AND m.id IN (SELECT m.id FROM movies m, stars s, people p WHERE m.id=s.movie_id AND p.id=s.person_id AND p.name='Kevin Bacon' AND p.birth='1958')