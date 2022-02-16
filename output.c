/*
FILE: Output.c
Author: Austin Bevacqua
StudentID: 2016289
Unit: Unix and C Programming
Purpose: Provides functions for outputting text the screen for the stringReplace program
Last modified: 19/09/2020
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include "output.h"

/* Function: output
Purpose: Controls the overall "loop" of the program. Calls functions to do comparisons; replacements; and output
Parametres:   argv(A string array containing all command line arguments)
              newStr(A string POINTER which will point to an the string when replacements take place)
              indexes(An array of int which will store the locations of all known valid matches 
              txtCh(A function pointer which points to a text manipulation function.)*/
void output(char** argv, char** newStr, int* indexes, textChange txtCh)
{
    /*Pointer variables which point to command line string arguments. Used to make refering to variables easier*/
    char** originalSentence = &argv[1];
    char** targetWord = &argv[2];
    char** replacementWord = &argv[3];
    
    /*Assign integer values to the command line color values*/
    int colorTar = getColor(argv[4]);
    int colorRep = getColor(argv[5]); 

    /* declariations for integer values */
    int i, matches, diff, ptr; 

    /* We point newStr to an MALLOCED string, as the end of the algorithm frees what newStr is pointing to. 
    If we have no matches, newStr need to be pointing to a malloced string or we will seg fault */
    strcpyAlloc(newStr, *originalSentence);    
    
    /* We calculate the difference between the replaceent and target strings */
    diff = strlen(*replacementWord) - strlen(*targetWord);

    matches = 0;
    i = 0;
    ptr = 0;

    /* The loop continues until there the length of the taregt word is greater than the remaining characters to be matched against */
    while(isFindable(*targetWord, *originalSentence, i) == TRUE)
    {
        /*Although it would make sence to print the head BEFORE any string comparison takes place, we need to update the indexes in real time
            If we want to display all current indexex. Therefore we must print the head after any matching has taken place */
        /* If there is an instance of the target word at the current iteration of the original word */
        if (find(*originalSentence, *targetWord, i) == TRUE) 
        {
            updateIndex(indexes, i, &matches); /* We update the indexes and array to represent where in the string we have found the replacement */
            replace(newStr, *replacementWord, *targetWord, ptr); /*We create a new MALLOCED array, with the replacement word replacing the target word */
            outputHead(*targetWord, *replacementWord, indexes, matches); /*We output the head of the program "x -> y"*/
            outputBody(*newStr, indexes, colorRep, strlen(*replacementWord), diff, txtCh); /*We output the "body", which shows the string replacements in real time*/
            outputTail(ptr, "found", colorRep); /* We output the "^ pointer" underneath the updated string, with the word "found" used to show we found a match */
            i += strlen(*targetWord); /*Our original string ITERATOR is increased by the length of the ORIGINAL TARGET WORD*/
            ptr += strlen(*replacementWord); /*Out DISPLAY ITERATOR/POINTER is increased by the length of the NEW REPLACEMENT WORD */
        }
        else
        {
            /* If there are no matches */
            outputHead(*targetWord, *replacementWord, indexes, matches); 
            outputBody(*newStr, indexes, colorRep, strlen(*replacementWord), diff, txtCh);
            outputTail(ptr, "no matches", colorTar);
            i++; /* If there are no matches, we simply move the string and display iterators up by one */
            ptr++;
        }
    }
    
    /*If the search algorithm is complete, everything is shown to the user again with "END" being displayed under the '^'*/
    outputHead(*targetWord, *replacementWord, indexes, matches);
    outputBody(*newStr, indexes, colorRep, strlen(*replacementWord), diff, txtCh);
    outputTail(ptr, "END", colorRep);

    /*The FINAL screen shown to the user*/
    /*Clears everything, then shows the NEW vs OLD strings, with any matches/replacements shown in a UNDERLINED new color*/
    txtCh = &setUnderline; /* We set the function pointer to UNDERLINE, instead of previously assigned HIGHLIGHT */
    outputBody(*originalSentence, indexes, colorTar, strlen(*targetWord), 0, txtCh);
    outputBody(*newStr, indexes, colorRep, strlen(*replacementWord), diff, txtCh);
}

/* Funcction: outputHead
Purpose: Outputs the top of the CMD output that specefies "Replace: <target> -> <replacement>"
Imports: targetWord (String), replacementWord (String), indexes (ARRAY OF int), match (int)
Last Modified: 19/09/2020 */
void outputHead(char* targetWord, char* replacementWord, int* indexes, int match) {
    
    #ifdef INDEX /* If we have compiled using the INDEX value, we print out all matching indexes */
    outputIndexes(indexes, match);
    #endif
    printf("Replace: %s -> %s\n", targetWord, replacementWord); 
}

/* Funcction: outputIndexes
Purpose: Prints out all current indexes of matches of the original strinng
Imports: indexes (ARRAY OF int), match (int)
Last Modified: 19/09/2020 */
void outputIndexes(int* indexes, int match)
{
    int i;
    printf("Indexes found: ");
    for (i = 0; i < match; i++)
    {
        printf("%d ", *(indexes+i));
    }
    printf("\n");
}

/* Function: outputBody
Purpose: Outputs the updated string with any matches shown in a different color
Parametres: newStr (String we are printing)
              indexes (int* that contains the locations of all "matches"
              matchColor(int that contains the color we will print to the CMD with if a match is found
              changeLen(int that specefied how long we will need to use the different color for if a match is found
              diff (int that speciefies the difference between the TARGET and REPLACEMENT words. 
                        As indexes array shows the indexes for the ORIGINAL STRING, we need to use diff to find the matches in the new string)
              txtCh (textChange: function pointer which specifies what text operation (HIGHLIGHT or UNDERLINE) to use 
Last Modidied: 19/09/2020 */
void outputBody(char* newStr, int* indexes, int matchColor, int changeLen, int diff, textChange txtCh)
{
    int i, j, match;

    match = 0;
    i = 0;
    while((*(newStr+i)) != '\0') { /* Loop continues until we reach the end of the string */
        /*(indexes + match) shows us what index the NEXT MATCH is located at. However, these indexes are for the ORIGINAL STRING. 
        To match these indexes with the new, updated string, we need to get (indexes + match) and sum it will (diff*match); the number
        of the current match, and the difference between the two strings. If this total value is equal to the current iteration (i), then
        a match occurs at the current location */
        if ((*(indexes+match) + diff*match) == i) { 
            /* txtCh points to a function that will perform text manipulation, either HIGHLIGHTING or UNDERLINING */
            txtCh(matchColor);
            for (j = 0; j < changeLen; j++) {
                printf("%c", *(newStr+i)); /* We print out characters until the length of the match */
                i++;
            }
            match++; 
            resetColor(); /* The ANSI terminal output is reset to its default values */
        }
        else {  
        /* If there is NOT a match at the current index, we simply print the character with no text manipulation */
            printf("%c", *(newStr+i));
            i++;
        }
    }
    printf("\n"); /* Once everything is printed, we print a new line */
}

/* Funcction: outputTail
Purpose: Once the sentence/word has been outputted to the screen, underneath is a '^' "pointer" and text underneat/
Imports: iter (int), text (String), color (int)
Last Modified: 19/09/2020 */
void outputTail(int iter, char* text, int color)
{
    whiteSpace(iter); /*We produce whitespace UNTIL where the algorithm has iterated to*/
    printf("^\n"); /* Prints the '^' "pointer"*/

    whiteSpace(iter); 
    setTextColor(color); 
    printf("%s\n", text); /*We then produce an equal amount of whitespace and then the specefied text in a specified color*/

    resetColor(); /*Resets the CMD output color back to default*/
    sleep(1); /*STOPS THE PROGRAM for 1 second as per assessment guildlines*/
    CLEAR; /*clears the terminal window */
}

/* Funcction: whiteSpace
Purpose: Produces a line of whitespace equal to "iter" characters long
Imports: iter (int)
Last Modified: 19/09/2020 */
void whiteSpace(int iter) {
    int i;
    for (i = 0; i < iter; i++) {
        printf(" ");
    }
}
