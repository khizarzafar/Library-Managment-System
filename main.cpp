#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <conio.h> // For getch()

using namespace std;

// Class
class UserLogin
{
private:
    string LoginId, Password;

public:
    UserLogin() : LoginId(""), Password("") {}
    // setters
    void SetId(string id) { LoginId = id; }
    void Setpass(string pass) { Password = pass; }
    // getters
    string getId() { return LoginId; }
    string getpass() { return Password; }
};

// Function to get hide password
string getHiddenPassword()
{
    string password;
    char ch;

    cout << "\tEnter Password: ";
    while ((ch = _getch()) != '\r') // Stop when Enter is pressed
    {
        if (ch == '\b') // Handle backspace
        {
            if (!password.empty())
            {
                cout << "\b \b"; // Remove last *
                password.pop_back();
            }
        }
        else
        {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

// Registration function
void registration(UserLogin &user)
{
    system("cls");
    string id, pass;

    cout << "\t\033[34mEnter id: ";
    cin >> id;
    user.SetId(id);

start:
    pass = getHiddenPassword();
    if (pass.length() >= 8)
    {
        user.Setpass(pass);
    }
    else
    {
        cout << "\tEnter password of minimum 8 characters.\n";
        goto start;
    }
    ofstream MyFile("Data File.txt", ios::app);
    if (!MyFile)
    {
        cout << "\tError: File cannot be opened." << endl;
    }
    else
    {
        MyFile << user.getId() << " : " << user.getpass() << endl;
        cout << "\tStudent data is entered successfully!";
    }
    MyFile.close();
    cout << "\n\tPress enter to continue...\033[0m";
    cin.ignore();
    cin.get();
}

// login function
void login()
{
    system("cls");
    string id, pass;
    cout << "\t\033[34mEnter the id: ";
    cin >> id;
    pass = getHiddenPassword();

    ifstream MyFile("Data File.txt");
    if (!MyFile)
    {
        cout << "\tError! File can't be opened.";
    }
    else
    {
        string line;
        bool found = false;
        while (getline(MyFile, line))
        {
            stringstream ss;
            ss << line;
            string userID, userPass;
            char delimeter;
            ss >> userID >> delimeter >> userPass;

            if (id == userID && pass == userPass)
            {
                found = true;
                cout << "\tPlease Wait";
                for (int i = 0; i < 3; i++)
                {
                    cout << ".";
                    Sleep(800);
                }
                system("cls");
                cout << "\tLogin Successful!" << endl;
                cout << "\tWelcome to the Library Management System!" << endl;
            }
        }
        if (!found)
        {
            cout << "\tIncorrect user ID or Password." << endl;
        }
    }
    cout << "\tPress Enter to continue...\033[0m";
    cin.ignore();
    cin.get();
    MyFile.close();
}

void displayMenu()
{
    cout << "\t\033[1;31mWELCOME TO LIBRARY MANAGEMENT SYSTEM!!!\033[0m" << endl;
    cout << "\t\033[1;34m1. Register" << endl;
    cout << "\t2. Login" << endl;
    cout << "\t3. Exit" << endl;
    cout << "\tEnter choice: ";
}

// main function
int main()
{
    UserLogin log;
    bool exit = false;
    while (!exit)
    {
        system("cls"); // clear the previous output
        displayMenu();

        int val;

        // Checking for invalid input
        while (!(cin >> val))
        {
            // fail state(prevent futher inputs)
            cin.clear();           // this allows cin to accept new input.
            cin.ignore(100, '\n'); // remove previous input buffer
            cout << "\tInvalid input! Enter a number: ";
            continue;
        }

        Sleep(3000);

        switch (val)
        {
        case 1:
            registration(log);
            break;
        case 2:
            login();
            break;
        case 3:
            system("cls");
            exit = true;
            cout << "\tExited the program successfully!";
            Sleep(2000);
            break;
        default:
            cout << "\tInvalid choice! Please select 1, 2, or 3.";
            Sleep(2000);
        }
    }

    return 0;
}
