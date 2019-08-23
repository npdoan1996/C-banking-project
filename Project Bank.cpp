//============================================================================
// Name        : CECS275project.cpp
// Author      : Nguyen Doan(017474221) and Kay Luu
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <iomanip>
using namespace std;

// ==========================================================================
//	genericAccount class													=
// ==========================================================================
class genericAccount
{
protected:
	int		numOfDeposits,
		 	numOfWithdrawals;
	double 	balance,
			interestRate,
		 	monthlyInEarned,
			monthlyBalance,
		 	beginBalance,
		 	totalDeposit,
		 	totalWithdrawal,
			serviceCharge;
public:

	genericAccount(double bal = 0,double iR = 0);
	virtual ~genericAccount();
	void GetBalance() const {
		cout << "The balance is $" <<  balance;
	}
	virtual void Deposit(double d);
	virtual void Withdraw(double w);
	virtual void CalcInt();
	virtual void monthlyProc();
	virtual void Statistics();
};

// ==========================================================================
//	genericAccount class functions											=
// ==========================================================================

	genericAccount::genericAccount(double bal,double iR)
	{
		balance = beginBalance = monthlyBalance = bal;
		interestRate = iR;
		numOfDeposits = numOfWithdrawals = monthlyInEarned = totalDeposit = totalWithdrawal = serviceCharge= 0;
	}

	genericAccount::~genericAccount()
	{

	}

	void genericAccount::Deposit(double d)
		{
			balance += d;
			numOfDeposits++;
			totalDeposit += d;
		}

	void genericAccount::Withdraw(double w)
		{
			balance -= w;
			numOfWithdrawals++;
			totalWithdrawal += w;
		}

	void genericAccount::CalcInt()
		{
			monthlyInEarned = (balance * interestRate) / 12;
			balance += monthlyInEarned;
		}

	void genericAccount::monthlyProc()
		{
			CalcInt();
			numOfWithdrawals = numOfDeposits = serviceCharge = 0;
		}

	void genericAccount::Statistics()
		{
			cout << setprecision(2) << fixed;
			cout << "Account Opening Balance:   $" << beginBalance << endl;
			cout << "Monthly Balance:	   $" << monthlyBalance << endl;
			cout << "Total deposit amount:	   $" << totalDeposit << endl;
			cout << "Monthly Deposit: 	   " << numOfDeposits << endl;
			cout << "Total withdrawal amount:   $" << totalWithdrawal << endl;
			cout << "Monthly Withdrawal: 	   " << numOfWithdrawals << endl;
			//specified monthlyProc function since it is an overloaded function. Will run neither if not specified.
			genericAccount::monthlyProc();
			cout << "Ending Monthly Balance:	   $" << balance << endl;
			monthlyBalance = balance;

		}
// ==========================================================================
//	savingAccount class 													=
// ==========================================================================
class savingAccount : public genericAccount
{
private:
	bool 	status;
	void 	CheckStatus()
	{
		if (balance < 25)
		{
			status = false;
		}
		else
		{
			status = true;
		}
	}
public:
	savingAccount(double ba = 0, double iR = 0) : genericAccount(ba, iR){
		CheckStatus();
	}
	void Withdraw();
	void Deposit();
	void monthlyProc();
	void Statistics();
};

// ==========================================================================
//	savingAccount class functions											=
// ==========================================================================

	void savingAccount::Withdraw()
	{
		CheckStatus();
		if (status)
		{
			double w;
			cout << "Enter amount: ";
			cin >> w;
			if (w < balance)
			{
				//monthlyProc function checks before the base function is called so it must takes in account the withdrawal that is about to be made
				monthlyProc();
				genericAccount::Withdraw(w);
			}
			else
			{
				cout << "Not enough money to withdraw in saving account\n";
			}
		}
		else
		{
		cout << "Your account is INACTIVE \n";
		}
	}

	void savingAccount::Deposit()
	{
		double d;
		cout << "Enter Amount: ";
		cin >> d;
		genericAccount::Deposit(d);
		CheckStatus();
	}

	void savingAccount::monthlyProc()
	{
		//see savingAccount::Withdraw() for condition being 3 and not 4.
		if (numOfWithdrawals > 3)
		{
			serviceCharge = numOfWithdrawals  - 3;
			cout << "A service charge of $" << serviceCharge << " will be made to your account \n "
				"at the end of the month for additional withdrawals." << endl;
		}
		CheckStatus();
	}

	void savingAccount::Statistics()
	{
		balance -= serviceCharge;
		genericAccount::Statistics();
		CheckStatus();
	}

// ==========================================================================
//	checkingAccount class 													=
// ==========================================================================

class checkingAccount : public genericAccount
{
public:
	checkingAccount(double ba = 0, double iR = 0): genericAccount(ba, iR){}
	void Withdraw(double w)
	{
		if (balance - w < 0)
		{
			cout << "Not enough money to withdraw in checking account.\n"
					" A service charge of $15 will be made to your account.\n";
			serviceCharge = 15;
			cout << serviceCharge;
			balance -= serviceCharge;
		}
		else
		{
			genericAccount::Withdraw(w);
		}
	}
};


// ==========================================================================
//	Main function												 			=
// ==========================================================================

int main()
{
	int 			response;
	double 			amount;
	savingAccount 	saving(1000, .01);	// initial balance at $1000;	monthly interest rate at 1%
	checkingAccount checking; 			// initial balance at $0; 		monthly interest rate at 0%
	genericAccount *generic = &checking;
	do {
			cout 	<< "\n		Choose the option that you want: \n"
					<< "|===============================================================|\n"
					<< "|	 Savings 		|	Checking		|\n"
					<< "|---------------------------------------------------------------|\n"
					<< "|	1. Deposit		| 	4. Deposit		|\n"
					<< "|	2. Withdrawal 		|	5. Withdrawal		|\n"
					<< "|	3. Monthly Statistics	|	6. Monthly Statistics	|\n"
					<< "|===============================================================|\n"
					<< "Type '0' to exit " << endl;
			cin >> response;

			switch(response)
			{
				case 1:
					saving.Deposit();
					break;
				case 2:
					saving.Withdraw();
					break;
				case 3:
					saving.Statistics();
					break;
				case 4:
					cout << "Enter the amount: ";
					cin >> amount;
					generic->Deposit(amount);
					break;
				case 5:
					cout << "Enter the amount: ";
					cin >> amount;
					checking.Withdraw(amount);
					break;
				case 6:
					generic->Statistics();
					break;
				case 0:
					break;

			default:
				cout << "Invalid choice \n";
			}


	}while (response != 0);

	return 0;
}
