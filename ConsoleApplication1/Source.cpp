
#include "PokerTable.h"

const int NotUsed = system("color 20"); //������ ���� ��� ���� ���� �������

void SetColor(ConsoleColor text, ConsoleColor background);




int main()
{
	srand(time(0));
	SetColor(White, Green);

	PokerTable PT;

	PT.DoGAME();


	cout << endl;
}