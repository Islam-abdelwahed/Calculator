

#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#include "STD.h"
#include "Stack.h"

// Function to convert Infix expression to postfix
char* InfixToPostfix(char* expression);

// Function to verify whether an operator has higher precedence over other
uint8 HasHigherPrecedence(char operator1, char operator2);

// Function to verify whether a character is operator symbol or not.
uint8 IsOperator(char C);

// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not.
uint8 IsOperand(char C);

uint8 GegetToperatorWeight(char op);

uint8 performOperation(uint8 op1, uint8 op2, char op);

uint8 IsRightAssociative(char op);

#endif /* CALCULATOR_H_ */