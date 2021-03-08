#ifndef GAUSSECOST2D_H
#define GAUSSECOST2D_H

#include <vector>

//##############################################################################//
//########################Class GausseCostDp####################################//
class GausseCostDp{
public:
  //------------------------------constructor-------------------------------------//
  GausseCostDp(){};
  GausseCostDp(unsigned int dim, unsigned int i, unsigned int t, double* si_1, double* st, double mi_1pen);
  //------------------------------accessory---------------------------------------//
  unsigned int get_coef() const;
  double get_coef_Var() const;
  double get_mi_1_p() const;
  std::vector<double> get_mu();
  double get_min();     // q_it is a paraboloid => min{q_it} = coef_Var + mi_1_p
private:
  unsigned int coef;                //(t - i + 1)
  double coef_Var;                  //coef * sumVar(xk_it)
  double mi_1_p;                    //mi_1 + penalty
  std::vector<double> mu;           //mu[k] = E(xk_it), k =0,dim-1
  
};
//#########################End Class GausseCostDp###############################//
#endif // GAUSSECOSTDP