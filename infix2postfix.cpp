#include "infix2postfix.h"

#include <unordered_map>
#include <stack>
#include <iostream>


std::unordered_map<char, int> precendenceLookupMap{
	{'+', 1},
	{ '-', 1 },
	{ '*', 2 },
	{ '/', 2 },

};

int Evaluate(std::string const & postfix)
{
	std::stack<int> stack; //( postfix.length() );

	for (std::string::const_iterator it = postfix.begin(); it != postfix.end(); ++it) {
		char token = *it;

		if (token >= '0' && token <= '9') {
			stack.push(token - '0');
		}
		else {
			int arg2 = stack.top();
			stack.pop();
			int arg1 = stack.top();
			stack.pop();

			switch (token) {
			case '+':
				stack.push(arg1 + arg2);
				break;
			case '-':
				stack.push(arg1 - arg2);
				break;
			case '*':
				stack.push(arg1 * arg2);
				break;
			case '/':
				stack.push(arg1 / arg2);
				break;
			default:
				std::cout << "Unknown operator" << std::endl;
			}
		
		}
	}
	return stack.top();
}

bool comparePrecedence(char lhs, char rhs) {
	return precendenceLookupMap[lhs] >= precendenceLookupMap[rhs];
}

std::string Infix2postfix(std::string const & infix)
{
	std::stack<char> transitionStack;

	std::string postFix;
	std::string::const_iterator b = infix.begin(), e = infix.end();

	while(b!=e) {
		switch (*b) {
		case '(':
			transitionStack.push(*b);
			break;
		case ')':
			while (transitionStack.top() != '(') {
				postFix.push_back(transitionStack.top());
				transitionStack.pop();
			}
			transitionStack.pop();
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			if(transitionStack.empty() || transitionStack.top() == '(' || comparePrecedence(*b, transitionStack.top())) {
				transitionStack.push(*b);
			}else {
				postFix.push_back(transitionStack.top());
				transitionStack.pop();
				--b;
			}
			break;
		default:
			postFix.push_back(*b);
			break;
		}

		++b;

	}

	while(!transitionStack.empty()) {
		postFix.push_back(transitionStack.top());
		transitionStack.pop();
	}

	return postFix;
}
