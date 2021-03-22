#' @title data_gen2D
#'  
#' @description Generation of data of dimension 2 with a given values of means and changepoints
#' 
#' @param n number of data point.
#' @param p parameter of dimension.
#' @param changepoints a vector of increasing changepoint indices (last element is always n!).
#' @param means matrix of successive means for data.
#' @param noise standard deviation of an additional normal noise.
#'  
#' @return matrix of data of dimension p x n with a given values of means by the segmentation.
#'  
#' @examples
#' data_genDp(p = 2, n = 4, chpts = c(2, 4), means = matrix(c (0, 1, 1, 0), nrow = 2), noise = 1)
#' data_genDp(p = 3, n = 4, chpts = c(2, 4), means = matrix(c (0, 0, 0, 10, 10, 10), nrow = 3), noise = 1)
 
data_genDp <- function(p, n, chpts, means, noise = 1){
  #---stop---#
  if (n!= chpts[length(chpts)]){stop('last element of changepoints is always n')}
  if(!is.numeric(chpts)){stop('changepoints are not all numeric')}
  if(is.unsorted(chpts)){stop('changepoints should be an increasing vector')}
  if(!is.numeric(means)){stop('means are not all numeric')}
  if(length(chpts) != length(means[1,])){stop('changepoints and means vectors are of different size')}
  if(!is.double(noise)){stop('noise is not a double')}
  if(noise < 0){stop('noise must be non-negative')}
  #---function---#	
  data <- matrix(0,p,n)
  InttT<- diff(c(0,chpts))
  for (i in 1:p){data[i,] <- rep(means[i,], InttT) + rnorm(n, 0, noise)}
  return(data)
}
