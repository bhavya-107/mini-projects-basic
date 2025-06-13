#include <iostream>
#include <fstream>
using namespace std;

class temp
{
    string userName, email, password;
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

    switch (choice)
    {
    case '1':
        /* code */
        break;
    case '2':
        /* code */
        break;
    case '3':
        /* code */
        break;
    case '4':
        /* code */
        break;

    default:
        cout << "Invalid Selection!";
        break;
    }
    return 0;
}

void temp ::signUp()
{
    cout << "\n Enter your User Name : ";
    getline(cin, userName);
    cout << "\n Enter your Email Address : ";
    getline(cin, email);
    cout << "\n Enter your Password : ";
    getline(cin, password);

    file.open("loginData.txt", ios ::out | ios ::app);
    file << userName << "*" << email << "*" << password << endl;

    cout<<"test";
}