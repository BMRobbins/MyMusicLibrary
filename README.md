# MyMusicLibrary
### A simple C program that loads a music library from a file and allows the user to delete, add, and search for specific song titles.

The program takes a filename as input and opens the file. It then parses the input and creates a music library which stores each song by its
title and also stores its artist and year published. This music library is sorted alphabetically by its title. After that the user is prompted 
continuously for a command. The choices for commands are I, P, D, L, Q. "I" allows the user to insert a new song into the music library. 
The program will prompt user for a title, artist and year published. "P" prints the music library in alphabetical order. "D" deletes the
song that the user specifies and removes it from the music library. "L" looks up a song specified by the user and does a binary search on 
the music library. It then provides the title, artist and year published of the song that was specified. "Q" saves the current MusicLibrary
to its file and exits the program.

