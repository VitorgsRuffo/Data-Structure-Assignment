#include <stdlib.h>
#include <stdio.h>

//argc: it's the number of string arguments you entered on the command
//line when executing this program.

//argv: it's the string arguments you entered.

//obs: char* == string, so char* argv[] is like an array of strings.
int main (int argc, char* argv[]){

    int i;

    printf("argc = %d\n", argc);

    printf("argv[] content:\n\n");

    for(i = 0; i<argc; i++){
        printf("argv[%d] = %s.\n", i, argv[i]);
    }

    return 0;
}