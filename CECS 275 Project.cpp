//============================================================================
// Name        : CECS275project.cpp
// Author      : nguyendoan
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <ctype.h>
using namespace std;

// ==========================================================================
//	genericAccount class													=
// ==========================================================================
class genericAccount
{
protected:
	double	balance;
	int		numOfDeposits;
	int 	numOfWithdrawals;
	double 	interestRate;
	double 	monthlyInEarned;
	double 	beginBalance;
	double 	totalDeposit;
	double 	totalWithdrawal;
	double 	serviceCharge;
public:

	genericAccount(double bal = 0,double iR = 0);
	void GetBalance() const {
		cout << "The balance is $" <<  balance;
	}
	virtual void Deposit(double d);
	virtual void Withdraw(double w);
	virtual void CalcInt();
	virtual void monthlyProc();
	void Statistics() const;
};

// ==========================================================================
//	genericAccount class functions											=
// ==========================================================================

	genericAccount::genericAccount(double bal,double iR)
	{
		balance = beginBalance = bal;
		interestRate = iR;
		numOfDeposits = numOfWithdrawals = monthlyInEarned = totalDeposit = totalWithdrawal = serviceCharge= 0;
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

	void genericAccount::Statistics() const
		{
			cout << "The beginning balance is $" << beginBalance << endl;
			cout << "The total amount of deposits is $" << totalDeposit << endl;
			cout << "The total amount of withdrawals is $" << totalWithdrawal << endl;
			cout << "The ending balance is $" << balance << endl;
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
	void Withdraw(double w);
	void Deposit(double d);
	void monthlyProc();
};

// ==========================================================================
//	savingAccount class functions											=
// ==========================================================================

	void savingAccount::Withdraw(double w)
	{
		if (status)
		{
			if (w < balance)
			{
				genericAccount::Withdraw(w);
			}
			else
			{
				cout << "Not enough money to withdraw in saving account\n";
			}
		}
		else
		{
		cout << "You account is INACTIVE \n";
		}
	}

	void savingAccount::Deposit(double d)
	{
		if (status)
		{
			genericAccount::Deposit(d);
		}
		else
		{
			genericAccount::Deposit(d);
			CheckStatus();
		}
	}

	void savingAccount::monthlyProc()
	{
		if (numOfWithdrawals > 4)
		{
			serviceCharge = numOfWithdrawals  - 4;
		}
		balance -= serviceCharge;
		CheckStatus();
		genericAccount::monthlyProc();
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
			cout << "Not enough money to withdraw in checking account. $15 will be charged as service charge \n";
			serviceCharge = 15;
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
	char 			response;
	double 			amount;
	savingAccount 	saving;
	checkingAccount checking;
	do {
		cout << "Choose the option that you want: \n"
			 << "1. Deposit to saving account \n"
			 << "2. Withdraw from the saving account \n"
			 << "3. Generate monthly statistics for saving account \n"
			 << "4. Deposit to checking account \n"
			 << "5. Withdraw from checking account\n"
			 << "6. Generate monthly statistics for checking account\n"
			 << "Type 'Q' or 'q' to exit " << endl;
		cin >> response;
		genericAccount *generic = &saving;
		response  = toupper(response);
		switch(response)
		{
		case '1':
			cout << "Enter the amount: ";
			cin >> amount;
			generic->Deposit(amount);
			break;
		case '2':
			cout << "Enter the amount: ";
			cin >> amount;
			generic->Withdraw(amount);
			break;
		case '3':
			generic->monthlyProc();
			saving.Statistics();
			break;
		case '4':
			cout << "Enter the amount: ";
			cin >> amount;
			checking.Deposit(amount);
			break;
		case '5':
			generic = &checking;
			cout << "Enter the amount: ";
			cin >> amount;
			generic->Withdraw(amount);
			break;
		case '6':
			checking.monthlyProc();
			checking.Statistics();
			break;
		case 'Q':
			break;
		default:
			cout << "Invalid choice \n";
		}
	} while (response != 'Q');
	return 0;
}
