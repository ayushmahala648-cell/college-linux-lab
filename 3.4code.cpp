// preemptive priority scheduling

#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], pr[n], rt[n];
    int ct[n], wt[n], tat[n];

    int time = 0, completed = 0, idx;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    cout << "Enter Arrival Time, Burst Time and Priority:\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> at[i] >> bt[i] >> pr[i];
        rt[i] = bt[i];
    }

    while (completed < n) {
        idx = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 &&
                (idx == -1 || pr[i] < pr[idx])) {
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        rt[idx]--;
        time++;

        if (rt[idx] == 0) {
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tPriority\t"
         << "Completion Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t"
             << at[i] << "\t\t"
             << bt[i] << "\t\t"
             << pr[i] << "\t\t"
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