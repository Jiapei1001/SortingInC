There are two folders: 
"min_heap_int" is the min heap for sorting integers for step 2,
"min_heap_arbitrary" is the min heap for sorting arbitrary structures for step 3.


I finished this homework by myself, and asked some questions to the TAs during the office hour. It took me around a day, 8-10 hours to finish.

I think the logic is pretty clear. It took some time for me to find out how to deal with memory leak.

It took me a lot of time to understand the pointers of pointer, and how it works with struct.
For instance, I know I need to malloc for struct. When there is a pointer array inside the struct, I don't know if it is necessary to malloc for the pointer array inside the struct. 


I think it will be much much more helper if there is a basic code example or code walk through to introduce these ideas, besides just giving a chapter in a book with many many contents.


After this homework, I still have lots of questions about pointers of pointer. I still dont't know how to use them.
I find inside the heapsort method, whenever I want to add a loop, it will trigger segmentation errors. Then I extract the loop part to a separate method outside the heapsort method, then it works.
I don't know what triggers the segmentation error.





When you have a folder of code in Github, it's a good practice to have a README.md that describes the code and other details about the project/directory. 

At the least, you should have a readme at the top level of your repo, and for this class in every assignment folder. 

A good readme includes things like: 

How to build and run the code
Including any command line arguments
An example of the input and output
Description of the files in the directory
External libraries the code relies on 
And where to find them
Any assumptions you made about writing the code
A summary of the project
In this class, a short summary of the assignment. 
Links to references, acknowledgments and other resources. 
Other things we'd like to see in this class: 

What went well
What was hard or tricky
How much time you spent on it