import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Scanner;

/**
 * O(N) time:
 * Print every other number 1 to n, then print the unprinted numbers
 * Edge cases:
 * 1 for n = 1
 * NO SOLUTION for n < 4
 * 2 4 1 3 for n = 4
 */
public class Permutations {
    public static void main(String[] args) throws IOException {
        //In this solution we print out many numbers, so we use BufferedWriter to make it faster.
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out, "ASCII"), 512);
        Scanner scanner = new Scanner(System.in);
        //Read input
        int n = scanner.nextInt();
        scanner.close();
        //Edge cases
        if(n == 1) {
            System.out.println("1");
            return;
        }
        if(n < 4) {
            System.out.println("NO SOLUTION");
            return;
        }
        if(n == 4) {
            System.out.println("2 4 1 3");
            return;
        }
        //Otherwise, n > 4 and we implement our solution.
        //Print odd numbers
        for(int i = 1; i <= n; i += 2) {
            out.write(i + " ");
        }
        //Print even numbers
        for(int i = 2; i <= n; i += 2) {
            out.write(i + "");
            //Only add a space if this is not the last number in the sequence
            if(i <= n-2) out.write(" ");
        }
        out.write("\n");
        out.flush();
    }
}
