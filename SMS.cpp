#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

struct Student
{
    int id;
    char name[50];
    int age;
    char course[50];
};

void addStudent()
{
    Student s;

    ofstream file("students.dat", ios::binary | ios::app);

    cout << "\nEnter Student ID : ";
    cin >> s.id;
    cin.ignore();

    cout << "Enter Name       : ";
    cin.getline(s.name, 50);

    cout << "Enter Age        : ";
    cin >> s.age;
    cin.ignore();

    cout << "Enter Course     : ";
    cin.getline(s.course, 50);

    file.write((char*)&s, sizeof(Student));

    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents()
{
    Student s;

    ifstream file("students.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo student records found!\n";
        return;
    }

    cout << "\n========== STUDENT RECORDS ==========\n";

    bool found = false;

    while (file.read((char*)&s, sizeof(Student)))
    {
        // Skip invalid records
        if (s.id <= 0)
        {
            continue;
        }

        cout << "\nStudent ID : " << s.id << endl;
        cout << "Name       : " << s.name << endl;
        cout << "Age        : " << s.age << endl;
        cout << "Course     : " << s.course << endl;
        cout << "--------------------------------------";

        found = true;
    }

    if (!found)
    {
        cout << "\nNo valid records found!\n";
    }

    file.close();
}

void searchStudent()
{
    int searchId;
    bool found = false;

    Student s;

    cout << "\nEnter Student ID to Search : ";
    cin >> searchId;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(Student)))
    {
        if (s.id == searchId)
        {
            cout << "\nStudent Found!\n";

            cout << "Student ID : " << s.id << endl;
            cout << "Name       : " << s.name << endl;
            cout << "Age        : " << s.age << endl;
            cout << "Course     : " << s.course << endl;

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nStudent Record Not Found!\n";
    }
}

void updateStudent()
{
    int updateId;
    bool found = false;

    Student s;

    cout << "\nEnter Student ID to Update : ";
    cin >> updateId;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(Student)))
    {
        if (s.id == updateId)
        {
            cout << "\nEnter New Name   : ";
            cin.ignore();
            cin.getline(s.name, 50);

            cout << "Enter New Age    : ";
            cin >> s.age;
            cin.ignore();

            cout << "Enter New Course : ";
            cin.getline(s.course, 50);

            // Move pointer back
            file.seekp(file.tellg() - streampos(sizeof(Student)));

            file.write((char*)&s, sizeof(Student));

            cout << "\nStudent Record Updated Successfully!\n";

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nStudent Record Not Found!\n";
    }
}

void deleteStudent()
{
    int deleteId;
    bool found = false;

    Student s;

    ifstream file("students.dat", ios::binary);
    ofstream tempFile("temp.dat", ios::binary);

    cout << "\nEnter Student ID to Delete : ";
    cin >> deleteId;

    while (file.read((char*)&s, sizeof(Student)))
    {
        if (s.id != deleteId)
        {
            tempFile.write((char*)&s, sizeof(Student));
        }
        else
        {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
    {
        cout << "\nStudent Record Deleted Successfully!\n";
    }
    else
    {
        cout << "\nStudent Record Not Found!\n";
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n========== STUDENT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "===============================================\n";

        cout << "Enter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nProgram Closed Successfully!\n";
                break;

            default:
                cout << "\nInvalid Choice! Please Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}
