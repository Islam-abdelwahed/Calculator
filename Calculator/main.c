
#include "Buzzer.h"
#include "STD.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "Calculator.h"
#include "Stack.h"
#include <ctype.h>
#include <stdlib.h>

void evaluate(char* expresion){
	
	char  buffer[15];
	sint32 i, op1, op2, len, j, x;
	 
	
	len=sizeof(expresion)/sizeof(expresion[0]);

	j = 0;
	for (i = 0; i < len; i++) {

		if (expresion[i] >= '0' && expresion[i] <= '9') {
			buffer[j++] = expresion[i];
		}
		else if (expresion[i] == ' ') {
			if (j > 0) {
				buffer[j] = '\0';
				x = atoi(buffer);
				push(x);
				j = 0;
			}
		}

		else if (isOperator(expresion[i])) {
			op1 = getTop();
			pop();
			op2 = getTop();
			pop();
			push(performOperation(op1, op2, expresion[i]));
		}
	}
	//cout<<"Answer = "<<getTop();
	LCD_WRITE_INTEGER(getTop());

}

int main(void)
{

	BUZZER_Init();
	BUZZER_BEEP_BEEP();
	LCD_INIT();
	
	int index = 0;
	char expression[30]={0};

	while (1)
	{
		uint8 KeyPressed = keypadGetValue();
		if(!KeyPressed )
		{
			switch(KeyPressed)
			{
				case 'c':
				{
					
					LCD_CLR();
					index = 0;
					
					break;
				}
				case '=':
								{
									//evaluate(expression);
									index = 0;
									
									break;
								}
				default:
				
				{
					if(expression[0]=='\0')
					LCD_CLR();
					
					expression[index]=KeyPressed;
					LCD_WRITE_CHAR(KeyPressed);
					index++;
					
					break;
				}
			}
			expression[index]='\0';
		}
	}
}

