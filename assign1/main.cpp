#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// File paths for output
const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

/**
 * Represents a course a student can take in ExploreCourses.
 * We assume all three fields are strings so that the course can be
 * constructed from three string literals.
 */
struct Course {
    std::string title;
    std::string number_of_units;
    std::string quarter;
};

/**
 * Include utils.cpp after Course is defined so that all functions and
 * operator overloads have the complete definition of Course.
 */
#include "utils.cpp"

/**
 * Reads the CSV file (ignoring the first header line) and populates
 * the vector `courses` with Course structs.
 */
void parse_csv(const std::string& filename, std::vector<Course>& courses) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string line;
    bool header = true;
    while (std::getline(file, line)) {
        if (header) { 
            header = false; 
            continue; 
        }
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < 3)
            continue; // Skip lines that don't have enough fields.
        Course course{ tokens[0], tokens[1], tokens[2] };
        courses.push_back(course);
    }
    file.close();
}

/**
 * Writes the courses that are offered (based on a criterion) to the file
 * "student_output/courses_offered.csv", and then removes these courses from
 * the all_courses vector.
 *
 * Here we assume that a course is offered if its quarter is "2023-2024 Winter".
 */
void write_courses_offered(std::vector<Course>& all_courses) {
    std::ofstream ofs(COURSES_OFFERED_PATH);
    if (!ofs) {
        std::cerr << "Error opening file for courses offered: " << COURSES_OFFERED_PATH << std::endl;
        return;
    }
    // Write CSV header.
    ofs << "title,number_of_units,quarter" << std::endl;

    // Keep track of offered courses.
    std::vector<Course> offeredCourses;
    for (const auto& course : all_courses) {
        if (course.quarter == "2023-2024 Winter") {  // Offered criterion.
            ofs << course.title << "," << course.number_of_units << "," << course.quarter << std::endl;
            offeredCourses.push_back(course);
        }
    }
    ofs.close();

    // Remove each offered course from all_courses using the provided utility.
    for (const auto& course : offeredCourses) {
        delete_elem_from_vector(all_courses, course);
    }
}

/**
 * Writes the remaining (non-offered) courses to the file
 * "student_output/courses_not_offered.csv". This function is called after
 * write_courses_offered, so all_courses now only contains unlisted courses.
 */
void write_courses_not_offered(std::vector<Course>& unlisted_courses) {
    std::ofstream ofs(COURSES_NOT_OFFERED_PATH);
    if (!ofs) {
        std::cerr << "Error opening file for courses not offered: " << COURSES_NOT_OFFERED_PATH << std::endl;
        return;
    }
    // Write CSV header.
    ofs << "title,number_of_units,quarter" << std::endl;
    for (const auto& course : unlisted_courses) {
        ofs << course.title << "," << course.number_of_units << "," << course.quarter << std::endl;
    }
    ofs.close();
}

int main() {
    // Static assertion to ensure our Course struct meets the requirements.
    static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

    std::vector<Course> courses;
    parse_csv("courses.csv", courses);

    // Uncomment for debugging purposes:
    // print_courses(courses);

    write_courses_offered(courses);
    write_courses_not_offered(courses);

    // Run the autograder (provided in utils.cpp).
    return run_autograder();
}
