import java.util.Scanner;

public class lab_3
{
        public static void main (String[] args)
                {
                    Scanner user_input = new Scanner(System.in);
                    String ones = new String(), tens = new String(), hundreds = new String(), thousands = new String();
                    int user_num, ones_dec, tens_dec, hundreds_dec, thousands_dec;
                    boolean too_big = false;

                    System.out.print("Please enter a decimal number between 3,999 and 1 inclusive: ");
                    user_num = Integer.parseInt(user_input.next());

                    if (user_num > 0) //if the number can be converted to roman numerals, do it.
                    {
                        ones_dec = user_num % 10;   //isolate the number in the "ones" spot

                        switch (ones_dec)
                        {
                            case 0: ones = "";    break;
                            case 1: ones = "I";     break;
                            case 2: ones = "II";    break;
                            case 3: ones = "III";   break;
                            case 4: ones = "IV";    break;
                            case 5: ones = "V";     break;
                            case 6: ones = "VI";    break;
                            case 7: ones = "VII";   break;
                            case 8: ones = "VIII";  break;
                            case 9: ones = "IX";    break;
                        }

                        if (user_num > 9)
                        {
                            tens_dec = (user_num % 100) / 10;   //isolate the number in the "tens" spot
                            
                            switch (tens_dec)
                            {
                                case 0: tens = "";    break;
                                case 1: tens = "X";     break;
                                case 2: tens = "XX";     break;
                                case 3: tens = "XXX";     break;
                                case 4: tens = "XL";     break;
                                case 5: tens = "L";     break;
                                case 6: tens = "LX";     break;
                                case 7: tens = "LXX";     break;
                                case 8: tens = "LXXX";     break;
                                case 9: tens = "XC";     break;
                            }
                        }

                        if (user_num > 99)
                        {
                            hundreds_dec = (user_num % 1000) / 100; //isolate the number in the "hundreds" spot
                            
                            switch (hundreds_dec)
                            {
                                case 0: hundreds = "";    break;
                                case 1: hundreds = "C";     break;
                                case 2: hundreds = "CC";     break;
                                case 3: hundreds = "CCC";     break;
                                case 4: hundreds = "CD";     break;
                                case 5: hundreds = "D";     break;
                                case 6: hundreds = "DL";     break;
                                case 7: hundreds = "DLL";     break;
                                case 8: hundreds = "DLLL";     break;
                                case 9: hundreds = "DM";     break;
                            }
                        }

                        if (user_num > 999)
                        {
                            thousands_dec = user_num / 1000;    //isolate the number in the "thousands" spot
                            
                            switch (thousands_dec)
                            {
                                case 0: thousands = "";    break;
                                case 1: thousands = "M";     break;
                                case 2: thousands = "MM";     break;
                                case 3: thousands = "MMM";     break;
                                case 4: too_big = true;     break;  //if the number is bigger than 3999, then make sure to output a message
                                case 5: too_big = true;     break;
                                case 6: too_big = true;     break;
                                case 7: too_big = true;     break;
                                case 8: too_big = true;     break;
                                case 9: too_big = true;     break;
                            }
                        }

                        if (too_big == true)    //user entered too large a number
                        {
                            System.out.println("This number is too big. Please try again.");
                        }
                        else
                        {
                            System.out.println("The roman numeral equivalent is: " + thousands + hundreds + tens + ones);
                        }
                   
                    }

                    else    //the user seems to have entered 0. This can't be converted to roman numerical form.
                    {
                        System.out.println("You have not entered a convertable number. Please try again.");
                    }
                }
}