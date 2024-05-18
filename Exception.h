s

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

class illegal_argument : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Illegal argument exception";
    }
};

class underflow : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Underflow exception";
    }
};

#endif
