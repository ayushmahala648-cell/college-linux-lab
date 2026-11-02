// C++ program to implement FCFS scheduling
#include <iostream>
using namespace std;

// Function to find waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[])
{
    // Waiting time for first process is 0
    wt[0] = 0;

    // Calculate waiting time for remaining processes
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

// Function to calculate turnaround time
void findTurnAroundTime(int processes[], int n, int bt[],
                        int wt[], int tat[])
{
    // Turnaround time = burst time + waiting time
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

// Function to calculate average waiting and turnaround time
void findAverageTime(int processes[], int n, int bt[])
{
    int wt[n], tat[n];

    // Calculate waiting time
    findWaitingTime(processes, n, bt, wt);

    // Calculate turnaround time
    findTurnAroundTime(processes, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;

    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];

        cout << "P" << processes[i] << "\t"
             << bt[i] << "\t\t"
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

    int processes[n], burstTime[n];

    cout << "Enter burst time for each process:\n";

    for (int i = 0; i < n; i++)
    {
        processes[i] = i + 1;

        cout << "P" << processes[i] << ": ";
        cin >> burstTime[i];
    }

    findAverageTime(processes, n, burstTime);

    return 0;
}