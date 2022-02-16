String Replace

Author: Austin Bevacqua

Prerequisites
    The program requires a instaliation of the gcc C compiler.

Overall design and functionality
    The design implements finding and replacing algorithms to find every instance of a word in a larger word,
	and then replace it with another word
    ANSI codes are used to manipulte the output text

Compiling the program
    Simple run "make" to compile the program
    Optionally, run make INDEX=1 to enable the output of the index locations
    Furthermore, run "make clean" to delete all .o files.

Running the program
    The algorithm ust run with the following arguments
    ./stringReplace <string> <word_to_be_replaced> <replacement_word> <
    The first 3 arguments can be encased inside of double quotes (""), 
	but this is unnecessary if the strings have no spaces

Example of the program running
    ./stringReplace "he loves helicopter" he she red blue

    