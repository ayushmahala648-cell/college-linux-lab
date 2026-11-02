// C++ program to implement Preemptive SJF
// (Shortest Remaining Time First) scheduling

#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int processes[n], burstTime[n], arrivalTime[n];
    int remainingTime[n], waitingTime[n], turnAroundTime[n];

    cout << "Enter arrival time and burst time for each process:\n";

    for (int i = 0; i < n; i++)
    {
        processes[i] = i + 1;

        cout << "P" << processes[i] << " Arrival Time: ";
        cin >> arrivalTime[i];

        cout << "P" << processes[i] << " Burst Time: ";
        cin >> burstTime[i];

        remainingTime[i] = burstTime[i];
        waitingTime[i] = 0;
        turnAroundTime[i] = 0;
    }

    int completed = 0;
    int currentTime = 0;

    // Continue until all processes are completed
    while (completed != n)
    {
        int shortest = -1;
        int minimum = 9999;

        // Find the process with the shortest remaining time
        // among the processes that have arrived
        for (int i = 0; i < n; i++)
        {
            if (arrivalTime[i] <= currentTime &&
                remainingTime[i] > 0 &&
                remainingTime[i] < minimum)
            {
                minimum = remainingTime[i];
                shortest = i;
            }
        }

        // If no process has arrived yet
        if (shortest == -1)
        {
            currentTime++;
            continue;
        }

        // Execute the selected process for 1 unit of time
        remainingTime[shortest]--;
        currentTime++;

        // If process is completed
        if (remainingTime[shortest] == 0)
        {
            completed++;

            // Turnaround Time = Completion Time - Arrival Time
            turnAroundTime[shortest] =
                currentTime - arrivalTime[shortest];

            // Waiting Time = Turnaround Time - Burst Time
            waitingTime[shortest] =
                turnAroundTime[shortest] - burstTime[shortest];
        }
    }

    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];

        cout << "P" << processes[i] << "\t"
             << arrivalTime[i] << "\t\t"
             << burstTime[i] << "\t\t"
             << waitingTime[i] << "\t\t"
             << turnAroundTime[i] << endl;
    }

    cout << "\nAverage Waiting Time = "
         << (float)totalWaitingTime / n;

    cout << "\nAverage Turnaround Time = "
         << (float)totalTurnAroundTime / n << endl;

    return 0;
}