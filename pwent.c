#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pwent.h"

double he_entropy(int l, int n);

int main(int argc, char *argv[]){
    int length, n;
    double e = 0.0;
    char * input;

    if(argc == 3){         
        length = (int) atoi(argv[1]);
        n = (int) atoi(argv[2]);
        }
    
    else if(argc == 1){
        input = prompti("Length of string: ");
        length = input;
        input = prompti("Number of possible symbols: ");
        n = input;
        }
    else if(argc == 2){
        length = strlen(argv[1]);
        printf("Length: %d\n", length);
        n = uniqueb(argv[1]);
        printf("Unique symbols: %d\n", n);
        }  
    
    else{
        printf("Usage: %s length alphabet_size ", argv[0]);
        return 1;
        }

    e = he_entropy(length, n);
    printf("%4.4f bits.\n\n", e);
    return 0;

}

int prompti(char * ptext){
    char input[16];
    printf("%s\n", ptext);
    fgets(input, 16, stdin);
    return atoi(input);
}

double he_entropy(int l, int n){
    return log2(pow(l, n));
}

int uniqueb(char * in){ //Find the number of unique characters in a string
    char * buff;
    int buffsize = 256;

    int i = 0;
    int j = 0;
    int last = 1;

    char found = 0;
    
    buff = (char *) calloc(buffsize, sizeof(char));

    printf("  uniqueb - Buff: %d %s\n", strlen(buff), buff);
    printf("  uniqueb - In:   %d %s\n", strlen(in), in);
    
    
    buff[0] = in[0];
    
    //while(last < buffsize){
        for(i = 0; i < strlen(in); i++){
            for(j = 0; j < last; j++){
                if(in[i] == buff[j]){
                    found = 1;
                }
            }
            if(!found){
                buff[last++] = in[i];
            }
            found = 0;
        }    
    
    //} 
    printf("  uniqueb - Buff: %d %s\n", strlen(buff), buff);
    printf("  uniqueb - In:   %d %s\n", strlen(in), in);

    return strlen(buff);

}

double he_strentropy(char * in){
    int unique = uniqueb(in);
    int len = strlen(in);
    double e = he_entropy(unique, len);
    
    return e;
    
}
