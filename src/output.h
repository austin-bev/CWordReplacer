/* 
FILE: Output.h
Author: Austin Bevacqua
StudentID: 20162896
Unit: Unix and C Programming
Purpose: A header file for output.c
Last modified: 19/09/2020
*/
#ifndef OUTPUT_H
#define OUTPUT_H
#include "output.h"
#include "colors.h"
#include "stringTools.h"

/* Typedef */
typedef void (*textChange)(int);

/* FUNCTION PROTOTYPES */
/* Output.c */
void output(char**, char**, int*, textChange);
void outputBody(char*, int*, int, int, int, textChange);
void outputHead(char*, char*, int*, int);
void outputIndexes(int*, int);
void outputTail(int, char*, int);
void whiteSpace(int);

/* Macros */
#define CLEAR (system("clear"))

#endif
