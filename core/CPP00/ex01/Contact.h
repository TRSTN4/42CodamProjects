#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>

class Contact {
private:
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;

public:
    Contact();
    void setFirstName(const std::string& fname);
    void setLastName(const std::string& lname);
    void setNickname(const std::string& nname);
    void setPhoneNumber(const std::string& pnumber);
    void setDarkestSecret(const std::string& secret);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getNickname() const;
    std::string getPhoneNumber() const;
    std::string getDarkestSecret() const;
};

#endif
