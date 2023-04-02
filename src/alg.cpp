// Copyright 2021 NNTU-CS
#include <stack>
#include <string>
#include <algorithm>
#include <iostream>

bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return true;
    return false;
}

int precedence(char ch)
{
    if (ch == '*' || ch == '/')
        return 2;
    if (ch == '+' || ch == '-')
        return 1;
    return 0;
}


std::string infx2pstfx(std::string infix)
{
    std::stack<char> stk;
    std::string postfix;

    for (int i = 0; i < infix.size(); i++)
    {
        if (isOperator(infix[i]))
        {
            postfix.push_back(' ');
            while (!stk.empty() && precedence(stk.top()) >= precedence(infix[i]))
            {
                postfix += stk.top();
                stk.pop();
            }
            stk.push(infix[i]);
        }
        else if (infix[i] == '(')
            stk.push(infix[i]);
        else if (infix[i] == ')')
        {
            while (!stk.empty() && stk.top() != '(')
            {
                //postfix.push_back(' ');
                postfix += stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else
            postfix += infix[i];
    }

    while (!stk.empty())
    {
        postfix += stk.top();
        stk.pop();
    }
    return postfix;
}



std::string evaluate(char op, int operand1, int operand2)
{
    switch (op)
    {
    case '+': return std::to_string(operand1 + operand2);
    case '-': return std::to_string(operand1 - operand2);
    case '*': return std::to_string(operand1 * operand2);
    case '/': return std::to_string(operand1 / operand2);
    }
}

int eval(std::string postfix)
{
    std::stack<std::string> stk;
    std::string pust = " ";
    std::string operand_2;
    std::string operand_1;
    for (int i = 0; i < postfix.size(); i++)
    {
        if (isOperator(postfix[i]))
        {
            if (stk.top() == "0")
            {
                while (!stk.empty() && stk.top() != pust)
                {
                    operand_2 += stk.top();
                    stk.pop();
                }
                std::reverse(operand_2.begin(), operand_2.end());
            }
            else
            {
                while (!stk.empty() && stk.top() != pust)
                {
                    operand_2 += stk.top();
                    stk.pop();
                }
            }
            if (stk.top() == " ")
            {
                stk.pop();

                if (stk.top() == "0")
                {
                    while (!stk.empty() && stk.top() != pust)
                    {
                        operand_1 += stk.top();
                        stk.pop();
                    }
                    std::reverse(operand_1.begin(), operand_1.end());
                }
                else
                {
                    while (!stk.empty() && stk.top() != pust)
                    {
                        operand_1 += stk.top();
                        stk.pop();
                    }
                }

            }

            std::string result = evaluate(postfix[i], std::stoi(operand_1), std::stoi(operand_2));
            stk.push(result);
        }
        else
            if (postfix[i] == ' ')
                stk.push(" ");
            else
                stk.push(std::to_string(postfix[i] - '0'));

        operand_1 = " ";
        operand_2 = " ";
    }

    return std::stoi(stk.top());
}
