#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int is_op(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int is_dig(char ch) {
    return '0' <= ch && ch <= '9';
}

int parse_num(const char* s, int* index) {
    int res = 0;
    int i = *index;
    while(is_dig(s[i])) {
        res = 10 * res + (s[i] - '0');  
        ++i;
    }
    *index = i;
    return res;
}

int* parse_integers(const char* str) {
    int i = 0;
    int index = 0;
    int*nums = (int*)malloc(3 * sizeof(int));
    while (str[i] != '\0')
    {
        while(!is_dig(str[i]) && str[i] != '\0') {
            ++i;
        }
        if (str[i] != '\0') {
            nums[index] = parse_num(str, &i);
            ++index;
            ++i;
        }
    }
    return nums;
}

double calc(int lhs, int rhs, char op) {
    if (op == '+') {
        return lhs + rhs;
    } else if (op == '-') {
        return lhs - rhs;
    } else if (op == '/') {
        return (double)lhs / rhs;
    } else if (op == '*') {
        return lhs * rhs;
    }
    return 0.;
}

char const* exec(char const* s, int* lvl, char* op) {
    for(; *s != '\0'; ++s) {
        if (*s == '(') {
            ++(*lvl);
        } else if (*s == ')') {
            --(*lvl);
        } else if (is_op(*s)) {
            *op = *s;
            ++s;
            break;
        } 
    }
    return s;
}

double calc_result(char const* str) {
    char const* curr = str;
    int lvl1 = 0;
    char op1 = 0; 
    curr = exec(curr, &lvl1, &op1);
    
    int lvl2 = lvl1;
    char op2 = 0; 
    exec(curr, &lvl2, &op2);
    int* nums = parse_integers(str);

    double ans = 0;
    
    if (lvl1 > lvl2) {    
        ans = calc(
            calc(nums[0], nums[1], op1),
            nums[2], 
            op2
        );
    } else if (lvl1 < lvl2) {
        ans = calc(
            nums[0], 
            calc(nums[1], nums[2], op2),
            op1
        );
    } else {
        if (op1 == '/' || op1 == '*') {
            ans = calc(
                calc(nums[0], nums[1], op1),
                nums[2], 
                op2
            );  
        } else if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) {
            ans = calc(
                nums[0], 
                calc(nums[1], nums[2], op2),
                op1
            );  
        } else {
            ans = calc(
                calc(nums[0], nums[1], op1),
                nums[2], 
                op2
            );  
        }
    }
    free(nums);
    return ans;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 0;
    }
    printf("%f\n", calc_result(argv[1]) );
    return 0;
}