# diseaseMonitor
Program for solving queries with: Hashtable, AVL-Trees, Linked Lists and Max-Heap.

### Compile and Run .cmd with autograder

When in the directory, to compile and run the program type:

``` ./validator.sh 'inputFile.txt' 'ht1Entries' 'ht2Entries' 'bucketSize' ```

This validation script will run 10 commands and will tell us if we passed all the requested tests.

Tip: For bucketSize, the formula is: bucketSize=(bucketSize/24). So we need >24.

### Compile and Run particular .cmd

If you want to run particular commands,you have only to do:

1) ```make```

And then, to run the 1st .cmd for example with pipe: 

``` ./diseaseMonitor -p patientRecordsFile –h1 diseaseHashtableNumOfEntries
–h2 countryHashtableNumOfEntries –b bucketSize < 0_input_command_RND10244096.cmd 
```

