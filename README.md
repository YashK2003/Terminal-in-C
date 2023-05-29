# Terminal in C



## Requirements

- GCC compiler
- Linux OS (preferably Ubuntu)
---

## Running Shell

From the root directory of project, run `make` followed by `./a.out`

---
## File & Functions

### Supporting Files

#### Files containing functions required for proper functioning of the shell.

- `main.c`

  - Run Shell Loop
  - Extract Arguments from command
  - Bind functions from different files together

- `main.h`

  - contains included headers 

- `display.c`

  - for the view of the terminal

- `callexe.c`

  - calling fg and bg processes
  - for tokenising strings commands

- `exe.c`

  - for executing various commands

- `data.txt`

  - file for storing the commands for history

- `readinput.c`

  - file for reading input from user


### Command Files

#### Files containing functions to run a particular command.

- `echo.c`

  - Contains commands `echo`
  - Outputs the strings that are passed to it as arguments.
    

- `cd.c`

  - Navigate to different directories

- `pwd.c`

  - Prints the working directory

- `forground.c`

  - Brings a process to foreground and changes it state to Running.

- `background.c`

  - Changes status of background process from Stopped to Running.

- `history.c`

  - Used to view the previously executed commands.

- `pinfo.c`

  - Prints info about process with given PID (current process if none is given)


- `ls.c`

  - Prints all files/sub-directories in a location
  - Flags implemented: `a` and `l`
  - Multiple directories supported


- `autocom.c`

  - autocomplete the rest of the folder or file names

- `disco.c`

  - Prints all the file names by recursively going through all folders.

- `jobs.c`

  - Prints all currently running background processes.


- `pipe.c`

  - implement the pipe command
  - Used to combine two or more commands.
  - pass the output of one command  as input to another command


- `sig.c`

  - for the sig fg and bf command
---

## Functions implemented overall

    * cd command
    * pwd
    * echo
    * cd  
    * pwd
    * history
    * pinfo
    * ls
    * runs background processes
    * runs foreground processes
    * discover command
    * input output redirection
    * jobs 
    * sig
    * fg 
    * bg
    * autocomplete
    * ctrl + C
    * ctrl + Z
    * ctrl + D

---

Will try to implement more features as I get time 😇.