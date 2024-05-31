#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    std::cout << "--- valid init ---\n";
    Bureaucrat bureaucrat1("Bureaucrat1", 50);
    Form form1("Form1", 40, 30);
    std::cout << bureaucrat1 << "\n";
    std::cout << form1 << "\n";

    std::cout << "--- valid sign ---\n";
    Bureaucrat bureaucrat2("Bureaucrat2", 30);
    Form form2("Form2", 40, 30);
    std::cout << bureaucrat2 << "\n";
    bureaucrat2.signForm(form2);
    std::cout << form2 << "\n";

    std::cout << "--- too low grade to sign ---\n";
    try {
        Bureaucrat bureaucrat3("Bureaucrat3", 50);
        Form form3("Form3", 40, 30);
        std::cout << bureaucrat3 << "\n";
        bureaucrat3.signForm(form3);
    } catch (const std::exception &e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "--- form not signed ---\n";
    try {
        Bureaucrat bureaucrat4("Bureaucrat4", 5);
        Form form4("Form4", 10, 5);
        std::cout << bureaucrat4 << "\n";
        form4.beSigned(bureaucrat4);
        std::cout << form4 << "\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "--- copy ---\n";
    Form form5(form1);
    std::cout << form5 << "\n";

    std::cout << "--- copy assignment ---\n";
    Form form6("Form6", 50, 50);
    form6 = form1;
    std::cout << form6 << "\n";

    return 0;
}
