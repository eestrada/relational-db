/**
 *
 * @author Ethan Estrada
 * CS 142
 */

/**
 * Code computed pi as 3.141592 and computed pi after 4 million iterations
 */
public class quiz_4_extra_cred
{
    public static void main(String[] args)
    {
        double pi = 1.0;
        //System.out.println("pi equals: " + pi);
        boolean minus = true;

        for (long i = 3; i<4000000; i+=2)
        {
            if(minus == true)
            {
                pi-= (1.0/i);
                minus = false;
            }
            else
            {
                pi+= (1.0/i);
                minus = true;
            }
        }
        pi*=4;
        System.out.print("pi equals: ");
        System.out.printf("%1.6f", pi);
        System.out.println();
    }
}
