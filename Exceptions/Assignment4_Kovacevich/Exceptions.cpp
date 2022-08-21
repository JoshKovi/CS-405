// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>


//This is a class for a custom exception derived from standard::exception, very simple
class customException : public std::exception {

public:
    
    const char* what() {
        //Returns this message for exception's what fuunction call
        return "Custom derived exception";
        
    }
};


bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    //Here I will throw an out_of_range exception
    throw std::out_of_range("Out of Range Error occured in do_even_more_custom_application_logic");

    return true;
}
void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch(std::exception e){
        std::cout << "do_even_more_custom_application_logic failed to execute." << std::endl <<  "Exception: " << e.what() << std::endl;
    }

    

    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main


    std::cout << "Leaving Custom Application Logic." << std::endl;

    //Here I throw a custom exception defined above.
    throw customException();

}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    if (den == 0) {
        //throws invalid arguement exception when attempting to divide by 0
        throw std::invalid_argument("Bad Denominator: Can not divide by 0.");
    }
    return (num / den);
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl; //This is here due to auto result being initialized here.
        //If cout statement is outside of try the program will not compile.
    }
    catch(std::invalid_argument e){
        //Catches the invalid argument exception thrown by the divide function
        std::cout << e.what() << std::endl;
    }
    
    
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // TODO: Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.
    try {
        do_division();
        do_custom_application_logic();
    }
    catch (customException e) {
        std::cout << e.what() << std::endl;
    }
    catch (std::exception e) {
        //Would catch a std:: exception if one was unhandled until the main method
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        //Would notify the user an otherwise unhandled exception was thrown for the user to troubleshoot
        //and allow the program to unwind rather than terminate without doing so.
        std::cout << "Otherwise uncaught exception detected" << std::endl;
    }
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu