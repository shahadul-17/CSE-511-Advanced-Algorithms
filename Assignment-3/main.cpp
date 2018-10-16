#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <pthread.h>        // in latest CodeBlocks, this POSIX Thread header file is part of the default installation...

using namespace std;

class student
{
    public:
        student()
        {
            name[0] = '\0';
            id = credits_completed = 0;
            cgpa = 0.0;
        }

        char * get_name()
        {
            return name;
        }

        int get_id()
        {
            return id;
        }

        int get_credits_completed()
        {
            return credits_completed;
        }

        double get_cgpa()
        {
            return cgpa;
        }

        static void store_students(int number_of_students, student *students)
        {
            FILE *file = fopen("output.txt", "w");

            if (file == NULL)
            {
                printf("error: an error occurred while opening the file...\n\n");

                return;
            }

            for (int i = 0; i < number_of_students; i++)
            {
                fprintf(file, "%d\t\t%s\t\t%d\t\t%.2lf\n", students[i].id, students[i].name, students[i].credits_completed, students[i].cgpa);
            }

            fclose(file);
        }

        static student * load_students(int *number_of_students)
        {
            FILE *file = fopen("input.txt", "r");

            if (file == NULL)
            {
                *number_of_students = 0;

                return NULL;
            }

            int maximum_characters_in_line = 0;

            *number_of_students = analyze_file(&maximum_characters_in_line, file);

            char line[maximum_characters_in_line];         // assuming each line will contain 200 characters at max...

            student * students = new student[*number_of_students];          // number of lines indicates the number of student information available in text file...

            for (int i = 0; i < *number_of_students && !feof(file); i++)
            {
                if (line != fgets(line, maximum_characters_in_line, file))
                {
                    break;
                }

                int line_length = strlen(line);

                if (line[line_length - 1] == '\n')          // this basically removes new-line character...
                {
                    line[line_length - 1] = '\0';
                }

                students[i] = to_student(line, line_length);
            }

            fclose(file);

            return students;
        }

    protected:

    private:
        char name[25];
        int id, credits_completed;
        double cgpa;

        // returns number of lines in the file...
        // also counts the maximum number of characters available in a single line...
        static int analyze_file(int *maximum_characters_in_line, FILE *file)
        {
            char character = '\0';
            int temp = 0, lines = 0;

            *maximum_characters_in_line = 1;

            while (!feof(file))
            {
                character = fgetc(file);

                if (character == '\n' || character == -1)
                {
                    if (temp < *maximum_characters_in_line)
                    {
                        temp = *maximum_characters_in_line;
                    }

                    *maximum_characters_in_line = 1;

                    lines++;
                }

                (*maximum_characters_in_line)++;
            }

            *maximum_characters_in_line = temp;

            fseek(file, 0, SEEK_SET);       // seeks the file back to beginning...

            return lines;
        }

        // converts string (array of characters) to student object...
        static student to_student(char *line, int line_length)
        {
            char temp[line_length];
            int information_count = 0;

            student student_information;

            for (int i = 0, j = 0; i <= line_length; i++)
            {
                if (line[i] == '\t' || line[i] == '\0')
                {
                    if (temp[0] != '\0')        // already stored the info...
                    {
                        temp[j] = '\0';
                        j = 0;

                        switch (information_count)
                        {
                        case 0:
                            student_information.id = atoi(temp);

                            break;
                        case 1:
                            strcpy(student_information.name, temp);

                            break;
                        case 2:
                            student_information.credits_completed = atoi(temp);

                            break;
                        case 3:
                            student_information.cgpa = atof(temp);

                            break;
                        default:
                            break;
                        }

                        temp[0] = '\0';
                        information_count++;
                    }

                    continue;
                }

                temp[j] = line[i];

                j++;
            }

            return student_information;
        }
};

// this structure is used to pass parameter to threads...
struct thread_parameter
{
    int start_index, end_index, number_of_threads;

    student *students;
};



// swaps two values of specified indices in the 'students' array...
void swap(int first_index, int second_index, student *students)
{
    student temp = students[first_index];
    students[first_index] = students[second_index];
    students[second_index] = temp;
}

int partition(int start_index, int end_index, student *students)
{
    int partitioning_index = start_index - 1, temp_cgpa = -1,
        pivot = (int)(students[end_index].get_cgpa() * 100);     // we are converting double to int just to avoid error while comparing two double variables...

    for (int i = start_index; i < end_index; i++)
    {
        temp_cgpa = (int)(students[i].get_cgpa() * 100);    // we are converting double to int just to avoid error while comparing two double variables...

        if (pivot <= temp_cgpa)
        {
            partitioning_index++;

            swap(i, partitioning_index, students);
        }
    }

    partitioning_index++;

    swap(partitioning_index, end_index, students);

    return partitioning_index;
}

int randomized_partition(int start_index, int end_index, student *students)
{
    srand(time(NULL));
    swap(start_index + (rand() % (end_index - start_index)), end_index, students);

    return partition(start_index, end_index, students);
}

void randomized_quick_sort(int start_index, int end_index, student *students)
{
    if (start_index < end_index)
    {
        int partitioning_index = randomized_partition(start_index, end_index, students);

        randomized_quick_sort(start_index, partitioning_index - 1, students);
        randomized_quick_sort(partitioning_index + 1, end_index, students);
    }
}

void * multithreaded_randomized_quick_sort(void *argument)
{
    struct thread_parameter *parameter = (struct thread_parameter *)argument;

    if ((*parameter).number_of_threads < 2)
    {
        randomized_quick_sort((*parameter).start_index, (*parameter).end_index, (*parameter).students);
    }
    else
    {
        if ((*parameter).start_index < (*parameter).end_index)
        {
            int partitioning_index = randomized_partition((*parameter).start_index, (*parameter).end_index, (*parameter).students);

            struct thread_parameter parameters[2];      // two parameters to be passed on two threads...

            parameters[0].start_index = (*parameter).start_index;
            parameters[0].end_index = partitioning_index - 1;

            parameters[1].start_index = partitioning_index + 1;
            parameters[1].end_index = (*parameter).end_index;

            parameters[0].number_of_threads =
                    parameters[1].number_of_threads =
                            (*parameter).number_of_threads / 2;
            parameters[0].students = parameters[1].students = (*parameter).students;

            pthread_t threads[2];       // two threads for two partitions of the array...

            for (int i = 0; i < 2; i++)
            {
                // POSIX thread creation fails due to insufficient resource...
                if (pthread_create(&threads[i], NULL, multithreaded_randomized_quick_sort, (void *)(&parameters[i])) != 0)
                {
                    cout << "error: thread creation failed...!!!" << endl;
                }
            }

            for (int i = 0; i < 2; i++)     // waiting for both threads to finish...
            {
                pthread_join(threads[i], NULL);
            }
        }
    }

    return NULL;
}

int main()
{
    int selection = 1, number_of_threads = 2, number_of_students = 0;
    long time = 0L;

    student *students = student::load_students(&number_of_students);     // loading student information from file...

    cout << "Specify the version of sorting you would like to perform:\n"
        << "\t1. Single-threaded\n\t2. Multithreaded" << endl << "Selection: ";

    cin >> selection;

    if (selection < 2)
    {
        time = clock();
        randomized_quick_sort(0, number_of_students - 1, students);
        time = clock() - time;
    }
    else
    {
        cout << "Specify the number of threads: ";
        cin >> number_of_threads;

        struct thread_parameter parameter;

        parameter.number_of_threads = number_of_threads;
        parameter.start_index = 0;
        parameter.end_index = number_of_students - 1;
        parameter.students = students;

        time = clock();     // ignoring the time to initialize the thread_parameter...
        multithreaded_randomized_quick_sort((void *)(&parameter));
        time = clock() - time;
    }

    cout << endl << "Time required for sorting: " << (double)time / CLOCKS_PER_SEC << " seconds" << endl;

    student::store_students(number_of_students, students);      // writes the 'students' array to file...

    return 0;
}
