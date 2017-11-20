// imports
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <Windows.h>
#include <windows.h>
#include <sys/types.h>
#include <string.h>

// defines
#define size 1000

// function declarations
void Command(char*);

void cd();
void chdirfunc();
void date();
void time();
void Start();
void CreateInstance();
char* CurrentDirectory();
void getDate();
void getTime();
char* setAddressFormat(char*);

// stackoverflow hides the cursor copy & paste
void hidecursor(int hide)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   if(hide == 1) {
        info.bVisible = FALSE;
   } else {
        info.bVisible = TRUE;
   }
   SetConsoleCursorInfo(consoleHandle, &info);
}

void chdirfunc() {
    char command[size];
    char format[size];
    printf("address here: ");
    fgets(command, sizeof(command), stdin);
    sscanf(command, "%[^\n]s", format);
    chdir(format);
}

//no need for this yees
char* setAddressFormat(char* address) {
    char finalformat[size];

    int addlen = strlen(address);
    int ctr = 0, idx = 0, flag = 0;

    while(ctr < addlen) {
        if(flag != 1 && address[ctr] == '\\') {
            finalformat[idx] = address[ctr];
            if(address[ctr+1] != '\\') {
                idx++;
                finalformat[idx] = address[ctr];
            }
            flag = 1;
        } else {
            finalformat[idx] = address[ctr];
            flag = 0;
        }
        idx++;
        ctr++;
    }
    address = finalformat;
    return address;
}

char* getCommand(char* str) {
    char finalformat[size];
    char * pch;

    pch = strtok (str," ");
    if(strcmp("cd",pch) == 0) {
        return directtory
    }

    return 0;
}

// function definitions
void Command(char* command){
    if(strcmp("cd",command) == 0) {
        cd();
    } else if(strcmp("cmd",command) == 0) {
        CreateInstance();
    } else if(strcmp("cls", command) == 0) {
        // And this makes it do everything including return the cursor to the beginning: ANSI
        printf( "\033[0m\033[2J\033[H");
    } else if(strcmp("date", command) == 0) {
        getDate();
    } else if(strcmp("time", command) == 0) {
        getTime();
    } else if(strcmp("chdir", command) == 0) {
        cd();
    } else if(strcmp("dir", command) == 0) {
        system("dir");
    } else {
        printf("\'%s\'is not recognized as an internal or external command, \noperable program or batch file.\n\n", command);
    }
    Start();
}

void getaddress(int, char*);
void getaddress(int command, char* string) {
    int len01 = strlen(string);
    char directory[len01];

    if(command == 1) {
        int ctr = 3, idx = 0;
        while(ctr < len01) {
            directory[idx] = string[ctr];
            ctr++; idx++;
        }
        chdir(directory);
    }
}

char * getDay(int day) {
    if(day == 0) {
        return "Sun";
    } else if(day == 1) {
        return "Mon";
    } else if(day == 2) {
        return "Tue";
    } else if(day == 3) {
        return "Wed";
    } else if(day == 4) {
        return "Thu";
    } else if(day == 5) {
        return "Fri";
    } else if(day == 6) {
        return "Sat";
    }
}

void getDate() {
    SYSTEMTIME datenow;
    GetSystemTime(&datenow);

    printf("The current date is: %d/%d/%d\n", datenow.wDay, datenow.wMonth,datenow.wYear);
    date();
}

void getTime() {
    SYSTEMTIME datenow;
    GetSystemTime(&datenow);

    printf("The current time is: %d:%d:%d.%d\n", datenow.wHour, datenow.wMinute, datenow.wSecond, datenow.wMilliseconds);
    time();
}

void time() {
    char input[size];
    char newtime[size];

    printf("Enter the new time: ");

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%[^\n]s", newtime);

    if(input[0]== '\n') {
        printf("\n");
    } else {
        if(isValidTimeFormat(input) == 0){
            printf("The system cannot accept the time entered.\n");
            time();
        } else {
            printf("A required privilege is not held by the client.\n\n");
        }
    }
}

void date() {
    char input[size];
    char newdate[size];

    printf("Enter the new date: (dd-mm-yy) ");

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%[^\n]s", newdate);

    if(input[0]== '\n') {
        printf("\n");
    } else {
        // dd-mm-yy
        if(isValidDateFormat(input)) {
            printf("The system cannot accept the date entered.\n");
            date();
        } else {
            printf("A required privilege is not held by the client.\n\n");
        }
    }
}

int isValidDateFormat(char* date) {
    // note: use regex for this

    return 0;
    // [0-9]{2}-[0-9]{2}-[0-9]{2}
}

int isValidTimeFormat(char* time) {
    return 0;
}

void cd() {
    printf("%s\n\n", CurrentDirectory());
}

char* CurrentDirectory() {
    char *buf; //it should be pointers
    char *ptr;

    if ((buf = (char *)malloc((size_t)size)) != NULL)
        ptr = getcwd(buf, (size_t)size);

     return ptr;
 }

 void Start() {
    // inputs the commands needed
    char command[size];
    char format[size];

    CurrentDirectory();
    printf("%s>", CurrentDirectory());

    fgets(command, sizeof(command), stdin);
    sscanf(command, "%[^\n]s", format);

    if(command[0] == '\n') {
        Start();
    } else {
        int i;
        // ensures that the commands are key insensitive
        for(i = 0; format[i]; i++){
          format[i] = tolower(format[i]);
        }
        Command(format);
    }
 }

 void CreateInstance() {
    //printf("Microsoft Windows [Version 10.0.15063]\n");
    system("ver"); // check another way for this
    printf("2017 Microsoft Corporation. All rights reserved.\n\n");
 }

int main()
{
    CreateInstance();
    // hidecursor();
    Start();
    return 0;
}
