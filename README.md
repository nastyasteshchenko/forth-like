# HOW TO RUN:  
> cmake .  
> make  
> ./forth  

# LAB2 FORTH-LIKE INTERPRETER  

Write a language interpreter that supports some of the functionality of the Forth language

**Description of the language. Basic version (15 points)**

***Numbers***

Only integers are supported, the boundaries of the number coincide with the boundaries of the int type in C++ on your platform

When a number is fed to the interpreter, the number is put on the stack:  
> 3
< ok

***Arithmetic operations***

Supported operations: * / + - mod

All these operations take the top of the stack as the right operand, and the second number on the glass as the left, calculate the result and put it on the stack. If there are not enough numbers on the stack or if the operation is illegal, then an appropriate exception should be thrown and an error printed (numbers are removed from the stack)  

***Built-in commands***

**dup** -copy the top of the stack and put it on the stack  
**drop** - remove the top number from the stack  
**.** - print the top number on the stack, remove it from the stack  
**swap** - swap the top and second numbers on the stack  
**rot** - cyclically shift the top three numbers.
for example, the stack before: 4 1 2 3, the stack after: 4 3 1 2  
**over** - copy the second number and put a copy above the top one.
for example, stack before: 3 2 1, stack after: 3 2 1 2  
**emit** - print the top number on the stack as an ascii code and remove it from the stack.
for example, 65 emit will print A  
**cr** is a line break. for example, 100 200 . cr . will print 200\n100


***Logical operations***

Supported operations: > < =

All these operations take the top of the stack as the right operand, and the second number on the stack as the left, calculate the result and put it on the stack. If there are not enough numbers on the stack or if the operation is illegal, then an appropriate exception should be thrown and an error printed (the numbers are removed from the stack).
The result of the operation: 0 if the result of the operation is false; 1 if true  

***Printing lines***

The view command ."STRING_CONTENT" prints the specified string (without quotes).

**Description of the language. Advanced version (+ 5 points)**

***Conditional operator***

Two formats are supported:

1)  if THEN_BRANCH then ;
If there is 0 on the stack, then nothing happens, if any other number, then THEN_BRANCH is executed.A semicolon after the command is required
2)  if THEN_BRANCH else ELSE_BRANCH then ;
If 0 is on the stack, then ELSE_BRANCH is executed, if any other number, then THEN_BRANCH is executed. A semicolon after the command is required

**Requirements**

*  The code should be covered with tests https://github.com/google/googletest
*  Public methods should be documented (in English)
*  The program should be built using cmake
*  There should be no memory leaks in the program
*  Command instances should be wrapped in smart pointers
*  Custom exceptions must be defined in the program
*  It is recommended to use standard collections (std::map, std::stack...)
