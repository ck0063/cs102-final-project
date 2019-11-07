#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int userInput();

int main(){
    //int i;

    printf("user input is %d\n", userInput());

	return 0;
}

//do NOT commit to master until fixed
int userInput(){ //this function does NOT work as-is. invalid input starts infinite loop. not sure why
    int num, i;
    char term;
    do{
        if(scanf(" %d%c", &num, &term) != 2 || term != '\n'){
            printf("failure\n");
            i = 0;
        }
        else{
            i = 1;
            return num;
        }
    }while(i != 1);
}
