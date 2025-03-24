package cpsc4620;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.sql.*; //TODO: debug

/*
 * This file is where the front end magic happens.
 * You will have to write the methods for each of the menu options. *
 * This file should not need to access your DB at all, it should make calls to the DBNinja that will do all the connections.
 * You can add and remove methods as you see necessary. But you MUST have all of the menu methods (including exit!)
 * Simply removing menu methods because you don't know how to implement it will result in a major error penalty (akin to your program crashing)
 * Speaking of crashing. Your program shouldn't do it. Use exceptions, or if statements, or whatever it is you need to do to keep your program from breaking.
 */

public class Menu {

    public static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws SQLException, IOException {

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // present a menu of options and take their selection
        System.out.println("Welcome to Pizzas-R-Us!");
        PrintMenu();
        String option = reader.readLine();
        int menu_option = intResponseCheck(option);
        while (menu_option != 9) {
            switch (menu_option) {
                case 1:// enter order
                    EnterOrder();
                    break;
                case 2:// view customers
                    viewCustomers();
                    break;
                case 3:// enter customer
                    EnterCustomer();
                    break;
                case 4:// view order
                       // open/closed/date
                    ViewOrders();
                    break;
                case 5:// mark order as complete
                    MarkOrderAsComplete();
                    break;
                case 6:// view inventory levels
                    ViewInventoryLevels();
                    break;
                case 7:// add to inventory
                    AddInventory();
                    break;
                case 8:// view reports
                    PrintReports();
                    break;
            }
            PrintMenu();
            option = reader.readLine();
            menu_option = intResponseCheck(option);
        }

    }

    public static boolean isDateInputValud(String value) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        dateFormat.setLenient(false);
        try {
            dateFormat.parse(value);
            return true;
        } catch (ParseException e) {
            return false;
        }
    }

    private static String getOrderTypeChoice() throws IOException {
        return switch (intResponseCheck(reader.readLine())) {
            case 1 -> DBNinja.DINE_IN;
            case 2 -> DBNinja.PICKUP;
            case 3 -> DBNinja.DELIVERY;
            default -> {
                System.out.println("Invalid choice");
                yield null;
            }
        };
    }


    /*
    * Ask if the order is delivery, pickup, or dinein
     * if dine in....ask for table number
     * if pickup...
     * if delivery...
     *
     * Then, build the pizza(s) for the order (there's a method for this) until
     * there are no more pizzas for the order
     * Add the pizzas to the order
     * Apply order discounts as needed (including to the DB)
     * Return to menu
     */
    public static void EnterOrder() throws SQLException, IOException {

        Order o = createInitialOrder();

        setOrderType(o);
        o = createSpecificOrderType(o);

        if (o instanceof DeliveryOrder || o instanceof PickupOrder) {
            handleCustomerForOrder(o);
        }

        if (o instanceof DeliveryOrder) {
            setDeliveryAddress((DeliveryOrder) o);
        }

        if (o instanceof PickupOrder) {
            System.out.println("We can't wait to see you - the pizza will be ready soon");
        }

        askForPizzas(o);
        askForDiscounts(o);

        DBNinja.addOrder(o);

        System.out.println("Finished adding order...Returning to menu...");
    }

    private static Order createInitialOrder() throws SQLException, IOException {
        int id = DBNinja.getLastOrder().getOrderID() + 1;
        return new Order(id, 0, null, null, 0.0, 0.0, 0);
    }

    private static void setOrderType(Order o) throws IOException {
        while (o.getOrderType() == null) {
            displayOrderTypeOptions();
            String typeChoice = getOrderTypeChoice();
            o.setOrderType(typeChoice);
        }
    }

    private static void displayOrderTypeOptions() {
        System.out.println("Is this order for:");
        System.out.println("1.) Dine-in");
        System.out.println("2.) Pick-up");
        System.out.println("3.) Delivery");
        System.out.println("Enter the number of your choice:");
    }

    private static Order createSpecificOrderType(Order o) throws IOException {
        return switch (o.getOrderType()) {
            case DBNinja.DINE_IN -> {
                System.out.println("What is the table number for this order?");
                yield new DineinOrder(o.getOrderID(), o.getCustID(), o.getDate(), o.getCustPrice(),
                        o.getBusPrice(), o.getIsComplete(), intResponseCheck(reader.readLine()));
            }
            case DBNinja.PICKUP -> {
                yield new PickupOrder(o.getOrderID(), o.getCustID(), o.getDate(), o.getCustPrice(),
                        o.getBusPrice(), o.getIsComplete(), o.getIsComplete());
            }
            case DBNinja.DELIVERY -> {
                yield new DeliveryOrder(o.getOrderID(), o.getCustID(), o.getDate(), o.getCustPrice(),
                        o.getBusPrice(), o.getIsComplete(), null);
            }
            default -> o;
        };
    }

    private static void handleCustomerForOrder(Order o) throws IOException, SQLException {
        int existingChoice = Integer.MIN_VALUE;
        while (existingChoice == Integer.MIN_VALUE) {
            System.out.println("Is this order for an existing customer? Answer y/n: ");

            existingChoice = switch (reader.readLine()) {
                case "n" -> {
                    EnterCustomer();
                    yield 0;
                }
                case "y" -> {
                    handleExistingCustomer(o);
                    yield 1;
                }
                default -> Integer.MIN_VALUE;
            };
        }
    }

    private static void handleExistingCustomer(Order o) throws IOException, SQLException {
        System.out.println("Here's a list of the current customers: ");
        viewCustomers();
        System.out.println("Which customer is this order for? Enter ID Number:");
        o.setCustID(intResponseCheck(reader.readLine()));
    }

    private static void setDeliveryAddress(DeliveryOrder o) throws IOException {
        String[] prompts = {
                "House/Apt Number (i.e., 111)",
                "Street (i.e., Smile Street)",
                "City (i.e., Greenville)",
                "State (i.e., SC)",
                "Zip Code (i.e., 20605)"
        };
        String[] addressParts = new String[prompts.length];
        for (int i = 0; i < prompts.length; i++) {
            System.out.println("What is the " + prompts[i] + " for this order?");
            addressParts[i] = reader.readLine();
        }
        o.setAddress(String.join(" ", addressParts));
    }

    private static void askForPizzas(Order o) throws IOException, SQLException {
        int stop = 0;
        while (stop != -1) {
            System.out.println("Let's build a pizza!");

            o.addPizza(buildPizza(o.getOrderID()));

            System.out.print("Enter -1 to stop adding pizzas...");
            System.out.println("Enter anything else to continue adding pizzas to the order.");
            stop = intResponseCheck(reader.readLine());
        }
    }

    private static void askForDiscounts(Order o) throws IOException, SQLException {
        int existingChoice = Integer.MIN_VALUE;
        while (existingChoice == Integer.MIN_VALUE) {
            System.out.println("Do you want to add discounts to this order? Enter y/n?");
            existingChoice = switch (reader.readLine()) {
                case "n" -> 0;
                case "y" -> {
                    requestDiscounts(o);
                    yield 1;
                }
                default -> Integer.MIN_VALUE;
            };
        }
    }

    private static void requestDiscounts(Order o) throws IOException, SQLException {
        ArrayList<Discount> discountList = DBNinja.getDiscountList();
        while (true) {

            for (Discount d : discountList) {
                System.out.println(d.toString());
            }

            System.out.print("Which Order Discount do you want to add?");
            System.out.println("Enter the DiscountID. Enter -1 to stop adding Discounts: ");
            int discountID = intResponseCheck(reader.readLine());
            if (discountID == -1) {
                break;
            }
            Discount d = discountList.get(--discountID); // decrement to get the correct index
            o.addDiscount(d); // decrement to get the correct index
        }
    }

    /*
     * Simply print out all of the customers from the database.
     */
    public static void viewCustomers() throws SQLException, IOException {
        ArrayList<Customer> list = DBNinja.getCustomerList();
        for (Customer cust : list) {
            System.out.println(
                    cust.getCustID() + ":\t" + cust.getFName() + "\t" + cust.getLName() + "\t" + cust.getPhone());
        }

    }

    // Enter a new customer in the database
    /*
     * Ask for the name of the customer:
     * = First Name <space> Last Name
     *
     * Ask for the phone number.
     * (##########) (No dash/space)
     *
     * Once you get the name and phone number, add it to the DB
     */
    public static void EnterCustomer() throws SQLException, IOException {

        System.out.println("What is this customer's name (first <space> last)");
        String[] nameSplit = reader.readLine().split(" ");
        System.out.println("What is this customer's phone number (##########) (No dash/space)");
        DBNinja.addCustomer(new Customer(0, nameSplit[0], nameSplit[1], reader.readLine()));

    }

    /*
     * This method allows the user to select between three different views of the
     * Order history:
     * The program must display:
     * a. all open orders
     * b. all completed orders
     * c. all the orders (open and completed) since a specific date (inclusive)
     *
     * After displaying the list of orders (in a condensed format) must allow the
     * user to select a specific order for viewing its details.
     * The details include the full order type information, the pizza information
     * (including pizza discounts), and the order discounts.
     *
     */
    // View any orders that are not marked as completed
    public static void ViewOrders() throws SQLException, IOException {
        DBConnector.make_connection();
        // DBNinja.getLastOrder().toSimplePrint(); // TODO: debug

        // User Input Prompts...
        System.out.println(
                "Would you like to:\n(a) display all orders [open or closed]\n(b) display all open orders\n(c) display all closed orders\n(d) display orders from a specific date");
        String line = reader.readLine().toLowerCase();

        ArrayList<Order> list;
        if (line.equals("a")) {

            list = DBNinja.getOrders(false);

        } else if (line.equals("b")) {

            list = DBNinja.getOrders(true);

        } else if (line.equals("c")) {

            list = DBNinja.getCompleteOrders();

        } else if (line.equals("d")) {

            while (true) { // TODO: check autograder to see error checking

                System.out.println("What is the date you want to restrict by? (FORMAT= YYYY-MM-DD)");
                String date_response = reader.readLine();
                if (isDateInputValud(date_response) == true) {
                    list = DBNinja.getOrdersByDate(date_response);
                    break;
                }
                // System.out.println("I don't understand that input, Returning to menu.");
                System.out.println("I don't understand that input.");
            }

        } else {
            System.out.println("I don't understand that input, Returning to menu.");
            return;
        }

        if (list == null || list.isEmpty()) {

            System.out.println("No orders to display, returning to menu.");
            return;

        } else {

            System.out.println("Order ID  Cust ID, Order Type   Date  Is Complete");
            for (Order o : list) {
                System.out.print(o.getOrderID() + ":\t" + o.getCustID() + "\t");
                System.out.print(o.getOrderType() + "\t" + o.getDate() + "\t");
                System.out.println(o.getIsComplete());
            }

            System.out.println("Which order would you like to see in detail? Enter the number (-1 to exit): ");
            int id = intResponseCheck(reader.readLine());
            if (id == -1) {
                return;
            }

            int index = -1;

            for (int i = 0; i < list.size(); i++) {
                if (list.get(i).getOrderID() == id) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                System.out.println("I don't understand that input, Returning to menu.");
                return;
            } else {
                System.out.println("OrderID\tCustID\tOrder Type\tDate\t \t \tCust Price   Bus Price   is Complete");
                System.out.println(list.get(index).getOrderID() + ":\t" + list.get(index).getCustID() + "\t"
                        + list.get(index).getOrderType() + "\t"
                        + list.get(index).getDate() + "\t\t" + list.get(index).getCustPrice() + "\t"
                        + list.get(index).getBusPrice() + "\t" +
                        list.get(index).getIsComplete());
            }

            // Need to get this function working

        }

    }

    // When an order is completed, we need to make sure it is marked as complete
    public static void MarkOrderAsComplete() throws SQLException, IOException {
        /*
         * All orders that are created through java (part 3, not the orders from part 2)
         * should start as incomplete
         *
         * When this method is called, you should print all of the "opoen" orders marked
         * and allow the user to choose which of the incomplete orders they wish to mark
         * as complete
         *
         */

        // User Input Prompts...
        ArrayList<Order> list;
        list = DBNinja.getOrders(true);
        if (list.isEmpty()) {
            System.out.println("There are no open orders currently... returning to menu...");
        }

        System.out.println("Which order would you like mark as complete? Enter the OrderID: ");
        String choice = reader.readLine();
        int num = intResponseCheck(choice);
        boolean correct = false;
        for (Order o : list) {
            if (num == o.getOrderID()) {
                correct = true;
            }
        }
        if (correct) {
            DBNinja.completeOrder(list.get(num));
        } else {
            System.out.println("Incorrect entry, not an option");
        }

    }

    /*
     * Print the inventory. Display the topping ID, name, and current inventory
     */
    public static void ViewInventoryLevels() throws SQLException, IOException {
        DBNinja.printInventory();
    }

    /*
     * This should print the current inventory and then ask the user which topping
     * (by ID) they want to add more to and how much to add
     */
    public static void AddInventory() throws SQLException, IOException {

        // User Input Prompts...
        ArrayList<Topping> list = DBNinja.getToppingList();
        DBNinja.printInventory();
        System.out.println("Which topping do you want to add inventory to? Enter the number: ");
        String choice1 = reader.readLine();
        int topID = intResponseCheck(choice1);
        if (topID < 1 || topID > list.size()) {
            System.out.println("Incorrect entry, not an option");
            return;
        }
        System.out.println("How many units would you like to add? ");
        String choice2 = reader.readLine();
        int amount = intResponseCheck(choice2);
        DBNinja.addToInventory(list.get(topID - 1), amount);

    }

    // A method that builds a pizza. Used in our add new order method
    public static Pizza buildPizza(int orderID) throws SQLException, IOException {

        /*
         * - This is a helper method for first menu option.
         * - It should ask which size pizza the user wants and the crustType.
         * - Once the pizza is created, it should be added to the DB.
         * - We also need to add toppings to the pizza. (Which means we not only need to
         * add toppings here, but also our bridge table)
         * - We then need to add pizza discounts (again, to here and to the database)
         * - Once the discounts are added, we can return the pizza
         */

        String size_choice = null;
        String crust_choice = null;
        String extra_choice = null;
        String[] sizes = { DBNinja.SIZE_S, DBNinja.SIZE_M, DBNinja.SIZE_L, DBNinja.SIZE_XL };
        String[] crusts = { DBNinja.CRUST_THIN, DBNinja.CRUST_ORIG, DBNinja.CRUST_PAN, DBNinja.CRUST_GF };
        int topping_choice = Integer.MIN_VALUE;

        StringBuilder size_menu = new StringBuilder("What size is the pizza?\n");
        for (int i = 0; i < sizes.length; i++) {
            size_menu.append(String.format("%d. %s\n", i + 1, sizes[i]));
        }
        size_menu.append("Enter the corresponding number: ");

        while (size_choice == null) {
            System.out.print(size_menu.toString());
            size_choice = switch (intResponseCheck(reader.readLine())) {
                case 1 -> DBNinja.SIZE_S;
                case 2 -> DBNinja.SIZE_M;
                case 3 -> DBNinja.SIZE_L;
                case 4 -> DBNinja.SIZE_XL;
                default -> {
                    System.out.println("Invalid choice");
                    yield null;
                }
            };
        }

        StringBuilder crust_menu = new StringBuilder("What crust for this pizza?\n");
        for (int i = 0; i < crusts.length; i++) {
            crust_menu.append(String.format("%d. %s\n", i + 1, crusts[i]));
        }
        crust_menu.append("Enter the corresponding number: ");

        while (crust_choice == null) {
            System.out.print(crust_menu.toString());
            crust_choice = switch (intResponseCheck(reader.readLine())) {
                case 1 -> DBNinja.CRUST_THIN;
                case 2 -> DBNinja.CRUST_ORIG;
                case 3 -> DBNinja.CRUST_PAN;
                case 4 -> DBNinja.CRUST_GF;
                default -> {
                    System.out.println("Invalid choice");
                    yield null;
                }
            };
        }

        Pizza new_pizza = DBNinja.retrieveBasePizza(size_choice, crust_choice);

        ArrayList<Topping> topping_inventory = DBNinja.getToppingList();
        while (topping_choice == Integer.MIN_VALUE) {

            System.out.println("Available Toppings:");
            DBNinja.printInventory();
            System.out.println("Which topping do you want to add? Enter the TopID. Enter -1 to stop adding toppings: ");

            topping_choice = intResponseCheck(reader.readLine());
            if (topping_choice == -1) {
                break;
            }

            if (topping_choice <= 0 || topping_inventory.size() < topping_choice) {
                System.out.println("I don't understand that input...");
                continue;
            }

            Topping t = topping_inventory.get(--topping_choice); // decrement to get the correct index
            System.out.println(t.toString()); // TODO: debug
            if (t.getCurINVT() <= t.getMinINVT()) {
                System.out.println("We don't have enough of that topping to add it...");
                continue;
            }

            while (extra_choice == null) {
                System.out.println("Do you want to add extra of this topping? Enter y/n?");
                if (t.getCurINVT() <= t.getMinINVT() - 1) {
                    System.out.println("We don't have enough of that topping to add it...");
                    break;
                }
                extra_choice = switch (reader.readLine()) {
                    case "n" -> "n";
                    case "y" -> {
                        new_pizza.modifyDoubledArray(topping_choice, true);
                        yield "y";
                    }
                    default -> {
                        System.out.println("I don't understand that input...");
                        yield null;
                    }
                };
            }
            System.out.println(t.toString());
            System.out.println(new_pizza.getIsDoubleArray()[topping_choice]);
            new_pizza.addToppings(t, new_pizza.getIsDoubleArray()[topping_choice]);
        }
        System.out.println(new_pizza.getToppings().toString()); // TODO: debug
        System.out.println(new_pizza.getIsDoubleArray().toString()); // TODO: debug

        System.out.println("Do you want to add discounts to this Pizza? Enter y/n?");

        String choice = reader.readLine();
        ArrayList<Discount> discountList = DBNinja.getDiscountList();

        while (choice.equals("y")) {
            System.out.println(
                    "Which Pizza Discount do you want to add? Enter the DiscountID. Enter -1 to stop adding Discounts: ");
            for (Discount d : discountList) {
                System.out.println(d.toString());
            }
            String discount = reader.readLine();
            int discountID = intResponseCheck(discount);
            int index = -1;

            for (int i = 0; i < discountList.size(); i++) {
                if (discountList.get(i).getDiscountID() == discountID) {
                    index = i;
                    break;
                }
            }
            // ret.addDiscounts(discountList.get(index));
            System.out.println("Do you want to add more discounts to this Pizza? Enter y/n?");
            choice = reader.readLine();
        }

        return new_pizza;

    }

    public static void PrintReports() throws SQLException, NumberFormatException, IOException {
        /*
         * This method asks the use which report they want to see and calls the DBNinja
         * method to print the appropriate report.
         *
         */

        // User Input Prompts...
        System.out.println(
                "Which report do you wish to print? Enter\n(a) ToppingPopularity\n(b) ProfitByPizza\n(c) ProfitByOrderType:");
        String choice = reader.readLine();
        if (choice.equals("a")) {
            DBNinja.printToppingPopReport();
        } else if (choice.equals("b")) {
            DBNinja.printProfitByPizzaReport();
        } else if (choice.equals("c")) {
            DBNinja.printProfitByOrderType();
        } else {
            System.out.println("I don't understand that input... returning to menu...");
            return;
        }

    }

    // Prompt - NO CODE SHOULD TAKE PLACE BELOW THIS LINE
    // DO NOT EDIT ANYTHING BELOW HERE, THIS IS NEEDED TESTING.
    // IF YOU EDIT SOMETHING BELOW, IT BREAKS THE AUTOGRADER WHICH MEANS YOUR GRADE
    // WILL BE A 0 (zero)!!

    public static void PrintMenu() {

        System.out.println("\n\nPlease enter a menu option:");
        System.out.println("1. Enter a new order");
        System.out.println("2. View Customers ");
        System.out.println("3. Enter a new Customer ");
        System.out.println("4. View orders");
        System.out.println("5. Mark an order as completed");
        System.out.println("6. View Inventory Levels");
        System.out.println("7. Add Inventory");
        System.out.println("8. View Reports");
        System.out.println("9. Exit\n\n");
        System.out.println("Enter your option: ");
    }

    public static Integer intResponseCheck(String str) {
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException e) {
            return Integer.MIN_VALUE;
        }
    }

    /*
     * autograder controls....do not modiify!
     */

    public final static String autograder_seed = "6f1b7ea9aac470402d48f7916ea6a010";

    private static void autograder_compilation_check() {

        try {
            Order o = null;
            Pizza p = null;
            Topping t = null;
            Discount d = null;
            Customer c = null;
            ArrayList<Order> alo = null;
            ArrayList<Discount> ald = null;
            ArrayList<Customer> alc = null;
            ArrayList<Topping> alt = null;
            double v = 0.0;
            String s = "";

            DBNinja.addOrder(o);
            DBNinja.addPizza(p);
            DBNinja.useTopping(p, t, false);
            DBNinja.usePizzaDiscount(p, d);
            DBNinja.useOrderDiscount(o, d);
            DBNinja.addCustomer(c);
            DBNinja.completeOrder(o);
            alo = DBNinja.getOrders(false);
            o = DBNinja.getLastOrder();
            alo = DBNinja.getOrdersByDate("01/01/1999");
            ald = DBNinja.getDiscountList();
            d = DBNinja.findDiscountByName("Discount");
            alc = DBNinja.getCustomerList();
            c = DBNinja.findCustomerByPhone("0000000000");
            alt = DBNinja.getToppingList();
            t = DBNinja.findToppingByName("Topping");
            DBNinja.addToInventory(t, 1000.0);
            v = DBNinja.getBaseCustPrice("size", "crust");
            v = DBNinja.getBaseBusPrice("size", "crust");
            DBNinja.printInventory();
            DBNinja.printToppingPopReport();
            DBNinja.printProfitByPizzaReport();
            DBNinja.printProfitByOrderType();
            s = DBNinja.getCustomerName(0);
        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }

}
