How to build and run the code
I mainly used "Make test" for compiling and getting the test file for testing.
Then I used "./test" for running the testing part. I used "valgrind --leak-check=full ./test" to check if there is any memory leak.
make test
./test


Description of the files in the directory
In the folder there are several files. "neuchre.h" is the interface of "neuchre.c", which contains the implementations and functions of card,
hand, and game functions. "neuchre.h" is also the interface of "deck.c", which contains the implementations and functions of the deck. 
"neuchre_run.c" acts as the controller to keep the game running.


External libraries the code relies on 
I watched the channel of "mycodeschool" on youtube. It explains the fundamentals of C, and have multiple playlist.
I feel the explanations are very clear and helpful.


For this project, I used stack as the fundamental structure for implementing hand.
I used double linked list as the structure for hand.
This helps me to understand how to use struct in C. I find it is also helpful for me to understand more about pointer and its applications to specific problems.

I find the double linked list is harder to implement, especially the method of "RemoveCardFromHand".
I spent a lot of time on how to use clint.py and Valgrind.

I spent more than 24 hours in total on this total project.

