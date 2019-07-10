#pragma once
#include "PokerTable.h"
const int NotUsed = system("color 20"); //Задаем цвет для фона всей консоли

void SetColor(ConsoleColor text, ConsoleColor background);
void SetConsCurPos(short x, short y);

class PrintWorld
{
	int pos;
	int index;

public:
	PrintWorld();
	PrintWorld(int p, int in);
	PrintWorld(const PrintWorld & obj);
	PrintWorld & operator=(const PrintWorld & obj);
	void setPos(int p);
	void setIndex(int in);
	int getPos();
	int getIndex();
	void ShowWorld();
	~PrintWorld();
};

