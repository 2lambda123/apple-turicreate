% Generated by roxygen2 (4.1.1): do not edit by hand
% Please edit documentation in R/getinfo.xgb.DMatrix.R
\docType{methods}
\name{getinfo}
\alias{getinfo}
\alias{getinfo,xgb.DMatrix-method}
\title{Get information of an xgb.DMatrix object}
\usage{
getinfo(object, ...)

\S4method{getinfo}{xgb.DMatrix}(object, name)
}
\arguments{
\item{object}{Object of class \code{xgb.DMatrix}}

\item{...}{other parameters}

\item{name}{the name of the field to get}
}
\description{
Get information of an xgb.DMatrix object
}
\details{
The information can be one of the following:

\itemize{
    \item \code{label}: label Xgboost learn from ;
    \item \code{weight}: to do a weight rescale ;
    \item \code{base_margin}: base margin is the base prediction Xgboost will boost from ;
    \item \code{nrow}: number of rows of the \code{xgb.DMatrix}.
}
}
\examples{
data(agaricus.train, package='xgboost')
train <- agaricus.train
dtrain <- xgb.DMatrix(train$data, label=train$label)
labels <- getinfo(dtrain, 'label')
setinfo(dtrain, 'label', 1-labels)
labels2 <- getinfo(dtrain, 'label')
stopifnot(all(labels2 == 1-labels))
}
