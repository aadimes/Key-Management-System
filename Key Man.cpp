#include <iostream>
#include <fstream>
//#include <string>
using namespace std;

struct Employee {
    string name;
    int nKeysPossessed;
    string keys[5];


};
bool reader(string input_filename, Employee employees[], int& nEmployees);
void writer(string output_filename, Employee employees[], int nEmployees);
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey);
bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey);
void printAllEmploy(Employee employees[], int nEmployees);
void printEmployKeys(Employee employees[], int nEmployees, string emp_name);
void printEmployWKey(Employee employees[], int nEmployees, string key);

int main() {
    string filename;

    const int MAX_EMPLOYEES = 100;
    cout << "Please enter key file name to start: ";
    cin >> filename;
    Employee employees[MAX_EMPLOYEES];
    int nEmployees;
    if (!reader(filename, employees, nEmployees)) {
        cout << "File not found, exiting the program..." << endl;
        exit(1);
    }
    int choice;
    string empName;
    string key;
    string empA;
    string newKey;
    string empR;
    string returnKey;
    string outfile;
    do {
        cout << "Please select from the following options: " << endl;
        cout << "  1. show all employees and their keys" << endl;
        cout << "  2. show the keys an employee possesses" << endl;
        cout << "  3. show which employees possess a specific key" << endl;
        cout << "  4. add a key to an employee" << endl;
        cout << "  5. return a key by an employee" << endl;
        cout << "  6. save the current key status" << endl;
        cout << "  7. exit the program" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            printAllEmploy(employees, nEmployees);
            cout << endl;
            break;

        case 2:
            //string empName;
            cout << "Please enter employee's name: ";
            getline(cin, empName);
            printEmployKeys(employees, nEmployees, empName);
            cout << endl;
            break;
        case 3:
            //string key;
            cout << "Please enter a key: ";
            getline(cin, key);
            printEmployWKey(employees, nEmployees, key);
            cout << endl;
            break;
        case 4:
            //string empA;
            //string newKey;
            cout << "Please enter employee's name: ";
            getline(cin, empA);
            cout << "Please enter a new key: ";
            getline(cin, newKey);
            addKeyForEmployee(employees, nEmployees, empA, newKey);
            cout << endl;
            break;
        case 5:
            //string empR;
            //string returnKey;
            cout << "Please enter employee's name: ";
            getline(cin, empR);
            cout << "Please enter the returned key: ";
            getline(cin, returnKey);
            returnAKey(employees, nEmployees, empR, returnKey);
            cout << endl;
            break;
        case 6:
            //string outfile;
            cout << "Please enter output file name: ";
            getline(cin, outfile);
            writer(outfile, employees, nEmployees);
            cout << endl;
            break;
        case 7:
            cout << "Thank you for using the system! Goodbye!" << endl;
            writer("keys_updated.txt", employees, nEmployees);
            //cout << endl;
            break;
        default:
            cout << "Not a valid option. Please try again." << endl;
            cout << endl;
            break;
        }
        //cout << endl;
    } while (choice != 7);



    return 0;
}

bool reader(string input_filename, Employee employees[], int& nEmployees) {
    ifstream fin;
    fin.open(input_filename);
    if (!fin.is_open()) {
        return false;
    }
    //int nEmployees = 0;
    string line;
    fin >> nEmployees;
    fin.ignore();
    while (fin.good()) {
        //fin >> nEmployees;
        //fin.ignore();

        for (int i = 0; i < nEmployees; i++) {
            getline(fin, employees[i].name);

            fin >> employees[i].nKeysPossessed;
            fin.ignore();
            for (int j = 0; j < employees[i].nKeysPossessed; j++) {
                fin >> employees[i].keys[j];
            }
            fin.ignore();
        }

    }
    fin.close();
    return true;

}

void writer(string output_filename, Employee employees[], int nEmployees) {
    ofstream fout;
    fout.open(output_filename);
    fout << nEmployees << endl;
    for (int i = 0; i < nEmployees; i++) {
        fout << employees[i].name << endl;
        fout << employees[i].nKeysPossessed << " ";
        for (int j = 0; j < employees[i].nKeysPossessed; ++j) {
            fout << employees[i].keys[j];
            if (j != employees[i].nKeysPossessed - 1) {
                fout << " ";
            }
        }
        fout << endl;
    }
    fout.close();

}
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey) {
    bool w = false;
    int location = 0;
    for (int i = 0; i < nEmployees; i++) {
        if (employees[i].name == emp_name) {
            w = true;
            location = i;
        }
    }

    if (w == false) {
        cout << "Cannot find the specified employee!" << endl;
        return w;
    }

    else if (employees[location].nKeysPossessed == 5) {
        cout << "This employee already has 5 keys!" << endl;
        w = false;
        return w;

    }
    else if (employees[location].nKeysPossessed < 5) {
        for (int j = 0; j < employees[location].nKeysPossessed; j++) {
            if (employees[location].keys[j] == newKey) {
                cout << "This employee already has this key!" << endl;
                w = false;
                return w;
            }
        }
        employees[location].keys[employees[location].nKeysPossessed++] = newKey; // idk if inside or outside
        // adding one more
        cout << "Key added successfully." << endl;
        return w;
    }

    return w;

    /*
    for (int i = 0; i < nEmployees; ++i) {
         if (employees[i].name == emp_name) {
             if (employees[i].nKeysPossessed >= MAX_KEYS) {
                 cout << "This employee already has 5 keys!" << endl;
                 return false;
             }
             for (int j = 0; j < employees[i].nKeysPossessed; ++j) {
                 if (employees[i].keys[j] == newKey) {
                     cout << "This employee already has this key!" << endl;
                     return false;
                 }
             }
             employees[i].keys[employees[i].nKeysPossessed++] = newKey;
             cout << "Key added successfully." << endl;
             return true;
         }
     }
     cout << "Cannot find the specified employee!" << endl;
     return false;

    */


}

bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey) {
    for (int i = 0; i < nEmployees; i++) {
        if (employees[i].name == emp_name) {
            for (int j = 0; j < employees[i].nKeysPossessed; j++) {
                if (employees[i].keys[j] == returnKey) {
                    employees[i].keys[j] = employees[i].keys[--employees[i].nKeysPossessed];

                    cout << "Key returned successfully." << endl;
                    return true;
                }
            }
            cout << "This employee does not have the specified key!" << endl;
            return false;
        }
    }
    cout << "Cannot find the specified employee!" << endl;
    return false;
}

void printAllEmploy(Employee employees[], int nEmployees) {
    for (int i = 0; i < nEmployees; i++) {
        cout << "Name: " << employees[i].name << endl;
        cout << "Keys possessed: ";
        for (int j = 0; j < employees[i].nKeysPossessed; ++j) {
            cout << employees[i].keys[j] << " ";
        }
        cout << endl;
    }
}

void printEmployKeys(Employee employees[], int nEmployees, string emp_name) {
    for (int i = 0; i < nEmployees; i++) {
        if (employees[i].name == emp_name) {
            cout << employees[i].name << " possess the following keys: ";
            for (int j = 0; j < employees[i].nKeysPossessed; j++) {
                cout << employees[i].keys[j] << " ";
            }
            cout << endl;
            return;
        }
    }
    cout << "Cannot find the specified employee!" << endl;
}

void printEmployWKey(Employee employees[], int nEmployees, string key) {
    bool found = false;
    for (int i = 0; i < nEmployees; i++) {
        for (int j = 0; j < employees[i].nKeysPossessed; j++) {
            if (employees[i].keys[j] == key) {
                cout << employees[i].name << ", ";
                found = true;
                break;
            }
        }
    }
    if (found) {
        cout << "possess this key." << endl;
    }
    else {
        cout << "No one possesses this key." << endl;
    }
}




