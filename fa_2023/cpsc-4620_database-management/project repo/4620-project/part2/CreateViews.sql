-- Bowen
USE Pizzeria
;

DROP VIEW IF EXISTS ToppingPopularity;

CREATE VIEW ToppingPopularity AS
SELECT
  T.ToppingName AS Topping,
  COUNT(PT.PizzaOrderToppingID) + SUM(CASE WHEN PT.PizzaOrderIsDouble = 1 THEN 1 ELSE 0 END) AS ToppingCount
FROM
  topping T
  LEFT JOIN pizza_order_topping PT ON T.ToppingID = PT.PizzaOrderToppingToppingID
  LEFT JOIN pizza_order P ON PT.PizzaOrderToppingPizzaOrderID = P.PizzaOrderID
GROUP BY
  T.ToppingName
ORDER BY
  ToppingCount DESC;

SELECT * FROM ToppingPopularity;

DROP VIEW IF EXISTS ProfitByPizza;

CREATE VIEW ProfitByPizza AS
SELECT BP.BasePizzaSize AS 'Size',
  BP.BasePizzaCrust AS Crust,
-- SUM((BP.BasePizzaCurrentCustomerPrice-BP.BasePizzaCurrentBusinessCost) + (T.PizzaOrderToppingCustomerPrice-T.PizzaOrderBusinessCost)) AS Profit,
  SUM(FO.FullOrderCustomerBasePrice - FO.fullOrderBusinessCost) AS Profit,
  DATE_FORMAT(FO.FullOrderRequestTimestamp, '%c/%Y') AS 'Order Month'
FROM
  base_pizza BP
JOIN pizza_order PO ON PO.PizzaOrderBasePizzaID = BP.BasePizzaID
JOIN full_order FO ON FO.FullOrderID = PO.PizzaOrderFullOrderID

WHERE FO.FullOrderRequestTimestamp < '2023-04-30' AND FO.FullOrderRequestTimestamp > '2023-03-01'
GROUP BY
  BP.BasePizzaSize, Crust
ORDER BY
  Profit
  ;

  SELECT * FROM ProfitByPizza;

  DROP VIEW IF EXISTS ProfitByOrderType;

CREATE VIEW ProfitByOrderType AS
SELECT
  FO.FullOrderType,
  DATE_FORMAT(FO.FullOrderRequestTimestamp, '%c/%Y') AS `Order Month`,
  SUM(FO.FullOrderCustomerBasePrice) AS TotalOrderPrice,
  SUM(FO.FullOrderBusinessCost) AS TotalOrderCost,
  SUM(FO.FullOrderCustomerBasePrice - FO.FullOrderBusinessCost) AS Profit
FROM full_order FO
WHERE (FO.FullOrderRequestTimestamp < '2023-04-30' AND FO.FullOrderRequestTimestamp > '2023-03-01')
GROUP BY FO.FullOrderType, DATE_FORMAT(FO.FullOrderRequestTimestamp, '%c/%Y')

UNION ALL

SELECT
  NULL AS FullOrderType,
  'Grand Total' AS `Order Month`,
  SUM(FO.FullOrderCustomerBasePrice) AS TotalOrderPrice,
  SUM(FO.FullOrderBusinessCost) AS TotalOrderCost,
  SUM(FO.FullOrderCustomerBasePrice - FO.FullOrderBusinessCost) AS Profit
FROM full_order FO
WHERE (FO.FullOrderRequestTimestamp < '2023-04-30' AND FO.FullOrderRequestTimestamp > '2023-03-01');

  SELECT * FROM ProfitByOrderType;