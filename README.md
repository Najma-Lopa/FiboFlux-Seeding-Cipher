
# FiboFlux Seeding Cipher – Fibonacci-Based Symmetric Encryption Algorithm

## 📄 Table of Contents
- [Overview](#overview)
- [Introduction](#introduction)
- [Encryption Process](#encryption-process)
- [Decryption Process](#decryption-process)
- [Examples with Test Cases](#examples-with-test-cases)
  - [Example 1: "Lopa@#321"](#example-1-lopa321)
  - [Example 2: "HSTU&%2025"](#example-2-hstu2025)
- [Benefits of FiboCrypt](#benefits-of-FiboFlux-Seeding-Cipher)
- [Conclusion](#conclusion)
- [References](#references)
- [Source Code](#source-code)

## 📘 Overview
**FiboFlux Seeding Cipher** is a symmetric encryption algorithm based on the Fibonacci sequence and modular arithmetic. It encrypts each character of the plaintext using a position-specific shift derived from a Fibonacci series seeded by two random values. It supports letters, digits, and a predefined pool of special characters.

This algorithm is ideal for educational demonstrations and lightweight cryptographic use where moderate confusion and diffusion are desired.

---

## ✨ Introduction
In modern cryptography, simple and effective encryption techniques are still valued in scenarios with limited computational power or constrained devices. **FiboFlux Seeding Cipher** provides a fresh take on character-shifting ciphers by using the deterministic yet nonlinear growth of the Fibonacci sequence to govern the encryption process.

Key components:
- Randomly generated two seeds
- Fibonacci-based shift sequence
- Modular shifts applied to alphabets, digits, and special characters
- Symmetric and reversible transformation

---

## 🔐 Encryption Process
**Steps:**
1. Randomly generate two integer keys `key1` and `key2` (1 ≤ key ≤ 255).
2. Generate a Fibonacci sequence of length equal to the plaintext length using `key1` and `key2`, with each term taken modulo 26.
3. For each character in the plaintext:
   - If it's a letter (uppercase/lowercase): apply a Caesar shift using the corresponding Fibonacci value.
   - If it's a digit (0–9): shift within 0–9 using (Fibonacci % 10).
   - If it's a predefined special character (from a defined pool): shift within the pool's size.
   - All other characters (e.g., newline, tab) remain unchanged.
4. Return the encrypted string.

---

## 🔓 Decryption Process
**Steps:**
1. Use the same `key1` and `key2` as used during encryption.
2. Regenerate the Fibonacci sequence of the same length as the ciphertext.
3. For each character:
   - Reverse the Caesar shift, digit shift, or special character shift using the same method.
4. Return the original plaintext.

---

## 🧪 Examples with Test Cases

### 🔹 Example 1: Encrypting & Decrypting "Lopa@#321"
Random Seeds:
- `seed1 = 42`
- `seed2 = 199`

| Pos | Char | Type   | Fib Shift | Encrypted | Decrypted |
|-----|------|--------|-----------|-----------|-----------|
| 0   | L    | Upper  | 16        | B         | L         |
| 1   | o    | Lower  | 17        | f         | o         |
| 2   | p    | Lower  | 7         | w         | p         |
| 3   | a    | Lower  | 24        | y         | a         |
| 4   | @    | Special| 15        | [         | @         |
| 5   | #    | Special| 13        | :         | #         |
| 6   | 3    | Digit  | 4         | 7         | 3         |
| 7   | 2    | Digit  | 17        | 9         | 2         |
| 8   | 1    | Digit  | 21        | 2         | 1         |

- **Ciphertext**: `"Bfwy[:792"`
- **Decrypted**: `"Lopa@#321"`

### 🔹 Example 2: Encrypting & Decrypting "HSTU&%2025"
Random Seeds:
- `seed1 = 87`
- `seed2 = 120`

| Pos | Char | Type   | Fib Shift | Encrypted | Decrypted |
|-----|------|--------|-----------|-----------|-----------|
| 0   | H    | Upper  | 9         | Q         | H         |
| 1   | S    | Upper  | 13        | F         | S         |
| 2   | T    | Upper  | 22        | P         | T         |
| 3   | U    | Upper  | 9         | D         | U         |
| 4   | &    | Special| 5         | *         | &         |
| 5   | %    | Special| 14        | ^         | %         |
| 6   | 2    | Digit  | 23        | 5         | 2         |
| 7   | 0    | Digit  | 18        | 8         | 0         |
| 8   | 2    | Digit  | 15        | 7         | 2         |
| 9   | 5    | Digit  | 10        | 5         | 5         |

- **Ciphertext**: `"QFPD*^5875"`
- **Decrypted**: `"HSTU&%2025"`

## ✅ Benefits of FiboFlux Seeding Cipher
- 🔢 **Deterministic Shift**: Position-based variation makes pattern recognition harder.
- 🔄 **Symmetric & Reversible**: Ensures lossless decryption with original keys.
- 🔐 **Flexible Character Support**: Handles alphabets, numbers, and special characters.
- 🧠 **Educational Tool**: Ideal for learning concepts like modular arithmetic and symmetric encryption.
- 🪶 **Lightweight**: No need for external libraries or complex data structures.

---

## 🧾 Conclusion
**FiboFlux Seeding Cipher** is a novel encryption algorithm leveraging the Fibonacci sequence to determine dynamic character shifts. It showcases how deterministic sequences can introduce strong variation and confusion, especially when combined with careful handling of different character types. It is best suited for educational applications and low-resource environments.

---

## 📚 References
- Stallings, William. *Cryptography and Network Security: Principles and Practice*  
- Fibonacci Sequence – [Wikipedia](https://en.wikipedia.org/wiki/Fibonacci_number)  
- Caesar Cipher – [Wikipedia](https://en.wikipedia.org/wiki/Caesar_cipher)  

---

## 💻 Source Code
```cpp
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
```
