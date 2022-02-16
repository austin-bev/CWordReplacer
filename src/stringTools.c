/*
FILE: stringTools.c
Author: Austin Bevacqua
StudentID: 2016289
Unit: Unix and C Programming
Purpose: 
Last modified: 19/09/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringTools.h"

/*Function: strToUpper
Purpose: Converts a string to all uppercase values
Parametres: string (String)
Last modified: 19/09/2020 */
void strToUpper(char* string)
{
    int i = 0;
    char curr;

    while ((*(string+i)) != '\0') /* Loop continues until string ends */
    {
        curr = *(string+i);
        if ((curr >= 97) && (curr <= 122)) /*ASCII values for lowercase characters. If a char falls into this range, it is changed*/
        {
            *(string+i) = (curr - 32); /*By subtracting 32 from the ASCII value, we get a character's uppercase equivalent*/
        }
        i++;
    }
}

/*Function: strComp
Purpose: Compares if two strings are identical
Parametres: strOne (String), strTwo (String)
Last modified: 19/09/2020 */
int strComp(char* strOne, char* strTwo)
{
    int similar = TRUE;
    int i = 0;

    while(((strOne[i]!='\0') || (strTwo[i]!='\0')) && (similar == TRUE))
    {
        if(strOne[i]!=strTwo[i])
        {
            similar = FALSE;
        }
        i++;
    }

    return similar;
}


/*Function: find
Purpose: Checks to see if a string is found inside of another string; starting at char i
Imports: original (String), findStr (String), start (int)
Last Modified: 19/09/2020 */
int find(char* original, char* findStr, int start)
{    
    int found, i;

    found = TRUE;
    i = 0;
    do 
    {
        /* Compares the values of both strings at location i. Converts both characters to lowercase for case-insensetive matching */
        if (charToLower(*(original + start + i)) != charToLower(*(findStr + i)))
        {
            found = FALSE; /* If the characters do not have the same ASCII value; the match is labled as FALSE */
        }
        i++;    
    }while((found == TRUE) && (*(findStr + i) != '\0')); /* Loop continues until a mismatch between values has been found or the end of string has been reached */
    return found;
}

/*Function: charToLower
Purpose: Converts a character into its lowercase equivalent
Imports: character (char)
Last Modified: 19/09/2020 */
char charToLower(char character)
{
    char newChar;
    /* If the character lies between the ASCII values for uppercase values */
    if ((character >= 65) && (character <= 90))
    {
        /* We add 32 to find the characters lowercase ASCII equivalent */
        newChar = character + 32;
    }
    else
    {
        newChar = character;
    }
    return newChar;
}

/*Function: strcpyAlloc
Purpose: Creates a MALLOCED copy of a string
Imports: newStr (String pointer), sentence (String)
Last Modified: 19/09/2020 */
void strcpyAlloc(char** newStr, char* sentence)
{
    int senLength = strlen(sentence); /*We find the length of the sentence we are mallocing */
    char* mallocStr = (char*)malloc(sizeof(char*) * (senLength + 1)); /* We malloc a string at length of the sentence + 1 for a null terminator */
    strncpy(mallocStr, sentence, senLength); /*We use strncpy to copy over the values fom the sentence */
    *newStr = mallocStr; /*We set the dereferenced value of the string pointer to point to the new malloced string */
}

/*FunctuinL replace
Purpose: Replaces a set of characters inside of a string to a differennt set of characters
Imports: newStr (String pointer), replacementWord (String), targetWord (String), found (int)
Last Modified: 19/09/2020 */
void replace(char** newStr, char* replacementWord, char* targetWord, int found)
{
    /* We find the length of the new string by taking the CURRENT LENGTH, subtracting the TARGET WORD and adding the REPLACEMENT WORD */
    int newlen = strlen(*newStr) - strlen(targetWord) + strlen(replacementWord);
    /* We find the index of the original string where the target word ends */
    int endLen = found + strlen(targetWord);

    /* We allocate a new string in memory with out calculated length. We +1 to add room for a string terminator*/
    char* updatedStr = (char*)malloc(sizeof(char*) * (newlen +1));

    /* We copy every character from the old array BEFORE the replacement word */
    memcpy(updatedStr, *newStr, found);

    /* We copy the replacement word onto the new string, APPENDING it to the string by making the location (updatedStr + found)*/
    memcpy(updatedStr + found, replacementWord, strlen(replacementWord));

    /* We copy the rest of the old string onto the new string, again APPENDING to finish the new string*/
    memcpy(updatedStr + found + strlen(replacementWord), *newStr + endLen, strlen(*newStr) - endLen);

    free(*newStr); /* newStr is currently pointing at a MALLOCED string. We free this string, as it is outdated and we have made a new, updated one */
    *newStr = updatedStr; /*We set out "newStr" pointer to point to the new string */
}

/*Function: updateIndex
Purpose: Updates the "found" variables by reference
Import: indexes (ARRAY OF int), found (int), matches (POINTER TO int)
Last Modified: 19/09/2020*/
void updateIndex(int* indexes, int found, int *matches) 
{
    /* We update both values by reference */
    *(indexes+*matches)= found;
    *matches += 1;
}

/*Function: isFindable
Purpose:    Calculates whether any more matches of a word can be found in a string from starting point i. 
            Returns FALSE if there are not enough remaining characters to find another instance of targetWord 
Imports: targetWord (String), originalSentence (String), i (int)
Last Modified: 19/09/2020*/
int isFindable(char* targetWord, char* originalSentence, int i)
{
    int value = FALSE;
    /* (i + strlen(targetWord) works out how many characters are needed to find a replacement at the current index. 
        If this is smaller than the number of currenr characters in the sentence strlen(originalSentence), no matches can be found and FALSE is returned */
    if (i + strlen(targetWord) <= strlen(originalSentence)) 
    {
        value = TRUE;
    }
    return value;
}
