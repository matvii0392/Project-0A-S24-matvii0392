# Project-0A-S24-matvii0392
In this lab, we refreshed the knowledge of programming in C. We started learning about Linux utilities' implementation.
We also began learning about system calls and their usage. 
This project is Part A of Project 0.
The program tuls lists information about the FILES in a directory (folder). 
By default, tuls lists the files in the current directory.
If there is no additional parameter for the tuls command, it lists the files in the current directory.
If the directory path is included with the tuls command, then it prints the list of files in the current
directory and recursively prints the list of files in all directories specified by the directory path argument.
For example:
```
prompt> **./tuls** 
  lscmd.c
  a.out
  ..
  .
  
OR

prompt> **./tuls direc   <**where **direc** is a directory path**>**
[[direc]]
  ->direc_1_file
  ->direc_2_file
->local_1_file
->local_2_file
->local_3_file
..
.
```
