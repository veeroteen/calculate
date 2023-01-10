#include "utils.h"
double toDouble(const char* str)
{
	size_t length = strlen(str);
	double result = 0;
	bool decimal = false;
	size_t shift;
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == '.' || str[i] == ',')
		{
			decimal = true;
			shift = i;
			continue;
		}

		if (!decimal)
		{
			result *= 10;
			result += str[i] - 48;
		}
		else
		{
			double var = str[i] - 48;
			var = var / (pow(10, i - shift));
			result += var;
		}

	}
	return result;
}
char* toCstr(double number)
{
	int digit = number;
	double decimal = number - digit;
	unsigned int length = 0;
	unsigned int digLength = 0;
	while(digit > 0)
	{
		digit /= 10;
		length++;
		digLength++;
	}

	digit = 1;

	while(digit != 0)
	{
		decimal *= 10;
		digit = decimal;
		decimal -= digit;
		length++;
	}

	digit = number;
	char* str = (char*)calloc(length + 1, sizeof(char));

	for(int i = 0; i < digLength; i++)
	{
		int divide = pow(10, digLength - i - 1);
		str[i] = digit / divide + 48;
		int buff = digit / divide;
		digit -= buff * divide;
	}

	str[digLength] = '.';
	digit = number;
	decimal = number - digit;
	length = digLength + 1;

	while (true)
	{
		decimal *= 10;
		digit = decimal;
		if(digit != 0)
		{
			str[length] = digit + 48;
		}
		else
		{
			break;
		}
		decimal -= digit;	
		length++;
	}

	return str;
}

char* subcstr(const char* str, size_t begin, size_t end)
{
	int length = end - begin + 1;
	char* result = (char*)calloc(length + 1, sizeof(char));

	for(int i = 0; i < length; i++)\
	{
		result[i] = str[i + begin];
	}

	return result;
}

void clear(char* &str, size_t begin, size_t end)
{
	size_t length = strlen(str);
	char* buff = (char*)calloc(length - (end - begin), sizeof(char));

	for(size_t i = 0; i < begin; i++)
	{
		buff[i] = str[i];
	}

	for(size_t i = 0; i+end+1 < length; i++)
	{
		buff[begin + i] = str[i + end + 1];
	}

	free(str);
	str = buff;

}

void incert(char* &change, char* add, size_t position)
{
	size_t lengthChange = strlen(change);
	size_t lengthAdd = strlen(add);

	char* buff = (char*)calloc(lengthAdd+lengthChange + 1, sizeof(char));

	for(int i = 0; i < position; i++)
	{
		buff[i] = change[i];
	}

	for(int i = 0; i < lengthAdd; i++)
	{
		buff[i + position] = add[i];
	}

	for(int i = position; i < lengthChange; i++)
	{
		buff[i + lengthAdd] = change[i];
	}

	free(change);
	change = buff;
}