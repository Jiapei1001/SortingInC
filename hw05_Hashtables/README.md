Please see attached:

anagrams_run.c is the controller file.

chained_ht.h is the header file for the hashtable.

chained_ht.c is the implementation file for the hashtable.

anagrams_test.c is the test file.


Please use attached make commands:

make compile ------ to compile the file

make run ------ to run the file

make compile_test ------ to compile the test file

make test ------ to run the test file



I like this assignment as it gives me a more clear understanding about the hashtable and it structure.
However, I think it will be great if the instructions of the assignment can be more clear or gives a bit more contexts or hint.
I spent around 8 hours to find out what triggers the leak memory or memory crash until I realize the default number of buckets is not set big 
enough to allow for accommodate each unique anagram. 

I tried a lot of times to know the relationship between pointers within or outside a method, and how to free them. 
As the memory leak is very important in C, I think it will be great if there is more introduction of it, besides just utilizing valgrind. 
It can be sometimes hard to use valgrind to trace the triggering issue.


