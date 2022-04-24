import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * There are N! many strings. We solve this in O(N!) time.
 * 
 * We can construct all permutations by treating each character as distinct,
 * and making a recursive call. As we go, we will add to and check against a hashmap
 * of existing strings to avoid repeating a permutation when the same character appears multiple times 
 * in the input. We always generate with the lexographically first characters first to ensure our strings
 * strings are generated in alphabetical order.
 */
public class CreatingStrings {
    //Keep count of how many each character remain to be placed in output string
    static int[] remainingCharacters;
    static ArrayList<String> output;
    public static void main(String[] args) throws IOException {
        //Fast output
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out, "ASCII"), 512);
        //take input
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        scanner.close();
        //Build remaining characters array
        remainingCharacters = new int[26];
        for(int i = 0; i < input.length(); i++) {
            remainingCharacters[input.charAt(i)-'a']++;
        }
        output = new ArrayList<String>();
        //Solve recursively and print at base case
        solve(input.length(), "");
        //Output our solution
        out.write(output.size()+"\n");
        for(String str : output) {
            out.write(str+"\n");
        }
        out.flush();
    }
    private static void solve(int l, String builtString) throws IOException {
        //Base case
        if(builtString.length() == l) {
            //output string and remember that it has been output
            output.add(builtString);
            return;
        }
        //Otherwise, we recursively call this with another selected character added on
        for(int i = 0; i < 26; i++) {
            int characterCount = remainingCharacters[i];
            if(characterCount == 0) continue;//None of this character to place
            //Othewise, make the output string with this character placed here
            //we use backtracking to store which characters have been used
            remainingCharacters[i]--;
            solve(l, builtString+Character.toString((char)(i+'a')));
            remainingCharacters[i]++;
        }
    }
}
