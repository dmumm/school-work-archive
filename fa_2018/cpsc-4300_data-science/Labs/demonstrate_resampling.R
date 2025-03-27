rm(list = ls())
library(ISLR)
library(boot) # can be used to implement k-fold into glm itself

# Author: Alex Herzog, Dylan Mumm
# Date: Oct 5th, 2018
# Purpose: Demonstrate resampling methods

attach(Default)
set.seed(42)

#  -----------------------------------
#
#   1) validation set
#
#  -----------------------------------

N <- nrow(Default)           # size of data set
train <- sample(N, N / 2)    # Vector with 5000 random numbers between 1 and 10,000
test <- seq(N)[-train]       # Vector of every value between 1 and 10,000 not in train

# Model with default as response, balance + income and family (a binomial) as predictors,
# restricted with the values of train as data points
glm.fit <- glm(default ~ balance + income, family = binomial, subset = train)

# Predict values of test set by testing all values test set
pred.probs <- predict(glm.fit, Default[test,], type = "response")

# Assigning every value of the vector with the label of No, unless its probability is above .05
pred.default <- rep("No", N/2)
pred.default[pred.probs > 0.5] <- "Yes"

# Generates error rate of data (Wrong in 2.52% of cases)
error.rate <- mean(pred.default != default[test])

#  -----------------------------------
#
#   2) k-fold cross validation
#
#  -----------------------------------

# Data is data, glmfit is the output, cost is a supplied model, K is amount of folds
# cv.glm(data, glmfit, cost, K)

glmfit <- glm(default ~ balance + income, family = binomial)

myCost <- function(r, pi = 0) {
  mean(abs(r-pi) > 0.5)
  
}

cv.error.10 <- cv.glm(Default, glm.fit, myCost, K=10)   # Making model with above parameters
names(cv.error.10)                                      # Returns stored call, K, delta, and seed
cv.error.10$delta                                       # Returns error rate and something else idk

# ----------------------------------------
#
#   3) Leave-one-out cross validation
#
# ----------------------------------------

loocv.error <- cv.glm(Default, glm.fit, myCost, K=N) # slow af lol
