package cpsc4620;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.ArrayList;

/*
 * This file is where most of your code changes will occur You will write the code to retrieve
 * information from the database, or save information to the database
 *
 * The class has several hard coded static variables used for the connection, you will need to
 * change those to your connection information
 *
 * This class also has static string variables for pickup, delivery and dine-in. If your database
 * stores the strings differently (i.e "pick-up" vs "pickup") changing these static variables will
 * ensure that the comparison is checking for the right string in other places in the program. You
 * will also need to use these strings if you store this as boolean fields or an integer.
 *
 *
 */

/**
 * A utility class to help add and retrieve information from the database
 */

public final class DBNinja {

	private static Connection conn;

	public final static String PICKUP = "Pickup";
	public final static String DELIVERY = "Delivery";
	public final static String DINE_IN = "Dine-in";

	public final static String SIZE_S = "Small";
	public final static String SIZE_M = "Medium";
	public final static String SIZE_L = "Large";
	public final static String SIZE_XL = "XLarge";

	public final static String CRUST_ORIG = "Original";
	public final static String CRUST_THIN = "Thin";
	public final static String CRUST_GF = "Gluten-Free";
	public final static String CRUST_PAN = "Pan";

	public final static String COMPLETE = "Complete";
	public final static String OPEN = "In Progress";

	private static boolean connect_to_db() throws SQLException, IOException {

		try {
			conn = DBConnector.make_connection();
			return true;
		} catch (SQLException e) {
			System.out.print("There was a Conn Issue!");
			return false;
		} catch (IOException e) {
			return false;
		}

	}

	/*
	 * add code to add the order to the DB. Remember that we're not just
	 * adding the order to the order DB table, but we're also recording
	 * the necessary data for the delivery, dinein, and pickup tables
	 */
	public static void addOrder(Order o) throws SQLException, IOException {

		connect_to_db();
		Timestamp full_order_timestamp = new Timestamp(System.currentTimeMillis());
		o.setDate(full_order_timestamp.toString());

		String q1 = "INSERT INTO full_order" +
				"( FullOrderRequestTimestamp, FullOrderType, FullOrderBusinessCost, FullOrderCustomerBasePrice, FullOrderCustomerDiscountedPrice )"
				+
				"VALUES" +
				"(?, ?, ?, ?, ?)";

		String q2 = " SET @fullOrderID = LAST_INSERT_ID()";

		String q3 = "";
		if (o instanceof DineinOrder == false) {
			q3 = "CALL fn_update_customer" +
					"(?, ?, ?, ?);";
		}

		String q4 = "";
		String q5 = "";
		if (o instanceof DeliveryOrder) {
			q4 = "CALL fn_update_address" +
					"(?, ?, ?, ?, ?, ?);";
			q5 = "INSERT INTO delivery" +
					"( DeliveryFullOrderID, AddressCustomerID)" +
					"VALUES" +
					"(?, ?);";
		}

		PreparedStatement s1 = conn.prepareStatement(q1);
		s1.setString(1, o.getDate());
		s1.setString(2, o.getOrderType());
		s1.setDouble(3, o.getBusPrice());
		s1.setDouble(4, o.getCustPrice());
		s1.setDouble(5, o.getCustPrice()); // TODO: Change this to discounted price
		conn.prepareStatement(q2);

		if (o instanceof DineinOrder == false) {
			PreparedStatement s3 = conn.prepareStatement(q3);
			s3.setString(1, DBNinja.getCustomerName(o.getCustID()));
		}

		for (Pizza p : o.getPizzaList()) {
			addPizza(p);
		}

		for (Discount d : o.getDiscountList()) {
			useOrderDiscount(o, d);
		}

		conn.close();

		// DO NOT FORGET TO CLOSE YOUR CONNECTION
	}

	/*
	 * Add the code needed to insert the pizza into into the database.
	 * Keep in mind adding pizza discounts and toppings associated with the pizza,
	 * there are other methods below that may help with that process.
	 *
	 */
	public static void addPizza(Pizza p) throws SQLException, IOException {
		connect_to_db();

		Timestamp full_order_timestamp = new Timestamp(System.currentTimeMillis());
		p.setPizzaDate(full_order_timestamp.toString());

		String q1 = "" +
				"INSERT INTO pizza_order" +
				"(PizzaOrderBasePizzaID, PizzaOrderFullOrderID, PizzaOrderBusinessCost, PizzaOrderCustomerBasePrice, PizzaOrderCustomerDiscountedPrice)"
				+
				"VALUES" +
				"(?, fullOrderID, ?, ?, ?)";

		String q2 = " SET @pizzaID = LAST_INSERT_ID()";

		PreparedStatement s1 = conn.prepareStatement(q1);
		s1.setInt(1, retrieveBasePizza(p.getSize(), p.getCrustType()).getPizzaID());
		s1.setDouble(3, p.getBusPrice());
		s1.setDouble(4, p.getCustPrice());
		s1.setDouble(5, p.getCustPrice()); // TODO: Change this to discounted price
		s1.executeUpdate();

		PreparedStatement s2 = conn.prepareStatement(q2);
		s2.executeQuery();

		for (Topping t : p.getToppings()) {
			useTopping(p, t, p.getIsDoubleArray()[t.getTopID()]);
		}

		for (Discount d : p.getDiscounts()) {
			usePizzaDiscount(p, d);
		}
		conn.close();
	}

	/*
	 * this method will update toppings inventory in SQL and add entities to the
	 * Pizzatops table. Pass in the p pizza that is using t topping
	 *
	 * This method should do 2 two things.
	 * - update the topping inventory every time we use t topping (accounting for
	 * extra toppings as well)
	 * - connect the topping to the pizza
	 *
	 * Ideally, you should't let toppings go negative....but this should be dealt
	 * with BEFORE calling this method.
	 *
	 */
	public static void useTopping(Pizza p, Topping t, boolean isDoubled) throws SQLException, IOException {

		String doubleIfExtra = isDoubled ? " * 2" : "";
		String q1 = "" +
				"UPDATE topping " +
				"SET ToppingInventoryCurrent = " +
				"ToppingInventoryCurrent - " +
				"(ToppingUnitsIn" + p.getSize() + doubleIfExtra + ") " +
				"WHERE ToppingID = ?;";

		String q2 = "" +
				"INSERT INTO pizza_order_topping " +
				"(PizzaOrderToppingPizzaOrderID, PizzaOrderToppingToppingID, PizzaOrderIsDouble, PizzaOrderToppingBusinessCost, PizzaOrderToppingCustomerPrice) "
				+
				"VALUES " +
				"(@pizzaID, ?, ?, ?, ?);";

		try {

			connect_to_db();

			PreparedStatement s1 = conn.prepareStatement(q1);
			s1.setInt(1, t.getTopID());
			System.out.println(s1.toString()); // TODO: debug print
			s1.executeUpdate();

			PreparedStatement s2 = conn.prepareStatement(q2);
			s2.setInt(2, t.getTopID());
			s2.setBoolean(3, isDoubled);
			s2.setDouble(4, t.getBusPrice());
			s2.setDouble(5, t.getCustPrice());
			System.out.println(s2.toString()); // TODO: debug print
			s2.executeUpdate();

		} catch (Exception e) {
			System.out.println("Error in useTopping");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}

		conn.close();
	}

	/*
	 * This method connects a discount with a Pizza in the database.
	 * What that means will be specific to your implementatinon.
	 */
	public static void usePizzaDiscount(Pizza p, Discount d) throws SQLException, IOException {

		String q1 = "" +
				"CALL fn_process_pizza_discount " +
				"(?, ?, ?, @dollarsSaved)";

		String discount_name = d.getDiscountName();
		double order_original_price = p.getCustPrice();
		int pizza_id = p.getOrderID();

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			s1.setString(1, discount_name);
			s1.setDouble(2, order_original_price);
			s1.setInt(3, pizza_id);
			s1.executeUpdate();

		} catch (Exception e) {
			System.out.println("Error in usePizzaDiscount");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}

		conn.close();
	}

	/*
	 * This method connects a discount with an order in the database
	 *
	 * You might use this, you might not depending on where / how to want to update
	 * this information in the dabast
	 */
	public static void useOrderDiscount(Order o, Discount d) throws SQLException, IOException {

		String q1 = "" +
				"CALL fn_process_order_discount " +
				"(?, ?, ?, @dollarsSaved)";

		String discount_name = d.getDiscountName();
		double order_original_price = o.getCustPrice();
		int order_id = o.getOrderID();

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			s1.setString(1, discount_name);
			s1.setDouble(2, order_original_price);
			s1.setInt(3, order_id);
			s1.executeUpdate();

		} catch (Exception e) {
			System.out.println("Error in useOrderDiscount");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}
	}

	/*
	 * This method adds a new customer to the database.
	 */
	public static void addCustomer(Customer c) throws SQLException, IOException {

		connect_to_db();

		String q1 = "" +
				"INSERT INTO customer " +
				"(CustomerFirstName, CustomerLastName, CustomerPhoneNumber) " +
				"VALUES " +
				"(?, ?, ?);";

		PreparedStatement s1 = conn.prepareStatement(q1);
		s1.setString(1, c.getFName());
		s1.setString(2, c.getLName());
		s1.setString(3, c.getPhone());
		s1.executeUpdate();

		conn.close();
	}

	/*
	 * Find the specifed order in the database and mark that order as complete in
	 * the database.
	 */
	public static void completeOrder(Order o) throws SQLException, IOException {
		String q1 = "UPDATE full_order SET isComplete = ? WHERE FullOrderID = ?";

		try {
			
			connect_to_db();

			PreparedStatement s1 = conn.prepareStatement(q1);
			s1.setString(1, COMPLETE);
			s1.setInt(2, o.getOrderID());
			s1.executeUpdate();

		} catch (Exception e) {
			System.out.println("Error in completeOrder");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}

	}

	public static ArrayList<Order> getOrders(boolean openOnly) throws SQLException, IOException {
		connect_to_db();
		/*
		 * Return an arraylist of all of the orders.
		 * openOnly == true => only return a list of open (ie orders that have not been
		 * marked as completed)
		 * == false => return a list of all the orders in the database
		 * Remember that in Java, we account for supertypes and subtypes
		 * which means that when we create an arrayList of orders, that really
		 * means we have an arrayList of dineinOrders, deliveryOrders, and pickupOrders.
		 *
		 * Don't forget to order the data coming from the database appropriately.
		 *
		 */

		PreparedStatement os;
		ArrayList<Order> resultBuilder = new ArrayList<>();
		String q1;
		if (openOnly) {
			System.out.println("A registered");
			q1 = "SELECT * FROM full_order WHERE FullOrderStatus = 'In Progress';";
		} else {
			q1 = "SELECT * FROM full_order;";
		}

		ResultSet rset;
		os = conn.prepareStatement(q1);
		rset = os.executeQuery();
		int x = -2;
		while (rset.next()) {
			if (rset.getString("FullOrderStatus").equals(OPEN)) {
				x = 0;
			} else {
				x = 1;
			}
			Order a = new Order(rset.getInt("FullOrderID"), 0, rset.getString("FullOrderType"),
					rset.getString("FullOrderRequestTimestamp"), rset.getDouble("FullOrderCustomerBasePrice"),
					rset.getDouble("FullOrderBusinessCost"), x);
			resultBuilder.add(a);
		}

		conn.close();
		return resultBuilder;
	}

	public static ArrayList<Order> getCompleteOrders() throws SQLException, IOException {
		connect_to_db();
		PreparedStatement os;
		ArrayList<Order> resultBuilder = new ArrayList<>();
		String q1;
		q1 = "SELECT * FROM full_order WHERE FullOrderStatus = 'Complete';";

		ResultSet rset;
		os = conn.prepareStatement(q1);
		rset = os.executeQuery();
		int x = -2;
		while (rset.next()) {
			if (rset.getString("FullOrderStatus").equals(OPEN)) {
				x = 0;
			} else {
				x = 1;
			}
			Order a = new Order(rset.getInt("FullOrderID"), 0, rset.getString("FullOrderType"),
					rset.getString("FullOrderRequestTimestamp"), rset.getDouble("FullOrderCustomerBasePrice"),
					rset.getDouble("FullOrderBusinessCost"), x);
			resultBuilder.add(a);
		}

		conn.close();
		return resultBuilder;
	}

	public static Order getLastOrder() throws SQLException, IOException {
		connect_to_db();
		/*
		 * Query the database for the LAST order added
		 * then return an Order object for that order.
		 * NOTE...there should ALWAYS be a "last order"!
		 */

		PreparedStatement os;
		String query = "SELECT * FROM full_order ORDER BY FullOrderID DESC LIMIT 1;"; // Query to get the last order

		ResultSet rset;
		os = conn.prepareStatement(query);
		rset = os.executeQuery();

		Order lastOrder = null;
		if (rset.next()) {
			int statusFlag = rset.getString("FullOrderStatus").equals("open") ? 0 : 1;
			lastOrder = new Order(rset.getInt("FullOrderID"), 0, rset.getString("FullOrderType"),
					rset.getString("FullOrderRequestTimestamp"), rset.getDouble("FullOrderCustomerBasePrice"),
					rset.getDouble("FullOrderBusinessCost"), statusFlag);
		}

		conn.close();
		return lastOrder;
	}

	public static void printLastOrder() throws SQLException, IOException {
		Order o = getLastOrder();
		System.out.println("Last Order:\nOrder ID\tOrder Type\tOrder Timestamp\t Order Status");
		System.out.println(o.getOrderID() + "\t" + o.getOrderType() + "\t" + o.getDate() + "\t" + o.getIsComplete());

	}

	/*
	 * Query the database for ALL the orders placed on a specific date
	 * and return a list of those orders.
	 */
	public static ArrayList<Order> getOrdersByDate(String date) throws SQLException, IOException {

		int id, customer, status;
		String type, timestamp;
		double customer_price, business_cost;

		ArrayList<Order> orders_on_date = new ArrayList<>();

		String q1 = ""
				+ "SELECT fo.*, "
				+ "CASE "
				+ "    WHEN fo.FullOrderType = 'pickup' THEN p.PickupCustomerID "
				+ "    WHEN fo.FullOrderType = 'delivery' THEN d.AddressCustomerID "
				+ "END AS CustomerID "
				+ "FROM full_order fo "
				+ "    LEFT JOIN pickup p ON fo.FullOrderID = p.PickupFullOrderID "
				+ "    LEFT JOIN delivery d ON fo.FullOrderID = d.DeliveryFullOrderID "
				+ "WHERE DATE(fo.FullOrderRequestTimestamp) = ?;";

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			s1.setString(1, date);
			ResultSet r1 = s1.executeQuery();

			while (r1.next()) {

				id = r1.getInt("FullOrderID");
				customer = r1.getInt("FullOrderCustomerID"); // field doesnt exist
				type = r1.getString("FullOrderType");
				timestamp = r1.getString("FullOrderRequestTimestamp");
				customer_price = r1.getDouble("FullOrderCustomerBasePrice");
				business_cost = r1.getDouble("FullOrderBusinessCost");
				status = r1.getString("FullOrderStatus").equals(DBNinja.OPEN) ? 0 : 1;

				Order a = new Order(id, customer, type, timestamp, customer_price, business_cost, status);
				orders_on_date.add(a);
			}

		} catch (Exception e) {
			System.out.println("Error in getOrdersByDate");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}
		return orders_on_date;
	}

	public static ArrayList<Discount> getDiscountList() throws SQLException, IOException {
		connect_to_db();
		/*
		 * Query the database for all the available discounts and
		 * return them in an arrayList of discounts.
		 *
		 */
		PreparedStatement os;
		ArrayList<Discount> resultBuilder = new ArrayList<>();
		String q1;
		q1 = "SELECT * FROM coupon C JOIN discount D ON D.DiscountCouponID = C.couponID";

		ResultSet rset;
		os = conn.prepareStatement(q1);
		// os.setInt(1, );
		rset = os.executeQuery();
		boolean isPercent;
		while (rset.next()) {
			if (rset.getString("CouponDiscountType").equals("Dollar")) {
				isPercent = false;
			} else {
				isPercent = true;
			}
			Discount d = new Discount(rset.getInt("CouponID"), rset.getString("CouponName"),
					rset.getDouble("DiscountAmount"), isPercent);
			resultBuilder.add(d);
		}

		conn.close();
		return resultBuilder;
		// DO NOT FORGET TO CLOSE YOUR CONNECTION
	}

	/*
	 * Query the database for a discount using it's name.
	 * If found, then return an OrderDiscount object for the discount.
	 * If it's not found....then return null
	 *
	 */
	public static Discount findDiscountByName(String name) throws SQLException, IOException {
		ArrayList<Discount> list = getDiscountList();

		for (int i = 0; i < list.size(); i++) {

			if (list.get(i).getDiscountName().equals(name)) {
				return list.get(i);
			}

		}

		return null;
	}

	/*
	 * Query the data for all the customers and return an arrayList of all the
	 * customers.
	 * Don't forget to order the data coming from the database appropriately.
	 */
	public static ArrayList<Customer> getCustomerList() throws SQLException, IOException {

		ArrayList<Customer> customer_list = new ArrayList<>();
		String q1 = "SELECT * FROM customer;";
		int id;
		String fname, lname, phone;

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			ResultSet r1 = s1.executeQuery();
			while (r1.next()) {

				id = r1.getInt("CustomerID");
				fname = r1.getString("CustomerFirstName");
				lname = r1.getString("CustomerLastName");
				phone = r1.getString("CustomerPhoneNumber");

				Customer c = new Customer(id, fname, lname, phone);

				customer_list.add(c);
			}

		} catch (Exception e) {
			System.out.println("Error in getCustomerList");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}

		return customer_list;
	}

	public static Customer findCustomerByPhone(String phoneNumber) throws SQLException, IOException {
		/*
		 * Query the database for a customer using a phone number.
		 * If found, then return a Customer object for the customer.
		 * If it's not found....then return null
		 */
		int index = -1;
		ArrayList<Customer> list = getCustomerList();

		for (int i = 0; i < list.size(); i++) {
			if (list.get(i).getPhone().equals(phoneNumber)) {
				index = i;
				break;
			}
		}
		if (index != -1) {
			return list.get(index);
		} else {
			return null;
		}

	}

	/*
	 * Queries the database and prints the current topping list with quantities.
	 * The result should be readable and sorted as indicated in the prompt.
	 */
	public static ArrayList<Topping> getToppingList() throws SQLException, IOException {
		ArrayList<Topping> list = new ArrayList<>();
		String q1 = "SELECT * FROM topping;";

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			ResultSet r1 = s1.executeQuery();

			while (r1.next()) {

				Topping t = new Topping(
						r1.getInt("ToppingID"),
						r1.getString("ToppingName"),
						r1.getDouble("ToppingUnitsInSmall"),
						r1.getDouble("ToppingUnitsInMedium"),
						r1.getDouble("ToppingUnitsInLarge"),
						r1.getDouble("ToppingUnitsInXLarge"),
						r1.getDouble("ToppingCurrentCustomerPricePerUnit"),
						r1.getDouble("ToppingCurrentBusinessCostPerUnit"),
						r1.getInt("ToppingInventoryMinimum"),
						r1.getInt("ToppingInventoryCurrent"));

				list.add(t);

			}

		} catch (Exception e) {
			System.out.println("Error in getToppingList");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}
		return list;
	}

	/*
	 * Query the database for the topping using it's name.
	 * If found, then return a Topping object for the topping.
	 * If it's not found....then return null
	 */
	public static Topping findToppingByName(String name) throws SQLException, IOException {

		ArrayList<Topping> list = getToppingList();

		for (int i = 0; i < list.size(); i++) {
			if (list.get(i).getTopName().equals(name)) {
				return list.get(i);
			}
		}
		return null;

	}

	/*
	 * Updates the quantity of the topping in the database by the amount specified.
	 */
	public static void addToInventory(Topping t, double quantity) throws SQLException, IOException {
		String q1 = "UPDATE topping SET ToppingInventoryCurrent = ? WHERE ToppingID = ?";
		double new_quantity = t.getCurINVT() + quantity;
		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			s1.setDouble(1, new_quantity);
			s1.setInt(2, t.getTopID());
			s1.executeUpdate();

		} catch (Exception e) {
			System.out.println("Error in addToInventory");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}
	}

	/*
	 * Query the database for the base pizza with the specified size and crust.
	 */
	public static Pizza retrieveBasePizza(String size, String crust) throws SQLException, IOException {

		final int NULL_INT = -1;
		Timestamp time = new Timestamp(System.currentTimeMillis());
		double customer_price = getBaseCustPrice(size, crust);
		double business_price = getBaseBusPrice(size, crust);

		Pizza base_pizza = new Pizza(NULL_INT, crust, size, NULL_INT, OPEN, time.toString(), customer_price,
				business_price);

		return base_pizza;
	}

	/*
	 * Query the database for id for that size and crust pizza.
	 */
	public static int getBasePizzaID(String size, String crust) throws SQLException, IOException {

		String q1 = "" +
				"SELECT BasePizzaID " +
				"FROM base_pizza WHERE BasePizzaSize = ? AND BasePizzaCrust = ?";

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			s1.setString(1, size);
			s1.setString(2, crust);

			ResultSet rset = s1.executeQuery();

			if (rset.next()) {
				return rset.getInt("BasePizzaID");
			}
		} catch (Exception e) {
			System.out.println("Error in getBasePizzaID");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}
		return -1;
	}

	/*
	 * Query the database for the base customer price for that size and crust pizza.
	 */
	public static double getBaseCustPrice(String size, String crust) throws SQLException, IOException {
		String q1 = "" +
				"SELECT BasePizzaCurrentCustomerPrice " +
				"FROM base_pizza WHERE BasePizzaSize = ? AND BasePizzaCrust = ?";

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			s1.setString(1, size);
			s1.setString(2, crust);

			ResultSet rset = s1.executeQuery();

			if (rset.next()) {
				return rset.getDouble("BasePizzaCurrentCustomerPrice");
			}

		} catch (Exception e) {
			System.out.println("Error in getBaseCustPrice");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}
		return 0.0;
	}

	/*
	 * Query the database fro the base business price for that size and crust pizza.
	 */
	public static double getBaseBusPrice(String size, String crust) throws SQLException, IOException {

		String q1 = "" +
				"SELECT BasePizzaCurrentBusinessCost " +
				"FROM base_pizza WHERE BasePizzaSize = ? AND BasePizzaCrust = ?";

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			s1.setString(1, size);
			s1.setString(2, crust);

			ResultSet rset = s1.executeQuery();

			if (rset.next()) {
				return rset.getDouble("BasePizzaCurrentBusinessCost");
			}

		} catch (Exception e) {
			System.out.println("Error in getBaseBusPrice");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}
		return 0.0;
	}

	/*
	 * Queries the database and prints the current topping list with quantities.
	 * The result should be readable and sorted as indicated in the prompt.
	 */
	public static void printInventory() throws SQLException, IOException {

		String q1 = "SELECT * FROM topping;";

		connect_to_db();
		PreparedStatement s1 = conn.prepareStatement(q1);
		ResultSet rset = s1.executeQuery();
		while (rset.next()) {
			System.out.println(rset.getString("ToppingID") + "\t" + rset.getString("ToppingName") + "\t"
					+ rset.getString("ToppingInventoryCurrent"));
		}
		conn.close();
	}

	/*
	 * Prints the ToppingPopularity view. Remember that this view
	 * needs to exist in your DB, so be sure you've run your createViews.sql
	 * files on your testing DB if you haven't already.
	 *
	 * The result should be readable and sorted as indicated in the prompt.
	 */
	public static void printToppingPopReport() throws SQLException, IOException {

		String topping_name;
		int topping_orders;

		String q1 = "SELECT * FROM ToppingPopularity";

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			ResultSet r1 = s1.executeQuery();

			if (!r1.next()) {
				System.out.println("No orders found");
			}

			System.out.println("Topping\tTopping Count");

			while (r1.next()) {

				topping_name = r1.getString("Topping");
				topping_orders = r1.getInt("ToppingCount");

				System.out.println(topping_name + "\t" + topping_orders);
			}

		} catch (Exception e) {
			System.out.println("Error in printToppingPopReport");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}
	}

	/*
	 * Prints the ProfitByPizza view. Remember that this view
	 * needs to exist in your DB, so be sure you've run your createViews.sql
	 * files on your testing DB if you haven't already.
	 *
	 * The result should be readable and sorted as indicated in the prompt
	 */
	public static void printProfitByPizzaReport() throws SQLException, IOException {
		String size, crust, month;
		double profit;

		String q1 = "SELECT * FROM ProfitByPizza";

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			ResultSet r1 = s1.executeQuery();

			if (!r1.next()) {
				System.out.println("No orders found");
			}

			System.out.println("Size\tCrust\tProfit\tOrder Month");
			while (r1.next()) {

				size = r1.getString("Size");
				crust = r1.getString("Crust");
				profit = r1.getDouble("Profit");
				month = r1.getString("Order Month");

				System.out.println(size + "\t" + crust + "\t" + profit + "\t" + month + "\t");
			}

		} catch (Exception e) {
			System.out.println("Error in printProfitByPizzaReport");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}
	}

	public static void printProfitByOrderType() throws SQLException, IOException {
		/*
		 * Prints the ProfitByOrderType view. Remember that this view
		 * needs to exist in your DB, so be sure you've run your createViews.sql
		 * files on your testing DB if you haven't already.
		 *
		 * The result should be readable and sorted as indicated in the prompt.
		 */
		String type, month;
		double price, cost, profit;

		String q1 = "SELECT * FROM ProfitByOrderType";

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			ResultSet r1 = s1.executeQuery();
			System.out.println("Order Type\t Order Month\t Order Price   Order Cost   Profit");

			if (!r1.next()) {
				System.out.println("No orders found");
			}

			while (r1.next()) {
				type = r1.getString("FullOrderType");
				month = r1.getString("Order Month");
				price = r1.getDouble("TotalOrderPrice");
				cost = r1.getDouble("TotalOrderCost");
				profit = r1.getDouble("Profit");
				System.out.println(type + "\t" + month + "\t" + price + "\t" + cost + "\t" + profit);
			}

		} catch (Exception e) {
			System.out.println("Error in printProfitByOrderType");
			System.out.println("Exception type: " + e.getClass().getName());
		} finally {
			conn.close();
		}
	}

	public static String getCustomerName(int CustID) throws SQLException, IOException {
		/*
		 * This is a helper method to fetch and format the name of a customer
		 * based on a customer ID. This is an example of how to interact with
		 * your database from Java. It's used in the model solution for this
		 * project...so the code works!
		 *
		 * OF COURSE....this code would only work in your application if the table &
		 * field names match!
		 *
		 */
		String q1 = "SELECT CustomerFirstName, CustomerLastName FROM customer WHERE CustomerID=?;";

		try {

			connect_to_db();
			PreparedStatement s1 = conn.prepareStatement(q1);
			s1.setInt(1, CustID);

			ResultSet r1 = s1.executeQuery();

			if (!r1.next()) {
				return "Customer not found";
			}

			return r1.getString("CustomerFirstName") + " " + r1.getString("CustomerLastName");

		} catch (Exception e) {
			System.out.println("Error in getCustomerName");
			System.out.println("Exception type: " + e.getClass().getName());
			return "Customer not found";
		} finally {
			conn.close();
		}

	}

	/*
	 * The next 3 private methods help get the individual components of a SQL
	 * datetime object.
	 * You're welcome to keep them or remove them.
	 */
	private static int getYear(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(0, 4));
	}

	private static int getMonth(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(5, 7));
	}

	private static int getDay(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(8, 10));
	}

	public static boolean checkDate(int year, int month, int day, String dateOfOrder) {

		int orderYear = getYear(dateOfOrder);
		int orderMonth = getMonth(dateOfOrder);
		int orderDay = getDay(dateOfOrder);

		if (orderYear > year) {
			return true;
		} else if (orderYear < year) {
			return false;
		}

		if (orderMonth > month) {
			return true;
		} else if (orderMonth < month) {
			return false;
		}
		return orderDay >= day;
	}

}