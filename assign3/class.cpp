#include "class.h"
#include <numeric>


Student::Student() {
    name = "Unknown";
    id = 0;
    gpa = 0.0;
}


Student::Student(std::string studentName, int studentId) {
    name = studentName;
    id = studentId;
    gpa = 0.0;
}


void Student::calculateGPA() {
    if (grades.empty()) {
        gpa = 0.0;
        return;
    }
    
    double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
    gpa = sum / grades.size();
}


std::string Student::getName() const {
    return name;
}

int Student::getId() const {
    return id;
}

double Student::getGPA() const {
    return gpa;
}


void Student::setName(std::string newName) {
    name = newName;
}

void Student::setId(int newId) {
    id = newId;
}

void Student::addGrade(double grade) {
    grades.push_back(grade);
    calculateGPA();
}