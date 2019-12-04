//Christopher Kegley
//Dawson Loveless

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define SIZE 1000

struct item{ //honestly not sure what this is gonna get used for. seemed like a good idea at the time
    char name[100];
    int quantity, id;
    float price;
};

char singleUserInput();
int pluralUserInput();
void startMenu();
void checkoutMenu();
void itemLookup();
void addItem(int);

int main(){
    printf("Welcome to the CS102 Grocery Store Kiosk!\n");
    startMenu();

	return 0;
}

void startMenu(){
    char input;
    int flag = 0;

    printf("\n-----Start menu-----\n\nInput the number of the task you wish to do.\n\n1. Start checkout\n2. Look up item\n\n");
    do{
        input = singleUserInput();
        switch(input){
            case '1':
                flag = 1;
                checkoutMenu();
                break;

            case '2':
                flag = 1;
                itemLookup();
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
                printf("\nPlease enter an item ID: ");
                flag = 1;
                addItem(pluralUserInput());

                break;

            case '2': //remove item
                flag = 1;

                break;

            case '3': //payment
                flag = 1;
                int pay = 0;
                float cash = 0;
                puts("Would you like to pay with (1) Cash or (2) Credit?");
                scanf("%d", &pay);
                if (pay == 1)
                {	puts("Please enter the amount of cash you are paying.\n");
                    scanf("%.2f", &cash);
                }
                else
                {
                    FILE *listPtr;
                    char print[16], cast[16];
                    int CARDNUMBER, i;
                    puts("Please enter your card number for us to check our members list.\n");
                    listPtr = fopen("members.txt", "r+");
                        if(listPtr == NULL)
                    {
                         puts("We're sorry, but our member lookup system is experiencing technical difficulties. Please seek assistance from staff.");
                        }
                        else
                    {
                            scanf("%s", &print);
                            while(!feof(listPtr)){ //until end of file,
                                fgets(print, SIZE, listPtr); //read in all data up to SIZE bytes to the print array,
                                //puts("");
                                for(i = 0; i < 16; i++){ //and printf the print array.
                                    if(print[i] == ' '){
                                        break;
                                    }
                                }
                                memcpy(cast, print, 16);
                                CARDNUMBER = atoi(cast);
                                strcmp(print, CARDNUMBER);
                                if (cast == CARDNUMBER)
                                {
                                    puts("Thank you for shopping with us, you have been billed. Please visit again!\n");

                                }
                            }
                            if(cast != CARDNUMBER)
                                {
                                    puts("We're sorry, but the number you entered is not part of our register.\n");
                                }
                        fclose(listPtr);

                    }
                }
                break;
            case '4': //return to start
                flag = 1;
                startMenu(); //this exposes us to dangerous overflow conditions, but we probably dont have to worry about it.
                break; //the potentially-recursive function calling should all collapse at the end, so it's probably fine.

            default:
                printf("That isn't valid input. Please try again: ");
        }
    }while(flag != 1);
}

void itemLookup(){
    FILE *listPtr;
    char print[SIZE];

    listPtr = fopen("items.txt", "r+"); //arbitrary filename for personal testing
    if(listPtr == NULL){ //check file open success
        puts("We're sorry, but the item lookup system is experiencing technical difficulties. Seek assistance from staff.");
    }
    else{
        int i;
        puts("");
        printf("ID | ITEM | PRICE\n----------------\n");
        while(!feof(listPtr)){ //until end of file,
            fgets(print, SIZE, listPtr); //read in all data up to SIZE bytes to the print array,
            for(i = 0; i < SIZE - 1; i++){ //and printf the print array.
                if(print[i] == '\0'){
                    break;
                }
                printf("%c", print[i]);
            }
        }
    }
    fclose(listPtr);
    startMenu();
}

void addItem(int input){
    while(input == 0){
        printf("That item ID could not be found. Please try again: ");
        input = pluralUserInput();
    }
    FILE *listPtr;
    char print[SIZE], cast[SIZE];
    struct item item1;

    listPtr = fopen("items.txt", "r+"); //arbitrary filename for personal testing
    if(listPtr == NULL){ //check file open success
        puts("We're sorry, but the checkout system is experiencing technical difficulties. Seek assistance from staff.");
    }
    else{
        int i, id;
        puts("");
        while(!feof(listPtr)){ //until end of file,
            fgets(print, SIZE, listPtr); //read in all data up to SIZE bytes to the print array,
            //puts("");
            for(i = 0; i < SIZE - 1; i++){ //and printf the print array.
                if(print[i] == ' '){
                    break;
                }
            }
            memcpy(cast, print, 4);
            id = atoi(cast);
            if(id == input){
                item1.id = id;
                printf("How many of that item would you like?: ");
                item1.quantity = singleUserInput() - '0';
                printf("id is %d, quantity is %d", item1.id, item1.quantity);
                break;
            }
        }
        if(id != input){
            puts("That item can not be found. Returning to checkout menu.");
        }
        fclose(listPtr);
        checkoutMenu();
    }
}

char singleUserInput(){ //taking input as a string literal prevents most bad-ness.
    char term[SIZE];
    int result;

    result = scanf(" %s", term);

    if(strlen(term) > 1){ //if user inputs more than one character, just return something that will trigger the function recall
        if(result == EOF){ //this is the only method i could find to save our souls from someone inputting the EOF character. we just have to say bye-bye and shut it all down.
            exit(0);
        }
        term[0] = '\0';
    }
    return term[0];
}

int pluralUserInput(){
    char term[SIZE];
    int eofcheck, result, i;

    eofcheck = scanf(" %s", term);

    if(strlen(term) % 4 != 0){
        if(eofcheck == EOF){
            exit(0);
        }
        for(i = 0; i < 16; i++){ //arbitrarily writing garbage to the first 16 bytes if the length isnt divisible by 4
            term[i] = '\0';
        }
    }
    else{
        result = atoi(term); //function from stdlib to convert string to int
    }
    //printf("%d\n", result);
    return result; //returns 0 in case of wrong number of digits OR non-digits. use 0 as function recall flag
}

void printReceipt(){
    FILE *listPtr;
    char print[SIZE];

    listPtr = fopen("items.txt", "r+"); //arbitrary filename for personal testing
    if(listPtr == NULL){ //check file open success
        puts("We're sorry, but the item lookup system is experiencing technical difficulties. Seek assistance from staff.");
    }
    else{
        int i;
        puts("");
        while(!feof(listPtr)){ //until end of file,
            fgets(print, SIZE, listPtr); //read in all data up to SIZE bytes to the print array,
            for(i = 0; i < SIZE - 1; i++){ //and printf the print array.
                if(print[i] == '\0'){
                    break;
                }
                printf("%c", print[i]);
            }
        }
    }
    fclose(listPtr);
}
