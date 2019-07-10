#include "Card.h"

const int NotUsed = system("color 20"); //Задаем цвет для фона всей консоли

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}



Card::Card()
{
	rank = 0;
	suit = '0';
}
Card::Card(int num, char s)
{
	rank = num;
	suit = s;
}
Card::Card(const Card & obj)
{
	rank = obj.rank;
	suit = obj.suit;
}
Card & Card::operator=(const Card & obj)
{
	if (this == &obj)
		return *this;
	
	rank = obj.rank;
	suit = obj.suit;
	return *this;
}

void Card::setRank(int num)
{
	rank = num;
}
void Card::setSuit(char s)
{
	suit = s;
}
int Card::getRank()
{
	return rank;
}
char Card::getSuit()
{
	return suit;
}
bool Card::operator<(const Card & obj)
{//Для других игр необходимо сравнивать еще и масть
	if ((rank, obj.rank) < 0)
		return true;
	else
		return false;
}
bool Card::operator>(const Card & obj)
{
	if ((rank, obj.rank) > 0)
		return true;
	else
		return false;
}
bool Card::operator==(const Card & obj)
{
	if ((rank, obj.rank)== 0)
		return true;
	else
		return false;
}
void Card::Show_Card()
{
	char *masSymbol[13] = { "2","3","4","5","6","7","8","9","10","B","D","K","T" };
	char a1 = char(5);
	char a2 = char(6);
	if (suit == a1 || suit == a2)
		SetColor(Black, Green);
	else
		SetColor(LightRed, Green);
	cout << masSymbol[rank] << suit<<" ";
	SetColor(White, Green);
}

Card::~Card()
{
}
