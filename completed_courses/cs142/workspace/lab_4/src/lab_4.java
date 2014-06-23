/**
 * @author Ethan Estrada
 */

import java.util.Scanner;

public class lab_4
{
	public static void main(String[] args)
	{
		String user_string = new String();
		boolean run_again = true;

		do
		{

			String word_part_A = new String(), word_part_B = new String(), translated_string = new String(), translated_word = new String();
			Scanner scan_in = new Scanner(System.in), word_scanner;
			int first_vowel = 0;

			System.out.print("Please enter a string to convert to pig latin (or \"opstay\" to end program): ");
			user_string = scan_in.nextLine();
			word_scanner = new Scanner(user_string);

			if(user_string.equalsIgnoreCase("opstay")) //make this the last time the program runs if the user enters "opstay"
			{
				run_again = false;
			}

			while(word_scanner.hasNext())
			{
				String current_word = word_scanner.next(), punctuation = new String("");
                                boolean uppercase = false;

                                if(Character.isUpperCase(current_word.charAt(0)))
                                {
                                    uppercase = true;
                                }

                                if(!Character.isLetter(current_word.charAt(current_word.length() - 1)))
                                {
                                    punctuation += current_word.charAt(current_word.length() - 1);
                                    current_word = current_word.substring(0, (current_word.length() - 1));
                                }

				for(int i = 0;i < current_word.length();i++)
				{       //Check for a vowel in order to split the word for Pig Latin translation
					if(current_word.charAt(i)=='a' || current_word.charAt(i)=='e' || current_word.charAt(i)=='i' || current_word.charAt(i)=='o' || current_word.charAt(i)=='u' || current_word.charAt(i)=='A' || current_word.charAt(i)=='E' || current_word.charAt(i)=='I' || current_word.charAt(i)=='O' || current_word.charAt(i)=='U')
					{
						first_vowel = i;
						i = current_word.length() + 1;
					}
				}

				word_part_A = current_word.substring(0, first_vowel).toLowerCase();
				word_part_B = current_word.substring(first_vowel, current_word.length());
				translated_word= word_part_B + word_part_A + "ay" + punctuation + " ";
                                
                                if(uppercase) //properly make word capitalized if it was initially
                                {
                                    translated_word = translated_word.replaceFirst(translated_word.substring(0, 1), translated_word.substring(0, 1).toUpperCase());
                                }

                                translated_string += translated_word;
			}

                        System.out.println(translated_string);

		}while(run_again);
	}
}
