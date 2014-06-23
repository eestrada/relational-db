import java.util.Scanner;

public class lab_2
{
	public static void main ( String[] args)
		{

		float car_cost_A, car_cost_B, resale_val_A, resale_val_B, gas_price;
		int miles_per_gallon_A, miles_per_gallon_B, miles_per_year;
		
		Scanner response = new Scanner(System.in);
		
		System.out.println("Welcome!");
		
		System.out.print("Please enter your estimated number of miles driven per year: ");
		miles_per_year = response.nextInt();
		
		System.out.print("Please enter the estimated price of a gallon of gas: ");
		gas_price = response.nextFloat();
		
		System.out.print("Please enter the price of car A: ");
		car_cost_A = response.nextFloat();
		
		System.out.print("Please enter the miles per gallon efficiency of car A: ");
		miles_per_gallon_A = response.nextInt();
		
		System.out.print("Please enter the resale value after five years of car A: ");
		resale_val_A = response.nextFloat();
		
		
		
		System.out.print("Please enter the price of car B: ");
		car_cost_B = response.nextFloat();
		
		System.out.print("Please enter the miles per gallon efficiency of car B: ");
		miles_per_gallon_B = response.nextInt();
		
		System.out.print("Please enter the resale value after five years of car B: ");
		resale_val_B = response.nextFloat();		
		
		System.out.print("The total cost of ownership over five years for car A is $");
		System.out.printf("%1.2f", (gas_price / miles_per_gallon_A) * (miles_per_year * 5) + (car_cost_A - resale_val_A));
		System.out.print(" with the cost of gas alone being $");
		System.out.printf("%1.2f", (gas_price / miles_per_gallon_A) * (miles_per_year * 5));
		System.out.println(".");
		
		System.out.print("The total cost of ownership over five years for car B is $");
		System.out.printf("%1.2f", (gas_price / miles_per_gallon_B) * (miles_per_year * 5) + (car_cost_B - resale_val_B));
		System.out.print(" with the cost of gas alone being $");
		System.out.printf("%1.2f", (gas_price / miles_per_gallon_B) * (miles_per_year * 5));
		System.out.print(".");
		}

}
