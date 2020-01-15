HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Saaif Ahmed >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< www.cplusplus.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 17 >



TESTING & DEBUGGING STRATEGY:
For Debugging:
The primary form of debugging was to utilize Clion's IDE debugger and
observe how variables changed and got passed into functions. I drew out
the paths that variables would take to ensure I knew exactly what was
happening. Thinking about each and every scenario was important as well.
Print debugging was used, but very sparingly. I preferred to instead set break
points within functions and loops to see if the expected changes were occuring.

For More Tests:
The strategy here was to utilize the functions to the absolute extreme.
I created and deleted the Unrolled lists using every function that
would allow me to do so. I tested the assignment operator with a fresh
list and with a list that had been edited. I tested the -- operator by
comparing it to another Unrolled list and printing it backwards to assure
that it knew how to handle the NULL pointer situations


ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, UnrolledLL, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case?

        UnrolledLL  dslist  STL
size        O(1)     O(1)   O(1)
front       O(1)     O(1)   O(1)
back        O(1)     O(1)   O(n)
push_front  O(n)     O(1)   O(1)
push_back   O(1)     O(1)   O(n)
pop_back    O(1)     O(1)   O(n)
pop_front   O(n)     O(1)   O(1)
erase       O(n)     O(1)   O(1)
insert      O(n)     O(1)   O(1)
begin       O(1)     O(1)   O(1)
end         O(1)     O(1)   O(1)
copy_list   O(n*m)   O(n)   O(n)
print       O(n*m)   O(n)   O(n)
destroy     O(n)     O(n)   O(n)

**m is number of elements per Node

The memory usage of UnrolledLL in the worst case is still arguably better
than the usage of either dslist or STL. This is because less objects are created
on the heap in an average scenario as compared to the other data types. It also
has pointers to the tail of the list so that those operations can be O(1).
The UnrolledLL structure is inefficient when there is a deliberate creation of
multiple Node objects in which it does not take advantage of the array storage of
each Node. For example each node could look like:
________________________________________
Node<T>
<------------------------:prev
num_elements: 1
elements [1][n/a][n/a][n/a][n/a][n/a]
next:--------------------------------->
________________________________________
This would require much more memory allocation on the heap and revert the UnrolledLL
essentially a dslist. The average number of elements per node would be 1.


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


