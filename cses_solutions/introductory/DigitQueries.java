import java.util.Scanner;

/**
 * Note there are 9 digits at the start with no extra numbers between (1-9)
 * Then there are 10 with a 1 between them (10-19)
 * 10 with a 2 between them (20-29), and so on up to (90-99)
 * for a total of 90 numbers with digits 1-9 between them.
 * Then there are 900 numbers seperated by 2 digits each
 * etc.
 * 
 * First, we find which order of magnitude it's in
 * Then we find the index within that order of magnitude
 * 
 * Note the use of longs to avoid overflow
 */
public class DigitQueries {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int q = scanner.nextInt();
        for(int i = 0; i < q; i++) {
            //Note that k is big so we use long.
            long k = scanner.nextLong();
            System.out.println(solve(k));
        }
        scanner.close();
    }

    private static int solve(long k) {
        long level = 0;
        //Find the level k is in.
        while(k > levelMax(level)) level++;
        //Now we can have the index of k within the level by subtracting the max index of prev level
        k -= levelMax(level-1);
        //We get the number at which k points by dividing by the number of digits in each number
        long pointedTo = (long)Math.pow(10, level-1) + (k-1)/level;
        //And the digit of that number pointed to with modulo
        long digitIndexPointedTo = level - 1 - ((k-1) % level);
        //Extract digit at that index
        return (int)((pointedTo / ((long)Math.pow(10, digitIndexPointedTo))) % 10);
    }

    //get the max index of elements in a "level"
    //with levels being level 1 = 1-9, level 2 = 10-99, level 3 = 100-999, etc.
    private static long levelMax(long level) {
        if(level == 0) return 0;
        return (9*(long)Math.pow(10, level-1)*(level)+levelMax(level-1));
    }
}
