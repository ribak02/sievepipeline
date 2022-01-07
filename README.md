# sievepipeline
This practical involved the design and implementation of a simple data processing pipeline framework. These stages which are processed in parallel through the use of pipe() and fork().
Design and Implementation:
The Pipeline struct has a two int array to store the input/output file des for pipe(). I created a dynamically allocated array to store the functions as well as a count variable to keep track of size of dynamic array.
