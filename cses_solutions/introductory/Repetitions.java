import java.util.Scanner;

/*
    We solve in O(n) time by reading left to right, counting how many same characters 
    we've seen in a row, and reembering the maximum such length.
*/

public class Repetitions {
    public static void main(String[] args) {
        //For reading input
        Scanner scanner = new Scanner(System.in);
        //Read input
        String sequence = scanner.nextLine();
        //For remembering the maximum ength repetition we've seen
        int maxLength = 1;
        //For remembering how long the current repetition we're reading is
        int repLen = 1;
        //Previous character we read
        char prevC = sequence.charAt(0);
        for(int i = 1; i < sequence.length(); i++) {
            //character at our index
            char c = sequence.charAt(i);
            if(c != prevC) {//character not same as previous, start new sequence
                repLen = 1;
            } else {//otherwise, increment length of this sequence and update maxLength if necessary
                repLen++;
                if(repLen > maxLength) maxLength = repLen;
            }
            //Set previous character
            prevC = c;
        }
        //Print solution
        System.out.println(maxLength);
        scanner.close();
    }
}
