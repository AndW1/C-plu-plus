#include "Player.h"



Player::Player()
{
	name = _strdup("noname");
	stack_money = 0;
	bet = 0;
	status_player = -1;
	table_status = 0;
	MyCombo = 0;
}
Player::Player(const Player & obj)
{
	name = _strdup(obj.name);
	stack_money = obj.stack_money;
	bet = obj.bet;
	status_player = obj.status_player;
	table_status = obj.table_status;
	MyCombo = obj.MyCombo;
	P = obj.P;
}
Player & Player::operator=(const Player & obj)
{
	if (this == &obj)
		return *this;
	if (name)
		delete[]name;
	if (P.getSize())
		P.ClearPack();
	name = _strdup(obj.name);
	stack_money = obj.stack_money;
	bet = obj.bet;
	status_player = obj.status_player;
	table_status = obj.table_status;
	MyCombo = obj.MyCombo;
	P = obj.P;
	return *this;
}
void Player::TURN_BRAIN()
{
	if (stack_money == 0)//если нечем играть
	{
		status_player = -5;
		bet = 0;
		return;
	}
	if (stack_money / bet <= 4)//если мало фишек то ставится все
	{//ALL IN
		status_player = 6;
		bet = stack_money;
		return;
	}
	if (status_player == 0)
	{//пас
		
		return;
	}
	int combo = WHAT_THE_COMBO();
	if (table_status == 0)
	{
		if (status_player == 3)
		{
			status_player = 1;
			return;
		}
		if (combo == 9 || combo == 8)
		{
			int x = rand() % 2;
			switch (x) {
			case 0:
				bet *= 2;
				status_player = 2;
				break;
			case 1:
				status_player = 2;
				break;
			}
			return;
		}
		if (combo == 7 || combo == 6 || combo == 5 || combo == 4 || combo == 3 || combo == 2)
		{
			status_player = 2;
			return;
		}
		if (combo == 1 || combo == 2 || combo==0)
		{
			int x = rand() %3;//%6
			if (x == 0 || x == 1)
			{
				status_player = 2;
				return;
			}
			if(x==2) //(x == 2 || x == 3 || x == 4 || x == 5)
			{
				status_player = 0;
				return;
			}
		}
	}
	if (table_status == 1)//когда чек
	{
		if (status_player == 1 || status_player == 2 || status_player == 3)
		{
			status_player = 1;
			return;
		}
		if (combo == 9 || combo == 8)
		{
			int x = rand() % 2;
			switch (x) {
			case 0:
				bet *= 2;
				status_player = 2;
				break;
			case 1:
				status_player = 2;
				break;
			}
			return;
		}
		if (combo == 7 || combo == 6 || combo == 5 || combo == 4 || combo == 3 || combo == 2)
		{
			status_player = 1;
			return;
		}
		if (combo == 1 || combo == 2 || combo == 0)
		{
			status_player = 1;
			return;
		}
	}
	if (table_status == 2)//если ставка
	{
		if (status_player == 3 || status_player == 1)
		{
			return;
		}
		if (combo == 9 || combo == 8)
		{
			int x = rand() % 2;
			switch (x) {
			case 0:
				bet *= 2;
				status_player = 4;//Raise
				break;
			case 1:
				status_player = 3;//Coll
				break;
			}
			return;
		}
		if (combo == 7 || combo == 6 || combo == 5 || combo == 4 || combo == 3 || combo == 2)
		{
			status_player = 3;
			return;
		}
		if (combo == 1 || combo == 2 || combo == 0)
		{
			int x = rand() % 2;
			if (x == 0)
			{
				status_player = 3;
				return;
			}
			if (x == 1)
			{
				status_player = 0;
				return;
			}
		}
	}
	if (table_status == 3)//если coll
	{
		if(status_player==3 || status_player==2)
	   {
			status_player = 1;
		return;
	   }
		if (combo == 9 || combo == 8)
		{
			int x = rand() % 2;
			switch (x) {
			case 0:
				bet *= 2;
				status_player = 4;//Raise
				break;
			case 1:
				status_player = 3;//Coll
				break;
			}
			return;
		}
		if (combo == 7 || combo == 6 || combo == 5 || combo == 4 || combo == 3 || combo == 2)
		{
			status_player = 3;
			return;
		}
		if (combo == 1 || combo == 2 || combo == 0)
		{
			int x = rand() % 5;
			if (x == 0)
			{
				status_player = 3;
				return;
			}
			if (x == 1 || x==2 || x==3 || x==4)
			{
				status_player = 0;
				return;
			}
		}
	}
	if (table_status == 4)//raise
	{
		if (combo == 9 || combo == 8)
		{
			int x = rand() % 2;
			switch (x) {
			case 0:
				bet *= 3;
				status_player = 5;//RE Raise
				break;
			case 1:
				status_player = 3;//Coll
				break;
			}
			return;
		}
		if (combo == 7 || combo == 6 || combo == 5 || combo == 4 || combo == 3 || combo == 2)
		{
			int x = rand() % 2;
			if (x == 0)
			{
				status_player = 3;//Coll
				return;
			}
			if (x == 1)
			{
				status_player = 0;//pass
				return;
			}
		}
		if (combo == 1 || combo == 2 || combo == 0)
		{
			status_player = 0;
			return;
		}
	}
	if (table_status == 5)//Re raise
	{
		if (combo == 9 || combo == 8)
		{
			int x = rand() % 2;
			switch (x) {
			case 0:
				status_player = 3;//Coll
				break;
			case 1:
				status_player = 0;//pass
				break;
			}
			return;
		}
		if (combo == 7 || combo == 6 || combo == 5)
		{
			{
				int x = rand() % 2;
				switch (x) {
				case 0:
					status_player = 3;//Coll
					break;
				case 1:
					status_player = 0;//pass
					break;
				}
				return;
			}
		}
		if ( combo == 4 || combo == 3 || combo == 2 || combo == 1 || combo == 0)
		{
			status_player = 0;
			return;
		}
	}
	if (table_status == 5)//ALL IN
	{
		if (stack_money / bet >= 4)
		{
			if (combo == 9 || combo == 8)
			{
				if (combo == 9 || combo == 8)
				{
					status_player = 3;//Call
					return;
				}
			}
			if (combo == 7 || combo == 6 || combo == 5)
			{
				int x = rand() % 3;
				if (x == 1)
					status_player = 3;
				else
					status_player = 0;
				return;
			}
			if (combo == 4 || combo == 3 || combo == 2 || combo == 1 || combo == 0)
			{
				int x = rand() % 2;
				switch (x) {
				case 0:
					status_player = 3;//Coll
					break;
				case 1:
					status_player = 0;//pass
					break;
				}
				return;
			}
		}
		if (stack_money / bet < 4)
		{
			status_player = 0;//pass
			return;
		}
	}
}//END TURN_BRAIN

void Player::takeCard(Card obj)
{
	P.addCard(obj);
}
void Player::takeMoney(int m)//взять выигрыш
{
	stack_money += m;
}
void Player::setName(char *strname)
{
	name = _strdup(strname);
}
char * Player::getName()
{
	return name;
}
void Player::sortCards()
{
	P.SortForPoker();
}
void Player::setStackMoney(int m)//с какой суммой вступить в игру
{
	stack_money = m;
}
void Player::setBet(int b)//установить размер ставки
{
	bet = b;
}
int Player::getBet()
{
	if (stack_money - bet == 0)
		status_player = -5; 
	return bet;
}
void Player::MinusBet()
{
	stack_money -= bet;
}
void Player::setStatusPlayer(int s)//установить статус
{
	if (s == 1)//когда чек => с него ставку не брать
	{
		//bet = 0;
		status_player = s;
	}
	else if (s == 4)
	{
		bet *= 2;
		status_player = s;
	}
	else if (s == 5)
	{
		bet *= 3;
		status_player = s;
	}
	else if (s == 6)
	{
		bet = stack_money;
		status_player = s;
	}
	else
	status_player = s;
}
void Player::ClearPlayer()
{
	P.ClearPack();
}
int Player::getStatusPlayer()
{
	return status_player;
}
void Player::setTableStatus(int ts)
{
	table_status = ts;
}
int Player::getStackMoney()
{
	return stack_money;
}
void Player::setMyCombo(int n)
{
	MyCombo = n;
}
int Player::getMyCombo()
{
	return MyCombo;
}
int Player::Chek_5cards_Combo()
{
	P.SortForPoker();
	int combo = 0;
	int n = 5;
	int chek_rank = 0;
	int chek_suit = 0;
	Card *mas = new Card[n];
	for (int i = 0; i < n; i++)
		mas[i] = P[i];
	if ((mas[0].getRank() - mas[1].getRank()) == 1 && (mas[1].getRank() - mas[2].getRank() == 1) && (mas[2].getRank() - mas[3].getRank() == 1) && (mas[3].getRank() - mas[4].getRank() == 1))
		chek_rank = 1;
	if ((mas[0].getSuit() == mas[1].getSuit()) && (mas[1].getSuit() == mas[2].getSuit()) && (mas[2].getSuit() == mas[3].getSuit()) && (mas[3].getSuit() == mas[4].getSuit()))
		chek_suit = 1;
	if (chek_rank == 1 && chek_suit == 1 && mas[0].getRank() == 12)//Флеш-Рояль
	{
		delete[]mas;
		MyCombo = 9;
		return 9;
	}
   if (chek_rank == 1 && chek_suit == 1 && mas[0].getRank() != 12)//Стрит-флеш
	{
	   delete[]mas;
	   MyCombo = 8;
	   return 8;
	}
   if (chek_rank == 1 && chek_suit != 1)//Стрит
   {
	   delete[]mas;
	   MyCombo = 4;
	   return 4;
   }
   if (mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank() && mas[0].getRank() == mas[3].getRank())
   {//Каре
	   delete[]mas;
	   MyCombo = 7;
	   return 7;
   }
   if (mas[1].getRank() == mas[2].getRank() && mas[2].getRank() == mas[3].getRank() && mas[3].getRank() == mas[4].getRank())
   {//Каре
	   delete[]mas;
	   MyCombo = 7;
	   return 7;
   }
   if ((mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank()) && mas[3].getRank() == mas[4].getRank())
   {//Фул-хаус
	   delete[]mas;
	   MyCombo = 6;
	   return 6;
   }
   if (mas[0].getRank() == mas[1].getRank() && (mas[2].getRank() == mas[3].getRank() && mas[2].getRank() == mas[4].getRank()))
   {//Фул-хаус
	   delete[]mas;
	   MyCombo = 6;
	   return 6;
   }
   if (mas[0].getSuit() == mas[1].getSuit() && mas[0].getSuit() == mas[2].getSuit() && mas[0].getSuit() == mas[3].getSuit() && mas[0].getSuit() == mas[4].getSuit())
   {//Флеш
	   delete[]mas;
	   MyCombo = 5;
	   return 5;
   }
   if ((mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank()) || (mas[1].getRank() == mas[2].getRank() && mas[1].getRank() == mas[3].getRank()) || (mas[2].getRank() == mas[3].getRank() && mas[2].getRank() == mas[4].getRank()))
   {//Тройка
	   delete[]mas;
	   MyCombo = 3;
	   return 3;
   }
   if ((mas[0].getRank() == mas[1].getRank() && mas[2].getRank() == mas[3].getRank()) || (mas[1].getRank() == mas[2].getRank() && mas[3].getRank() == mas[4].getRank()))
   {//Две пары
	   delete[]mas;
	   MyCombo = 2;
	   return 2;
   }
   if (mas[0].getRank() == mas[1].getRank() || mas[1].getRank() == mas[2].getRank() || mas[2].getRank() == mas[3].getRank() || mas[3].getRank() == mas[4].getRank())
   {//Пара
	   delete[]mas;
	   MyCombo = 1;
	   return 1;
   }
   delete[]mas;
   MyCombo = 0;
   return combo;//Старшая карта
}

int Player::Chek_6cards_Combo()
{
	P.SortForPoker();
	int combo = 0;
	int n = 6;
	int chek_rank = 0;
	int chek_suit = 0;
	Card *mas = new Card[n];
	for (int i = 0; i < n; i++)
		mas[i] = P[i];

	if ((mas[0].getRank() - mas[1].getRank()) == 1 && (mas[1].getRank() - mas[2].getRank() == 1) && (mas[2].getRank() - mas[3].getRank() == 1) && (mas[3].getRank() - mas[4].getRank() == 1))
		chek_rank = 1;
	if ((mas[0].getSuit() == mas[1].getSuit()) && (mas[1].getSuit() == mas[2].getSuit()) && (mas[2].getSuit() == mas[3].getSuit()) && (mas[3].getSuit() == mas[4].getSuit()))
		chek_suit = 1;
	if (chek_rank == 1 && chek_suit == 1 && mas[0].getRank() == 12)//Флеш-Рояль
	{
		delete[]mas;
		MyCombo = 9;
		return 9;
	}
	if (chek_rank == 1 && chek_suit == 1 && mas[0].getRank() != 12)//Стрит-флеш
	{
		delete[]mas;
		MyCombo = 8;
		return 8;
	}
	if (chek_rank == 1 && chek_suit != 1)//Стрит
	{
		delete[]mas;
		MyCombo = 4;
		return 4;
	}
	if ((mas[1].getRank() - mas[2].getRank()) == 1 && (mas[2].getRank() - mas[3].getRank() == 1) && (mas[3].getRank() - mas[4].getRank() == 1) && (mas[4].getRank() - mas[5].getRank() == 1))
		chek_rank = 1;
	if ((mas[1].getSuit() == mas[2].getSuit()) && (mas[2].getSuit() == mas[3].getSuit()) && (mas[3].getSuit() == mas[4].getSuit()) && (mas[4].getSuit() == mas[5].getSuit()))
		chek_suit = 1;

	if (chek_rank == 1 && chek_suit == 1)//Стрит-флеш
	{
		delete[]mas;
		MyCombo = 8;
		return 8;
	}
	if (chek_rank == 1 && chek_suit != 1)//Стрит
	{
		delete[]mas;
		MyCombo = 4;
		return 4;
	}
	if (mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank() && mas[0].getRank() == mas[3].getRank())
	{//Каре
		delete[]mas;
		MyCombo = 7;
		return 7;
	}
	if (mas[1].getRank() == mas[2].getRank() && mas[1].getRank() == mas[3].getRank() && mas[1].getRank() == mas[4].getRank())
	{//Каре
		delete[]mas;
		MyCombo = 7;
		return 7;
	}
	if (mas[2].getRank() == mas[3].getRank() && mas[2].getRank() == mas[4].getRank() && mas[2].getRank() == mas[5].getRank())
	{//Каре
		delete[]mas;
		MyCombo = 7;
		return 7;
	}
	
	if (mas[0].getRank() == mas[1].getRank() && (mas[2].getRank() == mas[3].getRank() && mas[2].getRank() == mas[4].getRank()))
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if (mas[0].getRank() == mas[1].getRank() && (mas[3].getRank() == mas[4].getRank() && mas[3].getRank() == mas[5].getRank()))
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	
	if (mas[1].getRank() == mas[2].getRank() && (mas[3].getRank() == mas[4].getRank() && mas[3].getRank() == mas[5].getRank()))
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	
	if ((mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank()) && mas[3].getRank() == mas[4].getRank())
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if ((mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank()) && mas[4].getRank() == mas[5].getRank())
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	
	if ((mas[1].getRank() == mas[2].getRank() && mas[1].getRank() == mas[3].getRank()) && mas[4].getRank() == mas[5].getRank())
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	
	
	if (mas[0].getSuit() == mas[1].getSuit() && mas[0].getSuit() == mas[2].getSuit() && mas[0].getSuit() == mas[3].getSuit() && mas[0].getSuit() == mas[4].getSuit())
	{//Флеш
		delete[]mas;
		MyCombo = 5;
		return 5;
	}
	if (mas[1].getSuit() == mas[2].getSuit() && mas[1].getSuit() == mas[3].getSuit() && mas[1].getSuit() == mas[4].getSuit() && mas[1].getSuit() == mas[5].getSuit())
	{//Флеш
		delete[]mas;
		MyCombo = 5;
		return 5;
	}
	if (mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank())
	{//Тройка
		delete[]mas;
		MyCombo = 3;
		return 3;
	}
	if (mas[1].getRank() == mas[2].getRank() && mas[1].getRank() == mas[3].getRank())
	{//Тройка
		delete[]mas;
		MyCombo = 3;
		return 3;
	}
	if (mas[2].getRank() == mas[3].getRank() && mas[2].getRank() == mas[4].getRank())
	{//Тройка
		delete[]mas;
		MyCombo = 3;
		return 3;
	}
	if (mas[3].getRank() == mas[4].getRank() && mas[3].getRank() == mas[5].getRank())
	{//Тройка
		delete[]mas;
		MyCombo = 3;
		return 3;
	}
	
	if (mas[0].getRank() == mas[1].getRank() && mas[2].getRank() == mas[3].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[0].getRank() == mas[1].getRank() && mas[3].getRank() == mas[4].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[0].getRank() == mas[1].getRank() && mas[4].getRank() == mas[5].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	
	if (mas[1].getRank() == mas[2].getRank() && mas[3].getRank() == mas[4].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[1].getRank() == mas[2].getRank() && mas[4].getRank() == mas[5].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	
	if (mas[2].getRank() == mas[3].getRank() && mas[4].getRank() == mas[5].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	
	if (mas[0].getRank() == mas[1].getRank() || mas[1].getRank() == mas[2].getRank() || mas[2].getRank() == mas[3].getRank() || mas[3].getRank() == mas[4].getRank() || mas[4].getRank()==mas[5].getRank())
	{//Пара
		delete[]mas;
		MyCombo = 1;
		return 1;
	}

	delete[]mas;
	MyCombo = 0;
	return combo;//Старшая карта
}
int Player::Chek_7cards_Combo()
{
	P.SortForPoker();
	int combo = 0;
	int n = 7;
	int chek_rank = 0;
	int chek_suit = 0;
	Card *mas = new Card[n];
	for (int i = 0; i < n; i++)
		mas[i] = P[i];


	if ((mas[0].getRank() - mas[1].getRank()) == 1 && (mas[1].getRank() - mas[2].getRank() == 1) && (mas[2].getRank() - mas[3].getRank() == 1) && (mas[3].getRank() - mas[4].getRank() == 1))
		chek_rank = 1;
	if ((mas[0].getSuit() == mas[1].getSuit()) && (mas[1].getSuit() == mas[2].getSuit()) && (mas[2].getSuit() == mas[3].getSuit()) && (mas[3].getSuit() == mas[4].getSuit()))
		chek_suit = 1;
	if (chek_rank == 1 && chek_suit == 1 && mas[0].getRank() == 12)//Флеш-Рояль
	{
		delete[]mas;
		MyCombo = 9;
		return 9;
	}
	if (chek_rank == 1 && chek_suit == 1 && mas[0].getRank() != 12)//Стрит-флеш
	{
		delete[]mas;
		MyCombo = 8;
		return 8;
	}
	if (chek_rank == 1 && chek_suit != 1)//Стрит
	{
		delete[]mas;
		MyCombo = 4;
		return 4;
	}

	if ((mas[1].getRank() - mas[2].getRank()) == 1 && (mas[2].getRank() - mas[3].getRank() == 1) && (mas[3].getRank() - mas[4].getRank() == 1) && (mas[4].getRank() - mas[5].getRank() == 1))
		chek_rank = 1;
	if ((mas[1].getSuit() == mas[2].getSuit()) && (mas[1].getSuit() == mas[3].getSuit()) && (mas[1].getSuit() == mas[4].getSuit()) && (mas[1].getSuit() == mas[5].getSuit()))
		chek_suit = 1;
	
	if (chek_rank == 1 && chek_suit == 1 && mas[0].getRank() != 12)//Стрит-флеш
	{
		delete[]mas;
		MyCombo = 8;
		return 8;
	}
	if (chek_rank == 1 && chek_suit != 1)//Стрит
	{
		delete[]mas;
		MyCombo = 4;
		return 4;
	}

	if ((mas[2].getRank() - mas[3].getRank()) == 1 && (mas[3].getRank() - mas[4].getRank() == 1) && (mas[4].getRank() - mas[5].getRank() == 1) && (mas[5].getRank() - mas[6].getRank() == 1))
		chek_rank = 1;
	if ((mas[2].getSuit() == mas[3].getSuit()) && (mas[2].getSuit() == mas[4].getSuit()) && (mas[2].getSuit() == mas[5].getSuit()) && (mas[2].getSuit() == mas[6].getSuit()))
		chek_suit = 1;
	
	if (chek_rank == 1 && chek_suit == 1 && mas[0].getRank() != 12)//Стрит-флеш
	{
		delete[]mas;
		MyCombo = 8;
		return 8;
	}
	if (chek_rank == 1 && chek_suit != 1)//Стрит
	{
		delete[]mas;
		MyCombo = 4;
		return 4;
	}

	if (mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank() && mas[0].getRank() == mas[3].getRank())
	{//Каре
		delete[]mas;
		MyCombo = 7;
		return 7;
	}
	if (mas[1].getRank() == mas[2].getRank() && mas[1].getRank() == mas[3].getRank() && mas[1].getRank() == mas[4].getRank())
	{//Каре
		delete[]mas;
		MyCombo = 7;
		return 7;
	}
	if (mas[2].getRank() == mas[3].getRank() && mas[2].getRank() == mas[4].getRank() && mas[2].getRank() == mas[5].getRank())
	{//Каре
		delete[]mas;
		MyCombo = 7;
		return 7;
	}
	if (mas[3].getRank() == mas[4].getRank() && mas[3].getRank() == mas[5].getRank() && mas[3].getRank() == mas[6].getRank())
	{//Каре
		delete[]mas;
		MyCombo = 7;
		return 7;
	}

	if ((mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank()) && mas[3].getRank() == mas[4].getRank())
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if ((mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank()) && mas[4].getRank() == mas[5].getRank())
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if ((mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank()) && mas[5].getRank() == mas[6].getRank())
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}

	if ((mas[1].getRank() == mas[2].getRank() && mas[1].getRank() == mas[3].getRank()) && mas[4].getRank() == mas[5].getRank())
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if ((mas[1].getRank() == mas[2].getRank() && mas[1].getRank() == mas[3].getRank()) && mas[5].getRank() == mas[6].getRank())
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if ((mas[2].getRank() == mas[3].getRank() && mas[2].getRank() == mas[4].getRank()) && mas[5].getRank() == mas[6].getRank())
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}

	if (mas[0].getRank() == mas[1].getRank() && (mas[2].getRank() == mas[3].getRank() && mas[2].getRank() == mas[4].getRank()))
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if (mas[0].getRank() == mas[1].getRank() && (mas[3].getRank() == mas[4].getRank() && mas[3].getRank() == mas[5].getRank()))
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if (mas[0].getRank() == mas[1].getRank() && (mas[4].getRank() == mas[5].getRank() && mas[4].getRank() == mas[6].getRank()))
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if (mas[1].getRank() == mas[2].getRank() && (mas[3].getRank() == mas[4].getRank() && mas[3].getRank() == mas[5].getRank()))
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if (mas[1].getRank() == mas[2].getRank() && (mas[4].getRank() == mas[5].getRank() && mas[4].getRank() == mas[6].getRank()))
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if (mas[2].getRank() == mas[3].getRank() && (mas[4].getRank() == mas[5].getRank() && mas[4].getRank() == mas[6].getRank()))
	{//Фул-хаус
		delete[]mas;
		MyCombo = 6;
		return 6;
	}
	if (mas[0].getSuit() == mas[1].getSuit() && mas[0].getSuit() == mas[2].getSuit() && mas[0].getSuit() == mas[3].getSuit() && mas[0].getSuit() == mas[4].getSuit())
	{//Флеш
		delete[]mas;
		MyCombo = 5;
		return 5;
	}
	if (mas[1].getSuit() == mas[2].getSuit() && mas[1].getSuit() == mas[3].getSuit() && mas[1].getSuit() == mas[4].getSuit() && mas[1].getSuit() == mas[5].getSuit())
	{//Флеш
		delete[]mas;
		MyCombo = 5;
		return 5;
	}
	if (mas[2].getSuit() == mas[3].getSuit() && mas[2].getSuit() == mas[4].getSuit() && mas[2].getSuit() == mas[5].getSuit() && mas[2].getSuit() == mas[6].getSuit())
	{//Флеш
		delete[]mas;
		MyCombo = 5;
		return 5;
	}

	if (mas[0].getRank() == mas[1].getRank() && mas[0].getRank() == mas[2].getRank())
	{//Тройка
		delete[]mas;
		MyCombo = 3;
		return 3;
	}
	if (mas[1].getRank() == mas[2].getRank() && mas[1].getRank() == mas[3].getRank())
	{//Тройка
		delete[]mas;
		MyCombo = 3;
		return 3;
	}
	if (mas[2].getRank() == mas[3].getRank() && mas[2].getRank() == mas[4].getRank())
	{//Тройка
		delete[]mas;
		MyCombo = 3;
		return 3;
	}
	if (mas[3].getRank() == mas[4].getRank() && mas[3].getRank() == mas[5].getRank())
	{//Тройка
		delete[]mas;
		MyCombo = 3;
		return 3;
	}
	if (mas[4].getRank() == mas[5].getRank() && mas[4].getRank() == mas[6].getRank())
	{//Тройка
		delete[]mas;
		MyCombo = 3;
		return 3;
	}

	if (mas[0].getRank() == mas[1].getRank() && mas[2].getRank() == mas[3].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[0].getRank() == mas[1].getRank() && mas[3].getRank() == mas[4].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[0].getRank() == mas[1].getRank() && mas[4].getRank() == mas[5].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[0].getRank() == mas[1].getRank() && mas[5].getRank() == mas[6].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[1].getRank() == mas[2].getRank() && mas[3].getRank() == mas[4].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[1].getRank() == mas[2].getRank() && mas[4].getRank() == mas[5].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[1].getRank() == mas[2].getRank() && mas[5].getRank() == mas[6].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[2].getRank() == mas[3].getRank() && mas[4].getRank() == mas[5].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[2].getRank() == mas[3].getRank() && mas[5].getRank() == mas[6].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}

	if (mas[3].getRank() == mas[4].getRank() && mas[5].getRank() == mas[6].getRank())
	{//Две пары
		delete[]mas;
		MyCombo = 2;
		return 2;
	}
	if (mas[0].getRank() == mas[1].getRank() || mas[1].getRank() == mas[2].getRank() || mas[2].getRank() == mas[3].getRank() || mas[3].getRank() == mas[4].getRank() || mas[4].getRank() == mas[5].getRank() || mas[5].getRank()==mas[6].getRank())
	{//Пара
		delete[]mas;
		MyCombo = 1;
		return 1;
	}
	delete[]mas;
	MyCombo = 0;
	return combo;//Старшая карта
}
int Player::WHAT_THE_COMBO()
{
	int result;
	if (P.getSize() == 5)
	{
		return result = Chek_5cards_Combo();
	}
	else if (P.getSize() == 6)
	{
		return result = Chek_6cards_Combo();
	}
	else
	{
		if (P.getSize() == 7)
			return result = Chek_7cards_Combo();
	}
}
void Player::ShowPlayerCards()
{
	//cout << name << endl;
	P.ShowPack();
}
void Player::SowTwoCards()
{
	//cout << name << endl;
	P.ShowOnlyTwo();
}
Player::~Player()
{
	if (name)
		delete[]name;
}
