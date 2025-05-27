#include <bits/stdc++.h>  // For time

using namespace std;

// FiboFlux Seeding Cipher
// FiboRandom Seeding Cipher

vector<int> generateFibonacci(int n, int seed1, int seed2)
{
    if (n <= 0)
        return {}; // Handle empty or invalid length
    vector<int> fib(n);
    if (n > 0)
        fib[0] = seed1 % 26;
    if (n > 1)
        fib[1] = seed2 % 26;
    for (int i = 2; i < n; ++i)
    {
        fib[i] = (fib[i - 1] + fib[i - 2]) % 26;
    }
    return fib;
}

char encryptChar(char ch, int shift)
{
    // Define the pool of special characters to be encrypted.
    // This string contains 33 characters: space, and common punctuation/symbols.
    // Note: backslash `\` is escaped as `\\`.
    static const string SPECIAL_CHAR_POOL = " !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    if (isupper(ch))
    {
        return 'A' + (ch - 'A' + shift) % 26;
    }
    else if (islower(ch))
    {
        return 'a' + (ch - 'a' + shift) % 26;
    }
    else if (isdigit(ch))
    {
        // Shift digits '0'-'9'
        // The 'shift' value is 0-25 from Fibonacci.
        // We'll take this shift modulo 10 for digits.
        return '0' + (ch - '0' + (shift % 10)) % 10;
    }
    else // Handle other characters (including special characters)
    {
        size_t pos = SPECIAL_CHAR_POOL.find(ch);
        if (pos != string::npos)
        {
            // Character is in our defined pool of special characters
            int pool_size = SPECIAL_CHAR_POOL.length();
            // The 'shift' is 0-25. pool_size is 33.
            // (pos + shift) % pool_size will correctly cycle within the pool.
            return SPECIAL_CHAR_POOL[(pos + shift) % pool_size];
        }
        else
        {
            // Character is not alphanumeric and not in our special pool
            // (e.g., newline, tab, other control characters, or extended ASCII not in the pool)
            return ch; // Return unchanged
        }
    }
}

char decryptChar(char ch, int shift)
{
    // Define the pool of special characters consistent with encryptChar.
    static const string SPECIAL_CHAR_POOL = " !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    if (isupper(ch))
    {
        return 'A' + (ch - 'A' - shift + 26) % 26;
    }
    else if (islower(ch))
    {
        return 'a' + (ch - 'a' - shift + 26) % 26;
    }
    else if (isdigit(ch))
    {
        // Decrypt digits '0'-'9'
        // The 'shift' value is 0-25 from Fibonacci.
        // We must use the same effective shift (mod 10) that was used for encryption.
        return '0' + (ch - '0' - (shift % 10) + 10) % 10;
    }
    else // Handle other characters (including special characters)
    {
        size_t pos = SPECIAL_CHAR_POOL.find(ch);
        if (pos != string::npos)
        {
            // Character is in our defined pool of special characters
            int pool_size = SPECIAL_CHAR_POOL.length();
            // (pos - shift + pool_size) ensures the argument to % is non-negative
            return SPECIAL_CHAR_POOL[(pos - shift + pool_size) % pool_size];
        }
        else
        {
            // Character is not alphanumeric and not in our special pool
            return ch; // Return unchanged
        }
    }
}

string encrypt(string plaintext, int seed1, int seed2)
{
    int n = plaintext.length();
    if (n == 0)
        return ""; // Handle empty string
    vector<int> fib = generateFibonacci(n, seed1, seed2);
    string ciphertext = "";

    for (int i = 0; i < n; ++i)
    {
        ciphertext += encryptChar(plaintext[i], fib[i]);
    }
    return ciphertext;
}

string decrypt(string ciphertext, int seed1, int seed2)
{
    int n = ciphertext.length();
    if (n == 0)
        return ""; // Handle empty string
    vector<int> fib = generateFibonacci(n, seed1, seed2);
    string plaintext = "";

    for (int i = 0; i < n; ++i)
    {
        plaintext += decryptChar(ciphertext[i], fib[i]);
    }
    return plaintext;
}

int main()
{
    srand(time(0)); // Seed the random number generator

    // Use a wider range for seeds initially, then fibonacci generation will take %26
    int seed1 = rand() % 255 + 1; // Example range, can be anything
    int seed2 = rand() % 255 + 1; // Example range, can be anything

    string text;
    cout << "Enter plaintext (can include letters, numbers, spaces, special characters): ";
    getline(cin, text);

    if (text.empty())
    {
        cout << "Plaintext is empty. Nothing to encrypt." << endl;
        return 0;
    }

    cout << "\nRandomly generated keys:" << endl;
    cout << "key1: " << seed1 << "\nkey2: " << seed2 << endl;

    string encrypted = encrypt(text, seed1, seed2);
    cout << "\nEncrypted: " << encrypted << endl;

    string decrypted = decrypt(encrypted, seed1, seed2);
    cout << "Decrypted: " << decrypted << endl;


    return 0;
}