// Dylan Mumm

package cpsc2150.lab7;

import java.util.Scanner;


public class QueueApp {

    public static void main(String [] args)
    {
        IntegerQueueI q;

        /* You will add in code here to ask the user whether they
           want an array implementation or a list implementation.
           Then use their answer to initialize q appropriately */

        Scanner sc = new Scanner(System.in);
        System.out.println("Would you like to use an array or list implementation? Reply \"A\" or \"L\".");
        char c = sc.next().charAt(0);
        if(c == 'A' || c == 'a') {
            q = new ArrayQueueImp();
        } else {
            q = new ListQueueImp();
        }


        Integer x = 42;
        q.add(x);
        x = 17;
        q.add(x);
        x = 37;
        q.add(x);
        x = 36;
        q.add(x);
        x = 12;
        q.add(x);

        //Add the code to print the queue. After the code is finished, the queue should contain all its values in order
        int size = q.size();
        for(int i = 0; i < size; i++) {
            Integer result = q.pop();
            System.out.println("#" + i + ": ");
            System.out.println(result);
            q.add(result);
        }


    }
}
