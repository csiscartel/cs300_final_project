
// By Oumar Kenneh on 10/18/2025.
// cs300 final project

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Define the course type to hold the number, title, and prerequisites of a class.
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Node for BST
struct Node {
    Course course;
    Node* left;
    Node* right;
    Node(Course aCourse) : course(aCourse), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class CourseBST {
private:
    Node* root;

    void addNode(Node* node, Course course) {
        if (course.courseNumber < node->course.courseNumber) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            } else {
                addNode(node->left, course);
            }
        } else if (course.courseNumber > node->course.courseNumber) {
            if (node->right == nullptr) {
                node->right = new Node(course);
            } else {
                addNode(node->right, course);
            }
        }
    }

    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
        inOrder(node->right);
    }

    void printCourseInfo(Node* node, string courseNumber) {
        if (node == nullptr) return;
        if (courseNumber == node->course.courseNumber) {
            cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
            if (node->course.prerequisites.empty()) {
                cout << "Prerequisites: None" << endl;
            } else {
                cout << "Prerequisites: ";
                for (int i = 0; i < node->course.prerequisites.size(); ++i) {
                    cout << node->course.prerequisites[i];
                    if (i < node->course.prerequisites.size() - 1) cout << ", ";
                }
                cout << endl;
            }
            return;
        } else if (courseNumber < node->course.courseNumber) {
            printCourseInfo(node->left, courseNumber);
        } else {
            printCourseInfo(node->right, courseNumber);
        }
    }

public:
    CourseBST() : root(nullptr) {}

    void Insert(Course course) {
        if (root == nullptr) {
            root = new Node(course);
        } else {
            addNode(root, course);
        }
    }

    void InOrder() {
        inOrder(root);
    }

    void PrintCourseInfo(string courseNumber) {
        printCourseInfo(root, courseNumber);
    }
};

// Function for uploading courses from the CSV file
void loadCourses(string fileName, CourseBST* bst) {
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cout << "Error: File could not be opened." << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Warning: Skipped a corrupted line." << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }
        bst->Insert(course);
    }
    cout << "Courses successfully loaded!" << endl;
    file.close();
}

// Menu printing
void printMenu() {
    cout << "\nOptions:" << endl;
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course Information" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    CourseBST* bst = new CourseBST();
    string fileName;
    int choice = 0;
    bool dataLoaded = false;

    cout << "Welcome to the ABCU Advising Assistance Program." << endl;

    while (choice != 9) {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name you want to load: ";
            cin >> fileName;
            loadCourses(fileName, bst);
            dataLoaded = true;
            break;
        case 2:
            if (dataLoaded) {
                cout << "\nA sample schedule is:\n" << endl;
                bst->InOrder();
            } else {
                cout << "Please first load the file." << endl;
            }
            break;
        case 3:
            if (dataLoaded) {
                string courseNum;
                cout << "Enter course number, example, CS300: ";
                cin >> courseNum;
                cout << endl;
                bst->PrintCourseInfo(courseNum);
            } else {
                cout << "File is not loaded yet." << endl;
            }
            break;
        case 9:
            cout << "Thank you for using the Advising Help Program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}

