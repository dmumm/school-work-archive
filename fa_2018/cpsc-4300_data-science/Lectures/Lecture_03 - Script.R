rm(list = ls())

library(ggplot2)

# Author: Alex Herzog
# Date: January 25, 2018
# Purpose: Explore Senate candidate tweets

data <- read.csv("combined_tweets.csv")

tmp1 <- aggregate(article_id ~ author + party + incumbent + state, data, length)
names(tmp1)[names(tmp1)=="article_id"] <- "tweets"

tmp2 <- aggregate(followers ~ author, data, max)

a <- merge(tmp1, tmp2, by="author")

# Visualizing distributions
# Categorical variables
plot(a$incumbent)
a$incumbent <- factor(a$incumbent, levels=c(0,1), labels=c("No incumbent", "Incumbent"))

p <- ggplot(data=a, aes(incumbent)) +
  geom_bar()
print(p)


a$party <- factor(a$party, levels=c("R", "D", "I"))
p <- ggplot(data=a, aes(party)) +
  geom_bar()
print(p)


# Continuous variable
p <- ggplot(a, aes(x=tweets)) +
  geom_histogram()
print(p)


# Categorical and continuouse variable
p <- ggplot(a, aes(x=party, y=tweets)) +
  geom_boxplot()
print(p)


# Two continuouse variables
p <- ggplot(a, aes(x=log(tweets), y=log(followers))) +
  theme_bw() + 
  geom_point(size=3) +
  geom_smooth(method="lm")
print(p)





