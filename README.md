# CSE 511: Advanced Algorithms
Assignments done in **_CSE 511: Advanced Algorithms_** course in MS (CSE) program in North South University (NSU).

# Assignment 1
Find the first index where the given target value appears in a given sorted array.

**Sample input**

Enter sorted array: 1 2 3 5 5 5 5 5 8 12  
Enter target: 5

**Sample output**

Leftmost index of target is: 3

# Assignment 2
Compute the number of inversions in a given array.

**Sample input**

Enter sorted array: 12 3 15 4

**Sample output**

Number of inversions: 3

# Assignment 3
Sort an array of students based on their CGPAs in order to assign course registration slots to them. Specifically, student **_A_** should get course registration slot before student **_B_** if **_A_** has higher CGPA than **_B_**.
For example, **_A_** has **_CGPA 3.5_** and **_B_** has **_CGPA 3.2_**, then **_A_** should come before **_B_** in the sorted order.
To do so, create a class called **_Student_** containing some basic information of students such as **_id_**, **_name_**, **_credits completed_**, and **_CGPA_**. Then implement **_Quicksort Algorithm_** using **_random pivot_** with multithreading option to sort these students.

**Sample input**

A text file called **_input.txt_** containing all the information of students. Each line of this file should contain the **_id_**, **_name_**, **_credits completed_**, and **_CGPA_** separated by tabs just like below

<pre>
12345   Abid Raihan     30    3.4
26345   Hafiz Adnan     100   3.24
17345   Jakaria Ahmed   80    2.94
72845   Harun Yahia     100   3.84
23745   Jabid Hannan    80    3.47
</pre>

Also ask the user if he/she wants to run the multithreaded version or single-threaded version of the sorting algorithm and execute the version selected by the user.

**Sample output**

A text file called **_output.txt_** should contain the student-records in sorted order. e.g. for the above input, the **_output.txt_** should look just like below

<pre>
72845   Harun Yahia     100   3.84
23745   Jabid Hannan    80    3.47
12345   Abid Raihan     30    3.40
26345   Hafiz Adnan     100   3.24
17345   Jakaria Ahmed   80    2.94
</pre>

Also show the time taken to complete the sorting (in microsecond or millisecond) in console.

# Assignment 4
Select/find the student with i'th highest CGPA in a given array of students. To do so, create a class called **_Student_** containing some basic information of students such as **_id_**, **_name_**, **_credits completed_**, and **_CGPA_**. Then implement **_Randomized Selection Algorithm_**.

**Sample input**

Just like **_input.txt_** of Assignment-3. Take the value of **_i_** as user input.

**Sample output**

In the console, show all the information of the student having i'th highest CGPA. e.g. if user enters **_i = 3_** then your program should print the following in the console

<pre>
12345   Abid Raihan   30    3.40
</pre>

# Assignment 5
Solve the **_Activity Scheduling Problem_** based on **priority** from a given array of activities using both **_Top-down_** and **_Bottom-up_** approach, where each activity has **_start time_**, **_finishing time_** and **_priority_**.

**Sample input**

A text file called **_input.txt_** containing all the information of activities. Each line of this file should contain the **_start time_**, **_finishing time_** and **_priority_** separated by space just like below

1 10 10  
7 18 20  
13 20 5  
16 27 20  
23 32 15  

**Sample output**

In the console, show all the information of activities that maximize total priority and print the total priority as well. e.g. for the above input, the output should look just like below

<pre>
Select preferred approach:
        [1] Top-down approach
        [2] Bottom-up approach

Selection: 1

Scheduled activities:

Starting time: 23
Finishing time: 32
Priority: 15

Starting time: 7
Finishing time: 18
Priority: 20

Total priority: 35
</pre>

# Project
The primary focus of this project is to develop a faster algorithm to search through **_Unsorted Array_** than any of the existing searching algorithms (e.g. linear search). This algorithm is called **_Bring Front Search_** as it brings the found query to the front of the array.
