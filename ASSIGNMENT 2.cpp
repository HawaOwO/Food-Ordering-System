/*******************************************************************************/
/* What the program do: Food Ordering System
/* Programmer name: DAYINI AL HAWANI BINTI KHAIRUD-DIN
/* Programmer Matric #:153629
/******************************************************************************/

#include <iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;

//this is global constant variable for column in array 2D
const int COL = 2;
//this is global constant variable for stock number
const double STOC_K = 10;

//function prototype for Manager
void ManagerMain(string[][COL], int, int&, int& , double&, double&, double&, double&, double&, double[]); 
void ManagerMenuPrice(string[][COL],int); 
void AcceptOrders(int&, double&, double&, double&, double&, double&, string[][COL], int);
void NumberCustOrder(int&, int&);
void SalesEachItemAndForADay(double&, double&, double&, double&, double&, string[][COL], int, double[]);
void PopularDish(double&, double&, double&, double&, double&, string[][COL], int);

//function protoype for User
void CustomerMain(int&, int&, double&, double&, double&, double&, double&, string[][COL], int, double[]);
double TotalPayment(int[], int, string[][COL], int, double[]);
int DeliveryTime(int);
double DeliveryPRICE(int);

int main()
{
	int customer = 0; //variable and initialize for number of customer
	int ordertoday = 0; //variable and initialize for number of order
	ifstream namefile;
	char typeOfUser; //variable for type of user
	string line1, line2, line3, line4, line5; //variable for menu name
	string price1, price2, price3, price4, price5; //variable for price of the foods
	string Arr[10][COL];  //array of menu foods and prices
	double ChangePrice[10]; //array of the price of the food

	//integer pass by reference for func  SalesEachItemAndForADay
	double food1 = 0;
	double food2 = 0;
	double food3 = 0;
	double food4 = 0;
	double food5 = 0;

	//loop will repeats as long as the user didnt want to exit	
	do
	{
		cout << "****************************************************************************" << endl;
		cout << "		WELCOME TO NO FOOD NO LIFE RESTAURANT" << endl;
		cout << "****************************************************************************" << endl;
		cout << "****************************************************************************" << endl;
		
		//displaying menu from file
		cout << "MENU\t\t\tPRICE(RM)" << endl<<endl;
		namefile.open("MENU.txt"); //opening the menu file

		if (namefile) //if the file can be open
		{
			//display all the menu and the price of them
			//and store them in the array
			getline(namefile, line1, '\t');
			cout << line1;
			Arr[0][0] = line1;
			namefile >> price1;
			cout << "\t" << price1;
			Arr[0][1] = price1;
			ChangePrice[0] = stod(price1); //to change the string of price to double

			getline(namefile, line2, '\t');
			cout << line2;
			Arr[1][0] = line2;
			namefile >> price2;
			cout << "\t" << price2;
			Arr[1][1] = price2;
			ChangePrice[1] = stod(price2); //to change the string of price to double

			getline(namefile, line3, '\t');
			cout << line3;
			Arr[2][0] = line3;
			namefile >> price3;
			cout << "\t" << price3;
			Arr[2][1] = price3;
			ChangePrice[2] = stod(price3); //to change the string of price to double

			getline(namefile, line4, '\t');
			cout << line4;
			Arr[3][0] = line4;
			namefile >> price4;
			cout << "\t" << price4;
			Arr[3][1] = price4;
			ChangePrice[3] = stod(price4); //to change the string of price to double

			getline(namefile, line5, '\t');
			cout << line5;
			Arr[4][0] = line5;
			namefile >> price5;
			cout << "\t" << price5;
			Arr[4][1] = price5;
			ChangePrice[4] = stod(price5); //to change the string of price to double

			namefile.close(); //close the file
		}
		else //if file cannot be open
			cout << "!!!ERROR OPENING FILE!!!" << endl; //it will display the error message

		cout << endl;
		cout << "****************************************************************************" << endl;
		cout << endl;
		
		//displaying the option for the user 
		cout << "PLEASE STATE TYPE OF USER OR WHERE DO YOU WANT TO GO :" << endl<<endl;
		cout << "\ta) MANAGER- M" << endl; //enter M for manager
		cout << "\tb) CUSTOMER-C" << endl; //enter C for customer
		cout << "\tc) EXIT-E" << endl<<endl; //enter E to exit program
		cout << "WHICH CATEGORY ARE YOU? ";
		cin >> typeOfUser;

		//displaying the error message and ask the user to re-enter the category.
		while (typeOfUser != 'M' && typeOfUser != 'm' && typeOfUser != 'C' && typeOfUser != 'c' && typeOfUser != 'E' && typeOfUser != 'e')
		{
			cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID CATEGORY !!!!!!!!!!!!!!!" << endl;
			cout << "\t\tPLEASE CHOOSE AGAIN : ";
			cin >> typeOfUser;
			cout << endl;
		}

		if (typeOfUser == 'm' || typeOfUser == 'M')
		{
			ManagerMain(Arr, 10,customer,ordertoday, food1, food2, food3, food4, food5, ChangePrice); //the program will go to manager function 
		}
		else if(typeOfUser=='c'||typeOfUser=='C')
		{
			CustomerMain(customer, ordertoday, food1, food2, food3, food4, food5, Arr, 10, ChangePrice); //the program will go to customer function
		}
		
	}

	while (typeOfUser != 'E' && typeOfUser != 'e'); //as long as the user didnt want to exit, it will loop

	cout << "\n****************************************************************************" << endl;
	cout << "		THANK YOU FOR USING OUR PROGRAM <3" << endl;
	cout << "****************************************************************************" << endl;

	//program ends here when the user decides to exit the program, or else it will loop . 

	return 0;
		
}

//function of customers 
void CustomerMain(int& customer2, int& ordertoday2, double& food111, double& food222, double& food333, double& food444, double& food555, string C[][COL], int rowC, double BPRICE[])
{
	int UserMainArrayMenu[100]; //array for customer's order
	int userfood; //variable for what user order
	int count = 0; //count of total order per customer
	char YesOrNoMenu; //variable for the option to order more or not
	char discount; //variable to know customer have discount coupon or not
	char methodPay; //variable for method to pay
	char userChanges; //variable to ask customer wants changes to be prepared or not by the shop
	string CouponCode; //variable of the discount code
	double payment; //variable for customer money 
	double TotalFoodPrice, DeliveryPrice, TotalPrice, balance; //variable for total price of food, delivery charges, price including food price and delivery charges , and the balance
	int DeliveryT; //variable delivery time in minutes
	int status; //variable to know wether the food is still in stock or not
	ofstream userfile;


	cout << "\n****************************************************************************" << endl;
	cout << "		WELCOME TO OUR RESTAURANTS, OUR DEAR CUSTOMERS" << endl;
	cout << "****************************************************************************" << endl;

	userfile.open("USERORDER.txt", ios::app); //open file and make sure any customer's order is add to the end of the file
	do
	{
		cout << "PLEASE ENTER ORDER (ENTER FOOD NUMBER): ";
		cin >> userfood;
		while (userfood != 1 && userfood != 2 && userfood != 3 && userfood != 4 && userfood != 5) //if invalid number is given
		{
			cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID CATEGORY !!!!!!!!!!!!!!!" << endl; //display error message
			cout << "\t\tPLEASE RE-ENTER ORDER(FOOD NUMBER): ";
			cin >> userfood;
			cout << endl;
		}

		UserMainArrayMenu[count] = userfood; //store the order in array
		cout << endl;

		if (userfood == 1)
		{
			if (food111 < STOC_K)
			{
				userfile  << "\n" <<C[0][0]; //display the order name in file
				food111 += 1; //the order of first food will plus by one
				count++; //count of order per customer will plus by one if this food is in stock
				ordertoday2++; //number of order will plus by one for each order that's been made
			}
			else if (food111 >= STOC_K)
			{
				cout << "~~SORRY THIS FOOD IS OUT OF STOCK~~\n" << endl;
			}
		}	
		else if (userfood == 2)
		{
			if (food222 < STOC_K)
			{
				userfile << C[1][0];//display the order name in file
				food222 += 1; //the order of second food will plus by one
				count++; //count of order per customer will plus by one if this food is in stock
				ordertoday2++; //number of order will plus by one for each order that's been made
			}
			else if (food222 >= STOC_K)
			{
				cout << "~~SORRY THIS FOOD IS OUT OF STOCK~~\n" << endl;
			}

		}
		else if (userfood == 3)
		{
			if (food333 < STOC_K)
			{
				userfile << C[2][0]; //display the order name in file
				food333 += 1; //the order of third food will plus by one
				count++; //count of order per customer will plus by one if this food is in stock
				ordertoday2++; //number of order will plus by one for each order that's been made
			}
			else if (food333 >= STOC_K)
			{
				cout << "~~SORRY THIS FOOD IS OUT OF STOCK~~\n" << endl;
			}

		}
		else if (userfood == 4)
		{
			if (food444 < STOC_K)
			{
				userfile << C[3][0]; //display the order name in file
				food444 += 1; //the order of fourth food will plus by one
				count++; //count of order per customer will plus by one if this food is in stock
				ordertoday2++; //number of order will plus by one for each order that's been made

			}
			else if (food444 >= STOC_K)
			{
				cout << "~~SORRY THIS FOOD IS OUT OF STOCK~~\n" << endl;
			}

		}
		else if (userfood == 5)
		{
			if (food555 < STOC_K)
			{
				userfile << C[4][0]; //display the order name in file
				food555 += 1; //the order of fifth food will plus by one
				count++; //count of order per customer will plus by one if this food is in stock
				ordertoday2++; //number of order will plus by one for each order that's been made
			}
			else if (food555 >= STOC_K)
			{
				cout << "~~SORRY THIS FOOD IS OUT OF STOCK~~\n" << endl; 
			}

		}

		cout << "DO YOU WANT TO ORDER MORE?" << endl; //loop if the customer want to order more
		cout << "\tYES-Y\n\tNO-N" << endl;
		cout << "\nCHOICE: ";
		cin >> YesOrNoMenu;
		cout << endl;
		while (YesOrNoMenu != 'Y' && YesOrNoMenu != 'y' && YesOrNoMenu != 'N' && YesOrNoMenu != 'n') //if invalid input
		{
			cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID !!!!!!!!!!!!!!!" << endl; //display error message
			cout << "\t\tDO YOU WANT TO ORDER MORE?" << endl;
			cout << "\n\t\tYES-Y\n\t\tNO-N" << endl;
			cout << "\n\t\tCHOICE: ";
			cin >> YesOrNoMenu;
			cout << endl;
		}
	} while (YesOrNoMenu == 'Y' || YesOrNoMenu == 'y');

	userfile.close();
	customer2++; //number of customer

		cout << "\nYOUR ORDER HAS BEEN ADDED TO CART\n" << endl;
		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
		cout << "			PAYMENT SECTION" << endl;
		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;

		//option if the customer have a discount coupon
		cout << "\n\nDO YOU HAVE A DISCOUNT COUPON?" << endl;
		cout << "\tYES-Y\n\tNO-N" << endl;
		cout << "\nCHOICE: ";
		cin >> discount;

		while (discount != 'Y' && discount != 'y' && discount != 'N' && discount != 'n')
		{
			cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID !!!!!!!!!!!!!!!" << endl; //error message if invalid input
			cout << "\t\tDO YOU HAVE A DISCOUNT COUPON?" << endl;
			cout << "\n\t\tYES-Y\n\t\tNO-N" << endl;
			cout << "\n\t\tCHOICE: ";
			cin >> discount;
			cout << endl;
		}
		TotalFoodPrice = TotalPayment(UserMainArrayMenu, count, C, rowC, BPRICE); //function to count the total food price
		DeliveryT = DeliveryTime(count); //delivery time
		DeliveryPrice = DeliveryPRICE(count); //function to count the delivery price

		//if the customer have discount coupon
		if (discount == 'y' || discount == 'Y')
		{
			cout << "\nPLEASE ENTER THE CODE OF YOUR COUPON: ";
			cin.ignore(); //to clear the buffer that is caused by cin before.
			getline(cin, CouponCode);

			if (CouponCode == "TeN10")
			{
				TotalFoodPrice = 0.9 * TotalFoodPrice; //discount 10 percent of the food price 
			}
			else if (CouponCode == "FrEEd")
			{
				DeliveryPrice = 0;  //no delivery charge( delivery = RM0)
			}
			else if (CouponCode == "F5TY")
			{
				TotalFoodPrice = 0.5 * TotalFoodPrice; //discount 50 percent of the food price 
			}
			else
			{
				cout << "\nINVALID COUPON !!" << endl; //invalid message if the code is not correct
			}
		}
		cout << "\n......................................................................" << endl;
		cout << "\tPLEASE WAIT WHILE WE SORT OUT YOUR ORDER" << endl;
		cout << "......................................................................" << endl;

		TotalPrice = TotalFoodPrice + DeliveryPrice; //total price including food price and delivery charges

		//display all the information about the payment
		//use fixed, showpoint and setprecision to make sure the price is displayed with the cents.
		cout << fixed << showpoint << setprecision(2) << "\t~ FOOD PRICE: $" << TotalFoodPrice << endl;
		cout << "\t~ DELIVERY TIME: " << DeliveryT << " MINUTES" << endl;
		cout << fixed << showpoint << setprecision(2) << "\t~ DELIVERY PRICE: $" << DeliveryPrice << endl;
		cout << fixed << showpoint << setprecision(2) << "\t~ TOTAL PRICE: $" << TotalPrice << endl;

		//customer can choose the method to do the payment
		cout << "PLEASE ENTER THE MODE OF YOUR PAYMENT" << endl;
		cout << "\tCASH - C" << endl; //enter C for cash
		cout << "\tONLINE BANKING - O" << endl; //enter O for online banking
		cout << "METHOD : ";
		cin >> methodPay;
		cout << endl;

		while (methodPay != 'C' && methodPay != 'c' && methodPay != 'O' && methodPay != 'o') //if input is invalid
		{
			cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID CATEGORY !!!!!!!!!!!!!!!" << endl; //display error message
			cout << "\t\tPLEASE ENTER THE MODE OF YOUR PAYMENT" << endl;
			cout << "\t\tCASH - C" << endl;
			cout << "\t\tONLINE BANKING - O" << endl;
			cout << "\t\tMETHOD : ";
			cin >> methodPay;
			cout << endl;
		}

		// if the customer choose to pay by cash, it will ask the customer wether they wants the shop to prepare changes or not.
		if (methodPay == 'C' || methodPay == 'c')
		{
			cout << "DO YOU WANT US TO PREPARE CHANGES?" << endl;
			cout << "\tYES-Y\n\tNO-N" << endl;
			cout << "\nCHOICE: ";
			cin >> userChanges;

			while (userChanges != 'Y' && userChanges != 'y' && userChanges != 'N' && userChanges != 'n') //if invalid character is given
			{
				cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID CATEGORY !!!!!!!!!!!!!!!" << endl; //display error message
				cout << "\t\tDO YOU WANT US TO PREPARE CHANGES?" << endl; 
				cout << "\t\tYES-Y\n\t\tNO-N" << endl;
				cout << "\nCHOICE: ";
				cin >> userChanges;
				cout << endl;
			}

		if (userChanges == 'y' || userChanges == 'Y')
			cout << "\nALRIGHT, WE WILL MAKE SURE THAT WE HAVE CHANGES FOR CASH PAYMENT." << endl;
		else
			cout << "\nTHANK YOU FOR YOUR UNDERSTANDING." << endl;
		}

		//if the customer choose to pay by online banking
		else
		{
			cout << "PLEASE ENTER THE PAYMENT: ";
			cin >> payment;
			while (payment < TotalPrice) //if the payment entered by the customer is less than the total price 
			{
				cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS LESS THAN THE TOTAL PRICE !!!!!!!!!!!!!!!" << endl; //it will display error message 
				cout << "\t\tPLEASE ENTER AGAIN: "; //and ask the user to re-enter the money value
				cin >> payment;
				cout << endl;
			}

		
		cout << "..........................................................................." << endl;
		balance = payment - TotalPrice; //calculate balance
		cout << fixed << showpoint << setprecision(2); //to make sure the value of the money will be displayed with the cents too.
		cout << "YOUR BALANCE IS RM" << balance << endl; //display balance
		}

		cout << "THANK YOUR FOR COMPLETING YOUR ORDER WITH US.\nWE HOPE YOU ENJOY YOUR FOOD <3" << endl; //display thank you message
		cout << "****************************************************************************\n\n" << endl;

	// customer features ends here.

	return;
}


//this is the function of the main manager 
void ManagerMain(string a[][COL], int row, int& customer1, int& ordertoday1, double& food11, double& food22, double& food33, double& food44, double& food55, double APRICE[])
{
	string password; //declare variable of password
	char ManagerMainOption; //declare variable of manager option 
	
	cout << "****************************************************************************" << endl;
	cout <<setw(4)<< "\nPLEASE ENTER YOUR PASSWORD: "; //this is to make sure that only manager can log in and see the features
	cin >> password;
	while (password != "MNG37") //MNG37 is the password
	{
		cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID PASSWORD !!!!!!!!!!!!!!!" << endl; //display error message if its incorrect password
		cout << "\t\tRE-ENTER PASSWORD: ";
		cin >> password;
		cout << endl;
	}

	//display the manager menu and options on what to do
	cout << "\n#WELCOME OUR DEAR MANAGER#\n" << endl;
	cout << "CHOOSE THE OPTIONS OF THE PROGRAM" << endl;
	cout << "\ta) UPDATING THE MENU AND PRICES- A" << endl;
	cout << "\tb) ACCEPTING CUSTOMERS ORDERS- B" << endl;
	cout << "\tc) POPULAR DISH- C" << endl;
	cout << "\td) NUMBER OF CUSTOMERS OF A DAY AND NUMBER OF ORDERS BY CUSTOMERS- D" << endl;
	cout << "\te) SALES FOR EACH ITEM AND TOTAL SALES FOR A DAY- E" << endl;

	cout << "#PLEASE ENTER YOUR OPTION ALPHABET# : "; //enter the option wanted
	cin >> ManagerMainOption;
	cout << endl;
	
	while (ManagerMainOption != 'A' && ManagerMainOption != 'a' && ManagerMainOption != 'B' && ManagerMainOption != 'b'
		  && ManagerMainOption != 'C' && ManagerMainOption != 'c'&& ManagerMainOption != 'D' && ManagerMainOption != 'd' 
		   && ManagerMainOption != 'E' && ManagerMainOption != 'e')
	{
		cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID OPTION !!!!!!!!!!!!!!!" << endl; //display error if the option is invalid/ not available
		cout << "\t\tPLEASE CHOOSE AGAIN : "; //loop will repeats until valid option is given
		cin >> ManagerMainOption;
	}

	//functions for each option/feature that the manager can do. 

	switch (ManagerMainOption)
	{
	case 'A': ManagerMenuPrice(a, 10);
		break;
	case 'a': ManagerMenuPrice(a,10);
		break;
	case 'B': AcceptOrders(ordertoday1, food11, food22, food33, food44, food55, a, 10);
		break;
	case 'b': AcceptOrders(ordertoday1, food11, food22, food33, food44, food55, a, 10);
		break;
	case 'C': PopularDish(food11, food22, food33, food44, food55 ,a, row);
		break;
	case 'c':PopularDish(food11, food22, food33, food44, food55,a, row);
		break;
	case 'D': NumberCustOrder(customer1,ordertoday1);
		break;
	case 'd': NumberCustOrder(customer1, ordertoday1);
		break;
	case 'E':  SalesEachItemAndForADay(food11, food22 , food33 , food44 ,food55, a, row, APRICE );
		break;
	case 'e': SalesEachItemAndForADay(food11, food22, food33, food44, food55, a, row, APRICE);
		break;
	
		cout << "****************************************************************************" << endl;
	}
	
	return;
	//manager function ends here after it's done the option that's been ask.
}

//function for manager to do any changes for menu and price 
void ManagerMenuPrice(string c[][COL], int row1)
{
	int ManagerMenuPriceOption; //variable declaration for the option for manager
	ofstream namefile;
	string updatefood; //variable for the new food name
	string updateprice; //variable for the new price
	double changePrice, newPrice;
	int numberchange; //variable for which menu that want to be changed

	cout << "****************************************************************************" << endl;
	
	cout << "DO YOU WANT TO :" << endl; //option for the manager to update the menu or update price
	cout << "\ta) UPDATE THE MENU- 1" << endl;
	cout << "\tb) UPDATE PRICES- 2" << endl;
	
	cout << "\nWHICH NUMBER (1/2): ";
	cin >> ManagerMenuPriceOption;
	cout << endl;

	while (ManagerMenuPriceOption != 1 && ManagerMenuPriceOption != 2 ) //if other number than 1 and 2 is given
	{
		cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID NUMBER !!!!!!!!!!!!!!!" << endl; //display invalid message
		cout << "\t\tPLEASE CHOOSE AGAIN : ";
		cin >> ManagerMenuPriceOption;
		cout << endl;
	}

	//update the menu

	if (ManagerMenuPriceOption == 1)
	{
		

			namefile.open("MENU.txt");
			cout << "PLEASE ENTER THE NUMBER OF THE MENU YOU WANT TO CHANGE: "; //enter the number of the menu
			cin >> numberchange;
			cout << endl;
			while (numberchange != 1 && numberchange != 2 && numberchange != 3 && numberchange != 4 && numberchange != 5) //if other than 1,2,3,4,5 is given
			{
				cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID !!!!!!!!!!!!!!!" << endl; //display error message
				cout << "PLEASE ENTER THE NUMBER OF THE MENU YOU WANT TO CHANGE: ";
				cin >> numberchange;
				cout << endl;
			}

			if (numberchange == 1) //first menu
			{
				cout << "PLEASE ENTER THE NEW MENU NAME " << endl;
				cin.ignore(); //to clear any buffer
				getline(cin, updatefood); //get the food name
				c[0][0] = updatefood; //store the new menu name in array
				cout << "PRICE: RM ";
				getline(cin, updateprice); //get price
				c[0][1] = updateprice; //store the new price in the array

				//output the new menu to the file
				namefile <<"1)"<< c[0][0] << "\t" << c[0][1]; 
				namefile << c[1][0] << "\t" << c[1][1] ;
				namefile << c[2][0] << "\t" << c[2][1] ;
				namefile << c[3][0] << "\t" << c[3][1] ;
				namefile << c[4][0] << "\t" << c[4][1] ;
				
			}
			else if (numberchange == 2) //second menu
			{
				cout << "PLEASE ENTER THE NEW MENU NAME" << endl;
				cin.ignore(); //to clear any buffer
				getline(cin, updatefood); //get the food name
				c[1][0] = updatefood;	//store the new menu name in array
				cout << "PRICE: RM ";
				getline(cin, updateprice); //get price
				c[1][1] = updateprice;	//store the new price in the array

				//output the new menu to the file
				namefile << c[0][0] << "\t" << c[0][1];
				namefile <<"\n2)"<< c[1][0] << "\t" << c[1][1] ;
				namefile << c[2][0] << "\t" << c[2][1] ;
				namefile << c[3][0] << "\t" << c[3][1] ;
				namefile << c[4][0] << "\t" << c[4][1] ;
			}
			else if (numberchange == 3) //third menu
			{
				cout << "PLEASE ENTER THE NEW MENU NAME" << endl;
				cin.ignore(); //to clear any buffer
				getline(cin, updatefood); //get the food name
				c[2][0] = updatefood;	//store the new menu name in array
				cout << "PRICE: RM ";
				getline(cin, updateprice); //get price
				c[2][1] = updateprice;	//store the new price in the array

				//output the new menu to the file
				namefile << c[0][0] << "\t" << c[0][1] ;
				namefile << c[1][0] << "\t" << c[1][1] ;
				namefile <<"\n3)"<< c[2][0] << "\t" << c[2][1];
				namefile << c[3][0] << "\t" << c[3][1] ;
				namefile << c[4][0] << "\t" << c[4][1] ;
			}
			else if (numberchange == 4) //fourth menu
			{
				cout << "PLEASE ENTER THE NEW MENU NAME" << endl;
				cin.ignore(); //to clear any buffer
				getline(cin, updatefood); //get the food name
				c[3][0] = updatefood;	//store the new menu name in array
				cout << "PRICE: RM ";
				getline(cin, updateprice); //get price
				c[3][1] = updateprice;	//store the new price in the array

				//output the new menu to the file
				namefile << c[0][0] << "\t" << c[0][1] ;
				namefile << c[1][0] << "\t" << c[1][1] ;
				namefile << c[2][0] << "\t" << c[2][1] ;
				namefile <<"\n4)"<< c[3][0] << "\t" << c[3][1] ;
				namefile << c[4][0] << "\t" << c[4][1] ;
			}
			else if (numberchange == 5) //fifth menu
			{
				cout << "PLEASE ENTER THE NEW MENU NAME" << endl;
				cin.ignore(); //to clear any buffer
				getline(cin, updatefood); //get the food name
				c[4][0] = updatefood;	//store the new menu name in array
				cout << "PRICE: RM ";
				getline(cin, updateprice); //get price
				c[4][1] = updateprice;	//store the new price in the array

				//output the new menu to the file
				namefile << c[0][0] << "\t" << c[0][1] ;
				namefile << c[1][0] << "\t" << c[1][1] ;
				namefile << c[2][0] << "\t" << c[2][1] ;
				namefile << c[3][0] << "\t" << c[3][1] ;
				namefile <<"\n5)"<< c[4][0] << "\t" << c[4][1] ;

			}
			
			cout << "\n ~ THE UPDATING MENU IS SUCCESFULLY DONE ~\n" << endl;

		namefile.close(); //close file
	}

	//update the prices

	else
	{

		cout << "WHICH FOOD'S PRICE THAT YOU WANT TO CHANGE(ENTER THE NUMBER OF FOOD)?" << endl; //ask the manager to put the number of the food 
		cin >> changePrice;
		cout << endl;
		while (changePrice != 1 && changePrice != 2 && changePrice != 3 && changePrice != 4 && changePrice != 5) //if invalid input is entered
		{
			cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID !!!!!!!!!!!!!!!" << endl; //display error message
			cout << "\t\tPLEASE CHOOSE AGAIN "<<endl;
			cout << "\t\tWHICH FOOD'S PRICE THAT YOU WANT TO CHANGE(ENTER THE NUMBER)?" << endl; //it will loop until manager enter valid number
			cin >> changePrice;
			cout << endl;
		}
		namefile << fixed << showpoint << setprecision(2); //to make sure the price is displayed with the cents too
		namefile.open("MENU.txt" );

		//rewrite all of the menu food and price with the changes too

		if (changePrice == 1)
		{
			cout << "\tENTER THE NEW PRICE: RM"; //change the first menu's price
			cin >> newPrice;
			c[0][1] = newPrice; //store the update price in the array
			namefile << c[0][0] << "\t" << newPrice ;
			namefile << c[1][0] << "\t" << c[1][1] ;
			namefile << c[2][0] << "\t" << c[2][1];
			namefile  << c[3][0] << "\t" << c[3][1] ;
			namefile  << c[4][0] << "\t" << c[4][1] ;
		}
		else if (changePrice == 2) 
		{
			cout << "\tENTER THE NEW PRICE: RM"; //changes the second menu's price
			cin >> newPrice;
			c[1][1] = newPrice; //store the update price in the array
			namefile << c[0][0] << "\t" << c[0][1];
			namefile  << c[1][0] << "\t" << newPrice ;
			namefile  << c[2][0] << "\t" << c[2][1] ;
			namefile  << c[3][0] << "\t" << c[3][1] ;
			namefile << c[4][0] << "\t" << c[4][1] ;
		}
		else if (changePrice == 3)
		{
			cout << "\tENTER THE NEW PRICE: RM"; //changes the third menu's price
			cin >> newPrice;
			c[2][1] = newPrice; //store the update price in the array
			namefile << c[0][0] << "\t" << c[0][1];
			namefile << c[1][0] << "\t" << c[1][1];
			namefile <<  c[2][0] << "\t" << newPrice ;
			namefile <<  c[3][0] << "\t" << c[3][1] ;
			namefile <<  c[4][0] << "\t" << c[4][1] ;
		}
		else if (changePrice == 4)
		{
			cout << "\tENTER THE NEW PRICE: RM"; //changes the fourth menu's price
			cin >> newPrice;
			c[3][1] = newPrice; //store the update price in the array
			namefile <<  c[0][0] << "\t" <<  c[0][1] ;
			namefile <<  c[1][0] << "\t" << c[1][1];
			namefile <<  c[2][0] << "\t" << c[2][1] ;
			namefile <<  c[3][0] << "\t" <<newPrice;
			namefile  << c[4][0] << "\t" << c[4][1] ;
		}
		else if (changePrice == 5)
		{
			cout << "\tENTER THE NEW PRICE: RM"; //changes the fifth menu's price
			cin >> newPrice;
			c[4][1] = newPrice; //store the update price in the array
			namefile <<  c[0][0] << "\t" <<  c[0][1] ;
			namefile << c[1][0] << "\t" << c[1][1] ;
			namefile <<  c[2][0] << "\t" << c[2][1] ;
			namefile <<  c[3][0] << "\t" << c[3][1] ;
			namefile <<  c[4][0] << "\t" << newPrice ;
		}  
		cout << "\n ~ THE UPDATING PRICE IS SUCCESFULLY DONE ~\n" << endl;

		namefile.close(); //close the file

	}
	
	return;

	//function for updating menu/price ends.
}


//function that allows the manager to accept orders
void AcceptOrders(int& ordertoday3, double& foodAA, double& foodBB, double& foodCC, double& foodDD, double& foodEE, string C[][COL], int rowC)
{
	char Accept; //variable to indicate the manager accept or not the order
	string userorder; //declare variable for order name
	ifstream userfile1;

	userfile1.open("USERORDER.txt"); //opening file of the customer's orders
	cout << "CUSTOMER'S ORDERS THAT ARE IN STOCK: " << endl;
	cout << endl;
	if (userfile1)
	{
		while (getline(userfile1, userorder)) //get all the order's name
		{
			
			cout <<"\t"<< userorder;
			cout << endl;
		}
		userfile1.close();
	}
	
	//display error if its unable to open the file
	else
	{
		cout << "ERROR OPENING FILE" << endl;
	}

	//display the leftover stock for each food
	cout << "\nTHE STOCK REMAINED FOR OUR RESTAURANTS.\n" << endl;	
	// use static cast to display the number of stocks left in int
	cout <<	C[0][0] <<" have " << static_cast<int>(STOC_K - foodAA) << " stocks left." << endl;
	cout << C[1][0] << " have " << static_cast<int>(STOC_K - foodBB) << " stocks left." << endl;
	cout << C[2][0] << " have " << static_cast<int>(STOC_K - foodCC) << " stocks left." << endl;
	cout << C[3][0] << " have " << static_cast<int>(STOC_K - foodDD) << " stocks left." << endl;
	cout << C[4][0] << " have " << static_cast<int>(STOC_K - foodEE) << " stocks left." << endl;

	//display the total order
	cout << "\nTHE CUSTOMER HAVE ORDER " << ordertoday3 << " TOTAL OF FOOD FROM THE MENU." << endl;
	//ask the manager to accept order
	cout << "ACCEPT ORDER(Y/N):";
	cin >> Accept;
	cout << endl;

	while (Accept != 'Y' && Accept != 'y' && Accept != 'N' && Accept != 'n') //if the input entered is invalid
	{
		cout << "\n!!!!!!!!!!!!!!! UH OH! THIS IS INVALID !!!!!!!!!!!!!!!" << endl; // display error message until the manager enter the Y/N
		cout << "\tACCEPT ORDER(Y/N):";
		cin >> Accept;
		cout << endl;
	}
	if (Accept == 'Y' || Accept == 'y')
		cout << "THE ORDER HAS BEEN ACCEPTED\n" << endl; //the order is succesfully accepted
	else
		cout << "THE ORDER HAS BEEN REJECTED\n" << endl; //the order is rejected for some reasons
	return;

}

//functions that will return the total price of the food
double TotalPayment(int aar[], int count1, string B[][COL], int row, double PRICE[])
{
	double total = 0;
	int count2 = count1-1;
	
	//base on the customer's order that is stored in the array, it will add the price of each food that is ordered
	for(int i=0; i<=count2;i++)
	{
		if (aar[i] == 1)
		{
			total += PRICE[0];
		}
		else if (aar[i] == 2)
		{
			total += PRICE[1];
		}
		else if ( aar[i] == 3)
		{
			total += PRICE[2];
		}
		else if(aar[i]==4)
		{
			total += PRICE[3];
		}
		else
		{
			total += PRICE[4];
		}
	}
	return total; //return total price of food in double
}

//function that will return minutes of delivery time in int
int DeliveryTime(int count3)
{
	int deliverytime = 0;
	deliverytime = (count3 + 1) * 5 + 20; //delivery time including the time to prepare the food, and the time to deliver the food
	return deliverytime;
}

// calculate the delivery charges according on how many order is there
double DeliveryPRICE(int count4)
{
	
	double Dprice = 4.50 ; //the basic price of delivery is RM4.50
	if (count4 > 2) //if the order is more than 3
	{
		Dprice += 0.50; //the charges will add an extra charges
	}
	return Dprice;
	//return the delivery charges in double data type
}

//this is the feature of the manager to know the number of order and number of customers for the day
//it will not return any value 
//it have 2 pass by reference variable in its parameter
void NumberCustOrder(int& customer3,int& ordertoday3)
{

	cout << "NUMBER OF ORDERS BY CUSTOMERS TODAY: "<<ordertoday3 <<endl; //display the number of orders by customers
	cout << "NUMBER OF CUSTOMERS FOR THE DAY: "<<customer3 <<endl<<endl;  //display the number of customers
	return;
	//didnt return any value 
}

//this is another feature of the manager to find out the total sales for each item and the total sales for all of the menu.
//this function return nothing. It will just display the information
void SalesEachItemAndForADay(double& fooda, double& foodb, double& foodc, double& foodd, double& foode, string A[][COL], int rowA, double PRICEB[])
{
	//variable to store the sales.
	double pricea, priceb, pricec, priced, pricee; 
	double totalPrice;
	
	//calculations is made for each menu food.
	//it will calculate the number of per food with the price of the food.
	pricea = PRICEB[0] * fooda;
	priceb= PRICEB[1] * foodb;
	pricec = PRICEB[2] * foodc;
	priced = PRICEB[3] * foodd;
	pricee = PRICEB[4] * foode;
	
	//calculate total sales for all of the food.
	totalPrice = pricea + priceb + pricec + priced + pricee;

	//Display the sales in a table form
	cout << showpoint << fixed << setprecision(2) << endl; //to make sure it will displays with the cents.
	cout << "SALES FOR EACH ITEM IN THE MENU IS GIVEN BELOW" << endl;
	cout << "_________________________________" << endl;
	cout << "|MENU\t\t\t| SALES\t |" << endl;
	cout << "|_______________________|________|" << endl;
	cout << "|" <<A[0][0]<<"\t| $ "<< pricea <<" |" ;
	cout << "\n|                       |        |" << A[1][0] << "\t| $ " << priceb << " |" ;
	cout << "\n|                       |        |" << A[2][0] << "\t| $ " << pricec << " |" ;
	cout << "\n|                       |        |" <<A[3][0]<<"\t| $ " << priced << " |" ;
	cout << "\n|                       |        |" <<A[4][0]<<"\t| $ " << pricee << " |" ;
	cout << "\n|_______________________|________|" ;

	//Display the total sales for the day
	cout << "\n\nTOTAL SALES FOR A DAY : $ " << totalPrice << endl<<endl;

	return;
	// the feature ends here and will return to the main function.

}

//this function will display the popular dish base on the number of food that is ordered by the customers.
//this function will not return anything.
// it will only display the information.
void PopularDish(double& foodaa, double& foodbb, double& foodcc, double& fooddd, double& foodee, string BARR[][COL], int row)
{
	cout << "\nDISPLAYING THE POPULAR DISH EVER FOR THE DAY!!" << endl;

	//base on the variables value that are pass by reference, the function can
	//figure out which food have the most order.

	//if the first food have the most order.
	if (foodaa > foodbb && foodaa > foodcc && foodaa > fooddd && foodaa > foodee)
	{
		cout << "\n"<< BARR[0][0]<<" IS THE FAMOUS DISH TODAY.\n" << endl;
	}

	//if the second food have the most order.
	else if (foodbb > foodaa && foodbb > foodcc && foodbb > fooddd && foodbb > foodee)
	{
		cout << "\n" << BARR[1][0] << " IS THE FAMOUS DISH TODAY.\n" << endl;
		
	}

	//if the third food have the most order.
	else if (foodcc > foodbb && foodcc > foodaa && foodcc > fooddd && foodcc > foodee)
	{
		cout << "\n" << BARR[2][0] << " IS THE FAMOUS DISH TODAY.\n" << endl;
	}

	//if the fourth food have the most order.
	else if (fooddd > foodbb && fooddd > foodcc && fooddd > foodaa && fooddd > foodee)
	{
		cout << "\n" << BARR[3][0] << " IS THE FAMOUS DISH TODAY.\n" << endl;
	}

	//if the fifth food have the most order.
	else if (foodee > foodbb && foodee > foodcc && foodee > fooddd && foodee > foodaa)
	{
		cout << "\n" << BARR[4][0] << " IS THE FAMOUS DISH TODAY.\n" << endl;
	}

	//if there is no order yet for the day.
	else
	{
		cout << "\nTHERE'S NO POPULAR DISH YET TODAY.\n" << endl;
	}
	//the function ends here.
}


