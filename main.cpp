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
	printf("���� : %d\t������ : %d\n", num, (int)num % 4);

	return (int)num % 4;
}

int rand_num_select()
{
	int num = rand();
	printf("���� : %d\t������ : %d\n", num, (int)num % 13 + 1);
	return (int)num % 13 + 1;
}


void change_num_to_shape(struct shape_and_num* p) {
	p->shape_rand = rand_shape_select();
	switch (p->shape_rand)
	{
	case 0:
		strcpy(p->sha, "��");
		break;
	case 1:
		strcpy(p->sha, "��");
		break;
	case 2:
		strcpy(p->sha, "��");
		break;
	case 3:
		strcpy(p->sha, "��");
		break;
	}
}

void change_num_to_num(struct shape_and_num* p) {
	p->number_rand = rand_num_select();
	p->number_score = p->number_rand;
	switch (p->number_rand)
	{
	case 1:
		strcpy(p->num, "��");	break;
	case 2:
		strcpy(p->num, "��");	break;
	case 3:
		strcpy(p->num, "��");	break;
	case 4:
		strcpy(p->num, "��");	break;
	case 5:
		strcpy(p->num, "��");	break;
	case 6:
		strcpy(p->num, "��");	break;
	case 7:
		strcpy(p->num, "��");	break;
	case 8:
		strcpy(p->num, "��");	break;
	case 9:
		strcpy(p->num, "��");	break;
	case 10:
		strcpy(p->num, "��");	break;
	case 11:
		strcpy(p->num, "��");
		p->number_score = 10;
		break;
	case 12:
		strcpy(p->num, "��");
		p->number_score = 10;
		break;
	case 13:
		strcpy(p->num, "��");
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
		printf("Player BlackJack!! ������ �ݾ��� 1.5�踦 �޽��ϴ�. (%d��)\n", gain_money);
		capital += gain_money ;
		player_score = 0;

		printf("���ο� ������ �����մϴ�. \n");
	}

	if (dealer_score == 21) {
		printf("Dealer BlackJack!! ������ �ݾ��� 1.5�踦 �ҽ��ϴ�. (%d��)", gain_money);
		capital -= loss_money;
		dealer_score = 0;
	}
	return 0;
}


int choose_ace_num(int a)
{
	int ace_num;
	printf("%d��° ī�� ace ���� ����(1 or 11) : ", a);
	while (1) {
		scanf("%d", &ace_num);
		if (ace_num == 1 || ace_num == 11) break;
		else printf("�߸� �Է��ϼ̽�����. 1�� 11�� �ϳ��� �Է��ϼ��� : ");
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
			printf("�ٽ� �Է����ּ���. \n");
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
	srand((unsigned int)time(NULL)); // random seed�� ����� ���� time �Լ�
	int Dealer_draw = 1;
	int Player_draw = 1;
	int end = 1; // 1�϶� �÷��̾� ������, 0�϶� ���� ����, 2�϶� ���� ����
	int bet_money; // ������ �� 
	int remainder; // ���� ��
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



			//���ñ� �Է�
			printf("\n\n\n\n\n\n\n\n\n\n\n\n");
			printf("���ñ��� �Է��ϼ���(���� �ܾ� : %d ) : ", capital);
			while (1) {

				scanf("%d", &bet_money);
				if (bet_money > capital) {
					printf("�ܾ��� �����մϴ�.\n");
					printf("���ñ��� �ٽ� �Է��Ἴ�� : ");
				}
				else if (bet_money <= 0)
				{
					printf("�߸� �Է��ϼ̽��ϴ�.\n");
					printf("���ñ��� �ٽ� �Է��Ἴ�� : ");
				}
				else break;
			}
			capital = remainder_func(capital, bet_money);
		}






		printf("\n\n\n\n\n\n\n\n\n\n\n\n");
		// ���� ��
		switch (Dealer_draw)
		{
		case 1:
			printf("\nDealer\n");
			printf("����������������\n");
			if (end == 1) {
				printf("��%s����%s��\n", hidden.sha, Deal_buf2.sha);
				printf("��%s����%s��\n", hidden.num, Deal_buf2.num);
			}
			else if (end == 0) {
				printf("��%s����%s��\n", Deal_buf1.num, Deal_buf2.num);
				printf("��%s����%s��\n", Deal_buf1.num, Deal_buf2.num);
			}
			printf("����������������\n\n");


			break;
		case 2:

			break;
		}
		//���ñݾ�
		printf("���ñ� : %d\n\n", bet_money);

		// �÷��̾� ��
		switch (Player_draw)
		{
		case 1:

			printf("����������������\n");
			printf("��%s����%s��\n", play_buf1.sha, play_buf2.sha);
			printf("��%s����%s��\n", play_buf1.num, play_buf2.num);
			printf("����������������\n");
			if (play_buf1.number_score == 1) play_buf1.number_score = choose_ace_num(1);
			if (play_buf2.number_score == 1) play_buf2.number_score = choose_ace_num(2);
			player_score = play_buf1.number_score + play_buf2.number_score;

			printf("\nPlayer      ���� ���� : %d      ���� �ݾ� : %d\n\n", player_score, capital);
			
			if (player_score == 21) {
				blackJack(bet_money);
				Player_draw = 1; Dealer_draw = 1;
			}
			else Player_draw = hit_or_stay(Player_draw);

			break;
		case 2:
			printf("������������������������\n");
			printf("��%s����%s����%s��\n", play_buf1.sha, play_buf2.sha, play_buf3.sha);
			printf("��%s����%s����%s��\n", play_buf1.num, play_buf2.num, play_buf3.num);
			printf("������������������������\n");
			if (play_buf3.number_score == 1) play_buf3.number_score = choose_ace_num(3);
			player_score += play_buf3.number_score;


			printf("\nPlayer      ���� ���� : %d      ���� �ݾ� : %d\n\n", player_score, capital);
			Player_draw = hit_or_stay(Player_draw);

			break;
		}


		printf("\n");



		system("pause");

	}









	return 0;

}
