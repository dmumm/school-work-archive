-- Bowen main, Dylan support
USE Pizzeria;

/*   Procedures */
DELIMITER $$
/*   fn_retrieve_base_pizza */
CREATE PROCEDURE fn_retrieve_base_pizza (
    IN inBasePizzaSize VARCHAR(255),
    IN inBasePizzaCrust VARCHAR(255),
    OUT outBasePizzaID INT,
    OUT outBasePizzaCurrentCustomerPrice DECIMAL(10, 2),
    OUT outBasePizzaCurrentBusinessCost DECIMAL(10, 2)
) BEGIN
SELECT BasePizzaID,
    BasePizzaCurrentCustomerPrice,
    BasePizzaCurrentBusinessCost INTO outBasePizzaID,
    outBasePizzaCurrentCustomerPrice,
    outBasePizzaCurrentBusinessCost
FROM base_pizza
WHERE BasePizzaSize = inBasePizzaSize
    AND BasePizzaCrust = inBasePizzaCrust;

END $$
/*    fn_retrieve_base_pizza */

/*   fn_process_pizza_discount */
CREATE PROCEDURE fn_process_pizza_discount
(
    IN inDiscountName VARCHAR(255),
    IN inOriginalPrice DECIMAL(10, 2),
    IN inPizzaOrderID INT,
    OUT outDollarsSaved DECIMAL(10, 2)
)
BEGIN

    DECLARE discountType ENUM('Dollar', 'Percent');
    DECLARE discountAmount DECIMAL(10, 2);
    DECLARE couponID INT;

    SELECT
        c.CouponID,
        c.CouponDiscountType,
        d.DiscountAmount
    INTO
        couponID,
        discountType,
        discountAmount
    FROM
        coupon c JOIN discount d
            ON c.CouponID = d.DiscountCouponID
    WHERE c.CouponName = inDiscountName
    LIMIT 1;

    IF discountType = 'Dollar' THEN
        SET outDollarsSaved = discountAmount
    ;
    ELSEIF discountType = 'Percent' THEN
        SET outDollarsSaved = inOriginalPrice * discountAmount
    ;
    END IF;

    IF outDollarsSaved > inOriginalPrice THEN
        SET outDollarsSaved = inOriginalPrice
    ;
    END IF;

    INSERT INTO pizza_order_discount
    (
        PizzaOrderDiscountPizzaOrderID,
        PizzaOrderDiscountCouponID,
        PizzaOrderDollarsSaved
    )
    VALUES (inPizzaOrderID, couponID, outDollarsSaved)
    ;

END $$
/*    fn_process_pizza_discount */



/*   fn_process_order_discount */
CREATE PROCEDURE fn_process_order_discount
(
    IN in_DiscountName VARCHAR(255),
    IN in_OriginalPrice DECIMAL(10, 2),
    IN in_FullOrderID INT,
    OUT out_DollarsSaved DECIMAL(10, 2)
)
BEGIN

    DECLARE discountType ENUM('Dollar', 'Percent');
    DECLARE discountAmount DECIMAL(10, 2);
    DECLARE couponID INT;

    SELECT
        c.CouponID,
        c.CouponDiscountType,
        d.DiscountAmount
    INTO
        couponID,
        discountType,
        discountAmount
    FROM
        coupon c JOIN discount d
            ON c.CouponID = d.DiscountCouponID
    WHERE c.CouponName = in_DiscountName
    LIMIT 1;

    IF discountType = 'Dollar' THEN
        SET out_DollarsSaved = discountAmount
    ;
    ELSEIF discountType = 'Percent' THEN
        SET out_DollarsSaved = in_OriginalPrice * discountAmount
    ;
    END IF;

    IF out_DollarsSaved > in_OriginalPrice THEN
        SET out_DollarsSaved = in_OriginalPrice
    ;
    END IF;

    INSERT INTO full_order_discount
    (
        FullOrderDiscountFullOrderID,
        FullOrderDiscountCouponID,
        FullOrderDiscountDollarsSaved
    )
    VALUES (in_FullOrderID, couponID, out_DollarsSaved)
    ;

    UPDATE full_order
    SET FullOrderCustomerDiscountedPrice =
        FullOrderCustomerDiscountedPrice - out_DollarsSaved
    WHERE FullOrderID = in_FullOrderID
    ;
END $$
/*    fn_process_order_discount */


/*   fn_apply_full_order_discount */
CREATE PROCEDURE fn_apply_full_order_discount
(
    IN in_DiscountName VARCHAR(255),
    IN in_OriginalPrice DECIMAL(10, 2),
    IN in_FullOrderID INT,
    OUT out_DollarsSaved DECIMAL(10, 2)
)
BEGIN

    DECLARE discountType ENUM('Dollar', 'Percent');
    DECLARE discountAmount DECIMAL(10, 2);
    DECLARE couponID INT;

    SELECT
        c.CouponID,
        c.CouponDiscountType,
        d.DiscountAmount
    INTO
        couponID,
        discountType,
        discountAmount
    FROM
        coupon c JOIN discount d
            ON c.CouponID = d.DiscountCouponID
    WHERE c.CouponName = in_DiscountName
    LIMIT 1;

    IF discountType = 'Dollar' THEN
        SET out_DollarsSaved = discountAmount
    ;
    ELSEIF discountType = 'Percent' THEN
        SET out_DollarsSaved = in_OriginalPrice * discountAmount
    ;
    END IF;

    IF out_DollarsSaved > in_OriginalPrice THEN
        SET out_DollarsSaved = in_OriginalPrice
    ;
    END IF;

    INSERT INTO full_order_discount
    (
        FullOrderDiscountFullOrderID,
        FullOrderDiscountCouponID,
        FullOrderDiscountDollarsSaved
    )
    VALUES (in_FullOrderID, couponID, out_DollarsSaved)
    ;


END $$
/*    fn_apply_full_order_discount */

/*   fn_get_topping_prices */
CREATE PROCEDURE fn_get_topping_prices
(
    IN in_ToppingName VARCHAR(255),
    IN in_IsDouble BOOLEAN,
    IN in_PizzaSize ENUM('Small', 'Medium', 'Large', 'XLarge'),
    OUT out_CustomerPrice DECIMAL(10, 2),
    OUT out_BusinessCost DECIMAL(10, 2),
    OUT out_ToppingID INT
)
BEGIN

    DECLARE v_Units INT;
    DECLARE v_Multiplier INT;
    SET v_Multiplier = IF(in_IsDouble, 2, 1);

    CASE in_PizzaSize

        WHEN 'Small' THEN
            SET v_Units = (SELECT ToppingUnitsInSmall FROM topping WHERE ToppingName = in_ToppingName);
        WHEN 'Medium' THEN
            SET v_Units = (SELECT ToppingUnitsInMedium FROM topping WHERE ToppingName = in_ToppingName);
        WHEN 'Large' THEN
            SET v_Units = (SELECT ToppingUnitsInLarge FROM topping WHERE ToppingName = in_ToppingName);
        WHEN 'XLarge' THEN
            SET v_Units = (SELECT ToppingUnitsInXLarge FROM topping WHERE ToppingName = in_ToppingName);
        ELSE
            SET v_Units = 0
        ;

    END CASE;

    SELECT
        v_Units * ToppingCurrentCustomerPricePerUnit * v_Multiplier,
        v_Units * ToppingCurrentBusinessCostPerUnit * v_Multiplier,
        ToppingID
    INTO
        out_CustomerPrice,
        out_BusinessCost,
        out_ToppingID
    FROM
        topping
    WHERE
        ToppingName = in_ToppingName
    ;

END $$
/*    fn_get_topping_prices */

/*   fn_apply_pizza_discounts */
CREATE PROCEDURE fn_apply_pizza_discounts
(
    IN in_PizzaOrderID INT
)
BEGIN

    DECLARE v_pizzaTotalDiscount DECIMAL(10, 2) DEFAULT 0.00;

    -- Declare variables for the cursor
    DECLARE c_done INT DEFAULT FALSE;
    DECLARE c_id INT;
    DECLARE c_dollars_saved DECIMAL(10, 2);
    DECLARE c_discount CURSOR FOR
        SELECT PizzaOrderDiscountID, PizzaOrderDollarsSaved
        FROM pizza_order_discount
        WHERE PizzaOrderDiscountPizzaOrderID = in_PizzaOrderID;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET c_done = TRUE;
    OPEN c_discount;

    -- Loop through the cursor
    discount_loop: LOOP

        FETCH c_discount INTO c_id, c_dollars_saved;
        IF c_done THEN
            LEAVE discount_loop;
        END IF;

        SET v_pizzaTotalDiscount = v_pizzaTotalDiscount + c_dollars_saved;

    END LOOP;
    CLOSE c_discount;

    UPDATE pizza_order
    SET PizzaOrderCustomerDiscountedPrice =
        PizzaOrderCustomerDiscountedPrice - v_pizzaTotalDiscount
    WHERE PizzaOrderID = in_PizzaOrderID
    ;

END $$
/*    fn_apply_pizza_discounts */

/*   fn_find_full_order_costs_and_prices */
CREATE PROCEDURE fn_find_full_order_costs_and_prices
(
    IN in_FullOrderID INT,
    OUT out_BusinessCost DECIMAL(10, 2),
    OUT out_CustomerBasePrice DECIMAL(10, 2)
)
BEGIN

    DECLARE v_totalBusinessCost DECIMAL(10, 2) DEFAULT 0.00;
    DECLARE v_totalCustomerPrice DECIMAL(10, 2) DEFAULT 0.00;

    -- Declare variables for the cursor
    DECLARE c_done INT DEFAULT FALSE;
    DECLARE c_id INT;
    DECLARE c_business_cost DECIMAL(10, 2);
    DECLARE c_customer_price DECIMAL(10, 2);
    DECLARE c_pizza CURSOR FOR
        SELECT PizzaOrderID, PizzaOrderBusinessCost, PizzaOrderCustomerDiscountedPrice
        FROM pizza_order
        WHERE PizzaOrderFullOrderID = in_FullOrderID;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET c_done = TRUE;
    OPEN c_pizza;

    -- Loop through the cursor
    pizza_loop: LOOP

        FETCH c_pizza INTO c_id, c_business_cost, c_customer_price;
        IF c_done THEN
            LEAVE pizza_loop;
        END IF;

        SET v_totalBusinessCost = v_totalBusinessCost + c_business_cost;
        SET v_totalCustomerPrice = v_totalCustomerPrice + c_customer_price;

    END LOOP;
    CLOSE c_pizza;
    UPDATE full_order
    SET
        FullOrderBusinessCost = v_totalBusinessCost,
        FullOrderCustomerBasePrice = v_totalCustomerPrice,
        FullOrderCustomerDiscountedPrice = FullOrderCustomerBasePrice
    WHERE
        FullOrderID = in_FullOrderID
    ;

    SET out_CustomerBasePrice = v_totalCustomerPrice;

END $$
/*    fn_find_full_order_costs_and_prices */

/*   fn_mark_pizza_order_complete */
CREATE PROCEDURE fn_mark_pizza_order_complete(IN in_PizzaOrderID INT)
BEGIN

    UPDATE pizza_order
    SET PizzaOrderStatus = 'Complete'
    WHERE PizzaOrderID = in_PizzaOrderID
    ;

END$$ /*    fn_mark_pizza_order_complete */

/*   fn_mark_full_order_complete */
CREATE PROCEDURE fn_mark_full_order_complete(IN in_FullOrderID INT)
BEGIN
    IF
    (
        SELECT COUNT(*)
        FROM pizza_order
        WHERE PizzaOrderFullOrderID = in_FullOrderID
          AND PizzaOrderStatus != 'Complete'
    ) = 0
    THEN
        UPDATE full_order
        SET FullOrderStatus = 'Complete'
        WHERE FullOrderID = in_FullOrderID;
    END IF;
END$$ /*    fn_mark_full_order_complete */

/*   fn_update_customer */
CREATE PROCEDURE fn_update_customer
(
    IN in_FirstName VARCHAR(255),
    IN in_LastName VARCHAR(255),
    IN in_PhoneNumber VARCHAR(255),
    OUT out_ID INT
)
BEGIN

    SELECT CustomerID INTO out_ID
    FROM customer
    WHERE
        CustomerFirstName = in_FirstName AND CustomerLastName = in_LastName
    LIMIT 1;

    IF out_ID IS NULL THEN
        INSERT INTO customer
        (
            CustomerFirstName,
            CustomerLastName,
            CustomerPhoneNumber
        )
        VALUES
        (
            in_FirstName,
            in_LastName,
            in_PhoneNumber
        );
        SET out_ID = LAST_INSERT_ID();
    ELSE
        UPDATE customer
        SET CustomerPhoneNumber = in_PhoneNumber
        WHERE CustomerID = out_ID AND CustomerPhoneNumber != in_PhoneNumber;
    END IF;
END$$ /*    fn_update_customer */

/*   fn_update_address */
CREATE PROCEDURE fn_update_address
(
    IN in_CustomerID INT,
    IN in_StreetNumber INT,
    IN in_StreetName VARCHAR(255),
    IN in_City VARCHAR(255),
    IN in_State VARCHAR(255),
    IN in_Zip INT
)
BEGIN
    DECLARE v_addressID INT;
    SELECT AddressCustomerID INTO v_addressID
    FROM address
    WHERE
        AddressCustomerID = in_CustomerID
    LIMIT 1;

    IF v_addressID IS NULL THEN

        UPDATE customer
        SET CustomerHasAddress = TRUE
        WHERE CustomerID = in_CustomerID
        ;

        INSERT INTO address
        (
            AddressCustomerID,
            CustomerStreetNumber,
            CustomerStreetName,
            CustomerCity,
            CustomerState,
            CustomerZip
        )
        VALUES
        (
            in_CustomerID,
            in_StreetNumber,
            in_StreetName,
            in_City,
            in_State,
            in_Zip
        );

    ELSEIF (
        CustomerStreetNumber != in_StreetNumber OR
        CustomerStreetName != in_StreetName OR
        CustomerCity != in_City OR
        CustomerState != in_State OR
        CustomerZip != in_Zip
        ) THEN UPDATE address
        SET
            CustomerStreetNumber = in_StreetNumber,
            CustomerStreetName = in_StreetName,
            CustomerCity = in_City,
            CustomerState = in_State,
            CustomerZip = in_Zip
        WHERE AddressCustomerID = in_CustomerID;
    END IF;
END$$ /*    fn_update_address */



DELIMITER ;
/*    Procedures */


/*   Initialize database with data */
INSERT INTO base_pizza (
        BasePizzaSize,
        BasePizzaCrust,
        BasePizzaCurrentCustomerPrice,
        BasePizzaCurrentBusinessCost
    )
VALUES ('Small', 'Thin', 3, 0.5),
    ('Small', 'Original', 3, 0.75),
    ('Small', 'Pan', 3.5, 1),
    ('Small', 'Gluten-Free', 4, 2),
    ('Medium', 'Thin', 5, 1),
    ('Medium', 'Original', 5, 1.5),
    ('Medium', 'Pan', 6, 2.25),
    ('Medium', 'Gluten-Free', 6.25, 3),
    ('Large', 'Thin', 8, 1.25),
    ('Large', 'Original', 8, 2),
    ('Large', 'Pan', 9, 3),
    ('Large', 'Gluten-Free', 9.5, 4),
    ('XLarge', 'Thin', 10, 2),
    ('XLarge', 'Original', 10, 3),
    ('XLarge', 'Pan', 11.5, 4.5),
    ('XLarge', 'Gluten-Free', 12.5, 6);

INSERT INTO topping (
        ToppingName,
        ToppingCurrentCustomerPricePerUnit,
        ToppingCurrentBusinessCostPerUnit,
        ToppingInventoryCurrent,
        ToppingInventoryMinimum,
        ToppingUnitsInSmall,
        ToppingUnitsInMedium,
        ToppingUnitsInLarge,
        ToppingUnitsInXLarge
    )
VALUES (
        'Pepperoni',
        1.25,
        0.2,
        100,
        50,
        2,
        2.75,
        3.5,
        4.5
    ),
    (
        'Sausage',
        1.25,
        0.15,
        100,
        50,
        2.5,
        3,
        3.5,
        4.25
    ),
    ('Ham', 1.5, 0.15, 78, 25, 2, 2.5, 3.25, 4),
    ('Chicken', 1.75, 0.25, 56, 25, 1.5, 2, 2.25, 3),
    (
        'Green Pepper',
        0.5,
        0.02,
        79,
        25,
        1,
        1.5,
        2,
        2.5
    ),
    ('Onion', 0.5, 0.02, 85, 25, 1, 1.5, 2, 2.75),
    (
        'Roma Tomato',
        0.75,
        0.03,
        86,
        10,
        2,
        3,
        3.5,
        4.5
    ),
    ('Mushrooms', 0.75, 0.1, 52, 50, 1.5, 2, 2.5, 3),
    (
        'Black Olives',
        0.6,
        0.1,
        39,
        25,
        0.75,
        1,
        1.5,
        2
    ),
    ('Pineapple', 1, 0.25, 15, 0, 1, 1.25, 1.75, 2),
    (
        'Jalapenos',
        0.5,
        0.05,
        64,
        0,
        0.5,
        0.75,
        1.25,
        1.75
    ),
    (
        'Banana Peppers',
        0.5,
        0.05,
        36,
        0,
        0.6,
        1,
        1.3,
        1.75
    ),
    (
        'Regular Cheese',
        0.5,
        0.12,
        250,
        50,
        2,
        3.5,
        5,
        7
    ),
    (
        'Four Cheese Blend',
        1,
        0.15,
        150,
        25,
        2,
        3.5,
        5,
        7
    ),
    ('Feta Cheese', 1.5, 0.18, 75, 0, 1.75, 3, 4, 5.5),
    (
        'Goat Cheese',
        1.5,
        0.2,
        54,
        0,
        1.6,
        2.75,
        4,
        5.5
    ),
    ('Bacon', 1.5, 0.25, 89, 0, 1, 1.5, 2, 3);

INSERT INTO coupon (CouponName, CouponDiscountType)
VALUES ('Lunch Special Medium', 'Dollar');

INSERT INTO discount (DiscountCouponID, DiscountAmount)
VALUES (LAST_INSERT_ID(), 1.00);

INSERT INTO coupon (CouponName, CouponDiscountType)
VALUES ('Lunch Special Large', 'Dollar');

INSERT INTO discount (DiscountCouponID, DiscountAmount)
VALUES (LAST_INSERT_ID(), 2.00);

INSERT INTO coupon (CouponName, CouponDiscountType)
VALUES ('Specialty Pizza', 'Dollar');

INSERT INTO discount (DiscountCouponID, DiscountAmount)
VALUES (LAST_INSERT_ID(), 1.50);

INSERT INTO coupon (CouponName, CouponDiscountType)
VALUES ('Employee', 'Percent');

INSERT INTO discount (DiscountCouponID, DiscountAmount)
VALUES (LAST_INSERT_ID(), 0.15);

INSERT INTO coupon (CouponName, CouponDiscountType)
VALUES ('Happy Hour', 'Percent');

INSERT INTO discount (DiscountCouponID, DiscountAmount)
VALUES (LAST_INSERT_ID(), 0.10);

INSERT INTO coupon (CouponName, CouponDiscountType)
VALUES ('Gameday Special', 'Percent');

INSERT INTO discount (DiscountCouponID, DiscountAmount)
VALUES (LAST_INSERT_ID(), 0.20);

/*    Initialize database with data */


/*   Order 1 */
SET
    @orderTimestamp = '2023-03-05 12:03:00',
    @orderType = 'Dine-in',
    @tableNumber = 21
;
/*   Order calls */
INSERT INTO full_order
(
    FullOrderRequestTimestamp,
    FullOrderType,
    FullOrderBusinessCost,
    FullOrderCustomerBasePrice,
    FullOrderCustomerDiscountedPrice
)
VALUES
(
    @orderTimestamp,
    @orderType,
    0,
    0,
    0
);
SET @fullOrderID = LAST_INSERT_ID()
; /*    Order calls */

INSERT INTO dinein
(
    DineinFullOrderID,
    DineinTable
)
VALUES
(
    @fullOrderID,
    @tableNumber
)
;

/*   Pizza 1 */
SET
    @pizzaSize = 'Large',
    @pizzaCrust = 'Thin',
    @pizzaCost = 3.68,
    @pizzaOriginalPrice = 20.75; /* tho it should be 21.75? */
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
;

/*    Pizza Calls */


    /*   Extra Regular Cheese */
SET
    @toppingName = 'Regular Cheese',
    @isDouble = TRUE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);

INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Extra Regular Cheese */

    /*   Pepperoni */
SET
    @toppingName = 'Pepperoni',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Pepperoni */

    /*   Sausage */
SET
    @toppingName = 'Sausage',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Sausage */

/*   Pizza Discounts */
SET @pizzaDiscountName = 'Lunch Special Large';
CALL fn_process_pizza_discount(@pizzaDiscountName, @pizzaOriginalPrice, @pizzaID, @dollarsSaved);
/*    Pizza Discounts */


CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID);

/*    Pizza 1 */

CALL fn_find_full_order_costs_and_prices(@fullOrderID, @fullOrderBusinessCost, @fullOrderCustomerBasePrice);
CALL fn_mark_full_order_complete(@fullOrderID); /*    Order 1 */

/*   Order 2 */
SET
    @orderTimestamp = '2023-04-03 12:05:00',
    @orderType = 'Dine-in',
    @tableNumber = 4
;
/*   Order calls */
INSERT INTO full_order
(
    FullOrderRequestTimestamp,
    FullOrderType,
    FullOrderBusinessCost,
    FullOrderCustomerBasePrice,
    FullOrderCustomerDiscountedPrice
)
VALUES
(
    @orderTimestamp,
    @orderType,
    0,
    0,
    0
);
SET @fullOrderID = LAST_INSERT_ID()
; /*    Order calls */

INSERT INTO dinein
(
    DineinFullOrderID,
    DineinTable
)
VALUES
(
    @fullOrderID,
    @tableNumber
)
;

/*   Pizza 1 */
SET
    @pizzaSize = 'Medium',
    @pizzaCrust = 'Pan',
    @pizzaCost = 3.23,
    @pizzaOriginalPrice = 12.85;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */


    /*   Feta Cheese */
SET
    @toppingName = 'Feta Cheese',
    @isDouble = FALSE
;
        /*   Topping Calls */
CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
;
        /*    Topping Calls */
    /*    Feta Cheese */

    /*   Black Olives */
SET
    @toppingName = 'Black Olives',
    @isDouble = FALSE
;
        /*   Topping Calls */
CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
;
        /*    Topping Calls */
    /*    Black Olives */

    /*   Roma Tomato */
SET
    @toppingName = 'Roma Tomato',
    @isDouble = FALSE
;
        /*   Topping Calls */
CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
;
        /*    Topping Calls */
    /*    Roma Tomato */

    /*   Mushrooms */
SET
    @toppingName = 'Mushrooms',
    @isDouble = FALSE
;
        /*   Topping Calls */
CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
;
        /*    Topping Calls */
    /*    Mushrooms */

    /*   Banana Peppers */
SET
    @toppingName = 'Banana Peppers',
    @isDouble = FALSE
;
        /*   Topping Calls */
CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
;
        /*    Topping Calls */
    /*    Banana Peppers */


/*   Pizza Discounts */

SET @pizzaDiscountName = 'Lunch Special Medium';
CALL fn_process_pizza_discount(@pizzaDiscountName, @pizzaOriginalPrice, @pizzaID, @dollarsSaved);

SET @pizzaDiscountName = 'Specialty Pizza';
CALL fn_process_pizza_discount(@pizzaDiscountName, @pizzaOriginalPrice, @pizzaID, @dollarsSaved);

/*    Pizza Discounts */


CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 1 */

/*   Pizza 2 */
SET
    @pizzaSize = 'Small',
    @pizzaCrust = 'Original',
    @pizzaCost = 1.40,
    @pizzaOriginalPrice = 6.93;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */


    /*   Regular Cheese */
SET
    @toppingName = 'Regular Cheese',
    @isDouble = FALSE
;
        /*   Topping Calls */
CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
;
        /*    Topping Calls */
    /*    Regular Cheese */

    /*   Chicken */
SET
    @toppingName = 'Chicken',
    @isDouble = FALSE
;
        /*   Topping Calls */
CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
;
        /*    Topping Calls */
    /*    Chicken */

    /*   Banana Peppers */
SET
    @toppingName = 'Banana Peppers',
    @isDouble = FALSE
;
        /*   Topping Calls */
CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
;
        /*    Topping Calls */
    /*    Banana Peppers */


CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 2 */


CALL fn_find_full_order_costs_and_prices(@fullOrderID, @fullOrderBusinessCost, @fullOrderCustomerBasePrice);
CALL fn_mark_full_order_complete(@fullOrderID); /*    Order 2 */

/*   Order 3 */
SET
    @orderTimestamp = '2023-03-03 21:30:00',
    @orderType = 'Pickup'
;

    /*   Order calls */
INSERT INTO full_order
(
    FullOrderRequestTimestamp,
    FullOrderType,
    FullOrderBusinessCost,
    FullOrderCustomerBasePrice,
    FullOrderCustomerDiscountedPrice
)
VALUES
(
    @orderTimestamp,
    @orderType,
    0,
    0,
    0
);
SET @fullOrderID = LAST_INSERT_ID()
; /*    Order calls */

SET
    @customerFirst = 'Andrew',
    @customerLast = 'Wilkes-Krier',
    @customerPhone = '864-254-5861'
;
CALL fn_update_customer(@customerFirst, @customerLast, @customerPhone, @customerID);

INSERT INTO pickup
(
    PickupFullOrderID,
    PickupCustomerID
)
VALUES
(
    @fullOrderID,
    @customerID
)
;

/*   Pizza 1 */
SET
    @pizzaSize = 'Large',
    @pizzaCrust = 'Original',
    @pizzaCost = 3.30,
    @pizzaOriginalPrice = 14.88;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */

    /*   Regular Cheese */
SET
    @toppingName = 'Regular Cheese',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Regular Cheese */

    /*   Pepperoni */
SET
    @toppingName = 'Pepperoni',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Pepperoni */

CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 1 */

/*   Pizza 2 */
SET
    @pizzaSize = 'Large',
    @pizzaCrust = 'Original',
    @pizzaCost = 3.30,
    @pizzaOriginalPrice = 14.88;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */

    /*   Regular Cheese */
SET
    @toppingName = 'Regular Cheese',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Regular Cheese */

    /*   Pepperoni */
SET
    @toppingName = 'Pepperoni',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Pepperoni */

CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 2 */

/*   Pizza 3 */
SET
    @pizzaSize = 'Large',
    @pizzaCrust = 'Original',
    @pizzaCost = 3.30,
    @pizzaOriginalPrice = 14.88;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */

    /*   Regular Cheese */
SET
    @toppingName = 'Regular Cheese',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Regular Cheese */

    /*   Pepperoni */
SET
    @toppingName = 'Pepperoni',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Pepperoni */

CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 3 */

/*   Pizza 4 */
SET
    @pizzaSize = 'Large',
    @pizzaCrust = 'Original',
    @pizzaCost = 3.30,
    @pizzaOriginalPrice = 14.88;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */

    /*   Regular Cheese */
SET
    @toppingName = 'Regular Cheese',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Regular Cheese */

    /*   Pepperoni */
SET
    @toppingName = 'Pepperoni',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Pepperoni */

CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 4 */

/*   Pizza 5 */
SET
    @pizzaSize = 'Large',
    @pizzaCrust = 'Original',
    @pizzaCost = 3.30,
    @pizzaOriginalPrice = 14.88;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */

    /*   Regular Cheese */
SET
    @toppingName = 'Regular Cheese',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Regular Cheese */

    /*   Pepperoni */
SET
    @toppingName = 'Pepperoni',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Pepperoni */

CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 5 */

/*   Pizza 6 */
SET
    @pizzaSize = 'Large',
    @pizzaCrust = 'Original',
    @pizzaCost = 3.30,
    @pizzaOriginalPrice = 14.88;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */

    /*   Regular Cheese */
SET
    @toppingName = 'Regular Cheese',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Regular Cheese */

    /*   Pepperoni */
SET
    @toppingName = 'Pepperoni',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Pepperoni */

CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 6 */


CALL fn_find_full_order_costs_and_prices(@fullOrderID, @fullOrderBusinessCost, @fullOrderCustomerBasePrice);
CALL fn_mark_full_order_complete(@fullOrderID); /*    Order 3 */


/*   Order 4 */
SET
    @orderTimestamp = '2023-04-20 19:11:00',
    @orderType = 'Delivery'
; #q1

    /*   Order calls */
INSERT INTO full_order
(
    FullOrderRequestTimestamp,
    FullOrderType,
    FullOrderBusinessCost,
    FullOrderCustomerBasePrice,
    FullOrderCustomerDiscountedPrice
)
VALUES
(
    @orderTimestamp,
    @orderType,
    0,
    0,
    0
);
SET @fullOrderID = LAST_INSERT_ID()
; #q2 /*    Order calls */

SET
    @customerFirst = 'Andrew',
    @customerLast = 'Wilkes-Krier',
    @customerPhone = '864-254-5861',
    @streetNumber = '115',
    @streetName = 'Party Blvd',
    @city = 'Anderson',
    @state = 'SC',
    @zip = '29621'
;

    /*   delivery calls */
CALL fn_update_customer
(
    @customerFirst,
    @customerLast,
    @customerPhone,
    @customerID -- out
);
CALL fn_update_address
(
    @customerID,
    @streetNumber,
    @streetName,
    @city,
    @state,
    @zip
)
;

INSERT INTO delivery
(
    DeliveryFullOrderID,
    AddressCustomerID
)
VALUES
(
    @fullOrderID,
    @customerID
)
; /*    delivery calls */

/*   Pizza 1 */
SET
    @pizzaSize = 'XLarge',
    @pizzaCrust = 'Original',
    @pizzaCost = 9.19,
    @pizzaOriginalPrice = 27.94;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */


    /*   Four Cheese Blend */
SET
    @toppingName = 'Four Cheese Blend',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Four Cheese Blend */


    /*   Pepperoni */
SET
    @toppingName = 'Pepperoni',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Pepperoni */



    /*   Sausage */
SET
    @toppingName = 'Sausage',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);

INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Sausage */


CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 1 */



/*   Pizza 2 */
SET
    @pizzaSize = 'XLarge',
    @pizzaCrust = 'Original',
    @pizzaCost = 6.25,
    @pizzaOriginalPrice = 31.50;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */


    /*   Four Cheese Blend */
SET
    @toppingName = 'Four Cheese Blend',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Four Cheese Blend */


    /*   Ham */
SET
    @toppingName = 'Ham',
    @isDouble = TRUE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Ham */



    /*   Pineapple */
SET
    @toppingName = 'Pineapple',
    @isDouble = TRUE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);

INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Pineapple */

    /*   Pizza Discounts */
SET @pizzaDiscountName = 'Specialty Pizza';
CALL fn_process_pizza_discount(@pizzaDiscountName, @pizzaOriginalPrice, @pizzaID, @dollarsSaved); /*    Pizza Discounts */

CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 2 */


/*   Pizza 3 */
SET
    @pizzaSize = 'XLarge',
    @pizzaCrust = 'Original',
    @pizzaCost = 8.18,
    @pizzaOriginalPrice = 26.75;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */


    /*   Four Cheese Blend */
SET
    @toppingName = 'Four Cheese Blend',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Four Cheese Blend */


    /*   Chicken */
SET
    @toppingName = 'Chicken',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Chicken */


    /*   Bacon */
SET
    @toppingName = 'Bacon',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);

INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Bacon */

CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 3 */


CALL fn_find_full_order_costs_and_prices(@fullOrderID, @fullOrderBusinessCost, @fullOrderCustomerBasePrice);

/*   Order Discounts */
SET @orderDiscountName = 'Gameday Special';
CALL fn_process_order_discount(@orderDiscountName, @fullOrderCustomerBasePrice, @fullOrderID, @dollarsSaved);
/*    Order Discounts */

CALL fn_mark_full_order_complete(@fullOrderID); /*    Order 4 */


/*   Order 5 */
SET
    @orderTimestamp = '2023-03-02 17:30:00',
    @orderType = 'Pickup'
;

    /*   Order calls */
INSERT INTO full_order
(
    FullOrderRequestTimestamp,
    FullOrderType,
    FullOrderBusinessCost,
    FullOrderCustomerBasePrice,
    FullOrderCustomerDiscountedPrice
)
VALUES
(
    @orderTimestamp,
    @orderType,
    0,
    0,
    0
);
SET @fullOrderID = LAST_INSERT_ID()
; /*    Order calls */

SET
    @customerFirst = 'Matt',
    @customerLast = 'Engers',
    @customerPhone = '864-474-9953'
;

    /*   pickup calls */
CALL fn_update_customer(@customerFirst, @customerLast, @customerPhone, @customerID);

INSERT INTO pickup
(
    PickupFullOrderID,
    PickupCustomerID
)
VALUES
(
    @fullOrderID,
    @customerID
)
; /*    pickup calls */

/*   Pizza 1 */
SET
    @pizzaSize = 'XLarge',
    @pizzaCrust = 'Gluten-Free',
    @pizzaCost = 4.24,
    @pizzaOriginalPrice = 25.81;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */


    /*   Goat Cheese */
SET
    @toppingName = 'Goat Cheese',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Goat Cheese */


    /*   Roma Tomato */
SET
    @toppingName = 'Roma Tomato',
    @isDouble = FALSE
;
        /*   Topping Calls */
CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
;
        /*    Topping Calls */
    /*    Roma Tomato */


    /*   Green Pepper */
SET
    @toppingName = 'Green Pepper',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Green Pepper */

    /*   Onion */
SET
    @toppingName = 'Onion',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Onion */

    /*   Mushrooms */
SET
    @toppingName = 'Mushrooms',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Mushrooms */


    /*   Black Olives */
SET
    @toppingName = 'Black Olives',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Black Olives */


    /*   Pizza Discounts */
SET @pizzaDiscountName = 'Specialty Pizza';
CALL fn_process_pizza_discount(@pizzaDiscountName, @pizzaOriginalPrice, @pizzaID, @dollarsSaved); /*    Pizza Discounts */


CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 1 */


CALL fn_find_full_order_costs_and_prices(@fullOrderID, @fullOrderBusinessCost, @fullOrderCustomerBasePrice);

CALL fn_mark_full_order_complete(@fullOrderID); /*    Order 5 */


/*   Order 6 */
SET
    @orderTimestamp = '2023-03-02 18:17:00',
    @orderType = 'Delivery'
;

    /*   Order calls */
INSERT INTO full_order
(
    FullOrderRequestTimestamp,
    FullOrderType,
    FullOrderBusinessCost,
    FullOrderCustomerBasePrice,
    FullOrderCustomerDiscountedPrice
)
VALUES
(
    @orderTimestamp,
    @orderType,
    0,
    0,
    0
);
SET @fullOrderID = LAST_INSERT_ID()
; /*    Order calls */

SET
    @customerFirst = 'Frank',
    @customerLast = 'Turner',
    @customerPhone = '864-232-8944',
    @streetNumber = '6745',
    @streetName = 'Wessex St',
    @city = 'Anderson',
    @state = 'SC',
    @zip = '29621'
;

    /*   delivery calls */
CALL fn_update_customer
(
    @customerFirst,
    @customerLast,
    @customerPhone,
    @customerID -- out
);
CALL fn_update_address
(
    @customerID,
    @streetNumber,
    @streetName,
    @city,
    @state,
    @zip
)
;

INSERT INTO delivery
(
    DeliveryFullOrderID,
    AddressCustomerID
)
VALUES
(
    @fullOrderID,
    @customerID
)
; /*    delivery calls */

/*   Pizza 1 */
SET
    @pizzaSize = 'Large',
    @pizzaCrust = 'Thin',
    @pizzaCost = 9.19,
    @pizzaOriginalPrice = 27.94;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */


    /*   Four Cheese Blend */
SET
    @toppingName = 'Four Cheese Blend',
    @isDouble = TRUE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Four Cheese Blend */


    /*   Chicken */
SET
    @toppingName = 'Chicken',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Chicken */


    /*   Green Pepper */
SET
    @toppingName = 'Green Pepper',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Green Pepper */


    /*   Onion */
SET
    @toppingName = 'Onion',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Onion */


    /*   Mushrooms */
SET
    @toppingName = 'Mushrooms',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);

INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Mushrooms */


CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 1 */


CALL fn_find_full_order_costs_and_prices(@fullOrderID, @fullOrderBusinessCost, @fullOrderCustomerBasePrice);
CALL fn_mark_full_order_complete(@fullOrderID); /*    Order 6 */

/*   Order 7 */
SET
    @orderTimestamp = '2023-04-13 20:32:00',
    @orderType = 'Delivery'
;

    /*   Order calls */
INSERT INTO full_order
(
    FullOrderRequestTimestamp,
    FullOrderType,
    FullOrderBusinessCost,
    FullOrderCustomerBasePrice,
    FullOrderCustomerDiscountedPrice
)
VALUES
(
    @orderTimestamp,
    @orderType,
    0,
    0,
    0
);
SET @fullOrderID = LAST_INSERT_ID()
; /*    Order calls */

SET
    @customerFirst = 'Milo',
    @customerLast = 'Auckerman',
    @customerPhone = '864-878-5679',
    @streetNumber = '8879',
    @streetName = 'Suburban Home',
    @city = 'Anderson',
    @state = 'SC',
    @zip = '29621'
;

    /*   delivery calls */
CALL fn_update_customer
(
    @customerFirst,
    @customerLast,
    @customerPhone,
    @customerID -- out
);
CALL fn_update_address
(
    @customerID,
    @streetNumber,
    @streetName,
    @city,
    @state,
    @zip
)
;

INSERT INTO delivery
(
    DeliveryFullOrderID,
    AddressCustomerID
)
VALUES
(
    @fullOrderID,
    @customerID
)
; /*    delivery calls */

    /*   Pizza 1 */
SET
    @pizzaSize = 'Large',
    @pizzaCrust = 'Thin',
    @pizzaCost = 2.75,
    @pizzaOriginalPrice = 18.00;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */


    /*   Four Cheese Blend */
SET
    @toppingName = 'Four Cheese Blend',
    @isDouble = TRUE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Four Cheese Blend */


CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 1 */


    /*   Pizza 2 */
SET
    @pizzaSize = 'Large',
    @pizzaCrust = 'Thin',
    @pizzaCost = 3.25,
    @pizzaOriginalPrice = 19.25;
SET @pizzaDiscountedPrice = @pizzaOriginalPrice;

    /*   Pizza Calls */
CALL fn_retrieve_base_pizza
(
    @pizzaSize, -- in
    @pizzaCrust, -- in
    @basePizzaID, -- out
    @basePizzaCustomerPrice, -- out
    @basePizzaBusinessCost -- out
)
;

INSERT INTO pizza_order
(
    PizzaOrderBasePizzaID,
    PizzaOrderFullOrderID,
    PizzaOrderBusinessCost,
    PizzaOrderCustomerBasePrice,
    PizzaOrderCustomerDiscountedPrice
)
VALUES
(
    @basePizzaID,
    @fullOrderID,
    @pizzaCost,
    @pizzaOriginalPrice,
    @pizzaDiscountedPrice
);
SET @pizzaID = LAST_INSERT_ID()
; /*    Pizza Calls */


    /*   Regular Cheese */
SET
    @toppingName = 'Regular Cheese',
    @isDouble = FALSE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Regular Cheese */


    /*   Pepperoni */
SET
    @toppingName = 'Pepperoni',
    @isDouble = TRUE
;

CALL fn_get_topping_prices(@toppingName, @isDouble, @pizzaSize, @toppingPrice, @toppingCost, @toppingID);


INSERT INTO pizza_order_topping
(
    PizzaOrderToppingPizzaOrderID,
    PizzaOrderToppingToppingID,
    PizzaOrderIsDouble,
    PizzaOrderToppingBusinessCost,
    PizzaOrderToppingCustomerPrice
)
VALUES
(
    @pizzaID,
    @toppingID,
    @isDouble,
    @toppingCost,
    @toppingPrice
)
; /*    Pepperoni */



CALL fn_apply_pizza_discounts(@pizzaID);
CALL fn_mark_pizza_order_complete(@pizzaID); /*    Pizza 2 */



CALL fn_find_full_order_costs_and_prices(@fullOrderID, @fullOrderBusinessCost, @fullOrderCustomerBasePrice);

/*   Order Discounts */
SET @orderDiscountName = 'Employee';
CALL fn_process_order_discount(@orderDiscountName, @fullOrderCustomerBasePrice, @fullOrderID, @dollarsSaved);
/*    Order Discounts */

CALL fn_mark_full_order_complete(@fullOrderID); /*    Order 7 */
