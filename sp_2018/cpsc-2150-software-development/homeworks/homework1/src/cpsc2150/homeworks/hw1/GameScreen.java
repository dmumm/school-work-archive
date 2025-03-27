// Dylan Mumm, 2150
// HW1
// February 18th


package cpsc2150.homeworks.hw1;
import java.util.*;


public class GameScreen {


    public static void main (String [] args) {

         final int MAX_PLAYERS = 10;
         final int MIN_PLAYERS = 2;
         final int MAX_DIMENSION = IGameBoard.MAX_SIZE;
         final int MIN_DIMENSION = 1;
         final char PLAYER_SELECTION[] =  {'X', 'O', 'Y', 'Z', 'A', 'K', 'E', 'J', 'N', 'H'};


        Scanner sc = new Scanner(System.in);
        boolean start = true;

        // Game loop
        gameLoop:
        while (start) {

            //  starts new session
            GameBoardFast b;
            boolean won = false;
            char type = '0';
            int players = -1;
            int rows = -1;
            int cols = -1;
            int toWin = -1;
            int turn = 0;

            while(players < MIN_PLAYERS || players > MAX_PLAYERS) {
                System.out.println("How many players will play? (Max of 10) ");
                players = sc.nextInt();
                if(players < MIN_PLAYERS || players > MAX_PLAYERS)
                    System.out.println("Must be between 2 and 10 players");
            }

            char cast[] = new char[players];
            for(int i = 0; i < players; i++)
                cast[i] = PLAYER_SELECTION[i];

            char currentPlayer = cast[turn];


            while(rows < MIN_DIMENSION || rows > MAX_DIMENSION) {
                System.out.println("How many rows should be on the board?");
                rows = sc.nextInt();
                if(rows < MIN_DIMENSION || rows > MAX_DIMENSION)
                    System.out.println("Can only have 100 rows or less");
            }

            while(cols < MIN_DIMENSION || cols > MAX_DIMENSION) {
                System.out.println("How many columns should be on the board?");
                cols = sc.nextInt();
                if(cols < MIN_DIMENSION || cols > MAX_DIMENSION)
                    System.out.println("Can only have 100 columns or less");
            }

            while((toWin > rows && toWin > cols) || toWin < 0) {
                System.out.println("Many many in a row to win?");
                toWin = sc.nextInt();
                if((toWin > rows && toWin > cols) || toWin < 0)
                    System.out.println("You can't have that many because thats more than the number of rows or columns");
            }

            while(type != 'F' && type != 'f' && type != 'M' && type != 'm') {
                System.out.println("Enter F for a (F)ast implementation or M for a (M)emory efficient implementation");
                type = sc.next().charAt(0);
            }

            // if (type == 'F' || type == 'f') {
                b = new GameBoardFast(rows, cols, toWin);
//              }
//            if (type == 'M' || type == 'm') {
//                 b = new GameBoardFast(rows, cols, toWin);
//            }


            matchLoop:
            while (!won) {

                // Prints out board and resets conditional checkers
                System.out.println(b.toString());
                int row = -1, col = -1;
                boolean available = false;

                // turn
                while (row < 0 || row > rows-1 || col < 0 || col > cols-1 || !available) {
                    System.out.println("Player " + currentPlayer + " Please enter your ROW");
                    row = sc.nextInt();
                    System.out.println("Player " + currentPlayer + " Please enter your COLUMN");
                    col = sc.nextInt();
                    BoardPosition p = new BoardPosition(row, col, currentPlayer);
                    available = b.checkSpace(p);

                    // If permitted, inputs selection, and checks for win and draw
                    if (row < 0 || row > rows-1 || col < 0 || col > cols-1 || !available)
                        System.out.println("That space is unavailable, please pick again");
                    else {
                        b.placeMarker(p);
                        if (b.checkForWinner(p)) {
                            System.out.println("Player " + currentPlayer + " WINS!");
                            System.out.println("Would you like to play again Y/N");
                            char c = sc.next().charAt(0);

                            // If they want to replay, only resets match. If they want to quit, ends game loop
                            if (c == 'Y' || c == 'y') {
                                break matchLoop;
                            } else {
                                break gameLoop;
                            }
                        }
                        else if (b.checkForDraw()) {
                            System.out.println("Draw!");
                            System.out.println("Would you like to play again Y/N");
                            char c = sc.next().charAt(0);
                            if (c == 'Y' || c == 'y') {
                                break matchLoop;
                            } else {
                                break gameLoop;
                            }
                        }
                    }
                }

                turn++;
                if(turn == players)
                    turn = 0;

                currentPlayer = cast[turn];

            }
        }
    }
}
