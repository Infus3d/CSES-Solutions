import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Note the code that satisfies the property for n=1:
 * 0
 * 1
 * Now a code that satisfies n=2:
 * 00
 * 01
 * 11
 * 10
 * And n=3:
 * 000
 * 001
 * 011
 * 010
 * 110
 * 111
 * 101
 * 100
 * Notice that the solution for some n is the solution for (n-1) preceded by 0s, followed by the solution for (n-1), backwards
 * and preceded by 1s.
 * We can thus recursively define our solution with a function that adds these levels. 
 * 
 */
public class GrayCode {
    public static void main(String[] args) throws IOException {
        //Take input
        Scanner scanner = new Scanner(System.in);
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out, "ASCII"), 512);
        int n = scanner.nextInt();
        scanner.close();
        ArrayList<String> output = solve(n);
        //Print our output
        for(String str : output) {
            out.write(str+"\n");
        }
        out.flush();
    }
    //Our recursive solution
    public static ArrayList<String> solve(int n) {
        //Base case
        if(n == 1) {
            ArrayList<String> output = new ArrayList<String>();
            output.add("0");
            output.add("1");
            return output;
        }
        //Recursive call to get our solution for n-1
        ArrayList<String> subCall = solve(n-1);
        //Build our solution
        ArrayList<String> output = new ArrayList<String>();
        //Place each element in subCall into output preceded by a 0.
        for(int i = 0; i < subCall.size(); i++) {
            output.add("0"+subCall.get(i));
        }
        //Now place elements in reverse order preceded by a 1.
        for(int i = 0; i < subCall.size(); i++) {
            output.add("1"+subCall.get(subCall.size()-1-i));
        }
        return output;
    }
}
