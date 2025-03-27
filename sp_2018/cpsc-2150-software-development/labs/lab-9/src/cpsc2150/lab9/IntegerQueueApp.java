//  Dylan Mumm

package cpsc2150.lab9;

import java.util.Scanner;


public class IntegerQueueApp {

    private static Scanner in;

    public static void main(String[] args) {

        in = new Scanner(System.in);
        System.out.println("Enter 1 for array implementation or 2 for List implementation");                 int answer = in.nextInt();
        IQueue q;
        if(answer == 1) {
            q = new ArrayQueueImp();
        }
        else {
            q = new ListQueueImp();
        }

        displayMenu();
        answer = in.nextInt();
        while(answer != 8) {
            if(answer == 1)
            {
                addToQueue(q);
            }
            else if(answer == 2)
            {
                getNext(q);
            }
            else if(answer == 3)
            {
                peekInQueue(q);
            }
            else if(answer == 4)
            {
                peekAtEnd(q);
            }
            else if(answer == 5)
            {
                insertInQueue(q);
            }
            else if(answer == 6)
            {
                getFromQueue(q);
            }
            else if(answer == 7)
            {
                removeFromQueue(q);
            }
            else {
                System.out.println("Not a valid option!");
            }
            System.out.println("Queue is: ");
            System.out.println(q.toString());
            System.out.println(" ");
            displayMenu();
            answer = in.nextInt();
        }



    }

    private static void displayMenu(){
        System.out.println("Select an option: ");
        System.out.println("1. Add to the Queue");
        System.out.println("2. Get next number from the Queue");
        System.out.println("3. Peek at the front of the Queue");
        System.out.println("4. Peek at the end of the Queue");
        System.out.println("5. Insert in the Queue");
        System.out.println("6. Get a position in the Queue");
        System.out.println("7. Remove from a position in the Queue");
        System.out.println("8. Quit");

    }

    private static void addToQueue(IQueue q) {
        System.out.println("What number to add to the Queue?");
        int answer = in.nextInt();
        q.add(answer);
    }

    private static void getNext(IQueue q) {
        Integer result = (Integer) q.pop();
        if(result == null)
            System.out.println("Queue is empty!");
        else
            System.out.println("Next number is " + result);
    }

    private static void peekInQueue(IQueue q) {
        Integer result = (Integer) q.peek();
        if(result == null)
            System.out.println("Queue is empty!");
        else
            System.out.println("Peek: " + q.peek());
    }

    private static void peekAtEnd(IQueue q) {
        Integer result = (Integer) q.peek();
        if(result == null)
            System.out.println("Queue is empty!");
        else
            System.out.println("Peek: " + q.endOfQueue());
    }

    private static void insertInQueue(IQueue q) {
        if(q.peek() == null){
            System.out.println("Queue is empty!");
            return;
        }

        int position = -1, number;
        System.out.println("What number to add to the Queue?");
        number = in.nextInt();

        while (position < 0 || position > q.size()) {
            System.out.println("What position to insert in?");
            position = in.nextInt();
             if (position > 0 && position <= q.size())
                q.insert(number, position);
            else
                System.out.println("Not a valid position in the Queue!");
        }
    }

    private static void getFromQueue(IQueue q) {
        if(q.peek() == null){
            System.out.println("Queue is empty!");
            return;
        }

        int position = -1;
        while (position < 0 || position > q.size()) {
            System.out.println("What position to get from the Queue?");
            position = in.nextInt();
            if (position > 0 && position <= q.size())
                q.get(position);
            else
                System.out.println("Not a valid position in the Queue!");
        }
    }

    private static void removeFromQueue(IQueue q) {
        if(q.peek() == null){
            System.out.println("Queue is empty!");
            return;
        }

        int position = -1;
        while (position < 0 || position > q.size()) {
            System.out.println("What position to remove from the Queue?");
            position = in.nextInt();
            if (position > 0 && position <= q.size())
                q.remove(position);
            else
                System.out.println("Not a valid position in the Queue!");
        }
    }




}
