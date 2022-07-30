import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * To get a disk to a certain post, we need to move all disks atop it to the other post.
 * We want to get the last disk to the 3rd post, so we make a recursive call to move the second to last
 * disk to the second post, move the 3rd disk, then make another recursive call to move the second to 
 * last disk onto the last disk. 
 * To move the second to last, we must first move the 3rd to last disk, another recursive call.
 * 
 * This pattern continues to our base case, where we can simply move the disk directly.
 */
public class TowerOfHanoi {
    public static void main(String[] args) throws IOException{
        //Fast output
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out, "ASCII"), 512);
        //Take input
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.close();
        //We represent a move as an int array of length two: {a, b}
        //We construct an arraylist that stores our sequence of moves.
        ArrayList<int[]> moves = new ArrayList<int[]>();
        solve(n, moves, 1, 3);
        //Output number of moves it took
        out.write(moves.size()+"\n");
        //Output each move
        for(int[] move : moves) {
            out.write(""+move[0] + " " + move[1] + "\n");
        }
        //Flush buffer
        out.flush();
    }
    //Info we need to pass recursively: number in stack, list to write moves to, stack moving from, and stack moving to.
    private static void solve(int n, ArrayList<int[]> moves, int a, int b) {
        //Base case, stack is empty - no need to make moves
        if(n == 0) return;
        //Index of other pole
        int c = 1;
        while(c == a || c == b) c++;
        //Move all smaller disks to other pole
        solve(n-1, moves, a, c);
        //Move this disk to target pole
        int[] move = {a, b};
        moves.add(move);
        //Move all smaller disks from other pole to target pole
        solve(n-1, moves, c, b);
    }
}
