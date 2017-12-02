
/* -------------------------------------------------------------------------
 * This program simulates a single-server FIFO service node using arrival
 * times and service times read from a text file.  The server is assumed
 * to be idle when the first job arrives.  All jobs are processed completely
 * so that the server is again idle at the end of the simulation.   The
 * output statistics are the average interarrival time, average service
 * time, the average delay in the queue, and the average wait in the service 
 * node. 
 *
 * Name              : ssq1.c  (Single Server Queue, version 1)
 * Authors           : Steve Park & Dave Geyer
 * Modified by       : Arjun Cosare
 * Language          : ANSI C
 * Latest Revision   : 9-01-98
 * Compile with      : gcc ssq1.c 
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>                             
#include <math.h>
#include "rvg.h"
#include "datgen.h"

               
#define START        0.0
#define COMBINATION  16
#define CARS         10000
#define DEBUG        1

long   count     = 0;                        /* job index                           */
float arrival   = START;                    /* arrival time                        */
float delay;                                /* delay in queue                      */
float service;                              /* service time                        */
float wait;                                 /* delay + service                     */
float departure = START;                    /* departure time                      */  
  
struct Data{
  float sum_delay;                          /* sum of queueing delay                */
  float avg_delay;                          /* average queueing delay               */
  float std_delay;                          /* standard derivation of queueing delay*/
  float mean_delay;                         /* average queueing delay               */
  float var_delay;                          /* varience of queueing delay           */
  float delays[CARS];                       /* record of delays                     */
}res[COMBINATION];
  
/* =========================== */
   float GetArrival(FILE *fp)                 /* read an arrival time */
/* =========================== */
{ 
  float a;

  fscanf(fp, "%f\n", &a);
  return (a);
}

/* =========================== */
   float GetService(FILE *fp)                 /* read a service time */
/* =========================== */
{ 
  float s;

  fscanf(fp, "%f\n", &s);
  return (s);
}
void reset(){
    count     = 0;                        
    arrival   = START;                   
    delay     = START;                           
    service   = START;                             
    wait      = START;                                 
    departure = START;                    
}
void test(){
  FILE *file;
  
  file = fopen("arv0.data", "w");
  for(int i = 0; i < CARS; i++){
    fprintf(file,"%f",res[3].delays[i]);
	fprintf(file,"%s","\n");
  }
  fclose(file);
}
void printTable(){
    printf("Lambda               Det                                    Exp                        Hyper                       CorrExp          \n");
    printf(" 0.50   |    mean: %8.2lf std: %8.2lf  |   mean: %8.2lf std: %8.2lf  |  mean: %8.2lf std: %8.2lf  |  mean: %8.2lf std: %8.2lf | \n",res[0].mean_delay, res[0].std_delay,res[1].mean_delay, res[1].std_delay,res[2].mean_delay, res[2].std_delay,res[3].mean_delay, res[3].std_delay);
    printf(" 0.55   |    mean: %8.2lf std: %8.2lf  |   mean: %8.2lf std: %8.2lf  |  mean: %8.2lf std: %8.2lf  |  mean: %8.2lf std: %8.2lf |\n",res[4].mean_delay, res[4].std_delay,res[5].mean_delay, res[5].std_delay,res[6].mean_delay, res[6].std_delay,res[7].mean_delay, res[7].std_delay);
    printf(" 0.60   |    mean: %8.2lf std: %8.2lf  |   mean: %8.2lf std: %8.2lf  |  mean: %8.2lf std: %8.2lf  |  mean: %8.2lf std: %8.2lf |\n",res[8].mean_delay, res[8].std_delay,res[9].mean_delay, res[9].std_delay,res[10].mean_delay, res[10].std_delay,res[11].mean_delay, res[11].std_delay);
    printf(" 0.65   |    mean: %8.2lf std: %8.2lf  |   mean: %8.2lf std: %8.2lf  |  mean: %8.2lf std: %8.2lf  |  mean: %8.2lf std: %8.2lf |\n",res[12].mean_delay, res[12].std_delay,res[13].mean_delay, res[13].std_delay,res[14].mean_delay, res[14].std_delay,res[15].mean_delay, res[15].std_delay);
}
void calc(const char *file1, const char *file2, int ind){
  FILE   *fp_arr,*fp_serv;                     /* input data file                     */    
  float   temp_var,temp1_var   = 0.0;

    
    fp_arr = fopen(file1, "r");
    fp_serv = fopen(file2, "r");
    if (fp_arr == NULL || fp_serv == NULL) {
        if(fp_arr == NULL)
            fprintf(stderr, "Cannot open input file %s\n", file1);
        else
            fprintf(stderr, "Cannot open input file %s\n", file2); 
        return;
    }

    while (!feof(fp_arr) && !feof(fp_serv)) {
        count++;
        arrival                       = GetArrival(fp_arr);
        if (arrival < departure) 
            delay                     = departure - arrival;        /* delay in queue      */
        else 
            delay                     = 0.0;                        /* no delay            */
        service                       = GetService(fp_serv);
        wait                          = delay + service;            /* wait = soujorn time */
        departure                     = arrival + wait;             /* time of departure   */
        res[ind].sum_delay           += delay;
        res[ind].delays[count - 1]    = delay;
    }


    res[ind].mean_delay = res[ind].sum_delay / CARS;

    /*Calculate the standard deviation*/
    for(int i = 0; i < CARS; i++){
        //res[ind].var_delay += exp2(res[ind].delays[i] - res[ind].mean_delay);
        temp_var = pow(res[ind].delays[i] - res[ind].mean_delay,2);
        temp1_var += temp_var;
    }

    //res[ind].var_delay = res[ind].var_delay/CARS;
    res[ind].var_delay = temp1_var/CARS;
    res[ind].std_delay = sqrt(res[ind].var_delay);
    
    /* resets the variables for the next computations*/
    reset();

    fclose(fp_arr);
    fclose(fp_serv);  
}
/* ============== */
int main(int argc, char *argv[])
/* ============== */
{


  if(argc == 1){
    /*Generates all arrival files*/
    /*I know, horrible code right?*/
    arr_run(0.50,"arr0.data");
    arr_run(0.55,"arr1.data");
    arr_run(0.60,"arr2.data");
    arr_run(0.65,"arr3.data");

    /*Generate all service files*/
    srv_run("deterministic","det.data");
    srv_run("exponential","exp.data");
    srv_run("hyper-exponential","hyp.data");
    srv_run("correlated exponential","corr.data");
    
    
    /* intialization */
    reset();
    
    for(int i = 0; i < COMBINATION; i++){
        res[i].sum_delay = START;
        res[i].avg_delay = START;
        res[i].std_delay = START;
        res[i].mean_delay = START;
        res[i].var_delay  = START;
        for(int j = 0; j < CARS; j++){
            res[i].delays[j] = START;
        }
    }

    /* Calcuate each values for all possible combination of files */
    /* This might be a gross code, but bare with me until I figure 
       out a cleaver way of doing it*/
    calc("arr0.data","det.data",0);
    calc("arr0.data","exp.data",1);
    calc("arr0.data","hyp.data",2);
    calc("arr0.data","corr.data",3);
    
    calc("arr1.data","det.data",4);
    calc("arr1.data","exp.data",5);
    calc("arr1.data","hyp.data",6);
    calc("arr1.data","corr.data",7);

    calc("arr2.data","det.data",8);
    calc("arr2.data","exp.data",9);
    calc("arr2.data","hyp.data",10);
    calc("arr2.data","corr.data",11);

    calc("arr3.data","det.data",12);
    calc("arr3.data","exp.data",13);
    calc("arr3.data","hyp.data",14);
    calc("arr3.data","corr.data",15);    
    
    #ifdef DEBUG
    test();
    #endif
    printTable();
  }
    else{
        printf("Not enough or Too Much Arguments");
    }
  return (0);
}
