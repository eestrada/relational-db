/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 *
 * 
 * @author Ethan Estrada
 */
public class lab_6
{
    static int emptyLines = 0;
    
    public static void main(String[] args) throws FileNotFoundException
    {
        boolean keepRunning;
        
        System.out.print("**************** Welcome to Ethan's alphabetic name sorting program! ****************\n\n");
        
        do
        {
            Scanner myScan;
            String answer, nameArray[];
            boolean reverse = false, lastFirst = true;

            myScan = new Scanner(System.in);
            System.out.print("\nWould you like me to sort and print your list by last name first(yes/no)? ");
            answer = myScan.next();
            if(0 == answer.compareToIgnoreCase("y") || 0 == answer.compareToIgnoreCase("yes"))
            {
                lastFirst = true;
            }
            else
            {
                lastFirst = false;
            }

            myScan = new Scanner(System.in);//refresh myScan to empty out previous input
            System.out.print("Would you like me to print your list in reverse from Z to A(yes/no)? ");
            answer = myScan.next();
            if(0 == answer.compareToIgnoreCase("yes") || 0 == answer.compareToIgnoreCase("y"))
            {
                reverse = true;
            }

            myScan = new Scanner(System.in);//refresh myScan to empty out previous input
            System.out.print("Please enter the location of the names file that you would like to sort alphabetically: ");
            nameArray = readFile(myScan.nextLine());

            if (lastFirst == true)//if the names are to be in last-name-first order they must first be reversed, then sorted, then formatted for readability
            {
                nameArray = lastAsFirst(nameArray);//swap last name for first name
                nameArray = mergeNsort(nameArray);//sort array according to alphanumeric order
                nameArray = formatArray(nameArray);//format  names as "Last, First"
            }
            else
            {
                nameArray = mergeNsort(nameArray);//sort array according to alphanumeric order by first name first
            }
            myScan = new Scanner(System.in);
            System.out.print("please enter the name of the name and location of the file you word like to create: ");
            answer = myScan.next();

            writeToFile(answer, nameArray, reverse);

            prntStrArray(nameArray, reverse);//print array and reverse it if the user wants it that way

            myScan = new Scanner(System.in);//refresh myScan to empty out previous input
            System.out.print("\nWould you like to read in another file(yes/no)? ");
            answer = myScan.next();
            if(0 == answer.compareToIgnoreCase("yes") || 0 == answer.compareToIgnoreCase("y"))
            {
                keepRunning = true;
            }
            else
            {
                keepRunning = false;
            }
            
        }while(keepRunning);
    }

    public static void writeToFile(String fileName, String[] strArray, boolean reverse) throws FileNotFoundException
    {
        PrintWriter out = new PrintWriter(fileName);
        int place = 0;
        if (reverse)
        {
            for(int i = strArray.length - 1; i >= place; i--)
            {
                out.println((i + 1) + ": " + strArray[i]);
            }
        }
        else
        {
            place = strArray.length;
            for(int i = 0; i < place; i++)
            {
                out.println((i + 1) + ": " + strArray[i]);
            }
        }

        out.close();
        return;

    }


    /**
     * 
     * @param fileStr
     * @throws FileNotFoundException
     */
    public static String[] readFile(String fileStr) throws FileNotFoundException
    {        
        Scanner textScan;
        String[] tempArray = new String[100], nameArray;
        int arrayLngth = 0;
        
        try//if the user enters a bad filename, catch it and tell the user about it
        {
            File thisFile = new File(fileStr);
            textScan = new Scanner(thisFile);
            System.out.print("\n");
        }
        catch(FileNotFoundException e)
        {
            System.out.print("\nYou have received the following error:\n\n"+
                    "\t" + e + ". \n\n" +
                    "Please check to see if the file exists then try again.\n");

            textScan = new Scanner("");
        }        

        while (textScan.hasNextLine())
        {
            tempArray[arrayLngth] = textScan.nextLine();
            arrayLngth++;
        }
        
        nameArray = new String[arrayLngth];//decrease the size of the array to be returned to the size of the incoming array's members
        
        for (int i = 0; i < arrayLngth; i++)//place all the members of the temporary array into the array to be returned
        {
            nameArray[i] = tempArray[i];
        }

       
        return nameArray;
    }

    /**
     * 
     * @param strArray
     * @return
     */
    public static String[] mergeNsort(String[] strArray)
    {
        if (strArray.length <= 1)
        {
            return strArray;
        }
        else
        {
            String[] resultA, resultB, resultFinal;

            if(strArray.length%2 != 0)
            {
                resultA = new String[((strArray.length/2)+1)];
                resultB = new String[(strArray.length)/2];
                resultFinal = new String[strArray.length];
            }
            else
            {
                resultA = new String[((strArray.length)/2)];
                resultB = new String[(strArray.length)/2];
                resultFinal = new String[strArray.length];
            }

            for(int i = 0; i < resultA.length; i++)
            {
                resultA[i] = strArray[i];
            }
            for(int i = resultA.length; i < resultFinal.length; i++)
            {
                resultB[(i - resultA.length)] = strArray[i];
            }

            resultA = mergeNsort(resultA);
            resultB = mergeNsort(resultB);

            resultFinal = mergeFinal(resultA, resultB, ((resultA.length + resultB.length)));

            return resultFinal;
        }
    }

    /**
     * 
     * @param arrayA
     * @param arrayB
     * @return
     */
    public static String[] mergeFinal(String[] arrayA, String[] arrayB, int arrsz)
    {
        String[] mergeResult= new String[arrsz];
        int place = 0;
        
        while(arrayA.length > 0 || arrayB.length > 0)
        {
            if(arrayA.length > 0 && arrayB.length > 0/* && arrayA[0] != null && arrayB[0] != null*/)
            {
                if(0 >= arrayA[0].compareToIgnoreCase(arrayB[0]))
                {
                    String[] tempArray = new String[arrayA.length - 1];

                    mergeResult[place] = arrayA[0];

                    for (int i = 0; i < tempArray.length; i++)
                    {
                      tempArray[i] = arrayA[i + 1];
                    }
                    arrayA = tempArray;
                }
                else
                {
                    String[] tempArray = new String[arrayB.length - 1];

                    mergeResult[place] = arrayB[0];

                    for (int i = 0; i < tempArray.length; i++)
                    {
                      tempArray[i] = arrayB[i + 1];
                    }
                    arrayB = tempArray;
                }

                place++;
            }
            else if (arrayA.length > 0 && arrayA[0] != null)
            {
                String[] tempArray = new String[arrayA.length - 1];

                mergeResult[place] = arrayA[0];

                for (int i = 0; i < tempArray.length; i++)
                {
                  tempArray[i] = arrayA[i + 1];
                }
                arrayA = tempArray;

                place++;
            }
            else if (arrayB.length > 0 && arrayB[0] != null)
            {

                String[] tempArray = new String[arrayB.length - 1];

                mergeResult[place] = arrayB[0];

                for (int i = 0; i < tempArray.length; i++)
                {
                  tempArray[i] = arrayB[i + 1];
                }
                arrayB = tempArray;

                place++;
            }
        }

        return mergeResult;
    }

    /**
     *
     * @param nameArray
     * @return Returns the submitted array with the first and second tokens of
     * each member in the array swapped.
     */
    public static String[] lastAsFirst(String[] nameArray)
    {
        Scanner myScan;
        String first, last, rtrnArray[] = new String[nameArray.length];
        int place = nameArray.length;
        for(int i = 0; i < place; i++)
        {
            myScan = new Scanner (nameArray[i]);
            first = myScan.next();
            last = myScan.next();
            rtrnArray[i] = (last + " " + first);
        }
        return rtrnArray;
    }

    public static String[] formatArray(String[] nameArray)
    {
        Scanner myScan;
        String first, last, rtrnArray[] = new String[nameArray.length];
        int place = nameArray.length;
        for(int i = 0; i < place; i++)
        {
            myScan = new Scanner (nameArray[i]);
            first = myScan.next();
            last = myScan.next();
            rtrnArray[i] = (first + ", " + last);
        }
        return rtrnArray;
    }

    /**
     * 
     * @param strArray
     */
    public static void prntStrArray(String[] strArray, boolean reverse)
    {
        //int place = strArray.length;
        int place = 0;
        if (reverse)
        {
            for(int i = strArray.length - 1; i >= place; i--)
            {
                System.out.println((i + 1) + ": " + strArray[i]);
            }
        }
        else
        {
            place = strArray.length;
            for(int i = 0; i < place; i++)
            {
                System.out.println((i + 1) + ": " + strArray[i]);
            }
        }
        return;
    }

}
