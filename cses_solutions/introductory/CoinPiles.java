import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Scanner;

/**
 * The following properties hold for all valid piles:
 * The upper bound of b is 2a (always removing two b)
 * The lower bound of b is 1/2a (always removing two from a)
 * (a+b) % 3 = 0 (since we remove 3 coins total each step)
 */
public class CoinPiles {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out, "ASCII"), 512);
        long t = scanner.nextLong();
        //Solve each case
        for(int i = 0; i < t; i++) solve(scanner, out);
        out.flush();
    }
    public static void solve(Scanner scanner, BufferedWriter out) throws IOException {
        long a = scanner.nextLong();
        long b = scanner.nextLong();
        if(b <= 2*a && a <= 2*b && (a+b)%3 == 0) {
            out.write("YES\n");
        } else {
            out.write("NO\n");
        }
    }
}
