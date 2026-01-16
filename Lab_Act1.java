import java.io.IOException;

public class Lab_Act1 {}
public static void main(String[] args) { try {
// Create a process that runs "whoami" ProcessBuilder pb = new ProcessBuilder("whoami");
pb.inheritIO(); // let child process output show in parent's

console

Process process = pb.start();	// similar to fork + exec

// Print parent process ID
long pid = ProcessHandle.current().pid(); System.out.println("\nProcess ID is: " + pid);

// Wait for child process to finish process.waitFor();

} catch (IOException e) { System.out.println("Process creation failed"); e.printStackTrace();
