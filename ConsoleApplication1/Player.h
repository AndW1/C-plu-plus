#pragma once
#include "Pack.h"
class Player
{
	Pack P;
	char *name;//им€ игрока
	int stack_money;//начальный игровой стек
	int bet;//размер ставки
	int status_player;//состо€ние выбора решени€ по комбинации
	int table_status;//определить ход предыдущего
	int MyCombo;
public:
	Player();
	Player(const Player & obj);
	Player & operator=(const Player & obj);
	void setName(char*);
	void takeCard(Card obj);
	void takeMoney(int m);//вз€ть выигрыш
	char * getName();
	void sortCards();
	int Chek_5cards_Combo();
	int Chek_6cards_Combo();
	int Chek_7cards_Combo();
	int WHAT_THE_COMBO();
	void TURN_BRAIN();
	void ClearPlayer();
	void setStackMoney(int m);//с какой суммой вступить в игру
	void setBet(int b);//установить размер ставки
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

