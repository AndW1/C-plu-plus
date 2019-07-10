#include "PrintWorld.h"



PrintWorld::PrintWorld()
{
	pos = 0;
	index = 0;
}
PrintWorld::PrintWorld(int p, int in)
{
	pos = p;
	index = in;
}
PrintWorld::PrintWorld(const PrintWorld & obj)
{
	pos = obj.pos;
	index = obj.index;
}
PrintWorld & PrintWorld::operator=(const PrintWorld & obj)
{
	if (this == &obj)
		return *this;
	pos = obj.pos;
	index = obj.index;
	return *this;
}
void PrintWorld::setPos(int p)
{
	pos = p;
}
void PrintWorld::setIndex(int in)
{
	index = in;
}
int PrintWorld::getPos()
{
 return pos;
}
int PrintWorld::getIndex()
{
return index;
}
void PrintWorld::ShowWorld()
{
	SetColor(LightBlue, Green);
	if (pos == 0)
	SetConsCurPos(1, 8);
	if(pos==1)
		SetConsCurPos(22, 0);
	if(pos==2)
		SetConsCurPos(41, 8);
	if(pos==3)
		SetConsCurPos(22, 15);
	if (index == 0)
	{
		cout << "PASS";
		Sleep(1000);
	}
	if (index == 1)
	{
		cout << "CHEK";
		Sleep(1000);
	}
	if (index == 2)
	{
		cout << "BET";
		Sleep(1000);
	}
	if (index == 3)
	{
		cout << "COLL";
		Sleep(1000);
	}
	if (index == 4)
	{
		cout << "RAISE";
		Sleep(1000);
	}
	if (index == 5)
	{
		cout << "RE-RAISE";
		Sleep(1000);
	}
	if (index == 6)
	{
		cout << "ALL-IN";
		Sleep(1000);
	}
	if (index == -5)
	{
		cout << "EMPTY";
		Sleep(1000);
	}
	SetColor(White, Green);
}
PrintWorld::~PrintWorld()
{
}
