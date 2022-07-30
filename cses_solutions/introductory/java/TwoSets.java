import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Greedy Algorithm, O(N) time.
 * Starting with the greatest element in the range [1..n], 
 * add it to the second set. Then iteratively add the next smaller element to whichever set has
 * a lower sum. If we end up with inbalanced sets, there is no solution.
 */
public class TwoSets {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        //Bufferedwriter for faster outputs sincewe'll be printing up to 10^6 elements
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out, "ASCII"), 512);
        //take input
        int n = scanner.nextInt();
        scanner.close();
        //Our sets of integers
        ArrayList<Integer> set1 = new ArrayList<Integer>();
        ArrayList<Integer> set2 = new ArrayList<Integer>();
        //Sums of elements in sets
        long sum1 = 0;
        long sum2 = 0;
        //Move down from n, adding to lower set and tracking sums
        for(int i = n; i > 0; i--) {
            if(sum1 > sum2) {
                set2.add(i);
                sum2 += i;
            } else {
                set1.add(i);
                sum1 += i;
            }
        }
        //Output no if sets not balanced
        if(sum1 != sum2) {
            out.write("NO\n");
        } else {//Otherwise, output our sets
            out.write("YES\n");
            writeSet(set1, out);
            writeSet(set2, out);
        }
        //Don't forget to flush buffer to make output
        out.flush();
    }
    //Output a set and its number of elements as defined in problem
    public static void writeSet(ArrayList<Integer> set, BufferedWriter out) throws IOException {
        out.write(set.size() + "\n");
        for(int i = 0; i < set.size(); i++) {
            out.write("" + set.get(i));
            //Don't print space on end of line (after last element)
            if(i < set.size()-1) out.write(" ");
        }
        out.write("\n");
    }
}
