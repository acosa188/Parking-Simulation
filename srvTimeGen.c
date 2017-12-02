/* run: cc srvTimeGen.c rvg.c -lm*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rvg.h"
#include "datgen.h"

#define NUMCARS 100000
//#define DEBUG 1

void srv_run(const char *type, const char* filename){
    
  float result = 0;
  FILE *file;

  srandom(1234567);

  /*Write the data on this file*/
    file = fopen(filename, "w");

  if( file == 0){
    printf("Can't open the file!");
  }
  else{
    if(strcmp("deterministic",type) == 0){
      #ifdef DEBUG
      printf("deterministic file has been made\n");
      #endif
      for(int i = 0; i < NUMCARS; i++){
	result = Deterministic();
	fprintf(file,"%f",result);
	fprintf(file,"%s","\n");	
      }
    }else if(strcmp("exponential",type) == 0){
      #ifdef DEBUG
      printf("exponential file has been made\n");
      #endif
      for(int i = 0; i < NUMCARS; i++){
	result = Exponential(1.5);
	fprintf(file,"%f",result);
	fprintf(file,"%s","\n");    
      }
    }else if(strcmp("hyper-exponential",type) == 0){
      #ifdef DEBUG
      printf("hyper-exponential file has been made\n");
      #endif
      for(int i = 0; i < NUMCARS; i++){
	result = HyperExponential(1.0,2.0);
	fprintf(file,"%f",result);
	fprintf(file,"%s","\n"); 
      }
    }else if(strcmp("correlated exponential",type) == 0){
      #ifdef DEBUG
      printf("correlated-exponential file has been made\n");
      #endif
      for(int i = 0; i < NUMCARS; i++){
	result = Corr_Exponential(1.5,0.2);
	fprintf(file,"%f",result);
	fprintf(file,"%s","\n");    
      } 
    }else{
      printf("No such option exist! \n");
      return;
    }
  }
  fclose(file);
}

