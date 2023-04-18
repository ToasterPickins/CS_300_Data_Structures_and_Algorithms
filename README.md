# CS_300_Data_Structures_and_Algorithms

### What was the problem you were solving in the projects for this course?
For this course, I was tasked with designing a system for ABCU (a fictional university) that would take in a CSV file containing a listing of courses (course numbers, names, and prerequisites), store this in a data structure, and allow for printing a sorted list or a specific course. I needed to review the data structures available to me (i.e., vector, linked list, hash table, and binary search tree) to determine the best one to use for this specific scenario.

### How did you approach the problem? Consider why data structures are important to understand.
To solve this problem, I created different sets of pseudocode this system using each of the data structures. Then, using this pseudocode, I reviewed and analized the runtime and memory requirements of each for creation, sorting, and traversal of the data structure to determine which was the most efficient option.

### How did you overcome any roadblocks you encountered while going through the activities or project?
Roadblocks were overcome by debugging code and searching the internet for solutions. One example of this was my code to create and use a hash table. I had originally designed it to be a vector of "buckets" with each "bucket" being a linked list. I tried to combine all of this within one class but could not get my code to work correctly. Upon debugging, I decided to rework the code by breaking it down into more discrete segments. Out of this, I ended up with a hash table class that consisted of a vector and some basic functions to manipulate it at a higher level then nested a linked list class within it. This nested class defined the linked lists that would be in each bucket and the functions that would operate directly on those lists. While there are other ways of tackling this problem, it broke the problem down into more maneagable problems and gave me the opportunity to explore the concept of nested classes which is something that I hadn't had a chance to do until then.

### How has your work on this project expanded your approach to designing software and developing programs?
This project and class has helped me to understand the importance of data structures and the algorithms that operate on them. Without this knowledge, I probably would have fallen back on using vectors for all situations which isn't the best solution in all cases.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
I think the biggest example of this is the one that I described above with the nested classes. This example helped solidify in my mind the need to break things down into manageable chunks. Once I reworked the code, it was much easier to build and read and the fine tuning of it to workout any bugs was simpler since the code was organized much better.
