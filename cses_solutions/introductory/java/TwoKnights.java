import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Scanner;

/**
 * There are k*k ways to place the first knight. The placement of the first knight blocks up to 9 squares:
 * 1 for the square it's on, and the rest for its moves. The number of squares it blocks via moves is reduced
 * if it is near an edge, based on number of squares that fall outside the board. if within 2 of top edge, top two squares are 
 * outside the board.
 * For n < 20, we will simply solve by brute force
 * Otherwise, the following holds:
 * There are 4 squares where placing the knight blocks just 3 squares for the second knight (corners)
 * 8 squares where 4 squares are blocked (adjacent to corners)
 * k*4-16 squares where 5 blocked (outer edge, not corner)
 * 4 squares where 5 blocked (diagonal to corner)
 * k*4-16 squares where 7 blocked (second from outer, not in corner)
 * k*k-(4+8+4+(k*4-16)+(k*4-16)) squares where 9 blocked (everything else)
 * 
 * We divide by 2 because switching the squares the knights are placed on results in the same placement (knights are identical)
 */
public class TwoKnights {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out, "ASCII"), 512);
        scanner.close();
        //Brute force up to 20
        for(int k = 1; k < 20 && k <= n; k++) {
            //Total number of ways to place two knights in this board size
            out.write(bruteforce(k) + "\n");
        }
        //Solve for each k in [20..n]
        for(int k = 20; k <= n; k++) {
            //Now we apply our formula for larger n
            out.write(calculate(k) + "\n");
        }
        out.flush();
    }
    //Implementation of our formula for calculating larger values
    public static long calculate(int k) {
        long size = k*k;
        return (4*(size-3)+8*(size-4)+(k*4-16)*(size-5)+4*(size-5)+(k*4-16)*(size-7)+(size-(4+8+4+(k*4-16)+(k*4-16)))*(size-9)) / 2;
    }
    //Find number of possibilities via bruteforce on small board size
    public static long bruteforce(int k) {
        long options = 0;
        //Size of board
        int size = k*k;
        //Iterate over squares
        for(int row = 0; row < k; row++) {
            for(int col = 0; col < k; col++) {
                int blocked = countBlocked(k, row, col);
                options += size - blocked;
            }
        }
        return options/2;
    }
    //Count number of squares blocked by certain knight placement
    public static int countBlocked(int k, int row, int col) {
        int blocked = 9;
        //Check boundries against each knight movement square
        if(row < 2 || col < 1) blocked--;
        if(row < 2 || col > k-2) blocked--;
        if(row < 1 || col > k-3) blocked--;
        if(row > k-2 || col > k-3) blocked--;
        if(row > k-3 || col > k-2) blocked--;
        if(row > k-3 || col < 1) blocked--;
        if(row > k-2 || col < 2) blocked--;
        if(row < 1 || col < 2) blocked--;
        return blocked;
    }
}
