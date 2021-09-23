#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <locale.h>
int rand_shape_select();
int rand_num_select();
void change_num_to_shape(struct shape_and_num* p);
void change_num_to_num(struct shape_and_num* p);
void hidden_card_func(struct hidden_card* p);
int remainder_func(int pre_money, int bet_money);
int dealer_card(struct shape_and_num* Deal_buf1, shape_and_num* Deal_buf2, shape_and_num* Deal_buf3, shape_and_num* Deal_buf4);
int player_card(struct shape_and_num* play_buf1, shape_and_num* play_buf2, shape_and_num* play_buf3, shape_and_num* play_buf4);
int blackJack(int bet_money);



int capital = 100000;
int player_score = 0;
int dealer_score = 0;

struct shape_and_num {
	char sha[5];
	char num[5];
	int shape_rand;
	int number_rand;
	int number_score;
};
struct hidden_card {
	char sha[5];
	char num[5];
};


int rand_shape_select()
{
	int num = rand();
	printf("난수 : %d\t나머지 : %d\n", num, (int)num % 4);

	return (int)num % 4;
}

int rand_num_select()
{
	int num = rand();
	printf("난수 : %d\t나머지 : %d\n", num, (int)num % 13 + 1);
	return (int)num % 13 + 1;
}


void change_num_to_shape(struct shape_and_num* p) {
	p->shape_rand = rand_shape_select();
	switch (p->shape_rand)
	{
	case 0:
		strcpy(p->sha, "♤");
		break;
	case 1:
		strcpy(p->sha, "♡");
		break;
	case 2:
		strcpy(p->sha, "♧");
		break;
	case 3:
		strcpy(p->sha, "◇");
		break;
	}
}

void change_num_to_num(struct shape_and_num* p) {
	p->number_rand = rand_num_select();
	p->number_score = p->number_rand;
	switch (p->number_rand)
	{
	case 1:
		strcpy(p->num, "ⓐ");	break;
	case 2:
		strcpy(p->num, "②");	break;
	case 3:
		strcpy(p->num, "③");	break;
	case 4:
		strcpy(p->num, "④");	break;
	case 5:
		strcpy(p->num, "⑤");	break;
	case 6:
		strcpy(p->num, "⑥");	break;
	case 7:
		strcpy(p->num, "⑦");	break;
	case 8:
		strcpy(p->num, "⑧");	break;
	case 9:
		strcpy(p->num, "⑨");	break;
	case 10:
		strcpy(p->num, "⑩");	break;
	case 11:
		strcpy(p->num, "ⓙ");
		p->number_score = 10;
		break;
	case 12:
		strcpy(p->num, "ⓠ");
		p->number_score = 10;
		break;
	case 13:
		strcpy(p->num, "ⓚ");
		p->number_score = 10;
		break;
	}
}

void hidden_card_func(struct hidden_card* p) {
	strcpy(p->num, "  ");
	strcpy(p->sha, "  ");
}
int dealer_card(struct shape_and_num* Deal_buf1, shape_and_num* Deal_buf2, shape_and_num* Deal_buf3, shape_and_num* Deal_buf4)
{
	change_num_to_num(Deal_buf1);
	change_num_to_shape(Deal_buf1);
	change_num_to_num(Deal_buf2);
	change_num_to_shape(Deal_buf2);
	change_num_to_num(Deal_buf3);
	change_num_to_shape(Deal_buf3);
	change_num_to_num(Deal_buf4);
	change_num_to_shape(Deal_buf4);

	return 0;
}

int player_card(struct shape_and_num* play_buf1, shape_and_num* play_buf2, shape_and_num* play_buf3, shape_and_num* play_buf4)
{
	change_num_to_num(play_buf1);
	change_num_to_shape(play_buf1);
	change_num_to_num(play_buf2);
	change_num_to_shape(play_buf2);
	change_num_to_num(play_buf3);
	change_num_to_shape(play_buf3);
	change_num_to_num(play_buf4);
	change_num_to_shape(play_buf4);


	return 0;

}

int blackJack(int bet_money)
{
	int gain_money = bet_money * 1.5 + bet_money;
	int loss_money = bet_money * 0.5;

	if (player_score == 21) {
		printf("Player BlackJack!! 배팅한 금액의 1.5배를 받습니다. (%d원)\n", gain_money);
		capital += gain_money ;
		player_score = 0;

		printf("새로운 게임을 시작합니다. \n");
	}

	if (dealer_score == 21) {
		printf("Dealer BlackJack!! 배팅한 금액의 1.5배를 잃습니다. (%d원)", gain_money);
		capital -= loss_money;
		dealer_score = 0;
	}
	return 0;
}


int choose_ace_num(int a)
{
	int ace_num;
	printf("%d번째 카드 ace 숫자 선택(1 or 11) : ", a);
	while (1) {
		scanf("%d", &ace_num);
		if (ace_num == 1 || ace_num == 11) break;
		else printf("잘못 입력하셨습나다. 1과 11중 하나를 입력하세요 : ");
	}
	return ace_num;
}


int hit_or_stay(int player_turn)
{
	char HorS = 'A';

	while (1)
	{
		if (HorS == 'A') {
			printf("Hit or Stay?? (input H/S) : ");
			scanf("%c", &HorS);
			scanf("%c", &HorS);
		}
		if (HorS == 'H') {
			return player_turn + 1; break;
		}
		else if (HorS == 'S') {
			return 0; break;
		}
		else {
			printf("다시 입력해주세요. \n");
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

int main(void)
{
	struct shape_and_num p1;
	srand((unsigned int)time(NULL)); // random seed를 만들기 위한 time 함수
	int Dealer_draw = 1;
	int Player_draw = 1;
	int end = 1; // 1일때 플레이어 진행중, 0일때 딜러 진행, 2일때 게임 종료
	int bet_money; // 베팅한 돈 
	int remainder; // 남은 돈
	struct hidden_card hidden;
	struct shape_and_num Deal_buf1;
	struct shape_and_num Deal_buf2;
	struct shape_and_num Deal_buf3;
	struct shape_and_num Deal_buf4;
	struct shape_and_num play_buf1;
	struct shape_and_num play_buf2;
	struct shape_and_num play_buf3;
	struct shape_and_num play_buf4;
	hidden_card_func(&hidden);

	while (1)
	{
		if (Player_draw == 1 && Dealer_draw == 1)
		{
			dealer_card(&Deal_buf1, &Deal_buf2, &Deal_buf3, &Deal_buf4);

			player_card(&play_buf1, &play_buf2, &play_buf3, &play_buf4);



			//배팅금 입력
			printf("\n\n\n\n\n\n\n\n\n\n\n\n");
			printf("배팅금을 입력하세요(현재 잔액 : %d ) : ", capital);
			while (1) {

				scanf("%d", &bet_money);
				if (bet_money > capital) {
					printf("잔액이 부족합니다.\n");
					printf("배팅금을 다시 입력햐세요 : ");
				}
				else if (bet_money <= 0)
				{
					printf("잘못 입력하셨습니다.\n");
					printf("배팅금을 다시 입력햐세요 : ");
				}
				else break;
			}
			capital = remainder_func(capital, bet_money);
		}






		printf("\n\n\n\n\n\n\n\n\n\n\n\n");
		// 딜러 턴
		switch (Dealer_draw)
		{
		case 1:
			printf("\nDealer\n");
			printf("┌──┐┌──┐\n");
			if (end == 1) {
				printf("│%s││%s│\n", hidden.sha, Deal_buf2.sha);
				printf("│%s││%s│\n", hidden.num, Deal_buf2.num);
			}
			else if (end == 0) {
				printf("│%s││%s│\n", Deal_buf1.num, Deal_buf2.num);
				printf("│%s││%s│\n", Deal_buf1.num, Deal_buf2.num);
			}
			printf("└──┘└──┘\n\n");


			break;
		case 2:

			break;
		}
		//배팅금액
		printf("베팅금 : %d\n\n", bet_money);

		// 플레이어 턴
		switch (Player_draw)
		{
		case 1:

			printf("┌──┐┌──┐\n");
			printf("│%s││%s│\n", play_buf1.sha, play_buf2.sha);
			printf("│%s││%s│\n", play_buf1.num, play_buf2.num);
			printf("└──┘└──┘\n");
			if (play_buf1.number_score == 1) play_buf1.number_score = choose_ace_num(1);
			if (play_buf2.number_score == 1) play_buf2.number_score = choose_ace_num(2);
			player_score = play_buf1.number_score + play_buf2.number_score;

			printf("\nPlayer      현재 숫자 : %d      남은 금액 : %d\n\n", player_score, capital);
			
			if (player_score == 21) {
				blackJack(bet_money);
				Player_draw = 1; Dealer_draw = 1;
			}
			else Player_draw = hit_or_stay(Player_draw);

			break;
		case 2:
			printf("┌──┐┌──┐┌──┐\n");
			printf("│%s││%s││%s│\n", play_buf1.sha, play_buf2.sha, play_buf3.sha);
			printf("│%s││%s││%s│\n", play_buf1.num, play_buf2.num, play_buf3.num);
			printf("└──┘└──┘└──┘\n");
			if (play_buf3.number_score == 1) play_buf3.number_score = choose_ace_num(3);
			player_score += play_buf3.number_score;


			printf("\nPlayer      현재 숫자 : %d      남은 금액 : %d\n\n", player_score, capital);
			Player_draw = hit_or_stay(Player_draw);

			break;
		}


		printf("\n");



		system("pause");

	}









	return 0;

}
