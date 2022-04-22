//No package

import java.util.Scanner;

public class MissingNumber {
    public static void main(String[] args) {
        //Scanner to read input
        Scanner scanner = new Scanner(System.in);
        //Read in n, the length of input
        int n = scanner.nextInt();
        //We create an array to mark which of the numbers we see in the input
        boolean covered[] = new boolean[n];
        //We read the numbers on the next line and check off corresponding indicies in our array
        for(int i = 0; i < n-1; i++) {
            int num = scanner.nextInt();
            //Subtract 1 to get index because the first index of our array is 0
            covered[num-1] = true;
        }
        //Finally we find and print the unmarked number.
        for(int i = 0; i < n; i++) {
            //If i was covered by the input numbers, skip to the next index
            if(covered[i]) continue;
            //Otherwise, we've found our missing number
            System.out.println(i+1);
        }
        scanner.close();
    }
}
