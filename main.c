#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define SIZE 1000

char userInput();
void checkoutMenu();

int main(){
    char input;
    int flag = 0;

    printf("Welcome to the CS102 Grocery Store Kiosk! Input the number of the task you wish to do. Make your selection now!\n\n1. Start checkout\n2. Look up item\n\n");
    do{
        input = userInput();
        switch(input){
            case '1':
                flag = 1;
                //checkoutMenu();
                break;

            case '2':
                flag = 1;
                //itemLookup();
                break;

            default:
                printf("That isn't valid input. Please try again: ");
        }
    }while(flag != 1);

	return 0;
}

char userInput(){ //taking input as a string literal prevents most bad-ness.
    char term[SIZE];
    int result;

    result = scanf(" %s", term);
    
    if (strlen(term) > 1){ //if user inputs more than one character, just return something that will trigger the function recall
        if (result == EOF){ //this is the only method i could find to save our souls from someone inputting the EOF character. we just have to say bye-bye and shut it all down.
            exit(0);
        }
        term[0] = '\0';
    }
    return term[0];
}
