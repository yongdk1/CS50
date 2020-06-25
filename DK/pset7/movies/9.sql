/*
In 9.sql, write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year.
Your query should output a table with a single column for the name of each person.
People with the same birth year may be listed in any order.
No need to worry about people who have no birth year listed, so long as those who do have a birth year are listed in order.
If a person appeared in more than one movie in 2004, they should only appear in your results once.
*/

SELECT name FROM (SELECT DISTINCT p.id, p.name FROM people p, movies m, stars s WHERE p.id=s.person_id AND m.id=s.movie_id AND m.year='2004' ORDER BY p.birth);