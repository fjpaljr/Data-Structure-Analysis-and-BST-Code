# Data-Structure-Analysis-and-BST-Code

What was the problem you were solving in the projects for this course?
The goal was to build an advising system for ABCU that could load course data from a file, store it efficiently, and allow advisers to look up courses and print a sorted course list. The core challenge was choosing the right data structure to make those operations practical at scale.

How did you approach the problem? Consider why data structures are important to understand.
I analyzed three data structures: vector, hash table, and binary search tree. I compared their time complexity for insertion, search, and sorted output before writing any code. Data structures matter because the wrong choice can turn a fast program into a slow one as data grows. The BST was the clear choice because its in-order traversal produces alphanumerically sorted output naturally, eliminating the need for a separate sorting step altogether.

How did you overcome any roadblocks you encountered while going through the activities or project?
The biggest roadblock was handling edge cases in the input file, like trailing commas producing empty tokens during prerequisite parsing. Breaking the file loading into two passes, one to collect all course numbers for validation, and one to build the course objects is what made the logic easier to reason through and debug one piece at a time.

How has your work on this project expanded your approach to designing software and developing programs?
It reinforced the habit of thinking about data organization before writing code. Choosing a structure based on what operations the program needs most, rather than defaulting to whatever is familiar, leads to cleaner and more efficient solutions.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
Keeping each function responsible for one thing made the code easier to read and modify. When problems arose, like accounting for case sensitivity in the input, the impact was limited to one small function rather than scattered across the whole program.
