#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define emptyItem NULL
#define emptyPtr NULL

typedef int BalanceFactor;
typedef char* heapItem;
typedef enum {Left,Right} Direction;

typedef char* bucketItem;
typedef char* treeItem;
typedef char* patientInfo;
typedef char* AVLItem;

typedef struct Tables{

    char* diseases;
    char* countries;

} HashBitMap;

//typedef HashBitMap* hashBitMapPtr;

typedef struct Record{

    patientInfo recordID;
    patientInfo patientFirstName;
    patientInfo patientLastName;
    patientInfo diseaseID;
    patientInfo country;
    patientInfo entryDate;
    patientInfo exitDate;
    struct Record* recordPtr;

} patientRecord;

/*Record of a Patient*/
typedef patientRecord* recordPointer;
//typedef recordPointer* headRecord;


typedef struct Heap{

    int id;
    int counter;
    //struct Heap* PLink;
    struct Heap* RLink;
    struct Heap* LLink;
    heapItem item;

} MaxHeap;

/*Max-Heap*/
typedef MaxHeap* HeapPointer;


typedef struct Tree{

    BalanceFactor BF;
    treeItem item;
    struct Tree* LLink;
    struct Tree* RLink;
    recordPointer patientRecord;

} BalancedTree;


/*Binary Balanced Tree*/
typedef BalancedTree* TreePointer;  //Pointer for the Balanced Binary Tree


typedef struct BucketEntry{

    bucketItem item;
    TreePointer treePtr;
    struct BucketEntry** collision;

} Bucket;

/*Bucket of Hashtable*/
typedef Bucket* BucketPointer;      //Pointer for the bucket of the Hashtable
typedef BucketPointer* BigBucket;   //The real "bucket" structure


typedef struct Entry{

    BigBucket bucket;

} HashEntry;

/*HashTable*/
typedef HashEntry* HashPointer;     //Pointer of a Hashtable
typedef HashPointer* HashTable;     //Pointer pointing into a pointer of the Hashtable (The real Hashtable)