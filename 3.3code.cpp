// C++ program to implement Non-Preemptive SJF
// (Shortest Job First) scheduling

#include <iostream>
using namespace std;

// Function to find waiting time and completion time
void findWaitingTime(int processes[], int n, int at[],
                     int bt[], int wt[], int ct[])
{
    bool completed[n];

    for (int i = 0; i < n; i++)
        completed[i] = false;

    int currentTime = 0;
    int completedCount = 0;

    while (completedCount < n)
    {
        int shortest = -1;
        int minBurst = 9999;

        // Find process with shortest burst time
        // among the processes that have arrived
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= currentTime &&
                !completed[i] &&
                bt[i] < minBurst)
            {
                minBurst = bt[i];
                shortest = i;
            }
        }

        // If no process has arrived
        if (shortest == -1)
        {
            currentTime++;
            continue;
        }

        // Execute selected process completely-------------------------------------------------------------------------------
        currentTime += bt[shortest];

        // Completion time
        ct[shortest] = currentTime;

        // Waiting time = CT - AT - BT
        wt[shortest] =
            ct[shortest] - at[shortest] - bt[shortest];

        completed[shortest] = true;
        completedCount++;
    }
}

// Function to find turnaround time
void findTurnAroundTime(int processes[], int n,
                        int at[], int bt[], int wt[],
                        int tat[])
{
    // Turnaround Time = CT - AT
    // Since TAT = WT + BT
    for (int i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];
}

// Function to calculate average waiting and turnaround time
void findAverageTime(int processes[], int n,
                     int at[], int bt[])
{
    int wt[n], tat[n], ct[n];

    // Calculate waiting time and completion time
    findWaitingTime(processes, n, at, bt, wt, ct);

    // Calculate turnaround time
    findTurnAroundTime(processes, n, at, bt, wt, tat);

    int total_wt = 0;
    int total_tat = 0;

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];

        cout << "P" << processes[i] << "\t"
             << at[i] << "\t\t"
             << bt[i] << "\t\t"
             << ct[i] << "\t\t"
             << wt[i] << "\t\t"
             << tat[i] << endl;
    }

    cout << "\nAverage Waiting Time = "
         << (float)total_wt / n;

    cout << "\nAverage Turnaround Time = "
         << (float)total_tat / n << endl;
}

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int processes[n], arrivalTime[n], burstTime[n];

    cout << "Enter Arrival Time and Burst Time for each process:\n";

    for (int i = 0; i < n; i++)
    {
        processes[i] = i + 1;

        cout << "P" << processes[i] << ": ";
        cin >> arrivalTime[i] >> burstTime[i];
    }

    findAverageTime(processes, n, arrivalTime, burstTime);

    return 0;
}