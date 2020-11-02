"make run" to run the code
Please note, in the main function, please run uncomment one or comment the other one:
    
    1. either: Seattle_WA to Boston_MA
    
        * Boston_MA:2969.17<--Rochester_NY:2572.67<--Flint_MI:2239.84<--Milwaukee_WI:2008.15<--Waukesha_WI:1988.78<--Saint_Cloud_MN:1599.05<--Bismarck_ND:1235.84<--Billings_MT:820.21<--Missoula_MT:475.65<--Coeur_d'Alene_ID:311.11<--Seattle_WA:0.00
    
    
    2. or Minneapolis_MN to Ann Arbor_MI
        
        * Ann_Arbor_MI:611.50<--Lansing_MI:539.24<--Milwaukee_WI:347.29<--Waukesha_WI:327.92<--Eau_Claire_WI:93.34<--Saint_Paul_MN:9.83<--Minneapolis_MN:0.00


The program has been tested by clint.py. However, there are some "Using sizeof(type) for malloc", or "nprintf is better than strcpy" are not included
in the code, as I tried to revise them, but it didn't work.



There is a memory leak note after the shortest result is printed. Please note that I don't know what triggers 
this note, as I tried to free the malloc'ed key strings, nodes, listItem, graph and hashtable one by one.



Having a talk with amazing TA during office hour, I use Graph and HashTable as the data structure for the implementation. 
The graph is used to store all the city nodes and their edges from reading the file. The graph is implemented by adjacency list. 
Each unique city node is stored in the city node array. All the linked city nodes to the front node are stored in the listItem linked structure.


I used HashTable to store the name and distance value of each city node, as kay and value. Hashtable is great for easy access to the value through referencing the key string.


Some additional pointers are included into the struct of the node, or hashNode, such as "foundBy", which is used to track the closet path from the source city to the target destination city.




* Take away from the assignment

    1. From this homework, I feel I'm much more confident in using pointers and pointers are really nice.
    2. I find youtube videos are great source to understand the Djikstra's Algorithm, as there are many visual representations.
    3. The Djikstra's Algorithm is not that complicated, but when it combines with the data structure of graph and hashtable, it's more complicated.
    4. I think when finding the current min value city node after each loop, it will be great if there is a hint in the instructions.
    5. I spent the vast amount of time on the syntax of C, compared with the time of the algorithm. I feel without the built in libraries like in java, sometimes the syntax or memory leak issues can be frustrating. It will be great if there are more guidance on this.
    
