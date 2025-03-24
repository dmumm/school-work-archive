-- Dylan

USE Pizzeria;

DROP TABLE IF EXISTS full_order_discount;
DROP TABLE IF EXISTS pizza_order_discount;
DROP TABLE IF EXISTS pizza_order_topping;
DROP TABLE IF EXISTS pizza_order;
DROP TABLE IF EXISTS base_pizza;
DROP TABLE IF EXISTS topping;
DROP TABLE IF EXISTS discount;
DROP TABLE IF EXISTS coupon;
DROP TABLE IF EXISTS dinein;
DROP TABLE IF EXISTS pickup;
DROP TABLE IF EXISTS delivery;
DROP TABLE IF EXISTS address;
DROP TABLE IF EXISTS customer;
DROP TABLE IF EXISTS full_order;

DROP VIEW IF EXISTS ToppingPopularity;
DROP VIEW IF EXISTS ProfitByPizza;
DROP VIEW IF EXISTS ProfitByOrderType;

DROP SCHEMA IF EXISTS Pizzeria;