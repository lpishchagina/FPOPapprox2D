#ifndef OPD2_H
#define OPD2_H

#include "Geom1.h"
#include "Geom2.h"
#include "Geom3.h"
#include "DiskDp.h"
#include "RectDp.h"
#include "GausseCostDp.h"

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include "Rcpp.h"

//################################################################################//
//############################### Class<GeomX> OPD2 ##################################//
template <class GeomX> 
class OPD2{
private:
  double penalty;                                       //value of penalty 
  unsigned int n;                                       // data length
  double** sx12;                                        // vector sum x1,x2, x1^2, x2^2
  std::vector<unsigned int> chpts;                      // changepoints vector 
  std::vector<double> means1;                           // means vector for x1
  std::vector<double> means2;                           // means vector for x2        
  double globalCost;                                    // value of global cost
  double* m;                                            // "globalCost" = m[n+1] - changepoints.size()*penalty
  GeomX geom;
  std::list<GeomX> list_geom;                               //list of geom
  std::list<DiskDp> list_disks;                      //list of disks
public:
  //------------------------------constructor-------------------------------------//
  OPD2(){}
  
  OPD2(std::vector<double>& x1, std::vector<double>& x2, double beta){
    unsigned int dim = 2;
    penalty = beta;
    n = x1.size();
    sx12 = new double*[n+1]; 
    for(unsigned int i = 0; i < n+1; i++) {sx12[i] = new double[2*dim];}
    m = new double[n + 1];        // "globalCost" = m[n+1] - chpts.size()*penalty
  }
  //---------------------------------destructor-----------------------------------//
  ~OPD2(){
    for(unsigned int i = 0; i < n+1; i++) {delete(sx12[i]);}
    delete [] sx12;
    sx12 = NULL;
    delete [] m;
    m = NULL;
  }
  //---------------------------------accessory------------------------------------//
  std::vector<unsigned int> get_chpts() const {return chpts;}
  std::vector<double> get_means1() const {return means1;}
  std::vector<double> get_means2() const {return means2;}
  double get_globalCost() const {return globalCost;}
  unsigned int get_n() const {return n;}
  double** get_sx12(){return sx12;};
  
  //------------------------------vect_sx12---------------------------------------//
  double** vect_sx12(std::vector<double>& x1, std::vector<double>& x2){
    unsigned int n = x1.size();
    for (unsigned i = 0; i < 4; i++){ sx12[0][i] = 0;}
    for (unsigned int j = 1; j < (n + 1); j++){
      sx12[j][0] = sx12[j - 1][0] + x1[j - 1];
      sx12[j][1] = sx12[j - 1][1] + x2[j - 1];
      sx12[j][2] = sx12[j - 1][2] + x1[j - 1] * x1[j - 1];
      sx12[j][3] = sx12[j - 1][3] + x2[j - 1] * x2[j - 1];
    }
    return(sx12);
  }
  //-------------------------------algoFPOPD2---------------------------------------//
  void algoFPOPD2(std::vector<double>& x1, std::vector<double>& x2, unsigned int type){
    unsigned int dim = 2;
    n = x1.size();
    sx12 = vect_sx12(x1, x2);           
    m[0] = 0;
    double** last_chpt_mean = new double*[3];         // vectors of best last changepoints, mean1 and mean2
    for(unsigned int i = 0; i < 3; i++) {last_chpt_mean[i] = new double[n];} 
    list_disks.clear();
    for (unsigned int t = 0; t < n ; t++){
      double min_val = INFINITY;                      //min value of cost
      std::vector<double> mean;                                   //means for (lbl, t)
      unsigned int lbl;                               //best last position for t
      //-----------------------new geom D_tt------------------------------------
      geom = GeomX(t); 
      geom.fillDisks(list_disks);
      list_geom.push_back(geom);
      geom.fillDisks(list_disks);    // fill disks_t_1 in geometry tt
      typename std::list<GeomX>::iterator it;
      //-----------------First run: search min----------------------------------
      it = list_geom.begin();
      list_disks.clear();
      while(it != list_geom.end()){
        unsigned int u = it->get_label_t();
        list_disks.push_back(u);
        GausseCostDp cost = GausseCostDp(dim, u, t, sx12[u], sx12[t + 1], m[u]);
        if(cost.get_min() < min_val){
          lbl = u;
          min_val = cost.get_min();
          mean = cost.get_mu();
           
        }
        ++it;
      };
      m[t + 1] = min_val + penalty;     // new min 
   //   list_disks.pop-back();            // remove label t
   //   it = list_geom.end();
    //  it-> fillDisks(list_of_disks);    // fill disks_t_1 in geometry tt
      //-----------------best last changepoints and means-----------------------
      last_chpt_mean[0][t] = lbl;       //last_chpt_mean[0] - vector of best last chpt
      last_chpt_mean[1][t] = mean[0];     //last_chpt_mean[1] - vector of means (lbl,t) for x1
      last_chpt_mean[2][t] = mean[1];     //last_chpt_mean[2] - vector of means (lbl,t) for x2
      //------------------Second run: pruning-----------------------------------
      it = list_geom.begin();      
      while (it != list_geom.end()){
        lbl = it->get_label_t();
        GausseCostDp cost = GausseCostDp(dim, lbl, t, sx12[lbl], sx12[t + 1], m[lbl]);
        
        double r2 = (m[t + 1] - m[lbl] - cost.get_coef_Var())/cost.get_coef();
        
        if (r2 <= 0){
          it = list_geom.erase(it);     //delete geom PELT 
          --it;
        }// PELT   
        else{
          if (type >= 1){
            DiskDp disk_t = DiskDp(cost.get_mu(), sqrt(r2));
            it->UpdateGeom(disk_t);
            if (it->IsEmpty()){
              it = list_geom.erase(it);//delete geom FPOP
              --it;
            }
            else{list_disks.push_back(disk_t);}
          }
        }
        ++it;
      }//while (it != list_geom.end())
    }//for
    unsigned int chp = n;
    while (chp > 0){
      chpts.push_back(chp);
      means1.push_back(last_chpt_mean[1][chp-1]);
      means2.push_back(last_chpt_mean[2][chp-1]);
      chp = last_chpt_mean[0][chp-1];
    }
    reverse(chpts.begin(), chpts.end());
    reverse(means1.begin(), means1.end());
    reverse(means2.begin(), means2.end());
    
    globalCost = m[n + 1] - penalty * chpts.size() ;
    //----------------------------memory------------------------------------------
    for(unsigned int i = 0; i < 3; i++) {delete(last_chpt_mean[i]);}
    delete [] last_chpt_mean;
    last_chpt_mean = NULL;
  }//end function
};
  


//############################# End Class OPD2 #####################################//
#endif //OPD2_H