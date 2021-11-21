#define _CRT_SECURE_NO_WARNINGS
#define MaxDraw 11

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <locale.h>
#include <ctype.h>
#include <windows.h>
// --------------------------------------------------------
enum WHOs_TURN { PLAYER, DEALER, NEW_GAME, COMPARE };
enum Hide_or_Open { HIDE, OPEN };
enum Blackjack_or_Not { BLACKJACK, NOT_BLACKJACK };

int capital = 100000;
int player_score = 0;
int dealer_score = 0;

typedef struct {
	char sha[5];
	char num[5];
	int shape_rand;
	int number_rand;
	int number_score;
}DRAW;

typedef struct {
	char sha[5];
	char num[5];
}hidden_card;

//----------------------------------------------------------------------
int card_select(int card_list[4][13], int nth_draw);
void change_num_to_shape(DRAW* p, int card_shape);
void change_num_to_num(DRAW* p, int card_number);
void selected_card_num_and_shape(DRAW* p, int card_buffer);
void hidden_card_func(hidden_card* p);
int blackJack(int bet_money, WHOs_TURN* turn);
void bust(int bet_money, WHOs_TURN* turn);
int choose_ace_num(int a);
int hit_or_stay(int player_turn, Hide_or_Open* dealer_first_card, WHOs_TURN* turn);
int remainder_func(int pre_money, int bet_money);
void whos_gonna_win(int bet_money);
int dealer_ace_num(int dealer_turn);
int deal_hit_or_stay(int dealer_turn, WHOs_TURN* turn);
void deal_bust(int bet_money, WHOs_TURN* turn);
void card_upper(int draw_count);
void dealer_card_interface(DRAW Deal_buf[], hidden_card hidden, int draw_count, Hide_or_Open dealer_first_card);
void player_card_interface(DRAW Play_buf[], int draw_count);
void card_lower(int draw_count);
void defeat(void);
void win(void);
void textColor(int color_number);
void card_background(int mode);
void pause(void);
//-----------------------------------------------------------






//-------------------------Card Draw Func.---------------------------------


int card_select(int card_list[4][13], int nth_draw) {
	int randNum = rand() % (52 - nth_draw);

	// 이미 뽑은 카드는 넘어간다.
	for (int i = 0; i < randNum+1; i++)
	{
		if (*(*card_list + i) == 0) {
			randNum++;
		}
	}



	int selected_num = (*(*card_list + randNum));
	(*(*card_list + randNum)) = 0; // 뽑은 카드를 0으로 set

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++)
			printf("%d ", (*(*card_list + (13 * i + j))));
		printf("\n");
	}
	printf("\n");
	return selected_num;
}



void change_num_to_shape(DRAW* p, int card_shape) {
	p->shape_rand = card_shape;
	switch (p->shape_rand)
	{
	case 1:
		strcpy(p->sha, "♠");
		break;
	case 2:
		strcpy(p->sha, "♣");
		break;
	case 3:
		strcpy(p->sha, "◆");
		break;
	case 4:
		strcpy(p->sha, "♥");
		break;
	}
}

void change_num_to_num(DRAW * p, int card_number) {

	p->number_rand = card_number;
	p->number_score = p->number_rand;
	switch (p->number_rand)
	{
	case 1:
		strcpy(p->num, "Ａ");	break;
	case 2:
		strcpy(p->num, "⑵");	break;
	case 3:
		strcpy(p->num, "⑶");	break;
	case 4:
		strcpy(p->num, "⑷");	break;
	case 5:
		strcpy(p->num, "⑸");	break;
	case 6:
		strcpy(p->num, "⑹");	break;
	case 7:
		strcpy(p->num, "⑺");	break;
	case 8:
		strcpy(p->num, "⑻");	break;
	case 9:
		strcpy(p->num, "⑼");	break;
	case 10:
		strcpy(p->num, "10");	break;
	case 11:
		strcpy(p->num, "Ｊ");
		p->number_score = 10;
		break;
	case 12:
		strcpy(p->num, "Ｑ");
		p->number_score = 10;
		break;
	case 13:
		strcpy(p->num, "Ｋ");
		p->number_score = 10;
		break;
	}
}

void selected_card_num_and_shape(DRAW* p, int card_buffer) {
	int card_shape = card_buffer / 100;
	int card_number = card_buffer % 100;

	change_num_to_shape(p, card_shape);
	change_num_to_num(p, card_number);

}



void hidden_card_func(hidden_card* p) {
	strcpy(p->num, "  ");
	strcpy(p->sha, "  ");
}


//---------------------Game Rule Func.-----------------------------------

int blackJack(int bet_money, WHOs_TURN *turn)
{
	int gain_money = (bet_money * 1.5 )+ bet_money;


	if ((player_score == 21) && (dealer_score != 21)) {
		printf("Player BlackJack!! 1.5배의 금액을 얻습니다 (%d원).\n", gain_money);
		capital += gain_money ;
		*turn = NEW_GAME;
	}
	else if ((player_score == 21) && (dealer_score == 21)) {
		printf("비겼습니다!! \n");
		capital += bet_money;
		*turn = NEW_GAME;
	}


	return 0;
}

void bust(int bet_money, WHOs_TURN* turn) {

	pause();
	if (player_score > 21) {
		printf("Bust.. 배팅한 금액을 잃었습니다. (%d원)\n\n", bet_money);
		player_score = 0; dealer_score = 0;
		*turn = NEW_GAME;

		}


}

int choose_ace_num(int a)
{
	int ace_num = 2;
	printf("%d번째 카드 ace 숫자 선택(1 or 11) : ", a+1);
	while (1) {
		scanf("%d", &ace_num);
		if (ace_num == 1 || ace_num == 11) break;
		else {
		printf("잘못 입력하셨습나다. 1과 11중 하나를 입력하세요 : ");
		ace_num = 2;
		getchar();
		}
		
	}
	return ace_num;
}


int hit_or_stay(int player_turn, Hide_or_Open* dealer_first_card, WHOs_TURN* turn)
{
	char HorS;
	getchar();
	HorS = 'A';

	while (1)
	{
		if (HorS == 'A') {
			printf("Hit or Stay?? (input H/S) : ");
			scanf("%c", &HorS);
			if(islower(HorS))
				HorS = toupper(HorS);
		}
		else if (HorS == 'H') {
			return player_turn + 1; 
		}
		else if (HorS == 'S') {
			*dealer_first_card = OPEN;
			*turn = DEALER;
			return player_turn;

		}
		else {
			getchar();
			printf("\n잘못 입력하셨습니다. 다시 입력해주세요. \n");
			HorS = 'A';
		}
	}

}

int remainder_func(int pre_money, int bet_money)
{
	int remainder;
	remainder = pre_money - bet_money;
	return remainder;
}

void whos_gonna_win(int bet_money) {
	if (player_score > dealer_score) {
		printf("\n\nPlayer 승리!! 배팅 금액만큼 돈을 얻습니다. (%d원)\n\n", bet_money);
		capital += 2 * bet_money;
	}
	else if (player_score < dealer_score) {
		printf("\n\nDealer 승리!! 배팅 금액만큼 돈을 잃습니다. (%d원)\n\n", bet_money);

	}
	else {
		printf("\n\n비겼습니다! \n\n");
		capital += bet_money;
	}
}


//----------------------- Dealer Turn Func. -------------------------------
int dealer_ace_num(int dealer_turn)
{

	if (dealer_score < 11)
		return 11;
	else
		return 1;
}

int deal_hit_or_stay(int dealer_turn, WHOs_TURN* turn)
{
	if (dealer_score < 17)
		return dealer_turn+1;
	else {
		*turn = COMPARE;
		return dealer_turn;

	}
	pause();
}
void deal_bust(int bet_money, WHOs_TURN *turn)
{

	printf("Dealer Bust.!! %d 원을 얻었습니다.\n", bet_money);
	capital += 2 * bet_money;
	*turn = NEW_GAME;



}





// ----------------------  Interface Func. --------------------------------
//      ┌──┐
//      │ ♤ │
//      │ ⓐ │
//      └──┘

void card_upper(int draw_count) {
	int i;
	draw_count++;

	for (i = 0; i < draw_count; i++) {
		card_background(1);
	}
	printf("\n");
}

void dealer_card_interface(DRAW Deal_buf[], hidden_card hidden, int draw_count, Hide_or_Open dealer_first_card)
{
	int i=0;
	draw_count++;
	if (dealer_first_card == HIDE) {
		card_background(1);
	}
	else if (dealer_first_card == OPEN){
		card_background(2);
		if(Deal_buf[0].shape_rand <= 2)
			textColor(112); // 하양검정
		else
			textColor(116); // 하양빨강
		printf("%s", Deal_buf[0].sha);
		card_background(3);
	}



	for (i = 1; i < draw_count; i++) {
		card_background(2);
		if (Deal_buf[i].shape_rand <= 2)
			textColor(112); // 하양검정
		else
			textColor(116); // 하양빨강
		printf("%s", Deal_buf[i].sha);
		card_background(3);
	}

	printf("\n");

	if (dealer_first_card == HIDE) 
		card_background(1);
	
	else if (dealer_first_card == OPEN) {
		card_background(2);
		textColor(112); // 하양검정
		printf("%s", Deal_buf[0].num);
		card_background(3);
	}


	for (i = 1; i < draw_count; i++) {
		card_background(2);
		textColor(112); // 하양검정
		printf("%s", Deal_buf[i].num);
		card_background(3);
	}

	printf("\n");
}

void player_card_interface(DRAW Play_buf[], int draw_count)
{
	int i = 0;
	draw_count++;
	for (i = 0; i < draw_count; i++){
		card_background(2);
		if (Play_buf[i].shape_rand <= 2)
			textColor(112); // 하양검정
		else
			textColor(116); // 하양빨강
		printf("%s", Play_buf[i].sha);
		card_background(3);
	}
	printf("\n");


	for (i = 0; i < draw_count; i++){
		card_background(2);
		textColor(112); // 하양검정
		printf("%s", Play_buf[i].num);
		card_background(3);
	}
	printf("\n");
}



void card_lower(int draw_count) {
	int i;
	draw_count++;
	for (i = 0; i < draw_count; i++) {
		textColor(47); // 초록하양
		printf(" ");
		textColor(119); // 하양하양
		printf("    ");
		textColor(47); // 초록하양
	}

	printf("\n");
}

void defeat(void) {

	textColor(15);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	printf("	 　　 　ハハ\n");
	printf("	（(⊂/ (^ω^) ／⊃))\n");
	printf("	　　 ＼/　  _／\n");
	printf("	　＿＿/　  ｜\n");
	printf("	　(　＿＿  ｜\n");
	printf("	　 ＼＼　＼＼\n");
	printf("	　　(／　　/ /\n");
	printf("	　　　　　 ＼)\n");

	printf("┌──────────────────────────────────┐\n");
	printf("│      게임에 패배하였습니다...    │\n");
	printf("└──────────────────────────────────┘\n");
	textColor(0);
	system("pause");
}

void win(void) {

	textColor(15);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	printf("     　 / )))　　　 ＿\n");
	printf("      ／ イ 　　　((( ＼\n");
	printf("     (　 )　　　　 ￣Ｙ＼\n");
	printf("     |　(＼　∧＿∧　｜　)\n");
	printf("     ＼　＼`(　`o´) ／ )\n");
	printf("     　＼ |　⌒Ｙ⌒　/ /\n");
	printf("    　  ｜＼　 ｜　 ／／\n");
	printf("    　　 ＼ト--仝--イ／\n");
	printf("    　　  ｜ ミ土ミ  /\n");
	printf(" ┌───────────────────────────┐\n");
	printf(" │       게임 승리 !!!       │\n");
	printf(" └───────────────────────────┘\n");
	textColor(0);
	system("pause");
}

void card_background(int mode) {
	
	switch (mode) {
	case 1:
		textColor(47); // 초록하양
		printf(" ");
		textColor(119); // 하양하양
		printf("    ");
		textColor(47); // 초록하양
		break;
	case 2:
		textColor(47); // 초록하양
		printf(" ");
		textColor(119); // 하양하양
		printf(" ");
		break;
	case 3:
		textColor(119); // 하양하양
		printf(" ");
		textColor(47); // 초록하양
		break;
	}
}

void textColor(int color_number) {


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);


	//textColor(36); // 초록빨강
	//textColor(32); //초록검정
	//textColor(47); // 초록하양
	//---------------------------------------
	//textColor(112); // 하양검정
	//textColor(116); // 하양빨강
	//textColor(119); // 하양하양
}

void pause(void) {
	textColor(32);
	system("pause");
	textColor(47);
}

// ----------------------  main Func. --------------------------------

int main(void)
{
	system("mode con cols=55 lines=17");
	textColor(15);


	srand((unsigned int)time(NULL)); // random seed를 만들기 위한 time 함수
	int Dealer_draw = 0;
	int Player_draw = 0;
	int firstGameFlag = 0;

	WHOs_TURN turn = PLAYER;
	Hide_or_Open dealer_first_card = HIDE;
	Blackjack_or_Not player_blackjack = NOT_BLACKJACK;


	int bet_money = 0; // 베팅한 돈 
	int i = 0;

	DRAW Deal_buf[MaxDraw];
	DRAW Play_buf[MaxDraw];
	hidden_card hidden;


	int card_list[4][13] = {
	101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113,
	201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213,
	301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313,
	401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413 };

	int nth_draw = 0;



	hidden_card_func(&hidden); //플레이어 턴에 딜러 카드 숨김

	while (1)
	{
		//------------Card Draw and Bet Money-----------------------
		if (Player_draw == 0 && Dealer_draw == 0)
		{
			for (i = 0; i < MaxDraw; i++) {
				// Draw card

				selected_card_num_and_shape(&Deal_buf[i], card_select(card_list, nth_draw));
				nth_draw++;

				selected_card_num_and_shape(&Play_buf[i], card_select(card_list, nth_draw));
				nth_draw++;

			}


			//점수 조작
			
			//Play_buf[0].number_score = 10;
			//Play_buf[1].number_score = 11;
			
			//Deal_buf[0].number_score = 10;
			//Deal_buf[1].number_score = 10;

			//capital = 300000;



			textColor(15);
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			if (firstGameFlag == 0) {


				printf(" ┌──────────────────────────────────┐\n");
				printf(" │  승리 조건 : 30만원 이상 모으기  │\n");
				printf(" └──────────────────────────────────┘\n");
				printf("            ｏ\n");
				printf("              。\n");
				printf("               。\n");
				printf("            ∧＿∧\n");
				printf("            (*-ω-)\n");
				printf("      ＿＿＿(__つ /￣￣￣￣/＿＿＿\n");
				printf("               ＼/　  　　/\n\n\n");
				firstGameFlag = 1;
			}


			// Bet Money
			printf("배팅금을 입력하세요(현재 잔액 : %d ) : ", capital);
			while (1) {

				scanf("%d", &bet_money);
				if (bet_money > capital) {
					printf("잔액이 부족합니다.\n");
					printf("배팅금을 다시 입력햐세요 : ");
					getchar();
				}
				else if (bet_money <= 0)
				{
					printf("잘못 입력하셨습니다.\n");
					printf("배팅금을 다시 입력햐세요 : ");
					getchar();
				}

				else break;
			}
			capital = remainder_func(capital, bet_money);

			Player_draw = 1;
			Dealer_draw = 1;
		}


		

		//--------------------Game Start-----------------------------
		/*
		**딜러 게임 규칙**
		16이하면 무조건 Hit, 17이상이면 무조건 Stay
		버스트 되지 않는 한 A는 11로 카운트한다.
		*/

		// *******************Dealer Turn********************
		textColor(47); // 초록하양
		printf("\n\n\n\n\n\n\n\n\n\n\n\n");

		// First Turn
		if (Dealer_draw == 1) {
			if (Deal_buf[0].number_score == 1)
				Deal_buf[0].number_score = dealer_ace_num(0);
			dealer_score = Deal_buf[0].number_score;
		}
		if (Deal_buf[Dealer_draw].number_score == 1) {
			Deal_buf[Dealer_draw].number_score = dealer_ace_num(Dealer_draw);
		}
		
		dealer_score += Deal_buf[Dealer_draw].number_score;

		if (player_blackjack == BLACKJACK) {
			dealer_score = Deal_buf[0].number_score + Deal_buf[1].number_score;
			Dealer_draw = 1;
		}

		if (dealer_first_card == HIDE)
			printf("\nDealer      딜러 점수 ??\n");
		else
			printf("\nDealer      딜러 점수 %d\n", dealer_score);
		card_upper(Dealer_draw);
		dealer_card_interface(Deal_buf, hidden, Dealer_draw, dealer_first_card);
		card_lower(Dealer_draw);



		// Bet Amount
		printf("베팅금 : %d\n", bet_money);



		// ******************Player Turn**********************
		card_upper(Player_draw);
		player_card_interface(Play_buf, Player_draw);
		card_lower(Player_draw);
		// First Turn / Draw two cards
		if ((Player_draw == 1) && turn == PLAYER)
		{
			if (Play_buf[0].number_score == 1) 
				Play_buf[0].number_score = choose_ace_num(0);
			player_score = Play_buf[0].number_score;
		}

		
		if (turn == PLAYER) {
			if (Play_buf[Player_draw].number_score == 1) {
				Play_buf[Player_draw].number_score = choose_ace_num(Player_draw);
			}
			player_score += Play_buf[Player_draw].number_score;
		}


		printf("Player      현재 숫자 : %d      남은 금액 : %d\n\n", player_score, capital);

		// ******** 딜러 결과 인터페이스********
		if ((turn == DEALER) && (player_blackjack == NOT_BLACKJACK)) {
			if (dealer_score > 21)
				deal_bust(bet_money, &turn);
			else
				Dealer_draw = deal_hit_or_stay(Dealer_draw, &turn);
		}

		// Player Blackjack Judgement

		if (player_blackjack == BLACKJACK)
		{
			blackJack(bet_money, &turn);
		}
		if (turn == PLAYER) {
			// Blackjack
			if ((player_score == 21) && (Player_draw == 1)) {
				printf("Player BlackJack!! 딜러의 카드를 확인합니다.\n");
				dealer_first_card = OPEN;
				turn = DEALER;
				player_blackjack = BLACKJACK;
			}
			// --------------Bust or Hit_or_stay---------------------

			if (player_blackjack == NOT_BLACKJACK) {
				if (player_score > 21)
					bust(bet_money, &turn);
				else
					Player_draw = hit_or_stay(Player_draw, &dealer_first_card, &turn);
			}
		}


		// ********** 승자 결정 ******************
		if (turn == COMPARE)
		{
			pause();
			whos_gonna_win(bet_money);


			if ((capital >= 300000) || (capital <= 100)){
				break;
		}
			else
				turn = NEW_GAME;
		}


		// ************* 새로운 게임 *********************
		if (turn == NEW_GAME)
		{
			pause();
			if ((capital >= 300000) || (capital <= 100))
				break;
			else
				printf("\n*** 새로운 게임을 시작합니다. ***\n");

			// 변수 초기화
			Player_draw = 0; Dealer_draw = 0;
			player_score = 0; dealer_score = 0;
			dealer_first_card = HIDE;
			turn = PLAYER;
			player_blackjack = NOT_BLACKJACK;
			nth_draw = 0;
			for (int i = 1; i < 5; i++) {
				for (int j = 1; j < 14; j++) {
					card_list[i-1][j-1] = (i * 100) + j;
				}

			}

		}

		// ************ 게임 종료 *******************

		printf("\n");
		pause();
		printf("\n");


	}


	if (capital >= 300000) {
		printf("\n남은 돈 : %d원\n", capital);
		printf("30만원 이상을 모았습니다!! \n\n");
		pause();
		win();
	}
	else {
		printf("\n남은 돈 : %d원\n", capital);
		printf("돈을 모두 잃었습니다.... \n\n");
		pause();
		defeat();
	}

	return 0;

}
