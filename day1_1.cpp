#include <iostream>
#include <fstream>
#include <string>

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

	cout << rotary("input.txt");

	return 0;
}
