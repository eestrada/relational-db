
import acm.graphics.*;
import acm.program.*;
import java.awt.*; // Provides colors
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Ethan
 */
public class lab_8_driver extends GraphicsProgram
{
    public static void main(String[] args)
    {
        new lab_8_driver().start(args);
    }

    @Override
    public void run()
    {
    	GCompound composite = new GCompound();   
        Elf myElf = new Elf();
        add(myElf);

        GRect rect2 = new GRect(250, 110, 50, 100);
        add(rect2);
    }

}
