/*=====================================================================================================================================
FileName: Le_LongDiv_Oct2018.c
FileType: C Source File
Author : Dung Le
Created On : 12/1/2018 9:12:00 PM
Last Modified On : 12/2/2018 10:32:00 PM
Description : Calculates yearsmonthly payment
Editor: Notepad++ Ver. 7.5.9
Complier: Raspbian 6.3.0
Kernel: Linux raspberrypi 4.9.59-v7+
=====================================================================================================================================*/

#include <stdio.h>
#include <math.h> //pow function

/*
	Presents user with two options 
*/
void options(int *choice)
{
	printf("What do you want to do today?\n");
	printf("1. Calculate total amount of time to pay off loan given your desired monthly payment amount\n");
	printf("2. Calculate monthly payment knowing loan amount and total time to pay off loan\n");
	printf("Please enter 1 or 2: ");
	scanf(" %d", choice);
}	

/*
	Gathers total loan amount, interest rate, desired monthly payment
*/
void gather_info_time(float *total, float *interest, float *monthly)
{
	printf("\nHow much is your total loan? ");
	scanf(" %f", total);	//Scan for total loan value
	printf("\nWhat is the percentage of yearly interest of your bank? ");
	scanf(" %f", interest);	//Scan for yearly interest rate
	printf("\nHow much do you want your monthly payment to be? ");
	scanf(" %f", monthly);	//Scan for desired monthly payment
}

/*
	Finds corresponding amount of time it takes to pay off loan
*/
int months_finder(float total_loan, float interest_rate, float monthly_payment)
{
	int months = 0;
	float years;
	float principal;
	
	interest_rate /= 100;	//Interest rate percentage/100 = decimal value
	//If monthly payment is less than monthly interest rate, loan can never be paid off
	if(monthly_payment - total_loan * interest_rate/12 < 0){
		printf("You'll never be able to pay off your loan\n");
		return 0;
	}
	//Finding month count until loan is paid off
	do{
		principal = monthly_payment - total_loan * interest_rate/12;
		total_loan = total_loan - principal;
		months++;
	} while(total_loan > monthly_payment);
	years = months/12.0;
	
	//Prints number of months and translate into years
	printf("It will take %d months to pay off the loan\n", months);
	printf("That's %.2f years\n", years);
	return 0;
}

/*
	Gathers total loan amount, interest rate, loan period
*/
int gather_info_payment(float *total, float *interest, float *years)
{
	printf("\nHow much is your total loan? ");
	scanf(" %f", total); //Scan for total loan value
	printf("\nWhat is the percentage of interest of your bank? ");
	scanf(" %f", interest); //Scan for yearly interest rate
	printf("\nHow many years will it take to pay off your loan? ");
	scanf(" %f", years); //Scan for length of loan period, in years
}	

/*
	Finds corresponding monthly payment
*/
int payment_finder(float total_loan, float interest_rate, float term)
{
	float PMT;
	float bottom;
	
	interest_rate /= 100;
	bottom = pow(1 + (interest_rate/12), -12.0 * term);
	PMT = (total_loan * (interest_rate/12))/(1 - bottom);
	
	printf("\nYour monthly payment is %.2f\n", PMT);
}	

int main()
{
	int choice;
	float total, interest, monthly, term;

	options(&choice);
	
	if (choice == 1){
		gather_info_time(&total, &interest, &monthly);
		months_finder(total, interest, monthly);
	} else{
		gather_info_payment(&total, &interest, &term);
		payment_finder(total, interest, term);
	}	
	return 0;
}