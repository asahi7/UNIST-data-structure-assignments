
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

bool ifNumber(char c){
    return ((c >= '0' && c <= '9') || c == '.');
}

bool ifOperator(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}

char* remove_spaces(char* in){
    char* res = new char[10000];
    int resl = 0;
    for(int i = 0; in[i] != '\0'; i++){
        if(in[i] == ' ') continue;
        res[resl++] = in[i];
    }
    res[resl++] = '\0';
    return res;
}

std::string* convertToPostFix(char* in){
    in = remove_spaces(in);
    std::string* output = new std::string[10000];
    char buffer[1000];
    int bi = 0, ol = 0;
    Stack<char> opt;
    int precedence[200];
    precedence[(int)'*'] = 3;
    precedence[(int)'/'] = 3;
    precedence[(int)'+'] = 2;
    precedence[(int)'-'] = 2;
    precedence[(int)'('] = 1;
    bool sign = 0;
    for(int i = 0; in[i] != '\0'; i++){
        bool numberFound = 0;
        int j = i;
        while(ifNumber(in[j])){
            buffer[bi++] = in[j];
            j++;
            numberFound = 1;
        }       
        if(numberFound == true){
            buffer[bi++] = '\0';
            output[ol] += (sign == '\0' ? "" : "-"); 
            output[ol++] += buffer;
            bi = 0;
            i = j - 1;
            sign = 0;
            continue;
        }

        if(ifOperator(in[i])){
            if(in[i] == ')'){
                while(opt.IsEmpty() == false && opt.Top() != '('){
                    output[ol++] += opt.Top() + '\0';              
                    opt.Pop();
                }
                opt.Pop();
                continue;
            }
            if(in[i] == '-' && ((opt.IsEmpty() == true && i == 0) || (i > 0 && ifOperator(in[i - 1]) == true && in[i - 1] != ')'))){
                sign = 1;
                continue;
            }
            if(in[i] == '('){
                opt.Push(in[i]);
                continue;
            }
            while(opt.IsEmpty() == false && precedence[(int)in[i]] <= precedence[(int)opt.Top()]){
                output[ol++] += opt.Top() + '\0';
                opt.Pop();
            }
            opt.Push(in[i]);
        }
    }

    while(opt.IsEmpty() == false){
        output[ol++] += opt.Top() + '\0';
        opt.Pop();
    }

    output[ol++] = "\0";
    return output;
}

double calculatePostFix(std::string* postfix){
    Stack<double> st;
    for(int i = 0; postfix[i] != "\0"; i++){
        if(ifOperator((char)postfix[i][0]) == true && postfix[i].length() == 1){
            double res = 0;
            double a = st.Top();
            st.Pop();
            double b = st.Top();
            st.Pop();
            if(postfix[i][0] == '+') res = a + b;
            else if(postfix[i][0] == '-') res = b - a;
            else if(postfix[i][0] == '*') res = a * b;
            else if(postfix[i][0] == '/') res = b / a;
            st.Push(res);
        }
        else{
            char* number = new char[20];
            std::strcpy(number, postfix[i].c_str());
            double num = atof(number);
            //std::cout << num << std::endl;
            st.Push(num);
        }
    }
    return st.Top();
}

double Eval(char* in)
{
	double out = 0;
	std::string* postfix = convertToPostFix(in);
    /*for(int i = 0; postfix[i] != "\0"; i++){
        std::cout << postfix[i] << " ";
    }
    std::cout << std::endl;*/
    out = calculatePostFix(postfix);
	return out;	
}

#endif
