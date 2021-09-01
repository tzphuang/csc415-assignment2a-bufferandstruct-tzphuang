/**************************************************************
* Class:  CSC-415-1# Fall 2021
* Name:	Tony Huang
* Student ID: 915090688
* GitHub Name: tzphuang
* Project: Assignment 2 – Struct and Buffer
*
* File: huang_tony_HW2_main.c
*
* Description: 
*
**************************************************************/
#include <stdio.h> 
#include <string.h>
#include "assignment2.h"


int main(int argc, char *argv[]) 
{
	printf("hello this is hw2\n");
	
	personalInfo myInfo;
	personalInfo * myInfoPtr;
	int sizeMyInfo = sizeof(myInfo);

	printf("my info size is: %d\n", sizeMyInfo);

	return 0;
}
	
