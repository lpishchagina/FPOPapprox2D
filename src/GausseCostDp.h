#ifndef GAUSSECOSTDP_H
#define GAUSSECOSTDP_H

#include <vector>

class GausseCostDp{
private:
  unsigned int p;
  unsigned int coef;                //(t - i + 1)
  double coef_Var;                  //coef * sumVar(xk_it)
  double mi_1_p;                    //mi_1 + penalty
  std::vector<double> mu;           //mu[k] = E(xk_it), k =0,dim-1

public:
  GausseCostDp(){};
  GausseCostDp(unsigned int dim, unsigned int i, unsigned int t, double* si_1, double* st, double mi_1pen);

  unsigned int get_p();
  unsigned int get_coef() const;
  double get_coef_Var() const;
  double get_mi_1_p() const;
  std::vector<double> get_mu();
  double get_min();     // q_it is a paraboloid => min{q_it} = coef_Var + mi_1_p
};

#endif // GAUSSECOSTDP