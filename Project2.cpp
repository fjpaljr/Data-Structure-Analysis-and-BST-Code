/**
 * ProjectTwo.cpp
 * Francisco Palacios
 * CS 300 - Project Two
 * ABCU Course Advising System
 *
 * Uses a Binary Search Tree (BST) to store and retrieve
 * course data for the Computer Science department advising program.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ============================================================
// Data Structures
// ============================================================

// Holds information for a single course
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// BST node containing a course and left/right child pointers
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course aCourse) : course(aCourse), left(nullptr), right(nullptr) {}
};

// ============================================================
// BinarySearchTree Class
// ============================================================

class BinarySearchTree {
private:
    // Helper for recursive in-order traversal
    void InOrder(Node* node);

public:
    Node* root;

    BinarySearchTree();

    void Insert(Course course);
    Course Search(string courseNumber);
    void InOrderPublic();
};

// Constructor: initialize root to null
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

// Insert a course into the BST ordered by courseNumber
void BinarySearchTree::Insert(Course course) {
    Node* newNode = new Node(course);

    if (root == nullptr) {
        root = newNode;
    }
    else {
        Node* current = root;

        while (true) {
            if (course.courseNumber < current->course.courseNumber) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                }
                else {
                    current = current->left;
                }
            }
            else {
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                }
                else {
                    current = current->right;
                }
            }
        }
    }
}

// Search the BST for a course by courseNumber
// Returns the matching Course, or an empty Course if not found
Course BinarySearchTree::Search(string courseNumber) {
    Node* current = root;

    while (current != nullptr) {
        if (courseNumber == current->course.courseNumber) {
            return current->course;
        }
        else if (courseNumber < current->course.courseNumber) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return Course();
}

// Public wrapper to start in-order traversal from root
void BinarySearchTree::InOrderPublic() {
    InOrder(root);
}

// Recursive in-order traversal
void BinarySearchTree::InOrder(Node* node) {
    if (node != nullptr) {
        InOrder(node->left);

        cout << node->course.courseNumber << ", " << node->course.name << endl;

        InOrder(node->right);
    }
}

// ============================================================
// Functions
// ============================================================

// Load course data from the file into the BST
void LoadCourses(string filename, BinarySearchTree& bst) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: file not found" << endl;
        return;
    }

    vector<string> allCourseNumbers;
    vector<string> rawLines;
    string line;

    // First pass: read all lines and collect course numbers
    while (getline(file, line)) {
        if (line.empty()) continue;

        rawLines.push_back(line);

        stringstream ss(line);
        string courseNumber;
        getline(ss, courseNumber, ',');
        allCourseNumbers.push_back(courseNumber);
    }

    file.close();

    // Second pass: validate and build course objects
    for (size_t i = 0; i < rawLines.size(); ++i) {
        stringstream ss(rawLines[i]);
        vector<string> tokens;
        string token;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Validate minimum parameters
        if (tokens.size() < 2) {
            cout << "Error: line does not have enough parameters" << endl;
            continue;
        }

        // Create course object
        Course course;
        course.courseNumber = tokens[0];
        course.name = tokens[1];

        // Process prerequisites if they exist
        if (tokens.size() > 2) {
            bool skip = false;

            for (size_t j = 2; j < tokens.size(); ++j) {
                // Skip empty tokens caused by trailing commas
                if (tokens[j].empty()) continue;

                bool found = false;

                for (size_t k = 0; k < allCourseNumbers.size(); ++k) {
                    if (allCourseNumbers[k] == tokens[j]) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Error: prerequisite " << tokens[j] << " does not exist" << endl;
                    skip = true;
                    break;
                }

                course.prerequisites.push_back(tokens[j]);
            }

            if (skip) continue;
        }

        bst.Insert(course);
    }
}

// Search for a course and print its title and prerequisites
void SearchAndPrintCourse(BinarySearchTree& bst, string courseNumber) {
    // Convert to uppercase so input is case-insensitive
    for (size_t i = 0; i < courseNumber.size(); ++i) {
        courseNumber[i] = toupper(courseNumber[i]);
    }
    
    Course course = bst.Search(courseNumber);

    if (course.courseNumber.empty()) {
        cout << "Error: course not found" << endl;
        return;
    }

    cout << course.courseNumber << ", " << course.name << endl;

    if (course.prerequisites.empty()) {
        cout << "No prerequisites" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Print all courses using in-order traversal
void PrintAllCourses(BinarySearchTree& bst) {
    bst.InOrderPublic();
}

// ============================================================
// Main
// ============================================================

int main() {
    BinarySearchTree bst;
    string filename = "CS 300 ABCU_Advising_Program_Input.csv";
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << choice << " is not a valid option." << endl;
            continue;
        }

        if (choice == 1) {
            LoadCourses(filename, bst);
        }
        else if (choice == 2) {
            cout << "Here is a sample schedule:" << endl;
            cout << endl;
            PrintAllCourses(bst);
        }
        else if (choice == 3) {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            SearchAndPrintCourse(bst, courseNumber);
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}