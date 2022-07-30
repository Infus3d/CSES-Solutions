import java.util.Scanner;

/**
 * Note the large upper bound for N. We need to find something that runs in log(n) time or faster.
 * Consider that multiplying 2 and 5 will produce a trailing 0. 
 * We count the number of 5s and 2s in n!, and this count is our solution.
 * To count this, we calculate floor(n/5), floor(n/25), ...
 */
public class TrailingZeros {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextInt();
        scanner.close();
        System.out.println(solve(n));
    }
    
    /**
     * Count number of trailing zeros in n! by finding the number of times n is divisible by 5
     */
    public static long solve(long n) {
        long numberDivided = 0;
        while(n >= 5) {
            n /= 5;
            numberDivided += n;
        }
        return numberDivided;
    }
}
