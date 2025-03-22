/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

 #include "class.h"
 #include <iostream>
 
 void sandbox() {
   Student student1("Carlos Rodriguez", 12345);
   
   student1.addGrade(95.5);
   student1.addGrade(87.0);
   student1.addGrade(92.3);
   
   std::cout << "Student Name: " << student1.getName() << std::endl;
   std::cout << "Student ID: " << student1.getId() << std::endl;
   std::cout << "Current GPA: " << student1.getGPA() << std::endl;
   
   Student student2;
   
   student2.setName("Maria Sanchez");
   student2.setId(54321);
   student2.addGrade(88.5);
   
   std::cout << "\nSecond Student Name: " << student2.getName() << std::endl;
   std::cout << "Second Student ID: " << student2.getId() << std::endl;
   std::cout << "Second Student GPA: " << student2.getGPA() << std::endl;
 }