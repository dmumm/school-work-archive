# Clearing cached data
rm(list = ls())

# Author: Laura Setzer, Dalvin Parks, Dylan Mumm
# Date: December 6th, 2018
#
# Exploring what musical qualities are assosciated 
# with peak rankings on Billboard Hot 100 


# Required libraries
library(boot)
library(ggplot2)
library(splines)
library(glmnet)
library(gam)

# --------------- #
# Data Processing #
# --------------- #

# Forming data set
data = read.csv("Billboard_2000-2018+Spotify.csv", header = TRUE, stringsAsFactors = FALSE )
df <- as.data.frame(data)

# Seeing what each column is
summary.default(df)

# Copying relevant columns into new data frame
df1 <- df[c(2,7,8,9,10,18,19,20,21,22,23,24,25,26,27,28,29,30)]

# Seeing what types of values they are
summary.default(df1)

# Changing columns to numeric data
df1$energy            <- as.numeric(df1$energy )       
df1$liveness          <- as.numeric(df1$liveness)        
df1$tempo             <- as.numeric(df1$tempo )       
df1$speechiness       <- as.numeric(df1$speechiness)      
df1$acousticness      <- as.numeric(df1$acousticness)     
df1$instrumentalness  <- as.numeric(df1$instrumentalness  )
df1$time_signature    <- as.numeric(df1$time_signature)  
df1$danceability      <- as.numeric(df1$danceability )  
df1$key               <- as.numeric(df1$key)     
df1$duration_ms       <- as.numeric(df1$duration_ms)     
df1$loudness          <- as.numeric(df1$loudness)    
df1$valence           <- as.numeric(df1$valence  )    
df1$mode              <- as.numeric(df1$mode)

# Removing incomplete rows of data
df1 = na.omit(df1)

# ----------------- #
# Feature Selection #
# ----------------- #

# Linear model with all features
lin <- glm(peak_pos ~ energy + liveness + tempo + acousticness + instrumentalness + time_signature + danceability + duration_ms + loudness + valence, data = df1)


# add predictors to matrix to prepare LASSO analysis
x <- as.matrix(df1[c(1, 6, 7, 8, 9,10, 11, 12, 13, 14, 15, 16, 17)])
y <- as.matrix(df1[c(2)])

# conduct LASSO
set.seed(999)
cv.lasso <- cv.glmnet(x, y, family = "gaussian", alpha = .5, parallel = TRUE, standardize = TRUE, type.measure = "mse")

# LASSO Results
plot(cv.lasso)
plot(cv.lasso$glmnet.fit, xvar="lambda", label=TRUE)
cv.lasso$lambda.min
cv.lasso$lambda.1se

# See LASSO feature selection
coef(cv.lasso, s=cv.lasso$lambda.1se)

# Making linear model with those features
fit <- glm(peak_pos ~ danceability + year + duration_ms + valence, data = df1)
summary(fit)

# Non-linear model feature selection 
fit1 <- lm(peak_pos ~ poly(energy, 4), data = df1)
fit2 <- lm(peak_pos ~ poly(liveness, 4), data = df1) 
fit3 <- lm(peak_pos ~ poly(tempo, 4), data = df1 )
fit4 <- lm(peak_pos ~ poly(speechiness, 4), data = df1 )
fit5 <- lm(peak_pos ~ poly(acousticness, 4), data = df1 )
fit6 <- lm(peak_pos ~ poly(instrumentalness, 4), data = df1)
fit7 <- lm(peak_pos ~ poly(time_signature, 4), data = df1 )
fit8 <- lm(peak_pos ~ poly(danceability, 4) , data = df1 )
fit9 <- lm(peak_pos ~ poly(key, 4), data = df1)
fit10 <- lm(peak_pos ~ poly(duration_ms, 4), data = df1)
fit11 <- lm(peak_pos ~ poly(loudness, 4), data = df1)
fit12 <- lm(peak_pos ~ poly(valence, 4), data = df1 )
fit13 <- lm(peak_pos ~ poly(mode,1),data = df1)

# Comparing regressions for each attribute
  
summary(fit1)
summary(fit2)
summary(fit3)
summary(fit4)
summary(fit5)
summary(fit6)
summary(fit7)
summary(fit8)
summary(fit9)
summary(fit10)
summary(fit11)
summary(fit12)
summary(fit13)

# Forming multiple polynomial regression model
poly <- glm(peak_pos ~ poly(energy, 2) + poly(liveness, 3) + poly(tempo,1)+ poly(acousticness,2) + poly(instrumentalness,3) + poly(time_signature,3)+ poly(danceability,2) + poly(duration_ms,3)+ poly(loudness,1)+ poly(valence,1), data = df1)
summary(poly)


# Converting to generalized additive model and Backward Feature Selection
gam <- gam(peak_pos ~ s(energy, 2) + s(liveness, 3) + s(tempo,1)+ s(acousticness,2) + s(instrumentalness,3) + s(time_signature,3)+ s(danceability,2) + s(duration_ms,3)+ s(loudness,1)+ s(valence,1), data = df1)
summary(gam)

gam1 <- gam(peak_pos ~ s(liveness, 3) + s(tempo,1) + s(acousticness,2) + s(instrumentalness,3) + s(time_signature,3)+ s(danceability,2) + s(duration_ms,3)+ s(loudness,1)+ s(valence,1), data = df1)
summary(gam1) # removed energy

gam2 <- gam(peak_pos ~ s(liveness, 3) + s(tempo,1) + s(acousticness,2) + s(instrumentalness,3) + s(danceability,2) + s(duration_ms,3)+ s(loudness,1)+ s(valence,1), data = df1)
summary(gam2) # removed time signature

gam3 <- gam(peak_pos ~ s(liveness, 3) + s(tempo,1) + s(instrumentalness,3) + s(danceability,2) + s(duration_ms,3)+ s(loudness,1)+ s(valence,1), data = df1)
summary(gam3) # removed acousticness

# -------------------------- #
# Assessing prediction power #
# -------------------------- #

# K-Fold Cross Validation

cv.error.10 <- cv.glm(na.omit(df1), lin, K=10) # Linear Model with all features
cv.error.10$delta # MSE = 889.13

cv.error.10 <- cv.glm(na.omit(df1), fit, K=10) # Linear Model with removed features
cv.error.10$delta # MSE = 887.68

cv.error.10 <- cv.glm(na.omit(df1), gam1, K=10) # Polynomial Model with all features
cv.error.10$delta # MSE = 885.83

cv.error.10 <- cv.glm(na.omit(df1), gam2, K=10) # GAM with all features
cv.error.10$delta # MSE = 885.58

cv.error.10 <- cv.glm(na.omit(df1), gam5, K=10) # GAM with removed features
cv.error.10$delta # MSE = 888.6


# Linear model prediction
# Example: Childish Gambino: This Is America 
predict(fit, newdata=data.frame(danceability=.854, year=2018, duration_ms=225773, valence=.549))

# -------------- #
# Visualizations #
# -------------- # 

# Danceability
p <- ggplot(df1, aes(x=danceability, y=peak_pos)) +
  theme_bw() +
  geom_point(size=1, col="orange") +
  geom_smooth(method="loess", color = "black") +
  xlim(.2, .9) +
  labs(subtitle="Danceability Vs Peak Position", 
     y="Peak Position", 
     x="Danceability", 
     title="", 
     caption = "Source: Billboard and Spotify")
print(p)

barYear <- aggregate(df1[, 13], list(df1$year), median)
p <- ggplot(barYear, aes(x=Group.1, y=x)) +
  theme_bw() +
  geom_point(size=3, col="orange") +
  geom_smooth(method="loess", color = "grey", size=.5) +
  labs(subtitle="Year vs Danceability", 
       y="Danceability", 
       x="Year", 
       title="", 
       caption = "Source: Billboard and Spotify")
print(p)

# Duration
p <- ggplot(df1, aes(x=duration_ms / 1000, y=peak_pos)) +
  theme_bw() +
  geom_point(size=1, col="#40E0D0") +
  geom_smooth(method="loess", color = "black") +
  xlim(150, 310) +
  labs(subtitle="Duration Vs Peak Position", 
       y="Peak Position", 
       x="Duration (seconds)", 
       title="", 
       caption = "Source: Billboard and Spotify")
print(p)

barYear <- aggregate(df1[, 15], list(df1$year), median)
p <- ggplot(barYear, aes(x=Group.1, y= x / 1000)) +
  theme_bw() +
  geom_point(size=3, col="#40E0D0") +
  labs(subtitle="Year vs Duration", 
       y="Duration (seconds)", 
       x="Year", 
       title="", 
       caption = "Source: Billboard and Spotify")
print(p)

# Valence
p <- ggplot(df1, aes(x=valence, y=peak_pos)) +
  theme_bw() +
  geom_point(size=1, col="violet") +
  geom_smooth(method="gam", color = "black") +
  labs(subtitle="Valence (happiness) Vs Peak Position", 
       y="Peak Position", 
       x="Valence", 
       title="", 
       caption = "Source: Billboard and Spotify")
print(p)

barYear <- aggregate(df1[, 17], list(df1$year), median)
p <- ggplot(barYear, aes(x=Group.1, y=x)) +
  theme_bw() +
  geom_point(size=3, col="violet") +
  geom_smooth(method="loess", color = "grey", size = .5) +
  labs(subtitle="Year vs Valence (happiness)", 
       y="Median Valence", 
       x="Year", 
       title="", 
       caption = "Source: Billboard and Spotify")
print(p)
