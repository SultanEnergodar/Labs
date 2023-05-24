#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>

using namespace std;

class Employee {
public:
    Employee(string name, int birth_year, string position, string unit)
        : name_(name), birth_year_(birth_year), position_(position), unit_(unit) {}

    string GetName() const { return name_; }
    int GetBirthYear() const { return birth_year_; }
    string GetPosition() const { return position_; }
    string GetUnit() const { return unit_; }

private:
    string name_;
    int birth_year_;
    string position_;
    string unit_;
};

class EmployeesDatabase {
public:
    void LoadDataFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        string line = "";
        while (getline(file, line)) {
            string name, position, unit;
            int point=0;
            int birth_year;
            while (!(line[point] >= '0' && line[point] <= '9')) {
                name += line[point];
                point++; 
            }
            while (line[point] != ',') {
                unit += line[point];
                point++;
            }
            point+=2;
            birth_year = stoi(unit);
            while (line[point] != ',') {
                position += line[point];
                point++;
            }
            point+=2;
            unit = "";
            while (point != line.size()) {
                unit += line[point];
                point++;
            }
            employees_.push_back(Employee(name, birth_year, position, unit));
        }
        file.close();
    }

    void PrintAllEngineers() const {
        cout << "Инженеры:" << endl;
        for (const auto& employee : employees_) {
            if (employee.GetPosition() == "инженер") {
                cout << "ok";
                cout << employee.GetName() << ", " << employee.GetBirthYear()
                    << ", " << employee.GetPosition() << ", " << employee.GetUnit() << endl;
            }
        }
        cout << endl;
    }

    void PrintNonPresidents() const {
        cout << "Не председатели:" << endl;
        vector<Employee> non_presidents;
        copy_if(employees_.begin(), employees_.end(), back_inserter(non_presidents),
            [](const Employee& employee) { return employee.GetPosition() != "председатель"; });
        sort(non_presidents.begin(), non_presidents.end(), [](const Employee& a, const Employee& b) {
            return a.GetBirthYear() < b.GetBirthYear();
            });

        for (const auto& employee : non_presidents) {
            cout << employee.GetName() << ", " << employee.GetBirthYear()
                << ", " << employee.GetPosition() << ", " << employee.GetUnit() << endl;
        }
        cout << endl;
    }
    string print(int a) {
        cout << employees_[a].GetPosition();
        return employees_[a].GetPosition();
    }

private:
    vector<Employee> employees_;
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    EmployeesDatabase db;
    db.LoadDataFromFile("employees.txt");
    db.PrintAllEngineers();
    db.PrintNonPresidents();
    return 0;
}