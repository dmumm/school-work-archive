# REQUIREMENTS

## What we are modelling

* Database system for PIzzas-R-Us to track day-to-day operations
* Create an enhanced ER model
  * Crow's Foot Notation
    * Lectures
    * Chapters 4-5
  * Must contain all information needed for required views
    * Views do not actually need implemented yet
  * Add appropriate primary keys to entities when necessary
  * Have all brdge entities needed to properly prepresent M:M relationships
    * Conceptual database after all
  * Must need to re-intepret client's requirements
    * Cliet nmay provide extra information that may not be directly shown in diagram
      * Still implies what requirements are
      * Use teams to ask questions
      * Like some details about how pricing is determined

* Submit enhanced ER model

## Database requirements

* Store caries `Toppings`
    1. `Name`
    2. `Base cost per unit`
    3. `Base price per unit`
    4. `Units in personal`
    5. `Units in medium`
    6. `Units in large`
    7. `Units in x-large`
    8. `Minimum inventory level`
    9. `Current inventory level`
        * Updated whenever a pizza is ordered

* Each `pizza` made needs recorded
  1. `Crust type`
        1. `Thin`, `Original`, `Pan`, `Gluten-Free`
        * *QUESTION*: .pdf implies pricing based on crust type in addition to size, but inconsistent
  2. `Size`
      * 1:1
     1. `Personal`, `medium`, `large`, `x-large`
  3. `Requested toppings`
     * 1:M
     * See `Toppings`
     * 1 serving of cheese mandatory specifically
  4. `Base Cost`
      * Derived from base price of size & crust, and then base price of each topping for its size (double count as two of its kind). At time of order, not updated
      * *QUESTION*: How exactly does crust factor into the business cost and/or menu price of a pizza, mathematically?
  5. `Base price to customer`
      * Derived from size and toppings at time of order, not updated
  6. `Effective price to customer`
      * Derived by applying requested discounts to base price, not updated
  7. `State`
      1. `Completed by kitchen`, `being processed by kitchen`
  8. `Discounts`
      * 0:M
      * Can't be same discount as order

* Each `pizza` belongs to an `order`

  1. `Order type`
      * 1:1
      * Should be used as discriminator
      1. `dine-in`, `pickup`, `delivery`
  2. `Pizzas`
      * 1:M
      * Each pizza contained in order
      1. See `pizza`

  3. `isComplete`
      * Once all pizzas are complete

  4. `Base Cost`
      * Derived by adding up base costs of each pizza at time of order, does not update

  5. `Base price`
      * 1:1
      * Derived by adding up effective price of each pizza at time of order, does not update

  6. `Effective price`
      * 1:1
      * Derived by applying requested discounts to base price, does not update

  7. If dine-in, must have `table number`
      * 0:1
      * need to guarantee number is valid, not currently in use, and available -- and update it when it should be

  8. If pickup, must have `customer`
      * Used for future orders
      1. `Name`
      2. `Phone number`
      3. `Prior orders`
          * Includes delivery and pickup orders
          * Prior orders are just saved as reference, any new orders by customers that may copy them are new instances with current prices

  9. If delivery, must have `delivery customer`
      1. `Customer`
      2. `Address`

  10. `Request Timestamp`
      * When order was placed
      * Used for kitchen to prioritize orders, also saved

  11. `Discounts`
      * 0:M
      * *QUESTION*" Do not know if multiple pizzas in one order can have same discount

* Optional `Discounts`, which may be for individual pizzas, or orders
  * Can't apply same discount to both a pizza and an order
  * Can have multiple discounts overall
  * Multiple pizzas in one order can have same pizza-level discount
    1. `Name`
    2. `Discount type`
        * Totally complete, disjoint discriminator
        1. `dollar amount off`
        2. `percentage off`
    3. `Eligibility`
        1. `pizza`
        2. `order`
        3. `both`

## Required views

* `Popular Toppings`
  * Rank order of all toppings by popularity
    * including extras
    * from most to least popular
    * *QUESTION:* Does this account for size?
* `Profit by Pizza`
  * Summary of the profit by pizza size and pizza crust type over selected time period
    * By profit, most profitable to least profitable
    * Accounts for discounts
* `Profit by Order Type`
  * Summary of the profit for each order type by month, and ever
  * Accounts for discounts
