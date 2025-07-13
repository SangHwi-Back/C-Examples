#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TESTER_PASSWORD "1234"
#define TESTER_ACCOUNT_NUMBER "1234567812345678"
#define TESTER_PIN "88888888"
#define TESTER_BALANCE 50000

#define MENU_DEPOSIT 1
#define MENU_WITHDRAW 2  
#define MENU_BALANCE 3
#define MENU_EXIT 4

typedef struct {
	char account_number[16];
	char pin[8];
	int balance;
} Account;

static void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int getIntendedWorkFromUser(void) {
	printf("������ ���͵帱�Կ�.\n");
	printf("�Ա��� %d �� �����ּ���.\n", MENU_DEPOSIT);
	printf("����� %d �� �����ּ���.\n", MENU_WITHDRAW);
	printf("�ܾ������ %d�� �����ּ���.\n", MENU_BALANCE);
	printf("����� %d �� �����ּ���.\n", MENU_EXIT);

	int nInput = 0;
	scanf_s("%d", &nInput);
	clearInputBuffer();

	return nInput;
}

int verifyUserInWhile(void) {
	char userInput[100] = { 0 };
	printf("�ȳ��ϼ��� ATM ��⿡ ���� ���� ȯ���մϴ�.\n��й�ȣ�� �Է��ϼ���.\n");
	scanf_s("%s", userInput, (unsigned)_countof(userInput));
	clearInputBuffer();

	if (strcmp(userInput, TESTER_PASSWORD) == 0) {
		return 0; // Return false to break while-loop
	}
	else {
		return 1;
	}
}

int insertMoney(Account user) {
	int money = 0;
	printf("�Ա��� �ݾ��� �Է����ּ���.\n");
	scanf_s("%d", &money);
	clearInputBuffer();
	
	if (money < 0) {
		printf("�Ա� �ݾ��� 0 �̻��̾�� �ؿ�!\n");
		return user.balance;
	}

	return user.balance + money;
}

int getMoneyFromAccount(Account user) {
	int money = 0;
	printf("����� �ݾ��� �Է����ּ���.\n");
	scanf_s("%d", &money);
	clearInputBuffer();

	if (user.balance < money) {
		int userInput = 0;
		printf("��� �ݾ��� �ܾ׺��� Ŀ��. �ܾ��� %d ��ŭ�� ��ݵ� �ſ���.\n�׷��� �����Ͻðڴٸ� 1�� �����ּ���.\n",
			user.balance);
		scanf_s("%d", &userInput);
		clearInputBuffer();

		if (userInput == 1) {
			return user.balance;
		}
		else {
			printf("����� ��ҵǾ����ϴ�. �ٽ� �������ּ���.\n");
			return 0;
		}
	}

	return money;
}

int getBalance(Account user) {
	return user.balance;
}

bool verifyExit() {
	printf("���� �����Ͻðھ��? 1�� �Է����ֽø� ���Ḧ �����ϰڽ��ϴ�.\n");
	int input = 0;
	scanf_s("%d", &input);
	clearInputBuffer();

	return input == 1;
}

int main(void)
{
	int inputLimit = 5;

	while (verifyUserInWhile()) {
		if (inputLimit > 0) {
			inputLimit--;
			printf("Ʋ�� ��й�ȣ�Դϴ�. ���� �Է�Ƚ���� %d �Դϴ�.\n", inputLimit);
		}
		else {
			printf("��й�ȣ �Է� Ƚ�� �ʰ��Դϴ�! �����ڿ� �������ּ���.\n");
			return 0;
		}
	}

	printf("ȯ���մϴ� �׽��ʹ�!\n");

	Account tester = { TESTER_ACCOUNT_NUMBER, TESTER_PIN, TESTER_BALANCE };
	//Account opponent = { "1234123412341234", "88888888", 0 };

	while (true) {
		switch (getIntendedWorkFromUser()) {
		case 1:
			tester.balance += insertMoney(tester);
			break;
		case 2:
			tester.balance -= getMoneyFromAccount(tester);
			break;
		case 3:
			printf("�Ա��� ��� ��� ���: %d\n", getBalance(tester));
			break;
		case 4:
			if (verifyExit()) {
				printf("���α׷��� �����մϴ�.\n");
				return 0;
			}
			break;
		default:
			printf("Ȯ�ε��� ���� ���ɾ��Դϴ�!\n");
		}
	}

	printf("���α׷��� �����մϴ�.\n");
	return 0;
}