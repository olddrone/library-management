#pragma once
// C���� ��� ����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>		
#include <string.h>


// Window ��� ����
#include <Windows.h>

// ��ũ�� ����
#define AND	&&
#define OR		||
#define SEED()	srand((unsigned)time(NULL))		// �õ�(Seed)�� ����
#define random(a,b)	(rand() %b + a)				// ����(a ~ b)
#define CLEAR() system("cls")						// ��� ȭ���� ���
#pragma warning (disable:4996)						// ����(_s)���� �Լ� ����X

// ��� ����
typedef int Bool;
enum { LEN = 50};
enum { NUM = 7, NAME = 21, WRITER = 19, PUBLISH = 15};

// ���� ����ü
typedef struct BOOK
{
	char num[NUM];				// û����ȣ
	char name[NAME];			// ������
	char writer[WRITER];			// ����
	char publish[PUBLISH];		// �����
	int year;						// ���ǳ⵵
	char state[6];				// ���ǻ���(����, ����);
}Book;

// �Լ� ����
void Interface();				// ȭ�� ���

void RegistBook();			// 1. ���� ���
void StateBook();			// 2. ���� ��Ȳ
void SearchBook();			// 3. ���� �˻�
void BorrowBook();			// 4. ���� ����
void ReturnBook();			// 5 .���� �ݳ�

void Show1(char **);
void BubbleSort(Book *, int);			// ������ �������� ����ϱ� ���� ���� ����
int BorrowSort(Book *, int);