#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

using namespace std;

int peakSearch(vector<int> v, int size);

int main() {

	// Uses text file as input, vector as container, and string to receive characters
	fstream inputFile("peak.txt");
	vector<int> vector;
	string tempStr = "";

	// Takes each line as input string, converts to int, and puts into vector
	while (getline(inputFile, tempStr)) {
		int tempInt = stoi(tempStr);
		vector.push_back(tempInt);
	}
	inputFile.close();

	// Search for peak index
	int peakIndex = peakSearch(vector, vector.size());

	cout << "Peak occurs at index: " << peakIndex << " and the peak value is: " << vector[peakIndex] << endl;
}

/* Takes vector of integers v, and the size of the vector v to find peak value's index
 This method uses a lower bound, upper bound, and middle index to hone in on the peak value
 The middle index, mid, is updated to be between the lower bound and upper bound after each iteration
 After every iteration, the portion of the vector we search gets reduced by half as we either raise
 the lower bound to mid's right neighbor or lower the upper bound to mid's left neighbor.
 Eventually the two bounds will overlap and the peak will be found in logn time. */
int peakSearch(vector<int> v, int size) {
	int mid = 0;
	int upper = size - 1;
	int lower = 0;

	// If the vector only has one element, return that element
	if (size == 1) {
		return 0;
	}
	// Lower bound must be less than or equal to the upper bound
	while (lower <= upper) {
		// Find the middle between the bounds in the vector
		mid = (upper + lower) / 2;
		// If the middle is the first element, check that it is greater than its right neighbor to confirm a peak
		if (mid == 0) {
			if (v[mid] > v[mid + 1]) {
				return mid;
			}
		}
		// If the middle is the last element, check that it is greater than its left neighbor to confirm a peak
		else if (mid == (size - 1)) {
			if (v[mid] > v[mid - 1]) {
				return mid;
			}
		}
		// If the middle is in a position where it is greater than both neighbors, it is a peak
		else if (v[mid] > v[mid - 1] && v[mid] > v[mid + 1]) {
			return mid;
		}
		// Make sure that mid is not on the edge and the value at mid is less than its left neighbor
		// This means we need to lower the upper bound to mid's left neighbor
		if (mid > 0 && v[mid] < v[mid - 1]) {
			upper = mid - 1;
		}
		// Otherwise, we need to move lower up to mid's right neighbor
		else {
			lower = mid + 1;
		}
	}
	return mid;
}