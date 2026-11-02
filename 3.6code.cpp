//round robin problem

#include <iostream>
using namespace std;

int main() {
    int n, quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n];
    int ct[n], wt[n], tat[n];

    cout << "Enter Arrival Time and Burst Time:\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    int time = 0, completed = 0;
    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    while (completed < n) {
        bool processExecuted = false;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                processExecuted = true;

                if (rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                }
                else {
                    time += rt[i];
                    rt[i] = 0;

                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    completed++;
                }
            }
        }

        // If no process has arrived yet
        if (!processExecuted) {
            time++;
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\t"
         << "Completion Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t"
             << at[i] << "\t\t"
             << bt[i] << "\t\t"
             << ct[i] << "\t\t"
             << wt[i] << "\t\t"
             << tat[i] << endl;

        totalWaitingTime += wt[i];
        totalTurnaroundTime += tat[i];
    }

    cout << "\nAverage Waiting Time = "
         << totalWaitingTime / n << endl;

    cout << "Average Turnaround Time = "
         << totalTurnaroundTime / n << endl;

    return 0;
}