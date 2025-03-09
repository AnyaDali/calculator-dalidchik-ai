#ifndef CALCULATOR_H
#define CALCULATOR_H

int is_op(char ch);

int is_dig(char ch);

long int parse_num(const char* s, int* index);

long int* parse_integers(const char* str);

double calc(double lhs, double rhs, char op);

char const* exec(char const* s, int* lvl, char* op);

double calc_result(char const* str, int use_float);

int my_str_cmp(const char* str1, const char* str2);

#endif