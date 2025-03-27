//  Dylan Mumm
package cpsc2150.lab9;


/**
 *  Correspondence: this = myQ[0...depth-1], myQ[0] is the front of the Queue
 *  Correspondence: size = depth
 *
 *  @invariant: 0 <= depth <= MAX_DEPTH
 *
 */


public class ArrayQueueImp <T> implements IQueue <T> {

        private T[] myQ;
        private int depth;


        public ArrayQueueImp() {

            depth = 0;
            myQ = (T[]) new Object[MAX_DEPTH];

        }

        public void add(T x) {
            for(int i = 0; i <= depth; i++)
                if(myQ[i] == null) {
                    myQ[i] = x;
                    break;
                }
            depth++;

        }

        public T pop() {
            T result = myQ[0];
            for(int i = 0; i < depth; i++) {
                if (myQ[i + 1] != null) {
                    myQ[i] = myQ[i + 1];

                }
                else {
                    myQ[i] = null;
                    depth--;
                }
            }
            return result;
        }

        public int size() {
            return depth;
        }

    @Override
    public String toString() {

        StringBuilder str =  new StringBuilder("");

        for (int i = 0; i < size(); i++) {
            str.append(myQ[i]);
            str.append("\n");
        }

        return str.toString();

    }


    }


