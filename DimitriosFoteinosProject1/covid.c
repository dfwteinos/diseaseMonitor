#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include "covid.h"
#include <math.h>       //Don't forget -lm!
#include <limits.h>

void HTCreate( HashTable* HTPointer,int tableSize,int bucketSize  ){

    (*HTPointer)=malloc(sizeof(HashPointer)*tableSize);

    //(*HTPointer[i]==NULL) for every pointer
    
    //TODO FIXME (Don't waste your memory)
    
    //This is going to be on HTInsert

    for (int i=0; i<tableSize; i++){

        (*HTPointer)[i]=malloc(sizeof(HashEntry));

        //BucketCreate( (&(*HTPointer)[i]->bucket) , bucketSize, i );

    }

    return;
}

void HashFunction(bucketItem item, int *index,int tableSize){

    int hash=0;
    int PrimeN=127;

    if (item!=NULL){
        for(int i=0; i<strlen(item); i++){

            hash=( PrimeN*hash+(unsigned int)item[i] )%tableSize ;
        }
    }

    (*index)=hash;
    return;
}

void BucketCreate(BigBucket* bucket,int bucketSize){

    //(*bucket)=malloc(sizeof(BucketPointer)*bucketSize);
    (*bucket)=calloc(sizeof(BucketPointer),bucketSize);

    for(int j=0; j<bucketSize; j++){

        //(*bucket)[j]=emptyPtr;          //WhyNot?
        //(*bucket)[j]->item=NULL;
        //(*bucket)[j]->treePtr=emptyPtr;
        //(*bucket)[j]->collision=emptyPtr;

        /*(*bucket)[j]=malloc(sizeof(Bucket));
        (*bucket)[j]->item="Hands";
        AVLCreate( (&(*bucket)[j]->treePtr));
        //(*bucket)[j]->treePtr=emptyPtr;
        (*bucket)[j]->collision=emptyPtr;*/

  }

}

void BucketInsert(BigBucket* bucket,char* type,int bucketNumber, HashBitMap* BitMap,int bucketSize,bucketItem item,AVLItem treeItem,recordPointer* patientEntry ){

    /*if( (CheckisEmpty( BitMap, bucketNumber, type)==true ) ){                   //Check if the spesific bucket is empty.If it is,then allocate memory for it

        BucketCreate(bucket, bucketSize);
    }*/

    bool existing=false;
    BigBucket currentCollision;
    
    BigBucket previousCollision=NULL;
    
    if (*bucket!=NULL){
        if ( (*bucket)[bucketSize-1]!=NULL ){
            
            for(int i=0; i<bucketSize; i++){
            
                if ( strcmp( (*bucket)[i]->item ,item)==0) {
                    
                    existing=true;
                    break;
                    
                }

            }    

            if (existing==false){
            
                /*BigBucket*/ currentCollision=(*bucket)[bucketSize-1]->collision;

                while(currentCollision!=NULL){

                    for(int i=0; i<bucketSize; i++){
            
                        //previousCollision[i]=currentCollision[i];

                        if (currentCollision[i]!=NULL){
                            if ( strcmp( currentCollision[i]->item ,item)==0) {
                    
                                existing=true;
                                break;
                            }
                        }   
                    }

                    if (existing==true) break;

                    if( currentCollision[bucketSize-1]!=NULL) {

                        previousCollision=currentCollision;
                        currentCollision=currentCollision[bucketSize-1]->collision;

                    }

                    else break;
                    
                }

            }

            //currentCollision=currentCollision[bucketSize-1]->collision

            //else BucketCreate( (&(*bucket)[bucketSize-1]->collision) , bucketSize);
            //BucketCreate( (&(*bucket)[bucketSize-1]->collision) , bucketSize);
            
            //return;

            if(currentCollision==NULL && existing==false){

                if( bucketSize==1 && previousCollision!=NULL ){
                
                    BucketCreate(  &(previousCollision[bucketSize-1]->collision),bucketSize );

                }

                else BucketCreate( (&(*bucket)[bucketSize-1]->collision) , bucketSize);
                //BucketCreate( (&currentCollision),bucketSize );

            }
        
        }

    }

    else {

        BucketCreate( bucket , bucketSize);

    }

    int subBucket;
    BigBucket groupsOfBuckets=(*bucket);

    if( BucketCheck(&groupsOfBuckets,&subBucket,bucketSize,item)==true){        //Check which subBucket is free or ready to traverse it

        NewEntryBucket(&groupsOfBuckets,item,subBucket,treeItem,patientEntry);

    }                   

    else {

        SameEntryBucket(&groupsOfBuckets,subBucket,treeItem,patientEntry);

    }

    //NewEntryBucket(&groupsOfBuckets,item,subBucket,treeItem,patientEntry);

    //SameEntryBucket(&groupsOfBuckets,subBucket,treeItem,patientEntry);

    /*(*groupsOfBuckets)[subBucket]=malloc(sizeof(Bucket));
    //(*groupsOfBuckets)[subBucket]->item=malloc(sizeof(char));                 //Do I need to?
    strcpy( (*groupsOfBuckets)[subBucket]->item,item );
    AVLCreate( (&(*groupsOfBuckets)[subBucket]->treePtr) );
    //(*bucket)[j]->treePtr=emptyPtr;
    (*groupsOfBuckets)[subBucket]->collision=emptyPtr;*/

}

void SameEntryBucket(BigBucket* bucket,int subBucket,AVLItem treeItem,recordPointer* patientEntry ){

    //TreePointer AVLPointer;
    AVLInsert( (&(*bucket)[subBucket]->treePtr) , treeItem , patientEntry);                                                                              //main function for insertion

}

void NewEntryBucket(BigBucket* bucket, bucketItem item,int subBucket, AVLItem itemAVL ,recordPointer* patientEntry){

    (*bucket)[subBucket]=malloc(sizeof(Bucket));
    (*bucket)[subBucket]->item=malloc(sizeof(char));
    strcpy( (*bucket)[subBucket]->item,item );
    //AVLCreate( (&(*bucket)[subBucket]->treePtr), treeItem, patientEntry);
    (*bucket)[subBucket]->treePtr=emptyPtr;                                     //Don't know if it's needed(?)
    AVLInsert( (&(*bucket)[subBucket]->treePtr), itemAVL, patientEntry);                                                        
    (*bucket)[subBucket]->collision=NULL;

}

bool BucketCheck(BigBucket* bucket, int* subBucket, int bucketSize,bucketItem item ){

    bool check;
    int i;
    bool full=true;

    while( (*bucket)!=NULL && full==true ){

        for(i=0; i<bucketSize; i++){

            if( (*bucket)[i]==NULL /*|| strcmp( ( (*bucket)[i]->item),item  )==0*/  )  {                //If a bucket is NULL or if we have seen it again
                *subBucket=i;
                full=false;
                check=true;
                break;
            }

            if ( (*bucket)[i]!=NULL ){

                if ( strcmp( (*bucket)[i]->item,item)==0  ){
                    
                    *subBucket=i;
                    check=false;
                    full=false;
                    break;

                }


            }

        
        }

        if (full==true){

            if(  (*bucket)[bucketSize-1]->collision==NULL && ( (*bucket)[bucketSize-1]->item!=emptyItem)  ){    //If the group of buckets is full
                                                                                                                //Then allocate a new one
                BigBucket* collisionBucket;
                //(*collisionBucket)=(&(*bucket)[bucketSize-1]->collision);
                
                BucketCreate( collisionBucket,bucketSize  );
                (*bucket)[bucketSize-1]->collision=(*collisionBucket);
                //BucketCreate( (*bucket)[bucketSize-1]->collision , bucketSize );
                //(*bucket)=(*bucket)[bucketSize-1]->collision;
            }

            //(*bucket)=(*collisionBucket);
            (*bucket)=(*bucket)[bucketSize-1]->collision;           //In this occasion,we move to the next group of buckets
        }
    }

    if (check==true) return true;
    else return false;


}

void HeapCreate(HeapPointer* heapPtr,heapItem item,int* id){

    (*id)++;
    (*heapPtr)=malloc(sizeof(MaxHeap));
    (*heapPtr)->RLink=emptyPtr;
    (*heapPtr)->LLink=emptyPtr;
    (*heapPtr)->item=item;
    (*heapPtr)->id=(*id);
    (*heapPtr)->counter=1;

}

int MaxHeapify(HeapPointer* heapPtr){


    if( (*heapPtr)==NULL ) {

        return 0;
    }

    if (  (*heapPtr)->RLink==NULL && (*heapPtr)->LLink==NULL ){

        return (*heapPtr)->counter;

    }

    int left;
    int right;

    left=MaxHeapify( (&(*heapPtr)->LLink)) ;
    right=MaxHeapify( (&(*heapPtr)->RLink) );

    if (right>left && right> (*heapPtr)->counter  ) {

        HeapSwap( heapPtr, (&(*heapPtr)->RLink) );
        return right;

    }

    if ( right < left && left > (*heapPtr)->counter ) {                                       

        HeapSwap( heapPtr, (&(*heapPtr)->LLink) );
        return left;  
    }

}

bool HeapCheck(HeapPointer* root, int rootItem){

    bool flagLeft=true;
    bool flagRight=true;

    if ( (*root)->RLink==NULL || (*root)->LLink==NULL  ){

        if ( ((*root)->LLink!=NULL) ){

            if ( rootItem > (*root)->LLink->counter ) {

                flagLeft=HeapCheck( (&(*root)->LLink) , (*root)->LLink->counter );
                return flagLeft;

            }

            else return false;              //It's not heap!
        
        }

        else return true;                   //If it's a leaf,then we have nothing more to examinate: return true

    }
    
    if( (rootItem >= ((*root)->LLink->counter)) && (rootItem >= ((*root)->RLink->counter)) ){

        flagLeft=HeapCheck( (&(*root)->LLink) , (*root)->LLink->counter );
        flagRight=HeapCheck( (&(*root)->RLink) , (*root)->RLink->counter );

        if (flagLeft==false || flagRight==false) return false;
        else return true;

    }

    else return false;

}


void HeapSwap(HeapPointer* small,HeapPointer* big){

    HeapPointer swapPtr=malloc(sizeof(MaxHeap));
    
    swapPtr->counter=(*big)->counter;
    swapPtr->item=(*big)->item;

    (*big)->counter=(*small)->counter ;
    (*big)->item=(*small)->item;

    (*small)->counter = swapPtr->counter;
    (*small)->item= swapPtr->item;

    free(swapPtr);

}

int HeapGetHeight(HeapPointer* root){

    if ( (*root)==NULL ){
        return 0;
    }

    int LeftH=HeapGetHeight( (&(*root)->LLink)   );
    int RightH=HeapGetHeight( (&(*root)->RLink)  );

    if (LeftH>RightH) return LeftH+1;

    else return RightH+1;

}

void HeapInsert(HeapPointer* heapPtr ,heapItem item,int* id){                                                                                    //Function for increasing the counter at a Node     

    if ( (*heapPtr)==NULL ){

        HeapCreate( heapPtr, item , id);
        return;

    }
    
    int totalEntries;
    int height;
    height=HeapGetHeight(heapPtr);

    totalEntries=(int)( pow(2,height) -1);

    if (totalEntries==(*id) ) {                         //If our tree is already Full
    
        HeapPointer left;
        left=(*heapPtr);

        while( (left->LLink)!=NULL ){ 

            left=left->LLink;
        }

        HeapCreate( (&left->LLink) , item , id );

    }

    else {

        HeapPointer root;
        HeapPointer parent=NULL;
        HeapPointer realParent=NULL;
        int parentID;

        root=(*heapPtr);
        parentID=(((*id)+1)/2);

        for(int i=1; i<height; i++){
            HeapFindParent(&root,parentID,i,&parent);

            if(parent!=NULL){
                realParent=parent;
            }
        }

        if( realParent->LLink==NULL  ){
            HeapCreate( &(realParent->LLink), item, id );
        }

        else {

            HeapCreate( &(realParent->RLink), item, id );

        }
    
    }

}

void HeapFindParent(HeapPointer* root,int id,int height,HeapPointer* parent){

    if ( (*root)==NULL  ) {
        
        (*parent)=NULL;
        return;

    }

    if( height==1 ){

        if( ( (*root)->id)==id ){

            (*parent)=(*root);
        }

        else {
    
            (*parent)=NULL;
            return;
        }
    
    }

    else if( height>1 ){

        HeapFindParent( (&(*root)->LLink) ,id,height-1, parent );
        if ( (*parent)!=NULL) return ;

        HeapFindParent( (&(*root)->RLink) ,id,height-1, parent );
        if ( (*parent)!=NULL) return;
    }
}



void AVLCreate( TreePointer* treePointer, AVLItem item,recordPointer* patientEntry ){

    (*treePointer)=malloc(sizeof(BalancedTree));
    (*treePointer)->BF=1;                               //All nodes have initially balance factor equal to 1
    (*treePointer)->item=malloc(sizeof(11));            //Is this needed? We'll see
    strcpy( (*treePointer)->item, item )   ;            //Maybe I need to allocate memory(?));
    
    //(*treePointer)->item="DDMMYYYY";                  //Maybe I need to allocate memory(?)
    
    (*treePointer)->LLink=emptyPtr;
    (*treePointer)->RLink=emptyPtr;
    (*treePointer)->patientRecord=(*patientEntry);

}

void AVLInsert( TreePointer* root, AVLItem item, recordPointer* patientEntry ){

    BalanceFactor FinalBalance;
    Direction pointer;
    TreePointer newEntry;
    newEntry=(*root);

    bool way;

    if ( (*root)==NULL ){

        AVLCreate( root , item, patientEntry);                                                       
        return;
    }

    //pointer=AVLSearch(entry,item,&newEntry);
    way=AVLisGreater( item, (*root)->item  );  

    if(way==0) pointer=Left;
    else pointer=Right;

    if (pointer==Left) AVLInsert( &(newEntry->LLink) , item , patientEntry );

    else AVLInsert( &(newEntry->RLink) , item , patientEntry );

    AVLupdateBF(&newEntry);

    FinalBalance= (AVLgetBalanceFactor( &(newEntry->LLink) ))  - (AVLgetBalanceFactor( &(newEntry->RLink) ));

    /*Depending on Final Balance,there are 4 cases*/

    /*Left-Left => Single Right Rotation*/

    if (FinalBalance > 1 && (AVLisGreater(item, newEntry->LLink->item   ) )==false  ){

        AVLRightRotation(&newEntry,&FinalBalance);

    }

    /*Right-Right => Single Left Rotation*/

    if ( FinalBalance < -1 && ( AVLisGreater( item, newEntry->RLink->item  ) )==true){

        AVLLeftRotation(&newEntry,&FinalBalance);

    }

    /*Right-Left => Double: Right & Left Rotation*/

    if( FinalBalance < -1 && ( AVLisGreater( item, newEntry->RLink->item ) )==false)  {

        AVLRightRotation(&(newEntry->RLink), &FinalBalance );
        AVLLeftRotation(&newEntry,&FinalBalance );
    }

    /*Left-Right => Double: Left & Right Rotation*/

    if( FinalBalance > 1 && ( AVLisGreater( item, newEntry->LLink->item) )==true ){

        AVLLeftRotation(&(newEntry->LLink),&FinalBalance );
        AVLRightRotation(&newEntry,&FinalBalance);
        
    }

    (*root)=newEntry;

    return;

}

void AVLupdateBF(TreePointer* treePtr){

    int maxBF;
    AVLgetMax(&maxBF, ( AVLgetBalanceFactor( (&(*treePtr)->LLink)) ) , ( AVLgetBalanceFactor ( (&(*treePtr)->RLink)) ));   
    
    (*treePtr)->BF=1+maxBF;

} 


bool AVLisGreater( AVLItem itemEntry , AVLItem itemCompare ){

    //char *x2="25-1-2019";
    //char* x1="12-02-2020";
    //char* str=malloc(sizeof(char)*20);
    char str[30];
    
    
    strcpy(str,itemEntry);
    //strcpy(str,x2);

    int sumEntry;
    int sumCompare;
    int* number;
    int* number2;
    number=malloc(sizeof(int)*3);
    number2=malloc(sizeof(int)*3);
    int i=0;
   
    //char str[80] = "This is - www.tutorialspoint.com - website";
    const char s[2] = "-";
   
    //const char* s="-";
    char *token;
    char *token2;
   
    //get the first token 
    token = strtok(str, s);
   
    /* walk through other tokens */
    while( token != NULL ) {
        //printf( "string is: %s\n", token );

        number[i]=strtol(token,NULL,10);
        //printf("integer is: %d\n",number[i]);

        i++;
        token = strtok(NULL, s);
    }

    //sumEntry=number[0]+(number[1]*100)+(number[2]*1000);
    //sumEntry=number[0]+(number[1]*100)+(number[2]*1000);

    i=0;
    strcpy(str,itemCompare);
    token2 = strtok(str,s);

    while( token2 != NULL ) {
        //printf( "string is: %s\n", token2 );

        number2[i]=strtol(token2,NULL,10);
        //printf("integer is: %d\n",number2[i]);

        i++;
        token2 = strtok(NULL, s);
    }

    sumEntry=number[0]+(number[1]*100)+(number[2]*10000);

    sumCompare=number2[0]+(number2[1]*100)+(number2[2]*10000);

    for(int j=0; j<3; j++){

        //printf("%d\n",number[j]);
        //printf("%d\n",number2[j]);

    }

    free(number);
    free(number2);
    //free(str);

    number=NULL;
    number2=NULL;
    //str=NULL;

    if (sumEntry>=sumCompare) return 1;
    else return 0;
    
    /*int sumEntry,sumCompare;

    int i=0;
    int* numberEntry;
    int* numberCompare;
    
    char* token1;
    char* token2;

    const char s[2]="-";
    
    char stringEntry[11];
    char stringCompare[11];

    strcpy(stringEntry,itemEntry);
    strcpy(stringCompare,itemCompare);

    numberEntry=malloc(sizeof(int)*3);
    numberCompare=malloc(sizeof(int)*3);
   
    token1 = strtok(stringEntry, s);
    //token2 = strtok(stringCompare,s);
   
    while( token1!=NULL && token2!=NULL ){

        numberEntry[i]=strtol(token1,NULL,10);
        numberCompare[i]=strtol(token2,NULL,10);
        i++;
        token1=strtok(NULL,s);
        token2=strtok(NULL,s);

    }

    sumEntry=numberEntry[0] + (numberEntry[1]*100) + (numberEntry[2]*1000);
    sumCompare=numberCompare[0] + (numberCompare[1]*100) + (numberCompare[2]*1000);

    free(numberEntry);
    free(numberCompare);

    if( sumEntry>sumCompare) return true;
    else return false; */

}

Direction AVLSearch(TreePointer* entry, AVLItem item, TreePointer* newEntry){

    Direction pointer;
    TreePointer NextNode;
    NextNode=(*entry);

    while( NextNode!=NULL ) {

        (*newEntry)=NextNode;
        if ( (AVLisGreater( item , NextNode->item ) )==true) {
         
            NextNode=NextNode->RLink;
            pointer=Right;
        }

        else {
            
            NextNode=NextNode->LLink;
            pointer=Left;
        }
    }

    if ( pointer==Right ) return Right;
    else return Left;

}

BalanceFactor AVLgetBalanceFactor(TreePointer* treeNode){

    if ( (*treeNode)!=NULL ) return (*treeNode)->BF;
    else return 0;

}

void AVLgetMax(int* BF, int BF1 , int BF2){

    if( (BF1)>(BF2) ) (*BF)=(BF1);
    else (*BF)=(BF2);

}

void AVLRightRotation(TreePointer* treePtr,int* FinalBalance){

    TreePointer newRoot;
    TreePointer subTree;

    newRoot=(*treePtr)->LLink;
    subTree=newRoot->RLink;

    /*Here's the actual Rotation*/

    newRoot->RLink=(*treePtr);
    (*treePtr)->LLink=subTree;

    /*Updating the Balance Factor*/

    AVLupdateBF(treePtr);
    AVLupdateBF(&newRoot);

    (*treePtr)=newRoot;
    (*FinalBalance)= (AVLgetBalanceFactor( &( (*treePtr)->LLink) ))  - (AVLgetBalanceFactor( &( (*treePtr)->RLink) ));

}

void AVLLeftRotation(TreePointer* treePtr,int* FinalBalance){

    TreePointer newRoot;
    TreePointer subTree;

    newRoot=(*treePtr)->RLink;
    subTree=newRoot->LLink;

    /*Here's the actual Rotation*/

    newRoot->LLink=(*treePtr);
    (*treePtr)->RLink=subTree;

    /*Updating the Balance Factor*/

    AVLupdateBF(treePtr);
    AVLupdateBF(&newRoot);

    (*treePtr)=newRoot;
    (*FinalBalance)= (AVLgetBalanceFactor( &( (*treePtr)->LLink) ))  - (AVLgetBalanceFactor( &( (*treePtr)->RLink) ));


}


/*void Insert(FILE* fpointer, recordPointer* Head, recordPointer* Current,HashTable* hashtable,int disTable , int countryTable){

    while( (RecordsInsert(fpointer,Head,Current,hashtable )==true) ){       //While we don't have reached end of File,continue to Insert

    }
}*/


void RecordsInsert(FILE* fpointer,recordPointer* Head, recordPointer* Current,HashTable* CountryHashTable,HashTable* DiseaseHashTable, int disTable , int countryTable,int bucketSize, HashBitMap* BitMap ){

    int MaxLength=15;
    int diseaseBucket;
    int countryBucket;

    recordPointer NextEntry=(*Current);

    char* recordid=malloc( sizeof(char)*MaxLength);
    char* firstname=malloc(sizeof(char)*MaxLength);
    char* lastname=malloc( sizeof(char)*MaxLength);
    char* disease=malloc(  sizeof(char)*MaxLength);
    char* country=malloc(  sizeof(char)*MaxLength);
    char* entry=malloc(    sizeof(char)*MaxLength);
    char* exit=malloc(     sizeof(char)*MaxLength);

    while( (fscanf( fpointer, "%s %s %s %s %s %s %s", recordid , firstname , lastname , disease, country, entry , exit)!=EOF )){

        if ( (*Current)==NULL ){        //If it's the First Record Ever

            (*Current)=malloc(sizeof(patientRecord));
            NextEntry->recordPtr=(*Current);
            NextEntry=(*Current);

        }

        (*Current)->recordID=malloc( sizeof(char)*15 );
        //(*Current)->recordID=calloc(strlen(recordid),sizeof(char));
        strcpy( (*Current)->recordID,recordid);

        (*Current)->patientFirstName=malloc(sizeof(char)*15);
        //(*Current)->patientFirstName=calloc(strlen(firstname) ,sizeof(char) );
        strcpy( (*Current)->patientFirstName,firstname);

        (*Current)->patientLastName=malloc(sizeof(char)*15);
        //(*Current)->patientLastName=calloc(strlen(lastname),sizeof(char));
        strcpy( (*Current)->patientLastName,lastname);

        (*Current)->diseaseID=malloc(sizeof(char)*15);
        strcpy( (*Current)->diseaseID,disease);

        (*Current)->country=malloc(sizeof(char)*15);
        strcpy( (*Current)->country,country);

        (*Current)->entryDate=malloc(sizeof(char)*15);
        strcpy( (*Current)->entryDate,entry);

        (*Current)->exitDate=malloc(sizeof(char)*15);
        strcpy( (*Current)->exitDate,exit);

        (*Current)->recordPtr=emptyPtr;

        HashFunction( (*Current)->diseaseID , &diseaseBucket , disTable);
        HashFunction( (*Current)->country, &countryBucket, countryTable);

        //There will be an IF here
        //BucketCreate( &(CountryHashTable)[diseaseBucket]->bucket , bucketSize, 1 );         //Creating a bucket in the Hashtable
        //BucketCreate( &(CountryHashTable)[countryBucket]->bucket , bucketSize, 1 );         //Creating a bucket in the Hashtable

        /*
        InsertEntryOnHash(BitMap, countryBucket, "country" );
        InsertEntryOnHash(BitMap, diseaseBucket, "disease" );
        */

        //BucketInsert(BigBucket* , char* ,int, HashBitMap* ,int ,bucketItem,AVLItem );

        BucketInsert(  (&(*CountryHashTable)[countryBucket]->bucket) , "country" , countryBucket  , BitMap , bucketSize, country , entry, Current );
        BucketInsert(  (&(*DiseaseHashTable)[diseaseBucket]->bucket) , "disease" , diseaseBucket  , BitMap , bucketSize, disease , entry, Current );

        InsertEntryOnHash(BitMap, countryBucket, "country" );
        InsertEntryOnHash(BitMap, diseaseBucket, "disease" );
        

        //BucketInsert(  &(CountryHashTable)[countryBucket]->bucket , "country" , countryBucket  , &BitMap , bucketSize, country , entry );
        //BucketInsert(  &(CountryHashTable)[diseaseBucket]->bucket , "disease" , diseaseBucket  , &BitMap , bucketSize, disease , entry );




        /*free(recordid);
        free(firstname);
        free(lastname);
        free(disease); 
        free(country);                                                                          k  
        free(entry);
        free(exit);*/

        (*Current)=(*Current)->recordPtr;           //Current Pointer now pointing at NULL

        //return true;
    
    }

    (*Current)=NextEntry;
    
    free(recordid);
    free(firstname);
    free(lastname);
    free(disease); 
    free(country); 
    free(entry);
    free(exit);
    //return false;
    
}

void RecordsCreate(recordPointer* Head, recordPointer* Current ){

    (*Head)=malloc(sizeof(patientRecord));
    (*Current)=(*Head);

    // [Head]-> [-- empty Record --] <-[Current]

}

void InsertEntryOnHash( HashBitMap* BitMap, int thesis, char* type ){

    if( strcmp(type,"country")==0 ) {

        BitMap->countries[thesis]=1;
    }

    else if( strcmp(type,"disease")==0 ) {

        BitMap->diseases[thesis]=1;

    }

}        

void BitMapCreate(HashBitMap* BitMap,int country,int disease){

    BitMap->diseases=malloc(sizeof(char)*disease);
    BitMap->countries=malloc(sizeof(char)*country);

}


bool CheckisEmpty(HashBitMap* BitMap,int thesis,char* type){

    if( (strcmp(type,"country")==0 ) ){

        if( BitMap->countries[thesis]==0 ) {
            return true;
        }
        
        else{  
        
            return false;
        }
        //return false;

    }

    else if ( (strcmp(type,"disease")==0 ) )  {

        if( BitMap->diseases[thesis]==0 ) {
            return true;
        }
        
        else{   
            return false;
        }
        //return false;
    }

}

void globalDiseaseStats( char* date1 , char* date2 , HashBitMap* BitMap , HashTable* diseaseHashTable, int numberOfDiseaseBuckets , int bucketSize, bool currentPatients ){


    for(int i=0; i < numberOfDiseaseBuckets; i++ ){

        if( (BitMap)->diseases[i]==1 )  {                                                                                                                //We have an entry here

            BigBucket rootBucket;
            TreePointer Root;
            int numOfEntries=0;

            rootBucket=(*diseaseHashTable)[i]->bucket;

            while (rootBucket!=NULL){

                for(int j=0; j<bucketSize; j++){
                    
                    numOfEntries=0;

                    if ( rootBucket[j]!=NULL ) {

                        Root=rootBucket[j]->treePtr;

                        if(currentPatients==true){

                            getCurrentPatients( Root , &numOfEntries);
                            printf("For disease: [%s] , we have totally: [ %d ] number of current diseases.\n", rootBucket[j]->item, numOfEntries );

                        }

                        else {
                        
                            getNumberOfDiseases(Root, date1, date2, &numOfEntries,NULL );

                            //printf("For disease: [%s] , we have totally: [ %d ] number of diseases.\n", rootBucket[j]->item, numOfEntries );
                            printf("%s %d\n",rootBucket[j]->item, numOfEntries);
                        }

                    }

                }

                if ( rootBucket[bucketSize-1]!=NULL ){

                    rootBucket=rootBucket[bucketSize-1]->collision;

                }

                else rootBucket=NULL;

            }
        
        }

    }

}


void getNumberOfDiseases(TreePointer treePtr ,char* date1 ,char* date2,int* entries,char* country){

    if( treePtr==NULL ){

        return;
    }

    bool entry;
    bool exit;
    bool countryBool;

    if ( country==NULL ) countryBool=true;
    
    else {

        if( strcmp(country,treePtr->patientRecord->country)==0 ){

            countryBool=true;
        }

        else countryBool=false;

    }

    if ( date1!=NULL && date2!=NULL){

        entry=AVLisGreater( treePtr->item , date1);             
        exit=AVLisGreater( date2 , treePtr->item );
    
    }

    else if (date1==NULL && date2==NULL) {

        entry=true;
        exit=true;
    }

    if( entry==true && exit==true && countryBool==true  ) (*entries)++;


    getNumberOfDiseases( treePtr->LLink, date1, date2, entries, country );
    getNumberOfDiseases( treePtr->RLink, date1 , date2, entries, country);

    return;

}


void diseaseFrequency(char* date1 ,char* date2 ,HashTable* diseaseHashTable ,char* virusName,int numOfDiseaseBuckets,int bucketSize, char* country,bool currentPatients){

    int thesis;
    bool end=false;

    HashFunction(virusName, &thesis ,numOfDiseaseBuckets);

    if( (*diseaseHashTable)[thesis]->bucket!=NULL ){

        BigBucket rootBucket=(*diseaseHashTable)[thesis]->bucket;
        BucketPointer subBucket;
        TreePointer Root;
        int numOfEntries=0;

        while(rootBucket!=NULL && end==false){

            for(int i=0; i<bucketSize; i++){

                subBucket=rootBucket[i];
                if (subBucket!=NULL){
                    if( strcmp( subBucket->item,virusName )==0 ){

                        Root=subBucket->treePtr;

                        if (currentPatients==true) getCurrentPatients( Root, &numOfEntries);
                        
                        else{

                            getNumberOfDiseases(Root, date1, date2, &numOfEntries,country );
                        }

                        if( (country)==NULL && currentPatients==false){
                    
                            //printf("For disease: [%s] , we have totally: [ %d ] number of diseases.\n", virusName, numOfEntries );
                            printf("%s %d\n",virusName,numOfEntries);

                        }

                        else if( country!=NULL && currentPatients==false ) {

                            //printf("For disease: [%s] , we have totally: [ %d ] number of diseases in the country: [%s] .\n", virusName, numOfEntries, country );
                            printf("%s %d\n",virusName,numOfEntries);

                        }

                        else if ( country==NULL && currentPatients==true ){

                            //printf("For disease: [%s], we have totally: [%d] number of current diseases.\n ", virusName , numOfEntries );
                            printf("%s %d\n",virusName,numOfEntries);

                        }

                        end=true;
                        break;

                    }

                }
            }

            if(end==false) rootBucket=rootBucket[bucketSize-1]->collision;

        }

    }

    else {

        printf("Sorry,this virus has never been inside the system.\n");
        return;

    }

}

void getCurrentPatients(TreePointer treePtr, int* entries){

    if( treePtr==NULL ){

        return;
    }

    bool exitBool;

    if( strcmp(treePtr->patientRecord->exitDate ,"-")==0 ){

        exitBool=true;
    }

    else exitBool=false;


    if(  exitBool==true  ) (*entries)++;

    getCurrentPatients( treePtr->LLink, entries );
    getCurrentPatients( treePtr->RLink, entries );

    return;

}

void topkFunction( char* date1, char* date2, HashTable* currentHashTable ,char* topkItem ,int numOfCountriesBucket,int bucketSize,int topK,bool country){

    int thesis;
    bool found=false;

    HashFunction( topkItem , &thesis , numOfCountriesBucket);

    if( (*currentHashTable)[thesis]->bucket!=NULL ){

        BigBucket rootBucket=(*currentHashTable)[thesis]->bucket;
        BucketPointer subBucket;
        TreePointer Root;
        HeapPointer topKHeap=NULL;
        int idOfHeapNodes=0;
        int numOfEntries=0;
        int heapRoot;

        while(rootBucket!=NULL && found==false){

            for(int i=0; i<bucketSize; i++){

                subBucket=rootBucket[i];
                if (subBucket!=NULL){

                    if( strcmp( subBucket->item,topkItem )==0 ){

                        found=true;
                        Root=subBucket->treePtr;

                        if (date1==NULL && date2==NULL){

                            if (country==true) createTopkDiseases( NULL , NULL , Root, &topKHeap, &idOfHeapNodes ); 

                            else createTopkCountries(NULL,NULL,Root, &topKHeap, &idOfHeapNodes);

                        }

                        else {
                            
                            if (country==true) createTopkDiseases(date1,date2,Root,&topKHeap,&idOfHeapNodes);

                            else createTopkCountries(date1,date2,Root,&topKHeap,&idOfHeapNodes);
                        }

                        while(HeapCheck( &topKHeap ,topKHeap->counter )==false ){
                            heapRoot=MaxHeapify( &topKHeap);
                        }   
                        
                        printTopKDiseases( &topKHeap,topK,idOfHeapNodes,country);
                        break;

                    }

                }

            }

            if ( rootBucket[bucketSize-1]!=NULL  ){

                if (found==false) rootBucket=rootBucket[bucketSize-1]->collision;

            }

        }

        FreeHeap(&topKHeap);
        //printf("%p\n",&topKHeap);
        //if(topKHeap==NULL) printf("eimai mia mikrh katsaridoula");
        //printf("%s\n",topKHeap->item);
    
    }

}

void createTopkDiseases(char* date1 ,char* date2 ,TreePointer treePtr,HeapPointer* heapPtr,int* idOfHeapNodes){

    if( treePtr==NULL ){

        return;
    }

    bool entry;
    bool exit;
    bool newDiseaseBool;

    if ( date1!=NULL && date2!=NULL){

        entry=AVLisGreater( treePtr->item , date1);             
        exit=AVLisGreater( date2 , treePtr->item );
        
        if (entry==true && exit==true){

            newDiseaseBool=checkSameHeapInsert(heapPtr,treePtr->patientRecord->diseaseID);
            if (newDiseaseBool==false){

                HeapInsert( heapPtr , treePtr->patientRecord->diseaseID , idOfHeapNodes);

            }

        }

    }

    else if (date1==NULL && date2==NULL) {

        newDiseaseBool=checkSameHeapInsert(heapPtr,treePtr->patientRecord->diseaseID);

        if (newDiseaseBool==false){

            HeapInsert( heapPtr , treePtr->patientRecord->diseaseID , idOfHeapNodes);

        }
    }

    createTopkDiseases( date1, date2, treePtr->LLink, heapPtr, idOfHeapNodes );
    createTopkDiseases( date1 , date2, treePtr->RLink, heapPtr, idOfHeapNodes);

    return;

}

bool checkSameHeapInsert(HeapPointer* heapPtr,char* diseaseID){

    if( (*heapPtr)==NULL ){

        return false;
    }

    bool right;
    bool left;

    if( strcmp( (*heapPtr)->item , diseaseID)==0  ){

        (*heapPtr)->counter=(*heapPtr)->counter+1;
        return true;
    }

    else{

        right=checkSameHeapInsert(  (&(*heapPtr)->RLink),diseaseID);
        left=checkSameHeapInsert( (&(*heapPtr)->LLink) ,diseaseID);

        if (right==true || left==true) return true;
        else return false;
    }

}

void printTopKDiseases(HeapPointer* heapPtr,int topK,int totalEntries,bool country){

    int height;
    //int totalEntries;
    int counter=0;
    int left;
    bool flag=false;
    int auxLeft;

    height=HeapGetHeight(heapPtr);

    //totalEntries=(int)( pow(2,height) -1);

    while (flag==false){

        if ( topK<totalEntries && topK>=(pow(2,height-1)) ){

            flag=true;
        }

        else if (topK==totalEntries){

            for (int i=1; i<=height; i++){
                printGivenLevel( heapPtr, &counter, i, country);
            }

            return;

        }

        else if(topK>totalEntries){
            
            if(country==true) printf("Sorry,we only have: [%d] diseases available for this country.Try again.\n",totalEntries);

            else printf("Sorry,we only have: [%d] countries available for this disease.Try again.\n",totalEntries);
        
            return;
        }

        //if (flag==true) height=height-1;
        height=height-1;
        totalEntries=(int)( pow(2,height) -1);

    }

    if (flag==true){

        for(int i=1; i<=height; i++){
    
            printGivenLevel(heapPtr,&counter,i,country);
        }
    
    }

    left=topK-counter;
    auxLeft=left;

    int* array=malloc(sizeof(int)*left);
    for (int j=0; j<left; j++){
        array[j]=0;
    }

    getLeftDiseases( heapPtr, &array,height+1,left);
    
    for(int i=0; i<left; i++){
        printLeftDiseases( heapPtr , array[i], height+1, &auxLeft, country );
    }

    free(array);
}


void printGivenLevel(HeapPointer* heapPtr,int* counter,int height,bool country){

    if ( (*heapPtr)==NULL){
        return;
    }

    if (height==1){

        
        if(country==true) printf("%s %d\n",(*heapPtr)->item, (*heapPtr)->counter);
        //if(country==true) printf("For Disease: [%s] we have tottally: [%d] outbreaks.\n",(*heapPtr)->item, (*heapPtr)->counter);

        //else printf("For Country: [%s] we have tottally: [%d] outbreaks.\n",(*heapPtr)->item, (*heapPtr)->counter);
        else printf("%s %d\n",(*heapPtr)->item,(*heapPtr)->counter);

        (*counter)++;
    }

    else if (height>1){

        printGivenLevel( (&(*heapPtr)->LLink) ,counter,height-1,country);
        printGivenLevel( (&(*heapPtr)->RLink) ,counter,height-1,country);

    }
}

void getLeftDiseases(HeapPointer* heapPtr,int** array,int height,int left){

    if ( (*heapPtr)==NULL){
        return;
    }

    if (height==1){

        int minIndex=findMinElement(array,left);
        
        if ( (*array)[minIndex]< (*heapPtr)->counter ){
            
            (*array)[minIndex]=(*heapPtr)->counter;

        }
    }

    else if (height>1){

        getLeftDiseases( (&(*heapPtr)->LLink) ,array,height-1,left);
        getLeftDiseases( (&(*heapPtr)->RLink) ,array,height-1,left);

    }

}


int findMinElement(int** array,int size){

    int min=INT_MAX;
    int index;

    for(int i=0; i<size; i++){

        if ( ((*array)[i] ) < min  ){
            min=(*array)[i];
            index=i;
        }
    }

    return index;

}

void printLeftDiseases(HeapPointer* heapPtr,int counter,int height,int* left,bool country){

    if ( (*heapPtr)==NULL){
        return;
    }

    if( ( (*heapPtr)->counter)==counter && height==1 && (*left)>0  ){

        if(country==true) printf("%s %d\n",(*heapPtr)->item, (*heapPtr)->counter);

        //else printf("For country [%s] we have tottally: [%d] outbreaks.\n",(*heapPtr)->item, (*heapPtr)->counter);
        else printf("%s %d\n",(*heapPtr)->item ,(*heapPtr)->counter);

        (*left)--;
    }

    else {

        printLeftDiseases( (&(*heapPtr)->LLink),counter,height-1,left,country);
        printLeftDiseases( (&(*heapPtr)->RLink),counter,height-1,left,country);
    }

}

void createTopkCountries(char* date1 ,char* date2 ,TreePointer treePtr,HeapPointer* heapPtr,int* idOfHeapNodes){

    if( treePtr==NULL ){

        return;
    }

    bool entry;
    bool exit;
    bool newDiseaseBool;

    if ( date1!=NULL && date2!=NULL){

        entry=AVLisGreater( treePtr->item , date1);             
        exit=AVLisGreater( date2 , treePtr->item );
        
        if (entry==true && exit==true){

            newDiseaseBool=checkSameHeapInsert(heapPtr,treePtr->patientRecord->country);
            if (newDiseaseBool==false){

                HeapInsert( heapPtr , treePtr->patientRecord->country , idOfHeapNodes);

            }

        }

    }

    else if (date1==NULL && date2==NULL) {

        newDiseaseBool=checkSameHeapInsert(heapPtr,treePtr->patientRecord->country);

        if (newDiseaseBool==false){

            HeapInsert( heapPtr , treePtr->patientRecord->country , idOfHeapNodes);

        }
    }

    createTopkCountries( date1, date2, treePtr->LLink, heapPtr, idOfHeapNodes );
    createTopkCountries( date1 , date2, treePtr->RLink, heapPtr, idOfHeapNodes);

    return;

}

void FreeHeap(HeapPointer* heapPtr){

    if ( (*heapPtr)==NULL ){
        return;
    }

    HeapPointer right=(*heapPtr)->RLink;
    HeapPointer left=(*heapPtr)->LLink;

    (*heapPtr)->RLink=NULL;
    (*heapPtr)->LLink=NULL;
    (*heapPtr)->item=NULL;

    free(*heapPtr);
    (*heapPtr)=NULL;

    FreeHeap(&right);
    FreeHeap(&left);
}


void FreeRecords(recordPointer* headRecord){

    recordPointer currentRecord=(*headRecord)->recordPtr;

    while(currentRecord!=NULL){

        free( (*headRecord)->recordID);
        (*headRecord)->recordID=NULL;

        free( (*headRecord)->patientFirstName);
        (*headRecord)->patientFirstName=NULL;

        free( (*headRecord)->patientLastName);
        (*headRecord)->patientLastName=NULL;

        free( (*headRecord)->diseaseID);
        (*headRecord)->diseaseID=NULL;

        free( (*headRecord)->country);
        (*headRecord)->country=NULL;

        free( (*headRecord)->entryDate);
        (*headRecord)->entryDate=NULL;
        
        free( (*headRecord)->exitDate);
        (*headRecord)->exitDate=NULL;

        (*headRecord)->recordPtr=NULL;
        free( (*headRecord));
        

        (*headRecord)=currentRecord;
        currentRecord=currentRecord->recordPtr;

    }

    free( (*headRecord)->recordID);
    free( (*headRecord)->patientFirstName);
    free( (*headRecord)->patientLastName);
    free( (*headRecord)->diseaseID);
    free( (*headRecord)->country);
    free( (*headRecord)->entryDate);
    free( (*headRecord)->exitDate);
    (*headRecord)->recordPtr=NULL;
    free( (*headRecord));

}

void FreeAVL(TreePointer* treePtr){

    if ( (*treePtr)==NULL ){
        return;
    }

    TreePointer right=(*treePtr)->RLink;
    TreePointer left=(*treePtr)->LLink;

    (*treePtr)->RLink=NULL;
    (*treePtr)->LLink=NULL;
    free( (*treePtr)->item );
    (*treePtr)->item=NULL;
    (*treePtr)->patientRecord=NULL;

    free(*treePtr);
    (*treePtr)=NULL;

    FreeAVL(&right);
    FreeAVL(&left);

}