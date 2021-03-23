#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define SIZE 1000

enum {
    OK = EXIT_SUCCESS,
    FAIL = 1,
};



int findStr(char *str, char *line){
    int i = 0;
    while (line[i] != '\0') {
        if (line[i] == str[0]) {
            int counter = 0;
            while (line[counter] == line[counter + i]) {
                counter++;
            }
            return (str[counter] == '\n' || str[counter] == '\0' ? 1 : 0);
        }
        i++;
    }
    return 0;
}


int main(int argc, char* argv[]) {
    // Jestlize se program spatne zavola -> ukonci se
    if (argc > 3){
        fprintf(stderr, "Too many arguments\n");
        return FAIL;
    }
    if (argc < 3){
        fprintf(stderr, "Lack of arguments\n");
        return FAIL;
    }


    char *pattern = argv[1];
    char *file = argv[2];
    FILE * fileP;
    fileP = fopen(file, "r");
    char str[SIZE];


    if (fileP == NULL ) {
        fprintf(stderr,"File failed to open.\n");
        return FAIL;
    } else {
        printf("The file is now opened.\n") ;
        while(fgets (str, SIZE, fileP) != NULL )
        {
            if (findStr(pattern, str) == 1){
                printf("%s",str);
                return OK;
            }
        }
        fclose(fileP) ;
        printf("\nData successfully read from\n");

    }
    return OK;
}
