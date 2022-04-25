import java.util.Scanner;

public class AppleDivision {
    /**
     * We solve recursively with subtraction to represent adding to group 2, and \
     * addition for group 1.
     */
    public static long getClosest(long weights[], int idx, long target) {
        if(idx == weights.length) return 0;
        long weight = weights[idx];
        //Weight difference between groups if this one included in group 1
        long diffIncluded = getClosest(weights, idx+1, target-weight) + weight;
        //Wreight difference if this excluded
        long diffExcluded = getClosest(weights, idx+1, target+weight) - weight;
        //Return whichever one gets us closer to the target
        if(Math.abs(target - diffIncluded) > Math.abs(target - diffExcluded)) {
            return diffExcluded;
        }        
        return diffIncluded;
    }
    public static void main(String[] args) {
        //Read input
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        long weights[] = new long[n];
        for(int i = 0; i < n; i++) {
            weights[i] = scanner.nextInt();
        }
        scanner.close();

        long min = getClosest(weights, 0, 0);
        System.out.println(Math.abs(min));
    }
}