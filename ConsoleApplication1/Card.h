#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include<ctime>
#include <Windows.h>
#include <iostream>
using namespace std;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};




class Card
{
  int rank;//достоинство карты
	char suit;//масть карты
public:
	Card();
	Card(int num, char s);
	Card(const Card & obj);
	Card & operator=(const Card & obj);
	void setRank(int num);
	void setSuit(char s);
	int getRank();
	char getSuit();
	bool operator<(const Card & obj);
	bool operator>(const Card & obj);
	bool operator==(const Card & obj);
	void Show_Card();
	~Card();
};

