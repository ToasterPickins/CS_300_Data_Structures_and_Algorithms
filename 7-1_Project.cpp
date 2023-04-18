#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

//Course structure
struct Course {
	string courseNumber;
	string courseName;
	vector<string> preReqs;
	
	Course() {
	}

	Course(string courseNumber, string courseName, vector<string> preReqs) {
		this->courseNumber = courseNumber;
		this->courseName = courseName;
		this->preReqs = preReqs;
	}
};

//Course node structure
struct courseNode {
	Course course;
	courseNode* left;
	courseNode* right;

	courseNode() {
		left = nullptr;
		right = nullptr;
	}

	courseNode(Course course) : courseNode() {
		this->course = course;
	}
};


//Binary search tree class
class BinarySearchTree {
private:
	courseNode* root;

	void p_printAll(courseNode* node);

public:
	BinarySearchTree();
	void Insert(Course course);
	void PrintAll();
	void PrintOne(string courseNumber);
};

//Binary search tree constructor
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

//Binary search tree private methods

/**
* Prints all courses using a recursive in-order search
* @param node: current node for in-order search
* @returns void
*/
void BinarySearchTree::p_printAll(courseNode* node) {
	if (node != nullptr) {
		p_printAll(node->left);

		//Output course information formatted as "courseNumber, courseName"
		cout << node->course.courseNumber << ", ";
		cout << node->course.courseName << endl;

		p_printAll(node->right);
	}
}

//Binary search tree public methods

/**
* Adds a course to the binary search tree
* @param course: Course to add
* @returns void
*/
void BinarySearchTree::Insert(Course course) {
	//If tree is empty, add course to root
	if (root == nullptr) {
		root = new courseNode(course);
	}
	
	//Tree is not empty. Add to appropriate branch
	else {
		courseNode* current = root;
		while (current != nullptr) {

			//If course to add matches current, do nothing. Prevents adding duplicates
			if (course.courseNumber == current->course.courseNumber) {
				return;
			}

			//Left branch: either add new node or move to left and cycle again
			else if (course.courseNumber < current->course.courseNumber) {
				if (current->left == nullptr) {
					current->left = new courseNode(course);
					current = nullptr;
				}
				else {
					current = current->left;
				}
			}

			//Right branch: either add new node or move to right and cycle again
			else {
				if (current->right == nullptr) {
					current->right = new courseNode(course);
					current = nullptr;
				}
				else {
					current = current->right;
				}
			}
		}

	}
}

/**
* Prints all items in the binary search tree. Uses private print all method
* with root given as parameter to ensure that all PrintAll calls print all
* items in the binary search tree.
* @param none
* @returns void
*/
void BinarySearchTree::PrintAll() {
	//Call private method to print all starting at root
	p_printAll(root);
}

/**
* Searched for and prints one items in the binary search tree
* @param courseNumber: Course number to search for
* @returns void
*/
void BinarySearchTree::PrintOne(string courseNumber) {
	//Start at root and cycle through nodes to find correct course
	courseNode* current = root;
	while (current != nullptr) {
		
		//Course found
		if (current->course.courseNumber == courseNumber) {
			cout << current->course.courseNumber << ", ";
			cout << current->course.courseName << endl;
			cout << "Prerequisites: ";
			switch (current->course.preReqs.size()) {
			case 0:
				cout << "none" << endl;
				break;
			case 1:
				cout << current->course.preReqs.at(0) << endl;;
				break;
			default:
				for (int i = 0; i < (current->course.preReqs.size() - 1); i++) {
					cout << current->course.preReqs.at(i) << ", ";
				}
				cout << current->course.preReqs.back();
			}
			return;
		}

		//Course not found at current node, move to correct branch and search again
		else if (courseNumber < current->course.courseNumber) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	//Course not found in binary search tree
	cout << "Course not found" << endl;
}

/**
* Skips the byte order mark if present at the beginning of an input file. Code found from:
* https://stackoverflow.com/questions/10417613/c-reading-from-file-puts-three-weird-characters
* @param in: File input stream passed in by reference
* @return void
*/
void skipBOM(ifstream& in) {
	char test[3] = { 0 };
	
	//Read and extract the first 3 characters from the file
	in.read(test, 3);
	
	//If first three characters match BOM then return. Since file stream passed by reference, the stream will still be at the 4th character
	if ((unsigned char)test[0] == 0xEF && (unsigned char)test[1] == 0xBB && (unsigned char)test[2] == 0xBF) {
		return;
	}

	//Else move input position indicator back to start of file so no characters are lost
	else {
		in.seekg(0);
	}
}

/**
* Opens the input file, reads and parses contents, then builds binary search tree
* @param BST: Binary search tree (passed by reference) to add new courses to
* @param fileName: Name of the file to read from
* @return void
*/
void loadDataStructure(BinarySearchTree& BST, string fileName) {
	//create variables used in code
	ifstream inFS;
	istringstream inSS;
	string tempLine;
	string tempString;
	int descriptionPart;
	string courseID;
	string courseName;
	vector<string> coursePreReqs;


	//Attempt to open file
	inFS.open(fileName);
	if (!inFS.is_open()) {
		cout << "Could not open file";
		return;
	}

	//Skip byte order mark if present
	skipBOM(inFS);

	//While file stream is still good, read each line and store in tempLine variable
	while (inFS.good()) {
		getline(inFS, tempLine);
		if (!tempLine.empty()) {

			//Pass line into a string stream for parsing
			inSS.str(tempLine);

			//reset descriptionPart count and coursePreReqs vector
			descriptionPart = 0;
			coursePreReqs.clear();

			//While string stream is still good, read each comma separated value and store in tempString variable
			while (inSS.good()) {
				getline(inSS, tempString, ',');

				//Move value in tempString to correct course struct variable based on current desriptionPart value
				switch (descriptionPart) {
				//Course ID
				case 0:
					courseID = tempString;
					break;
				//course name
				case 1:
					courseName = tempString;
					break;
				//Pre reqs. This case repeats as many times as necessary for variable number of pre reqs
				default:
					coursePreReqs.push_back(tempString);
					break;
				}

				//Increment descriptionPart variable
				descriptionPart++;
			}

			//Check if missing course information
			if (descriptionPart < 2) {
				cout << "Error: course information for " << courseID << " is not complete and will not be added." << endl;
			}

			//Add course to binary search tree
			else {
				BST.Insert(*new Course(courseID, courseName, coursePreReqs));
			}
			inSS.clear();
		}
	}
	inFS.close();
}

/**
* Main function
*/
int main() {
	BinarySearchTree* bst = new BinarySearchTree();
	int userChoice;
	string fileName;
	string courseToPrint;
	cout << "Welcome to the course planner." << endl;
	
	//main loop of programm
	while (true) {
		cout << endl;
		cout << "   1. Load Data Structure" << endl;
		cout << "   2. Print Course List" << endl;
		cout << "   3. Print Course" << endl;
		cout << "   9. Exit" << endl;
		cout << endl;
		cout << "Please select an option: ";
		cin >> userChoice;
		cout << endl;

		switch (userChoice) {
		//load data to binary search tree
		case 1:
			cout << "Please enter name of file to load: ";
			cin >> fileName;
			cout << "Loading data..." << endl;
			loadDataStructure(*bst, fileName);
			cout << "Data load finished" << endl;
			break;
		//Print all courses
		case 2:
			bst->PrintAll();
			break;
		//print select course
		case 3:
			cout << "What course do you want to know about? ";
			cin >> courseToPrint;
			//transform input to uppercase
			transform(courseToPrint.begin(), courseToPrint.end(), courseToPrint.begin(), toupper);
			bst->PrintOne(courseToPrint);
			break;
		//exit
		case 9:
			cout << "Thank you for using the course planner!";
			return 0;
		//invalid entry
		default:
			cout << userChoice << " is not a valid selection. Please try again." << endl;
			break;
		}
	}
}