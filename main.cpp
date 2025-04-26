#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct toDo     // Store ID and Tasks
{
    int id;
    string task;
    string complete;
};

/* IGNORE THIS */
int choice, ID;
char save, more, RETURN, DELETE, mark;

toDo add;

void header();
void addTask();
void displayTasks();
void markTasks();
void removeTasks();

void saveToDo();
void moreToDo();
void returnToDo();
int searchID();
void delToDo();
/* ============= */

int main() 
{
    system("clear");

    // UI
    do {
        header();       // Display TO-DO LISTS

        cout << "[1] Add a task." << '\n';
        cout << "[2] Display task(s)." << '\n';
        cout << "[3] Mark task(s) as completed." << '\n';
        cout << "[4] Remove task(s)." << '\n';

        cout << "\n[0] Exit." << '\n';

        cout << "=======================================" << '\n';

        // Prompt User Inputs
        cout << "Enter your choice : ";
        cin >> choice;

        // Key Press
        switch (choice) {
            case 1:
                addTask();
                break;

            case 2:
                displayTasks();
                break;

            case 3:
                markTasks();
                break;

            case 4:
                removeTasks();
                break;

            case 0:
                exit(0);
                break;

            default:
                system("clear");
                cout << "\n** Please enter a valid number between [1] and [4]." << '\n';
        }

    } while (choice != 5);

    return 0;
}

void header() {
    cout << "\n=======================================" << '\n';
    cout << "\t      TO-DO LISTS" << '\n';
    cout << "=======================================" << '\n';
}

void addTask() {
    system("clear");
    header();

    char save, more;

    // Ask user what task to add
    cout << "Enter a new task : ";

    cin.clear();
    cin.ignore();
    getline(cin, add.task);

    // Ask user to save the task
    saveToDo();
    
    system("clear");
}

void displayTasks() {
    system("clear");
    header();

    // It will open .txt file
    ifstream f_in;
    f_in.open("todo.txt");

    cout << "Here is Your Task(s) : " << '\n';

    // Displaying tasks from .txt file
    while (!f_in.eof()) {
        f_in >> add.id;
        f_in.ignore();
        getline(f_in, add.task);

        if (add.task != "") {       // If tasks exist, show them
            cout << add.id << " : " << add.task << '\n';
        }
        else {
            cout << "Empty !" << '\n';      // If no tasks exist
        }
    }
    f_in.close();       // Close .txt file

    // Ask user to return to the main screen
    returnToDo();

    system("clear");
}

int searchID() {
    int id;
    cout << "Enter task ID : ";
    cin >> id;

    // Display the task
    ifstream f_in("todo.txt");

    while (!f_in.eof()) {       // Get info from .txt file
        f_in >> add.id;
        f_in.ignore();
        getline(f_in, add.task);

        if (add.id == id) {
            cout << add.id << " : " << add.task << '\n';
            return id;
        }
    }
    system("clear");

    // If no tasks exist
    cout << "NOT FOUND ! " << '\n';

    return 0;
}

void markTasks() {
    system("clear");
    header();

    char markMore;

    // Ask user for task ID
    do {
        // Ask user for task ID
        int id = searchID();
        bool taskFound = false; // Flag to track whether the task is found

        // If found, ask user to mark as done
        if (id != 0) {
            cout << "Mark as DONE? (y/n) : ";
            cin >> mark;

            if (mark == 'y' || mark == 'Y') {       // Mark the task as completed
                // Set the flag when the task is found
                taskFound = true;       
            } 
            else if (mark == 'n' || mark == 'N') {
                // Return to markTasks without marking the task as done
                system("clear");
                return;
            } 
            else {
                cout << "\nInvalid input." << '\n';
                // Return to markTasks without marking the task as done
                markTasks();
            }

            ifstream f_in("todo.txt");
            ofstream tempFile("temp.txt");
            int index = 1;

            while (!f_in.eof()) {
                f_in >> add.id;
                f_in.ignore();
                getline(f_in, add.task);

                if (add.id == id) {
                    // Mark the task as completed if 'y' or 'Y' is entered
                    tempFile << '\n' << index;
                    tempFile << '\n' << add.task << '\t' << "(DONE)";
                } 
                else {
                    tempFile << '\n' << index;
                    tempFile << '\n' << add.task;
                }
                index++;
            }

            f_in.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");

            system("clear");

            if (taskFound) {
                cout << "\nMarked as DONE Successfully ! " << '\n';
            } 
            else {
                cout << "\nTask not found. Nothing marked as DONE." << '\n';
                return;
            }
        }

        // Ask user to mark more task(s)
        cout << "\nMark another task as DONE? (y/n) : ";
        cin >> markMore;

        system("clear");

    } while (markMore == 'y' || markMore == 'Y');
}

void removeTasks() {
    system("clear");
    header();

    delToDo();
}

void saveToDo () {
    cout << "\nDo you want to save? (y/n) : ";
    cin >> save;

    if (save == 'y' || save == 'Y') {
        cout << "Saved Successfully ! " << '\n';
        ID++;

        // It will write the .txt file
        ofstream f_out;
        f_out.open("todo.txt", ios::app);
        f_out << "\n" << ID;
        f_out << "\n" << add.task;
        f_out.close();
            
        // Ask user to add another task
        moreToDo();
    }
    else if (save == 'n' || save == 'N') {
        return;
    }
    else {
        cout << "\n** Please enter a valid character.";
        saveToDo();
    }
}

void moreToDo() {
    cout << "\nDo you want to add another task? (y/n) : ";
    cin >> more;

    if (more == 'y' || more == 'Y') {
        addTask();
    } 
    else if (more == 'n' || more == 'N') {
        system("clear");
        cout << "Added Successfully ! " << '\n';
        return;
    }   
    else {
        cout << "\n** Please enter a valid character.";
        moreToDo();
    }
}       

void returnToDo() {
    cout << "Return ? (y/n) : ";
    cin >> RETURN;

    if (RETURN == 'y' || RETURN == 'Y') {
        return;
    }
    else if (RETURN == 'n' || RETURN == 'N') {
        displayTasks();
    }
    else {
        cout << "\n** Please enter a valid character." << '\n';
        returnToDo();
    }
}

void delToDo() {
    // Ask user for task ID
    int id = searchID();

    cout << "Do you want to DELETE? (y/n) : ";
    cin >> DELETE;

    // If found, ask user to delete
    if (id != 0) {
        if (DELETE == 'y' || DELETE == 'Y') {
            // Open .txt file and remove the task
            ofstream tempFile;
            tempFile.open("temp.txt");
            ifstream f_in;
            f_in.open("todo.txt");
            int index = 1;

            while (!f_in.eof()) {
                f_in >> add.id;
                f_in.ignore();
                getline(f_in, add.task);

                if (add.id != id) {
                    tempFile << '\n' << index;
                    tempFile << '\n' << add.task;
                    index++;
                    ID--;
                }
            }
            f_in.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");

            system("clear");

            cout << "\nDELETED Successfully ! " << '\n';
        }
        else if (DELETE == 'n' || DELETE == 'N') {
            system("clear");
            cout << "Not DELETED ! " << '\n';
            return;
        }
        else {
            cout << "\n** Please enter a valid character." << '\n';
            delToDo();
        }
    }
    // If not found, return back
    else {
        cout << "Tasks Not Found. " << '\n';
        return;
    }
}




