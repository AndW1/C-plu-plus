#pragma once
#include "Card.h"
class Pack//колода карт
{
	Card *masPack;
	int size;
public:
	Pack();
	Pack(const Pack & obj);
	Pack & operator=(const Pack & obj);
	void addCard(Card tmp);//добавлять карты в колоду
	void ShufflePack();//Перетасовать карты
	void SortForPoker();//Сортировка по достоинсву карты и старшинству масти
	Card & operator[](int);
	void ClearPack();
	void ScrollPack();
	int getEndPack();
	int getSize();
	void ShowOnlyTwo();
	void ShowPack();

	~Pack();
};

