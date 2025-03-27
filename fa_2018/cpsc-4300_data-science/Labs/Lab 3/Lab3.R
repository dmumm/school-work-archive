rm(list = ls())

# +================================
# Author: Dylan Mumm
# Date: September 14th, 2018
# Purpose: Linear Regression in R
# =================================

library(MASS)
library(ISLR)

View(Boston)
names(Boston)

# Question: What happens when you apply the summary() command to the data set?
#             * Gives 6 number summary of each column
summary(Boston)

# Use attach to load the data set into the workspace. 
# This way you can call columns in the data set 
# directly without using the "$" operator:
attach(Boston)

#=======================
#
#  1. Model Fitting
#
#=======================

# Estimate a simple regression model with medv as target and lstat as predictor:
lm.fit <- lm(medv ~ lstat)

# Type lm.fit into the R terminal to look at the regression output. 
# Now apply summary() to lm.fit.
# Question: How does the output differ?
#             * Summary gives much more detail
lm.fit
summary(lm.fit)

# Question: What is the association between median house value
#           and percent of households with low socioeconomic status? 
#           Write down a sentence based on the output from the model
# 
# * A $1000 increase of a neighborhoods's median home value is assosciated with a .95% 
#   decrease in the proportion of low economic status residents 

# Estimated 95% confience intervals
confint(lm.fit)

#=======================
#
#  2. Prediction
#
#=======================

# Use the estimated coefficients and "by hand" (i.e., typing the correct equations into R)
# calculate predicted values for medv for the following values of lstat:  5, 10, and 15 percent.
# *  34.503 = 34.55 + -0.95(.5)
# *  34.455 = 34.55 + -0.95(.10)
# *  34.408 = 34.55 + -0.95(.15)

# Using the predict() function with the same values forlstatas above.  Also produce confidence intervals for your prediction:
predict(lm.fit, data.frame(lstat = c(5, 10, 15)), interval = "confidence")

# Question: Compare the results to the prediction you have done "by hand".  Do you get the sameor different results?
#           * No, as I mistakenly did the manual predictions as a decimal, forgetting that the model was made with integers.

# Prediction intervals instead of confidence intervals:
predict(lm.fit, data.frame(lstat = c(5, 10, 15)), interval = "prediction")

# Question: How do the results differ?  Why are some values different?
       # The line of best fit is identical, but the lower and upper bounds are much looser 

#===========================
#
#  3. Visualizing results
#
#===========================

# scatterplot of the target and predictor along with the least squares regression line:
plot(lstat, medv)
abline(lm.fit)

# Using lwd to adjust the width of the regression line and col to select a different color.
# Using the pch option to create different plotting symbols.
abline(lm.fit, lwd=3)
abline(lm.fit, lwd=3, col="red")
plot(lstat, medv, col="red")
plot(lstat, medv, pch=20)
plot(lstat, medv, pch="+")

# Generating an overview of all available plotting symbols:
plot(1:20, 1:20, pch=1:20)

# Applying the plot() function to the regression output. This will produce four diagnostic plots
plot(lm.fit)

# Viewing all four plots together, using the par() function to divide the plotting region into a 2×2 panel grid:
par(mfrow=c(2,2))
plot(lm.fit)

#=======================
#
#  4. Exercises
#
#=======================

rm(list = ls())

View(Auto)
attach(Auto)

# 1 Use the lm() function to perform a simple linear regression with mpg (miles per gallon)  as the
#   response and horsepower (engine horsepower) as the predictor. Use the summary() function to print the results. 

lm.fit <- lm(mpg ~ horsepower)
summary(lm.fit)
confint(lm.fit)

predict(lm.fit, data.frame(horsepower = c(98)), interval = "confidence")
predict(lm.fit, data.frame(horsepower = c(98)), interval = "prediction")



    # (a) Is there a relationship between the predictor and the response
        # Yes
    
    # (b) How strong is the relationship between the predictor and the response?
        # R-squared of .6059
    
    # (c) Is the relationship between the predictor and the response positive or negative?
       # Negative
    
    # (d) What is the predicted mpg associated with a horsepower of 98? What are the associated 95% con???dence and prediction intervals?
       # 24.467
       # [23.973, 24.961]
       # [14.809, 34.125]

#  2. Plot the response and the predictor. Use the abline() function to display the least squares regression line.
plot(mpg, horsepower)
abline(lm.fit)

#  3. Use the plot() function to produce diagnostic plots of the least squares regression ???t. Comment on any problems you see with the ???t.
    # Not sure

par(mfrow=c(2,2))
plot(lm.fit)

