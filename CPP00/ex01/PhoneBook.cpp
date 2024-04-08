#include "PhoneBook.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

PhoneBook::PhoneBook() : contactCount(0), nextContactIndex(0) {}

std::string PhoneBook::getInput(const std::string& prompt) const {
    std::string input, trimmed;
    while (trimmed.empty()) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (std::cin.fail())
            std::exit(0);
        trimmed = trim(input);
        if (trimmed.empty())
            std::cout << "Empty field detected. Please try again.\n";
    }
    return trimmed;
}

std::string PhoneBook::trim(const std::string& str) const {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

void PhoneBook::addContact() {
    Contact newContact;

    std::cout << "------ Adding New Contact ------\n";

    newContact.setFirstName(getInput("Enter first name: "));
    newContact.setLastName(getInput("Enter last name: "));
    newContact.setNickname(getInput("Enter nickname: "));
    newContact.setPhoneNumber(getInput("Enter phone number: "));
    newContact.setDarkestSecret(getInput("Enter darkest secret: "));

    contacts[nextContactIndex] = newContact;
    nextContactIndex++;

    if (nextContactIndex >= 8)
        nextContactIndex = 0;
    if (contactCount < 8)
        contactCount++;
    
    std::cout << "--------------------------------\n";
}

void PhoneBook::searchContacts() const {
    if (contactCount == 0)
    {
        std::cout << "No contacts added, aborting search.\n";
        return;
    }
    
    std::cout << "---------------------------------------------\n";
    std::cout << "|" << std::setw(10) << "Index"
              << "|" << std::setw(10) << "First Name"
              << "|" << std::setw(10) << "Last Name"
              << "|" << std::setw(10) << "Nickname"
              << "|" << std::endl;
    std::cout << "---------------------------------------------\n";

    for (int i = 0; i < contactCount; ++i) {
        std::cout << "|" << std::setw(10) << i
                  << "|" << std::setw(10) << truncateString(contacts[i].getFirstName())
                  << "|" << std::setw(10) << truncateString(contacts[i].getLastName())
                  << "|" << std::setw(10) << truncateString(contacts[i].getNickname())
                  << "|" << std::endl;
    }
    std::cout << "---------------------------------------------\n";

   while (true) {
        std::cout << "Enter the index of the contact to display: ";
        std::string input;
        std::getline(std::cin, input);
        if (std::cin.fail())
            std::exit(0);
        std::stringstream ss(input);
        int index;
        if (ss >> index && !(ss >> input)) {
            if (index >= 0 && index < contactCount) {
                displayContactDetails(index);
                break;
            }
        }
        std::cout << "Invalid index. Please try again.\n";
    }
}

void PhoneBook::displayContactDetails(int index) const {
    const Contact& contact = contacts[index];
    std::cout << "---------------------------------------------\n";
    std::cout << "| First Name: " << contact.getFirstName() << std::endl;
    std::cout << "| Last Name: " << contact.getLastName() << std::endl;
    std::cout << "| Nickname: " << contact.getNickname() << std::endl;
    std::cout << "| Phone Number: " << contact.getPhoneNumber() << std::endl;
    std::cout << "| Darkest Secret: " << contact.getDarkestSecret() << std::endl;
    std::cout << "---------------------------------------------\n";
}

std::string PhoneBook::truncateString(const std::string& str) const {
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}
