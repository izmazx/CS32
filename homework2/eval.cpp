//
//  eval.cpp
//  homework2
//
//  Created by Izma Zuberi on 4/25/22.
//


#include <string>
#include <stack>
using namespace std;

int precedence(char s);

int precedence(char s)
{
    switch (s)
    {
        case '!':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
        default:
            return 0;
    }
}



int evaluate(string infix, string& postfix, bool& result);

int evaluate(string infix, string& postfix, bool& result)
{
    //infix to postfix conversion
    postfix = "";
    stack<char> solve;
    
    //get rid of spaces
    string deletespaces = "";
    for(int i = 0; i < infix.size(); i++)
    {
        if(infix.at(i) == ' ')
        {
            continue;
        }
        deletespaces += infix.at(i);
    }
    infix = deletespaces;
    
    //error checking at empty string, beg, end
    if (infix == "")
        return 1;
    if (infix.at(0) == '&' || infix.at(0) == '|' || infix.at(0) == ')')
        return 1;
    if (infix.at(infix.size() - 1) == '&' || infix.at(infix.size() - 1) == '|' || infix.at(infix.size() - 1) == '(' || infix.at(infix.size() - 1) == '!')
        return 1;
    

    for(size_t pos = 0; pos < infix.size(); pos++)
    {
        char c = infix.at(pos);
        switch (c)
        {
            case 'T':
            case 'F':
                if (pos + 1 < infix.size()) //error checking
                {
                    switch(infix.at(pos + 1))
                    {
                        case 'T':
                        case 'F':
                        case '(':
                        case '!':
                            return 1;
                        default:
                            break;
                    }
                }
                postfix += c;
                break;
            case '!':
            case '(':
                if (pos + 1 < infix.size()) //error checking
                {
                    switch(infix.at(pos + 1))
                    {
                        case ')':
                        case '&':
                        case '|':
                            return 1;
                        default:
                            break;
                    }
                }
                solve.push(c);
                break;
            case ')':
                if (pos + 1 < infix.size()) //error checking
                {
                    switch(infix.at(pos + 1))
                    {
                        case 'T':
                        case 'F':
                        case '(':
                            return 1;
                        default:
                            break;
                    }
                }
                while(solve.top() != '(')
                {
                    postfix += solve.top();
                    solve.pop();
                }
                solve.pop();
                break;
            case '|':
            case '&':
                if (pos + 1 < infix.size()) //error checking
                {
                    switch(infix.at(pos + 1))
                    {
                        case ')':
                        case '&':
                        case '|':
                            return 1;
                        default:
                            break;
                    }
                }
                while(!solve.empty() && solve.top() != '(' && precedence(c) <= precedence(solve.top()))
                {
                    postfix += solve.top();
                    solve.pop();
                    
                }
                solve.push(c);
                break;
            default:
                return 1;
        }
        
    }
    
    while(solve.size() != 0)
    {
        if(solve.top() == '(' || solve.top() == ')') //error checking
        {
            return 1;
        }
        postfix += solve.top();
        solve.pop();
    }
    
    
    //evaluation
    stack <bool> operate;
    for(size_t pos = 0; pos < postfix.size(); pos++)
    {
        char d = postfix.at(pos);
        if (d == 'T')
            operate.push(true);
        else if (d == 'F')
            operate.push(false);
        else if (d == '&' || d == '|')
        {
            bool oper1 = operate.top();
            operate.pop();
            bool oper2 = operate.top();
            operate.pop();
            if (d == '&')
                operate.push(oper1 && oper2);
            if (d == '|')
                operate.push(oper1 || oper2);
        }
        else if (d == '!')
        {
            bool top = operate.top();
            operate.pop();
            operate.push(!top);
        }
    }
    
    result = operate.top();
    return 0;
}



