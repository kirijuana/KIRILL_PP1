// KIRILL_PP1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <pthread.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<string> FIO = { "������� ������ �������������", "������� ����� ����������", "�������� ��������� ����������", "����� ������ �����������" };
vector<int> sum = { 1500, 500000, 88000, 15000};
vector<int> month = { 10, 2, 5, 8};
int N = 0;

void *proizv(void *param)
{
	int i, p = (*(int *)param) * 2;
	int *buf; buf = new int; *buf = 1;
	
	for (int i = p; i < p + 2; i++)
	{
		*buf = sum[i];
		for (int j = 0; j < N; j++)
		{
			*buf = *buf + *buf / 100 * month[i];
		}
		sum[i] = *buf;		
	}
	return (void *)buf;

}

int main()
{

	pthread_t thread[2]; int number[2];

	printf("������� ����� N ");
	scanf_s("%d", &N);

	for (int i = 0; i<2; i++)
	{
		number[i] = i; //��� �������� ��������� ������
		pthread_create(&thread[i], NULL, proizv, (void *)(number + i));
	}

	for (int i = 0; i<2; i++)
	{ //�������� ���������� ������ �������� �������
	  //� ��������� ���������� �� ����������
		pthread_join(thread[i], NULL);
	}

	for (int i = 0; i < 4; i++)
	{
		cout << "������ ����� �����������: " << FIO[i] << ", " << sum[i] << ", " << month[i] << "\n";
	}
	return 0;
}

