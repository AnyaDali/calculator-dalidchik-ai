#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int is_op(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int is_dig(char ch) {
    return '0' <= ch && ch <= '9';
}

long int parse_num(const char* s, int* index) {
    long int res = 0;
    int i = *index;
    while(is_dig(s[i])) {
        res = 10 * res + (s[i] - '0');  
        ++i;
    }
    *index = i;
    return res;
}

long int* parse_integers(const char* str) {
    int i = 0;
    int index = 0;
    long int*nums = (long int*)malloc(3 * sizeof(long int));
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

float calc(int lhs, int rhs, char op) {
    if (op == '+') {
        return lhs + rhs;
    } else if (op == '-') {
        return lhs - rhs;
    } else if (op == '/') {
        return (float)lhs / rhs;
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

double calc_result(char const* str, int use_float) {
    char const* curr = str;
    int lvl1 = 0;
    char op1 = 0; 
    curr = exec(curr, &lvl1, &op1);
    
    int lvl2 = lvl1;
    char op2 = 0; 
    exec(curr, &lvl2, &op2);
    long int* nums = parse_integers(str);

    float ans = 0;
    long int result =0;
    
    if (lvl1 > lvl2) {
        if(use_float==0){
            result = (long int)(calc(
                (long int)(calc(nums[0], nums[1], op1)+0.5),
                nums[2], 
                op2
            ) + 0.5);
        }else{
            ans = calc(
                calc(nums[0], nums[1], op1),
                nums[2], 
                op2
            );
        }
    } else if (lvl1 < lvl2) {
        if(use_float==0){
            result = (long int)(calc(
                nums[0], 
                (long int)(calc(nums[1], nums[2], op2)+0.5),
                op1
            )+0.5);
        } else{
            ans = calc(
                nums[0], 
                calc(nums[1], nums[2], op2),
                op1
            );
        }
    } else {
        if (op1 == '/' || op1 == '*') {
            if(use_float==0){
                result = (long int)(calc(
                    (long int)(calc(nums[0], nums[1], op1)+0.5),
                    nums[2], 
                    op2
                ) + 0.5);
            }else{
                ans = calc(
                    calc(nums[0], nums[1], op1),
                    nums[2], 
                    op2
                );
            }
        } else if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) {
            if(use_float==0){
                result = (long int)(calc(
                    nums[0], 
                    (long int)(calc(nums[1], nums[2], op2)+0.5),
                    op1
                )+0.5);
            } else{
                ans = calc(
                    nums[0], 
                    calc(nums[1], nums[2], op2),
                    op1
                );
            }
        } else {
            if(use_float==0){
                result = (long int)(calc(
                    (long int)(calc(nums[0], nums[1], op1)+0.5),
                    nums[2], 
                    op2
                ) + 0.5);
            }else{
                ans = calc(
                    calc(nums[0], nums[1], op1),
                    nums[2], 
                    op2
                );
            } 
        }
    }
    free(nums);
    if(use_float == 0){
        return (double)result;
    }
    return ans;
}

int my_str_cmp(const char* str1, const char* str2){
    while(*str1 && *str2){
        if(*str1!= *str2){
            return 0;
        }
        str1++;
        str2++;
    }
    return (*str1==*str2);
}

int main(int argc, char* argv[]) {
    int use_float = 0;
    /*if (argc != 2) {
        printf("invalid input\n");
        return -1;
    }*/
    const char* exp = NULL;

    for(int i =1; i<argc; i++){
        if(my_str_cmp(argv[i], "--float")){
            use_float =1;
        }else{
            exp = argv[i];
        }
    }
    long int result;
    float ans;
    if(use_float==0){
        result = ( long int)(calc_result(exp,use_float));
        printf("%ld\n", result);
    }else{
        ans = calc_result(exp,use_float);
        printf("%.4f\n", ans);
    }

    return 0;
}