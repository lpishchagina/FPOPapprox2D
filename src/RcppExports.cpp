// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// FPOP2D
List FPOP2D(std::vector<double> data1, std::vector<double> data2, double penalty, int type);
RcppExport SEXP _FPOPapprox2D_FPOP2D(SEXP data1SEXP, SEXP data2SEXP, SEXP penaltySEXP, SEXP typeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type data1(data1SEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type data2(data2SEXP);
    Rcpp::traits::input_parameter< double >::type penalty(penaltySEXP);
    Rcpp::traits::input_parameter< int >::type type(typeSEXP);
    rcpp_result_gen = Rcpp::wrap(FPOP2D(data1, data2, penalty, type));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_hello_world
List rcpp_hello_world();
RcppExport SEXP _FPOPapprox2D_rcpp_hello_world() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(rcpp_hello_world());
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_FPOPapprox2D_FPOP2D", (DL_FUNC) &_FPOPapprox2D_FPOP2D, 4},
    {"_FPOPapprox2D_rcpp_hello_world", (DL_FUNC) &_FPOPapprox2D_rcpp_hello_world, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_FPOPapprox2D(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
