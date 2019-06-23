#include "Bank.h"

CBank::CBank(int mtx)
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
	m_mtx = mtx;
	InitializeCriticalSection(&criticalSection);
}


CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	return client;
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	StartCriticalSection();
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	totalBalance += value;

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance != GetTotalBalance() + value) {
		std::cout << "! ERROR !" << std::endl;
	}

	SetTotalBalance(totalBalance);
	FinishCriticalSection();
}


int CBank::GetTotalBalance()
{
	return m_totalBalance;
}


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations()
{
	Sleep(1000);
}

void CBank::StartCriticalSection() {
	if (m_mtx == 0) {
		EnterCriticalSection(&criticalSection);
	}
	else if (m_mtx == 1) {
		mutex.lock();
	}
}

void CBank::FinishCriticalSection() {
	if (m_mtx == 0) {
		LeaveCriticalSection(&criticalSection);
	}
	else if (m_mtx == 1) {
		mutex.unlock();
	}
}