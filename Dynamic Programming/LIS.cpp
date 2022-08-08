#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(){

    // Uses text file as input, vector as container, and string to receive characters
	fstream inputFile("incseq.txt");
	vector<int> vector;
	string tempStr = "";

	// Takes each line as input string, converts to int, and puts into vector
	while (getline(inputFile, tempStr)) {
		int tempInt = stoi(tempStr);
		vector.push_back(tempInt);
	}
	inputFile.close();

    // Creates an array to take values from vector and another array to keep track of subsequence lengths at each index
    int n = vector.size();
    int* arr = new int[n];
    int* L = new int[n];

    // Transfer contents of vector to array and set all elements in L to 1
    // Dealing with an array is easier due to vector complaining about subscript errors
    for (int i = 0; i < n; i++){
        arr[i] = vector[i];
        L[i] = 1;
    }

    // Algorithm for finding subsequence lengths at an index; 
    // For each element of arr, go through previous elements and find one that is smaller and has
    // a maximum length in L
    for(int i = 0; i < n; i++){
        for(int j = i-1; j >= 0; j--){
            if(arr[j] < arr[i] && L[i] < L[j] + 1){
                L[i] = L[j] + 1;
            }
        }
    }

    // This goes through the array L to find the maximum value,
    // which is the length of the longest increasing subsequence
    int maxLen = 0;
    int maxIndex = 0;
    for(int i = 0; i < n; i++){
        if(L[i]>maxLen){
            maxLen = L[i];
            maxIndex = i;
        }
    }

    // Output input sequence and L[i] table
    cout << endl;
    cout << "Input sequence: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "L[i] table: ";
    for(int i = 0; i < n; i++){
        cout << L[i] << " ";
    }
    cout << endl;

    // This will go through the entire array and find the elements of the longest increasing subsequence
    // It works backwards in that it starts with the element at the end of the subsequence with length L[maxIndex]
    // and then moves back through the previous elements. When a previous element has a value in L that is 1 
    // less than L[maxIndex], its corresponding value in arr is added to the subsequence
    // The result stored in seq[] is then printed in order at the end
    int sz = maxLen;
    int* seq = new int[sz];
    sz--;
    // We already know the last element of the subsequence
    seq[sz] = arr[maxIndex];
    // Starting at the element previous to the last element of the subsequence, work backwards
    for (int i = maxIndex-1; i >= 0; i--){
        // If L[maxIndex] - L[i] == 1, then arr[i] must be the previous element in the subsequence
        if(L[maxIndex]-L[i]==1){
            sz--;
            L[maxIndex]--;
            seq[sz] = arr[i];
        }
    }

    // Output Length and Subsequence
    cout << "Longest Increasing Subsequence Length: " << maxLen << endl;
    cout << "Longest Increasing Subsequence: ";
    for (int i = 0; i < maxLen; i++){
        cout << seq[i] << " ";
    }
    cout << endl;
}