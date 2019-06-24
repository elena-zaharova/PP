#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void InfoHelp()
{
	cout << "Example: PP2.exe <clients count> <number synchronous primitive>" << endl;
	cout << "Numbers synchronous primitive: 0 for Critical Section, 1 for Mutex" << endl;
	cout << "Default: clients count = 2, number synchronous primitive = 0" << endl;
}


int main(int argc, char* argv[])
{
	int count = 0, mutex = 0;
	if(argc == 3)
	{
		count = atoi(argv[1]);
		mutex = atoi(argv[2]);
		if(count < 1)
		{
			cout << "Incorect count of clients" << endl;
			return 1;
		}
		if(mutex < 0 || mutex > 1)
		{
			cout << "Incorect count of synchronous primitive" << endl;
			return 1;
		}
	}
	if (argc == 2) {
		if (argv[1] == "/")
		{
			InfoHelp();
		}
		else
		{
			count = atoi(argv[1]);
			if (count < 1)
			{
				std::cout << "Incorect count of clients";
				return 1;
			}
		}
	}
	if(argc == 1)
	{
		InfoHelp();
		return 1;
	}
	CBank* bank = new CBank(mutex);
	vector<CBankClient> clients;

	for (int i = 0; i < count; i++) {
		CBankClient client = *(bank->CreateClient());
		clients.push_back(client);
	}

	string cmd;
	while (cin >> cmd)
	{
		if (cmd == "exit" || cmd == "quit") {
			std::cout << "Bank total balance: " << bank->GetTotalBalance() << std::endl;
		}

	}

    return 0;
}