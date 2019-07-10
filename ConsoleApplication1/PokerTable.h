#pragma once
#include "Player.h"


class PokerTable
{
	Player *masPlayer;//массив игроков
	Pack Dealler;//Крупье - перемешивает и сдает всем карты
	Pack Buffer;//В буфер записываются общие для всех карты
	int size;//количество игроков
	int i;//счутчик раздачи
	int bank;
	int status;//принимает решение игрока
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
	void StartDeal();//раздать всем по две карты
	void SetBank();
	int getBank();//выдать выигрыш игроку
	void SetPlayerBat(int b);
	void MinusBet();
	char * getName();
	void ShowTable();
	void ShowGameTable();
	void ShowDealerPack();
	~PokerTable();
};

