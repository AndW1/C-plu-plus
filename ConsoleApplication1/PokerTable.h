#pragma once
#include "Player.h"


class PokerTable
{
	Player *masPlayer;//������ �������
	Pack Dealler;//������ - ������������ � ����� ���� �����
	Pack Buffer;//� ����� ������������ ����� ��� ���� �����
	int size;//���������� �������
	int i;//������� �������
	int bank;
	int status;//��������� ������� ������
	int newBet;
public:
	PokerTable();
	PokerTable(const PokerTable & obj);
	PokerTable & operator=(const PokerTable & obj);
	void FindWinner();
	void Shuffle();
	void setName(char *str);
	void setPlayersMoney(int m);
	void setTableStatus(int st);
	void DoGAME();
	Player & operator[](int);
	void StartDeal();//������� ���� �� ��� �����
	void SetBank();
	int getBank();//������ ������� ������
	void SetPlayerBat(int b);
	void MinusBet();
	char * getName();
	void ShowTable();
	void ShowGameTable();
	void ShowDealerPack();
	~PokerTable();
};

