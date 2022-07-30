import java.util.Scanner;

/**
 * The number of bit strings of length N is 2**N (2 to the power of N) because each bit 
 * can be a 0 or a 1 (2 possibilities per bit, n bits, means 2 times itself n times total possibilities).
 * We compute this number modulo 10**9+7 by just taking the mod after each multiplication.
 */
public class BitStrings {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextInt();
        scanner.close();
        long solution = 1;
        for(int i = 0; i < n; i++) {
            solution = (solution * 2) % 1000000007;
        }
        System.out.println(solution);
    }
}
