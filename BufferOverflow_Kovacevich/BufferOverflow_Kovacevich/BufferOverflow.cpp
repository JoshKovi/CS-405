// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_order
  //  varaible, and its position in the declaration. It must always be directly before the variable used for input.

  const std::string account_number = "CharlieBrown42";
  std::string user_input; //Changing the data type to a dynamically sized string prevents an overflow from extra characters
  std::cout << "Enter a value: ";
  std::cin >> user_input;

  if (user_input.size() > 20) {
	  //Informs user that input exceeded 20 character intended limit
	  std::cout << "Your input was longer than anticipated...Please try again with a shorter (20 or less) character input.";
  }
  else {
	  //Only with a valid input length ( less than 21 characters) will the intended output be displayed.
	  std::cout << "You entered: " << user_input.c_str() << std::endl;
	  std::cout << "Account Number = " << account_number << std::endl;
  }


  //While I could use a stream to load to the character array it makes little sense to as it convuulutes the code,
  //while providing no tangible benefit in almost any case. I attempted to find a way to buffer overflow the std::string
  //but the only method I could come up with was by writing a string so long that it consumed all available memory, which seems
  //infeasible, unpredictable, and unlikely to result in successful execution of arbitrary code as memory allocation on a modern
  //system drastically changes second by second.
  
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
