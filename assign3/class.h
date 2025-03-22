#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
private:
    
    std::string name;
    int id;
    std::vector<double> grades;
    double gpa;
    
    
    void calculateGPA();

public:
    
    Student();
    
    
    Student(std::string studentName, int studentId);
    
    
    std::string getName() const;
    int getId() const;
    double getGPA() const;
    
    
    void setName(std::string newName);
    void setId(int newId);
    void addGrade(double grade);
};

#endif