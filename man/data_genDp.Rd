% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/FPOPapprox2D.R
\name{data_genDp}
\alias{data_genDp}
\title{data_genDp}
\usage{
data_genDp(
  p,
  n,
  chpts = NULL,
  means = matrix(0, ncol = 1, nrow = p),
  noise = 1
)
}
\arguments{
\item{p}{parameter of dimension.}

\item{n}{number of data point.}

\item{chpts}{a vector of increasing changepoint indices (last element is always less then n).
By default, 'chpts = NULL' (the data without changepoints).}

\item{means}{matrix of successive means for data, by default 'means = matrix(0, ncol = 1, nrow = p)'.}

\item{noise}{standard deviation of an additional normal noise, by default 'noise = 1'.}
}
\value{
matrix of data of dimension p x n with a given values of means by the segmentation.
}
\description{
Generation of data of dimension p with a given values of means and changepoints
}
\examples{
set.seed(13)

size <- 1000

Data1 =  data_genDp(p = 2, n = size, chpts = NULL, means = matrix(0, ncol = 1, nrow = 2), noise = 1) 

Data2 =  data_genDp(p = 2, n = size, chpts = 500, means = matrix(c(0,0,1,1), nrow = 2), noise = 1) 
}
