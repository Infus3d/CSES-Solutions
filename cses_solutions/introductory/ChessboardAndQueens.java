import java.util.Scanner;

/**
 * A chessboard is small, and we aren't placing many queens. We wolve with brute force.
 */
public class ChessboardAndQueens {
    //Store which squares are threatened, reserved, and free.
    static char board[][];
    //Recursive solution with brute force. Try placing queen at each square, and see how many
    //ways to place remaining queens afterward. Sum these possibilities.
    private static long solve(int queensToPlace) {
        //Base case
        if(queensToPlace == 0) return 1;
        long possibilities = 0;
        //Iterate over board squares and try placing queen there if not taken
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                //Skip if we can't place queen here
                if(board[i][j] != '.') continue;
                //Mark the squares threatened by placing the queen here
                mark(i, j, true);
                //See how many ways to place others in this config
                possibilities += solve(queensToPlace-1);
                //unmark those squares
                mark(i, j, false);
            }
        }
        return possibilities;
    }
    private static void mark(int row, int col, boolean placing) {
        //Character to remove
        char rChar = placing ? '.' : '!';
        //Character to place (we use ! to represent threatened square)
        char pChar = placing ? '!' : '.';
        //Mark squares in all directions from queen
        for(int dx = -1; dx < 2; dx++) {
            for(int dy = -1; dy < 2; dy++) {
                if(dy == 0 && dx == 0) continue;
                markVector(row, col, dx, dy, rChar, pChar);
            }
        }
    }
    //Mark all squares in a straight line from a point on the board
    private static void markVector(int row, int col, int dx, int dy, char rChar, char pChar) {
        if(row < 0 || col < 0 || row > 7 || col > 7) return;
        if(board[row][col] == rChar) board[row][col] = pChar;
        markVector(row+dx, col+dy, dx, dy, rChar, pChar);
    }
    public static void main(String[] args) {
        //Fill our board with input
        Scanner scanner = new Scanner(System.in);
        board = new char[8][8];
        for(int i = 0; i < 8; i++) {
            board[i] = scanner.nextLine().toCharArray();
        }
        scanner.close();
        long possibilities = solve(8);
        System.out.println(possibilities);
    }
}
