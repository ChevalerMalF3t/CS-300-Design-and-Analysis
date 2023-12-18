// ABC University Project 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//============================================================================
// Name        : ABC University Project 2.cpp
// Author      : Charles Shadley
// Version     : 1.0
// Description : Module 7-1: Project Two
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    Course(string num, string title, vector<string> prereqs)
        : courseNumber(move(num)), courseTitle(move(title)), prerequisites(move(prereqs)) {}
};

void loadDataStructure(vector<Course>& courses, const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string courseNumber, courseTitle, prereq;
        vector<string> prerequisites;

        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        while (getline(ss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        courses.emplace_back(courseNumber, courseTitle, prerequisites);
    }

    file.close();
}

void printCourseList(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses;
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    cout << "Here is a sample schedule:" << endl;
    cout << endl;
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

void printCourseInformation(const vector<Course>& courses, const string& courseNumber) {
    auto it = find_if(courses.begin(), courses.end(), [&courseNumber](const Course& c) {
        return c.courseNumber == courseNumber;
        });

    if (it != courses.end()) {
        cout << it->courseNumber << ", " << it->courseTitle << endl;
        if (!it->prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const auto& prereq : it->prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
    }
    else {
        cerr << "Course not found: " << courseNumber << endl;
    }
}

int main() {
    vector<Course> courses;

    while (true) {
        cout << "Welcome to the course planner." << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;

        int choice;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string fileName;
            cout << "Enter file name: ";
            cin >> fileName;
            loadDataStructure(courses, fileName);
            break;
        }
        case 2:
            printCourseList(courses);
            break;
        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            printCourseInformation(courses, courseNumber);
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        default:
            cerr << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}


