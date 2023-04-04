// Copyright 2021 NNTU-CS
#include <string>
#include <stack>
#include <algorithm>
#include "tstack.h"

bool isOperator(char ch) {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    return true;
  return false;
}

int prec(char ch) {
  if (ch == '*' || ch == '/')
    return 2;
  if (ch == '+' || ch == '-')
    return 1;
  return 0;
}

std::string infx2pstfx(std::string inf) {
  std::stack<char> stk;
  std::string prefix;
  for (int i = 0; i < inf.size(); i++) {
    if (isOperator(inf[i])) {
      prefix.push_back(' ');
      while (!stk.empty() && prec(stk.top()) >= prec(inf[i])) {
        prefix += stk.top();
        stk.pop();
        prefix.push_back(' ');
      }
      stk.push(inf[i]);
    } else if (inf[i] == '(') {
      stk.push(inf[i]);
    } else if (inf[i] == ')') {
      while (!stk.empty() && stk.top() != '(') {
        prefix.push_back(' ');
        prefix += stk.top();
        stk.pop();
      }
      stk.pop();
    } else {
      prefix += inf[i];
    }
  }
  while (!stk.empty()) {
    prefix.push_back(' ');
    prefix += stk.top();
    stk.pop();
  }
  return prefix;
}
std::string ev(char op, int op_1, int op_2) {
  switch (op) {
    case '+': return std::to_string(op_1 + op_2);
    case '-': return std::to_string(op_1 - op_2);
    case '*': return std::to_string(op_1 * op_2);
    case '/': return std::to_string(op_1 / op_2);
  }
  return 0;
}
int eval(std::string pref) {
  std::stack<std::string> stk;
  std::string pust = " ";
  std::string op_2;
  std::string op_1;
  for (int i = 0; i < pref.size(); i++) {
    if (isOperator(pref[i])) {
      if (stk.top() == " ") {
        stk.pop();
      }
      if (stk.top() == "0") {
        while (!stk.empty() && stk.top() != pust) {
          opera_2 += stk.top();
          stk.pop();
        }
        if (op_2[0] == '0')
          std::reverse(op_2.begin(), op_2.end());
      } else {
        while (!stk.empty() && stk.top() != pust) {
          op_2 += stk.top();
          stk.pop();
          if (op_2[0] == '0')
            std::reverse(op_2.begin(), op_2.end());
        }
        if (stk.top() == " ") {
          stk.pop();
          if (stk.top() == "0") {
            while (!stk.empty() && stk.top() != pust) {
              opera_1 += stk.top();
              stk.pop();
            }
            if (opera_1[0] == '0')
              std::reverse(op_1.begin(), op_1.end());
          } else {
            while (!stk.empty() && stk.top() != pust) {
              opera_1 += stk.top();
              stk.pop();
              if (op_1[0] == '0')
                std::reverse(op_1.begin(), op_1.end());
            }
          }
        }
        std::string res = ev(pref[i], std::stoi(op_1), std::stoi(opera_2));
        stk.push(res);
      }
    } else {
      if (pref[i] == ' ')
        stk.push(" ");
      else
        stk.push(std::to_string(pref[i] - '0'));
    }
    op_1 = " ";
    op_2 = " ";
  }
  return std::stoi(stk.top());
}
