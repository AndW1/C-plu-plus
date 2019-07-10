#include "PokerTable.h"
#include"PrintWorld.h"
void SetConsCurPos(short x, short y)
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x,y };
	SetConsoleCursorPosition(hConsole, coord);
}

void SetColor(ConsoleColor text, ConsoleColor background);

PokerTable::PokerTable()//По умолчанию устанавливается стол для игры на 4 игрока
{
    size = 4;
	masPlayer = new Player[size];
	int mas_num[13] = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };//13 карт в масти
	char mas_suit[52];//Всего 52 карты
	fstream fs("suit.txt", ios::in);
	if (fs.is_open())
	{
		for (int i1 = 0; i1 < 52; i1++)
		{
			fs >> mas_suit[i1];
		}
		fs.close();
	}
	int j = 0;
	for (int i1 = 0; i1 < 52; i1++)
	{
		if (j == 13)
			j = 0;
		Card b(mas_num[j], mas_suit[i1]);
		Dealler.addCard(b);
		j++;
	}
	masPlayer[0].setName("Player1");
	masPlayer[1].setName("Player2");
	masPlayer[2].setName("Player3");
	i = 0;
	bank = 0;
	status = 0;
	newBet = 0;
}
PokerTable::PokerTable(const PokerTable & obj)
{
	size = obj.size;
	for (int j = 0; j < size; j++)
		masPlayer[j] = obj.masPlayer[j];
	Dealler = obj.Dealler;
	Buffer = obj.Buffer;
	i = obj.i;
	bank = obj.bank;
	 status=obj.status;
	 newBet=obj.newBet;
}
PokerTable & PokerTable::operator=(const PokerTable & obj)
{
	if (this == &obj)
		return *this;
	if (size)
	{
		for (int j = 0; j < size; j++)
			masPlayer[j].ClearPlayer();
	}
	delete[]masPlayer;
	size = obj.size;
	masPlayer = new Player[size];
	for (int j = 0; j < size; j++)
		masPlayer[j] = obj.masPlayer[j];
	Dealler = obj.Dealler;
	Buffer = obj.Buffer;
	i = obj.i;
	bank = obj.bank;
	status = obj.status;
	newBet = obj.newBet;
	return *this;
}
void PokerTable::StartDeal()
{
	i = 0;
	Dealler.ShufflePack();
	int endPack = Dealler.getEndPack();
	
	for (int j=0; j < 2; j++)//2=> раздать по две карты
	{
	 Card tmp = Dealler[endPack - i];
	 masPlayer[0].takeCard(tmp);
	 i++;
	 tmp= Dealler[endPack - i];
	 masPlayer[1].takeCard(tmp);
	 i++;
	 tmp=Dealler[endPack - i];
	 masPlayer[2].takeCard(tmp);
	 i++;
	 tmp = Dealler[endPack - i];
	 masPlayer[3].takeCard(tmp);
	 i++;
	}
	for (int j = 0; j < 4; j++)
		masPlayer[j].sortCards();

 
	for (int j = 0; j < 3; j++)
	{
		Card tmp = Dealler[endPack - i];
		Buffer.addCard(tmp);
		i++;
	}
	Buffer.SortForPoker();
}
void PokerTable::DoGAME()
{
	char select;
	int endGame = 0;
	do {
		char str[50];
		ShowTable();
		cout << "\nInput your name->";
		cin >> str;
		setName(str);
		ShowTable();
		int s;
		do {
			cout << "\n Size of stack money ->";
			cin >> s;
			if (s < 500)
				cout << "ERROR! Stack mast be >=500" ;
		} while (s < 500);
		setPlayersMoney(s);
		ShowTable();
		int bet;
		do {
			cout << "\nIput bet(20/50/100) ->";
			cin >> bet;
		} while (bet !=20 && bet !=50 && bet != 100);
	
	
		int chekEnd = 0;
		do {//Begin Game
			int masChekMoney[4];//проверять у кого сколько банк в конце
			int countMas = 0;
			int count_chek = 0;//усли все пасуют и чек то переход на 6 карт
			int circle = 0;//2круга торговли на 5ти картах

			SetPlayerBat(bet);
			MinusBet();
			ShowTable();
			SetBank();
			ShowTable();

			Dealler.ShufflePack();
			StartDeal();
			ShowGameTable();
			SetColor(Yellow, Green);
			SetConsCurPos(18, 9);
			Buffer.ShowPack();
			SetConsCurPos(20, 11);
			SetColor(Yellow, Green);
			cout << "BANK : " << bank;
			SetColor(White, Green);
			for (int j = 0; j < 3; j++)
			{//дозаписать всем игрокам из буфера по три карты чтобы выбирать комбинацию из 5 карт
				masPlayer[0].takeCard(Buffer[j]);
				masPlayer[1].takeCard(Buffer[j]);
				masPlayer[2].takeCard(Buffer[j]);
				masPlayer[3].takeCard(Buffer[j]);
			}
			/*for (int j = 0; j < size; j++)
				masPlayer[j].sortCards();*///отсортировать
			
			//FIRST RAUND
			do{
			     for (int j = 0; j < 4; j++)
			       {//1
					 if (j == 3)
					 {//for real player
						 int x = masPlayer[j].getStatusPlayer();
						 if (x == -5)//eсли стек пуст
						 {
							 SetConsCurPos(22, 17);
							 SetColor(Yellow, Green);
							 cout << masPlayer[j].getStackMoney();
							 SetColor(White, Green);
							 PrintWorld p(j, masPlayer[j].getStatusPlayer());
							 p.ShowWorld();

							 count_chek--;
							 continue;
						 }
						 else if(x==0)//eсли пас
						 {
							 SetConsCurPos(22, 17);
							 SetColor(Yellow, Green);
							 cout << masPlayer[j].getStackMoney();
							 SetColor(White, Green);
							 PrintWorld p(j, masPlayer[j].getStatusPlayer());
							 p.ShowWorld();
							 count_chek++;
							 continue;
						 }
						 else
						 {
							 SetConsCurPos(1, 22);
							 int s;
							 cout << "Make select->";
							 cin >> s;
							 masPlayer[j].setStatusPlayer(s);
							 PrintWorld p(j, masPlayer[j].getStatusPlayer());
							 p.ShowWorld();
							 if (masPlayer[j].getStatusPlayer() != 1)
							 {
								 bank += masPlayer[j].getBet();
								 masPlayer[j].MinusBet();
							 }
							 newBet = masPlayer[j].getBet();
							 SetPlayerBat(newBet);
							 setTableStatus(status);
							 SetConsCurPos(22, 17);
							 SetColor(Yellow, Green);
							 cout << masPlayer[j].getStackMoney();
							 SetColor(White, Green);
							 continue;
						 }
					 }//end for real player
					 masPlayer[j].TURN_BRAIN();
					 if (masPlayer[j].getStatusPlayer() == -5)
					 {
						 if(j==0)
						 SetConsCurPos(1, 10);
						 if(j==1)
							 SetConsCurPos(22, 2);
						 if(j==2)
							 SetConsCurPos(41, 10);
						 SetColor(Yellow, Green);
						 cout << masPlayer[j].getStackMoney();
						 SetColor(White, Green);
						 count_chek--;
						 PrintWorld p(j, masPlayer[j].getStatusPlayer());
						 p.ShowWorld();
						 continue;
					 }
					  if (masPlayer[j].getStatusPlayer() == 0)//если пас
					  {
						  if (j == 0)
							  SetConsCurPos(1, 10);
						  if (j == 1)
							  SetConsCurPos(22, 2);
						  if (j == 2)
							  SetConsCurPos(41, 10);
						  SetColor(Yellow, Green);
						  cout << masPlayer[j].getStackMoney();
						  SetColor(White, Green);
						  PrintWorld p(j, masPlayer[j].getStatusPlayer());
						  p.ShowWorld();
						  count_chek++;
					  }
				          if (masPlayer[j].getStatusPlayer() != 0)
				              {
							    if (masPlayer[j].getStatusPlayer() == 1)//если чек
							       {
									if (j == 0)
										SetConsCurPos(1, 10);
									if (j == 1)
										SetConsCurPos(22, 2);
									if (j == 2)
										SetConsCurPos(41, 10);
									SetColor(Yellow, Green);
									cout << masPlayer[j].getStackMoney();
									SetColor(White, Green);
									PrintWorld p(j, masPlayer[j].getStatusPlayer());
									p.ShowWorld();
								     count_chek++;
							       }
							    else//иначе принимается ставка и изменяется статус стола
							       {
								status = masPlayer[j].getStatusPlayer();
								PrintWorld p(j, masPlayer[j].getStatusPlayer());
								p.ShowWorld();
									if (masPlayer[j].getStatusPlayer() != 1)
									{
								bank += masPlayer[j].getBet();
								masPlayer[j].MinusBet();
								}
								newBet = masPlayer[j].getBet();
								SetPlayerBat(newBet);
								setTableStatus(status);
								if (j == 0)
									SetConsCurPos(1, 10);
								if (j == 1)
									SetConsCurPos(22, 2);
								if (j == 2)
									SetConsCurPos(41, 10);
								SetColor(Yellow, Green);
								cout << masPlayer[j].getStackMoney();
								SetColor(White, Green);
								
				                  }
					}
				}//1
				 circle++;
				// masPlayer[0].ShowPlayerCards();
				 ShowGameTable();
				// masPlayer[0].ShowPlayerCards();
				 SetColor(Yellow, Green);
				 SetConsCurPos(18, 9);
				 Buffer.ShowPack();
				 SetConsCurPos(20, 11);
				 SetColor(Yellow, Green);
				 cout << "BANK : " << bank;
				 SetColor(White, Green);

				 if (count_chek >= 4 || circle==2)
					 break;

				/* ShowGameTable();
				 SetColor(Yellow, Green);
				 SetConsCurPos(18, 9);
				 Buffer.ShowPack();
				 SetConsCurPos(20, 11);
				 SetColor(Yellow, Green);
				 cout << "BANK : " << bank;
				 SetColor(White, Green);*/
			}while (count_chek <4 || circle<2);//END FIRST RAUND


			//После каждого раунда проверять есть ли желающие дальше играть
			//int countStatus = 0;
			//for (int j = 0; j < size; j++)
			//{
			//	if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
			//		countStatus++;
			//}
			//if (countStatus == 1)
			//{
			//	status = 0;
			//	setTableStatus(status);
			//	for (int j = 0; j < size; j++)
			//		masPlayer[j].setStatusPlayer(-1);
			//	for (int j = 0; j < size; j++)
			//		masPlayer[j].ClearPlayer();
			//	Buffer.ClearPack();
			//	bank = 0;
			//	countMas = 0;
			//	count_chek = 0;
			//	circle = 0;
			//	i = 0;
			//	FindWinner();//определить победителя в раунде
			//	continue;
			//}

			//TURN

			 count_chek = 0;//усли все пасуют и чек то переход на 7 карт
			 circle = 0;//2круга торговли на 6ти картах
			int endPack = Dealler.getEndPack();
			for (int j = 0; j < 4; j++)//выдать всем по одинаковой карте для сравнения
			{//только тем кто не пасует
				if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
					masPlayer[j].takeCard(Dealler[endPack - i]);
			}
		/*	for (int j = 0; j < size; j++)
				masPlayer[j].sortCards();*///отсортировать
			
			Buffer.addCard(Dealler[endPack - i]);
			Buffer.SortForPoker();
			for (int j = 0; j < 4; j++)
			{
				if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
					masPlayer[j].setStatusPlayer(-1);
			}
			ShowGameTable();
			SetColor(Yellow, Green);
			SetConsCurPos(18, 9);
			SetConsCurPos(20, 11);
			SetColor(Yellow, Green);
			cout << "BANK : " << bank;
			SetColor(White, Green);
			SetColor(LightRed, Green);
			SetConsCurPos(19, 8);
			cout << "  TURN";
			SetColor(White, Green);
			SetConsCurPos(19, 9);
				Buffer.ShowPack();
			
			do {//SECOND RAUND
				for (int j = 0; j < 4; j++)
				{//1
					if (j == 3)
					{//for real player
						int x = masPlayer[j].getStatusPlayer();
						if (x == -5)//eсли стек пуст
						{
							SetConsCurPos(22, 17);
							SetColor(Yellow, Green);
							cout << masPlayer[j].getStackMoney();
							SetColor(White, Green);
							PrintWorld p(j, masPlayer[j].getStatusPlayer());
							p.ShowWorld();

							count_chek--;
							continue;
						}
						else if (x == 0)//eсли пас
						{
							SetConsCurPos(22, 17);
							SetColor(Yellow, Green);
							cout << masPlayer[j].getStackMoney();
							SetColor(White, Green);
							PrintWorld p(j, masPlayer[j].getStatusPlayer());
							p.ShowWorld();
							count_chek++;
							continue;
						}
						else
						{
							SetConsCurPos(1, 22);
							int s;
							cout << "Make select->";
							cin >> s;
							masPlayer[j].setStatusPlayer(s);
							PrintWorld p(j, masPlayer[j].getStatusPlayer());
							p.ShowWorld();
							if (masPlayer[j].getStatusPlayer() != 1)
							{
								bank += masPlayer[j].getBet();
								masPlayer[j].MinusBet();
							}
							newBet = masPlayer[j].getBet();
							SetPlayerBat(newBet);
							setTableStatus(status);
							SetConsCurPos(22, 17);
							SetColor(Yellow, Green);
							cout << masPlayer[j].getStackMoney();
							SetColor(White, Green);
							continue;
						}
					}//end for real player
					masPlayer[j].TURN_BRAIN();
					if (masPlayer[j].getStatusPlayer() == -5)
					{
						if (j == 0)
							SetConsCurPos(1, 10);
						if (j == 1)
							SetConsCurPos(22, 2);
						if (j == 2)
							SetConsCurPos(41, 10);
						SetColor(Yellow, Green);
						cout << masPlayer[j].getStackMoney();
						SetColor(White, Green);
						count_chek--;
						PrintWorld p(j, masPlayer[j].getStatusPlayer());
						p.ShowWorld();
						continue;
					}
					// masPlayer[j].TURN_BRAIN();
					if (masPlayer[j].getStatusPlayer() == 0)//если пас
					{
						if (j == 0)
							SetConsCurPos(1, 10);
						if (j == 1)
							SetConsCurPos(22, 2);
						if (j == 2)
							SetConsCurPos(41, 10);
						SetColor(Yellow, Green);
						cout << masPlayer[j].getStackMoney();
						SetColor(White, Green);
						PrintWorld p(j, masPlayer[j].getStatusPlayer());
						p.ShowWorld();
						count_chek++;
					}
					if (masPlayer[j].getStatusPlayer() != 0)
					{
						if (masPlayer[j].getStatusPlayer() == 1)//если чек
						{
							if (j == 0)
								SetConsCurPos(1, 10);
							if (j == 1)
								SetConsCurPos(22, 2);
							if (j == 2)
								SetConsCurPos(41, 10);
							SetColor(Yellow, Green);
							cout << masPlayer[j].getStackMoney();
							SetColor(White, Green);
							PrintWorld p(j, masPlayer[j].getStatusPlayer());
							p.ShowWorld();
							count_chek++;
						}
						else//иначе принимается ставка и изменяется статус стола
						{
							//masPlayer[i].TURN_BRAIN();
							status = masPlayer[j].getStatusPlayer();
							PrintWorld p(j, masPlayer[j].getStatusPlayer());
							p.ShowWorld();
							if (masPlayer[j].getStatusPlayer() != 1)
							{
								bank += masPlayer[j].getBet();
								masPlayer[j].MinusBet();
								newBet = masPlayer[j].getBet();
							}
							SetPlayerBat(newBet);
							setTableStatus(status);
							if (j == 0)
								SetConsCurPos(1, 10);
							if (j == 1)
								SetConsCurPos(22, 2);
							if (j == 2)
								SetConsCurPos(41, 10);
							SetColor(Yellow, Green);
							cout << masPlayer[j].getStackMoney();
							SetColor(White, Green);
						}
					}
				}//1
				circle++;
				ShowGameTable();
				SetColor(Yellow, Green);
				SetConsCurPos(18, 9);
				Buffer.ShowPack();
				SetConsCurPos(20, 11);
				SetColor(Yellow, Green);
				cout << "BANK : " << bank;
				SetColor(White, Green);
				if (count_chek >= 4 || circle == 2)
					break;
				ShowGameTable();
				SetColor(Yellow, Green);
				SetConsCurPos(18, 9);
				Buffer.ShowPack();
				SetConsCurPos(20, 11);
				SetColor(Yellow, Green);
				cout << "BANK : " << bank;
				SetColor(White, Green);
			} while (count_chek <4 || circle<2);//END SECOND RAUND

		//После каждого раунда проверять есть ли желающие дальше играть
			// countStatus = 0;
			// for (int j = 0; j < size; j++)
			// {
			//	 if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
			//		 countStatus++;
			// }
			//if (countStatus == 1)
			//{
			//	status = 0;
			//	setTableStatus(status);
			//	for (int j = 0; j < size; j++)
			//		masPlayer[j].setStatusPlayer(-1);
			//	for (int j = 0; j < size; j++)
			//		masPlayer[j].ClearPlayer();
			//	Buffer.ClearPack();
			//	bank = 0;
			//	countMas = 0;
			//	count_chek = 0;//усли все пасуют и чек то переход на 6 карт
			//	circle = 0;
			//	i = 0;
			//	FindWinner();//определить победителя в раунде
			//	continue;
			//}


											
			//RIVER
			i++;
			count_chek = 0;//усли все пасуют и чек то переход на 7 карт
			circle = 0;//2круга торговли на 6ти картах
			 endPack = Dealler.getEndPack();
			for (int j = 0; j < 4; j++)//выдать всем по одинаковой карте для сравнения
			{//только тем кто не пасует
				if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
					masPlayer[j].takeCard(Dealler[endPack - i]);
			}
			/*for (int j = 0; j < size; j++)
				masPlayer[j].sortCards();*///отсортировать
			for (int j = 0; j < 4; j++)
			{
				if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
					masPlayer[j].setStatusPlayer(-1);
			}
			Buffer.addCard(Dealler[endPack - i]);
			Buffer.SortForPoker();
			ShowGameTable();
			SetColor(Yellow, Green);
			SetConsCurPos(18, 9);
			SetConsCurPos(20, 11);
			SetColor(Yellow, Green);
			cout << "BANK : " << bank;
			SetColor(White, Green);
			SetColor(LightRed, Green);
			SetConsCurPos(19, 8);
			cout << "  RIVER";
			SetColor(White, Green);
			SetConsCurPos(19, 9);
			Buffer.ShowPack();
			
			do {//THIRD RAUND
				for (int j = 0; j < 4; j++)
				{//1
					if (j == 3)
					{//for real player
						int x = masPlayer[j].getStatusPlayer();
						if (x == -5)//eсли стек пуст
						{
							SetConsCurPos(22, 17);
							SetColor(Yellow, Green);
							cout << masPlayer[j].getStackMoney();
							SetColor(White, Green);
							PrintWorld p(j, masPlayer[j].getStatusPlayer());
							p.ShowWorld();

							count_chek--;
							continue;
						}
						else if (x == 0)//eсли пас
						{
							SetConsCurPos(22, 17);
							SetColor(Yellow, Green);
							cout << masPlayer[j].getStackMoney();
							SetColor(White, Green);
							PrintWorld p(j, masPlayer[j].getStatusPlayer());
							p.ShowWorld();
							count_chek++;
							continue;
						}
						else
						{
							SetConsCurPos(1, 22);
							int s;
							cout << "Make select->";
							cin >> s;
							masPlayer[j].setStatusPlayer(s);
							PrintWorld p(j, masPlayer[j].getStatusPlayer());
							p.ShowWorld();
							if (masPlayer[j].getStatusPlayer() != 1)
							{
								bank += masPlayer[j].getBet();
								masPlayer[j].MinusBet();
							}
							newBet = masPlayer[j].getBet();
							SetPlayerBat(newBet);
							setTableStatus(status);
							SetConsCurPos(22, 17);
							SetColor(Yellow, Green);
							cout << masPlayer[j].getStackMoney();
							SetColor(White, Green);
							continue;
						}
					}//end for real player
					masPlayer[j].TURN_BRAIN();
					if (masPlayer[j].getStatusPlayer() == -5)
					{
						if (j == 0)
							SetConsCurPos(1, 10);
						if (j == 1)
							SetConsCurPos(22, 2);
						if (j == 2)
							SetConsCurPos(41, 10);
						SetColor(Yellow, Green);
						cout << masPlayer[j].getStackMoney();
						SetColor(White, Green);
						count_chek--;
						PrintWorld p(j, masPlayer[j].getStatusPlayer());
						p.ShowWorld();
						continue;
					}
					// masPlayer[j].TURN_BRAIN();
					if (masPlayer[j].getStatusPlayer() == 0)//если пас
					{
						if (j == 0)
							SetConsCurPos(1, 10);
						if (j == 1)
							SetConsCurPos(22, 2);
						if (j == 2)
							SetConsCurPos(41, 10);
						SetColor(Yellow, Green);
						cout << masPlayer[j].getStackMoney();
						SetColor(White, Green);
						PrintWorld p(j, masPlayer[j].getStatusPlayer());
						p.ShowWorld();
						count_chek++;
					}
					if (masPlayer[j].getStatusPlayer() != 0)
					{
						if (masPlayer[j].getStatusPlayer() == 1)//если чек
						{
							if (j == 0)
								SetConsCurPos(1, 10);
							if (j == 1)
								SetConsCurPos(22, 2);
							if (j == 2)
								SetConsCurPos(41, 10);
							SetColor(Yellow, Green);
							cout << masPlayer[j].getStackMoney();
							SetColor(White, Green);
							PrintWorld p(j, masPlayer[j].getStatusPlayer());
							p.ShowWorld();
							count_chek++;
						}
						else//иначе принимается ставка и изменяется статус стола
						{
							//masPlayer[i].TURN_BRAIN();
							status = masPlayer[j].getStatusPlayer();
							PrintWorld p(j, masPlayer[j].getStatusPlayer());
							p.ShowWorld();
							if (masPlayer[j].getStatusPlayer() != 1)
							{
								bank += masPlayer[j].getBet();
								masPlayer[j].MinusBet();
							}
							newBet = masPlayer[j].getBet();
							SetPlayerBat(newBet);
							setTableStatus(status);
							if (j == 0)
								SetConsCurPos(1, 10);
							if (j == 1)
								SetConsCurPos(22, 2);
							if (j == 2)
								SetConsCurPos(41, 10);
							SetColor(Yellow, Green);
							cout << masPlayer[j].getStackMoney();
							SetColor(White, Green);

						}
					}
				}//1
				circle++;
				ShowGameTable();
				SetColor(Yellow, Green);
				SetConsCurPos(18, 9);
				Buffer.ShowPack();
				SetConsCurPos(20, 11);
				SetColor(Yellow, Green);
				cout << "BANK : " << bank;
				SetColor(White, Green);
				if (count_chek >= 4 || circle == 2)
					break;
				/*ShowGameTable();
				SetColor(Yellow, Green);
				SetConsCurPos(18, 9);
				Buffer.ShowPack();
				SetConsCurPos(20, 11);
				SetColor(Yellow, Green);
				cout << "BANK : " << bank;
				SetColor(White, Green);*/
			} while (count_chek <4 || circle<2);//END THIRD RAUND

			FindWinner();//определить победителя в раунде




			
			for (int j = 0; j < 4; j++)//Поврить наличие денег. Если только у одного->выход
				masChekMoney[j] = masPlayer[j].getStackMoney();
			int count = 0;
			for (int j = 0; j < 4; j++)
			{
				if (masChekMoney[j] != 0)
					count++;
			}
			if (count == 1)
			{
				chekEnd = 1;
				break;
			}
			status = 0;
			setTableStatus(status);
			for (int j = 0; j < size; j++)
				masPlayer[j].setStatusPlayer(-1);
			for (int j = 0; j < size; j++)
				masPlayer[j].ClearPlayer();
			Buffer.ClearPack();
			bank = 0;
			 countMas = 0;
			 count_chek = 0;//eсли все пасуют и чек то переход на 6 карт
			 circle = 0; 
			 i = 0;

			
		} while (chekEnd != 1);//End Game

		for (int j = 0; j < 4; j++)//Поврить наличие денег. Если только у одного->выход
			
			if (masPlayer[j].getStackMoney())
			{
				SetConsCurPos(1, 20);
				cout << "\n\tWinner " << masPlayer[j].getName() << "   Stack = " << masPlayer[j].getStackMoney() << endl;
				Sleep(500);
		    }


		cout << "\nOne more game ? (Y/N)->";
		cin >> select;
		if (select != 'y' && select != 'Y')
			endGame = 1;
	} while (endGame != 1);
}
void PokerTable::FindWinner()//определить победителя в раунде
{
	
	int countStatus = 0;
	for (int j = 0; j < size; j++)
	{
		if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
			countStatus++;
	}
	if (countStatus == 1)
	{
		for(int j=0; j<size; j++)
			if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
			{
				//cout << "WIN";
				masPlayer[j].takeMoney(bank);
				break;
			}
		return;
	}
	if (countStatus == 2)
	{
		int mas[2];
		int j1 = 0;
		for (int j = 0; j<size; j++)
			if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
			{
				mas[j1] = masPlayer[j].getMyCombo();
				j1++;
			}
		if (mas[0] == mas[1])
		{
			int b = bank / 2;
			for (int j = 0; j<size; j++)
				if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
				{
					masPlayer[j].takeMoney(b);
				}
			return;
		}
		int x = mas[0] > mas[1] ? mas[0] : mas[1];
		for (int j = 0; j<size; j++)
			if (x == masPlayer[j].getMyCombo())
			{
				masPlayer[j].takeMoney(bank);
			}
		return;
	}
	if (countStatus == 3)
	{
		int mas[3];
		int j1 = 0;
		for (int j = 0; j<size; j++)
			if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
			{
				mas[j1] = masPlayer[j].getMyCombo();
				j1++;
			}
		if (mas[0] == mas[1] && mas[0] == mas[2])
		{
			int b = bank / 3;
			for (int j = 0; j<size; j++)
				if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
				{
					masPlayer[j].takeMoney(b);
				}
			return;
		}
		int x1 = mas[0] > mas[1] ? mas[0] : mas[1];
		int x = mas[2] > x1 ? mas[2] : x1;
		for (int j = 0; j<size; j++)
			if (x == masPlayer[j].getMyCombo())
			{
				masPlayer[j].takeMoney(bank);
			}
		return;
	}
	if (countStatus == 4)
	{
		int mas[4];
		int j1 = 0;
		for (int j = 0; j<size; j++)
			if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
			{
				mas[j1] = masPlayer[j].getMyCombo();
				j1++;
			}
		if (mas[0] == mas[1] && mas[0] == mas[2] && mas[0]==mas[3])
		{
			int b = bank / 4;
			for (int j = 0; j<size; j++)
				if (masPlayer[j].getStatusPlayer() != -5 && masPlayer[j].getStatusPlayer() != 0)
				{
					masPlayer[j].takeMoney(b);
				}
			return;
		}
		int x1 = mas[0] > mas[1] ? mas[0] : mas[1];
		int x2 = mas[2] > mas[3] ? mas[2] : mas[3];
		int x = x1 > x2 ? x1 : x2;
		for (int j = 0; j<size; j++)
			if (x == masPlayer[j].getMyCombo())
			{
				masPlayer[j].takeMoney(bank);
			}
		return;
	}
}
void PokerTable::setPlayersMoney(int m)
{
	for (int j = 0; j < size; j++)
	{
		masPlayer[j].setStackMoney(m);
	}
}
void PokerTable::MinusBet()
{
	for (int j = 0; j < size; j++)
		masPlayer[j].MinusBet();
}
void PokerTable::SetPlayerBat(int b)
{
	for (int j = 0; j < size; j++)
		masPlayer[j].setBet(b);
}
void PokerTable::setTableStatus(int st)
{
	for (int j = 0; j < size; j++)
		masPlayer[j].setTableStatus(st);
}
void PokerTable::SetBank()
{
	for (int j = 0; j < size; j++)
		bank += masPlayer[j].getBet();
}
int PokerTable::getBank()
{
	return bank;
}
Player & PokerTable::operator[](int pos)
{
	return masPlayer[pos];
}
void PokerTable::setName(char * str)
{
	masPlayer[size - 1].setName(str);
}

char * PokerTable::getName()
{
	return masPlayer[size - 1].getName();
}

void PokerTable::Shuffle()
{
	Dealler.ShufflePack();
}
void PokerTable::ShowTable()
{
	system("cls");
	SetConsCurPos(1, 9);
	cout << masPlayer[0].getName();
	SetConsCurPos(1, 10);
	SetColor(Yellow, Green);
	cout << masPlayer[0].getStackMoney();
	SetColor(White, Green);

	SetConsCurPos(22, 1);
	cout << masPlayer[1].getName();
	SetConsCurPos(22, 2);
	SetColor(Yellow, Green);
	cout << masPlayer[1].getStackMoney();
	SetColor(White, Green);

	SetConsCurPos(41, 9);
	cout << masPlayer[2].getName();
	SetConsCurPos(41, 10);
	SetColor(Yellow, Green);
	cout << masPlayer[2].getStackMoney();
	SetColor(White, Green);

	SetConsCurPos(22, 16);
	cout << masPlayer[3].getName();
	SetConsCurPos(22, 17);
	SetColor(Yellow, Green);
	cout << masPlayer[3].getStackMoney();
	SetColor(White, Green);

	SetConsCurPos(62, 1);
	cout << "CHOICE";
	SetConsCurPos(60, 3);
	cout << "6 - all in";
	SetConsCurPos(60, 4);
	cout << "5 - re raise";
	SetConsCurPos(60, 5);
	cout << "4 - raise";
	SetConsCurPos(60, 6);
	cout << "3 - call";
	SetConsCurPos(60, 7);
	cout << "2 - bet";
	SetConsCurPos(60, 8);
	cout << "1 - chek";
	SetConsCurPos(60, 9);
	cout << "0 - pass";
	
	SetConsCurPos(0, 20);
}
void PokerTable::ShowGameTable()
{
	system("cls");
	SetConsCurPos(1, 9);
	cout << masPlayer[0].getName();
	SetConsCurPos(1, 10);
	SetColor(Yellow, Green);
	cout << masPlayer[0].getStackMoney();
	SetColor(White, Green);
	SetConsCurPos(1, 11);
	masPlayer[0].SowTwoCards();

	SetConsCurPos(22, 1);
	cout << masPlayer[1].getName();
	SetConsCurPos(22, 2);
	SetColor(Yellow, Green);
	cout << masPlayer[1].getStackMoney();
	SetColor(White, Green);
	SetConsCurPos(22, 3);
	masPlayer[1].SowTwoCards();

	SetConsCurPos(41, 9);
	cout << masPlayer[2].getName();
	SetConsCurPos(41, 10);
	SetColor(Yellow, Green);
	cout << masPlayer[2].getStackMoney();
	SetColor(White, Green);
	SetConsCurPos(41, 11);
	masPlayer[2].SowTwoCards();
	//masPlayer[2].ShowPlayerCards();
	SetConsCurPos(22, 16);
	cout << masPlayer[3].getName();
	SetConsCurPos(22, 17);
	SetColor(Yellow, Green);
	cout << masPlayer[3].getStackMoney();
	SetColor(White, Green);
	SetConsCurPos(22, 18);
	masPlayer[3].SowTwoCards();

	

	SetConsCurPos(62, 1);
	cout << "CHOICE";
	SetConsCurPos(60, 3);
	cout << "6 - all in";
	SetConsCurPos(60, 4);
	cout << "5 - re raise";
	SetConsCurPos(60, 5);
	cout << "4 - raise";
	SetConsCurPos(60, 6);
	cout << "3 - call";
	SetConsCurPos(60, 7);
	cout << "2 - bet";
	SetConsCurPos(60, 8);
	cout << "1 - chek";
	SetConsCurPos(60, 9);
	cout << "0 - pass";
	SetConsCurPos(0, 20);
}

void PokerTable::ShowDealerPack()
{
	Dealler.ShowPack();
	cout << endl;
}
PokerTable::~PokerTable()
{
	if (size)
	{
		for (int j = 0; j < size; j++)
			masPlayer[j].ClearPlayer();
	}
		delete[]masPlayer;
}
