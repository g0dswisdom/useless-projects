#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

/*
    This is a text editor that prompts you to create a new file and then append content to it
*/

int main() {
    FILE *filePtr;
    char fileName[50];
    char answer[3];
    char *input;
    size_t input_size = 1024;

    input = malloc(input_size * sizeof(char));
    if (input == NULL) {
        printf("Couldnt allocate memory to the input");
        return 1;
    }

    SetConsoleTitle("Text Editor");

    printf("Please enter your new file name: ");
    fgets(fileName, sizeof(fileName), stdin);

    fileName[strcspn(fileName, "\n")] = '\0'; // this removes the \n from the filename

    filePtr = fopen(fileName, "w");
    if (filePtr == NULL) {
        printf("Unable to create file");
        return 1;
    }
    //fclose(filePtr);

    printf("Would you like to add contents to it? (y/n): ");
    fgets(answer, sizeof(answer), stdin);

    if (strcmp(answer, "y\n") == 0) { 
        printf("Content to add (Press Ctrl W to exit):\n");

        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        INPUT_RECORD irInBuf;
        DWORD cNumRead;
        DWORD fdwMode, fdwOldMode;
        HANDLE hConsole;

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
                }
            }
        }

        SetConsoleMode(hConsole, fdwOldMode);
        fprintf(filePtr, "%s", input);
        fclose(filePtr);

        free(input);

        printf("Done!");
    } else {
        exit(0);
    }

    return 0;
}
