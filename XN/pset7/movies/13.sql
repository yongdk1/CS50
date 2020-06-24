SELECT people.name                              
FROM people                                     
WHERE people.id IN (                            
SELECT DISTINCT stars.person_id                 --Distinct id in case there are people who star with Kevin Bacon in different movies 
FROM stars                                      
JOIN movies ON stars.movie_id = movies.id       
WHERE movies.id IN (                            
SELECT movies.id                                
FROM movies                                     
JOIN stars ON movies.id = stars.movie_id        
JOIN people ON stars.person_id = people.id      
WHERE name = "Kevin Bacon" AND birth = 1958))   
AND name != "Kevin Bacon"                       --Exclude Kevin Bacon