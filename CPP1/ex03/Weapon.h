#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
    private:
        std::string type;

    public:
        Weapon(const std::string type);
        const std::string& getType() const;
        void setType(const std::string type);
};

#endif
