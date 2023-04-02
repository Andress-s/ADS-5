// Copyright 2021 NNTU-CS
#include <stack>
#include <string>
#include <algorithm>
#include <iostream>

bool isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return true;
    return false;
}

int pr(char ch) {
    if (ch == '*' || ch == '/')
        return 2;
    if (ch == '+' || ch == '-')
        return 1;
    return 0;
}


std::string infx2pstfx(std::string infix) {
    std::stack<char> stk;
    std::string postfix;
    for (int i = 0; i < infix.size(); i++) {
        if (isOperator(infix[i])) {
            postfix.push_back(' ');
            while (!stk.empty() && pr(stk.top()) >= pr(infix[i])) {
                postfix += stk.top();
                stk.pop();
            }
            stk.push(infix[i]);
        }
        else if (infix[i] == '(') {
            stk.push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (!stk.empty() && stk.top() != '(') {
                //postfix.push_back(' ');
                postfix += stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else postfix += infix[i];
    }
    while (!stk.empty()) {
        postfix += stk.top();
        stk.pop();
    }
    return postfix;
}

std::string ev(char op, int op1, int op2) {
    switch (op) {
    case '+': return std::to_string(op1 + op2);
    case '-': return std::to_string(op1 - op2);
    case '*': return std::to_string(op1 * op2);
    case '/': return std::to_string(op1 / op2);
    }
    return 0;
}

int eval(std::string postfix) {
    std::stack<std::string> stk;
    std::string pust = " ";
    std::string op2;
    std::string op1;
    for (int i = 0; i < postfix.size(); i++) {
        if (isOperator(postfix[i])) {
            if (stk.top() == "0") {
                while (!stk.empty() && stk.top() != pust) {
                    op2 += stk.top();
                    stk.pop();
                }
                std::reverse(op2.begin(), op2.end());
            }
            else {
                while (!stk.empty() && stk.top() != pust) {
                    op2 += stk.top();
                    stk.pop();
                }
            }
            if (stk.top() == " ") {
                stk.pop();
                if (stk.top() == "0") {
                    while (!stk.empty() && stk.top() != pust) {
                        op1 += stk.top();
                        stk.pop();
                    }
                    std::reverse(op1.begin(), op1.end());
                }
                else {
                    while (!stk.empty() && stk.top() != pust) {
                        op1 += stk.top();
                        stk.pop();
                    }
                }
            }
            std::string r = ev(postfix[i], std::stoi(op1), std::stoi(op2));
            stk.push(r);
        }
        else if (postfix[i] == ' ') {
            stk.push(" ");
        }
        else {
            stk.push(std::to_string(postfix[i] - '0'));
        }
        op1 = " ";
        op2 = " ";
    }
    return std::stoi(stk.top());
}
