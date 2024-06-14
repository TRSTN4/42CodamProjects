#include "MutantStack.hpp"

#include <cassert>

int subject_test() {
    std::cout << "--- Subject test ---\n";

    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << mstack.top() << std::endl;

    mstack.pop();
    
    std::cout << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    //[...]
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);
    return 0;
}

int subject_list_test() {
    std::cout << "\n--- Subject list test ---\n";
    
    std::list<int> lst;

    lst.push_back(5);
    lst.push_back(17);

    std::cout << lst.back() << std::endl;

    lst.pop_back();
    std::cout << lst.size() << std::endl;

    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    //[...]
    lst.push_back(0);

    std::list<int>::iterator it = lst.begin();
    std::list<int>::iterator ite = lst.end();
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::list<int> l(lst);
    return 0;
}

void my_tests() {
    std::cout << "\n--- My test ---\n";
    
    MutantStack<int> mstack;

    std::cout << "My stack after pushing:\n";
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);
    for (auto it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << " ";

    std::cout << "\n\nMy stack's top element:\n" << mstack.top() << "\n";

    std::cout << "\nMy stack after popping top element:\n";
    mstack.pop();
    for (auto it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << " ";

    std::cout << "\n\nSize of the stack:\n" << mstack.size();

    std::cout << "\n\nCopy constructor:\n";
    MutantStack<int> copy_stack(mstack);
    for (auto it = copy_stack.begin(); it != copy_stack.end(); ++it)
        std::cout << *it << " ";

    std::cout << "\n\nOriginal stack after copy_stack push:\n";
    for (auto it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << " ";

    std::cout << "\n\nAssignment operator:\n";
    MutantStack<int> assign_stack;
    assign_stack.push(1);
    assign_stack.push(2);
    assign_stack = mstack;
    for (auto it = assign_stack.begin(); it != assign_stack.end(); ++it)
        std::cout << *it << " ";

    std::cout << "\n\nMy stack as list-based stack:\n";
    MutantStack<int, std::list<int>> list_stack;
    list_stack.push(1);
    list_stack.push(2);
    list_stack.push(3);
    for (auto it = list_stack.begin(); it != list_stack.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
}

int main()
{
    subject_test();
    subject_list_test();
    my_tests();
}
