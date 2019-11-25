#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define SIZE 1000

struct item{
    char name[100];
    int quantity, id;
    float price;
};

char singleUserInput();
void startMenu();
void checkoutMenu();
void itemLookup();

int main(){
    printf("Welcome to the CS102 Grocery Store Kiosk! Input the number of the task you wish to do. Make your selection now!\n");
    startMenu();

    return 0;
}

char singleUserInput(){ //taking input as a string literal prevents most bad-ness.
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

void startMenu(){
    char input;
    int flag = 0;

    printf("\n1. Start checkout\n2. Look up item\n\n");
    do{
        input = singleUserInput();
        switch(input){
            case '1':
                flag = 1;
                checkoutMenu();
                break;

            case '2':
                flag = 1;
                //itemLookup();
                break;

            default:
                printf("That isn't valid input. Please try again: ");
        }
    }while(flag != 1);
}

void checkoutMenu(){
    char input;
    int flag = 0;
    printf("\n-----Checkout menu-----\n\nInput the number of the task you wish to do.\n\n1. Add item\n2. Remove item\n3. Continue to payment\n4. Return to start menu\n\n");
    do{
        input = singleUserInput();
        switch(input){
            case '1': //add item
                flag = 1;

                break;

            case '2': //remove item
                flag = 1;

                break;

            case '3': //payment
                flag = 1;

                break;
            case '4': //return to start
                flag = 1;
                startMenu();
                break;

            default:
                printf("That isn't valid input. Please try again: ");
        }
    }while(flag != 1);
}

void itemLookup(){
    FILE *listPtr;
    char print[SIZE];

    listPtr = fopen("items.txt", "r+");
    if(listPtr == NULL){
        puts("We're sorry, but the item lookup system is experiencing technical difficulties. Seek assistance from staff.");
    }
    else{
        int i = 0;
        puts("");
        while(!feof(listPtr)){
            fgets(print, SIZE, listPtr);
            for(i = 0; i < SIZE - 1; i++){
                if(print[i] == '\0'){
                    break;
                }
                printf("%c", print[i]);
            }
        }
    }
    fclose(listPtr);
}
