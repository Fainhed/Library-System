#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
#include <tuple>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string user(string), admin(string);
vector<string> ListBookInfo;
vector<int> ListBookCount;

//Delay display
static int delay(int seconds) {
    clock_t goal = CLOCKS_PER_SEC + clock();
    while (goal > clock());
    return 1;
}
//Clears the screen
static void clear() {
    system("cls");
}
//Greets user
void StartingScreen() {

    delay(2);

    cout << "================================================================" << endl;
    cout << "                      Welcome to LibSys                         " << endl;
    cout << "================================================================" << endl;
    cout << "================================================================" << endl;
    cout << "             Your Library Management System Awaits!             " << endl;
    cout << "================================================================" << endl;

}
//Load the Vector with Data
void LoadFiles() {
    ifstream BookInfo("BookInfo.txt");

    if (BookInfo.is_open()) {
        string line;
        while (getline(BookInfo, line)) {
            ListBookInfo.push_back(line);
        }
        BookInfo.close();
    }
    else {
        cout << "No logs available." << endl;
    }

    BookInfo.close();
    
    ifstream BookCount("BookCount.txt");

    if (BookCount.is_open()) {
        string line;
        while (getline(BookCount, line)) {
            ListBookCount.push_back(stoi(line));
        }
        BookCount.close();
    }
    else {
        cout << "No logs available." << endl;
    }

    BookCount.close();

}
//Save to Book Name to File
void SaveBookInfo() {
    ofstream BookInfo("BookInfo.txt");

    if (!BookInfo) {
        return ;
    }

    for (int i = 0; i < ListBookInfo.size(); i++) {
        BookInfo << ListBookInfo[i] << endl;

    }

    BookInfo.flush();
    BookInfo.close();


}
// Save Book Count to File
void SaveBookCount() {
    ofstream BookCount("BookCount.txt");

    if (!BookCount) {
        return;
    }

    for (int i = 0; i < ListBookCount.size(); i++) {
        BookCount << ListBookCount[i] << endl;
    }

    BookCount.flush();
    BookCount.close();


}
//Saves the Progress to the two files
void Save() {
    SaveBookInfo();
    SaveBookCount();
}
//Displays the Books available in the file
void DisplayBooks() {

    for (int i = 0; i < ListBookInfo.size(); i++) {
        cout <<"[" << i << "] " << ListBookCount[i] << "x " << ListBookInfo[i] << endl;

    }
}

void logUserAction(const string& action, const string& username) {
    // Open the log file in append mode
    ofstream logFile("user_logs.txt", ios::app);

    if (logFile.is_open()) {
        // Get the current timestamp
        time_t now = time(0);
        char* timestamp = ctime(&now);
        timestamp[strlen(timestamp) - 1] = '\0';

        // Write the log entry (timestamp, action, and username)
        logFile << "[" << timestamp << "] User: " << username << " Action: " << action << endl;

        logFile.close();
    }
    else {
        cout << "Error opening log file!" << endl;
    }
}

void BorrowBook(const string &username) {
    DisplayBooks();
    int i;
    cout << endl;
    cout << "What Book Number do you want to borrow?: ";
    cin >> i;

    if (ListBookCount[i] == 0) {
        cout << "Book not available." << endl;
        cout << "Choose another book"<<endl;

        BorrowBook(username);
    }

    else {
        ListBookCount[i]--;

        logUserAction("Borrowed Book", username);
        cout << "You borrowed a book" << endl;
        Save();
    }
    
}

bool AccountChecker(const string& username, const string& password) {

    ifstream file("file.txt");

    if (!file.is_open()) {
        cout << "Error opening file" <<endl;
        return false;
    }

    string line, fileUsername, filePassword;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, fileUsername, ',');
        getline(ss, filePassword, ',');

        if (fileUsername == username && filePassword == password) {
            return true;
        }
    }
    cout << "Invalid Username or Password" << endl;;
    return false;
}
void RegisterUser(const string& username, const string& password) {

    ofstream file("file.txt", ios::app);

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }
    file << username << "," << password << endl;
    file.close();
    cout << "Successfully registered user! ";

}


void UserProfile(const string& username, const string& password) {

    ofstream ProfileIn("Profile.txt");

    int BorrowedBookCount = 0;

    if (ProfileIn.is_open()) {
        ProfileIn << "Username: " << username << endl;
        ProfileIn << "Books Borrowed: " << BorrowedBookCount << endl;

        ProfileIn.close();
    }
    else {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }

    ifstream ProfileOut("Profile.txt");

    if (ProfileOut.is_open()) {
        string info;
        while (getline(ProfileOut, info)) {
            cout << info << endl;
        }
        ProfileOut.close();
    }
    else {
        cout << "Error Loading User Profile" << endl;
    }
}

// Function to log user actions


void DisplayReturnBook(int &MaxNumBooks) {
    int i = 0;
    cout << "Returnable Books: " << endl;

    while (i < ListBookCount[i]) {
        
        if (ListBookCount[i] != MaxNumBooks) {
            cout << "[" << i << "] " << ListBookCount[i] << "/ " << MaxNumBooks << " " << ListBookInfo[i] << endl;

        }
        i++;
    }
}

// Function to display logs (for admin)
void displayLogs() {
    ifstream logFile("user_logs.txt");

    if (logFile.is_open()) {
        string line;
        while (getline(logFile, line)) {
            cout << line << endl;
        }
        logFile.close();
    }
    else {
        cout << "No logs available." << endl;
    }
}

// Function to clear logs (admin only)
void clearLogs() {
    ofstream logFile("user_logs.txt"); // Open in trunc mode to clear the file
    if (logFile.is_open()) {
        logFile.close();
        cout << "Logs have been cleared." << endl;
    }
    else {
        cout << "Error clearing log file!" << endl;
    }
}

// Admin login function
bool adminLogin() {
    string username, password;
    const string correctUsername = "admin";
    const string correctPassword = "admin123";

    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    return (username == correctUsername && password == correctPassword);
}

//Brings up the Main Menu
int Menu() {

    int answer;
    delay(2);

    cout << "================================================================" << endl;
    cout << "                      Welcome to LibSys                         " << endl;
    cout << "================================================================" << endl;
    cout << endl;
    cout << "                  What do you want to do? " << endl;
    cout << endl;
    cout << "1. Display Available Books  " << endl;
    cout << "2. Borrow a Book " << endl;
    cout << "3. Return a Book" << endl;
    cout << "4. Profile" << endl;
    cout << "5. Credits" << endl;
    cout << "6. Exit" << endl;
    cout << endl;

    cout << "Enter input: "; cin >> answer;
    return answer;

}
int SystemCredits() {
    ifstream Credits("Credits.txt");

    if (!Credits) {
        cout << "Error opening file. T_T" << endl;
        return false;
    }
    string line;
    
}

//Main code
int main() {

    int choice;
    string response;
    string username, password;

    /*clear();
    cout << "Starting...";
    delay(2);
    clear();

    StartingScreen();
    delay(3);
    clear();*/

    LoadFiles();

    cout << "To access the library, choose one of the options: " << endl;
    cout << "1. Log in " << endl;
    cout << "2. Register" << endl;
    cout << "3. Admin"<<endl;
    cout << endl;
    cout << "Enter choice: "; cin >> choice;

    switch (choice) {
        case 1:
            clear();
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;
            if (AccountChecker(username, password)) {
                clear();
                cout << "Login Successful.";
                delay(2);
                clear();
                int answer = Menu();
                while (true) {
                    switch (answer) {
                    case 1:
                        clear();
                        DisplayBooks();
                        cout << "Go back?(y/yes): ";
                        cin >> response;
                        if (response == "yes" || response == "y") {
                            clear();
                            answer = Menu();
                        }
                        break;
                       
                     case 2:
                         
                         BorrowBook(username);

                         
                         break;
                    
                    case 3:
                        int MaxNumBooks;
                         DisplayReturnBook(MaxNumBooks);
                         logUserAction("Returned a Book", username);
                         break;
                    /*
                        case 4:
                            UserProfile();
                            break;
                        case 5:
                            SystemCredits();
                            break;
                        */
                    case 6:
                        cout << "Exiting.... Thank you for using Libsys!" << endl;
                        return 0;
                        break;

                    default:
                        cout << "I dunno, you should not be here..." << endl;
                        break;

                    }
                }
            }
            else {
                // If login fails, ask the user if they want to try again
                cout << "Login failed. Would you like to try again? (yes/no): ";
                string response;
                cin >> response;
                if (response == "yes") {
                    main();  // Restart the login process
                }
                else {
                    cout << "Exiting the system..." << endl;
                    return 0;
                }
            }
            break;


        case 2:
            clear();
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;
            RegisterUser(username, password);
            break;

        case 3:
            clear();
            cout << "\nAdmin Login Section\n";
            if (adminLogin()) {
                clear();
                cout << "Admin login successful!" << endl;
                delay(2);
                clear();

                while (true) {
                    cout << "Choose an admin action: " << endl;
                    cout << "1. View Logs" << endl;
                    cout << "2. Add Book" << endl;
                    cout << "3. Clear Logs" << endl;
                    cout << "4. Display Books" << endl;
                    cout << "5. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    if (choice == 1) {
                        cout << "Displaying Logs: " << endl;
                        displayLogs();
                    }
                    else if (choice == 2) {

                        string input;
                        int num, MaxNumBooks;

                        cout << "What Book do you want to add? :"; 
                        cin >> input;
                        ListBookInfo.push_back(input);

                        cout << "How many?: ";
                        cin >> num;
                        MaxNumBooks = num;
                        ListBookCount.push_back(num);
                        
                        Save();
                        DisplayBooks();
                    }
                    else if (choice == 3) {
                        clearLogs();
                    }
                    else if (choice == 4) {
                        DisplayBooks();
                        break;
                    }
                    else if (choice == 5) {
                        return false;
                        break;
                    }
                    else {
                        cout << "Invalid choice." << endl;
                    }
                }
                
            }
            else {
                cout << "Invalid admin credentials!" << endl;
            }
            break;

        default: return 0;
     
    }
        
}
