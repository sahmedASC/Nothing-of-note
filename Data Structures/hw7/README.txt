HOMEWORK 7: SPATIALLY-EMBEDDED ADJACENCY MAPS


NAME:  < Saaif Ahmed >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< www.cplusplus.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 >



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity along with a short
justification for each of the functions below:

n: The total number of users
l: The total number of users with a location
d: The total number of users with degree >= 1
m: The total number of connections
p: The number of users that a function will print out

loadConnections():
O(N)
    goes through the whole file so must be O(N)
loadLocations():
O(L)
    goes through the whole file so must be O(L)
printAllUsersWithinDistance():
O(LlogL)
    searching through the map is logL and making sure it is a real values is
    L, so L*logL

printDegreesHistogram():
O(N)
    you have to run through all the users and generate a map based on their
    values so O(N)

printDegreesOfAll():
O(N)
    same as above. You have to run through all the users. O(N)

printFriendsWithDegree():
O(N*plogp)
    searching based on the thing to output will be pLogp due to map
    searching. The N is to make sure that it exists in the first place

printFriendsWithinDistance():
O(L*plogp)
    same reasoning as above. The output will be plogp as map search
    is logN and you have to ouput what you find so PlogP. The L is to
    assert that the locations exists

printUsersWithinIDRange():
O(p*N)
    The printing is the main part of this function so O(p). But you need to check
    against all the users so O(p*N)


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






