/* 
FILE: StringTools.h
Author: Austin Bevacqua
StudentID: 20162896
Unit: Unix and C Programming
Purpose: A header file for stringTools.c
Last modified: 19/09/2020
*/

/* Header Guard */
#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H

#include "stringTools.h"

/* Constants */
#define TRUE 0
#define FALSE 1

/* Functuon Declariations */
void strToUpper(char*);
int strComp(char*, char*);
int find(char*, char*, int);
void strcpyAlloc(char**, char*);
void replace(char**, char*, char*, int);
void updateIndex(int*, int, int*); 
int isFindable(char*, char*, int);
char charToLower(char);

#endif
