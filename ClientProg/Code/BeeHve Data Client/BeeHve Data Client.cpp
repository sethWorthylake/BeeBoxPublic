// BeeHve Data Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <Windows.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>    

int error = 0;
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::ostream;
using std::fstream;
using std::ios;

HANDLE hSerial;

void connectToBlueTooth(int choice);
string pullFromBluetooth();


int main()
{
	int choice = 0;
	bool correct = false;

	while (!correct)
	{
		std::cout << "What is the outgoing Bluetooth Port?" << endl;
		cin >> choice;

		if (choice > 0)
			correct = true;
	}
	
	connectToBlueTooth(choice);

	string retval = "";
	while(retval == string(""))
		retval = pullFromBluetooth();

	auto start = std::chrono::system_clock::now();
	// Some computation here
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	string filename;
	filename += std::ctime(&end_time);

	for (int ii = 0; ii < filename.size(); ii++)
	{
		if (filename[ii] == ' ')
			filename[ii] = '_';
		else if (filename[ii] == ':')
			filename[ii] = ';';
	}

	filename.pop_back();
	filename += ".txt";

	if (remove(filename.c_str()) == 0)
	{
		std::cout << "File Deleted" << std::endl;
	}
	else
	{
		std::cout << "This will be a new file" << std::endl;
	}

	fstream myfile;

	myfile.open(filename, ios::out | ios::app | ios::binary);

	if (myfile.is_open())
	{
		myfile << retval;

		myfile.close();	
	}
	else
	{
		std::cout << "File Couldnt Open." << std::endl;
	}

	std::cout << "Press A character then Enter To End Prog" << endl;
	cin >> choice;
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

void connectToBlueTooth(int choice)
{
	std::wstring port; //= L"COM";

	if (choice == 1)
		port = L"COM1";
	else if (choice == 2)
		port = L"COM2";
	else if (choice == 3)
		port = L"COM3";
	else if (choice == 4)
		port = L"COM4";
	else if (choice == 5)
		port = L"COM5";
	else if (choice == 6)
		port = L"COM6";
	else if (choice == 7)
		port = L"COM7";
	else if (choice == 8)
		port = L"COM8";
	else if (choice == 9)
		port = L"COM9";
	else if (choice == 10)
		port = L"COM10";
	else if (choice == 11)
		port = L"COM11";
	else if (choice == 12)
		port = L"COM12";
	else if (choice == 13)
		port = L"COM13";
	else if (choice == 14)
		port = L"COM14";
	else if (choice == 15)
		port = L"COM15";
	else if (choice == 16)
		port = L"COM16";

	LPCWSTR comPort = port.c_str();

	
	hSerial = CreateFile(comPort,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	DCB dcbSerialParams = { 0 };
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		//error getting state
		cout << "Error Setting Getting Serial Port State" << endl;
	}

	dcbSerialParams.BaudRate = CBR_38400;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		//error setting serial port state
		cout << "Error Setting Serial Port State" << endl;
	}

	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(hSerial, &timeouts)) {
		cout << "Error Setting the Comm timeouts" << endl;
	}


	if (!SetCommMask(hSerial, EV_RXCHAR))
	{
		cout << "Error Setting the Comm Mask" << endl;
	}

	DWORD dwsize = 10;
	LPCVOID pszBuff[10] = { (char*)'S',(char*)'E',(char*)'T',(char*)'H',(char*)'W' };
	unsigned long dwNumberOfBytesSent = 0;

	while (dwNumberOfBytesSent < dwsize)
	{
		unsigned long dwNumberOfBytesWritten;

		if (WriteFile(hSerial, &pszBuff[dwNumberOfBytesSent], 1, &dwNumberOfBytesWritten, NULL) != 0)
		{
			if (dwNumberOfBytesWritten > 0)
				++dwNumberOfBytesSent;
			else
				cout << "Error State" << endl;
		}
	}
}

string pullFromBluetooth()
{
	int valdex = 0;
	DWORD dwEventMask = { 0 };
	string value;
	std::stringbuf sb;
	std::stringbuf base;
	
	while (string(sb.str()) == string(base.str()))
	{

		if (WaitCommEvent(hSerial, &dwEventMask, NULL))
		{
			char szBuf;
			DWORD dwIncommingReadSize;
			DWORD dwSize = { 0 };

			do
			{
				if (ReadFile(hSerial, &szBuf, 1, &dwIncommingReadSize, NULL) != 0)
				{
					if (dwIncommingReadSize > 0)
					{
						dwSize += dwIncommingReadSize;
						sb.sputn(&szBuf, dwIncommingReadSize);
					}
				}
				
			} while (dwIncommingReadSize > 0);
			
		}
		
		
		//string message;
		if (sb.str() != "")
		{
			std::cout << sb.str();
			value = sb.str();
		}
	}

	return value;
}
