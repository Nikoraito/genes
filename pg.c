// Genetic algorithm password generator
// 
//  Goal: Practice using genetic algorithms by using one to generate passwords
//      with an optimum information entropy number, decided by running it through
//      my entropy program.
//  
//  -g, --generations   - number of generations to create
//  -s, --survivors     - number of survivors per generation
//  -t, --threshold     - number below which all will be rejected
//  -i, --initial       - specify a beginning DNA string
//  

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>


#include "pwent.h"
#include "pg.h"

int main(int argc, char* argv[]){
    int generations = 0;
    int survivors = 0;
    double threshold = 0;
    char * initial;
    
    int c = 0;
    
    while((c = getopt(argc, argv, "f:g:s:t:i:")) != -1){ 
        switch(c){
            case 'f':

                printf("Loading DNA... %s\n", optarg);
                  
                initial = calloc(strlen(optarg), sizeof(char));
                initial = load_dna(optarg);
                printf("DNA loaded.\n");

            case 'g':
                generations = atoi(optarg);
                break;

            case 's':
                survivors = atoi(optarg);
                break;

            case 't':
                threshold = atof(optarg);
                break;
            case 'i':
                initial = optarg;
                break;
            default:
                printf("Invalid arg: %c\n", c);
                return -1;
        }
        
    }

    //printf("Simulating with parameters:\ng: %d\ns: %d\nt: %f\ni: %s\n\n", generations, survivors, threshold, initial);
    fflush(stdout);
    simulate(generations, survivors, threshold);

}

char * load_dna(char * name){
    FILE * fp;
    char * dna;
    
    struct stat buff;
    int dnalen;
    
    char * path = calloc(64, sizeof(char));
    strcat(path, "dna/");
    strncat(path, name, 40);

    printf("      load_dna: Reading %s... (%s)\n", path, name); 


    fp = fopen(path, "r");


    if(fp == NULL){
        fp = fopen(path, "w+");
        fprintf(fp, "DNA: %s\n1A\n1B\n1C\n", name);
        printf("       File not found - %s created.\n\n", name);
        rewind(fp);
    }
    
    dna = calloc(128, sizeof(char));

    int i = 0;
    int c = 0;
    
    while((c = fgetc(fp)) != EOF){
        if (c != EOF){
            dna[i++] = c;
        }
    }

    fclose(fp);
    return dna;
}

int enumerate_dna(char * name[], double fitness[]){
    int i = 0;
    int dnac = 0;
    DIR * dp;
    struct dirent *ep;
    dp = opendir("./dna");
    
    if(dp != NULL){
        while( ((ep = readdir(dp)) != NULL) ){
            if(ep->d_name[0] != '.'){
                printf("  > Enumerating: %s\n", ep->d_name);
                name[i] = calloc(32, sizeof(char));   // < 32 characters long!
                name[i] = ep->d_name;
                //name[i][31] = '\0'; 
                dnac = ++i;  
            }
        }
        closedir(dp);
    }

    return dnac;

   //Accumulate the names of all dna in ./dna
   //   Then load them with load_dna
   //   Return the number of strings in the array (pass a pointer for name?)
   //   Iterate through each doing check_dna and process and checkpw 
}

int simulate(int generations, int survivors, double threshold){
    int gen = 0;
    int j = 0;

    char * name[32];
    double fitness[32];

    int dnac = 0;
    
    char * current;

    for(gen = 0; gen < generations; gen++){

        dnac = enumerate_dna(name, fitness);
        
        printf("GEN1: DNA Count: %d\n", dnac);
        for(j = 0; j < dnac; j++){
            if(strlen(name[j]) > 0){
                printf(" SIM: gen%d dna%d : %s\n", gen, j, name[j]); 
                current = load_dna(name[j]);
                printf(" %s\n", current);
                
                //check_dna(current);
                //process();
                //check_pw();

            }
            else{
                printf("FUCK\n");
            }
        }

    }

    return 0;

}

int process(char * dna){
    
}

int check_dna(char * dna){
    
}

int check_pw(char * name, double threshold){

}
