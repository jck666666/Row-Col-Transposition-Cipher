#include <iomanip>
#include <iostream>
#include <string>
#include <string.h>
#include <math.h>

using namespace std;

int key[50];
char text[50][50] = {};

int depth;
int keylen;
int textlen;

string plaintext;
string ciphertext;

bool AlreadyHave(int k, char c, int key[])
{
    for (int i = 0; i < k; i++)
    {
        if (c - '0' == key[i])
            return true;
    }
    return false;
}

int InputKey()
{
    string keyin;
    int k = 0;

    cout << "Key: ";
    cin.ignore(1024, '\n');
    getline(cin, keyin);
    while (1)
    {
        k = 0;
        for (int i = 0; i < keyin.length(); i += 2)
        {

            if (keyin[i] - '0' >= 0 && keyin[i] - '0' <= 9 && !AlreadyHave(k, keyin[i], key))
            {
                key[k++] = keyin[i] - '0';
            }
            else
            {
                break;
            }
        }

        if (2 * k - 1 == keyin.length())
        {
            break;
        }

        cout << "Invalid key :(     Input all the key again!\n\n";
        cout << "Key: ";
        getline(cin, keyin);
    }
    return k;
}

void outputText()
{
    for (int row = 0; row < depth; row++)
    {
        for (int col = 0; col < keylen; col++)
        {
            cout << text[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void encryption()
{
    /*------   ↓input the key↓   ------*/
    keylen = InputKey();

    /*------   ↓input the plain text↓   ------*/
    cout << "Plain Text: ";
    getline(cin, plaintext);

    textlen = 1;
    for (int i = 0; i < plaintext.length(); i++)
    {
        if (plaintext[i] != ' ') textlen++;
    }cout << endl;

    /*------   ↓construct text[][]↓  ------*/
    depth = ceil((float)textlen / keylen);
    int index = 0;
    for (int row = 0; row < depth; row++)
    {
        for (int col = 0; col < keylen; col++)
        {
            while (plaintext[index] == ' ')
            {
                index++;
            }

            if (plaintext[index] != '\0')
            {
                text[row][col] = plaintext[index++];
            }
            else
            {
                text[row][col] = 'X';
            }
        }
    }
    /*------   ↓output text[][]↓  ------*/
    outputText();

    /*------  ↓generate cipher text ↓  ------*/
    for (int i = 1; i <= keylen; i++) //find the key from 1
    {
        int col = -1;
        do
        {
            col++;
        } while (key[col] != i);

        if (key[col] == i)
        {
            for (int row = 0; row < depth; row++)
            {
                ciphertext += text[row][col];
            }
        }
    }

    cout << "ciphertext: " << ciphertext << endl<< endl;
}

void decryption()
{

    /*------   ↓input the key↓   ------*/
    keylen = InputKey();

    /*------   ↓input the cipher text↓   ------*/
    cout << "Cipher Text: ";
    getline(cin, ciphertext);

    textlen = 0;
    for (int i = 0; i < ciphertext.length(); i++)
    {
        ++textlen;
    }
    cout << endl;

    /*------   ↓construct text[][]↓  ------*/
    depth = ceil((float)textlen / keylen);
    int index = 0;
    for (int i = 1; i <= keylen; i++) //find the key from 1
    {
        int col = -1;
        do
        {
            col++;
        } while (key[col] != i);

        if (key[col] == i)
        {
            for (int row = 0; row < depth; row++)
            {
                text[row][col] = ciphertext[index++];
            }
        }
    }

    /*------   ↓output text[][]↓  ------*/
    outputText();

    /*------  ↓generate plain text ↓  ------*/
    for (int row = 0; row < depth; row++)
    {
        for (int col = 0; col < keylen; col++)
        {
            plaintext += text[row][col];
        }
    }
    cout << "plaintext: " << plaintext << endl;
}
int main()
{
    while (1)
    {
        cout << "E(Encryption) or D(Decryption): ";
        char operation;
        cin >> operation;

        if (operation == 'E')
        {
            encryption();
            break;
        }
        else if (operation == 'D')
        {
            decryption();
            break;
        }
        else
        {
            cout << "No such instructions. Please enter again." << endl
                 << endl;
        }
    }

    return 0;
}