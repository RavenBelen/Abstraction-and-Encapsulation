#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// Base class Employee 
class Employee {
protected:
    int id;
    string name;
    double salary;

public:
    Employee(int id, string name, double salary) : id(id), name(name), salary(salary) {}
    virtual double calculateSalary() = 0; 
    virtual void display() = 0;
    virtual string getType() = 0;
    int getId() { return id; }
};

// Full-time Employee
class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee(int id, string name, double salary) : Employee(id, name, salary) {}
    double calculateSalary() override { return salary; }
    void display() override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Fixed Monthly Salary: $" << salary << "\n\n";
    }
    string getType() override { return "Full-time Employees"; }
};

// Part-time Employee
class PartTimeEmployee : public Employee {
    int hoursWorked;
public:
    PartTimeEmployee(int id, string name, double hourlyWage, int hoursWorked)
        : Employee(id, name, hourlyWage), hoursWorked(hoursWorked) {}
    double calculateSalary() override { return salary * hoursWorked; }
    void display() override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Hourly Wage: $" << salary << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << calculateSalary() << "\n\n";
    }
    string getType() override { return "Part-time Employees"; }
};

// Contractual Employee
class ContractEmployee : public Employee {
    int projectsCompleted;
public:
    ContractEmployee(int id, string name, double projectPay, int projectsCompleted)
        : Employee(id, name, projectPay), projectsCompleted(projectsCompleted) {}
    double calculateSalary() override { return salary * projectsCompleted; }
    void display() override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Contract Payment Per Project: $" << salary << "\n";
        cout << "Projects Completed: " << projectsCompleted << "\n";
        cout << "Total Salary: $" << calculateSalary() << "\n\n";
    }
    string getType() override { return "Contractual Employees"; }
};

vector<Employee*> employees;

// Function to check duplicate ID
bool isDuplicateID(int id) {
    for (auto emp : employees) {
        if (emp->getId() == id) return true;
    }
    return false;
}

// Function to safely get a valid input
int getValidIntInput(const string& prompt) {
    string input;
    
    while (true) {
        cout << prompt;
        cin >> ws; 
        getline(cin, input); //para mabasa ang entire line

        // para sa number at spacing if natanggap
        if (!input.empty() && input.find_first_not_of("0123456789") == string::npos) {
            return stoi(input); // Convert to integer and return
        }

        cout << "Invalid input. Please try again. \n";
    }
}


// Function to safely get valid double input
double getValidDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0) { 
            cout << "Invalid input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return value;
}

// Function to add employees
void addEmployee(int type) {
    int id;
    string name;
    double salary;
    
    do {
        id = getValidIntInput("Enter Employee ID: ");
        if (isDuplicateID(id)) {
            cout << "Duplicate ID! Try again.\n";
        }
    } while (isDuplicateID(id));

    cout << "Enter Name: ";
    getline(cin, name);
    
    if (type == 1) {
        salary = getValidDoubleInput("Enter Fixed Salary: $");
        employees.push_back(new FullTimeEmployee(id, name, salary));
    } else if (type == 2) {
        int hoursWorked;
        salary = getValidDoubleInput("Enter Hourly Wage: $");
        hoursWorked = getValidIntInput("Enter Hours Worked: ");
        employees.push_back(new PartTimeEmployee(id, name, salary, hoursWorked));
    } else if (type == 3) {
        int projects;
        salary = getValidDoubleInput("Enter Contract Payment Per Project: $");
        projects = getValidIntInput("Enter Number of Projects Completed: ");
        employees.push_back(new ContractEmployee(id, name, salary, projects));
    }
    cout << "Employee added successfully!\n\n";
}

// Function to display payroll report
void displayPayrollReport() {
    cout << "------ Employee Payroll Report ------\n";
    
    vector<string> types = {"Full-time Employees", "Part-time Employees", "Contractual Employees"};
    for (const string& type : types) {
        bool hasEmployees = false;
        for (auto emp : employees) {
            if (emp->getType() == type) {
                if (!hasEmployees) {
                    cout << "\n" << type << "\n";
                    cout << "-----------------------------\n";
                    hasEmployees = true;
                }
                emp->display();
            }
        }
    }
    cout << "\n";
}

int main() {
    int choice;
    do { //para sa looping
        cout << "Menu\n";
        cout << "1 - Full-time Employee\n";
        cout << "2 - Part-time Employee\n";
        cout << "3 - Contractual Employee\n";
        cout << "4 - Display Payroll Report\n";
        cout << "5 - Exit\n";
        choice = getValidIntInput("Enter choice: ");
        
        switch (choice) {
            case 1: case 2: case 3:
                addEmployee(choice);
                break;
            case 4:
                displayPayrollReport();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
