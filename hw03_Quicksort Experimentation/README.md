Command line arguments:

./sort -a \
./sort -b \
./sort -c \
./sort -all

<br />

#### Result:

**Note: sorting time periods are counted in milliseconds.**



###### Sort size:     16;     32;     64;    128;    256;    512;   1024;   2048;   4096;   8192;  16384;  32768;  65536; 131072; 262144; 524288;1048576;2097152;


----------------------------------------------------------------------------------------------------------------------------------------------------------

###### Algo A:         1;      3;      6;     13;     31;     66;    133;    279;    600;   1176;   2358;   4443;   9456;  20635; 140731;  91003; 193891; 402875;

###### Algo B:         1;      2;      6;     14;     29;     70;    114;    247;    525;    999;   1750;   3748;   7904;  16771;  51353;  71594; 151716; 318060;

###### Algo C:         0;      2;      4;      9;     20;     42;     90;    199;    429;    788;   1474;   3183;   6743;  14649;  30891;  63355; 133229; 278369;


---

<br />
<br />

> From the table above, we can see the differences between the three algorithms. For small sizes of array of random numbers,such as from 16 to 64, 
there is no significant difference in terms of running time, although we can see Algorithm C's running time is slightly less than the other two.

> For comparison between Algorithm A and B, we can see Algorithm B is better than Algorithm A. There only difference is that the pivot location is chosen as
the leftmost index in A, and the median number index in B. From this, I would use the method in Algorithm B in future implementation of quicksort, as it can 
save some running time.

> When the sizes of arrays with random numbers are getting bigger, we can see the differences in running time are gradually getting bigger and bigger.
From the numbers, we can know Algorithm C (hybrid of quicksort and intertion sort) is the most optimized, as the running time are the lowest.
In the implementation, when the size of array reaches to less than 10, utilizing insertion sort can help to optimize the sorting method. 
However, the implementation of C is a bit more complex than the other two. It also depends on how many number to be sorted. If the size of numbers 
to be sorted is relatively small, there is no need to use the hybrid method. But when the size of numbers are bigger, the hybrid option stands out clearly.

