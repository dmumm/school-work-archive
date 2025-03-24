-- Dylan main, Bowen support
CREATE SCHEMA IF NOT EXISTS Pizzeria
;

USE Pizzeria
;

CREATE TABLE
  full_order (
    FullOrderID INT PRIMARY KEY AUTO_INCREMENT,
    FullOrderRequestTimestamp DATETIME NOT NULL,
    FullOrderStatus ENUM('In Progress', 'Complete') NOT NULL DEFAULT 'In Progress',
    FullOrderType ENUM('Delivery', 'Pickup', 'Dine-in') NOT NULL,
    FullOrderBusinessCost DECIMAL(10, 2) NOT NULL,
    FullOrderCustomerBasePrice DECIMAL(10, 2) NOT NULL,
    FullOrderCustomerDiscountedPrice DECIMAL(10, 2) NOT NULL
  )
;

CREATE TABLE
  customer (
    CustomerID INT PRIMARY KEY AUTO_INCREMENT,
    CustomerFirstName VARCHAR(255) NOT NULL,
    CustomerLastName VARCHAR(255) NOT NULL,
    CustomerPhoneNumber VARCHAR(255) NOT NULL,
    CustomerHasAddress BOOLEAN NOT NULL DEFAULT FALSE
  )
;

CREATE TABLE
  address (
    AddressCustomerID INT NOT NULL,
    CustomerStreetNumber INT NOT NULL,
    CustomerStreetName VARCHAR(255) NOT NULL,
    CustomerCity VARCHAR(255) NOT NULL,
    CustomerState VARCHAR(255) NOT NULL,
    CustomerZip INT NOT NULL,
    FOREIGN KEY (AddressCustomerID) REFERENCES customer (CustomerID) ON DELETE CASCADE
  )
;

CREATE TABLE
  delivery (
    DeliveryFullOrderID INT PRIMARY KEY,
    AddressCustomerID INT NOT NULL,
    FOREIGN KEY (DeliveryFullOrderID) REFERENCES full_order (FullOrderID),
    FOREIGN KEY (AddressCustomerID) REFERENCES address (AddressCustomerID) ON DELETE CASCADE
  )
;

CREATE TABLE
  pickup (
    PickupFullOrderID INT PRIMARY KEY,
    PickupCustomerID INT NOT NULL,
    FOREIGN KEY (PickupFullOrderID) REFERENCES full_order (FullOrderID) ON DELETE CASCADE,
    FOREIGN KEY (PickupCustomerID) REFERENCES customer (CustomerID)
  )
;

CREATE TABLE
  dinein (
    DineinFullOrderID INT PRIMARY KEY,
    DineinTable INT NOT NULL,
    FOREIGN KEY (DineinFullOrderID) REFERENCES full_order (FullOrderID) ON DELETE CASCADE
  )
;

CREATE TABLE
  coupon (
    CouponID INT PRIMARY KEY AUTO_INCREMENT,
    CouponName VARCHAR(255) NOT NULL UNIQUE,
    CouponEligibility ENUM('Pizza', 'FullOrders', 'Both') NOT NULL DEFAULT 'Both',
    CouponDiscountType ENUM('Dollar', 'Percent') NOT NULL
  )
;

CREATE TABLE
  discount (
    DiscountCouponID INT PRIMARY KEY,
    DiscountAmount DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (DiscountCouponID) REFERENCES coupon (CouponID) ON DELETE CASCADE
  )
;

CREATE TABLE
  topping (
    ToppingID INT PRIMARY KEY AUTO_INCREMENT,
    ToppingName VARCHAR(255) NOT NULL,
    ToppingCurrentCustomerPricePerUnit DECIMAL(10, 2) NOT NULL,
    ToppingCurrentBusinessCostPerUnit DECIMAL(10, 2) NOT NULL,
    ToppingInventoryCurrent INT NOT NULL,
    ToppingInventoryMinimum INT NOT NULL,
    ToppingUnitsInSmall INT NOT NULL,
    ToppingUnitsInMedium INT NOT NULL,
    ToppingUnitsInLarge INT NOT NULL,
    ToppingUnitsInXLarge INT NOT NULL
  )
;

CREATE INDEX idx_topping_name_prices ON topping (
  ToppingName,
  ToppingCurrentCustomerPricePerUnit,
  ToppingCurrentBusinessCostPerUnit
)
;

CREATE TABLE
  base_pizza (
    BasePizzaID INT PRIMARY KEY AUTO_INCREMENT,
    BasePizzaSize ENUM('Small', 'Medium', 'Large', 'XLarge') NOT NULL,
    BasePizzaCrust ENUM('Original', 'Thin', 'Gluten-Free', 'Pan') NOT NULL DEFAULT 'Original',
    BasePizzaCurrentCustomerPrice DECIMAL(10, 2) NOT NULL,
    BasePizzaCurrentBusinessCost DECIMAL(10, 2) NOT NULL
  )
;

CREATE TABLE
  pizza_order (
    PizzaOrderID INT PRIMARY KEY AUTO_INCREMENT,
    PizzaOrderBasePizzaID INT NOT NULL,
    PizzaOrderFullOrderID INT NOT NULL,
    PizzaOrderStatus ENUM('In Progress', 'Complete') NOT NULL DEFAULT 'In Progress',
    PizzaOrderBusinessCost DECIMAL(10, 2) NOT NULL,
    PizzaOrderCustomerBasePrice DECIMAL(10, 2) NOT NULL,
    PizzaOrderCustomerDiscountedPrice DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (PizzaOrderBasePizzaID) REFERENCES base_pizza (BasePizzaID),
    FOREIGN KEY (PizzaOrderFullOrderID) REFERENCES full_order (FullOrderID)
  )
;

CREATE TABLE
  pizza_order_topping (
    PizzaOrderToppingID INT PRIMARY KEY AUTO_INCREMENT,
    PizzaOrderToppingPizzaOrderID INT NOT NULL,
    PizzaOrderToppingToppingID INT NOT NULL,
    PizzaOrderIsDouble BOOLEAN NOT NULL,
    PizzaOrderToppingBusinessCost DECIMAL(10, 2) NOT NULL,
    PizzaOrderToppingCustomerPrice DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (PizzaOrderToppingPizzaOrderID) REFERENCES pizza_order (PizzaOrderID),
    FOREIGN KEY (PizzaOrderToppingToppingID) REFERENCES topping (ToppingID)
  )
;

CREATE TABLE
  pizza_order_discount (
    PizzaOrderDiscountID INT PRIMARY KEY AUTO_INCREMENT,
    PizzaOrderDiscountPizzaOrderID INT NOT NULL,
    PizzaOrderDiscountCouponID INT NOT NULL,
    PizzaOrderDollarsSaved DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (PizzaOrderDiscountPizzaOrderID) REFERENCES pizza_order (PizzaOrderID),
    FOREIGN KEY (PizzaOrderDiscountCouponID) REFERENCES coupon (CouponID)
  )
;

CREATE TABLE
  full_order_discount (
    FullOrderDiscountID INT PRIMARY KEY AUTO_INCREMENT,
    FullOrderDiscountFullOrderID INT NOT NULL,
    FullOrderDiscountCouponID INT NOT NULL,
    FullOrderDiscountDollarsSaved DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (FullOrderDiscountFullOrderID) REFERENCES full_order (FullOrderID),
    FOREIGN KEY (FullOrderDiscountCouponID) REFERENCES coupon (CouponID)
  )
;