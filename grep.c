#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define SIZE 1000
#define PRE 11
#define PO 6

enum {
    OK = EXIT_SUCCESS,
    FAIL = 1,
};

// moje funkce
size_t strLen(const char* str);
int findStr(char *pattern,char *line);
int highlight(char *str, char *line);



int main(int argc, char *argv[]) {
    // Jestlize se program spatne zavola,
    // ukonci se
    if (argc > 4) {
        fprintf(stderr, "Too many arguments\n");
        return FAIL;
    } else if (argc == 4) {
        FILE *fileP;
        char str[SIZE];
        char *pattern = argv[2];
        char *file = argv[3];
        char *mode = "r";
        fileP = fopen(file, mode);
        if (fileP == NULL) {
            fprintf(stderr, "Failed to open.\n");
        }
        while (fgets(str, SIZE, fileP) != NULL) {
            return ((highlight(pattern, str) == 1) ? OK : FAIL);
        }
            fclose(fileP);

    } else if (argc == 3) {
        // povinne zadani
        // kdyz je spravny pocet argumentu
        // program pokracuje
        char *pattern = argv[1];
        FILE *fileP;
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
        // uvolneni pameti
        free(fileP);
        free(file);
        free(pattern);
    } else if (argc == 2) {
        char *word = argv[1];
        char str[SIZE];
        while (fgets(str, SIZE, stdin) != NULL) {
            return (findStr(word, str) ? OK : FAIL);

        }
    } else if (argc < 2) {
        fprintf(stderr, "Lack of arguments\n");
        return FAIL;

    }
    return OK;
}




// spocitani poctu prvku
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


int highlight(char *str, char *line){
    int b = 0;
    int i = 0;
    int ret = 0;
    char target[SIZE];
    char pred[] = "\033[01;31m\033[K";
    char po[] = "\033[m\033[K";
    while (!(line[i] == '\0' || line[i] == '\n' || i >= SIZE)) {
        target[b] = line[i];
        if (line[i] != str[0]) {}
        else {
            int iback = i, bback = b;
            int a = 0;
            for (int c = 0; c < PRE; c++) {
                target[b + c] = pred[c];
            }
            b += PRE;
            while(line[a + i] == str[a]) {
                target[b + a] = line[a + i];
                a++;
            }
            b += a;

            if (str[a] == '\n' || str[a] == '\0') {
                for (int c = 0; c < PO; c++) {
                    target[b + c] = po[c];
                }
                b += PO;
                b -= 1;
                i -= 1;
                i += a;
                ret = 1;
            } else {
                i = iback;
                b = bback;
                target[b] = line[i];
            }
        }
        b++;
        i++;
    }
    if (ret) {
        target[b] = '\0';
        printf("%s\n", target);
    }
    return 1;
}


