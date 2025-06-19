#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// Abstract Base Class
class Person {
protected:
    string name;
    int id;
public:
    Person() {}
    Person(string n, int i) : name(n), id(i) {}
    virtual void showDetails() = 0;
    string getName() const { return name; }
    int getID() const { return id; }
};

class Student : public Person {
    int totalDays, presentDays;
public:
    Student() {}
    Student(string n, int i) : Person(n, i), totalDays(0), presentDays(0) {}

    void markAttendance(bool present) {
        totalDays++;
        if (present) presentDays++;
    }

    void showDetails() {
        cout << "Student Name: " << name << ", ID: " << id << endl;
    }

    string getAttendanceData() const {
        stringstream ss;
        ss << name << "," << id << "," << totalDays << "," << presentDays;
        return ss.str();
    }

    void loadAttendanceData(int t, int p) {
        totalDays = t;
        presentDays = p;
    }

    void viewAttendance() const {
        cout << left << setw(15) << name << setw(10) << id
             << setw(15) << totalDays << setw(15) << presentDays << endl;
    }

    string getData() const {
        stringstream ss;
        ss << name << "," << id;
        return ss.str();
    }
};

class Teacher : public Person {
    string subject;
public:
    Teacher() {}
    Teacher(string n, int i, string s) : Person(n, i), subject(s) {}

    void showDetails() {
        cout << "Teacher Name: " << name << ", ID: " << id << ", Subject: " << subject << endl;
    }

    string getSubject() { return subject; }

    string getData() const {
        stringstream ss;
        ss << name << "," << id << "," << subject;
        return ss.str();
    }
};
class Staff : public Person {
    string role;
public:
    Staff() {}
    Staff(string n, int i, string r) : Person(n, i), role(r) {}

    void showDetails() {
        cout << "Staff Name: " << name << ", ID: " << id << ", Role: " << role << endl;
    }

    string getData() const {
        stringstream ss;
        ss << name << "," << id << "," << role;
        return ss.str();
    }

    string getRole() const { return role; }
};


// New Class for Biometric Attendance for Teachers
class TeacherBiometricAttendance {
public:
    static void markAttendance(const vector<Teacher>& teachers) {
        ofstream out("teacher_biometric_attendance.txt", ios::app);
        int tid;
cout << "Enter your Teacher ID: ";
cin >> tid;

bool found = false;
for (int i=0;i<teachers.size();++i) {
    if (teachers[i].getID() == tid) {
        char input;
        cout << "Did " << teachers[i].getName() << " scan fingerprint? (y/n): ";
        cin >> input;
        out << teachers[i].getName() << "," << teachers[i].getID() << "," << (input == 'y' || input == 'Y' ? "Present" : "Absent") << endl;
        found = true;
        break;
    }
}
if (!found) {
    cout << "? Teacher ID not found!\n";
}

        out.close();
        cout << "? Teacher biometric attendance marked.\n";
    }

    static void viewAttendance() {
        ifstream in("teacher_biometric_attendance.txt");
        string line;
        cout << "\n?? Teacher Biometric Attendance Record:\n";
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
    }
};
class StaffAttendance {
public:
    static void markAttendance(const vector<Staff>& staffList) {
        int inputID;
        cout << "Enter your Staff ID to mark attendance: ";
        cin >> inputID;

        bool found = false;
        for (int i=0;i<staffList.size();++i) {
            if (staffList[i].getID() == inputID) {
                char input;
                cout << "Is " << staffList[i].getName() << " present? (y/n): ";
                cin >> input;

                ofstream out("staff_attendance.txt", ios::app);
                out << staffList[i].getName() << "," << staffList[i].getID() << "," 
                    << (input == 'y' || input == 'Y' ? "Present" : "Absent") << endl;
                out.close();

                cout << "? Attendance marked for " << staffList[i].getName() << ".\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "? Staff with ID " << inputID << " not found.\n";
        }
    }

    static void viewAttendance() {
        ifstream in("staff_attendance.txt");
        string line;
        cout << "\n?? Staff Attendance Record:\n";
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
    }
};



class Admin {
    string password = "admin123";
public:
    bool login() {
        string input;
        cout << "Enter admin password: ";
        cin >> input;
        return input == password;
    }
};

class Faculty {
    string facultyName;
    vector<Teacher> facultyTeachers;
public:
    Faculty() {}
    Faculty(string name) : facultyName(name) {}

    void addTeacher(const Teacher& t) {
        facultyTeachers.push_back(t);
    }

    void showFaculty() {
        cout << "\n?? Faculty: " << facultyName << "\n";
        if (facultyTeachers.empty()) {
            cout << "? No teachers in this faculty.\n";
            return;
        }
        for (int i = 0; i < facultyTeachers.size(); i++) {
            facultyTeachers[i].showDetails();
        }
    }

    vector<Teacher>& getTeachers() {
        return facultyTeachers;
    }

    string getFacultyName() const { return facultyName; }
};

class Department {
    string deptName;
    vector<Student> deptStudents;
public:
    Department(string name) : deptName(name) {}

    void addStudent(const Student& s) {
        deptStudents.push_back(s);
    }

    void showDepartment() {
        cout << "\n?? Department: " << deptName << "\n";
        for (int i = 0; i < deptStudents.size(); i++) {
            deptStudents[i].showDetails();
        }
    }
};

class Course {
    string code;
    string title;
    Teacher assignedTeacher;
public:
    Course() {}
    Course(string c, string t, Teacher teacher) : code(c), title(t), assignedTeacher(teacher) {}

    void showCourse() {
        cout << "?? Course: " << code << " - " << title << "\n";
        cout << "Assigned Teacher: ";
        assignedTeacher.showDetails();
    }
};

class Timetable {
    string day;
    string timeSlot;
    Course course;
public:
    Timetable(string d, string t, Course c) : day(d), timeSlot(t), course(c) {}

    void showSchedule() {
        cout << day << " [" << timeSlot << "] - ";
        course.showCourse();
    }
};

class Announcement {
    string message;
public:
    Announcement(string msg) : message(msg) {}

    void show() {
        cout << "?? Announcement: " << message << endl;
    }

    string getMessage() const {
        return message;
    }
};

class AnnouncementBoard {
    vector<Announcement> announcements;
public:
    void post(const string& msg) {
        announcements.push_back(Announcement(msg));
        ofstream out("announcements.txt", ios::app);
        out << msg << endl;
        out.close();
    }

    void display() {
        cout << "\n?? Announcements:\n";
        ifstream in("announcements.txt");
        string line;
        while (getline(in, line)) {
            cout << "?? Announcement: " << line << endl;
        }
        in.close();
    }
};

class FileManager {
public:
    static void saveAttendance(const vector<Student>& students) {
        ofstream out("attendance.txt");
        for (int i = 0; i < students.size(); i++) {
            out << students[i].getAttendanceData() << endl;
        }
        out.close();
    }

    static void loadAttendance(vector<Student>& students) {
        ifstream in("attendance.txt");
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            string name;
            int id, total, present;
            getline(ss, name, ',');
            ss >> id; ss.ignore(); ss >> total; ss.ignore(); ss >> present;
            Student s(name, id);
            s.loadAttendanceData(total, present);
            students.push_back(s);
        }
        in.close();
    }
    static void loadStudents(vector<Student>& students) {
    ifstream in("students.txt");
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string name;
        int id;
        getline(ss, name, ',');
        ss >> id;
        students.push_back(Student(name, id));
    }
    in.close();
}

static void loadTeachers(vector<Teacher>& teachers) {
    ifstream in("teachers.txt");
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string name, subject;
        int id;
        getline(ss, name, ',');
        ss >> id; ss.ignore();
        getline(ss, subject);
        teachers.push_back(Teacher(name, id, subject));
    }
    in.close();
}

static void loadStaff(vector<Staff>& staffList) {
    ifstream in("staff.txt");
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string name, position;
        int id;
        getline(ss, name, ',');
        ss >> id; ss.ignore();
        getline(ss, position);
        staffList.push_back(Staff(name, id, position));
    }
    in.close();
}


    };


/* int main() {
    
    vector<Staff> staffList;
    FileManager::loadStaff(staffList);
    vector<Teacher> teachers;
    FileManager::loadTeachers(teachers);

    Faculty sci("Science Faculty");
    for (const auto& t : teachers) {
    sci.addTeacher(t);
    }

    vector<Student> students;
    FileManager::loadStudents(students);


    Admin admin;
    if (!admin.login()) {
        cout << "? Wrong password. Exiting...\n";
        return 0;
    }

    int choice;
    AnnouncementBoard board;
    do {
        cout << "\n===== MAIN MENU =====\n";
         cout << "1. Mark Teacher Biometric Attendance\n";
        cout << "2. View Teacher Biometric Attendance\n";
        cout << "3. View Staff Attendance\n";
        cout << "4. Mark Staff Attendance\n";
        cout << "5. View Announcements\n";
        cout << "6. Post New Announcement\n";
        cout << "7. Mark Student Attendance\n";
        cout << "8. View Student Attendance\n";
        cout << "9. Exit\n";

        cin >> choice;
        
        // ? Add this block RIGHT after reading the input:
        if (cin.fail()) {
         cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove invalid input
        cout << "? Invalid input. Please enter a number.\n";
        continue; // Skip to next loop iteration
        }

    switch (choice) {
    case 1: TeacherBiometricAttendance::markAttendance(sci.getTeachers()); break;
    case 2: TeacherBiometricAttendance::viewAttendance(); break;
    case 3: StaffAttendance::viewAttendance(); break;
    case 4: StaffAttendance::markAttendance(staffList); break;
    case 5: board.display(); break;
    case 6: {
        cin.ignore();
        string msg;
        cout << "Enter new announcement: ";
        getline(cin, msg);
        board.post(msg);
        cout << "? Announcement posted.\n";
        break;
    }
    case 7: {
        for (int i = 0; i < students.size(); ++i) {
            char input;
            cout << "Is " << students[i].getName() << " (ID: " << students[i].getID() << ") present? (y/n): ";
            cin >> input;
            students[i].markAttendance(input == 'y' || input == 'Y');
        }
        FileManager::saveAttendance(students);
        cout << "? Student attendance marked and saved.\n";
        break;
    }
    case 8: {
        cout << "\n?? Student Attendance Record:\n";
        cout << left << setw(15) << "Name" << setw(10) << "ID"
             << setw(15) << "Total Days" << setw(15) << "Present Days" << endl;
        for (const auto& s : students) {
            s.viewAttendance();  
        }
        break;
    }
    case 9: cout << "Exiting...\n"; break;
    default: cout << "? Invalid choice.\n";
}
         } while (choice != 9);
         return 0;

}  */

int main() {
    vector<Staff> staffList;
    FileManager::loadStaff(staffList);

    vector<Teacher> teachers;
    FileManager::loadTeachers(teachers);

    Faculty sci("Science Faculty");
    for (int i=0;i<teachers.size();++i) {
        sci.addTeacher(teachers[i]);
    }

    vector<Student> students;
    FileManager::loadStudents(students);

    Admin admin;
    if (!admin.login()) {
        cout << "? Wrong password. Exiting...\n";
        return 0;
    }

    int choice;
    AnnouncementBoard board;

    do {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Mark Teacher Biometric Attendance\n";
        cout << "2. View Teacher Biometric Attendance\n";
        cout << "3. View Staff Attendance\n";
        cout << "4. Mark Staff Attendance\n";
        cout << "5. View Announcements\n";
        cout << "6. Post New Announcement\n";
        cout << "7. Mark Student Attendance\n";
        cout << "8. View Student Attendance\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        
        cin >> choice;

        // ? Input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "? Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline left in buffer

        switch (choice) {
            case 1:
                TeacherBiometricAttendance::markAttendance(sci.getTeachers());
                break;
            case 2:
                TeacherBiometricAttendance::viewAttendance();
                break;
            case 3:
                StaffAttendance::viewAttendance();
                break;
            case 4:
                StaffAttendance::markAttendance(staffList);
                break;
            case 5:
                board.display();
                break;
            case 6: {
                string msg;
                cout << "Enter new announcement: ";
                getline(cin, msg);
                board.post(msg);
                cout << "? Announcement posted.\n";
                break;
            }
            case 7: {
                for (int i = 0; i < students.size(); ++i) {
                    char input;
                    cout << "Is " << students[i].getName() << " (ID: " << students[i].getID() << ") present? (y/n): ";
                    cin >> input;
                    students[i].markAttendance(input == 'y' || input == 'Y');
                }
                FileManager::saveAttendance(students);
                cout << "? Student attendance marked and saved.\n";
                break;
            }
            case 8: {
                cout << "\n?? Student Attendance Record:\n";
                cout << left << setw(15) << "Name" << setw(10) << "ID"
                     << setw(15) << "Total Days" << setw(15) << "Present Days" << endl;
                for (int i=0;i<students.size();++i) {
                    students[i].viewAttendance();
                }
                break;
            }
            case 9:
                cout << "? Exiting...\n";
                break;
            default:
                cout << "? Invalid choice.\n";
        }

    } while (choice != 9);

    return 0;
}
