
#include "PokerTable.h"

const int NotUsed = system("color 20"); //Задаем цвет для фона всей консоли

void SetColor(ConsoleColor text, ConsoleColor background);




int main()
{
	srand(time(0));
	SetColor(White, Green);

	PokerTable PT;

	PT.DoGAME();


	cout << endl;
}