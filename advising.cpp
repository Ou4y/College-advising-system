#include<iostream>
#include<string>
#include<fstream>
#include<assert.h>
#include<vector>
#include<filesystem>
using namespace std;
class Course
{
public:
	string name;
	string id;
	string prereq;
	string lectime;
	string Day;
	int creditHours;
	Course()
	{
		name = "";
		id = "";
		creditHours = 0;
		prereq = "";
		lectime = "";
		Day = "";
	}
};
class Student {
private:
	double gpa;
public:
	string fullName;
	string id;
	string minor;
	int year;
	int semester;
	int creditHours;
	int numCourses;
	static vector <Course>courses;//current
	static vector <string>finished;//finished
	Student()
	{
		fullName = "";
		this->id = "";
		this-> minor = "";
		this-> year = 0;
		this-> semester = 0;
		this->creditHours = 0;
		this->numCourses = 0;
		this->gpa = 0.0;
	}
	double getGPA()
	{
		return gpa;
	}
	void setGPA(double gpa)
	{
		this->gpa = gpa;
	}

	void printDetails()
	{
		cout << "Welcome " << fullName << endl;
		cout << "Your ID: " << id << endl;
		cout << "Number of courses: " << numCourses << endl;
		cout << "Semester: " << semester << endl;
		cout << "Credit Hours: " << creditHours << endl;
		cout << "Your GPA: " << gpa << endl;
	}
	//add functions 
	void add(string coursecode, vector<Course>stcourses, Course arr[], string id) {
		bool access = false;
		for (int i = 0; i < 35; i++) {
			if (arr[i].id == coursecode) {
				if (arr[i].prereq.empty()) {
					if (id == this->id) {
						Student::courses.push_back(arr[i]);
						Student::numCourses++;
					}
				}
				else
					cout << "you didnt take the prerequisit";
			}
		}
	}
	//drop a course function
	void drop(string coursecode, vector<Course>stcourses,string id)
	{
		bool access = false;
		if (id == this->id) {
			Student::courses.pop_back(coursecode);
		}

	}
	//view scheduale function (under develop)
	void viewscheduale()
	{

	}
	static void addpre(Student arr[], string filenum) {
		ifstream inputss(filenum + ".txt");
			if (inputss.is_open()) {
				string code;
				while (getline(inputss, code) && ! inputss.eof()) {
					for (int i = 1; i < 6; i++) {
						if (arr[i].id == filenum) {
							arr[i].finished.push_back(code);
						}
					}
				}
			}
	}
};
class Instructor
{
public:
	string name;
	int pin;
	int numCourses;
	Course courses[5];
	Instructor()
	{
		name = "";
		pin = 0;
		numCourses = 0;
	}
	//instructor adding lecture day and time and adding them to the file of the student who takes the same course
	static void LecTime(string code, string startLectime, string endtime, string day, Course arr[],Student array[]) {
		if (day == "Friday" || day == "friday") {
			cout << "It's off day please choose another day...";
			return;
		}
		//search for the course
		for (int i = 0; i < 35; i++) {
			if (arr[i].id == code) {
				arr[i].lectime = "from "+startLectime + " to " + endtime;
			}
			//searching for student who takes the course
			for (int i = 0; i < 6; i++) {
				for (const Course& course : array[i].courses) {
					if (course.id == code) {
						ifstream stfile(array->fullName + ".txt",ios::app);
						ofstream temp("temp.txt", ios::app);
						if (stfile.is_open()&& temp.is_open()) {
							string read;
							while (getline(stfile, read) && !stfile.eof()) {
								bool insertContent = false;
								while (getline(stfile, read)) {
									// Write the current line to the temporary file
									temp << read <<endl;

									// Check if the line matches the condition to insert the content
									if (read.find(code) != string::npos) {
										insertContent = true;
									}
									if (insertContent) {
										temp << code << endl;
										insertContent = false;
									}
								}
							}
							stfile.close();
							temp.close();
							remove(stfile.c_str());
							rename("temp.txt",stfile.c_str());
						}
						  else {
							cout << "Error: Unable to open files." << endl;
						
						  }

								
							
						
     				}
				}
			}
		}
	}
};
int main()
{
	// Initialize students
	static Student students[6];
	//adding prerequisits to 5 
	Student::addpre(students, "225316");
	Student::addpre(students, "214423");
	Student::addpre(students, "202969");
	Student::addpre(students, "191722");
	Student::addpre(students, "225316");
	fstream input;
	input.open("all students.txt");
	if (input.is_open()) {
		for (int i = 0; i < 6; i++) {
			getline(input >> ws, students[i].fullName);
			input >> students[i].id;
			input.ignore();
			input >> students[i].numCourses;
			input.ignore();
			input >> students[i].semester;
			input.ignore();
			input >> students[i].creditHours;
			input.ignore();
			double gpa;
			input >> gpa;
			students[i].setGPA(gpa);
			input.ignore(); // ignore the newline character after the GPA
		}
	}	input.close();
	//array to store the instructors
	Instructor allinstructors[10];
	fstream input1;
	input1.open("Instructors.txt");
	if (input1.is_open()) {
		for (int i = 0; i < 10; i++) {
			getline(input1 >> ws, allinstructors[i].name);
			input1 >> allinstructors[i].pin;
			input1 >> allinstructors[i].numCourses;
			input1.ignore();
		}
	}
	else
		cout << "file not found!";
	//array to store all the courses
	Course allcourses[35];
	fstream input2;
	input2.open("all courses.txt");
	if (input2.is_open()) {
		int i = 0;
		while (i < 35 && !input2.eof()) {
			getline(input2 >> ws, allcourses[i].name);
			getline(input2 >> ws, allcourses[i].id);
			if (allcourses->prereq.length < 6) {
				input2.ignore();
			}
			else {
				input2 >> allcourses->prereq;
			}
			input2 >> allcourses->prereq;
			input2 >> allcourses[i].creditHours;
			input2.ignore();
			i++;
		}
		input2.close();
	}
	else {
		cout << "file not found";
	}
	int num = 1;
	while (num > 0) {
		cout << "Welcome!" << endl;
		cout << "1 - Login" << endl;
		cout << "2 - exit" << endl;
		int choice1;
		cin >> choice1;
		if (choice1 == 1) {
			cout << "1 - Enter as an instructor" << endl;
			cout << "2 - Enter as a student" << endl;
			int choice2;
			cin >> choice2;
			if (choice2 == 1) {
				string username;
				int pin;
				cin.ignore();
				cout << "Please enter your username: ";
				getline(cin, username);
				cout << "Please enter your PIN: ";
				cin >> pin;
				static bool access = false;
				// Check if the PIN is correct
				for (int i = 0; i < 10; i++) {
					if (pin == allinstructors[i].pin) {
						access = true;
						// Perform instructor tasks
						cout << "1-add course time:" << endl << "2-exit";
						int num1;
						cin >> num1;
						if (num1 == 1)
						{
							string starttime;
							string endtime;
							string day;
							string code;
							cout << "enter the course code:" << endl;
							cin >> code;
							cin.ignore();
							cout << "enter the day of the course:" << endl;
							cin >> day;
							cin.ignore();
							cout << "Enter the lecture time:";
							cin >> starttime;
							cout << "to ";
							cin >> endtime;
							Instructor::LecTime(code, starttime, endtime, day, allcourses,students);
							//string code, int startLectime, int endtime, string day, Course arr[], Student
							num = -1;
						}
						else if (num1 == 2)
							num = -1;
					}
				}
			}
			else if (choice2 == 2) {
				cout << "Enter your ID: ";
				string id1;
				cin >> id1;
				// Search for the student by ID
				int i = 0;
				bool found = false;
				for (i; i < 6; i++) {
					if (students[i].id == id1)
					{
						students[i].printDetails();
						found = true;
						if (found == true)
							break;
					}
				}
				if (found == true)
				{
					cout << "1-view current scheduale" << endl << "2-add a course" << endl << "3-drop a course" << endl;
					cout << "4-exit" << endl;
					int choice;
					cin >> choice;
					if (choice == 1) {
						students[i].viewscheduale();
						num = -1;
					}
					else if (choice == 2) {
						students[i].add();
					}
					else if (choice == 3) {
						string code;
						string id = id1;
						cout << "enter the code of the course you want to drop:";
						cin >> code;
						students[i].drop(code,Student::courses,);
					}
					else if (choice == 4)
						num = -1;
				}
				if (!found)
				{
					cout << "Student not found." << endl;
				}
			}
		}
		else if (choice1 == 2)
			num = -1;
	}
	cout << "Thank you";
}