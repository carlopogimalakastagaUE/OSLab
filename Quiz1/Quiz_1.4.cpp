#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    double burst_time, original_burst, arrival_time;
    double completion_time, turnaround_time, waiting_time;
};

void displayGanttChart(vector<pair<int, double>>& gantt) {
    cout << "\n========== GANTT CHART ==========\n+";
    for (auto& g : gantt) cout << "--------+";
    cout << "\n|";
    for (auto& g : gantt) cout << "  P" << g.first << "   |";
    cout << "\n+";
    for (auto& g : gantt) cout << "--------+";
    cout << "\n0";
    double time = 0;
    for (auto& g : gantt) cout << setw(7) << fixed << setprecision(1) << (time += g.second);
    cout << "\n\n";
}

void roundRobinScheduling(vector<Process>& processes, double quantum) {
    cout << "\n========== ROUND ROBIN (Quantum = " << quantum << ") ==========\n";
    
    vector<pair<int, double>> gantt;
    vector<Process> queue = processes;
    double current_time = 0;
    
    while (!queue.empty()) {
        Process p = queue.front();
        queue.erase(queue.begin());
        
        double time_slice = min(p.burst_time, quantum);
        current_time += time_slice;
        p.burst_time -= time_slice;
        gantt.push_back({p.id, time_slice});
        
        if (p.burst_time > 0) {
            queue.push_back(p);
        } else {
            p.completion_time = current_time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.original_burst;
            for (auto& orig : processes) {
                if (orig.id == p.id) { orig = p; break; }
            }
        }
    }
    
    cout << "Process\tBurst\tCompletion\tTurnaround\tWaiting\n";
    cout << "------\t------\t----------\t----------\t-------\n";
    double total_wait = 0, total_tat = 0;
    
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) { return a.id < b.id; });
    
    for (auto& p : processes) {
        cout << "P" << p.id << "\t" << fixed << setprecision(2) << p.original_burst << "\t"
             << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << "\n";
        total_wait += p.waiting_time;
        total_tat += p.turnaround_time;
    }
    
    cout << "\nAvg Waiting: " << fixed << setprecision(2) << (total_wait / processes.size())
         << " | Avg Turnaround: " << (total_tat / processes.size()) << "\n";
    
    displayGanttChart(gantt);
}

int main() {
    vector<double> burst_times = {99.99, 107.9, 143.77, 20.24, 50.55, 66.66};
    vector<Process> processes;
    
    cout << "========== CPU SCHEDULING ==========\n"
         << "Processes: " << burst_times.size() << " | Quantum: 25\nBurst Times: ";
    for (auto& bt : burst_times) cout << fixed << setprecision(2) << bt << " ";
    cout << "\n";
    
    for (int i = 0; i < burst_times.size(); i++) {
        processes.push_back({i + 1, burst_times[i], burst_times[i], 0, 0, 0, 0});
    }
    
    roundRobinScheduling(processes, 25);
    
    cout << "========== END ==========\n";
    return 0;
}
