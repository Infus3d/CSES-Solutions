import java.util.Scanner;

/**
 * We solve in O(N) time with a greedy algorithm: read left to right, and increase each element by the minimum amount needed 
 * to make it at least as large as the previous element. Output the total amount numbers changed.
 */
public class IncreasingArray {
    public static void main(String[] args) {
        //For reading input
        Scanner scanner = new Scanner(System.in);
        //length of input array
        int n = scanner.nextInt();
        //input array
        int xs[] = new int[n];
        //Read input array
        for(int i = 0; i < n; i++) {
            xs[i] = scanner.nextInt();
        }
        scanner.close();
        //Total amount by which elements changed. Long to avoid overflows.
        long totalChange = 0;
        //Start at index 1 because the first element does not have a previous
        for(int i = 1; i < n; i++) {
            int x = xs[i];
            int prev = xs[i-1];
            //If element greater than or equal to its previous, it is already valid and we skip to the next
            if(x >= prev) continue;
            //Otherwise, increase it by the difference between the numbers
            int difference = prev - x;
            xs[i] += difference;
            //Track total changes
            totalChange += difference;
        }
        //Output answer
        System.out.println(totalChange);
    }
}
