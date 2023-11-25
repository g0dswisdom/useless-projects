// notify-send ["your word is.."] "word"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

char* randomWordPicker(char* fileName) {
    FILE *file;
    char* line = NULL;
    ssize_t read;
    size_t len = 0;
    int total = 0;
    int selected = 0;

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Unable to locate file!");
        exit(1);
    }

    while ((read = (int)getline(&line, &len, file)) != -1) {
        total++;
    }

    srand(time(NULL));
    selected = rand() % total -1;

    fseek(file, 0, SEEK_SET);

    int current = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        current++;
        if (current == selected) {
            break;
        }
    }

    fclose(file);
    return line;
}

int main() {
    char* word = randomWordPicker("./words.txt");
    char command[1024];
    sprintf(command, "notify-send 'your word is..' '%s'", word);
    system(command);
    printf("%s", word);
}
