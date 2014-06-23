import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Scanner;

/**
 *
 * @author Ethan D. Estrada
 *
 * Application to compute a fake financial portfolio.
 *
 * CS 142 Lab 5
 */

public class lab_5
{
    static Scanner textScan;
    static double totalValue = 0.0;
    static byte chcking = 0, bnds = 0, stcks = 0, badLine = 0;

    /**
     *
     * @param args
     * @throws FileNotFoundException
     * @throws MalformedURLException
     * @throws IOException
     */
    public static void main(String[] args) throws FileNotFoundException, MalformedURLException, IOException
    {
        Scanner myScan = new Scanner(System.in);

        System.out.print("Please enter the location of your financial portfolio: ");
        parseLine(myScan.nextLine());
        System.out.println("\nThe number of bad lines is " + badLine + ".");
        System.out.printf("%s%.2f%s\n\n", "Your overall total portfolio value is $", totalValue, ".");
    }

    /**
     * Parses through the file provided by the user.
     *
     * @param textFile
     * @throws FileNotFoundException
     * @throws MalformedURLException
     * @throws IOException
     */
    public static void parseLine(String textFile) throws FileNotFoundException, MalformedURLException, IOException
    {
        File thisFile = new File(textFile);
        textScan = new Scanner(thisFile);

        System.out.printf("\n%s%.2f%s\n\n", "Your initial total value is $", totalValue, ".");

        while (textScan.hasNextLine())
        {
            String newLine = textScan.nextLine();
            Scanner lineScan = new Scanner(newLine);
            String nextAcct = lineScan.next();


            if (nextAcct.equalsIgnoreCase("bond"))
            {
                System.out.println("Computing a new bond...");
                computeBond(newLine);
            }
            else if(nextAcct.equalsIgnoreCase("checking"))
            {
                System.out.println("Computing a new checking account...");
                computeChecking(newLine);
            }
            else if(nextAcct.equalsIgnoreCase("stock"))
            {
                System.out.println("Computing a new stock...");
                computeStock(newLine);
            }
            else
            {
                badLine++;
                System.out.println("Current line is not formatted properly...\n");
            }
        }
    }

    /**
     * Computes a bonds as featured in the fake financial portfolio application.
     *
     * @param bondString
     */
    public static void computeBond(String bondString)
    {
        Scanner bondScan = new Scanner(bondString);
        String crrntTkn;

        int year = 0, numYears = 0, wordCount = 0;
        double bondVal = 0.0, bondAPR = 0.0;
        boolean lineGood = true;

        while (bondScan.hasNext() && lineGood)
        {
            wordCount++;

            if(wordCount == 1)
            {
                bondScan.next();
            }
            else if(wordCount == 2)
            {
                crrntTkn = bondScan.next();
            }
            else if(wordCount == 3)
            {
                if (bondScan.hasNextInt())
                {
                    bnds++;
                    year = bondScan.nextInt();
                }
                else
                {
                    badLine++;
                    lineGood = false;
                    System.out.println("That line is not formatted properly.");
                }

            }
            else if(wordCount == 4)
            {
                if (bondScan.hasNextInt())
                {
                    bnds++;
                    bondVal = bondScan.nextInt();
                }
                else
                {
                    badLine++;
                    lineGood = false;
                    System.out.println("That line is not formatted properly.");
                }

            }
            else if(wordCount == 5)
            {
                if (bondScan.hasNextDouble())
                {
                    bnds++;
                    bondAPR = bondScan.nextDouble();
                }
                else
                {
                    badLine++;
                    lineGood = false;
                    System.out.println("That line is not formatted properly.");
                }

            }
            else
            {
                badLine++;
                lineGood = false;
                crrntTkn = bondScan.next();
                System.out.println("This is something that I don't recognize: " + crrntTkn);
            }
        }

        numYears = 2010 - year;

        if (numYears == 0)
        {
            System.out.println("This bond was purchased this year and has not yet accrued any value.");
        }


        
        if(lineGood == false)
        {
            System.out.println("That line is not formatted properly.");
        }
        else
        {
                for (int currentYear = 1; currentYear <= numYears; currentYear++)
            {
                double interest = bondVal * bondAPR;
                bondVal += interest;
                System.out.printf("%4d %10.2f\n", (currentYear + year - 1), bondVal);
            }

            totalValue += bondVal;
        }

        /*for (int currentYear = 1; currentYear <= numYears; currentYear++)
        {
            double interest = bondVal * bondAPR;
            bondVal += interest;
            System.out.printf("%4d %10.2f\n", (currentYear + year - 1), bondVal);
        }

        totalValue += bondVal;*/

        System.out.printf("\n%s%.2f%s\n\n", "Your current total value is $", totalValue, ".");

        return;
    }

    /**
     * Computes stock account as featured in the fake financial portfolio application.
     *
     * @param stockString
     * @throws MalformedURLException
     * @throws IOException
     */
    public static void computeStock(String stockString) throws MalformedURLException, IOException
    {
        Scanner checkScan = new Scanner(stockString);
        String crrntTkn, currentStock;
        double stockVal = 0.0;
        int wordCount = 0, stockAmnt = 0;

        while (checkScan.hasNext())
        {
            wordCount++;

            if(wordCount == 1)
            {
                checkScan.next();
            }
            else if(wordCount == 2)
            {
                stockVal = crrntStockVal(checkScan.next());
            }
            else if(wordCount == 3)
            {
                if (checkScan.hasNextDouble())
                {
                    stcks++;
                    totalValue += (stockVal * checkScan.nextDouble());
                }
                else
                {
                    badLine++;
                    System.out.println("That line is not formatted properly.");
                }

            }
            else
            {
                crrntTkn = checkScan.next();
                System.out.println("This is something that I don't recognize: " + crrntTkn);
            }
        }

        System.out.printf("%s%.2f%s\n\n", "Your current total value is $", totalValue, ".");
        return;
    }

    /**
     * Finds the current value of certain stocks for the fake financial portfolio application.
     *
     * @param stockString
     * @return
     * @throws MalformedURLException
     * @throws IOException
     */
    public static double crrntStockVal(String stockString) throws MalformedURLException, IOException
    {
        URL newConnection = new URL("http://dna.cs.byu.edu/cs142/stocks.txt");
        Scanner stockScan = new Scanner(newConnection.openStream());
        double returnDouble = 0.0;

        while(stockScan.hasNextLine())
        {
            Scanner stockLine = new Scanner(stockScan.nextLine());

            if (stockString.equalsIgnoreCase(stockLine.next().toString()))
            {
                returnDouble = stockLine.nextDouble();
                break;
            }
        }

        return returnDouble;
    }

    /**
     * Computes a checking account as featured in the fake financial portfolio application.
     *
     * @param checkingString
     */
    public static void computeChecking(String checkingString)
    {
        Scanner checkScan = new Scanner(checkingString);
        String crrntTkn;
        int wordCount = 0;

        while (checkScan.hasNext())
        {
            wordCount++;

            if(wordCount == 1)
            {
                checkScan.next();
            }
            else if(wordCount == 2)
            {
                crrntTkn = checkScan.next();
            }
            else if(wordCount == 3)
            {
                if (checkScan.hasNextDouble())
                {
                    chcking++;
                    totalValue += checkScan.nextDouble();
                }
                else
                {
                    badLine++;
                    System.out.println("That line is not formatted properly.");
                }

            }
            else
            {
                crrntTkn = checkScan.next();
                System.out.println("This is something that I don't recognize: " + crrntTkn);
            }
        }

        System.out.printf("%s%.2f%s\n\n", "Your current total value is $", totalValue, ".");
        return;
    }
}