<a id="top"></a>
#  fpop2D Vignette
### Liudmila Pishchagina
### April 1, 2021

## Quick Start

`FPOPapprox2D` is an R package written in Rcpp/C++ and developed to detection changepoints using the Functional Pruning Optimal Partitioning method (FPOP) in `p`-variate time series of length `n`. 

The package implements the following types of FPOP-pruning: 

`type = 1`: ("intersection" of sets), approximation - "rectangle"; 

`type = 2`:("intersection" of sets)"minus"("union" of sets), approximation - "rectangle";

`type = 3`: (last disk)"minus"("union" of sets), approximation - "disk".


We present a basic use of the main functions of the `FPOPapprox2D` package. 

We install the package from Github:

```r
#devtools::install_github("lpishchagina/FPOPapprox2D")
library(FPOPapprox2D)
```

## The function data_genDp

The `data_genDp` function simulates a `p`-variate time series of length `n` with the arguments:

`p`  is the time series dimension.

`n`  is the time series length.

`chpts` is the changepoint vector that gives the last index of each segment.

The last element of `chpts` always equals to the length of time series.

`means` matrix of successive means for the `p`-variate time series.

The length of each matrix row is equal to the length of `chpts`.

`noise` is a variance of the time series (by default it is equal to `1`).


```r
Data =  data_genDp(p = 3, n = 100, chpts = c(100), means = matrix(c (0, 0, 0), nrow = 3), noise = 1) 
```
## The function FPOPDp

The `FPOPDp` function returns the result of the segmentation of FPOP-method using the parameters:

`data` is the `p`-variate time series (matrix of real numbers with p-rows and n-columns).

`penalty` is the value of penalty (a non-negative real number).

The `penalty` here equals to a classic `2*(noise^2)*log(n)`. 

`type` is a value defining the  type of geometry for FPOP-pruning.

The `type` must be either `1`, `2` or `3`:

`type = 1`: ("intersection" of sets), approximation - "rectangle"; 

`type = 2`:("intersection" of sets)"minus"("union" of sets), approximation - "rectangle";

`type = 3`: (last disk)"minus"("union" of sets), approximation - "disk".

We choose a Gaussian cost.

```r
library(base)

set.seed(13)

dim <-3

size <- 1000

sigma <- 1

beta <- 2 * sigma * log(size)

Data <- data_genDp(p = dim, n = size, chpts = c(size), means = matrix(c (0, 0, 0), nrow = 3), noise = 1) 

resFPOP1 <- FPOPDp(Data, penalty = beta, type = 1)

## resFPOP1$chpts
## [1] 1000
## resFPOP1$means
## $means[[1]]
##[1] -0.0031129231  0.0008128666  0.0146805743
## resFPOP1$globalCost
##[1] -13.81551
```

```
resFPOP2 <- FPOPDp(Data, penalty = beta, type = 2)

## resFPOP2$chpts
## [1] 1000
## resFPOP2$means
## $means[[1]]
##[1] -0.0031129231  0.0008128666  0.0146805743
## resFPOP2$globalCost
##[1] -13.81551
```

```
resFPOP3 <- FPOPDp(Data, penalty = beta, type = 2)

## resFPOP3$chpts
## [1] 1000
## resFPOP3$means
## $means[[1]]
##[1] -0.0031129231  0.0008128666  0.0146805743
## resFPOP3$globalCost
##[1] -13.81551
```
`chpts` is the changepoint vector that gives the last index of each segment.

The last element of `chpts` always equals to the length of time series.

`means` is the list of successive means for the p-variate time series.

`globalCost` is the overall Gaussian cost of the segmented data. 

[Back to Top](#top)