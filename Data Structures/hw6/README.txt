HOMEWORK 6: CROSSWORD BLACKOUT


NAME:  < Saaif Ahmed >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< www.cplusplus.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 40 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of words in the dictionary (d)? 
The total number of spaces with a letter (l)?
The total number of blacked out spaces (b)? 
The number of constraints (c)? 
Etc.

Function:           O(N):           Desc:
sub_a()             O((c)2^(wh))    search across
sub_d()             O((c)2^(wh))    search down
possible_board()    O(d(log(d)))    filter possible boards
build_board()       O((log(d)(d)^3) build a board and check if it's valid

These are the main functions that were very computation heavy for this algorithm.
sub_a and sub_b use substring to search parts of the board till a match is found
within the dictionary. Once a word is found is checked to see if a constraint
exists for it's size. possible_board determines is a set of words found will
make a valid board. Build board makes a test board out of one possible set of words
and uses the search function to ensure that no extra words are created.

DESCRIPTION OF YOUR ADDTIONAL PUZZLES/DICTIONARIES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).

One of the main points of the searching function is that there cannot
be a single word that is less that three letters long. Because I search
across wise first then down these files corner case each function. In test1
the sub_a function should find no words and in test2 sub_d should find no words.
However there is a valid solution for each board.


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES/DICTIONARIES:
# of solutions & approximate wall clock running time for different
puzzles / dictionaries for a single solution or all solutions. Be
specific about which puzzle/dictionary/parameters you were timing.

On the blackout series I find 3,1,and 15 respectively. These run in a few seconds.
On the nyt series I find 1, and 0 solutions respectively and this also runs in a few
seconds. On the reverse_ell series I find that each board has 1 solution and it takes a few
seconds as well to run the whole program. sporcle I could not get to run.

For all files that run, the parsing functions are very fast, this includes dictionaries and
parameters. Solving the puzzles take a bulk of the time. 1-3 seconds depending on the puzzle. For
example nyt1_mini took 2.3 seconds to run the whole sequence, but less than a second to get the parsing.

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
I know I did not get all of the points and will most likely do
poorly on this assignment. It was very hard to wrap my head around
all the possibilities. If possible I would like to see the hidden cases
so I know what I got wrong.