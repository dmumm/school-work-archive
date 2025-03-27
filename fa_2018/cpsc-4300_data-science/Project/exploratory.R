

library(ggplot2)
#install.packages("tree")
library(tree)


# Author: Lauren Setzer, Dalvin Parks, Dylan Mumm
# Date: November 30th, 2018
# Purpose: Exploratory Data Analysis 


# Tree Method

set = read.csv("FData.csv", header = TRUE, na.strings=c("", "NA", "NULL"))
set[[1]] <- as.Date(set[[1]], "%m/%d/%Y")

set$date <- NULL
set$last_pos <- NULL
set$weeks <- NULL
set$rank <- NULL
set$change <- NULL
set$instrumentalness <- NULL
set$mode <- NULL

set <- na.omit(set)

set.seed(1)
N <- nrow(set)
P <- ncol(set)-1
train <- sample(1:N, N/2)
test <- seq(1:N)[-train]



tree <- tree(peak_pos~., set, subset=train)
summary(tree)
plot(tree)
text(tree)
title(main = "Peak Position Predictors")
print(tree)


set = read.csv("FData.csv", header = TRUE, na.strings=c("", "NA", "NULL"))
set[[1]] <- as.Date(set[[1]], "%m/%d/%Y")

set$date <- NULL
set$last_pos <- NULL
set$peak_pos <- NULL
set$rank <- NULL
set$change <- NULL
set$instrumentalness <- NULL
set$mode <- NULL

set <- na.omit(set)

set.seed(1)
N <- nrow(set)
P <- ncol(set)-1
train <- sample(1:N, N/2)
test <- seq(1:N)[-train]



tree <- tree(weeks~., set, subset=train)
summary(tree)
plot(tree)
text(tree)
title(main = "Persistence Predictors")
print(tree)

# Non Linear Regression


set = read.csv("FData.csv", header = TRUE, na.strings=c("", "NA", "NULL"))
set[[1]] <- as.Date(set[[1]], "%m/%d/%Y")
set <- na.omit(set)

attach(set)


fit <- lm(danceability ~ poly(date, 4))

date.grid <- seq(from = min(date), to = max(date), by = 1)

pred <- predict(fit, newdata = list(date = date.grid), se = TRUE, na.rm=TRUE)
se.bands <- cbind(pred$fit + 2*pred$se.fit, pred$fit - 2*pred$se.fit)

plot(date, danceability, cex=.5, col="darkgray", main="Degree-4Polynomial")
lines(date.grid, pred$fit, lwd=2, col="blue")
matlines(date.grid, se.bands, lwd=1, col="blue", lty=3)


# ridge regressions, cross validation
# tuesday 1pm MAX
