#pragma once
#include <cstring>
#include <cmath>
double toDouble(const char* str);//Cstring to double
char* toCstr(double number);// double to Cstring
char* subcstr(const char* str, size_t begin, size_t end);//include begin and end values
void clear(char* &str, size_t begin, size_t end);//create new array, without begin to end range
void incert(char* &change, char* add, size_t begin);// incert an array on begin variable position

