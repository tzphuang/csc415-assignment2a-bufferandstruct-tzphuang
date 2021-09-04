/**************************************************************
* Class:  CSC-415-02# Fall 2021
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
#include <stdlib.h>
#include <string.h>
#include "assignment2.h"
#include <malloc.h>


int main(int argc, char *argv[]) 
{
	/*
	printf("hello this is hw2\n");
	personalInfo myInfo;
	personalInfo * myInfoPtr;
	int sizeMyInfo = sizeof(myInfo);
	int sizeOfPersonalInfo = sizeof(personalInfo);

	printf("my info size is: %d\n", sizeMyInfo);
	printf("struct personalInfo size is: %d\n", sizeOfPersonalInfo);
	
	//grabbing 128 bytes of memory to store the structure personalInfo so it can be populated
	//personalInfo * myInfoPtr = malloc((sizeof(personalInfo))+1);
	personalInfo * myInfoPtr = malloc(1);

	//size_t malloc_usable_size (myInfoPtr);

	//printf("example malloc size is: %ld\n", sizeof(malloc(129))); only returns the sizeof a ptr ie:8

	printf("update 1\n");
	//printf("malloc_usable_size: %d\n", malloc_usable_size);
	printf("myInfoPtr is size: %ld, at the address of %p\n", sizeof(*myInfoPtr), &myInfoPtr);*/


	//grabbing 128 bytes of memory to store the structure personalInfo so it can be populated
	personalInfo * myInfoPtr = malloc((sizeof(personalInfo)));

	myInfoPtr->firstName = argv[1];
	myInfoPtr->lastName = argv[2];
	//printf("argv[1]: %s, argv[2]: %s\n",myInfoPtr->firstName, myInfoPtr->lastName);
	myInfoPtr->studentID = 915090688;
	myInfoPtr->level = SENIOR;
	myInfoPtr->languages = 262171;
	//printf("student id: %d, student level: %d, languages: %d\n", myInfoPtr->studentID, myInfoPtr->level, myInfoPtr->languages);
	//printf("string length of argv[3]: %ld\n",strlen(argv[3])	);
	strcpy(myInfoPtr->message, argv[3]);
	//printf("Argv[3] copied to message is: %s\n", myInfoPtr->message);

	writePersonalInfo(myInfoPtr);
	/*
	int writeSuccess = writePersonalInfo(myInfoPtr);
	if (0 == writeSuccess){
		printf("Success on writePersonalInfo\n");
	}
	else{
		printf("Fail on writePersonalInfo\n");
	}*/

	/*
	// This is the first attempt at filling & flushing buffer
	char * block = malloc(BLOCK_SIZE);
	const char * nextString;
	do{
		nextString = getNext();

		if(nextString != NULL){
			strcat(block, nextString);
		}

		if(BLOCK_SIZE < strlen(block)){
			//printf("block: %s\n", block);
			commitBlock(block);
			free(block);
			block = malloc(BLOCK_SIZE);
		}
		
	} while(nextString != NULL);*/

	// This is the second attempt at filling & flushing buffer

	char * block = malloc(BLOCK_SIZE);
	const char * nextString = getNext();
	int blockFreeSpace = BLOCK_SIZE;
	int stringLengthNeedingCommit = strlen(nextString);

	int partialLengthToCommit;
	char * partialString = malloc(BLOCK_SIZE);
	//printf("\nblockFreeSpace: %d, stringLengthNeedingCommit %d\n", blockFreeSpace, stringLengthNeedingCommit);

	while(1)//loop until getNext returns NULL
	{
		//if nextString fits inside buffer block, concatenate it to whatever is in block
		if(blockFreeSpace >= stringLengthNeedingCommit){
			printf("inside loop if1 statement\n");
			strncat(block, nextString, stringLengthNeedingCommit);
			nextString = getNext();
			blockFreeSpace = blockFreeSpace - stringLengthNeedingCommit;

			//when there is no new nextString, break out of the loop
			if(nextString == NULL)
			{
				commitBlock(block);
				printf("inside loop break statement\n");
				printf("block message: %s\n\n", block);
				break;
			}

			
			stringLengthNeedingCommit = strlen(nextString);
			printf("block message: %s\n\n", block);
		}
		//if nextString is too big for what is left inside the buffer block
		//take what I need from getString and store it in the buffer
		
		else if(blockFreeSpace < stringLengthNeedingCommit){
			printf("inside loop else if1 statement\n");
			//fills block to full with partial String from nextString
			strncpy(partialString, nextString, blockFreeSpace); 
			strncat(block, partialString, blockFreeSpace); 
			stringLengthNeedingCommit = stringLengthNeedingCommit - blockFreeSpace;
			//reassigning nextString to the beginning of the address of what was not commmited to block
			strncpy(partialString, nextString+blockFreeSpace, stringLengthNeedingCommit); 
			nextString = partialString;
			blockFreeSpace = 0;
			printf("block message: %s\n\n", block);
		}
		//when there is 0 free space left in the buffer flush it
		if(blockFreeSpace == 0){
			printf("inside loop commitBlock statement\n\n");
			commitBlock(block);
			blockFreeSpace = BLOCK_SIZE;
			free(block);
			block = malloc(BLOCK_SIZE);
		}
	}


	checkIt();

	//for every malloc there must be a free
	free(myInfoPtr);
	myInfoPtr = NULL;

	free(block);
	block = NULL;

	free(partialString);
	partialString = NULL;

	return 0;
}
	
