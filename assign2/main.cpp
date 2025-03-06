/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <ctime>

std::string kYourName = "Mateo Pilaquinga"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */

 std::string get_initials(const std::string& name) {
  std::string initials = "";
  bool newWord = true;
  
  for (char c : name) {
      if (c == ' ' || c == '\t') {
          newWord = true;
      } else if (newWord) {
          initials += c;
          newWord = false;
      }
  }
  
  return initials;
}

std::set<std::string> get_applicants(std::string filename) {
  std :: set <std :: string> applicants;
  std :: ifstream file(filename);

  if (!file.is_open()) {
    std :: cerr << "Error: Could not open file " << filename << std :: endl;
    return applicants;
  }

  std :: string line;

  while (std :: getline(file, line)) {
    if (!line.empty()){
      applicants.insert(line);
    }
  }

  file.close();
  return applicants;
} 

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std :: queue<const std :: string*> matches;
  std :: string target_initials = get_initials(name);

  for (const auto& student : students) {
    if (get_initials(student) == target_initials) {
      matches.push(&student);
    }
  }
  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  if (matches.empty()) {
    return "No matches found.";
  }

  // Initialize random seed
  std :: srand (static_cast<unsigned int>(std :: time(nullptr)));

  // Picks a random element from the queue
  int size = matches.size();
  int random_index = std :: rand() % size;

  // We create a temporary queue to handle our selection process
  std :: queue<const std :: string*> temp_queue;
  const std :: string* selected_match = nullptr;

  // Bucle through the queue to find the randomly selected match
  for (int i = 0; i < size; i++) {
    const std :: string* current = matches.front();
    matches.pop();

    if (i == random_index){
      selected_match = current;
    }
    temp_queue.push(current);
  }

  //Restore the original queue without the selected match
  while (!temp_queue.empty()) {
    const std :: string* current = temp_queue.front();
    temp_queue.pop();

    if (current != selected_match) {
      matches.push(current);
    }
  }
  return *selected_match;

}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
