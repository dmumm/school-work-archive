//  Dylan Mumm

package cpsc2150.lab7;

/**
 * A queue containing integers.
 * A queue is a data structure where the first item added to the structure
 * is the first item removed from the structure
 *
 * This queue is bounded by MAX_DEPTH
 *
 *  Initialization ensures the queue is empty
 *  Defines: size:Z
 *  Constraints: 0 <= size <= MAX_DEPTH
 */

public interface IntegerQueueI {

    int MAX_DEPTH = 100;

    /**
     * Adds x to the end of the Queue
     *
     * @param x     Integer to be added to end of queue
     * @requires    x be an integer
     * @ensures     x is added to end of queue
     *
     */
     void add(Integer x);

    /**
     * removes and returns the Integer at the front of the queue
     *
     * @ensures integer at front of queue is returned and removed
     * @returns integer at front of queue
     *
     */
     Integer pop();

    /**
     * returns the number of Integers in the Queue
     *
     * @ensures size() = number of integers in the queue
     * @returns number of integers in the queue
     *
     */
     int size();

     default Integer peek() {
         if(size() > 0)
            return Character.getNumericValue(toString().charAt(0));
         else
             return null;
     }

     default Integer endOfQueue() {
         if(size() > 0)
             return Character.getNumericValue(toString().charAt(size()));
         else
             return null;
     }

     default void insert(Integer x, int pos) {

         String[] lines = toString().split(System.getProperty("line.separator"));
         for(int i = 0; i < size(); i++) {
             pop();
         }

         for(int i = 0; i < pos; i++) {
             add(Integer.parseInt(lines[i]));
         }

         add(x);

         for(int i = pos; i < size(); i++) {
             add(Integer.parseInt(lines[i]));
         }


     }

     default Integer remove(int pos) {

         String[] lines = toString().split(System.getProperty("line.separator"));
         int result = -1;

         for(int i = 0; i < size(); i++) {
             if(i == pos)
                 result = pop();
             else
                 pop();
         }

         for(int i = 0; i < pos; i++) {
             add(Integer.parseInt(lines[i]));
         }

         for(int i = pos+1; i < size(); i++) {
             add(Integer.parseInt(lines[i]));
         }

         return result;

     }

    default Integer get(int pos) {

        String[] lines = toString().split(System.getProperty("line.separator"));
        int result = -1;

        for(int i = 1; i < size()+1; i++) {
            if(i == pos)
                result = pop();
            else
                pop();
        }

        for(int i = 0; i < pos; i++) {
            add(Integer.parseInt(lines[i]));
        }

        for(int i = pos+1; i < size()-1; i++) {
            add(Integer.parseInt(lines[i]));
        }

        return result;

    }

}
