
#if !defined( _RVG_)
#define _RVG_


float Uniform01();
float Exponential(float mean);
float Poisson(float lambda);
float HyperExponential(float mean1, float mean2);
float Corr_Exponential(float mean, float corr);
float Deterministic();

#endif
