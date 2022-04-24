import java.util.Scanner;

/**
 * We solve in O(N) time as follows:
 * Iterate over the string, and keep an array containing the number of each character present. Then, 
 * begin placing matching characters at the front and back of output string as we can with out character counts.
 * Cases:
 * only 1 character has odd count: that character goes in the middle
 * more than 1 character odd count: no solution
 * all character counts even: place as normal
 */
public class PalindromeReorder {
    public static void main(String[] args) {
        //Take input
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        int n = input.length();
        scanner.close();
        //For storing count of how many of each character appear
        int[] characterCounts = new int[26];
        for(int i = 0; i < n; i++) {
            //Take character as a number, 0-25 for A-Z.
            int charNum = input.charAt(i)-'A';
            characterCounts[charNum]++;
        }
        //Check if one or more characters have odd count
        int oddIdx = -1;
        for(int i = 0; i < characterCounts.length; i++) {
            if(characterCounts[i]%2 == 1) {
                //If already found odd count, we do not have solution.
                if(oddIdx != -1) {
                    System.out.println("NO SOLUTION");
                    return;
                }
                //otherwise, set odd index to this one
                oddIdx = i;
            }
        }
        //Build output string from middle
        char[] output = new char[n];
        //If length of n is odd, start it off with its odd character in the middle
        if(n % 2 == 1) {
            output[n/2] = (char)(oddIdx+'A');
            characterCounts[oddIdx]--;
        }
        //Build the rest of the string by placing our characters
        int charToPlace = 0;
        for(int i = 0; i < n/2; i++) {
            //Move to next unplaced character
            while(characterCounts[charToPlace] == 0) charToPlace++;
            output[n-i-1] = (char)(charToPlace+'A');
            output[i] = (char)(charToPlace+'A');
            characterCounts[charToPlace] -= 2;
        }
        System.out.println(output);
    }
}
