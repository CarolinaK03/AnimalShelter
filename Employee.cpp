#include "Employee.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

/*****************************************************************/
// Employee Methods
Employee::Employee(const char* employee_name1, int id, const char* position1, const char* password1) {
    this->id = id;
    this->employee_name = new char[strlen(employee_name1) + 1];
    strcpy(this->employee_name, employee_name1);
    strcpy(this->position, position1);
    this->password = new char[strlen(password1) + 1];
    strcpy(this->password, password1);
    this->next = nullptr;
}
Employee::~Employee() {
    delete[] employee_name;
    delete[] password;
}
void Employee::setName(const char* newName) {
    delete[] this->employee_name;

    this->employee_name = new char[strlen(newName) + 1];
    strcpy(this->employee_name, newName);
}
void Employee::setPassword(const char* newPassword) {
    delete[] this->password;
    this->password = new char[strlen(newPassword) + 1];
    strcpy(this->password, newPassword);
}

/*****************************************************************/
// EmployeeList Methods
EmployeeList::EmployeeList() : head(nullptr), employeeCount(0) {}
EmployeeList::~EmployeeList() {
    while (head) {
        Employee* temp = head;
        head = head->next;
        delete temp;
    }
}

void EmployeeList::addEmployee(Employee* currentEmp) {
    bool permission = false;
    if (currentEmp->getID() / 10 >= 1099) { //checking for manager
        cout << '\n' << endl;
        cout<< "********************************" << endl ;
        cout << "Only managers may add Employees." << endl;
        cout<< "********************************" << endl ;
        return;
    }

    char name[50], position[10], password[50];
    cout << '\n' << endl;
    cout<< "********************************" << endl ;
    cout << "Enter Employee Name: ";
    cin >> name;
    cout << "Enter Position (Must be Manager, Vet, or Volunteer): ";
    cin >> position;
    cout << "Enter Password: ";
    cin >> password;
    cout<< "................................" << endl ;

    int idPrefix;
    if (strcmp(position, "Manager") == 0) idPrefix = 10;
    else if (strcmp(position, "Vet") == 0) idPrefix = 20;
    else if (strcmp(position, "Volunteer") == 0) idPrefix = 30;
    else idPrefix = 40;
    //id gen fixes for authorization

    int id = idPrefix * 1000 + ++employeeCount; 

    Employee* newEmployee = new Employee(name, id, position, password);
    newEmployee->next = head;
    head = newEmployee;

    cout << "Employee added successfully; ID: " << id << endl;
    cout<< "********************************" << endl ;
}

void EmployeeList::removeEmployee(Employee* currentEmp) {
    if (currentEmp->getID() / 10 >= 1099) { 
        cout << "You do not have permission to remove an employee. Contact a manager to perform this action." << endl;
        return;
    }
    cout << '\n' << endl;
    printList();
    int idRemove;
    char password[50];
    cout << "Enter the ID of the employee to remove: ";
    cin >> idRemove;
    cout << "Enter your password to confirm: ";
    cin >> password;

    if (strcmp(currentEmp->getPassword(), password) != 0) {
        cout << "Incorrect password. Removal operation aborted." << endl;
        return;
    }
    Employee* current = head;
    Employee* prev = nullptr;

    while (current && current->getID() != idRemove) {
        prev = current;
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Employee with ID " << idRemove << " was not found." << endl;
        return;
    }

    if (prev == nullptr) {
        head = current->next;
    } else {
        prev->next = current->next;
    }
    delete current;
    cout << "Employee removed successfully..." << endl;
}

void EmployeeList::editProfile(Employee* currentEmp) {
    int idEdit = currentEmp->getID();
    char newName[50], newPassword[50];
    if (currentEmp->getID() / 10 <= 1099) {
        printList();
        cout << '\n' << endl;
        cout << "Enter ID of the employee you'd like to edit: ";
        cin >> idEdit;
    }

    Employee* current = head;
    while (current && current->getID() != idEdit) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << '\n' << endl;
        cout<< "********************************" << endl ;
        cout << "Employee with ID " << idEdit << " does not exist :(" << endl;
        cout<< "********************************" << endl ;
        return;
    }
    cout << '\n' << endl;
    cout<< "********************************" << endl ;
    cout<< "         In Edit Mode           " << endl ;
    cout<< "................................" << endl ;
    cout << "Enter new name (leave empty to keep current): ";
    cin.ignore();
    cin.getline(newName, 50);
    if (strlen(newName) > 0) {
        current->setName(newName);
    }

    cout<< "................................" << endl ;
    cout << "Enter new password (leave empty to keep current): ";
    cin.getline(newPassword, 50);
    if (strlen(newPassword) > 0) {
        current->setPassword(newPassword);
    }
    cout<< "................................" << endl ;
    cout << "Employee information updated successfully!" << endl;
    cout<< "********************************" << endl ;
}

Employee* EmployeeList::authenticate(int id, const char* password) {
    Employee* current = head;
    while (current) {
        if (current->getID() == id &&strcmp(current->getPassword(), password) == 0) {
            return current;
        }
        current = current->next;

    }
    return nullptr;
}

void EmployeeList::printList() {
    Employee* current = head;
    cout << '\n';
    cout << "********************************" << endl;
    cout << "Employee List " << endl;
    cout << '\n';
    while (current) {
        cout << "ID: " << current->getID() <<endl;
        cout<< "Name: " << current->getName() << endl;
        cout<< "Position: " << current->getPosition() << endl;
        std::cout << '\n';
        current = current->next;
    }
    cout << "********************************" << endl;
}
   
void EmployeeList::saveToFile(const string& filename) {
    ofstream outFile(filename, ios::binary);

    if (!outFile) {
        cerr << "Error occured when trying to save data ;/" << endl;
        return;
    }

    Employee* current = head;
    while (current) {
        size_t name_len = strlen(current->employee_name);
        size_t password_len = strlen(current->password);
        
        outFile.write((char*)&name_len, sizeof(name_len));
        outFile.write(current->employee_name, name_len);
        outFile.write((char*)&current->id, sizeof(current->id));
        outFile.write(current->position, sizeof(current->position));
        outFile.write((char*)&password_len, sizeof(password_len));
        outFile.write(current->password, password_len);

        current = current->next;
    }

    outFile.close();
}

void EmployeeList::loadFromFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "No file to load..." << endl;
        return;
    }

    Employee* current = nullptr;
    while (!inFile.eof()) {
        size_t name_len, password_len;
        inFile.read((char*)&name_len, sizeof(name_len));
        if (inFile.eof()) break;

        char* name = new char[name_len + 1];
        inFile.read(name, name_len);
        name[name_len] = '\0';

        int id;
        inFile.read((char*)&id, sizeof(id));
        char position[10];
        inFile.read(position, sizeof(position));

        inFile.read((char*)&password_len, sizeof(password_len));
        char* password = new char[password_len + 1];
        inFile.read(password, password_len);
        password[password_len] = '\0';

        Employee* newEmployee = new Employee(name, id, position, password);
        newEmployee->next = nullptr;

        if (current) {
            current->setNext() = newEmployee;
        } else {
            head = newEmployee;
        }
        current = newEmployee;

        delete[] name;
        delete[] password;
    }

    inFile.close();
}
/*****************************************************************/