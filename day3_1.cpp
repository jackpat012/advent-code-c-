#include <string>
#include <fstream>
#include <chrono>
#include <iostream>
#include <algorithm>

using namespace std;

int joltage(string file) {
	string line;
	ifstream File(file);
	int sum = 0;

	while (getline(File, line)) {																		
		auto first_it = max_element(line.begin(), line.end() - 1);										// Find first index and value of highest number (besides last number in row).
		int index1 = distance(line.begin(), first_it);

		auto second_it = max_element(next(first_it), line.end());										// Find value of next highest number in row.
		int index2 = distance(line.begin(), second_it);

		int firstNum = (line[index1] - '0') * 10;														
		int secondNum = line[index2] - '0';

		sum += (firstNum + secondNum);																	// Combine chars and create number.
	}
	return sum;
}

int main() {

	auto begin = chrono::steady_clock::now();
	int result = joltage("input.txt");
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - begin);
	cout << "Result: " << result << endl;
	cout << "Time: " << duration << endl;																// ~2ms on AMD 7800X3D.
	return 0;
}
