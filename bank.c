#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Declaring all the functions
void viewBalance(char*);
void sendMoney(void);
void showDetails(char*);
void userInfo(char*);
void userLogin(void);
void loginSuccess(void);
void createAccount(void);
void accountSetup(void);
void afterLoginScreen(void);
void signOut(void);

// Declaring gotoXY function for setting cursor position
void gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Creating a structure to store data of the user
struct userDetails {
    char username[50];
    int day, month, year;
    char phoneNumber[15];
    char aadharNumber[20];
    char firstName[20];
    char lastName[20];
    char fatherName[20];
    char motherName[20];
    char address[50];
    char accountType[20];
};

// Structure to keep track of amount transfer
struct transfer {
    char toUsername[50];
    char fromUsername[50];
    long int amount;
};

struct userPassword {
    char password[50];
};

// Driver Code
int main()
{
    int choice;
    gotoXY(20, 3);

    // Creating a Main menu for the user
    printf("WELCOME TO BANK ACCOUNT SYSTEM\n\n");
    gotoXY(18, 5);
    printf("**********************************");
    gotoXY(25, 7);
    printf("DEVELOPER: Jane Doe");

    gotoXY(20, 10);
    printf("1. CREATE A BANK ACCOUNT");
    gotoXY(20, 12);
    printf("2. ALREADY A USER? SIGN IN");
    gotoXY(20, 14);
    printf("3. EXIT\n\n");

    printf("\n\nENTER YOUR CHOICE: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        system("cls");
        printf("\n\n USERNAME 50 CHARACTERS MAX!!");
        printf("\n\n PASSWORD 50 CHARACTERS MAX!!");
        createAccount();
        break;

    case 2:
        userLogin();
        break;

    case 3:
        exit(0);
        break;

    getch();
    }
}

// Function to create accounts of users
void createAccount(void)
{
    char password[20];
    int passwordLength, i;
    char ch;
    FILE *userFile;
    struct userDetails newUser;
    struct userPassword newPass;

    // Opening file to write data of a user
    userFile = fopen("user_data.txt", "ab");

    // Inputs
    system("cls");
    printf("\n\n!!!!!CREATE ACCOUNT!!!!!");

    printf("\n\nFIRST NAME: ");
    scanf("%s", newUser.firstName);

    printf("\n\nLAST NAME: ");
    scanf("%s", newUser.lastName);

    printf("\n\nFATHER's NAME: ");
    scanf("%s", newUser.fatherName);

    printf("\n\nMOTHER's NAME: ");
    scanf("%s", newUser.motherName);

    printf("\n\nADDRESS: ");
    scanf("%s", newUser.address);

    printf("\n\nACCOUNT TYPE: ");
    scanf("%s", newUser.accountType);

    printf("\n\nDATE OF BIRTH: ");
    printf("\nDAY: ");
    scanf("%d", &newUser.day);
    printf("\nMONTH: ");
    scanf("%d", &newUser.month);
    printf("\nYEAR: ");
    scanf("%d", &newUser.year);

    printf("\n\nAADHAR NUMBER: ");
    scanf("%s", newUser.aadharNumber);

    printf("\n\nPHONE NUMBER: ");
    scanf("%s", newUser.phoneNumber);

    printf("\n\nUSERNAME: ");
    scanf("%s", newUser.username);

    printf("\n\nPASSWORD: ");
    for (i = 0; i < 50; i++) {
        ch = getch();
        if (ch != 13) {
            password[i] = ch;
            ch = '*';
            printf("%c", ch);
        }
        else
            break;
    }

    // Writing to the file
    fwrite(&newUser, sizeof(newUser), 1, userFile);

    // Closing file
    fclose(userFile);

    // Calling another function after successful creation of account
    accountSetup();
}

// Successful account creation
void accountSetup(void)
{
    int i;
    system("cls");
    printf("PLEASE WAIT....\n\nYOUR DATA IS PROCESSING....");
    for (i = 0; i < 200000000; i++) {
        i++;
        i--;
    }

    gotoXY(30, 10);
    printf("ACCOUNT CREATED SUCCESSFULLY....");
    gotoXY(0, 20);
    printf("Press enter to login");

    getch();
    userLogin();
}

// Login function to check the username of the user
void userLogin(void)
{
    system("cls");

    char username[50];
    char password[50];
    int i;
    char ch;
    FILE *userFile;
    struct userDetails existingUser;

    // Opening file of user data
    userFile = fopen("user_data.txt", "rb");

    if (userFile == NULL) {
        printf("ERROR IN OPENING FILE");
    }
    gotoXY(34, 2);
    printf(" ACCOUNT LOGIN ");
    gotoXY(7, 5);
    printf("***********************************************"
           "********************************");

    gotoXY(35, 10);
    printf("==== LOG IN ====");

    // Take input
    gotoXY(35, 12);
    printf("USERNAME: ");
    scanf("%s", username);

    gotoXY(35, 14);
    printf("PASSWORD: ");
    for (i = 0; i < 50; i++) {
        ch = getch();
        if (ch != 13) {
            password[i] = ch;
            ch = '*';
            printf("%c", ch);
        }
        else
            break;
    }

    // Checking if username exists in the file or not
    while (fread(&existingUser, sizeof(existingUser), 1, userFile)) {
        if (strcmp(username, existingUser.username) == 0) {
            loginSuccess();
            showDetails(username);
        }
    }

    // Closing the file
    fclose(userFile);
}

// Redirect after successful login
void loginSuccess(void)
{
    int i;
    system("cls");
    printf("Fetching account details.....\n");
    for (i = 0; i < 20000; i++) {
        i++;
        i--;
    }

    gotoXY(30, 10);
    printf("LOGIN SUCCESSFUL....");
    gotoXY(0, 20);
    printf("Press enter to continue");

    getch();
}

// Display function to show the data of the user on screen
void showDetails(char username[])
{
    system("cls");
    FILE *userFile;
    int choice, i;
    userFile = fopen("user_data.txt", "rb");
    struct userDetails existingUser;

    if (userFile == NULL) {
        printf("Error in opening file");
    }

    while (fread(&existingUser, sizeof(existingUser), 1, userFile)) {
        if (strcmp(username, existingUser.username) == 0) {
            gotoXY(30, 1);
            printf("WELCOME, %s %s", existingUser.firstName, existingUser.lastName);
            gotoXY(28, 2);
            printf("..........................");
            gotoXY(55, 6);
            printf("==== YOUR ACCOUNT INFO ====");
            gotoXY(55, 8);
            printf("***************************");
            gotoXY(55, 10);
            printf("NAME: %s %s", existingUser.firstName, existingUser.lastName);

            gotoXY(55, 12);
            printf("FATHER's NAME: %s", existingUser.fatherName);

            gotoXY(55, 14);
            printf("MOTHER's NAME: %s", existingUser.motherName);

            gotoXY(55, 16);
            printf("AADHAR CARD NUMBER: %s", existingUser.aadharNumber);

            gotoXY(55, 18);
            printf("MOBILE NUMBER: %s", existingUser.phoneNumber);

            gotoXY(55, 20);
            printf("DATE OF BIRTH: %d-%d-%d", existingUser.day, existingUser.month, existingUser.year);

            gotoXY(55, 22);
            printf("ADDRESS: %s", existingUser.address);

            gotoXY(55, 24);
            printf("ACCOUNT TYPE: %s", existingUser.accountType);
        }
    }

    fclose(userFile);

    gotoXY(0, 6);

    // Menu to perform different actions by user
    printf(" HOME ");
    gotoXY(0, 7);
    printf("******");
    gotoXY(0, 9);
    printf(" 1. CHECK BALANCE");
    gotoXY(0, 11);
    printf(" 2. TRANSFER MONEY");
    gotoXY(0, 13);
    printf(" 3. LOG OUT\n\n");
    gotoXY(0, 15);
    printf(" 4. EXIT\n\n");

    printf(" ENTER YOUR CHOICE: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        viewBalance(username);
        break;

    case 2:
        sendMoney();
        break;

    case 3:
        signOut();
        userLogin();
        break;

    case 4:
        exit(0);
        break;
    }
}

// Function to transfer money from one user to another
void sendMoney(void)
{
    int i, j;
    FILE *moneyFile, *userFile;
    struct userDetails existingUser;
    struct transfer transaction;
    char fromUser[20];
    char toUser[20];
    system("cls");

    // Opening file in read mode to read user's username
    userFile = fopen("user_data.txt", "rb");

    // Creating another file to write amount along with username to which amount is going to be transferred
    moneyFile = fopen("transactions.txt", "ab");

    gotoXY(33, 4);
    printf("---- TRANSFER MONEY ----");
    gotoXY(33, 5);
    printf("========================");

    gotoXY(33, 11);
    printf("FROM (your username): ");
    scanf("%s", fromUser);

    gotoXY(33, 13);
    printf("TO (username of recipient): ");
    scanf("%s", toUser);

    // Checking for username if it is present in file or not
    while (fread(&existingUser, sizeof(existingUser), 1, userFile)) {
        if (strcmp(toUser, existingUser.username) == 0) {
            strcpy(transaction.toUsername, existingUser.username);
            strcpy(transaction.fromUsername, fromUser);
        }
    }
    gotoXY(33, 16);

    // Taking amount input
    printf("ENTER THE AMOUNT TO BE TRANSFERRED: ");
    scanf("%d", &transaction.amount);

    // Writing to the file
    fwrite(&transaction, sizeof(transaction), 1, moneyFile);

    gotoXY(0, 26);
    printf("--------------------------------------------------"
           "--------------------------------------------");

    gotoXY(0, 28);
    printf("--------------------------------------------------"
           "--------------------------------------------");

    gotoXY(0, 29);
    printf("Transferring amount, please wait...");

    gotoXY(10, 27);
    for (i = 0; i < 70; i++) {
        for (j = 0; j < 1200000; j++) {
            j++;
            j--;
        }
        printf("*");
    }

    gotoXY(33, 40);
    printf("AMOUNT SUCCESSFULLY TRANSFERRED....");
    getch();

    // Close the files
    fclose(userFile);
    fclose(moneyFile);

    // Function to return to the home screen
    showDetails(fromUser);
}

// Function to check balance in user's account
void viewBalance(char username[])
{
    system("cls");
    FILE *moneyFile;
    struct transfer transaction;
    int i = 1, totalBalance = 0;

    // Opening amount file record
    moneyFile = fopen("transactions.txt", "rb");

    int col1 = 5, row1 = 10;
    int col2 = 30, row2 = 10;
    int col3 = 60, row3 = 10;

    gotoXY(30, 2);
    printf("==== BALANCE DASHBOARD ====");
    gotoXY(30, 3);
    printf("***************************");
    gotoXY(col1, row1);
    printf("S no.");
    gotoXY(col2, row2);
    printf("TRANSACTION ID");
    gotoXY(col3, row3);
    printf("AMOUNT");

    // Reading username to fetch the correct record
    while (fread(&transaction, sizeof(transaction), 1, moneyFile)) {
        if (strcmp(username, transaction.toUsername) == 0) {
            gotoXY(col1, ++row1);
            printf("%d", i);
            i++;
            gotoXY(col2, ++row2);
            printf("%s", transaction.fromUsername);

            gotoXY(col3, ++row3);
            printf("%d", transaction.amount);
            // Adding and finding total money
            totalBalance += transaction.amount;
        }
    }

    gotoXY(80, 10);
    printf("TOTAL AMOUNT");

    gotoXY(80, 12);
    printf("%d", totalBalance);

    getch();

    // Closing file after reading it
    fclose(moneyFile);
    showDetails(username);
}

// Logout function to bring user to the login screen
void signOut(void)
{
    int i, j;
    system("cls");
    printf("Please wait, logging out");

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 25000000; j++) {
            i++;
            i--;
        }
        printf(".");
    }

    gotoXY(30, 10);
    printf("Signed out successfully..\n");

    gotoXY(0, 20);
    printf("Press any key to continue..");

    getch();
}
