library(ISLR)
attach(Wage)

# Polnomial Linear Regression
# ----------------------------

# 4th degree polynomial linear regression model
fit <- lm(wage ~ poly(age, 4))

# Grid of values for age
age.grid <- seq(min(age), max(age))

# Predict using the fit model, age vector, using standard errors
pred <- predict(fit, newdata = list(age = age.grid), se = TRUE)

# Using the computed standard errors, can compute 95% confidence bands
# For each age, added and subtracted assosciated standard error
se.bands <- cbind(pred$fit + 2*pred$se.fit, pred$fit - 2*pred$se.fit)

# Plot with age as x, wage as y
plot(age, wage, cex=0.5, col="darkgray", main="Degree-4Polynomial")

# Using the age vector and predictions, add a line of best fit
lines(age.grid, pred$fit, lwd=2, col="blue")

# Adding confidence bands by taking age as x and confidence bands as y
matlines(age.grid, se.bands, lwd=1, col="blue", lty=3)