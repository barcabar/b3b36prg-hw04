#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define SIZE 1000

enum {
    OK = EXIT_SUCCESS,
    FAIL = 1,
};


size_t strLen(const char* str);
int findStr(char *pattern,char *line);

int main(int argc, char* argv[]) {

    // Jestlize se program spatne zavola,
    // ukonci se
    if (argc > 3){
        fprintf(stderr, "Too many arguments\n");
        return FAIL;
    } else if (argc < 3){
        fprintf(stderr, "Lack of arguments\n");
        return FAIL;

        // kdyz je spravny pocet argumentu
        // program pokracuje
    } else {
        char *pattern = argv[1]; // hledane slovo
        FILE * fileP;
        char *file = argv[2];
        const char *mode = "r"; // cteni
        fileP = fopen(file, mode);
        char str[SIZE];


        if (!(fileP == NULL)) {
            while (fgets(str, SIZE, fileP) != NULL) {
                if (findStr(pattern, str) == 1) {
                    printf("%s", str);
                    return OK;
                }
            }
            fclose(fileP);

        } else {
            fprintf(stderr, "Failed to open.\n");
            return FAIL;
        }
        free(fileP);
        free(file);
        free(pattern);
    }

    return OK;
}


size_t strLen(const char* str){
    int size = 0;
    while (str[size++]);
    return size;
}


// funkce vraci 1
// pokud je shoda
int findStr(char *pattern, char *line) {
    for (int i = 0; i < strLen(line); i++) {
        if (line[i] != pattern[0]) {
            i++;
        } else {
            int size = 0;
            while (line[size + i] == pattern[size]) {
                size++;
            }
            return ((pattern[size] == '\n' || pattern[size] == '\0') ? 1 : 0);
        }
    }
    return 0;
}


