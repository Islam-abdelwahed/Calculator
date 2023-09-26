#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 80

// Function to evaluate Postfix expression and return output
char* InfixToPostfix(const char* expression);

// Function to verify whether a character is a digit or not.
int IsOperand(char C);

// Function to verify whether a character is an operator symbol or not.
int IsOperator(char C);

// Function to verify whether an operator is right associative or not.
int IsRightAssociative(char op);

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int GetOperatorWeight(char op);

// Function to perform an operation and return the result.
int HasHigherPrecedence(char op1, char op2);

char* InfixToPostfix(const char* expression)
{
	char* postfix = malloc(MAX_SIZE * sizeof(char));
	int len = strlen(expression);
	int x = 0;

	// Stack to store operators
	char stack[MAX_SIZE];
	int top = -1;

	for (int i = 0; i < len; i++) {
		if (expression[i] == ' ' || expression[i] == ',') {
			postfix[x++] =' ';
		}
		else if (IsOperator(expression[i])) {
			while (top != -1 && stack[top] != '(' && HasHigherPrecedence(stack[top], expression[i])) {
				postfix[x++] = stack[top--];
			}
			stack[++top] = expression[i];
		}
		else if (IsOperand(expression[i])) {
			postfix[x++] = expression[i];
		}
		else if (expression[i] == '(') {
			stack[++top] = expression[i];
		}
		else if (expression[i] == ')') {
			while (top != -1 && stack[top] != '(') {
				postfix[x++] = stack[top--];
			}
			top--; // Discard '(' from the stack
		}
	}

	while (top != -1) {
		postfix[x++] = stack[top--];
	}

	postfix[x] = '\0'; // Add null terminator to the postfix expression
	return postfix;
}

int IsOperand(char C)
{
	return (C >= '0' && C <= '9');
}

int IsOperator(char C)
{
	return (C == '+' || C == '-' || C == '*' || C == '/' || C == '$');
}

int IsRightAssociative(char op)
{
	return (op == '$');
}

int GetOperatorWeight(char op)
{
	int weight = 0;
	switch (op) {
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

int HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	if (op1Weight == op2Weight) {
		if (IsRightAssociative(op1)) {
			return 0;
		}
		else {
			return 1;
		}
	}
	return op1Weight > op2Weight ? 1 : 0;
}