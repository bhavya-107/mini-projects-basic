#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class temp
{
    string userName, email, password;
    string searchName, searchPass, searchEmail;
    fstream file;

public:
    void login();
    void signUp();
    void forgotPassword();
} obj;

int main()
{
    char choice;
    cout << "\n 1 - Login";
    cout << "\n 2 - Sign Up";
    cout << "\n 3 - Forgot Password";
    cout << "\n 4 - Exit";
    cout << "\n Enter your choice : ";
    cin >> choice;

    switch (choice)
    {
    case '1':
        obj.login();
        break;
    case '2':
        obj.signUp();
        break;
    case '3':
        obj.forgotPassword();
        break;
    case '4':
        return 0;

    default:
        cout << "Invalid Selection!";
        break;
    }
    return 0;
}

void temp::signUp()
{
    cout << "\n Enter your User Name : ";
    cin.ignore();
    getline(cin, userName);
    cout << "\n Enter your Email Address : ";
    getline(cin, email);
    cout << "\n Enter your Password : ";
    getline(cin, password);

    file.open("loginData.txt", ios::out | ios::app);
    if (file.is_open()) {
        file << userName << "*" << email << "*" << password << '\n';
        file.close();
        cout << "\n Account created successfully!" << endl;
    } else {
        cout << "\n Error: Could not open file for writing!" << endl;
    }
}

void temp::login()
{
    cout << "----------Login----------" << endl;
    cout << "Enter your User Name : ";
    cin.ignore();
    getline(cin, searchName);
    cout << "Enter your Password: ";
    getline(cin, searchPass);

    file.open("loginData.txt", ios::in);
    if (!file.is_open()) {
        cout << "\n Error: Could not open login data file!" << endl;
        return;
    }

    bool found = false;
    while (getline(file, userName, '*') && 
           getline(file, email, '*') && 
           getline(file, password, '\n'))
    {
        if (userName == searchName)
        {
            found = true;
            if (password == searchPass)
            {
                cout << "\n Account Login Successful!" << endl;
                cout << "\n User Name : " << userName << endl;
                cout << "\n Email : " << email << endl;
                file.close();
                return;
            }
            else
            {
                cout << "\n Incorrect Password!" << endl;
                file.close();
                return;
            }
        }
    }
    
    if (!found) {
        cout << "\n User Name not found!" << endl;
    }
    file.close();
}

void temp::forgotPassword()
{
    cout << "\n Enter your User Name : ";
    cin.ignore();
    getline(cin, searchName);
    cout << "\n Enter your Email Address : ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);
    if (!file.is_open()) {
        cout << "\n Error: Could not open login data file!" << endl;
        return;
    }

    bool found = false;
    while (getline(file, userName, '*') && 
           getline(file, email, '*') && 
           getline(file, password, '\n'))
    {
        if (userName == searchName && email == searchEmail)
        {
            cout << "\n Account found!" << endl;
            cout << "Your Password : " << password << endl;
            found = true;
            file.close();
            return;
        }
    }
    
    if (!found) {
        cout << "\n User Name or Email not found!" << endl;
    }
    file.close();
}