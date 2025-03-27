college <- read.csv("http://www-bcf.usc.edu/~gareth/ISL/College.csv")
rownames(college) <- college[ ,1]
View(college)

summary(college)

pairs(college[,1:10])

boxplot(college$Outstate ~ college$Private, main = "Outstate versus Private", xlab = "Private", ylab = "Outstate")

college$Elite <- rep("No", nrow(college))
college$Elite[college$Top10perc > 50] <- "Yes"
college$Elite <- as.factor(college$Elite)

summary(college)

boxplot(college$Outstate ~ college$Elite, main = "Outstate versus Elite", xlab = "Elite", ylab = "Outstate")

par(mfrow=c(2,2))
hist(college$Accept, breaks = 6, freq = TRUE, col = "blue", main = "Histogram", 
     xlab = "Accept", ylab = "Value")
hist(college$Accept, breaks = 10, freq = TRUE, col = "green", main = "Histogram", 
     xlab = "Accept", ylab = "Value")
hist(college$Enroll, breaks = 6, freq = TRUE, col = "blue", main = "Histogram", 
     xlab = "Enroll", ylab = "Value")
hist(college$Enroll, breaks = 10, freq = TRUE, col = "green", main = "Histogram", 
     xlab = "Enroll", ylab = "Value")
hist(college$Top10perc, breaks = 6, freq = TRUE, col = "blue", main = "Histogram", 
     xlab = "Top10perc", ylab = "Value")
hist(college$Top10perc, breaks = 10, freq = TRUE, col = "green", main = "Histogram", 
     xlab = "Top10perc", ylab = "Value")

#1.  What is the university with the most students in the top 10% of class?
q1 <- college[order(college$Top10perc),]
     # MIT
  
#2.  What university has the smallest acceptance rate?
q2 <- college[order(college$Accept / college$Apps),]
     # Harvard

#3.  What university has the most liberal acceptance rate?
q3 <- college[order(-college$Accept / college$Apps),]
     # Emporia State University

#4.  What is the correlation between out-of-state tuition and graduation rate?
cor(college$Outstate, college$Grad.Rate)
    # 0.5712899