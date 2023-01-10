#include "Calculator.h"

double Calculator::calc(const char* str)
{
	
	size = strlen(str);
	char* arr = (char*)calloc(size +1 , sizeof(char));
	for(int i = 0; i < size; i++)
	{
		if(str[i] != '.' && str[i] != ',' &&str[i] != '(' && str[i] != ')' && str[i] != '+' && 
			str[i] != '-' && str[i] != '/' && str[i] != '*' && str[i] != '^' && (str[i] > '9' || str[i] < '0'))
		{
			throw runtime_error("incorrect enter");
		}
		arr[i] = str[i];
	}
	removeBrecketsSmart(arr);
	size = strlen(arr);
	size_t start, end;

	while (true) {

		if(findOperation(start, end, arr)==0)
		{
			break;
		}
		char* operation = subcstr(arr, start, end);
		removeBrecketsAll(operation);
		double operationResult = calculate(operation);
		free(operation);
		char* result = toCstr(operationResult);
		clear(arr, start, end);
		incert(arr, result, start);
		free(result);
		removeBrecketsSmart(arr);
		size = strlen(arr);

	}
	double result = toDouble(arr);
	free(arr);
	return result;
}

size_t Calculator::findOperation(size_t& start, size_t& end, const char* str)const
{
	size_t operCount = 0;
	prioritet hightOperation, lastOperation;
	size_t bracket = 0;
	for (int i = 0; i < size; i++)
	{
		if (str[i] == '(')
		{
			bracket += 3;
			continue;
		}
		if (str[i] == ')')
		{
			bracket -= 3;
			//runtime eror!!!
			continue;
		}
		switch (str[i])
		{
		case '^':
			lastOperation.priority = bracket + 3;
			break;
		case '+':
			lastOperation.priority = bracket + 1;
			break;
		case '-':
			lastOperation.priority = bracket + 1;
			break;
		case '*':
			lastOperation.priority = bracket + 2;
			break;
		case '/':
			lastOperation.priority = bracket + 2;
			break;
		default:
			continue;
		}
		lastOperation.position = i;
		operCount++;
		if (lastOperation.priority > hightOperation.priority)
		{
			hightOperation = lastOperation;
		}
	}
	for (int i = hightOperation.position - 1; i >= 0; i--)
	{
		if (str[i] > '9' || str[i] < '0' && str[i] != '.' && str[i] != ',')
		{
			start = i + 1;
			break;
		}
		start = i;
	}
	for (int i = hightOperation.position + 1; i < size; i++)
	{
		if (str[i] > '9' || str[i] < '0' && str[i] != '.' && str[i] != ',')
		{
			end = i - 1;
			break;
		}
		end = i;
	}
	return operCount;
}
void Calculator::removeBrecketsAll(char*& str)const
{
	size_t length = strlen(str);
	for (int i = 0; i < length; i++)
	{
		if (str[i] == ')' || str[i] == '(')
		{
			clear(str, i, i);
			i--;
		}

	}
}
void Calculator::removeBrecketsSmart(char*& str)const
{
	size_t length = strlen(str);
	size_t counter = 0;
	size_t open = 0;
	bool operation = false;
	for (int i = 0; i < length; i++)
	{
		if (str[i] == '(')
		{
			counter++;
			open = i;
			operation = false;
		}
		else if (str[i] == ')' && !operation)
		{
			if(counter == 0)
			{
				throw runtime_error("incomplete brecket");
			}
			clear(str, open, open);
			i--;
			clear(str, i, i);
			i--;
			i = 0;
			size_t length = strlen(str);
		}
		else if (str[i] == '^' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			operation = true;
		}
	}
}
double Calculator::calculate(char* str)const throw(runtime_error)
{
	double leftOper, rightOper;
	char oper = 0;
	size_t length = strlen(str);
	for (int i = 0; i < length; i++)
	{
		if (str[i] == '^' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			oper = str[i];
			char* buff = subcstr(str, 0, i - 1);
			leftOper = toDouble(buff);
			free(buff);
			buff = subcstr(str, i + 1, length - 1);
			rightOper = toDouble(buff);
			free(buff);
		}

	}

	switch (oper)
	{
	case '^':
		return pow(leftOper, rightOper);
	case '+':
		return leftOper + rightOper;
	case '-':
		return leftOper - rightOper;
	case '*':
		return leftOper * rightOper;
	case '/':
		if(rightOper == 0)
		{
			throw runtime_error("divide on 0");
		}
		return leftOper / rightOper;
	default:
		throw runtime_error("operation error");
	}

}

