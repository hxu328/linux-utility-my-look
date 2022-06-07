# linux-utility-my-look
my-look is a simple program based on the utility look, Both look and my-look take a string as input and return any lines in a file that contain that string as a prefix. 


## Example Usage
prompt> ./my-look -f /usr/share/dict/words gn

The “./” before the my-look above is a UNIX thing; it just tells the system which directory to find my-look in (in this case, in the “.” (dot) directory, which means the current working directory).  As shown, my-look reads the file /usr/share/dict/words and prints out all the lines that start with the letters "gn". 

## Compiling
prompt> gcc -o my-look my-look.c -Wall -Werror
