#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int main() {
    cout << "=== Parent Process Starting ===" << endl;
    cout << "Parent PID: " << getpid() << endl << endl;
    
    cout << "Creating 5 child processes..." << endl;
    for (int i = 1; i <= 5; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            cerr << "Fork failed!" << endl;
            return 1;
        } 
        else if (pid == 0) {
            int delay_time = (6 - i) * 2;  
            
            sleep(delay_time);
            
            cout << "\n--- Child " << i << " Executing ---" << endl;
            cout << "Child " << i << " PID: " << getpid() << endl;
            cout << "Parent PID: " << getppid() << endl;
            cout << "Delay was: " << delay_time << " seconds" << endl;
            
            exit(0); 
        } 
        else {
            cout << "Created Child " << i << " with PID: " << pid << endl;
        }
    }
    
    cout << "\n=== All children created ===" << endl;
    cout << "Waiting for all children to complete...\n" << endl;

    for (int i = 0; i < 5; i++) {
        int status;
        pid_t completed_pid = wait(&status);
        cout << "Child with PID " << completed_pid << " has completed" << endl;
    }

    cout << "\n=== All children finished ===" << endl;
    cout << "Parent process exiting" << endl;
    
    return 0;
}
