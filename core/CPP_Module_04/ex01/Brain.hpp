#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

class Brain
{
    private:
        std::string ideas[100];
    public:
        Brain();
        ~Brain();
        Brain(const Brain& src);
        Brain& operator=(const Brain& src);

        void setIdea(int index, const std::string& idea);
        std::string getIdea(int index) const;
};
 
#endif
