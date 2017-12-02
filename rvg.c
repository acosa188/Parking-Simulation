#include <stdlib.h>
#include <math.h>
#include "rvg.h"


#define NUMGAMES 10   /* Number of games to simulate */

/* Debugging output */
#define DEBUG 1

/***********************************************************************/
/*                 RANDOM NUMBER GENERATION STUFF                      */
/***********************************************************************/

/* Parameters for random number generation. */
#define MAX_INT 2147483647       /* Maximum positive integer 2^31 - 1 */


float prev = 0.0;

/* Generate a random floating point value uniformly distributed in [0,1] */
float Uniform01()
  {
    
    float randnum;

    randnum = (float) 1.0 * random();
    while(randnum == 0.0){
    /* get a random positive integer from random() */
      randnum = (float) 1.0 * random();
    }
    /* divide by max int to get something in (0..1)  */
    randnum = (float) randnum / (1.0 * MAX_INT); 

    return( randnum );
  }

/* Generate an Exponential Variate */
float Exponential(float mean){
  float random,result;
   
  random = Uniform01();
  result = -(mean) * log(random);
  return result;
  }

/* Generate a Hyper-exponential */
float HyperExponential(float mean1, float mean2){
 
  if(Uniform01() < 0.5){
    return Exponential(mean1);
  }
  else
    return Exponential(mean2);
}
/* Generate a Poisson Variate */

float Poisson(float lambda){
  return Exponential(1.0/lambda);
  /*Test for correlation*/
  // return Corr_Exponential(1.0/lambda,0.20);
}

/* Deterministic */
float Deterministic(){
  return 1.5;
}

/*Exponential with a Corrolation*/
float Corr_Exponential(float mean, float corr){
   float corrnum = 0.0;

   float random, result;
   
   random = Uniform01();
   corrnum = Uniform01();
   
   
   if(corrnum < corr){
     if(prev != 0.0)
       random = prev;
   }
   result = -(mean) * log(random);
   prev = random;
   
   return result;
   
}
