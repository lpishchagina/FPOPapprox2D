#ifndef GAUSSECOSTDP_H
#define GAUSSECOSTDP_H
/*
 Class GausseCostDp
 -------------------------------------------------------------------------------
 Description: 
  The Gaussian cost for the interval (i,t) in p-dimension. 
 
 Parameters:
 "p" - dimension;
  "coef" = (t - i + 1);
  "mu" - vector of means for the interval (i,t);
  "mi_1_p" - sum of the value of the optimal cost at moment (i-1) and penalty;
  "coef_Var" = coef * sumVar(xk_i:t).
 -------------------------------------------------------------------------------
 */
class GausseCostDp{
private:
  unsigned int p;
  unsigned int coef;              
  double coef_Var;                  
  double mi_1_p;                  
  double* mu;                       

public:
  GausseCostDp(){};
  GausseCostDp(unsigned int dim);
  GausseCostDp(unsigned int dim, unsigned int i, unsigned int t, double* si_1, double* st, double mi_1pen);
  
  GausseCostDp(const GausseCostDp &cost);
  
  ~GausseCostDp();
  
  void InitialGausseCostDp(unsigned int dim, unsigned int i, unsigned int t, double* &si_1, double* &st, double mi_1pen);
  unsigned int get_p() const;
  unsigned int get_coef() const;
  double get_coef_Var() const;
  double get_mi_1_p() const;
  double* get_mu();
  double get_min();     // The Gaussian cost is a paraboloid => min{The Gaussian cost} = coef_Var + mi_1_p
};

#endif // GAUSSECOSTDP