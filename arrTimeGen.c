/*run: cc arrTimeGen.c rvg.c -lm*/
#include <stdio.h>
#include <stdlib.h>
#include "rvg.h"
#include "datgen.h"

#define NUMCARS 10000
void arr_run(float lambda,const char *argv){
  float result = 0;
  FILE *file;  
    
  /*Write the data on this file*/
  file = fopen(argv, "w");

  srandom(1342567);
  if( file == 0){
    printf("Can't open the file!");
  }
  else{
    for(int i = 0; i < NUMCARS; i++){
      result = result + Poisson(lambda);
      fprintf(file,"%8.2f",result);
      fprintf(file,"%s","\n");
    }
  }
  fclose(file);
}
