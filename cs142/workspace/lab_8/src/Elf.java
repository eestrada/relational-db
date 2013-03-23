import acm.graphics.*;
import acm.program.*;
import java.awt.*; // Provides colors

/**
 *
 * @author Ethan
 */
public class Elf extends GraphicsProgram
{
    private GCompound elf_body;
    private GRect body, arm_R, arm_L, leg_R, leg_L, foot_R, foot_L;
    private GArc hat;
    private GOval head;
    
    Elf()
    {
    	Color blue = new Color((float)0.0, (float)0.0, (float)1.0);
        elf_body = new GCompound();
    	leg_R = new GRect(100,100,100,100);
    	leg_R.setFillColor(blue);
    	leg_L = new GRect(100,100,100,100);
    	leg_R.setFillColor(blue);
    	body = new GRect(100,100,100,100);
    	leg_R.setFillColor(blue);
    	arm_R = new GRect(100,100,100,100);
    	leg_R.setFillColor(blue);
    	arm_L = new GRect(100,100,100,100);
    	leg_R.setFillColor(blue);
    	foot_L = new GRect(100,100,100,100);
    	leg_R.setFillColor(blue);
    	foot_L = new GRect(100,100,100,100);
    	leg_R.setFillColor(blue);
    	elf_body.add(body);
    	elf_body.add(leg_R);
    	elf_body.add(leg_L);
    	elf_body.add(arm_R);
    	elf_body.add(arm_L);
    	elf_body.add(foot_R);
    	elf_body.add(foot_L);    	        
    }
    
    public GCompound add()
    {
    	return elf_body;
    }

}
