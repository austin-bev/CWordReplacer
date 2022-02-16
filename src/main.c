/*
FILE: Main.c
Author: Austin Bevacqua
StudentID: 2016289
Unit: Unix and C Programming
Purpose: The entry point of the stringReplace program. Verifies if arguments are valid and declaries some vaiables. 
Last modified: 19/09/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char* argv[])
{
    /* If there are an incorrect number of arguments, the program ends and notified the user*/
    if(argc != 6) 
    {
        printf("Format: ./strnrpl <\"original\"> <\"target\"> <\"replacement\"> <target color> <replacement color>");
    }
    else 
    {
        /*We create a functon pointer to the setBgColor function. */
        textChange txtCh; 
   
        /*Create a POINTER to a STRING called newArray. This will store the location of the final modified string*/
        char* newStr = argv[1];

        /*Crate an malloc'd array of INT which will store the locations of all found matches in the string*/
        int* indexes = (int*)malloc(sizeof(int) * strlen(newStr));

        /* Changes the function pointer to change the BACKGROUND COLOR, which will initially be used by the algorithm */
        txtCh = &setBgColor;     
        /* We pass all variables to the output function, which will run finding and replacing algorithms as well as displaying information to the screen */
        output(argv, &newStr, indexes, txtCh);


        free(indexes);  /*We then FREE the malloc'd array, as it us using system memory*/ 
        free(newStr); /* The output function changes newStr to be pointing to a malloced array, so it must be freed from memory */
    }
    return 0;   
}
