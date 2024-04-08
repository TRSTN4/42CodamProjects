#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "Contact.h"
#include <iostream>

class PhoneBook {
private:
    Contact contacts[8];
    int contactCount;
	int nextContactIndex;
    std::string getInput(const std::string& prompt) const;
    std::string trim(const std::string& str) const;
    std::string truncateString(const std::string& str) const;

public:
    PhoneBook();
    void addContact();
    void searchContacts() const;
    void displayContactDetails(int index) const;
};

#endif 
