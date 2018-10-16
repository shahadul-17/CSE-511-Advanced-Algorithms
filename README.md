# CSE-511-Advanced-Algorithms
Assignments done in "advanced algorithms" course in MS (CSE) program in North South University (NSU).

# Assignment-1
Find the first index where the given target value appears in a given sorted array.

**Sample input**

Enter sorted array: 1 2 3 5 5 5 5 5 8 12
Enter target: 5

**Sample output**

Leftmost index of target is: 3

# Assignment-2
Compute the number of inversions in a given an array.

**Sample input**

Enter sorted array: 12 3 15 4

**Sample output**

Number of inversions: 3

# Assignment-3
Sort an array of students based on their CGPAs in order to assign course registration slots to them. Specifically, student 'A' should get course registration slot before student 'B' if 'A' has higher CGPA than 'B'.
For example, 'A' has CGPA 3.5 and 'B' has CGPA 3.2, then 'A' should come before 'B' in the sorted order.
To do so, create a class called "Student" containing some basic information of students such as id, name, credits completed, and CGPA. Then implement **_Quicksort Algorithm_** using **_random pivot_** with multithreading option to sort these students.

**Sample input**

A text file called **_input.txt_** containing all the information of students. Each line of this file should contain the id, name, credits completed, and CGPA separated by tabs just like below

12345	Abid Raihan			30		3.4
26345	Hafiz Adnan			100		3.24
17345	Jakaria Ahmed		80		2.94
72845	Harun Yahia			100		3.84
23745	Jabid Hannan		80		3.47

Also ask the user if he/she wants to run the multithreaded version or single-threaded version of the sorting algorithm and execute the version selected by the user.

**Sample output**

A text file called **_output.txt_** should contain the student-records in sorted order. e.g. for the above input, the **_output.txt_** should look just like below

72845	Harun Yahia			100		3.84
23745	Jabid Hannan		80		3.47
12345	Abid Raihan			30		3.40
26345	Hafiz Adnan			100		3.24
17345	Jakaria Ahmed		80		2.94

Also show the time taken to complete the sorting (in microsecond or millisecond) in console.

# Assignment-4
Select/find the student with i'th highest CGPA in a given array of students. To do so, create a class called "Student" containing some basic information of students such as id, name, credits completed, and CGPA. Then implement **_Randomized Selection Algorithm_**.

**Sample input**

Just like **_input.txt_** of Assignment-3. Take the value of 'i' as user input.

**Sample output**

In the console, show all the information of the student having i'th highest CGPA. e.g. if user enters **_i = 3_** then your program should print the following in the console

12345	Abid Raihan			30		3.4