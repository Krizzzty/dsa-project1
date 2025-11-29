/**************************************** 
 * Name:Kristiena Benny
 * Description: Arithematic Progressive Calculator
 * Date:12-01-2025
****************************************/

#include "APC_main.h"

int main(int argc,char** argv){
    calculator cal;
    if(argc==4 && validate_arguments(argv,&cal)==success){
        printf("Validation of arguments successfull\n");
        if(perform_operation(&cal)==success){
         printf("Arithematic operation is successfull\n");
        }
        else{
            
        }
    }
    else{
        printf("Failed in validation of arguments\n");
        printf("---------------------------HELP-----------------------------\n");
        printf("To perform addition operation----> ./a.out operand1 + operand2\n");
        printf("To perform subtraction operation----> ./a.out operand1 + operand2\n");
        printf("To perform multipliaction operation----> ./a.out operand1 \\* operand2\n");
        printf("To perform division operation----> ./a.out operand1 / operand2\n");
        printf("---------------------------HELP-----------------------------\n");
    }
}