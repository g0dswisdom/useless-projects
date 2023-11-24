#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

/*
    This is a text editor that prompts you to create a new file and then append content to it
    This is not meant to be used at all, just a fun project
    SHORTCUTS: 
        - CTRL + W: writes and saves file
        - CTRL + X: exits without saving file
    COMMAND LINE ARGUMENTS:
        - No arguments: Prompts you to create a new file or append content to one
        - --create <fileName>: Creates a file and lets you add content to it
        - --write <fileName>: Adds content to an existing file
*/

char* console(char *input) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD irInBuf;
    DWORD cNumRead;
    DWORD fdwMode, fdwOldMode;
    HANDLE hConsole;
    int cursorPos = 0;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hConsole, &fdwOldMode);
    fdwMode = ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT;
    SetConsoleMode(hConsole, fdwMode);

    while (1) {
        ReadConsoleInput(hStdin, &irInBuf, 1, &cNumRead);
        if (cNumRead != 0 && irInBuf.EventType == KEY_EVENT && irInBuf.Event.KeyEvent.bKeyDown) {
            if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
                putchar('\n');
                strcat(input, "\n");
            } else if (irInBuf.Event.KeyEvent.wVirtualKeyCode == 'W' && irInBuf.Event.KeyEvent.dwControlKeyState & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED)) {
                int msgBox = MessageBox(NULL, "Are you sure you want to save and exit?", "Text Editor", MB_YESNO | MB_ICONQUESTION);
                if (msgBox == IDYES) {
                    break;
                } else if (msgBox == IDNO) {
                    continue;
                }
            } else if (isprint(irInBuf.Event.KeyEvent.uChar.AsciiChar)) {
                putchar(irInBuf.Event.KeyEvent.uChar.AsciiChar);
                strncat(input, &(irInBuf.Event.KeyEvent.uChar.AsciiChar), 1);
            } else if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_BACK) {
                putchar('\b');
                putchar(' ');
                putchar('\b');
                input[strlen(input) - 1] = '\0';
            } else if (irInBuf.Event.KeyEvent.wVirtualKeyCode == 'X' && irInBuf.Event.KeyEvent.dwControlKeyState & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED)) {
                int msgBox = MessageBox(NULL, "Are you sure you want to quit without saving?", "Text Editor", MB_YESNO | MB_ICONQUESTION);
                if (msgBox == IDYES) {
                    exit(0);
                } else if (msgBox == IDNO) {
                    continue;
                }
            }
        }
    }

    SetConsoleMode(hConsole, fdwOldMode);
    return input;
}

void createFile(char* fileName, char *input) {
    FILE *file;
    file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Unable to create file");
        free(input);
        exit(0);
    }
    fprintf(file, "%s", input);
    fclose(file);

    free(input);
}

void appendToFile(char* fileName, char *input) {
    FILE *file;
    file = fopen(fileName, "a");
    if (file == NULL) {
        printf("Unable to locate file");
        free(input);
        exit(0);
    }
    fseek(file, 0, SEEK_SET);
    fputs(input, file);
    fclose(file);

    free(input);
}

int main(int argc, char *argv[]) {
    FILE *filePtr;
    char fileName[100];
    char answer[3], firstAnswer[3];
    char *input = NULL;
    size_t input_size = 1024;

    input = malloc(input_size * sizeof(char));
    if (input == NULL) {
        printf("Couldnt allocate memory to the input");
        return 1;
    }
    memset(input, 0, input_size);

    SetConsoleTitle("Text Editor");

    if (argc > 1 && strcmp(argv[1], "--create") == 0) {
        system("cls");
        SetConsoleTitle("Add contents to file");

        input = console(input);
        createFile(argv[2], input);
        free(input);
    } else if (argc > 1 && strcmp(argv[1], "--write") == 0) {
        system("cls");
        SetConsoleTitle("Add contents to file");

        input = console(input);
        appendToFile(argv[2], input);
        free(input);
    } else {
        printf("Would you like to open an existing file or create a new one? (1/2): ");
        fgets(firstAnswer, sizeof(firstAnswer), stdin); 

        firstAnswer[strcspn(firstAnswer, "\n")] = '\0';

        if (strcmp(firstAnswer, "1") == 0) { 
            printf("Please enter your file path: ");

            fgets(fileName, sizeof(fileName), stdin);
            fileName[strcspn(fileName, "\n")] = '\0';

            system("cls");
            SetConsoleTitle("Add contents to file");

            input = console(input);
            appendToFile(fileName, input);

            free(input);
        } else if (strcmp(firstAnswer, "2") == 0) {
            printf("Please enter your new file name: ");
            fgets(fileName, sizeof(fileName), stdin);

            fileName[strcspn(fileName, "\n")] = '\0'; 
            system("cls");
            SetConsoleTitle("Add contents to file");

            input = console(input);
            createFile(fileName, input);

            free(input);
        } else {
            printf("??");
        }
    }

    return 0;
}
