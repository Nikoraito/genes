#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "pwent.h"

char * load_dna(char * name);   //Use this function to load DNA as a string.
                                //  returns either "DNA: <$name>" or the full string of DNA.
                                //

int enumerate_dna(char * name [], double fitness []);
                                //Use this function to load 'by reference' the names and fitnesses of each piece of DNA
                                //  before each round. Fitness starts @ 0, and is updated before survivors are culled;
                                //  both arrays are emptied of the dead at the very END of each round.

int simulate(int generations, int survivors, double threshold);
                                //Use this function to generate passwords with all the DNA in ./dna
                                //  Executes $generations times
                                //  Moves all but $survivors DNA into ./dead
                                //  moves into ./dead all survivors w/ a threshold below $threshold
                                //  Prints a summary of each generation to $DATE.gen$generation.csv
                                //      .csv contains each name and a few more pieces of info for that DNA
                                //      (fitness, avg/min/max entropy/length/symbols)
                                //
int process(char * dna);   
                                //Using the DNA, interpret its contents and generate passwords in the directory ./pwds/$name
                                //  Interpet characters as commands, which may do more things than generate named passwords,
                                //  for instance, produce a copy of the DNA with mutated properties.
int check_dna(char * dna);        
                                //Using the DNA, check out its continuity, and passwords, and then accumulate stats based on it.
                                //  check to see if starts w/ "DNA:"
                                //  Check to see if all other lines XY\n

int check_pw(char * name, double threshold);      
                                //Using the dna's NAME,
                                //  Check to see if each password meets the following criteria:
                                //      Longer than 0 characters
                                //      Entropy > threshold
                                //          Count number above threshold
                                //      Passwords match [A-Z][a-z][0-9]{_-,.}
                                //      Check to make sure DNA generated at least 10 passwords
                                //      
                                //  Output 0 if dna survives
                                //      1 if DNA dies because it is too short
                                //      2 if DNA dies because 75% < of generated words meet threshold requirement
                                //      4 if DNA dies because it uses illegal characters
                                //      8 if DNA dies because it generated < 10 passwords
                                //          Or a combination of the above.
                                //  
