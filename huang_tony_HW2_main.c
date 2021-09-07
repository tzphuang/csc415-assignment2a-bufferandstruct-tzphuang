/**************************************************************
* Class:  CSC-415-02# Fall 2021
* Name:	Tony Huang
* Student ID: 915090688
* GitHub Name: tzphuang
* Project: Assignment 2 – Struct and Buffer
*
* File: huang_tony_HW2_main.c
*
* Description: Main program stores information relevant to myself including 
*			student id#/grade level/name/languages known. Program also takes in
*			string characters to be stored within a block buffer, if the block buffer
*			becomes full the program will flush that data, this will loop until
*			getNext() returns NULL.
**************************************************************/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "assignment2.h"
#include <malloc.h>


int main(int argc, char *argv[]) 
{
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

	char * block = malloc(BLOCK_SIZE);
	const char * nextString = getNext();
	int blockFreeSpace = BLOCK_SIZE; //block size free
	int stringLengthNeedingCommit = strlen(nextString);
	int blockIndex; //used for remembering the block index's next free address

	//int partialLengthToCommit;
	char * partialString = malloc(BLOCK_SIZE);

	while(1)//loop until getNext returns NULL
	{
		blockIndex = BLOCK_SIZE - blockFreeSpace;
		//if nextString fits inside buffer block, concatenate it to whatever is in block
		if(blockFreeSpace >= stringLengthNeedingCommit){
			//printf("inside loop if1 statement\n");
			memcpy(block + blockIndex, nextString, stringLengthNeedingCommit);
			nextString = getNext();
			blockFreeSpace = blockFreeSpace - stringLengthNeedingCommit;

			//when there is no new nextString, break out of the loop
			if(nextString == NULL)
			{
				commitBlock(block);
				//printf("inside loop break statement\n");
				//printf("block message: %s\n\n", block);
				break;
			}

			
			stringLengthNeedingCommit = strlen(nextString);
			//printf("block message: %s\n\n", block);
		}

		//if nextString is too big for what is left inside the buffer block
		//take what I need from getString and store it in the buffer
		else if(blockFreeSpace < stringLengthNeedingCommit){
			//printf("inside loop else if1 statement\n");

			//fills block to full with a partial string from nextString
			memcpy(block+blockIndex, nextString, blockFreeSpace);
			stringLengthNeedingCommit = stringLengthNeedingCommit - blockFreeSpace;

			//set nextString to the beginning of what was not commited to the buffer from partial string
			memcpy(partialString, nextString+blockFreeSpace, stringLengthNeedingCommit);
			nextString = partialString;
			blockFreeSpace = 0;

			//printf("block message2: %s\n\n", block);
		}
		//when there is 0 free space left in the buffer flush it
		if(blockFreeSpace == 0){
			//printf("inside loop commitBlock statement\n\n");
			commitBlock(block);
			blockFreeSpace = BLOCK_SIZE;
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

	//printf("Made it to the end!\n");
	return 0;
}
	
