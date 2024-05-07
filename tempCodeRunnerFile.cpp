


    stack.push(0, 10); // Push 10 to stack 0
    stack.push(1, 11); // Push 20 to stack 1
    stack.push(0, 20); // Push 10 to stack 0
    stack.push(1, 12); // Push 20 to stack 1
    stack.push(0, 30); // Push 10 to stack 0
    stack.push(1, 13); // Push 20 to stack 1
    stack.pop(0);      // Pop
    stack.pop(0);      // Pop
    stack.pop(0);      // Pop

    std::cout << "Stack capacity: " << stack.capacity() << std::endl;
    std::cout << "Stack 0 size: " << stack.size(0) << std::endl;
    std::cout << "Stack 1 size: " << stack.size(1) << std::endl;
    // std::cout << "Top of stack 0: " << stack.top(0) << std::endl;
    std::cout << "Top of stack 1: " << stack.top(1) << std::endl;

    // Check if the first stack is empty
    bool isStackEmpty = stack.empty(0);
    std::cout << "Is the first stack empty? " << (isStackEmpty ? "Yes" : "No") << std::endl;

    // Check if the second stack is empty
    isStackEmpty = stack.empty(1);
    std::cout << "Is the second stack empty? " << (isStackEmpty ? "Yes" : "No") << std::endl;
    
