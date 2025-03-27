//  Dylan Mumm
package cpsc2150.lab7;


import java.util.*;

/**
 *  Correspondence: this = myQ. The front of myQ is the front of the Queue
 *  Correspondence: size = myQ.size();
 *
 *  @invariant: 0 <= depth <= MAX_DEPTH
 */

public class ListQueueImp implements IntegerQueueI {

        private List<Integer> myQ;

        public ListQueueImp() {

            this.myQ = new ArrayList<Integer>();

        }

        public void add(Integer x) {
            myQ.add(x);
        }

        public Integer pop() {
            Integer result = myQ.get(0);
            myQ.remove(0);
            return result;
        }

        public int size() {
            return myQ.size();
        }

        @Override
        public String toString() {

            StringBuilder str =  new StringBuilder("");

            for (int i = 0; i < size(); i++) {
                str.append(myQ.get(i));
                str.append("\n");
            }

            return str.toString();

    }

    }

