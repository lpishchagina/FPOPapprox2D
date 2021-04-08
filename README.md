<a id="top"></a>
#  FPOPapprox2D Vignette
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

The last element of `chpts` is always less than to the length of time series.

By default, `chpts = NULL`  for the data without changepoints. 

`means` matrix of successive means for the `p`-variate time series.

By default, `means = matrix(0, ncol = 1, nrow = p)`  for the data without changepoints. 

The length of each matrix row is equal to the length of `chpts` plus one.

`noise` is a variance of the time series (by default it is equal to `1`).


```r

set.seed(13)

size <- 1000

Data1 =  data_genDp(p = 2, n = size) 

Data2 =  data_genDp(p = 2, n = size, chpts = 500, means = matrix(c(0,0,1,1), nrow = 2), noise = 1) 

```
## The function FPOPDp

The `FPOPDp` function returns the result of the segmentation of FPOP-method using the parameters:

`data` is the `p`-variate time series (matrix of real numbers with p-rows and n-columns).

`penalty` is the value of penalty (a non-negative real number).

The `penalty` here equals to a classic `2*p*(noise^2)*log(n)`. 

`type` is a value defining the  type of geometry for FPOP-pruning.

The `type` must be either `1`, `2` or `3`:

`type = 1`: ("intersection" of sets), approximation - "rectangle"; 

`type = 2`:("intersection" of sets)"minus"("union" of sets), approximation - "rectangle";

`type = 3`: (last disk)"minus"("union" of sets), approximation - "disk".

We choose a Gaussian cost.

```r
library(base)

set.seed(13)

dim <-2

size <- 1000

sigma <- 1

beta <- 2 * sigma * dim * log(size)

Data1 =  data_genDp(p = dim, n = size) 

Data2 =  data_genDp(p = dim, n = size, chpts = 500, means = matrix(c(0,0,1,1), nrow = dim), noise = 1)

FPOPDp(Data1, penalty = beta, type = 1)

FPOPDp(Data1, penalty = beta, type = 2)

FPOPDp(Data1, penalty = beta, type = 3)

$chpts
numeric(0)

$means
$means[[1]]
[1] -0.0031129231  0.0008128666

$globalCost
[1] 5.172187e-231


```

```
FPOPDp(Data2, penalty = beta, type = 1)

FPOPDp(Data2, penalty = beta, type = 2)

FPOPDp(Data2, penalty = beta, type = 3)

$chpts
[1] 500

$means
$means[[1]]
[1] -0.01552099 -0.02517320

$means[[2]]
[1] 1.044882 0.975139


$globalCost
[1] -27.63102

```

`chpts` is the changepoint vector that gives the last index of each segment.

The last element of `chpts` always equals to the length of time series.

`means` is the list of successive means for the p-variate time series.

`globalCost` is the overall Gaussian cost of the segmented data. 

[Back to Top](#top)