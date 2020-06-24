/*
In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
Your query should output a table with a single column for the name of each person.
*/

SELECT name FROM (SELECT DISTINCT p.id, p.name FROM movies m, directors d, people p, ratings r WHERE m.id=d.movie_id AND p.id=d.person_id AND m.id=r.movie_id AND r.rating>='9.0');