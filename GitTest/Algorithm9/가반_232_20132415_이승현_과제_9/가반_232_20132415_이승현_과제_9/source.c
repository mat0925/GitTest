#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define W 52	// �������� �־��� �ִ� ��뷮
#define nSize 8	// �迭�� ũ��
#define INF 1000000	// ���Ѽ�

int w[nSize] = { 0, 2, 10, 13, 17, 22, 42, INF };	// ����ġ �迭 
bool include[nSize] = {false, false, false, false, false , false , false, false };		// ���� ������ Ȯ���ϴ� �迭 
int weight = 0;	// ������ ���� ����ġ
int sequence = 1;	// ������ ������ ��Ÿ���� ���� ����
bool check = false;	// ���ʷ� ������ ������ �� Ž�� �ߴ��� ���� check ����

void sum_of_subsets(int i, int weight, int total);
void modified_sum_of_subsets(int i, int weight, int total);
bool promising(int i, int weight, int total);
int estimate();

int main(void) {
	int total;	// ���� ���¿��� ���� �� �ִ� ����ġ���� ��
	int num;
	int sum;	// Monte Carlo ����� ���� ����� ��� �������� ��

	float average;	// ���ġ�� �����ϱ� ���� ����

	srand(time(NULL));

	char input = 'y';	// ���α׷� ���� ���θ� Ȯ���ϱ� ���� char�� ����

	int choose = 0;		//  ���� ��ȣ ������ ���� int�� ����
	printf("////%8sAlgorithm Assignment #9%8s//// \n", " ", " ");
	while (input == 'y')		// while loop : 'y' �Է� �� ���α׷� �ݺ�
	{
		printf("\n���� ��ȣ�� �����Ͻʽÿ�. \n\n");
		printf("[****����****]\n%51. ���� 14�� <Sum of Subsets - Backtracking>\n%52. ���� 16�� <Modified Algorithm 5.4>\n%53. ���� 17�� <Monte Carlo>\n\n");
		printf("Input Number (1~3) : ");
		scanf("%d", &choose);	// ������ ���� ��ȣ�� ����
		switch (choose)				// �Է��� ���ڿ� ���� ���α׷��� �����մϴ�.
		{
		case 1:		// case 1 : ���� 14��
		{
			printf("���� 14�� <Sum of Subsets - Backtracking>\n\n");
			total = 126;
			weight = 0;
			for (num = 0; num < nSize; num++)	// include �迭 �ʱ�ȭ
				include[num] = false;
			sum_of_subsets(0, weight, total);
			printf("\n\n");
			break;
		}
		case 2:
		{
			printf("���� 16�� <Modified Algorithm 5.4>\n\n");
			total = 126;
			weight = 0;
			for (num = 0; num < nSize; num++)	// include �迭 �ʱ�ȭ
				include[num] = false;
			modified_sum_of_subsets(0, weight, total);
			printf("\n\n");
			break;
		}
		case 3:
		{
			sum = 0;
			printf("���� 17�� <Monte Carlo>\n\n");
			for (int num = 0; num < 10000; num++) {	// Monte Carlo ����� 100ȸ���� �ݺ�
				printf(">> Monte Carlo [ %d ] : %d \n", num + 1, estimate());	// n��° ��� �� ���
				sum += estimate();
			}
			average = sum / 100;		// ��� ���� ���� 100���� ������ ���ġ�� ���Ѵ�
			printf(">> Monte Carlo ��հ� : %f \n", average);
			printf("\n\n");
			break;
		}
		}
		while (1) {		// while loop : ���α׷� ���� ���� ����
			printf("�ѹ� �� �Ͻðڽ��ϱ�?  (y/n)\n");
			scanf("%c", &input);
			if (input == 32 || input == 10)
				scanf("%c", &input);
			if (input != 'y' && input != 'n')
				printf("�߸� �Է��ϼ̽��ϴ�.\n");
			else
			{
				printf("\n");
				break;
			}
		}
	}


	
	return 0;
}

/*
	sum_of_subsets () �Լ�
		- Algorithm 5.4�� ������ �Լ�
		- ���� 14���� �ش�
		- BackTracking ����� ��͸� ���� ����
		- ���̸� �ǹ��ϴ� int�� ���� i, ������ ����ġ�� ���ġ �� ���� ����ġ�� �ǹ��ϴ�
		   int�� ���� weight�� total�� �Է¹޽��ϴ�.
		- ���� ���θ� Ȯ���ϴ� include �迭�� ���� ���� Ȯ���մϴ�.
*/
void sum_of_subsets(int i, int weight, int total) {
	if (promising(i, weight, total)) {
		if (weight == W)	// ���� �����ϸ� ���
		{
			printf("\n>> %d��° �� ��� \n", sequence);	// �� ����� ����
			for (int j = 0; j < nSize; j++)
				if (include[j] == true)
					printf("   w[%d] ���� \n", j);
			sequence++;
		}
		else {
			include[i + 1] = true;	// case1 : ���� ��
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = false;		// case2 : ���� ���� ��
			sum_of_subsets(i + 1, weight, total - w[i+1]);
		}
	}
}
/*
	promising()�Լ�
		- Algorithm 5.4�� ������ �Լ�
		- ��尡 pomising���� �ƴ����� �Ǵ��ϴ� �Լ�
		- ���̸� �ǹ��ϴ� int�� ���� i, ������ ����ġ�� ���ġ �� ���� ����ġ�� �ǹ��ϴ�
		   int�� ���� weight�� total�� �Է¹޽��ϴ�.
		- ���� ����ġ�� ���� ����ġ�� ��ǥ ���� ���� ����
		- ��� ���̸� Ž�������� ��ǥġ�� ��ä�� ��� �Ǵ� ä���� ��ǥġ���� ���� ���
		- false�� �����մϴ�.
		- �������� �־��� ���̺��� �� ��� �������� false�� �����մϴ�.
*/
bool promising(int i, int weight, int total) {
	if (i == 7 )
		return false;
	else
		return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

/*
	modified_sum_of_subsets () �Լ�
		- Algorithm 5.4�� �����Ͽ� ������ �Լ�
		- ���� 16���� �ش�
		- sum_of_subset() �Լ��� �޸� ���� ���ϸ� Ž���� �����մϴ�.
		- ���� ���� check�� ����Ͽ� ���� ������ �ʾ��� �� Ž�� ����
*/
void modified_sum_of_subsets(int i, int weight, int total) {
	if (check)	// �̹� ���� ������ ���
		return;
	else if (promising(i, weight, total)) {
		if ((weight == W))	// ���� �����ϸ� ���
		{
			printf("\n>> �� ��� \n");
			for (int j = 0; j < nSize; j++)
				if (include[j] == true)
					printf("   w[%d] ���� \n", j);
			check = true;
		}
		else {
			include[i + 1] = true;	// case1 : ���� ��
			modified_sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = false;		// case2 : ���� ���� ��
			modified_sum_of_subsets(i + 1, weight, total - w[i+1]);
		}
	}
}
/*
	estimate() �Լ�
		- Algorithm 5.2 �� ������ �Լ�
		- ���� 17���� �ش�
		- Sum of Subsets ������ Monte Carlo ������� �����մϴ�.
		- ������ �����ϴ� ��� �ε����� ���� �Լ��� �����߽��ϴ�.
		- ������ �����Ͽ� ������ �ڽ� ��� �� �Ѱ����� ���� �մϴ�.
*/
int estimate() {

	const int t = 2;	// �־��� �������� �ڽ� ����� ��
	int numnodes = 1;	// ����� ����
	int m = 1;	// ������ �ڽ� ����� ����
	int mprod = 1;	// m�� ������
	int mWeight = 0;	// �������� �Ǵ��ϴ� �� ���̴� ����ġ ����
	int mTotal = 126; // �������� �Ǵ��ϴ� �� ���̴� �����ִ� ����ġ ���� ����
	int checking;	// ������ �����ϱ� ���� ����
	/*
		for �ݺ���
			- �ε��� i�� 0���� �������� �־��� ���̱��� �ݺ�
			- ������ �ڽ��� �� �̻� ������ �Լ� ����
	*/
		for (int i = 0; i < nSize; i++) {
			mprod = mprod * m;	// ������ �ڽ� ����� ���� m�� ���� ���� ������
			numnodes = numnodes + mprod * t;	// node�� �� += mprod+t
			if (promising(i + 1, mWeight + w[i + 1], mTotal - w[i + 1])) // ��带 �����ϴ� ��찡 ������ �� 
			{
				if (promising(i + 1, mWeight, mTotal - w[i + 1]))	// ��带 �������� �ʾƵ� ������ ���
				{
					m = 2;	// ������ �ڽ� ����� ��
					checking = rand() % m;	// ���� ����
					switch (checking) {	
					case 0:	 // 0 : w[i+1]�� �������� �ʴ� ���
						mTotal = mTotal - w[i + 1];
						break;
					case 1:	 // 0 : w[i+1]�� �����ϴ� ���
						mWeight = mWeight + w[i + 1];
						mTotal = mTotal - w[i + 1];
						break;
					}
				}
				else {	// w[i+1 ]��带 �����ϴ� ��츸 ������ ��
					m = 1;
					mWeight = mWeight + w[i + 1];
					mTotal = mTotal - w[i + 1];
				}
			}
			else if (promising(i + 1, mWeight, mTotal - w[i + 1]))	// w[i+1 ]��带 �������� �ʴ� ��츸 ������ ��
			{
				m = 1;
				mWeight = mWeight + w[i + 1];
				mTotal = mTotal - w[i + 1];
			}
			else {	// ������ ��尡 ���� ��
				m = 0;
				return numnodes;
			}
		}
	return numnodes;
}
