#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int checkPasswordStrength(const string &password)
{
    int score = 0;
    ;
    int length = password.length();

    if (length >= 8)
    {
        score += 2;
        cout << "Length is good (8+ characters): +2 points" << endl;
    }
    else if (length >= 6)
    {
        score += 1;
        cout << "Length is okay (6-7 characters): +1 point" << endl;
    }
    else
    {
        cout << "Length is too short (less than 6 characters): +0 points" << endl;
    }

    bool hasLower = false;
    for (char c : password)
    {
        if (islower(c))
        {
            hasLower = true;
            break;
        }
    }

    if (hasLower)
    {
        score += 1;
        cout << "Contains lowercase letters: +1 point" << endl;
    }
    else
    {
        cout << "No lowercase letters found: +0 points" << endl;
    }

    bool hasUpper = false;
    for (char c : password)
    {
        if (isupper(c))
        {
            hasUpper = true;
            break;
        }
    }

    if (hasUpper)
    {
        score += 1;
        cout << "Contains uppercase letters: +1 points" << endl;
    }
    else
    {
        cout << "No uppercase letters found: +0 points" << endl;
    }

    bool hasDigit = false;
    for (char c : password)
    {
        if (isdigit(c))
        {
            hasDigit = true;
            break;
        }
    }

    if (hasDigit)
    {
        score += 1;
        cout << "Contains numbers: +1 point" << endl;
    }
    else
    {
        cout << "No numbers found: +0 point" << endl;
    }

    bool hasSpecial = false;
    string specialChars = "!@#$%^&*(){}[]<>,.?|";
    for (char c : password)
    {
        for (char special : specialChars)
        {
            if (c == special)
            {
                hasSpecial = true;
                break;
            }
        }
        if (hasSpecial)
            break;
    }

    if (hasSpecial)
    {
        score += 2;
        cout << "Contains special characters: +2 points" << endl;
    }
    else
    {
        cout << "No special characters found: +0 point" << endl;
    }

    if (length >= 12)
    {
        score += 1;
        cout << "Bonus for long password (12+ characters): +1 point" << endl;
    }

    string lowerPassword = password;

    for (char &c : lowerPassword) {
        c = tolower(c);
    }

    string weakPasswords[] = {"password", "123456", "qwerty", "abc123", 
                             "password123", "admin", "letmein", "welcome"};
    
    for (string weak : weakPasswords) {
        if(lowerPassword == weak) {
            score -=3;
            cout << "Warning: This is a commonly used password! -3 points" <<endl;
            break;
        }
    }

    bool hasPattern = false;
    if (lowerPassword.find("123456") != string::npos ||
        lowerPassword.find("abcdef") != string::npos ||
        lowerPassword.find("qwerty") != string::npos) {
            score -=1;
            hasPattern= true;
            cout << "Contains common pattern: -1 point" <<endl;
        }

    return score;
 
}

string getPasswordRating(int score) {
    if (score >=7) {
        return "STRONG - Excellent password!";
    } else if (score >=5) {
        return "GOOD - Decent password, but could be better";
    } else if (score>=3) {
        return "WEAK - Consider making it stronger";
    } else {
        return "VERY WEAK - This password is easily hackable!";
    }
}

void giveSuggestions (const string& password) {
    cout << "\n=== Suggestions to improve your password ===" << endl;

    if (password.length()< 8) {
        cout << "Make it at least 8 characters long" << endl;
    }

    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial=false;

    for(char c: password) {
        if(islower(c)) hasLower=true;
        if(isupper(c)) hasUpper=true;
        if(isdigit(c)) hasDigit= true;
        if (string("!@#$%^&*()_+-=[]{}|;:,.<>?").find(c) != string::npos) hasSpecial=true;
    }

    if (!hasLower) cout << " Add some lowercase letters (a-z)" << endl;
    if (!hasUpper) cout << " Add some uppercase letters (A-Z)" << endl;
    if (!hasDigit) cout << " Add some numbers (0-9)" << endl;
    if (!hasSpecial) cout << "Add special characters (!@#$%^&*)" << endl;
    
    cout << " Avoid common passwords like 'password123'" << endl;
    cout << " Don't use personal information (birthdate, name)" << endl;
    cout << " Consider using a passphrase like 'Coffee$Morning2024!'" << endl;
}

int main() {
    string password;
    char choice;

     cout << "======================================" << endl;
    cout << " PASSWORD STRENGTH CHECKER " << endl;
    cout << "======================================" << endl;
    cout << "This tool will check how strong your password is!" << endl;
    cout << "Note: Your password won't be saved anywhere." << endl;

    do {
        cout << "\nEnter your password to check: ";
        getline(cin, password);

        if(password.empty()) {
            cout <<"Please enter a password!" << endl;
            continue;
        }

        cout <<"\n---Analyzing your password---"<<endl;

        int score = checkPasswordStrength(password);

        cout << "\n================================" << endl;
        cout << "TOTAL SCORE: " << score << "/8 points" << endl;
        cout << "RATING: " << getPasswordRating(score) << endl;
        cout << "================================" << endl;

        giveSuggestions(password);

        cout <<"\nWant to check another password? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice=='Y');

     cout << "\nThanks for using Password Strength Checker!" << endl;
    cout << "Remember: Use strong, unique passwords for all accounts! 🔒" << endl;
    
    return 0;
}

