#include "calculator.h"
#include <stdio.h>

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