CREATE TABLE CUSTOMER
  (
    CustomerID     INT         NOT NULL,
    CONSTRAINT CUS_PK
      PRIMARY KEY(CustomerID)
  );

CREATE TABLE OUTSIDE
  (
    outID     INT         NOT NULL,
    phone     CHAR(10)    NOT NULL,
    name      VARCHAR(30)    NOT NULL,
    CONSTRAINT OUT_PK
      PRIMARY KEY(outID, phone),
    CONSTRAINT OUT_CUS_FK
      FOREIGN KEY(outID) REFERENCES CUSTOMER(CustomerID)
  );

CREATE TABLE DELIVER
  (
    deliveringTo     INT         NOT NULL,
    address          VARCHAR(30) NOT NULL,
    CONSTRAINT DEL_PK
      PRIMARY KEY(deliveringTo, address),
    CONSTRAINT DEL_OUT_FK
      FOREIGN KEY(deliveringTo) REFERENCES OUTSIDE(outID)
  );

CREATE TABLE INSIDE
  (
    inID     INT         NOT NULL,
    tabNum   INT         NOT NULL,
    CONSTRAINT IN_PK
      PRIMARY KEY(inID),
    CONSTRAINT IN_CUS_FK
      FOREIGN KEY(inID) REFERENCES CUSTOMER(CustomerID)
  );

CREATE TABLE SEATS
  (
    diID        INT         NOT NULL,
    seatNum     INT         NOT NULL,
    CONSTRAINT SEATS_PK
      PRIMARY KEY(diID, seatNum),
    CONSTRAINT SEATS_IN_FK
      FOREIGN KEY(diID) REFERENCES INSIDE(inID)
  );

CREATE TABLE ORDERS
  (
    orderID     INT         NOT NULL,
    orderedBy   INT         NOT NULL,
    orderTime   Timestamp   NOT NULL,
    CONSTRAINT ORD_PK
      PRIMARY KEY(orderID),
    CONSTRAINT ORD_CUS_FK
      FOREIGN KEY(orderedBy) REFERENCES CUSTOMER(CustomerID)
  );

CREATE TABLE PIZZA
  (
    pizzaID     INT         NOT NULL,
    forOrder    INT         NOT NULL,
    complete    TINYINT(1)  NOT NULL DEFAULT 0,
    type        VARCHAR(11) NOT NULL,
    size        VARCHAR(7)  NOT NULL,
    CONSTRAINT PIZ_PK
      PRIMARY KEY(pizzaID),
    CONSTRAINT PIZ_CUS_FK
      FOREIGN KEY(forOrder) REFERENCES ORDERS(orderID)
  );

CREATE TABLE BASE_PRICE
  (
    size        VARCHAR(7)   NOT NULL,
    type        VARCHAR(11)    NOT NULL,
    price       DECIMAL(4,2)  NOT NULL,
    cost        DECIMAL(4,2)  NOT NULL,
    CONSTRAINT PRI_PK
      PRIMARY KEY(type, size)
  );


CREATE TABLE TOPPINGS
  (
    toppingID   INT           NOT NULL,
    topName     INT           NOT NULL,
    price       DECIMAL(3,2)  NOT NULL,
    costPerUnit DECIMAL(3,2)  NOT NULL,
    inventory   INT           NOT NULL,
    unitsS      DECIMAL(4,2)  NOT NULL,
    unitsM      DECIMAL(4,2)  NOT NULL,
    unitsL      DECIMAL(4,2)  NOT NULL,
    unitsX      DECIMAL(4,2)  NOT NULL,
    CONSTRAINT TOP_PK
      PRIMARY KEY(toppingID)
  );

CREATE TABLE TOPPING_ON
  (
    tID         INT         NOT NULL,
    pID         INT         NOT NULL,
    isDouble    TINYINT(1)  NOT NULL DEFAULT 0,
    CONSTRAINT ON_PK
      PRIMARY KEY(tID, pID),
    CONSTRAINT ON_PIZ_FK
      FOREIGN KEY(pID) REFERENCES PIZZA(pizzaID),
    CONSTRAINT ON_TOP_FK
      FOREIGN KEY(tID) REFERENCES TOPPINGS(toppingID)
  );

CREATE TABLE DISCOUNT
  (
    discountID    INT        NOT NULL,
    disName       INT        NOT NULL,
    percentOff    INT                ,
    dollarsOff    DECIMAL(4,2)       ,
    CONSTRAINT DIS_PK
      PRIMARY KEY(discountID)
  );

CREATE TABLE PIZZA_DISCOUNT
  (
    pizDiscountID    INT        NOT NULL,
    pizID            INT        NOT NULL,
    CONSTRAINT DIS_PK
      PRIMARY KEY(pizDiscountID, pizID),
    CONSTRAINT PIZDIS_DIS_FK
      FOREIGN KEY(pizDiscountID) REFERENCES DISCOUNT(discountID),
    CONSTRAINT PIZDIS_PIZ_FK
      FOREIGN KEY(pizID) REFERENCES PIZZA(pizzaID)
  );

CREATE TABLE ORDER_DISCOUNT
  (
    ordDiscountID    INT        NOT NULL,
    ordID            INT        NOT NULL,
    CONSTRAINT DIS_PK
      PRIMARY KEY(ordDiscountID, ordID),
    CONSTRAINT ORDDIS_DIS_FK
      FOREIGN KEY(ordDiscountID) REFERENCES DISCOUNT(discountID),
    CONSTRAINT ORDDIS_ORD_FK
      FOREIGN KEY(ordID) REFERENCES ORDERS(orderID)
  );
