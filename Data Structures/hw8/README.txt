HOMEWORK 8: ROPES


NAME:  < Saaif Ahmed >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Lecture Code, www.cplusplus.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor:
1:O(n)
2:O(n)
You need to go through all the nodes so it has to be O(n)

Construct from Node*:
1:O(p)
2:O(p)
When stealing the node most operations are O(1). But determining the size has to go through everything
on the right side as you add the weights together.

Index:
1:O(p)
2:O(p)
You have to reach a node that is a leaf in order to index it because only the leaves have strings. So you have to
traverse the longest path

Report:
1:O(p*n)
2:O(p*n)
The report function runs the index function for as long as desired by the user. If the user wants the whole string it will
go down the path p for every index of the string whose length is n. thus p*n


iterator operator++:
1:O(p)
2:O(p)
this is only dealing with going from the top of the rope down to the left most node to begin the ++
Therefore in the worst case scenario you have to take the longest path p.

Split:
1:O(p^2*n)
2:O(p*n)
It is tough to say but the unbalanced rope will most likely have to readjust all of its weights towards the end of the
split so it has to take another p path. The n is dependant on how large the string is, but as the approach infinity the
n becomes n/2 down the middle and in O notation that is equal to n.

Concat:
1:O(n)
2:O(n*p)
It depends on the size of the word being concatenated. This is because you have to make a copy of the rope with the
string size n. Either way it has to be adjusted to the size of the string. The balanced rope would also have to make
sure that the rope is still balanced, and adding the string would alter the longest path p.


An unbalanced rope is slower than a balanced rope, but as the sizes grow large they will mostly be the same I beleive.


TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

I made sure to test that constructors were working.
I also put myself in the mind of someone who is tinkering with this structure.
I believe that they would try the things that I tested. I also tested cases
discussed in the homework but not in the main code like splitting down the middle.
I made sure to also do the generic bad index and similar tests



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

