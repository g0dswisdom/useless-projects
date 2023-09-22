// Password Generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <string>

std::string generatePassword(int length, bool addSymbols) {
    std::string password;
    std::string symbols = "~`!@#$%^&*()_+-=][|}{,.;:";
    std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (addSymbols) {
        letters += symbols;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < length; ++i) {
        int random = std::rand() % letters.length();
        password += letters[random];
    }

    return password;
}

int main()
{
    int length;
    bool addSymbols;
    std::cout << "------- PASSWORD GENERATOR -------\nPassword length: ";
    std::cin >> length;
    std::cout << "Add symbols (true/false): ";
    std::cin >> addSymbols;
    std::cout << generatePassword(length, addSymbols);
}

