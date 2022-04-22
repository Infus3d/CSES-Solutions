import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Scanner;

/**
 * Note the sizes of inputs for this problem. To compute outputs quickly enough, we derive a formula
 * to calculate the solution to each test case in O(1) time.
 * Notice the pattern down the diagonal 1,3,7,13,21,...
 * The values along this diagonal follow the formula n^2 - (n-1), where (n, n) is the 
 * index of the square on the diagonal.
 * We can then calculate the value at an index (x, y) by first calculating the value at (n, n)
 * where n is the max of x and y, then find our value relative to this corner.
 */
public class NumberSpiral {
    public static void main(String[] args) throws NumberFormatException, IOException {
        //Input and outputs are large for this problem, so we use buffered reader/writer for faster I/O.
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out, "ASCII"), 512);
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        //number of test cases
        int t = Integer.parseInt(in.readLine());
        //iteratively solve each test case
        for(int i = 0; i < t; i++) solve(in, out);
        //Flush outputs to send to console
        out.flush();
    }
    //Read in and solve a case
    public static void solve(BufferedReader in, BufferedWriter out) throws IOException {
        //Read in the case
        String[] line = in.readLine().split(" ");
        long y = Integer.parseInt(line[0]);
        long x = Integer.parseInt(line[1]);
        //index of the diagonal we want is the max of x and y
        long n = Math.max(y, x);
        //value on diagonal
        long val = n*n - (n - 1);
        /*If n is odd, decreasing x to our value increases the number in our target square, while decreasing
        y decreases the number. If n is even, increasing x decreases our number while decreasing y decreases our number.*/
        if(n%2 == 1) val += x - y;
        else val += y - x;
        //Print the value we found
        out.write(val + "\n");
    }
}
