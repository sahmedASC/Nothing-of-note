HOMEWORK 9: IMDB SEARCH


NAME:  < Saaif AHmed >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< www.cplusplus.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 25 >


HASH FUNCTION DESCRIPTION
    The same function as given in lab 10. It takes a key
    as a string. Adds up all the ascii values, offsets it
    and shifts it left and right randomly. This gives a hash int
    where I mod it in order to fit into the hash table.



HASH TABLE IMPLEMENTATION
    The hashtable is a vector of movie pointers
    that point to movie objects on the heap. There are
    64 pointers and 64 movie objects, one for every partial
    hash of a movie. The collisions were handled using linear probing
    and and the resize doubled the size of the hashtable when the occupancy
    was too large.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


