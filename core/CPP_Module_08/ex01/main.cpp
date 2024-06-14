#include "Span.hpp"

void subject_test() {
    std::cout << "--- Subject test ---\n";

    Span sp = Span(5);

    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
}

void hunderedK_test() {
    std::cout << "\n--- 100k test ---\n";

    try {
        std::list<int> list;
        for (int i = 0; i < 100000; ++i)
            list.push_back(i);
        
        Span span(100000);
        span.addNumber(list.begin(), list.end());

    std::cout << "Shortest Span: " << span.shortestSpan() << "\n";
    std::cout << "Longest Span: " << span.longestSpan() << "\n";
    } catch (std::exception &e) {
        std::cout << e.what() << "\n"; 
    }
}

void edge_case_tests() {
    std::cout << "\n--- Duplicate test ---\n";
    try {
        Span span = Span(4);
        span.addNumber(6);
        span.addNumber(6);
        span.addNumber(6);
        span.addNumber(6);
        std::cout << "Shortest Span: " << span.shortestSpan() << "\n";
        std::cout << "Longest Span: " << span.longestSpan() << "\n";
    } catch (std::exception &e) {
        std::cout << e.what() << "\n"; 
    }

    std::cout << "\n--- Empty ---\n";
    try {
        Span span = Span(0);
        std::cout << "Shortest Span: " << span.shortestSpan() << "\n";
        std::cout << "Longest Span: " << span.longestSpan() << "\n";
    } catch (std::exception &e) {
        std::cout << e.what() << "\n"; 
    }

    std::cout << "\n--- Single Element ---\n";
    try {
        Span span = Span(1);
        span.addNumber(42);
        std::cout << "Shortest Span: " << span.shortestSpan() << "\n";
        std::cout << "Longest Span: " << span.longestSpan() << "\n";
    } catch (std::exception &e) {
        std::cout << e.what() << "\n"; 
    }

    std::cout << "\n--- Regular Test ---\n";
    try {
        Span span = Span(2);
        span.addNumber(42);
        span.addNumber(84);
        std::cout << "Shortest Span: " << span.shortestSpan() << "\n";
        std::cout << "Longest Span: " << span.longestSpan() << "\n";
    } catch (std::exception &e) {
        std::cout << e.what() << "\n"; 
    }

    std::cout << "\n--- Large Numbers ---\n";
    try {
        Span span = Span(3);
        span.addNumber(100000000);
        span.addNumber(200000000);
        span.addNumber(300000000);
        std::cout << "Shortest Span: " << span.shortestSpan() << "\n";
        std::cout << "Longest Span: " << span.longestSpan() << "\n";
    } catch (std::exception &e) {
        std::cout << e.what() << "\n"; 
    }

    std::cout << "\n--- Negative Numbers ---\n";
    try {
        Span span = Span(3);
        span.addNumber(-10);
        span.addNumber(-20);
        span.addNumber(-30);
        std::cout << "Shortest Span: " << span.shortestSpan() << "\n";
        std::cout << "Longest Span: " << span.longestSpan() << "\n";
    } catch (std::exception &e) {
        std::cout << e.what() << "\n"; 
    }

    std::cout << "\n--- Mixed Numbers ---\n";
    try {
        Span span = Span(3);
        span.addNumber(-10);
        span.addNumber(20);
        span.addNumber(-30);
        std::cout << "Shortest Span: " << span.shortestSpan() << "\n";
        std::cout << "Longest Span: " << span.longestSpan() << "\n";
    } catch (std::exception &e) {
        std::cout << e.what() << "\n"; 
    }
}

int main()
{
    subject_test();
    hunderedK_test();
    edge_case_tests();

    return 0;
}
