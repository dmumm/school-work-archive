# Author: Dylan Mumm
# Date: Sept 7, 2018
# Purpose: EDA and Visualization

# Loading tidyverse
library(tidyverse)


#############################
#                           #
#   3. Aesthetic Mappings   #
#                           #
#############################

# Using tidyverse's mpg database, we will look at the relationship between
# engine size and fuel efficiency on the highway

ggplot(data = mpg) +
  geom_point(mapping = aes(x = displ, y = hwy))

# 1. Which variables in mpg are categorical? Which variables are continuous? 
#    (Hint: type ?mpg to read the documentation for the dataset). 
#    How can you see this information when you run mpg?

?mpg
summary(mpg)

#    * Categorical: manufacturer, model, trans, drv, class, fl, year
#    * Continous:   displ, cty, hwy
#    * Discete:     cyl


# 2. Map a continuous variable to color, size, and shape. 
#    How do these aesthetics behave differently for categorical vs. continuous variables?

ggplot(data = mpg) +
  geom_point(mapping = aes(x = displ, y = hwy, color=cty, size=c, shape=drv))

#    * Categoricial: A color per category, a size per category, a shape per catagory
#    * Continuous: Color and shape becomes gradients, shape does not work 


# 3. What happens if you map the same variable to multiple aesthetics?
#    * Works fine

# 4. What happens if you map an aesthetic to something other than a variable name, 
#    like aes(color = displ < 5)?

ggplot(data = mpg) +
  geom_point(mapping = aes(x = displ, y = hwy, color = displ < 5))

#    * Conveys the result of the statement, for example, the above expresses
#      result of conditional 

#################
#               #
#   4. Facets   #
#               #
#################

# Plot split into facets via a singular variable
ggplot(data = mpg) +
  geom_point(mapping = aes(x = displ, y = hwy)) + 
  facet_wrap(~ class, nrow = 2)

# Plot faceted on the combination of two variables
ggplot(data = mpg) + 
  geom_point(mapping = aes(x = displ, y = hwy)) + 
  facet_grid(drv ~ cyl)

# 1. What happens if you facet on a continuous variable?
#    * One plot per unique observation of said variable 

ggplot(data = mpg) +
  geom_point(mapping = aes(x = cty, y = hwy)) + 
  facet_wrap(~ displ, nrow = 3)

# 2. What do the empty cells in plot with facet_grid(drv ~ cyl) mean?  
#    How do they relate to this plot?
#    * Empty cells indicate there are no observations at that cross tab
#    * That plot also conveys where there are no observations at that cross tab

ggplot(data = mpg) +
  geom_point(mapping = aes(x = drv, y = cyl))

# 3. Take the following faceted plots. What are the advantages to using faceting
#    rather than th ecolor aesthetic? What are the disadvantages? How might the
#    balance change if you had a large dataset?
#    * Faceting is much better at explicitly conveying the different distributions
#      of each category, but worse at conveying how the distributions compare to each other
#      and showing the full distribution
#    * A larger dataset would make the colored plot way too much of a mess

ggplot(data = mpg) +
  geom_point(mapping = aes(x = displ, y = hwy)) +
  facet_wrap(~ class, nrow = 2)

ggplot(data = mpg) +
  geom_point(mapping = aes(x = displ, y = hwy, color=class))

############################
#                          #
#   5. Geometric Objects   #
#                          #
############################

# Geom is the object that a plot uses to represent data
# To change the geom in your plot, change the geom function that you add to ggplot().
# As an example, compare the following two plots:

ggplot(data = mpg) +
  geom_point(mapping = aes(x = displ, y = hwy))

ggplot(data = mpg) +
  geom_smooth(mapping = aes(x = displ, y = hwy))

# Now combined....
ggplot(data = mpg, mapping = aes(x = displ, y = hwy)) +
  geom_point() +
  geom_smooth()

# 1. Run this code in your head and predict what the output will look like.
#    Then, run the code in R and check your predictions.
#    * Scatterplot comparing engine size and highway fuel efficiency,
#      colored in accordance to vehicle drivetrain, with a smoothed line of best fit

ggplot(data = mpg, mapping = aes(x = displ, y = hwy, color = drv)) +
  geom_point() +
  geom_smooth(se = FALSE)









