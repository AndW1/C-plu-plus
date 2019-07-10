#include "Pack.h"



Pack::Pack()
{
	masPack = nullptr;
	size = 0;
}
Pack::Pack(const Pack & obj)
{
	size = obj.size;
	for (int i = 0; i < size; i++)
		masPack[i] = obj.masPack[i];

}
Pack & Pack::operator=(const Pack & obj)
{
	if (this == &obj)
		return *this;
	if (size)
		ClearPack();
	size = obj.size;
	for (int i = 0; i < size; i++)
		masPack[i] = obj.masPack[i];
	return *this;
}
void Pack::addCard(Card tmp)
{
	if (size == 0)
	{
		masPack = new Card[1];
		masPack[0] = tmp;
		size++;
	}
	else
	{
		Card *mas1 = new Card[size + 1];
		for (int i = 0; i < size; i++)
			mas1[i] = masPack[i];
		mas1[size] = tmp;
		delete[]masPack;
		size++;
		masPack = mas1;
	}
}
void Pack::ShufflePack()//Перетасовать карты
{
	int i = 0;
	int *mas=new int [size];
	bool f = false;
	do
	{
		if (i > size - 1)
			break;
		int x = rand() % size;
		for (int i = 0; i < size; i++)
		{
			if (mas[i] == x)
			{
				f = true;
				break;
			}
			if (f == true)
				break;
		}

		if (f == true)
		{
			f = false;
			continue;
		}
		mas[i] = x;
		i++;
	} while (true);

	Card *buffer = new Card[size];

	for (int i = 0; i < size; i++)
		buffer[i] = masPack[mas[i]];
	delete[]mas;
	delete[]masPack;
	masPack = buffer;
}
void Pack::SortForPoker()//Сортировка по достоинсву карты и старшинству масти
{
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j > i; j--)
		{
			if (masPack[j - 1].getRank() < masPack[j].getRank())
			{
				Card tmp(masPack[j - 1].getRank(), masPack[j - 1].getSuit());
				masPack[j - 1] = masPack[j];
				masPack[j] = tmp;	
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j > i; j--)
		{
			if (masPack[j - 1].getRank() == masPack[j].getRank())
				if (masPack[j - 1].getSuit() > masPack[j].getSuit())
				{
					Card tmp(masPack[j - 1].getRank(), masPack[j - 1].getSuit());
					masPack[j - 1] = masPack[j];
					masPack[j] = tmp;
				}
		}
	}

}
Card & Pack::operator[](int pos)
{
	return masPack[pos];
}
void Pack::ScrollPack()
{
	Card tmp = masPack[0];
	for (int i = 0; i < size; i++)
		masPack[i] = masPack[i + 1];
	masPack[size - 1] = tmp;
}
void Pack::ClearPack()
{
	if (size)
		delete[]masPack;
	masPack = nullptr;
	size = 0;
}
int  Pack::getEndPack()
{
	int end = size - 1;
	return end;
}
int Pack::getSize()
{
	return size;
}
void Pack::ShowPack()
{
	for (int i = 0; i < size; i++)
		masPack[i].Show_Card();
}
void Pack::ShowOnlyTwo()
{
	for (int i = 0; i < 2; i++)
		masPack[i].Show_Card();
}
Pack::~Pack()
{
	if (size)
		delete[]masPack;
}
