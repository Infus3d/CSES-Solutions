import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

/**
 * The idea behind the solution is that we should greedily assign
 * the minimum sized apartment to the minimum size demanding applicant.
 * Let's sort apartments and applicants and let a[i] be the minimum
 * available applicant and b[j] be the minimum available apartment size.
 * Since every apartment can be assigned to at most one applicant,
 * it is best to assign b[j] to a[i] if it's within range instead of leaving
 * b[j] for later (for.ex. leaving it to assign to a[i+1], which obviously
 * is suboptimal).
 * Whenever we find a match, that is, (a[i]-k <= b[j] and b[j] <= a[i]+k) condition
 * is met, assign a[i] to b[j] and increase the answer.
 * 
 * Runtime O(n*log(n))
 */
public class Apartments {
    public static void main(String args[]){
        FastScanner in = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);

        int n = in.nextInt(), m = in.nextInt(), k = in.nextInt();
        int a[] = new int[n], b[] = new int[m];

        for(int i=0; i<n; i++) a[i] = in.nextInt();
        for(int i=0; i<m; i++) b[i] = in.nextInt();

        sort(a); sort(b);

        int acnt = 0, bcnt = 0, ans = 0;
        while(acnt < n && bcnt < m){
            if(a[acnt]-k <= b[bcnt] && b[bcnt] <= a[acnt]+k){ //if a match is found, pair them
                acnt++;
                bcnt++;
                ans++;
            }
            else if(b[bcnt] < a[acnt]-k) bcnt++; //if b[j] is far below a[i]'s desired range, then increase j
            else if(a[acnt]+k < b[bcnt]) acnt++; //if b[j] is far above a[i]'s desired range, then increase i
        }
        out.println(ans);
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
