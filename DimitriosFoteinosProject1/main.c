#include <stdio.h>
#include <stdlib.h>
#include "covid.h"
#include <unistd.h>
#include <string.h>

int main( int argc, char * argv[]) {

    int x=19;
    int tableSize=10;
    int opt;
    int x1;
    int x2;
    int byt;
    int i;

    ///////////   Declaring our Variables   ///////////////////////////////////////////
    HeapPointer Root;                       //Pointer to our Heap

    HashBitMap  BitMap;                     //BitMap for entries in hashtables
    HashTable CountryHashTable;             //The Hashtable for countries
    HashTable DiseaseHashTable;             //The Hashtable for diseases

    recordPointer headRecord;               //The first record
    recordPointer currentRecord;            //The each time current record

    FILE* entries;                          //File with entities

    int diseaseHashtableNumOfEntries;       //Number of buckets in Hashtable->Diseases
    int countryHashtableNumOfEntries;      //Number of buckets in Hashtable->Countries
    int bucketSize;                         //Sizeof each buckets in Bytes
    int counterCommands;                    //Helping us with intime run commands
    int c;

    char* file;                             //The name of the file of entities
    char* commands;                         //For our commands
    char* token;                            //Helping us with intime run commands
    char* auxtoken;                         //Helping us with intime run commands
    char* p;
    const char s[2]=" ";                    //Helping us with intime run commands

    if ( argc<8 ){
            
        printf("Sorry,we need more arguments\n");
        return -1;
    }

    else if ( argc>9 ){

        printf("Sorry,we less arguments\n");
        return -1;
    }

    else {

        for(i=1; i<argc; i++){

            if ( (strcmp(argv[i],"-p")==0 )){
                file=argv[i+1];
            } 

            if ( (strcmp(argv[i],"-h1")==0 )){
                diseaseHashtableNumOfEntries=atoi(argv[i+1]);
            }

            if ( (strcmp(argv[i],"-h2")==0)){
                countryHashtableNumOfEntries=atoi(argv[i+1]);
            } 

            if ( (strcmp(argv[i],"-b")==0)){
                bucketSize=atoi(argv[i+1])/24 ;
            } 
        }
    }

    commands=malloc(sizeof(char)*50);
    //printf("Welcome to the best disease Monitor! You would like to start?\nPress [y] or [n].\n");

    /*if (scanf("%s",commands)!=1){
        printf("Failed to read y/n. \n");
        return -1;
    }*/

    //if( strcmp(commands,"y")==0 ){

        entries=fopen(file,"r");                                               
        
        if (entries==NULL){
            printf("Error opening the file!\n");
            exit(EXIT_FAILURE); 
        }

        HTCreate( &DiseaseHashTable,diseaseHashtableNumOfEntries,bucketSize );                      //Initializing the Hashtable for Diseases
        HTCreate( &CountryHashTable,countryHashtableNumOfEntries,bucketSize );                      //Initializing the Hashtable for Countries

        BitMapCreate( &BitMap, diseaseHashtableNumOfEntries,countryHashtableNumOfEntries);          //Creating the BitMap for helping as at particular functions
        RecordsCreate( &headRecord,&currentRecord);                                                 //Allocating memory for the First Record Ever
        
        /*Creating and allocating memory for all the databases we'll need*/

        RecordsInsert( entries,&headRecord,&currentRecord, &CountryHashTable, &DiseaseHashTable, diseaseHashtableNumOfEntries ,countryHashtableNumOfEntries, bucketSize, &BitMap );


        //printf("You can now,give us one of the followup commands:\n");
        //printf("/globalDiseaseStats [date1 date2] \n/diseaseFrequency virusname [country] date1 date2 \n/topk-Diseases k country [date1 date2] \n/topk-Countries k disease [date1 date2] \n/insertPatientRecord  recordID  patientFirstName  patientLastName  diseaseID  entryDate\n/recordPatientExit  recordID  exitDate\n/numCurrentPatients [disease] \n/exit\n");

        //char* string;
        //scanf("%s",string);
        
        //scanf("%[^\n]s",commands);
        //fgets(commands,100,stdin);
        //while ( (c = getchar()) != '\n' && c != EOF );

        if( fgets(commands,100,stdin)==NULL){
            printf("Unable to read again a command. \n");
            return -1;
        }
        
        if ((p=strchr(commands, '\n')) != NULL){
            *p = '\0';
        }

        token = strtok(commands, s);

        while( strcmp(token,"/exit")==0 || strcmp(token,"/globalDiseaseStats")==0 || strcmp(token,"/diseaseFrequency")==0 || strcmp(token,"/topk-Diseases")==0 || strcmp(token,"/topk-Countries")==0 || strcmp(token,"/insertPatientRecord")==0 ||  strcmp(token,"/recordPatientExit")==0 || strcmp(token,"/numCurrentPatients")==0 ){

            //fgets(commands,100,stdin);
            //scanf ("%[^\n]%*c", commands);



            //token = strtok(commands, s);
            
            
            
            //strcpy(auxtoken,token);

            counterCommands=0;

            /*Case 1*/
            
            if( strcmp(token,"/globalDiseaseStats")==0 ){

                //char** dates=malloc(sizeof(char*)*2);
                //dates[0]=malloc(sizeof(char)*15);
                //dates[1]=malloc(sizeof(char)*15);

                bool dates;
                char* dates1=malloc(sizeof(char)*15);
                char* dates2=malloc(sizeof(char)*15);

                while( token != NULL ) {
            
                    token = strtok(NULL, s);
                    
                    if(token!=NULL){
                        
                        if (counterCommands==0) strcpy(dates1,token);
                        else strcpy(dates2,token);
                        //dates[counterCommands]=token;
                        counterCommands++;
                    }

                }

                //dates[counterCommands]=strtol(token,NULL,10);
                //dates[counterCommands]=token;

                if (counterCommands==2 ){

                    dates=AVLisGreater(dates2,dates1);
                    if (dates==false){
                        printf("Sorry,date 1 can't be greater than date1.Please, try again.\n");
                    }
                    
                    else {
                        globalDiseaseStats( dates1 , dates2 , &BitMap , &DiseaseHashTable, diseaseHashtableNumOfEntries, bucketSize,false );                                             
                    }

                } 

                else if(counterCommands==1 || counterCommands >2 ) {

                    printf("Sorry, /globalDiseaseStats format needs 0 or 2 dates.No between.\n");
                    //exit(EXIT_FAILURE);

                }

                else {
                    
                    //printf("mpainei edw\n");
                    globalDiseaseStats( NULL , NULL , &BitMap , &DiseaseHashTable, diseaseHashtableNumOfEntries, bucketSize,false );                                             
                }

                free(dates1);
                free(dates2);

            /*End of Case 1*/

            }
    
            /*Case 2*/

            else if( strcmp(token,"/diseaseFrequency")==0 ){

                char* dates1=malloc(sizeof(char)*15);
                char* dates2=malloc(sizeof(char)*15);
                char* virusName=malloc(sizeof(char)*30);
                char* country=malloc(sizeof(char)*30);

                while( token != NULL ) {
            
                    token = strtok(NULL, s);
                    
                    if(token!=NULL){
                        
                        if (counterCommands==0) strcpy(virusName,token);
                        //if ( strcmp(token,"virusName")==0 ) strcpy(virusName,token);

                        else if (counterCommands==1) strcpy(dates1,token);

                        //else if ( strcmp(token,"country")==0 ) strcpy(country,token);

                        else if (counterCommands==2) strcpy(dates2,token);
                        
                        ///else if ( strcmp(token,"[date1")==0 ) strcpy (dates1,token);

                        else if (counterCommands==3) strcpy (country,token);

                        //else if ( strcmp(token,"date2]")==0 ) strcpy (dates2,token);

                        counterCommands++;

                    }

                }

                if( counterCommands < 3 || counterCommands > 4 ){

                    printf("Sorry, /diseaseFrequency format needs 4 or 5 variables.\n");
                    exit(EXIT_FAILURE);

                }

                else if ( counterCommands == 3 ) {

                    //strcpy(dates2,dates1);
                    //strcpy(dates1,country);
                    country=NULL;
                    diseaseFrequency( dates1 ,dates2 , (&DiseaseHashTable) ,virusName,diseaseHashtableNumOfEntries  , bucketSize, country ,false);

                }

                else if (counterCommands==4 && country!=NULL){

                    diseaseFrequency( dates1 ,dates2 , (&DiseaseHashTable) ,virusName,diseaseHashtableNumOfEntries  , bucketSize, country ,false);

                }

                free(dates1);
                free(dates2);
                free(virusName);
                free(country);
            
            }

                
            /*End of Case 2*/


            /*Case 3*/
        
            else if( strcmp(token,"/topk-Diseases")==0 ){

                int topk;
                char* country=malloc(sizeof(char)*20);
                char* date1=malloc(sizeof(char)*20);
                char* date2=malloc(sizeof(char)*20);


                 while( token != NULL ) {
            
                    token = strtok(NULL, s);
                    
                    if(token!=NULL){
                        
                        if (counterCommands==0) topk=strtol(token,NULL,10);

                        else if (counterCommands==1) strcpy(country,token);

                        else if (counterCommands==2) strcpy(date1,token);

                        else if (counterCommands==3) strcpy (date2,token);

                        counterCommands++;

                    }

                }

                if(topk<=0){
                    printf("Sorry,topk number must be a positive number.\n");
                    //return -1;
                }

                if ( counterCommands < 2 || counterCommands >4 || counterCommands==3 ){

                    printf("Sorry, /topk-Diseases Format needs 2 or 4 commands.\n");
                    //return -1;
                }

                else if (counterCommands==2 && topk>0 ){

                    topkFunction( NULL , NULL , &CountryHashTable , country , countryHashtableNumOfEntries , bucketSize, topk, true);

                }

                else if (counterCommands==4 && topk>0 ){

                    topkFunction( date1 , date2 , &CountryHashTable , country , countryHashtableNumOfEntries , bucketSize, topk, true);
                }
            
                free(country);
                free(date1);
                free(date2);
            
            }


            /*End of Case 3*/

            /*Case 4*/

            else if( strcmp(token,"/topk-Countries")==0 ){

                int topk;
                char* disease=malloc(sizeof(char)*20);
                char* date1=malloc(sizeof(char)*20);
                char* date2=malloc(sizeof(char)*20);

                 while( token != NULL ) {
            
                    token = strtok(NULL, s);
                    
                    if(token!=NULL){
                        
                        if (counterCommands==0) topk=strtol(token,NULL,10);

                        else if (counterCommands==1) strcpy(disease,token);

                        else if (counterCommands==2) strcpy(date1,token);

                        else if (counterCommands==3) strcpy (date2,token);

                        counterCommands++;

                    }
                }

                if(topk<=0){
                    printf("Sorry,topk number must be a positive number.\n");
                    //return -1;
                }

                if ( counterCommands < 2 || counterCommands >4 || counterCommands==3 ){

                    printf("Sorry, /topk-Countries Format needs 2 or 4 commands.\n");
                    //return -1;
                }

                else if (counterCommands==2 && topk>0 ){

                    topkFunction( NULL , NULL , &DiseaseHashTable , disease , diseaseHashtableNumOfEntries , bucketSize, topk, false);

                }

                else if (counterCommands==4 && topk>0 ){

                    topkFunction( date1 , date2 , &DiseaseHashTable , disease , diseaseHashtableNumOfEntries , bucketSize, topk, false);
                }

            
                free(disease);
                free(date1);
                free(date2);

            }

            /*End of Case 4*/

            /*Case 5*/

            else if( strcmp(token,"/insertPatientRecord")==0 ){

                int diseaseBucket;
                int countryBucket;

                char* recordID=malloc(sizeof(char)*15);
                char* firstname=malloc(sizeof(char)*20);
                char* lastname=malloc(sizeof(char)*20);
                char* diseaseID=malloc(sizeof(char)*20);
                char* country=malloc(sizeof(char)*20);
                char* entry=malloc(sizeof(char)*20);
                char* exit=malloc(sizeof(char)*20);

                while( token != NULL ) {
            
                    token = strtok(NULL, s);
                    
                    if(token!=NULL){
                        
                        if (counterCommands==0) strcpy(recordID,token);

                        else if (counterCommands==1) strcpy(firstname,token);

                        else if (counterCommands==2) strcpy(lastname,token);
                        
                        else if (counterCommands==3) strcpy (diseaseID,token);

                        else if (counterCommands==4) strcpy (country,token);

                        else if (counterCommands==5) strcpy (entry,token);

                        else if (counterCommands==6) strcat (exit,token);
                        
                        counterCommands++;

                    }

                }

                if (counterCommands<6 || counterCommands>7) {

                    printf("Sorry, /insertPatientRecord format needs 5 or 6 variables.\n");
                    return -1;
                    //exit(EXIT_FAILURE);


                }

                if (counterCommands==6) strcpy(exit,"-");


                HashFunction( diseaseID , &diseaseBucket , diseaseHashtableNumOfEntries );
                HashFunction( country, &countryBucket, countryHashtableNumOfEntries );

                recordPointer newRecord;
                newRecord=currentRecord->recordPtr;

                if ( (newRecord)==NULL ){                                    //If it's the First Record Ever

                    (newRecord)=malloc(sizeof(patientRecord));
                    currentRecord->recordPtr=(newRecord);
                    //NextEntry=(*Current);

                }

                (newRecord)->recordID=malloc(sizeof(5));
                strcpy( (newRecord)->recordID,recordID);

                (newRecord)->patientFirstName=malloc(sizeof(15));
                strcpy( (newRecord)->patientFirstName,firstname);

                (newRecord)->patientLastName=malloc(sizeof(15));
                strcpy( (newRecord)->patientLastName,lastname);

                (newRecord)->diseaseID=malloc(sizeof(15));
                strcpy( (newRecord)->diseaseID,diseaseID);

                (newRecord)->country=malloc(sizeof(15));
                strcpy( (newRecord)->country,country);

                (newRecord)->entryDate=malloc(sizeof(15));
                strcpy( (newRecord)->entryDate,entry);

                (newRecord)->exitDate=malloc(sizeof(15));
                strcpy( (newRecord)->exitDate,exit);

                (newRecord)->recordPtr=emptyPtr;     

                BucketInsert(  (&(CountryHashTable)[countryBucket]->bucket) , "country" , countryBucket  , &BitMap , bucketSize, country , entry, &newRecord );
                BucketInsert(  (&(DiseaseHashTable)[diseaseBucket]->bucket) , "disease" , diseaseBucket  , &BitMap , bucketSize, diseaseID , entry, &newRecord );

                InsertEntryOnHash(&BitMap, countryBucket, "country" );
                InsertEntryOnHash(&BitMap, diseaseBucket, "disease" );

                printf("Record added\n");

                currentRecord=newRecord;

                newRecord=NULL;

                free(recordID);
                free(firstname);
                free(lastname);
                free(diseaseID);
                free(country);
                free(entry);
                free(exit);
            
            }

            /*End of Case 5*/

            /*Case 6*/

            else if( strcmp(token,"/recordPatientExit")==0 ){

                char* recordID=malloc(sizeof(char)*15);
                char* exit=malloc(sizeof(char)*20);

                recordPointer Current;
                Current=headRecord;

                while( token != NULL ) {
            
                    token = strtok(NULL, s);
                    
                    if(token!=NULL){
                        
                        if (counterCommands==0) strcpy(recordID,token);
                        else strcpy(exit,token);
                        //dates[counterCommands]=token;
                        counterCommands++;
                    }

                }

                if (counterCommands!=2) {

                    printf("Sorry,format for recordPatientExit takes exactly 2 arguments.\n");
                    return -1;
                }

                while( Current!=NULL ){

                    if( strcmp(recordID,Current->recordID) == 0 ){

                        if ( strcmp(Current->exitDate,"-")==0 || ( AVLisGreater(exit, Current->exitDate) )==true ){

                            strcpy(Current->exitDate, exit );
                            printf("Record updated\n");

                        }

                        else printf("Sorry,there is already one exit date there or the entry date is greater than the exit date.\n");

                    }
                
                    Current=Current->recordPtr;
              
                }
            
                free(recordID);
                free(exit);
            
            }

            /*End of Case 6*/

            /*Case 7*/

            else if( strcmp(token,"/numCurrentPatients")==0 ){

                char* disease=malloc(sizeof(char)*20);

                while( token != NULL ) {
            
                    token = strtok(NULL, s);
                    
                    if(token!=NULL){
                        
                        if (counterCommands==0) strcpy(disease,token);

                        counterCommands++;
                    }

                }

                if (counterCommands>1){

                    printf("Sorry, /numCurrentPatients format needs 0 or 1 commands.No More.\n");
                    return -1;
                }

                else if( counterCommands == 0 ){

                    globalDiseaseStats( NULL , NULL ,  &BitMap , &DiseaseHashTable, diseaseHashtableNumOfEntries , bucketSize, true );

                }

                else if ( counterCommands==1 ){

                    diseaseFrequency( NULL , NULL , &DiseaseHashTable , disease , diseaseHashtableNumOfEntries , bucketSize, NULL , true);

                }

                free(disease);
            }

            /*End of Case 7*/
            
            /*Case 8*/

            else if( strcmp(token,"/exit")==0 ){

                FreeRecords(&headRecord);

                /*First for diseases AVL-Trees*/

                for(int i=0; i<diseaseHashtableNumOfEntries; i++){


                    BigBucket rootBucket;
                    BigBucket currentBucket;
                    TreePointer Root;
                    int b;
                    bool final=false;

                    rootBucket=DiseaseHashTable[i]->bucket;
                    currentBucket=rootBucket;

                    while (currentBucket!=NULL && final==false ){

                        for(b=0; b<bucketSize; b++){

                            if(rootBucket[b]!=NULL){   
                                Root=rootBucket[b]->treePtr;

                                if (Root!=NULL){
                                    FreeAVL(&Root);
                                }

                                if( b==(bucketSize-1) ) {

                                    currentBucket=rootBucket[bucketSize-1]->collision;
                                    final=false;
                                }

                                else final=true;

                                rootBucket[b]->collision=NULL;
                                rootBucket[b]->treePtr=NULL;    //done it alread at freeavl
                                free(rootBucket[b]->item);
                                
                                rootBucket[b]->item=NULL;
                                
                                free(rootBucket[b]);
                                rootBucket[b]=NULL;

                            }
                        
                        }
                   
                        free(rootBucket);
                        rootBucket=NULL;
                        
                        if (final==true || final==false ){
                            rootBucket=currentBucket;

                        }

                    }

                    //free(DiseaseHashTable[i]);
                
                }
 
                for (int i=0; i<diseaseHashtableNumOfEntries; i++){

                    free (DiseaseHashTable[i]);
                    DiseaseHashTable[i]=NULL;

                }

                free(DiseaseHashTable);

                /*Then for countries AVL-Trees*/

                for (int j=0; j<countryHashtableNumOfEntries; j++){

                    BigBucket rootBucket;
                    BigBucket currentBucket;
                    TreePointer Root;
                    int b;
                    bool final=false;

                    rootBucket=CountryHashTable[j]->bucket;
                    currentBucket=rootBucket;

                    while (currentBucket!=NULL && final==false ){

                        rootBucket=currentBucket;

                        for(b=0; b<bucketSize; b++){

                            if(rootBucket[b]!=NULL){   
                                Root=rootBucket[b]->treePtr;

                                if(Root!=NULL){
                                    FreeAVL(&Root);
                                }

                                if( b==(bucketSize-1) ) {

                                    currentBucket=rootBucket[bucketSize-1]->collision;
                                    final=false;
                                }

                                else final=true;

                                rootBucket[b]->collision=NULL;
                                rootBucket[b]->treePtr=NULL;    //done it alread at freeavl
                                free(rootBucket[b]->item);
                                    
                                rootBucket[b]->item=NULL;
                                    
                                free(rootBucket[b]);
                                rootBucket[b]=NULL;

                            }
                        
                        }

                        free(rootBucket);
                        rootBucket=NULL;

                        if (final==true || final==false){
                            rootBucket=currentBucket;
                        }

                    }

                }

            
                for (int i=0; i<countryHashtableNumOfEntries; i++){

                    free (CountryHashTable[i]);
                    CountryHashTable[i]=NULL;

                }

                free(CountryHashTable);

                free(BitMap.countries);
                free(BitMap.diseases);
                printf("exiting\n");

                break;
        
            } 
            
            /*End of Case 8*/

            //printf("Please,give us again a command\n");
            if ( fgets(commands,100 ,stdin) ==NULL){
                printf("Unable to read again a command.\n");
                return -1;
            }
            
            if ((p=strchr(commands, '\n')) != NULL){
                *p = '\0';
            }

            token = strtok(commands, s);


        }

    //}

    /*else{

        printf("App will close within 5 sec.Thank you for using it.\n");
        sleep(5);
        exit(EXIT_SUCCESS);
    }*/


    free(commands);
    fclose(entries);


    return 0;
}
