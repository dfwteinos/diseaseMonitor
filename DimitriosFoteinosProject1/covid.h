//#include <stdio.h>
#include "types.h"
//#include <stdlib.h>

/*Hashtable*/
void HTCreate(HashTable* , int , int);                                                                              //Allocating Memory for HashTable
void HashFunction(bucketItem, int* ,int);                                                                           //HashFunction for our HashTable
void BucketCreate(BigBucket*, int );                                                                                //Allocating Memory for each Bucker of the Hashtable
void BucketInsert(BigBucket* , char* ,int, HashBitMap* ,int ,bucketItem,AVLItem,recordPointer* );                   //Real insertion in the buckets
bool BucketCheck(BigBucket* , int* , int ,bucketItem );                                                             //Function for creating a new subBucket or a new group of subBuckets, if it's needed. TRUE if we need a new subBucket, FALSE otherwise
void NewEntryBucket(BigBucket* , bucketItem ,int , AVLItem, recordPointer* );                                       //New Entry function
void SameEntryBucket(BigBucket* ,int ,AVLItem, recordPointer* );                                                    //Same Entry function


/*AVL Trees*/
void AVLCreate(TreePointer*, AVLItem,recordPointer*);                                                               //Creating the Root of the AVL Tree
void AVLInsert(TreePointer*, AVLItem,recordPointer*);                                                               //main function for insertion
void AVLgetMax(int*, int, int);                                                                                     //Get Max between 2 dates
void AVLupdateBF(TreePointer*);                                                                                     //Update Balance Factor at a node
void AVLRightRotation(TreePointer*,int*);                                                                           //Routine for right rotation
void AVLLeftRotation(TreePointer*,int*);                                                                            //Routine for left rotation
Direction AVLSearch(TreePointer*, AVLItem,TreePointer*);                                                            //Going to erase this function
bool AVLisGreater(AVLItem, AVLItem);                                                                                //Compare 2 dates function
BalanceFactor AVLgetBalanceFactor(TreePointer*);                                                                    //Get the Real Balance at a node


/*Max-Heap*/
void HeapCreate(HeapPointer*,heapItem,int*);                                                                        //Function for creating a Max-Heap
void HeapInsert(HeapPointer*,heapItem,int*);                                                                        //Function for increasing the counter at a Node     
void HeapSwap(HeapPointer*,HeapPointer*);
void HeapFindParent(HeapPointer*,int,int,HeapPointer*);
int MaxHeapify(HeapPointer*);                                                                                       //Restoring all the properties
bool HeapCheck(HeapPointer*,int);
int HeapGetHeight(HeapPointer*);


/*Linked List*/
void RecordsInsert(FILE*,recordPointer*, recordPointer*, HashTable*, HashTable*, int, int, int ,HashBitMap*);       //ALl the job is happening here
void RecordsCreate(recordPointer* , recordPointer* );                                                               //Just allocating memory for the First Record Ever

/*BitMap auxiliary functions*/
void BitMapCreate(HashBitMap*,int,int);                                                                             //Creating the BitMap,for knowing if a Bucket is empty or not
void InsertEntryOnHash(HashBitMap*,int,char* );                                                                     //We know which bucket has already an Entry
bool CheckisEmpty(HashBitMap*,int,char*);                                                                           //Check if a specific bucket is empty

/*Intime run Commands*/

void globalDiseaseStats(char*,char*,HashBitMap*,HashTable*,int,int,bool);                                           //1st Command
void getNumberOfDiseases(TreePointer,char*, char*,int*,char*);                                                      //1st Command && 2nd && 7th

void diseaseFrequency(char*,char*,HashTable*,char*,int,int,char*,bool);                                             //2nd Command

void getCurrentPatients(TreePointer,int*);                                                                          //7th Command

void topkFunction(char*,char*,HashTable*,char*,int,int,int,bool);                                                   //3rd Command
void createTopkDiseases(char*,char*,TreePointer,HeapPointer*,int*);                                                 //3rd Command
bool checkSameHeapInsert(HeapPointer*,char*);                                                                       //3rd Command
void printTopKDiseases(HeapPointer*,int,int,bool);                                                                  //3rd Command
void printGivenLevel(HeapPointer*,int*,int,bool);
void getLeftDiseases(HeapPointer*,int**,int,int);
void printLeftDiseases(HeapPointer* ,int,int,int*,bool);
int findMinElement(int**,int);
void createTopkCountries(char* ,char* ,TreePointer ,HeapPointer* ,int* );

/*De-Allocating Memory functions*/

void FreeHeap(HeapPointer*);
void FreeRecords(recordPointer*);
void FreeAVL(TreePointer*);