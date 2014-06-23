
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 *
 * @author Ethan D. Estrada
 *
 * CS142
 * Lab 7 Hotplate
 * 18/10/2010
 */
public class lab_7
{
    /**
     * Main class
     * @param args
     * @throws FileNotFoundException
     */
    public static void main(String[] args) throws FileNotFoundException
    {
        String answer;
        System.out.print("********************** Welcome! **********************\n\n");
        do
        {
            final int DEFAULTSIZE = 20;//default size of array in both the x and y directions
            final double ACCURACY = 0.1;//default level of accuracy to compute array with

            Scanner myScan = new Scanner (System.in);
            double myDub[][], levelOfAccuracy;

            System.out.print("What size array would you like to create? Type \"d\" for default size: ");
            answer = myScan.next();
            if(answer.equalsIgnoreCase("d")|| answer.equalsIgnoreCase("default"))//initializes array size to default
            {
                myDub = initDblArray(DEFAULTSIZE, DEFAULTSIZE);
            }
            else//initializes array size to user provided value
            {
                int tempInt = Integer.parseInt(answer);
                myDub = initDblArray(tempInt, tempInt);
            }

            myScan = new Scanner (System.in);//refresh scanner to clear out any previous values
            System.out.print("What degree of accuracy to compute array(i.e. \"0.1\")? Type \"d\" for default accuracy: ");
            answer = myScan.next();
            if(answer.equalsIgnoreCase("d")|| answer.equalsIgnoreCase("default"))//initializes accuracy to default
            {
                levelOfAccuracy = ACCURACY;
            }
            else//initializes accuracy to user provided value
            {
                levelOfAccuracy = Double.parseDouble(answer);
            }

            printFParray(myDub);//print out array before computation
            System.out.printf("Array has been initialized.\n");

            myDub = computeHotPlate(myDub, levelOfAccuracy);//compute the array

            myScan = new Scanner(System.in);//refresh scanner to clear out any previous values
            System.out.print("Please enter the name and location of the file you would like to create minus its extension: ");
            answer = myScan.next();

            writeToFile(answer, myDub);//write the array to the file specified and print the array to the screen

            myScan = new Scanner(System.in);//refresh scanner to clear out any previous values
            System.out.print("Run program again(yes/no)? ");
            answer = myScan.next();
            System.out.print("\n");

        }while(answer.equalsIgnoreCase("yes")||answer.equalsIgnoreCase("y"));//if user answers yes, run program again
    }

    /**
     *
     * @param outerSize Size of parent array.
     * @param innerSize Size of child array.
     * @return Returns an initalized 2D Array of doubles.
     */
    public static double[][] initDblArray(int outerSize, int innerSize)
    {
        double[][] initDub = new double[outerSize][innerSize];

        for(int outer = 0; outer < outerSize; outer++)//loop through the array and initialize each cell to either 0.0 or 100.0
        {
            for (int inner = 0; inner < innerSize; inner++)
            {
                if((outer == 0 && inner == 0) || (outer == outerSize-1 && inner == innerSize-1) || (outer == 0 && inner == innerSize-1))
                {
                    initDub[outer][inner] = 0.0;
                }
                else if((inner > 0 && inner <= innerSize) && (outer == 0 || outer == outerSize-1))
                {
                    initDub[outer][inner] = 100.0;
                }
            }
        }
        return initDub;
    }

    /**
     *
     * @param myDub 2D double array to compute
     * @param levelOfAccuracy Determines how finite the program should compute the value of each array cell.
     * @return Returns a 2D double array with the same dimensions as the array input into the method
     * except the returned array has been computed.
     */
    public static double[][] computeHotPlate(double[][] myDub, double levelOfAccuracy)
    {
        double[][] rtrnDub = myDub;
        int outerSize = myDub.length, innerSize = myDub[0].length, outerMiddle = myDub.length/2-1, innerMiddle = myDub[0].length/2-1;
        int iterations = 0;
        //boolean computeAgain = true;

        if(0 != myDub.length%2)//if the array has an odd number of members in its first dimension, the middle of the array should be equal to the length of the array divided by two plus one
        {
            outerMiddle++;
        }
        if(0 != myDub[0].length%2)//if the array has an odd number of members in its second dimension, the middle of the array should be equal to the length of the array divided by two plus one
        {
            innerMiddle++;
        }

        
        //while(computeAgain == true)
        double maxChange;
        do
        {
            int outer, inner;//since we have two for-loops that use the same variables they must be declared outside of both loops
            maxChange = 0.0;
            iterations++;

            /*This first set of nested for loops computes the average of each
             cell once; if the parent while loop iterates again then this for
             loop will iterate again, computing and updating all the cells.*/
            for(outer = 1; outer < outerSize-1; outer++)
            {
                for(inner = 1; inner < innerSize-1; inner++)
                {
                    double tempDub = rtrnDub[outer][inner];
                    rtrnDub[outer][inner] = ((rtrnDub[outer - 1][inner])+(rtrnDub[outer + 1][inner])+(rtrnDub[outer][inner - 1])+(rtrnDub[outer][inner + 1]))/4;

                    if(maxChange <  rtrnDub[outer][inner] - tempDub){maxChange = rtrnDub[outer][inner] - tempDub;}
                }
            }

            /*The following set of nested for-loops works through the entire
             array to see if any cell changes more than 0.1 degree, if so then
             the parent while loop will iterate again and again until this loop
             reports that a member of the array changes less than 0.1 degree*/
            /*computeAgain = false;
            for(outer = 1; outer < outerSize-1; outer++)
            {
                for(inner = 1; inner < innerSize-1; inner++)
                {
                    if(levelOfAccuracy < ((rtrnDub[outer - 1][inner])+(rtrnDub[outer + 1][inner])+(rtrnDub[outer][inner - 1])+(rtrnDub[outer][inner + 1]))/4 - rtrnDub[outer][inner])
                    {
                        computeAgain = true;
                    }
                }
            }*/
        }while(maxChange > levelOfAccuracy);

        System.out.print("Array has been computed.\nComputation iterations: "+ iterations + "\n");
        return rtrnDub;
    }


    /**
     *
     * @param fileName The location specified by the user to save the file.
     * @param dblArray The array to write to file.
     * @param reverse Reverse the write order of the array.
     * @throws FileNotFoundException Throws an error if the location specified
     * to write the new file does not exist. Should still allow proper execution
     * of the application.
     */
    public static void writeToFile(String fileName, double[][] dblArray) throws FileNotFoundException
    {
        try//try to write the data to file
        {
            PrintWriter out = new PrintWriter(fileName + ".csv");
            int place = 0;

            place = dblArray.length;
            for(int x = 0; x < place; x++)
            {
                double[] tempArray = dblArray[x];
                int chldArryPlace = dblArray[x].length;
                for(int i = 0; i < chldArryPlace; i++)
                {
                    out.printf("%3.1f,",tempArray[i]);
                }
                out.print("\n");
            }
            out.close();
            printFParray(dblArray);
            System.out.print("Array successfully written to file.\n");
        }
        catch(FileNotFoundException e)//if the user enters a non-existent location, throw an error.
        {
            System.out.print("\nYou have received the following error: \n\n" +
                    "\t" + e + "\n\n"
                    + "Please enter a location that exists.\n");
        }
        return;
    }

    /**
     * Prints the given 2d array of doubles to the screen.
     * @param myDub The 2D array of doubles to be printed.
     */
    public static void printFParray(double[][] myDub)
    {
            int place = 0;

            place = myDub.length;
            for(int x = 0; x < place; x++)
            {
                double[] tempArray = myDub[x];
                int chldArryPlace = myDub[x].length;
                for(int i = 0; i < chldArryPlace; i++)
                {
                    System.out.printf("%6.1f,",tempArray[i]);
                }
                System.out.print("\n");
            }
    }

}