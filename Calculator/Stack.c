#include "Stack.h"



sint32 inp_array[SIZE]={};
sint32 top = -1;

void push(sint32 c)
{

	if (top == SIZE - 1)
	{
		
	}
	else
	{
		top++;
		inp_array[top] = c;
	}
}

void pop()
{
	if (top == -1)
	{
		
	}
	else
	{
		
		top --;
	}
}

sint32 getTop(){
			
	if (top == -1)
	{
		
	}
	else
	{
		return inp_array[top];
	}
}
	
uint8 empty(){
	
	return (top==-1) ? 1 : 0;
	};