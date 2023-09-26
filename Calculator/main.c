#include "Buzzer.h"
#include "STD.h"
#include "LCD.h"
#include "KEYPAD.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 80

int performOperation(int op1, int op2, char op)
{
	volatile	int ans;
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

void evaluate(char* expression)
{
	char* postfix = InfixToPostfix(expression);
	uint8 buffer[15];
	uint16 i, op1, op2, len, j, x,error=0;
	len = strlen(postfix);
	j = 0;

	for (i = 0; i < len; i++) {

		if (postfix[i] >= '0' && postfix[i] <= '9') {
			buffer[j++] = postfix[i];
			push(postfix[i]-'0');
		}
		else if (postfix[i] == ' ') {
			if (j > 0) {
				buffer[j] = '\0';
				x = atoi(buffer);
				push(x);
				j = 0;
			}
		}
		else if (IsOperator(postfix[i])) {
			j = 0;
			op1 = getTop();
			pop();
			op2 = getTop();
			pop();
			if(postfix[i]=='/' && op1==0)
				{
					error=1;
					break;
				}
			push(performOperation(op1, op2, postfix[i]));
		}
	}
	if (error)
	{
		LCD_WRITE_STRING("Error");
	}
	else LCD_WRITE_INTEGER(getTop());
	free(postfix);
}

void start(){
	LOCATE_CURSOR(1, 5);
	LCD_WRITE_STRING("Calculator");
	_delay_ms(2000);
	LCD_CLR();
	BUZZER_SHORT_BEEP();
};

int main(void)
{
	char expression[MAX_SIZE];

	BUZZER_Init();
	BUZZER_BEEP_BEEP();
	LCD_INIT();
	KEYPAD_INIT();

	start();

	int index = 0;

	while (1)
	{
		uint8_t keyPressed = keypadGetValue();
		if (keyPressed != 0)
		{
			BUZZER_SHORT_BEEP();
			switch (keyPressed)
			{
				case 'c':
				if (expression[0] == '\0')
				LCD_CLR();
				else{
					expression[index] = ' ';
					LCD_WRITE_CHAR(' ');
				index++;}
				break;

				case '=':
				if (expression[0] == '\0')
				break;
				LCD_WRITE_CHAR('=');
				evaluate(expression);
				index = 0;
				break;

				default:
				if (expression[0] == '\0')
				LCD_CLR();
				
				expression[index] = keyPressed;
				LCD_WRITE_CHAR(keyPressed);
				index++;
				break;
			}
			expression[index] = '\0';
		}
	}
}