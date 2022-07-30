//Note: submissions must be in the default package (no package definiton in file)

import java.util.Scanner;

public class WeirdAlgorithm {
    public static void main(String[] args) {
        //Scanner to read input from standard in (console by default, test files on judge server)
        Scanner scanner = new Scanner(System.in);
        /*
        String we store our output in.
        Since we are using System.out.println() to print to standard out, calling it at every iteration
        of our simulation would be too slow. Instead we store our output, then print all at once.
        */
        String output = "";
        //input n as defined in problem. We use long to avoid overflows.
        long n = scanner.nextInt();
        //Output start
        output += n;
        //Repeat until n is not 1
        while(n != 1) {
            //simulate step as defined in problem
            if(n%2 == 0) {//n is even
                n = n/2;
            } else {//n is odd
                n = n*3 + 1;
            }
            //Print with preceding space to have inputs seperated
            output += " " + n;
        }
        //Printing newline at end is typically not strictly necessary, but good practice since
        //some problems require it.
        System.out.println(output);
        //This line does not matter to our solution, but it makes a compiler warning go away
        scanner.close();
    }
}