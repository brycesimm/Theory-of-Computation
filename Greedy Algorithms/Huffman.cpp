#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;
// Global parallel vectors that are later used for storing characters and 
// their codes from a binary tree 
vector<string> characters;
vector<string> codes;

// Nodes are used to build the binary tree through the use of left and right children
// data is the node's frequency value, while character is the node's character value
struct Node {
    int data;
    string character;
    struct Node* left;
    struct Node* right;
 
    Node(int val){
        data = val;
        left = NULL;
        right = NULL;
    }

    Node(string str){
        character = str;
        left = NULL;
        right = NULL;
    }
};

void printLeafNodes(Node* root, string str);

// function to print leaf
// nodes from left to right
// str keeps track of branches traversed which will be converted to a code
void printLeafNodes(Node* root, string str)
{
    // if node is null, return
    if (!root)
        return;
     
    // if node is leaf node, push it to global vectors  
    if ((root -> left == NULL) && (root -> right == NULL))
    {
        characters.push_back(root -> character);
        codes.push_back(str);
        return;
    }
 
    // if left child exists, check for leaf
    // recursively 
    // 0 is appended for every left-move
    if (root -> left != NULL){
       str.append("0");
       printLeafNodes(root -> left, str);
    }

    // Remove last element before going to right-side branch
    str.pop_back();

    // if right child exists, check for leaf
    // recursively
    // 1 is appended for every left-move
    if (root -> right != NULL){
       str.append("1");
       printLeafNodes(root -> right, str);
    }
}

int main() {
    
    fstream inputFile("freq.txt");
	string space = " ";
    string tempStr = "";
    vector<string> charvec;
    vector<int> freqvec;

	// Takes each line as input string, splits it into 2 disregrading a space between
    // the character and its frequency value
    // The character and frequency are both pushed into their relevant vectors
    int pos = 0;
	while (getline(inputFile, tempStr)) {
        pos = tempStr.find(space);
        charvec.push_back(tempStr.substr(0, pos));
        freqvec.push_back(stoi(tempStr.substr(pos + 1)));
	}
	inputFile.close();
    
    // Echos the iinput received from the input file
    cout << "Input from file: " << endl;
    for(int i = 0; i < charvec.size(); i++){
        cout << setw(2) << charvec[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < freqvec.size(); i++){
        cout << setw(2) << freqvec[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Sorts the frequency and character vectors at the same time
    // to preserve parallelism
    for (int i = 0 ; i < freqvec.size(); i++) {    
        for(int j = 0; j < freqvec.size(); j++){ 
            if(freqvec[i] < freqvec[j]){
                swap(freqvec[i], freqvec[j]);
                swap(charvec[i], charvec[j]);
            }
        }
    }

    // Prints out the input from the file in sorted order
    cout << "Sorted Input: " << endl;
    for(int i = 0; i < charvec.size(); i++){
        cout << setw(2) << charvec[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < freqvec.size(); i++){
        cout << setw(2) << freqvec[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Fills up list of nodes with the sorted values of characters and frequencies
    vector<Node*> Nodes;
    for(int i = 0; i < freqvec.size(); i++){
        Node* temp = new Node(freqvec[i]);
        temp -> character = charvec[i];
        Nodes.push_back(temp);
    }

    cout << "Algorithm Iterations: " << endl;

    // Beginning of Huffman Encoding algorithm
    for(int i = 0; i < freqvec.size(); i++){

        // Prints out each step of algorithm
        for(int k = 0; k < Nodes.size(); k++){
            cout << setw(2) << Nodes[k] -> data << " ";
        }
        cout << endl;

        // Create a node "temp" with frequency f(temp) = f(0) + f(1), 
        // temp's children are 0 and 1
        Node* temp = new Node(Nodes[0] -> data + Nodes[1] -> data);

        temp -> left = Nodes[0];
        temp -> right = Nodes[1];

        // Remove nodes 0 and 1 from the list of Nodes
        Nodes.erase(Nodes.begin());
        Nodes.erase(Nodes.begin());

        // If list becomes empty, push last node into L and we're done
        if(Nodes.size() == 0){
            Nodes.push_back(temp);
            break;
        }
        // Inserts temp node into correct position in Nodes list
        for(int j = 0; j < Nodes.size(); j++){
            // If you find a node with a higher frequency in the list, place temp before it
            if(Nodes[j] -> data > temp -> data){
                Nodes.insert((Nodes.begin() + j), temp);
                break;
            }
            // Insert into back of the list if greater than all elements
            if(j == Nodes.size() - 1){
                Nodes.push_back(temp);
                break;
            }
        }
    }

    // Prints out last iteration of Nodes list, should only have one node left
    for(int k = 0; k < Nodes.size(); k++){
        cout << setw(2) << Nodes[k] -> data << " ";
    }
    cout << endl;

    // Prints out leaf nodes from left to right, keeping track of branches for encoding
    // Also adds characters and codes to global vectors
    printLeafNodes(Nodes[0], "");
    cout << endl;

    // Take global vectors of characters and their codes and order them according to their
    // ASCII value
    int min = 0;
    for(int i = 0; i < characters.size(); i++){
        for(int j = i + 1; j < characters.size(); j++){
            if(characters[j] < characters[i]){
                string tempChar = characters[i];
                string tempCode = codes[i];
                characters[i] = characters[j];
                characters[j] = tempChar;
                codes[i] = codes[j];
                codes[j] = tempCode;
            }
        }
    }

    // Open output file to write to
    ofstream outputFile("codetable.txt");
    if(!outputFile) { 
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    // Print out ordered characters and codes
    // Also write characters and their codes to the output file
    for(int i = 0; i < characters.size(); i++){
        cout << setw(2) << "Character: " << characters[i] << " Code: " << codes[i] << endl;
        outputFile << characters[i] << " " << codes[i] << endl;
    }
    outputFile.close();
}