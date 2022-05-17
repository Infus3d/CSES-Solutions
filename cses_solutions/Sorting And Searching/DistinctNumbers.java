import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

/**
 * The solution is rather simple:
 * We can sort all numbers in O(n*log(n)) time and iterate through
 * the sorted array. If two adjacent numbers differ, we increase the
 * answer by one. Finally print answer+1 because we need to account
 * for the ver first number that wasn't compared with anything else
 * before it.
 */
public class DistinctNumbers {
    public static void main(String args[]){
        FastScanner in = new FastScanner(); //fast scanner
        PrintWriter out = new PrintWriter(System.out); //fast writer
        
        int n = in.nextInt();
        int x[] = new int[n];
        for(int i=0; i<n; i++)
            x[i] = in.nextInt();
        
        sort(x);

        int ans = 0;
        for(int i=1; i<n; i++){
            if(x[i] != x[i-1])
                ans++;
        }
        out.println(ans+1);
        out.close();
    }

    /**
     * Uses collections.sort to ensure nlogn runtime
     * as compared to arrays.sort's n^2 worst case runtime
     */
    static void sort(int[] a) {
        ArrayList<Integer> al = new ArrayList<>();
        for (int i : a)
            al.add(i);
        Collections.sort(al);
        for (int i = 0; i < a.length; i++)
            a[i] = al.get(i);
    }

    /**
     * This is a private template class for fast scanning. It has the same basic reading methods as Scanner
     * like nextInt(), nextLong(), etc.
     * It is recommended that you use this template for all the problems you solve.
     */
    static class FastScanner {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer("");
        String next() {while (!st.hasMoreTokens())try {st = new StringTokenizer(br.readLine());} catch (IOException e) {}return st.nextToken();}
        int nextInt() {return Integer.parseInt(next());}
        long nextLong() {return Long.parseLong(next());}
        double nextDouble() {return Double.parseDouble(next());}
        int[] readArray(int n) { int[] a = new int[n]; for (int i = 0; i < n; i++) {a[i] = nextInt();} return a;}
    }
}
