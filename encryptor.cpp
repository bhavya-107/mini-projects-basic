#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class textEncryptor
{
private:
    int shiftKey;

    char encryptChar(char ch)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            return ((ch - 'A' + shiftKey) % 26) + 'A';
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            return ((ch - 'a' + shiftKey) % 26) + 'a';
        }
        else
        {
            return ch;
        }
    }
    char decryptChar(char ch)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            return ((ch - 'A' - shiftKey + 26) % 26) + 'A';
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            return ((ch - 'a' - shiftKey + 26) % 26) + 'a';
        }
        else
        {
            return ch;
        }
    }

public:
    textEncryptor()
    {
        shiftKey = 0;
    }

    void setKey(int key)
    {
        shiftKey = ((key % 26) + 26) % 26;
        if (shiftKey == 0)
            shiftKey = 1;
    }

    string encryptText(const string &text)
    {
        string encrypted = "";
        for (char ch : text)
        {
            encrypted += encryptChar(ch);
        }
        return encrypted;
    }

    string decryptText(const string &text)
    {
        string decrypted = "";
        for (char ch : text)
        {
            decrypted += decryptChar(ch);
        }
        return decrypted;
    }

    bool encryptFile(const string &inputFile, const string &outputFile)
    {
        ifstream inFile(inputFile);
        ofstream outFile(outputFile);

        if (!inFile.is_open())
        {
            cout << "Error: Cannot open input file '" << inputFile << "'" << endl;
            return false;
        }

        if (!outFile.is_open())
        {
            cout << "Error; Cannot create output File '" << outputFile << "'" << endl;
            inFile.close();
            return false;
        }

        string line;
        while (getline(inFile, line))
        {
            outFile << encryptText(line) << '\n';
        }

        inFile.close();
        outFile.close();

        cout << "File encrypted successfully!" << endl;
        cout << "Input: " << inputFile << endl;
        cout << "Output: " << outputFile << endl;
        cout << "Shift Key: " << shiftKey << endl;

        return true;
    }

    bool decryptFile(const string &inputFile, const string &outputFile)
    {
        ifstream inFile(inputFile);
        ofstream outFile(outputFile);

        if (!inFile.is_open())
        {
            cout << "Error: Cannot open input file '" << inputFile << "'" << endl;
            return false;
        }

        if (!outFile.is_open())
        {
            cout << "Error; Cannot create output File '" << outputFile << "'" << endl;
            inFile.close();
            return false;
        }

        string line;
        while (getline(inFile, line))
        {
            outFile << decryptText(line) << '\n';
        }

        inFile.close();
        outFile.close();

        cout << "File decrypted successfully!" << endl;
        cout << "Input: " << inputFile << endl;
        cout << "Output: " << outputFile << endl;
        cout << "Shift Key: " << shiftKey << endl;

        return true;
    }

    int getKey() const
    {
        return shiftKey;
    }

    void demoEncryption()
    {
        cout << "\n=== ENCRYPTION DEMOSTRATION ===" << endl;
        cout << "Current shift key: " << shiftKey << endl;

        string example[] = {"Hello World!"};

        for (const string &text : example)
        {
            string encrypted = encryptText(text);
            string decrypted = decryptText(encrypted);

            cout << "\nOriginal: " << text << endl;
            cout << "Encrypted: " << encrypted << endl;
            cout << "Decrypted: " << decrypted << endl;
            cout << "Match: " << (text == decrypted ? "matched" : "not matched") << endl;
        }
    }
};

void displayMenu()
{
    cout << "\n|--------------------------------|" << endl;
    cout << "|     TEXT FILE ENCRYPTOR        |" << endl;
    cout << "|--------------------------------|" << endl;
    cout << "| 1. Encrypt a file              |" << endl;
    cout << "| 2. Decrypt a file              |" << endl;
    cout << "| 3. Set encryption key          |" << endl;
    cout << "| 4. View current key            |" << endl;
    cout << "| 5. Demo encryption             |" << endl;
    cout << "| 6. Exit                        |" << endl;
    cout << "|--------------------------------|" << endl;
    cout << "Enter your choice (1-6): ";
}

int main()
{
    textEncryptor encryptor;
    int choice;
    string inputFile, outputFile;
    int key;

    encryptor.setKey(3);

    cout << "Welcome to Text File Encryptor!" << endl;

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            cout << "\n---ENCRYPT FILE---" << endl;
            cout << "Enter input filename: ";
            getline(cin, inputFile);
            cout << "Enter output filename: ";
            getline(cin, outputFile);

            if (!encryptor.encryptFile(inputFile, outputFile))
            {
                cout << "Encryption failed" << endl;
            }
            break;
        }
        case 2:
        {
            cout << "\n---DECRYPT FILE---" << endl;
            cout << "Enter encrypted filename: ";
            getline(cin, inputFile);
            cout << "Enter output filename: ";
            getline(cin, outputFile);

            if (!encryptor.decryptFile(inputFile, outputFile))
            {
                cout << "Decryption failed" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "\n---SET ENCRYPTION KEY---" << endl;
            cout << "Enter shift value (1-25): ";
            cin >> key;

            if (key < 1 || key > 25)
            {
                cout << "Warning: Key should be between 1-25. Adjusting..." << endl;
            }

            encryptor.setKey(key);
            cout << "Encryption key set to: " << encryptor.getKey() << endl;
            break;
        }

        case 4:
        {
            cout << "\n---CURRENT SETTINGS---" << endl;
            cout << "Current encryption key: " << encryptor.getKey() << endl;
            cout << "Cipher type: Caesar Cipher" << endl;
            break;
        }

        case 5:
        {
            encryptor.demoEncryption();
            break;
        }

        case 6:
        {
            cout << "\nThank you for using Text File Encryptor!" << endl;
            break;
        }

        default:
        {
            cout << "Invalid choice! Please enter 1-6." << endl;
            break;
        }
        }

        if (choice != 6)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 6);

    return 0;
}