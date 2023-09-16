#include "Calculator.h"

/*
  Infix to postfix conversion in C++
  Input Postfix expression must be in a desired format.
  Operands and operator, both must be single character.
  Only '+'  ,  '-'  , '*', '/' and '$' (for exponentiation)  operators are expected.
*/




// Function to evaluate Postfix expression and return output
char* InfixgetTopostfix(char* expression)
{
	// Declaring a Stack from Standard template library in C++. 
	
	uint8 len=sizeof(expression)/sizeof(expression[0]);
	
	char* postfix = ""; // Initialize postfix as empty string.
	for ( uint8 i = 0; i < len; i++) {

		// Scanning each character from left. 
		// If character is a delimitter, move on. 
		
		if (expression[i] == ' ' || expression[i] == ',') continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back. 
		else if (IsOperator(expression[i]))
		{
			while (!empty() && getTop() != '(' && HasHigherPrecedence(getTop(), expression[i]))
			{
				postfix += getTop();
				pop();
			}
			push(expression[i]);
		}
		// Else if character is an operand
		else if (IsOperand(expression[i]))
		{
			postfix += expression[i];
		}

		else if (expression[i] == '(')
		{
			push(expression[i]);
		}

		else if (expression[i] == ')')
		{
			while (!empty() && getTop() != '(') {
				postfix += getTop();
				pop();
			}
			pop();
		}
	}

	while (!empty()) {
		postfix += getTop();
		pop();
	}

	return postfix;
}

// Function to verify whether a character is english letter or numeric digit. 
// We are assuming in this solution that operand will be a single character
uint8 IsOperand(char C)
{
	if (C >= '0' && C <= '9') return 1;
	if (C >= 'a' && C <= 'z') return 1;
	if (C >= 'A' && C <= 'Z') return 1;
	return 0;
}

// Function to verify whether a character is operator symbol or not. 
uint8 IsOperator(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$')
		return 1;

	return 0;
}

// Function to verify whether an operator is right associative or not. 
uint8 IsRightAssociative(char op)
{
	if (op == '$') return 1;
	return 0;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence. 
uint8 GegetToperatorWeight(char op)
{
	uint8 weight = -1;
	switch (op)
	{
	case '+':
	case '-':
		weight = 1;
		break;
	case '*':
	case '/':
		weight = 2;
		break;
	case '$':
		weight = 3;
		break;
	}
	return weight;
}

// Function to perform an operation and return output. 
uint8 HasHigherPrecedence(char op1, char op2)
{
	uint8 op1Weight = GegetToperatorWeight(op1);
	uint8 op2Weight = GegetToperatorWeight(op2);

	// If operators have equal precedence, return 1 if they are left associative. 
	// return 0, if right associative. 
	// if operator is left-associative, left one should be given priority. 
	if (op1Weight == op2Weight)
	{
		if (IsRightAssociative(op1)) return 0;
		else return 1;
	}
	return op1Weight > op2Weight ? 1 : 0;
}


uint8 isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
	return 1;
	else
	return 0;
}

uint8 performOperation(uint8 op1, uint8 op2, char op)
{
	uint8 ans;
	switch (op) {
		case '+':
		ans = op2 + op1;
		break;
		case '-':
		ans = op2 - op1;
		break;
		case '*':
		ans = op2 * op1;
		break;
		case '/':
		ans = op2 / op1;
		break;
	}
	return ans;
}
