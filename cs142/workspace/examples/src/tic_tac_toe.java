
import java.util.Arrays;
import java.util.Scanner;

public class tic_tac_toe {

	public static void main(String[] args) {
		// These will be used later to pause the output
		Scanner in = new Scanner(System.in);
		String prompt = "\nPress enter to continue...";

		// Here's our 2D array!
		// Changing the characters may yield a different winner
		char[][] board =
		{
				{'O','O','X'},
				{'X','X','X'},
				{'O','X','O'}
		};

		/* this is a line demonstrating how Arrays.toString() handles a 2D array
		*  it will print a sequence of memory addresses, which implies that the
		*  outer array contains pointers to the inner arrays. (Which is the case.)
		*/
		String printit = Arrays.toString(board);
		System.out.println(printit);

		// This is a simple way of suspending output until the user hits enter
		System.out.println(prompt);
		in.nextLine();

		// Since the Arrays.toString() didn't work, we create a method that takes
		// a 2D array as the first parameter, and the version number of the
		// printing algorithm (see printMyBoard method for details)
		printMyBoard(board, 1);

		// This is a simple way of suspending output until the user hits enter
		System.out.println(prompt);
		in.nextLine();

		// Version 2 is a little more Tic-Tac-Toe-looking
		printMyBoard(board, 2);

		// This is a simple way of suspending output until the user hits enter
		System.out.println(prompt);
		in.nextLine();

		//okay, who wins? Here we're only looking at the center spot.
		// TODO: How would we check for a winner in any location?
		char winner = checkCenter(board);
	}

	/**
	 * @param myBoard - the 2D tic tac toe board to be printed
	 * @param version - 1 => simple printing using Arrays.toString() inside a for each loop.
	 * 		any other number => nested for loop to print out each element and separators where needed.
	 */
	public static void printMyBoard(char[][] myBoard, int version)
	{
		if (version == 1)
		{
			System.out.println("Tic-Tac-Toe Board");
			for (char[] array : myBoard)
			{
				String row = Arrays.toString(array);
				System.out.println(row);
			}
		}
		else{
			System.out.println("Tic-Tac-Toe Board V2");
			for (int row = 0; row < myBoard.length; row++)	// for rows
			{
				// what does "myBoard[row].length" refer to?
				// It is the length of the array that myBoard[row] is pointing to
				for (int col = 0; col < myBoard[row].length; col++) // for columns
				{
					System.out.print(" " + myBoard[row][col]);// print out the element
					if (col < myBoard[row].length-1)	// vertical lines
						System.out.print(" |");
				}
				if (row < myBoard.length-1)
					System.out.println("\n---+---+---");	// horizontal lines
			}
		}
	}

	/**
	 * @param myBoard - Tic Tac Toe board to check.
	 * @return The winning character based only on the center square.  'e' if no winner.
	 */
	public static char checkCenter(char[][] myBoard)
	{
		char win = 'e';
		int row = 1;	// starting one in
		int col = 1;	// same for column
		char center = myBoard[row][col];	// getting the center square

		if (myBoard[row-1][col] == center && myBoard[row+1][col] == center)	// top and bottom
		{
			System.out.println(center + " wins vertically!");
			win = center;
		}
		if (myBoard[row][col-1] == center && myBoard[row][col+1] == center)	// left and right
		{
			System.out.println(center + " wins horizontally!");
			win = center;
		}
		if (myBoard[row-1][col-1] == center && myBoard[row+1][col+1] == center)	// diagonal \
		{
			System.out.println(center + " wins diagonally \\!");
			win = center;
		}
		if (myBoard[row-1][col+1] == center && myBoard[row+1][col-1] == center)// diagonal /
		{
			System.out.println(center + " wins diagonally /!");
			win = center;
		}
		return win;
	}

}
