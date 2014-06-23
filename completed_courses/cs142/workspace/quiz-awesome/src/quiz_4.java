/**
 * @author Ethan Estrada
 * CS 142
 */

/**Test Cases:
*Ethan == nahtE
*Harry == yrraH
*Java == avaJ
*forlorn == nrolrof*/

import java.util.Scanner;

public class quiz_4
{
    public static void main(String[] args)
    {
        Scanner myScan = new Scanner(System.in);
        String userString = new String(), newString = new String("");
        System.out.print("Please enter a word: ");
        userString = myScan.next();

        for(int i = userString.length(); i > 0; i--)
        {
            newString += userString.charAt(i-1);
        }

        System.out.println("Your word backwards is: " + newString);

    }
}

