#include <iostream>
#include <string>
#include <stack>
#include <cassert>

using namespace std;
int evaluate(string infix, string& postfix, bool& result);
bool validInfix(string infix);
int getPrecedence(char op);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.

int getPrecedence(char op)
{
	if (op == '!')
	{
		return 2;
	}
	if (op == '&')
	{
		return 1;
	}
	if (op == '|')
	{
		return 0;
	}
	return -1;
}


int evaluate(string infix, string& postfix, bool& result)
{
	if (validInfix(infix))
	{
		postfix = "";
		stack<char> operatorStack;
		string infix2 = "";
		for (size_t j = 0; j < infix.length(); j++)
		{
			infix2 += infix[j];
		}

		for (size_t i = 0; i < infix2.length(); i++)
		{
			switch (infix2[i])
			{
			case 'T':
			case 'F':
				postfix += infix2[i];
				break;
			case '(':
				operatorStack.push(infix2[i]);
				break;
			case ')':
				while (operatorStack.top() != '(')
				{
					postfix += operatorStack.top();
					operatorStack.pop();
				}
				operatorStack.pop();
				break;
			case '&':
			case '|':
			case '!':
				while (!operatorStack.empty() && operatorStack.top() != '(' && getPrecedence(infix2[i]) <= getPrecedence(operatorStack.top()))
				{
					postfix += operatorStack.top();
					operatorStack.pop();
				}
				operatorStack.push(infix2[i]);
				break;
			default:
				break;
			}
		}
		while (!operatorStack.empty())
		{
			postfix += operatorStack.top();
			operatorStack.pop();
		}
		//Infix has now been converted into postfix... now to evaluate the postfix expression
		/////////////////////////////////////
		stack<bool> operandStack;
		for (size_t m = 0; m < postfix.length(); m++)
		{
			if (postfix[m] == 'T')
			{
				operandStack.push(true);
			}
			else if (postfix[m] == 'F')
			{
				operandStack.push(false);
			}
			else if (postfix[m] == '!')
			{
				bool top = operandStack.top();
				operandStack.pop();
				operandStack.push(!top);
			}
			else
			{
				bool operand2 = operandStack.top();
				operandStack.pop();
				bool operand1 = operandStack.top();
				operandStack.pop();
				if (postfix[m] == '|')
				{
					bool result = operand1 || operand2;
					operandStack.push(result);
				}
				if (postfix[m] == '&')
				{
					bool result = operand1 && operand2;
					operandStack.push(result);
				}
			}
		}
		result = operandStack.top();
		return 0;
	}
	return 1;
	
} 

bool validInfix(string infix)
{

	int truecount = 0;
	int falsecount = 0;
	int parenthesescount = 0;
	//Remove spaces from the infix
	string infix2 = "";
	for (size_t i = 0; i < infix.length(); i++)
	{
		if (infix[i] != ' ')
		{
			infix2 += infix[i];
		}
	}
	if (infix2.size() == 0)
	{
		return false;
	}
	//Now check for the last character of infix. If the last char is an operator then the infix is not valid
	if (infix2[infix2.size() - 1] == '|' || infix2[infix2.size() - 1] == '&' || infix2[0] == '|' || infix2[0] == '&')
	{
		return false;
	}
	for (size_t j = 0; j < infix2.length(); j++)
	{
		switch (infix2[j]) {
		case '|':
		case '&':
			if ((infix2[j - 1] != 'T' && infix2[j - 1] != 'F' && infix2[j - 1] != ')') || (infix2[j + 1] != 'T' && infix2[j + 1] != 'F' && infix2[j + 1] != '!' && infix2[j + 1] != '('))
			{
				return false;
			}
			break;
		case 'T':
		case 'F':
			if (j != infix2.size() - 1)
			{
				if (infix2[j+1] != ')' && infix2[j+1] != '&' && infix2[j+1] != '|') 
				{
					return false;
				}
			}
			falsecount++;
			truecount++;
			break;
		case '(':
		case ')':
			parenthesescount++;
		default:
			break;
		}
	}
	if ((truecount == 0 && falsecount == 0) || (parenthesescount % 2 != 0))
	{
		return false;
	}
	return true;
}

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|"  &&  answer);
	assert(evaluate("T|", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("T(F|T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F|F)", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&|" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	assert(validInfix("T| F"));
	assert(!validInfix("T|"));
	assert(!validInfix("F F"));
	assert(!validInfix("TF"));
	assert(!validInfix("()"));
	assert(!validInfix("T(F|T)"));
	assert(!validInfix("T(&T)"));
	assert(!validInfix("(T&(F|F)"));
	assert(!validInfix(""));

	assert(validInfix("F  |   !F & (T&F) "));
	assert(validInfix(" F  "));
	assert(validInfix("((T))"));
	assert(validInfix("T & (T|F)"));
	assert(validInfix("!F"));
	assert(validInfix("T&(F)"));
	assert(validInfix("!F|T"));
	assert(!validInfix("T!"));
	assert(validInfix("F |T&T"));


	cout << "Passed all tests" << endl;

}