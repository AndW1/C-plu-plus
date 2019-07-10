#pragma once
#include "Card.h"
class Pack//������ ����
{
	Card *masPack;
	int size;
public:
	Pack();
	Pack(const Pack & obj);
	Pack & operator=(const Pack & obj);
	void addCard(Card tmp);//��������� ����� � ������
	void ShufflePack();//������������ �����
	void SortForPoker();//���������� �� ���������� ����� � ����������� �����
	Card & operator[](int);
	void ClearPack();
	void ScrollPack();
	int getEndPack();
	int getSize();
	void ShowOnlyTwo();
	void ShowPack();

	~Pack();
};

