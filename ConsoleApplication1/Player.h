#pragma once
#include "Pack.h"
class Player
{
	Pack P;
	char *name;//��� ������
	int stack_money;//��������� ������� ����
	int bet;//������ ������
	int status_player;//��������� ������ ������� �� ����������
	int table_status;//���������� ��� �����������
	int MyCombo;
public:
	Player();
	Player(const Player & obj);
	Player & operator=(const Player & obj);
	void setName(char*);
	void takeCard(Card obj);
	void takeMoney(int m);//����� �������
	char * getName();
	void sortCards();
	int Chek_5cards_Combo();
	int Chek_6cards_Combo();
	int Chek_7cards_Combo();
	int WHAT_THE_COMBO();
	void TURN_BRAIN();
	void ClearPlayer();
	void setStackMoney(int m);//� ����� ������ �������� � ����
	void setBet(int b);//���������� ������ ������
	int getBet();
	void setMyCombo(int n);
	int getMyCombo();
	void MinusBet();
	int getStackMoney();
	void setStatusPlayer(int s);
	int getStatusPlayer();
	void setTableStatus(int ts);
	void ShowPlayerCards();
	void SowTwoCards();
	//int & operator[](int);
	~Player();
};

