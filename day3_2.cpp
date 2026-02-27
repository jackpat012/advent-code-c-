#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>

using namespace std;

long long joltage(string file, int upTo) {
    ifstream File(file);
    if (!File.is_open()) return 0;

    string line;
    long long totalSum = 0;

    while (getline(File, line)) {
        auto current_pos = line.begin();
        long long currentLineValue = 0;

        for (int i = 0; i < upTo; i++) {
            int required_after = upTo - 1 - i;
            auto search_end = line.end() - required_after;

            if (current_pos >= search_end) break; // Safety check

            // Find the largest digit in the range
            auto max_it = max_element(current_pos, search_end);
            
            // Convert char to int and add to our number
            int digit = *max_it - '0';
            currentLineValue = currentLineValue * 10 + digit;

            current_pos = next(max_it);
        }
        totalSum += currentLineValue;
    }
    return totalSum;
}

int main() {
    auto begin = chrono::steady_clock::now();

    long long result = joltage("input.txt", 12);
    auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - begin);
    cout << "Result: " << result << endl;
    cout << "Time: " << duration.count() << " microseconds" << endl; // ~260 microseconds AMD 7800X3D Arch

    return 0;
}
