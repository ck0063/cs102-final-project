#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define SIZE 1000

char userInput();

int main(){

    printf("user input is %c\n", userInput());

	return 0;
}

char userInput(){ //taking input as a single character prevents most bad-ness. check the character externally as needed when reading user input.
    char term[SIZE];

    scanf("%c", &term);

    return term[0];
}
