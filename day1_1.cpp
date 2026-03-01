#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

int rotary(string filename) {
	ifstream File(filename);						// Read text file in
	string line;
	
	int M = 100;									// Size of Ring
	int startPos = 50;								// Starting position of "Dial".
	int counter = 0;

	if (File.is_open()) {
		while (getline(File, line)) {				// Iterate through all lines of file.
			int num = stoi(line.substr(1));			// Convert numeric portion of line string to integer.
			if (line[0] == 'L') {					// If 'L', convert integer to negative.
				num = -num;
			}
			startPos = (startPos + num) % M;		// Modulo arithmetic
			if (startPos == 0) {
				counter++;							// If position = 0, add to counter.
			}
		}
	}
	return counter;									// Passcode = Counter after all line iterations complete.
}

int main() {
	auto start = chrono::high_resolution_clock::now();
	int result = rotary("input.txt");
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << "Result: " << result << endl;
	cout << "Time taken: " << duration.count() << " microseconds." << endl;	 // ~700 microseconds AMD 7800X3D Arch

	return 0;
}
