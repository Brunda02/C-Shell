
Brief specification of all the files and their implementation:

display2.c 

- is used to take in the input and display prompt + handling the signals using ctrlc, ctrlz functions

input.c - to format the input and identify the correct function

tokenise.c - to tokenise the commands 

commands.c - implements 2nd specification in the assign2 document 

implemented cd, pwd, echo commands

In cd command these are supported:
cd.
cd..
cd~
cd -
cd file/directory

ls2.c - implements 2nd specification in the assign2 document

implements:
ls 
ls -l
ls -la
ls -a
ls file/directory
any combination of above 


processes3.c- implements background and foreground processes

processes4.c- creates a linked list to store background processes and to monitor the exit status.

repeat.c - implements 7th specification in the assign2 document 

it repeats a given command , the number of times given

headers.h - includes all required headers and global variables required..in all files

pinfo.c - implements 6th specification in the assign document 

displays the status of the running processes

history.c - implements Bonus specification in the document 
keeps the history of latest 20 commands throughout all the sessions

pipe4.c -

it handles rediection
it handles piping
it handles their combination

fgbg.c

It implements fg,bg commands

kill.c

It is used to send specific signals to a specific job

jobs.c

it implements jobs command

Limitations:

There is a limit of 100 background processes at a time.
The command entered at a time has a limit of 500 characters at a time.