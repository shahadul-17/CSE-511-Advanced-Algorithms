#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class activity
{
    public:
        activity()
        {
            // empty constructor...
        }

        int get_starting_time()
        {
            return starting_time;
        }

        void set_starting_time(int starting_time)
        {
            this->starting_time = starting_time;
        }

        int get_finishing_time()
        {
            return finishing_time;
        }

        void set_finishing_time(int finishing_time)
        {
            this->finishing_time = finishing_time;
        }

        int get_priority()
        {
            return priority;
        }

        void set_priority(int priority)
        {
            this->priority = priority;
        }

        string to_string()
        {
            stringstream string_stream;

            string_stream << "Starting time: " << starting_time << "\nFinishing time: " << finishing_time << "\nPriority: " << priority;

            return string_stream.str();
        }

        static activity * load_activities(int &number_of_activities)
        {
            ifstream fileInputStream("input.txt");

            if (!fileInputStream.is_open())
            {
                cout << "error: an error occurred while opening the input file..." << endl << endl;

                return NULL;
            }

            number_of_activities = count(istreambuf_iterator<char>(fileInputStream),
                                        istreambuf_iterator<char>(), '\n') + 1;
            activity *activities = new activity[number_of_activities];

            fileInputStream.seekg(0, ios::beg);         // seeking to the beginning of the stream...

            for (int i = 0; !fileInputStream.eof(); i++)
            {
                fileInputStream >> activities[i].starting_time;
                fileInputStream >> activities[i].finishing_time;
                fileInputStream >> activities[i].priority;
            }

            fileInputStream.close();

            return activities;
        }

    private:
        int starting_time, finishing_time, priority;
};

int get_last_non_clashing_activity(int index, activity *activities)
{
    int starting_time = activities[index].get_starting_time();

    for (int i = index - 1; i > -1; i--)
    {
        if (starting_time >= activities[i].get_finishing_time())
        {
            return i;
        }
    }

    return 0;
}

int top_down_schedule_activity(int index, int *last_non_clashing_activities,
                               int *memory, activity *activities)
{
    if (memory[index] == -1)
    {
        memory[index] = max(activities[index].get_priority() +
            top_down_schedule_activity(last_non_clashing_activities[index],
                last_non_clashing_activities, memory, activities),
            top_down_schedule_activity(index - 1, last_non_clashing_activities,
                memory, activities));
    }

    return memory[index];
}

int bottom_up_schedule_activity(int number_of_activities,
                                int *last_non_clashing_activities, int *memory,
                                activity *activities)
{
    for (int i = 1; i < number_of_activities; i++)
    {
        memory[i] = max(activities[i].get_priority() +
                        memory[last_non_clashing_activities[i]], memory[i - 1]);
    }

    return memory[number_of_activities - 1];
}

void print_scheduled_activities(int index, int *last_non_clashing_activities,
                            int *memory, activity *activities)
{
    if (index < 0)
    {
        return;
    }

    if (activities[index].get_priority() + memory[last_non_clashing_activities[index]] < memory[index - 1])
    {
        print_scheduled_activities(index - 1, last_non_clashing_activities, memory, activities);
    }
    else
    {
        cout << activities[index].to_string() << endl << endl;

        print_scheduled_activities(last_non_clashing_activities[index], last_non_clashing_activities, memory, activities);
    }
}

int main()
{
    int selection, number_of_activities, total_priority,
        *last_non_clashing_activities = NULL, *memory = NULL;

    activity *activities = activity::load_activities(number_of_activities);
    last_non_clashing_activities = new int[number_of_activities];
    memory = new int[number_of_activities];

    for (int i = 0; i < number_of_activities; i++)
    {
        last_non_clashing_activities[i] = get_last_non_clashing_activity(i, activities);
    }

    memory[0] = 0;          // initializing first slot of the memory with zero...

    cout << "Select preferred approach:" << endl << "\t[1] Top-down approach" << endl << "\t[2] Bottom-up approach" << endl << "Selection: ";
    cin >> selection;

    switch (selection)
    {
    case 1:
        memset(memory + 1, -1, sizeof(int) * number_of_activities);     // rest of the memory is filled with -1, needed for top-down approach...

        total_priority = top_down_schedule_activity(number_of_activities - 1, last_non_clashing_activities, memory, activities);

        break;
    case 2:
        total_priority = bottom_up_schedule_activity(number_of_activities, last_non_clashing_activities, memory, activities);

        break;
    default:
        cout << "error: invalid selection..." << endl << endl;

        return -1;
    }

    cout << endl << "Scheduled activities:" << endl << endl;

    print_scheduled_activities(number_of_activities - 1, last_non_clashing_activities, memory, activities);

    cout << "Total priority: " << total_priority << endl;

    delete [] last_non_clashing_activities;
    delete [] memory;
    delete [] activities;

    return 0;
}
