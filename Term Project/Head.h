#pragma once
// C관련 헤더 파일
#include <stdio.h>
#include <stdlib.h>
#include <time.h>		
#include <string.h>


// Window 헤더 파일
#include <Windows.h>

// 매크로 선언
#define AND	&&
#define OR		||
#define SEED()	srand((unsigned)time(NULL))		// 시드(Seed)값 설정
#define random(a,b)	(rand() %b + a)				// 난수(a ~ b)
#define CLEAR() system("cls")						// 출력 화면을 비움
#pragma warning (disable:4996)						// 보안(_s)관련 함수 에러X

// 상수 선언
typedef int Bool;
enum { LEN = 50};
enum { NUM = 7, NAME = 21, WRITER = 19, PUBLISH = 15};

// 도서 구조체
typedef struct BOOK
{
	char num[NUM];				// 청구기호
	char name[NAME];			// 도서명
	char writer[WRITER];			// 저자
	char publish[PUBLISH];		// 발행사
	int year;						// 출판년도
	char state[6];				// 출판상태(정상, 대출);
}Book;

// 함수 선언
void Interface();				// 화면 출력

void RegistBook();			// 1. 도서 등록
void StateBook();			// 2. 도서 현황
void SearchBook();			// 3. 도서 검색
void BorrowBook();			// 4. 도서 대출
void ReturnBook();			// 5 .도서 반납

void Show1(char **);
void BubbleSort(Book *, int);			// 파일을 연도별로 출력하기 위한 버블 정렬
int BorrowSort(Book *, int);