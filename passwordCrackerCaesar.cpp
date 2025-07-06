#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Decryptor
{
private:
    int shiftKey;

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
    void setKey(int key)
    {
        shiftKey = key;
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

    bool decryptFile(const string &inputFile)
    {
        ifstream inFile(inputFile);
        // ofstream outFile(outputFile);

        if (!inFile.is_open())
        {
            cout << "Error: Cannot open input file" << endl;
            return false;
        }

        // if (!outFile.is_open())
        // {
        //     cout << "Error: Cannot create output file" << endl;
        //     inFile.close();
        //     return false;
        // }

        string line;
        while (getline(inFile, line))
        {
            cout << "Trying Key " << shiftKey << ": " << decryptText(line) << endl;

        }

        inFile.close();
        // outFile.close();
        return true;
    }
};

int main()
{
    Decryptor decryptor;
    string inputFile;

    int keyList[26] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

    cout << "Enter file name: " << endl;
    getline(cin, inputFile);
    for (int i : keyList)
    {
        decryptor.setKey(i);
        decryptor.decryptFile(inputFile);
    }

    return 0;
}