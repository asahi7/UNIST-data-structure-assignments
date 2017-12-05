
#ifndef CALCULATOR_H
#define CALCULATOR_H

//
// Simple calculator using Stack
//
// Assignment 2 CSE221 Fall 2016
//
// Won-Ki Jeong (wkjeong@unist.ac.kr)
//
#include <iostream>
#include <math.h>
#include <string.h>
#include "stack.h"

Stack<double> opr; // stack for operands
Stack<char> opt;   // stack for operators

//
// Modify Eval() below to evaluate the given expression
//
double Eval(char* in)
{
	double out = 0;
	
	char buf[1000]; // temp buffer
	char lastToken = '#';
	
	double operand;
	int i = 0, bi = 0;
	
	opt.Push('#');
		
	while(in[i] != '\0')
	{		
		char c = in[i];
		
		// Operators
		if(c == '+' || c == '-' ||
		   c == '*' || c == '/' ||
		   c == '(' || c == ')')
		{
			if(bi > 0)
			{
				buf[bi++] = NULL;
				operand = atof(buf);				
				bi = 0;
				
				// push operand
				std::cout << "New operand : " << operand << std::endl;
				opr.Push(operand);
			}

			// push operator
			std::cout << "New operator : " << c << std::endl;
			opt.Push(c);
		}
		// Operands
		else if(c == '0' || c == '1' ||
				c == '2' || c == '3' ||
				c == '4' || c == '5' ||
				c == '6' || c == '7' ||
				c == '8' || c == '9' ||
				c == '.')
		{
			buf[bi++] = c;
		}
		else {}
	
		i++;
	}
	
	// push the very last operand if exists
	if(bi > 0)
	{
		buf[bi++] = NULL;
		operand = atof(buf);
		bi = 0;
		
		// push operand
		std::cout << "New operand : " << operand << std::endl;
		opr.Push(operand);
	}
		
	return out;	
}

#endif
