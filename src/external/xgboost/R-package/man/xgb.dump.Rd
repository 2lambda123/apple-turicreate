% Generated by roxygen2 (4.1.1): do not edit by hand
% Please edit documentation in R/xgb.dump.R
\name{xgb.dump}
\alias{xgb.dump}
\title{Save xgboost model to text file}
\usage{
xgb.dump(model = NULL, fname = NULL, fmap = "", with.stats = FALSE)
}
\arguments{
\item{model}{the model object.}

\item{fname}{the name of the text file where to save the model text dump. If not provided or set to \code{NULL} the function will return the model as a \code{character} vector.}

\item{fmap}{feature map file representing the type of feature.
Detailed description could be found at
\url{https://github.com/dmlc/xgboost/wiki/Binary-Classification#dump-model}.
See demo/ for walkthrough example in R, and
\url{https://github.com/dmlc/xgboost/blob/master/demo/data/featmap.txt}
for example Format.}

\item{with.stats}{whether dump statistics of splits
       When this option is on, the model dump comes with two additional statistics:
       gain is the approximate loss function gain we get in each split;
       cover is the sum of second order gradient in each node.}
}
\value{
if fname is not provided or set to \code{NULL} the function will return the model as a \code{character} vector. Otherwise it will return \code{TRUE}.
}
\description{
Save a xgboost model to text file. Could be parsed later.
}
\examples{
data(agaricus.train, package='xgboost')
data(agaricus.test, package='xgboost')
train <- agaricus.train
test <- agaricus.test
bst <- xgboost(data = train$data, label = train$label, max.depth = 2,
               eta = 1, nthread = 2, nround = 2,objective = "binary:logistic")
# save the model in file 'xgb.model.dump'
xgb.dump(bst, 'xgb.model.dump', with.stats = TRUE)

# print the model without saving it to a file
print(xgb.dump(bst))
}
