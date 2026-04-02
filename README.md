# CS4760-project2
<br>Name: Elisa Reyes
<br>Date: 03/31
<br>Environment: vi, visual studio code
<br>How to compile the project: Type 'make'
<br>Type 'make clean' to do a clean
<br> Example of how to run the project: ./oss -n 3 -s 2 -t 4 -i 0.6
<br>Generative AI used: chatgpt
<br>Prompts:
<br>Update my code Using the following pseudocode, write a simple program in C so that oss will go into a loop and start doing a fork() and then an exec() call to launch worker processes up to -s simul number of times. Then oss should make sure to update the process table with information as it is launching user processes. Next, oss() will be going into a loop, incrementing the clock and then constantly checking to see if a child has terminated.
<br>Summary: The inital generated code seemed to have good functionality