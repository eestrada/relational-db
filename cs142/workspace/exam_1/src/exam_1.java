import java.util.Scanner;

/**
 *
 * @author Ethan Estrada
 */

public class exam_1
{
    public static void main (String[] args)
    {
        boolean again = true; // used to run do-while loop

        do
        {
            Scanner my_scan = new Scanner(System.in);
            String user_input;
            int num_c = 0, num_g = 0, num_a = 0, num_t = 0;
            boolean error = false;

            print("Please enter a DNA string: ");
            user_input = my_scan.nextLine();

            if(user_input.equalsIgnoreCase("stop")) //Stop the program if the user enters the sentinel word
            {
                println("This program will now terminate. Beware the robot uprising. End of line.");
                again = false;
            }
            else if(user_input.length() == 0) //re-run the program if the string is empty
            {
                println("You don't seem to have entered anything. Computer feel sad now. End of line.\n");
            }
            else //main work of program is done here
            {
                for(int i = 0; i < user_input.length(); i++) //parse through each character of the string counting valid values and reporting invalid ones
                {
                    switch(user_input.charAt(i))
                    {
                        case 'c':
                            num_c++; break;
                        case 'C':
                            num_c++; break;
                        case 'g':
                            num_g++; break;
                        case 'G':
                            num_g++; break;
                        case 'a':
                            num_a++; break;
                        case 'A':
                            num_a++; break;
                        case 't':
                            num_t++; break;
                        case 'T':
                            num_t++; break;
                        case ' ':
                            println("Empty spaces are not valid in a DNA string."); error = true; break;
                        default:
                            println("The character \"" + user_input.charAt(i) + "\" is not valid in a DNA string."); error = true; break;
                    }
                }

                if (error == true) // if the user entered an invalid character
                {
                    println("Try again or suffer the consequences. End of line.\n");
                }
                else // if all goes well, count the number of different characters then compute and report their percentages.
                {
                    println("In the string \"" + user_input + "\" there are " + num_c + " c's, " + num_g + " g's, " + num_a + " a's and " + num_t + " t's.");
                    print("Thus the string is " +(((num_c + num_g) * 100)/(user_input.length()))+ "% c's and g's and " + (((num_a + num_t) * 100)/(user_input.length())) +"% a's and t's. ");

                    if((((num_c + num_g) * 100)/(user_input.length())) >= 40) //let the user know if this DNA string will likely be a gene or not
                    {
                        println("Since the percentage of c's and g's is equal to or greater than 40% this DNA string MIGHT be a gene.\n");
                    }
                    else
                    {
                        println("Since the percentage of c's and g's is less than 40% this DNA string is PROBABLY NOT a gene.\n");
                    }
                }
            }         

        }while(again == true); //keep running until boolean 'again' is made false
    }


    /**used to simplify printing to the screen*/
    public static void print (String this_string) 
    {
        System.out.print(this_string);
    }
    
    /**used to simplify printing to the screen with a newline character*/
    public static void println (String this_string)
    {
        System.out.println(this_string);
    }
}

