/*
In 4.sql, write a SQL query to determine the number of movies with an IMDb rating of 10.0.
Your query should output a table with a single column and a single row (plus optional header) containing the number of movies with a 10.0 rating.
*/

SELECT count(title) FROM movies m, ratings r WHERE m.id=r.movie_id AND rating='10.0'