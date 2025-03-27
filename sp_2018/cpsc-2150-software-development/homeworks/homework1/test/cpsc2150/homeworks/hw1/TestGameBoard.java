// Dylan Mumm, 2150
// HW2
// March 11th

package cpsc2150.homeworks.hw1;

import org.junit.Test;
import static org.junit.Assert.*;

public class TestGameBoard {

    private final int ROWS = 8;
    private final int COLS = 8;

    /* Testing checkSpace() */

    @Test
    public void testCheckSpace_x0_y0_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(0, 0, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y1_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(0, 1, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y2_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(0, 2, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y3_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(0, 3, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y4_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(0, 4, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y5_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(0, 5, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y6_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(0, 6, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y7_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(0, 7, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y0_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(1, 0, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y1_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(1, 1, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y2_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(1, 2, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y3_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(1, 3, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y4_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(1, 4, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y5_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(1, 5, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y6_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(1, 6, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y7_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(1, 7, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y0_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(2, 0, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y1_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(2, 1, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y2_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(2, 2, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y3_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(2, 3, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y4_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(2, 4, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y5_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(2, 5, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y6_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(2, 6, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y7_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(2, 7, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y0_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(3, 0, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y1_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(3, 1, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y2_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(3, 2, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y3_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(3, 3, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y4_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(3, 4, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y5_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(3, 5, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y6_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(3, 6, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y7_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(3, 7, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y0_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(4, 0, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y1_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(4, 1, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y2_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(4, 2, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y3_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(4, 3, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y4_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(4, 4, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y5_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(4, 5, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y6_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(4, 6, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y7_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(4, 7, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y0_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(5, 0, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y1_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(5, 1, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y2_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(5, 2, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y3_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(5, 3, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y4_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(5, 4, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y5_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(5, 5, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y6_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(5, 6, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y7_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(5, 7, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y0_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(6, 0, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y1_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(6, 1, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y2_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(6, 2, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y3_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(6, 3, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y4_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(6, 4, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y5_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(6, 5, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y6_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(6, 6, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y7_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(6, 7, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y0_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(7, 0, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y1_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(7, 1, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y2_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(7, 2, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y3_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(7, 3, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y4_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(7, 4, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y5_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(7, 5, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y6_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(7, 6, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y7_F() {

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(7, 7, 'X');
        b.placeMarker(p);

        boolean foundResult = b.checkSpace(p);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y0_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(1, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y1_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(0, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y2_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(0, 2, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y3_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(0, 3, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y4_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(0, 4, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y5_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(0, 5, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y6_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(0, 6, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x0_y7_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(0, 7, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y0_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(1, 0, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y1_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(1, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y2_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(1, 2, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y3_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(1, 3, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y4_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(1, 4, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y5_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(1, 5, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y6_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(1, 6, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x1_y7_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(1, 7, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y0_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(2, 0, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y1_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(2, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y2_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(2, 2, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y3_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(2, 3, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y4_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(2, 4, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y5_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(2, 5, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y6_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(2, 6, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x2_y7_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(2, 7, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y0_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(3, 0, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y1_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(3, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y2_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(3, 2, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y3_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(3, 3, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y4_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(3, 4, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y5_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(3, 5, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y6_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(3, 6, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x3_y7_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(3, 7, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y0_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(4, 0, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y1_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(4, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y2_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(4, 2, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y3_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(4, 3, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y4_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(4, 4, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y5_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(4, 5, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y6_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(4, 6, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x4_y7_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(4, 7, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y0_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(5, 0, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y1_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(5, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y2_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(5, 2, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y3_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(5, 3, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y4_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(5, 4, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y5_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(5, 5, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y6_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(5, 6, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x5_y7_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(5, 7, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y0_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(6, 0, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y1_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(6, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y2_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(6, 2, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y3_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(6, 3, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y4_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(6, 4, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y5_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(6, 5, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y6_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(6, 6, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x6_y7_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(6, 7, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y0_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(7, 0, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y1_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(7, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y2_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(7, 2, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y3_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(7, 3, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y4_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(7, 4, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y5_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(7, 5, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y6_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(7, 6, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckSpace_x7_y7_T() {

        GameBoard b = new GameBoard();
        BoardPosition p1 = new BoardPosition(7, 7, 'X');
        BoardPosition p2 = new BoardPosition(0, 0, 'X');
        b.placeMarker(p2);

        boolean foundResult = b.checkSpace(p1);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    /* Testing placeMarker() */

    @Test
    public void testPlaceMarker_x0_x0() {

        int x = 0, y = 0;
        char l = 'X';

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(x, y, l);
        b.placeMarker(p);

        char[][] expectedBoard = new char[ROWS][COLS];
        for(int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                expectedBoard[i][j] = ' ';
            }
        }
        expectedBoard[x][y] = l;

        String foundString = b.toString();
        String expectedString = arrayToString(expectedBoard);

        assertEquals(foundString, expectedString);

    }

    @Test
    public void testPlaceMarker_x7_y0() {

        int x = 7, y = 0;
        char l = 'X';

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(x, y, l);
        b.placeMarker(p);

        char[][] expectedBoard = new char[ROWS][COLS];
        for(int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                expectedBoard[i][j] = ' ';
            }
        }
        expectedBoard[x][y] = l;

        String foundString = b.toString();
        String expectedString = arrayToString(expectedBoard);

        assertEquals(foundString, expectedString);

    }

    @Test
    public void testPlaceMarker_x0_y7() {

        int x = 0, y = 7;
        char l = 'X';

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(x, y, l);
        b.placeMarker(p);

        char[][] expectedBoard = new char[ROWS][COLS];
        for(int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                expectedBoard[i][j] = ' ';
            }
        }
        expectedBoard[x][y] = l;

        String foundString = b.toString();
        String expectedString = arrayToString(expectedBoard);

        assertEquals(foundString, expectedString);

    }

    @Test
    public void testPlaceMarker_x7_y7() {

        int x = 7, y = 7;
        char l = 'X';

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(x, y, l);
        b.placeMarker(p);

        char[][] expectedBoard = new char[ROWS][COLS];
        for(int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                expectedBoard[i][j] = ' ';
            }
        }
        expectedBoard[x][y] = l;

        String foundString = b.toString();
        String expectedString = arrayToString(expectedBoard);

        assertEquals(foundString, expectedString);

    }

    @Test
    public void testPlaceMarker_x5_y2() {

        int x = 5, y = 2;
        char l = 'X';

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(x, y, l);
        b.placeMarker(p);

        char[][] expectedBoard = new char[ROWS][COLS];
        for(int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                expectedBoard[i][j] = ' ';
            }
        }
        expectedBoard[x][y] = l;

        String foundString = b.toString();
        String expectedString = arrayToString(expectedBoard);

        assertEquals(foundString, expectedString);

    }

    @Test
    public void testPlaceMarker_x2_y5() {

        int x = 2, y = 5;
        char l = 'X';

        GameBoard b = new GameBoard();
        BoardPosition p = new BoardPosition(x, y, l);
        b.placeMarker(p);

        char[][] expectedBoard = new char[ROWS][COLS];
        for(int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                expectedBoard[i][j] = ' ';
            }
        }
        expectedBoard[x][y] = l;

        String foundString = b.toString();
        String expectedString = arrayToString(expectedBoard);

        assertEquals(foundString, expectedString);

    }

    /* Testing checkForWinner() */

    @Test
    public void testCheckForWinner_H_W_V_L() {

        GameBoard b = new GameBoard();

        BoardPosition p0 = new BoardPosition(0, 0, 'X');
        BoardPosition p1 = new BoardPosition(0, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 2, 'X');
        BoardPosition p3 = new BoardPosition(0, 3, 'X');

        BoardPosition p4 = new BoardPosition(4, 4, 'O');
        BoardPosition p5 = new BoardPosition(4, 3, 'O');
        BoardPosition p6 = new BoardPosition(4, 2, 'O');
        BoardPosition p7 = new BoardPosition(4, 1, 'O');

        BoardPosition p8 = new BoardPosition(0, 4, 'X');


        b.placeMarker(p0);
        b.placeMarker(p1);
        b.placeMarker(p2);
        b.placeMarker(p3);
        b.placeMarker(p4);
        b.placeMarker(p5);
        b.placeMarker(p6);
        b.placeMarker(p7);
        b.placeMarker(p8);


        boolean foundResult = b.checkForWinner(p8);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }




    @Test
    public void testCheckForWinner_V_W() {

        GameBoard b = new GameBoard();

        BoardPosition p0 = new BoardPosition(0, 0, 'X');
        BoardPosition p1 = new BoardPosition(1, 0, 'X');
        BoardPosition p2 = new BoardPosition(2, 0, 'X');
        BoardPosition p3 = new BoardPosition(3, 0, 'X');
        BoardPosition p4 = new BoardPosition(4, 0, 'X');

        b.placeMarker(p0);
        b.placeMarker(p1);
        b.placeMarker(p2);
        b.placeMarker(p3);
        b.placeMarker(p4);


        boolean foundResult = b.checkForWinner(p4);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);
    }

    @Test
    public void testCheckForWinner_TL_W() {

        GameBoard b = new GameBoard();

        BoardPosition p0 = new BoardPosition(0, 0, 'X');
        BoardPosition p1 = new BoardPosition(1, 1, 'X');
        BoardPosition p2 = new BoardPosition(2, 2, 'X');
        BoardPosition p3 = new BoardPosition(3, 3, 'X');
        BoardPosition p4 = new BoardPosition(4, 4, 'X');

        b.placeMarker(p0);
        b.placeMarker(p1);
        b.placeMarker(p2);
        b.placeMarker(p3);
        b.placeMarker(p4);


        boolean foundResult = b.checkForWinner(p4);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckForWinner_BL_W() {

        GameBoard b = new GameBoard();

        BoardPosition p0 = new BoardPosition(7, 0, 'X');
        BoardPosition p1 = new BoardPosition(6, 1, 'X');
        BoardPosition p2 = new BoardPosition(5, 2, 'X');
        BoardPosition p3 = new BoardPosition(4, 3, 'X');
        BoardPosition p4 = new BoardPosition(3, 4, 'X');

        b.placeMarker(p0);
        b.placeMarker(p1);
        b.placeMarker(p2);
        b.placeMarker(p3);
        b.placeMarker(p4);


        boolean foundResult = b.checkForWinner(p4);
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);
    }

    @Test
    public void testCheckForWinner_H_L() {

        GameBoard b = new GameBoard();

        BoardPosition p0 = new BoardPosition(0, 0, 'X');
        BoardPosition p1 = new BoardPosition(0, 1, 'X');
        BoardPosition p2 = new BoardPosition(0, 2, 'X');
        BoardPosition p3 = new BoardPosition(0, 3, 'X');
        BoardPosition p4 = new BoardPosition(0, 5, 'X');

        b.placeMarker(p0);
        b.placeMarker(p1);
        b.placeMarker(p2);
        b.placeMarker(p3);
        b.placeMarker(p4);


        boolean foundResult = b.checkForWinner(p4);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }

    @Test
    public void testCheckForWinner_V_L() {

        GameBoard b = new GameBoard();

        BoardPosition p0 = new BoardPosition(0, 0, 'X');
        BoardPosition p1 = new BoardPosition(1, 0, 'X');
        BoardPosition p2 = new BoardPosition(2, 0, 'X');
        BoardPosition p3 = new BoardPosition(3, 0, 'X');
        BoardPosition p4 = new BoardPosition(5, 0, 'X');

        b.placeMarker(p0);
        b.placeMarker(p1);
        b.placeMarker(p2);
        b.placeMarker(p3);
        b.placeMarker(p4);


        boolean foundResult = b.checkForWinner(p4);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);
    }

    @Test
    public void testCheckForWinner_TL_L() {

        GameBoard b = new GameBoard();

        BoardPosition p0 = new BoardPosition(0, 0, 'X');
        BoardPosition p1 = new BoardPosition(1, 1, 'X');
        BoardPosition p2 = new BoardPosition(2, 2, 'X');
        BoardPosition p3 = new BoardPosition(3, 3, 'X');
        BoardPosition p4 = new BoardPosition(5, 5, 'X');

        b.placeMarker(p0);
        b.placeMarker(p1);
        b.placeMarker(p2);
        b.placeMarker(p3);
        b.placeMarker(p4);


        boolean foundResult = b.checkForWinner(p4);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);
    }

    @Test
    public void testCheckForWinner_BL_L() {

        GameBoard b = new GameBoard();

        BoardPosition p0 = new BoardPosition(7, 0, 'X');
        BoardPosition p1 = new BoardPosition(6, 1, 'X');
        BoardPosition p2 = new BoardPosition(5, 2, 'X');
        BoardPosition p3 = new BoardPosition(4, 3, 'X');
        BoardPosition p4 = new BoardPosition(2, 5, 'X');

        b.placeMarker(p0);
        b.placeMarker(p1);
        b.placeMarker(p2);
        b.placeMarker(p3);
        b.placeMarker(p4);


        boolean foundResult = b.checkForWinner(p4);
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);
    }

    /* Testing checkForDraw() */

    @Test
    public void testCheckForDraw_T() {

        GameBoard b = new GameBoard();

        // starts at "0" character
        int count = 48;

        for(int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                char c = (char)count++;
                BoardPosition p = new BoardPosition(i, j, c);
                b.placeMarker(p);
                b.checkForWinner(p);
            }
        }

        boolean foundResult = b.checkForDraw();
        boolean expectedResult = true;

        assertEquals(foundResult, expectedResult);


    }

    @Test
    public void testCheckForDraw_F() {

        GameBoard b = new GameBoard();

        // starts at "SPACE" character
        int count = 32;

        for(int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                char c = (char)count++;
                BoardPosition p = new BoardPosition(i, j, c);
                b.placeMarker(p);
                b.checkForWinner(p);
            }
        }

        boolean foundResult = b.checkForDraw();
        boolean expectedResult = false;

        assertEquals(foundResult, expectedResult);

    }


    /* Utility Functions */

    private String arrayToString(char[][] array) {

        StringBuilder str =  new StringBuilder("   0|1|2|3|4|5|6|7|");
        str.append("\n");
        for (int i = 0; i < ROWS; i++) {
            str.append(i);
            str.append("|");
            for (int j = 0; j < COLS; j++) {
                str.append(array[i][j]);
                str.append("|");
            }
            str.append("\n");
        }
        return str.toString();
    }




}
