#include "Head.h"

void Interface()				// 화면 출력
{
	int ch;
	while (TRUE)
	{
		CLEAR();
		printf("도서 관리 program \n\n");
		printf("1. 도서 등록 \n");
		printf("2. 도서 현황 \n");
		printf("3. 도서 검색 \n");
		printf("4. 도서 대출 \n");
		printf("5. 도서 반납 \n");
		printf("6. 종료 \n\n");

		printf("번호를 입력하고 Enter > ");
		scanf("%d", &ch);
		switch (ch)

		{
		case 1:
			printf("1번 입력");
			RegistBook();
			break;
		case 2:
			printf("2번 입력");
			StateBook();
			break;
		case 3:
			printf("3번 입력");
			SearchBook();
			break;
		case 4:
			printf("4번 입력");
			BorrowBook();
			break;
		case 5:
			printf("5번 입력");
			ReturnBook();
			break;
		case 6:
			printf("프로그램을 종료합니다.");
			return;
		default:
			printf("값을 다시 입력하세요");
			break;
		}
	}
}

// 1. 도서 등록 // 완료
void RegistBook()		
{
	Bool ch = TRUE;
	Book *book;
	FILE *f = fopen("book.txt", "ab");
	if (f == NULL)
	{
		puts("파일을 여는데 실패 \n");
		return;
	}
	while (ch)
	{
		book = (Book *)malloc(sizeof(Book));
		CLEAR();
		printf("도서 등록 \n\n");
		printf("청구 기호 입력 <최대 영문 6자>  : ");
		scanf("%s", book->num);
		printf("도서명 입력    <최대 한글 10자> : ");
		scanf("%s", book->name);
		printf("저자명 입력    <최대 한글 9자>  : ");
		scanf("%s", book->writer);
		printf("발행사 입력    <최대 한글 7자>  : ");
		scanf("%s", book->publish);
		printf("출판년도 입력  <정수 4자>       : ");
		scanf("%d", &book->year);
		strcpy(book->state, "정상");

		fprintf(f, "%s %s %s %s %d %s \n", book->num , book->name, book->writer, book->publish, book->year, book->state);

		puts("저장 완료");
		free(book);
		printf("계속 입력하시겠습니까?[1. 계속, 0. 종료] : ");
		scanf("%d", &ch);
		if (ch == FALSE)
			break;
		else
			continue;
	}
	fclose(f);
}   

// 2. 도서 현황 // 완료
void StateBook()
{
	int i = 0, cnt, idx;				// 반복문 관련 인덱스
	int ch, CH = TRUE;			// 선택
	Book store[LEN];			// 파일 정보를 담음

	FILE *f = fopen("book.txt", "rb");
	if (f == NULL)
	{
		puts("파일을 여는데 실패 \n");
		return;
	}
	while (!feof(f))
	{
		fscanf(f, "%s ", &*store[i].num);
		fscanf(f, "%s ", &*store[i].name);
		fscanf(f, "%s ", &*store[i].writer);
		fscanf(f, "%s ", &*store[i].publish);
		fscanf(f, "%d ", &store[i].year);
		fscanf(f, "%s ", &store[i].state);
		i++;
	}
	fclose(f);
	cnt = i;
	CLEAR();
	printf("도서 현황\n\n");
	printf("다음의 현황 출력기준 중에서 선택 \n\n");
	printf("1. 도서 등록 \n");
	printf("2. 출판 년도 \n");
	printf("3. 대출 도서 \n");
	printf("4. 이전 메뉴로 \n\n");
	printf("번호를 입력하고 Enter >> ");
	scanf("%d", &ch);
	switch (ch)
	{
	case 1:
		break;
	case 2:
		BubbleSort(store, cnt);
		break;
	case 3:
		i = BorrowSort(store, cnt);
		if (i == 0)
		{
			CLEAR();

			printf("대출 도서가 존재하지 않습니다.\n enter를 누르면 이전 메뉴로 돌아감");
			while (1)
			{
				ch = getch();
				if (ch == 13)
					return;
			}
		}
		break;
	case 4:
		return;
	default:
		printf("잘못입력하셨습니다.");
		return;
	}

	CLEAR();
	printf("도서 등록 현황 : 총 %d권 \n\n", i);
	printf("청구기호                  서명                     저자                    발행사                  출판년도       상태\n");
	printf("======================================================================================================================\n"); 
	for (idx = 0; idx < i; idx++)
		printf("%-20s     %-20s       %-20s      %-20s      %-6d    %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);
	printf("\n\nEnter 키를 누르면 이전 메뉴로 돌아감");
	while (1)
	{
		ch = getch();
		if (ch == 13)
			return;
	}
}

// 3, 도서 검색 // 완료
void SearchBook()
{
	int i = 0, ch, idx = 0;
	char *search = NULL;
	Book store[LEN];
	FILE *f = fopen("book.txt", "rb");
	if (f == NULL)
	{
		puts("파일을 여는데 실패 \n");
		return;
	}
	while (!feof(f))
	{
		fscanf(f, "%s ", &*store[i].num);
		fscanf(f, "%s ", &*store[i].name);
		fscanf(f, "%s ", &*store[i].writer);
		fscanf(f, "%s ", &*store[i].publish);
		fscanf(f, "%d ", &store[i].year);
		fscanf(f, "%s ", &store[i].state);
		i++;
	}
	CLEAR();
	printf("도서검색\n\n");
	Show1(&search);
	if (strcmp(search, "ERR") == 0)
	{
		free(search);
		fclose(f);
		return;
	}
	printf("\n검색결과\n");
	printf("청구기호                  서명                     저자                    발행사                  출판년도       상태\n");
	printf("======================================================================================================================\n");
	for (idx = 0; idx < i; idx++)
	{
		if (strcmp(search, store[idx].name) == 0 OR strncmp(search, store[idx].num, strlen(search)) == 0 OR strcmp(search, store[idx].writer) == 0)
		{
			printf("%-20s     %-20s       %-20s      %-20s      %-6d    %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);
		}
	}
	printf("\n\nEnter 키를 누르면 이전 메뉴로 돌아감");
	free(search);
	fclose(f);
	while (1)
	{
		ch = getch();
		if (ch == 13)
			return;
	}
}

// 4. 도서 대출 // 완료
void BorrowBook()
{
	int i = 0,idx=0;
	int ch;
	char *search = NULL;
	Book store[LEN];
	FILE *f = fopen("book.txt", "rb");
	FILE *f2 = fopen("replace.txt", "wb");
	if (f == NULL AND f2 == NULL)
	{
		puts("파일을 여는데 실패 \n");
		return;
	}
	while (!feof(f))
	{
		fscanf(f, "%s ", &*store[i].num);
		fscanf(f, "%s ", &*store[i].name);
		fscanf(f, "%s ", &*store[i].writer);
		fscanf(f, "%s ", &*store[i].publish);
		fscanf(f, "%d ", &store[i].year);
		fscanf(f, "%s ", &store[i].state);
		i++;
	}
	CLEAR();
	printf("도서 대출 \n\n");
	printf("대출할 도서의 항목 선택 \n\n");
	Show1(&search);
	if (strcmp(search, "ERR") == 0)
	{
		free(search);
		fclose(f);
		fclose(f2);
		return;
	}
	printf("\n검색결과\n");
	printf("청구기호                  서명                     저자                    발행사                  출판년도       상태\n");
	printf("======================================================================================================================\n");
	for (idx = 0; idx < i; idx++)
	{
		if (strcmp(search, store[idx].name) == 0 OR strncmp(search, store[idx].num,strlen(search)) == 0 OR strcmp(search, store[idx].writer) == 0)
		{
			printf("%-20s     %-20s       %-20s      %-20s      %-6d    %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);

			printf("\n\n위 도서를 대출하려면 1을, 취소는 0을 입력 >");
			scanf("%d", &ch);
			if (ch == 1)
			{
				strcpy(store[idx].state, "대출");
				printf("%-20s     %-20s       %-20s      %-20s      %-6d    %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);
			}
		}
	}
	for (idx = 0; idx < i; idx++)
	{
		fprintf(f2, "%s %s %s %s %d %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);
	}
	
	free(search);
	fclose(f);
	fclose(f2);
	remove("book.txt");
	rename("replace.txt", "book.txt");
	printf("\n\nEnter 키를 누르면 이전 메뉴로 돌아감");
	while (1)
	{
		ch = getch();
		if (ch == 13)
			return;
	}
}

// 5 .도서 반납 // 완료
void ReturnBook()
{
	int i = 0, idx = 0;
	int ch;
	char search[NUM];
	Book store[LEN];
	FILE *f = fopen("book.txt", "rb");
	FILE *f2 = fopen("replace.txt", "wb");
	if (f == NULL AND f2 == NULL)
	{
		puts("파일을 여는데 실패 \n");
		return;
	}
	while (!feof(f))
	{
		fscanf(f, "%s ", &*store[i].num);
		fscanf(f, "%s ", &*store[i].name);
		fscanf(f, "%s ", &*store[i].writer);
		fscanf(f, "%s ", &*store[i].publish);
		fscanf(f, "%d ", &store[i].year);
		fscanf(f, "%s ", &store[i].state);
		i++;
	}
	CLEAR();
	printf("도서 반납 \n\n");
	printf("반납할 도서의 청구기호<6자리> 입력 후 Enter >");
	scanf("%s", &search);
	printf("청구기호                  서명                     저자                    발행사                  출판년도       상태\n");
	printf("======================================================================================================================\n");
	for (idx = 0; idx < i; idx++)
	{
		if (strncmp(search, store[idx].num,strlen(search)) == 0)
		{
			printf("%-20s     %-20s       %-20s      %-20s      %-6d    %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);

			printf("\n\n위 반납하려면 1을, 취소는 0을 입력 >");
			scanf("%d", &ch);
			if (ch == 1)
			{
				strcpy(store[idx].state, "정상");
				printf("%-20s     %-20s       %-20s      %-20s      %-6d    %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);
			}

		}
	}
	for (int idx = 0; idx < i; idx++)
	{
		fprintf(f2, "%s %s %s %s %d %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);
	}

	fclose(f);
	fclose(f2);
	remove("book.txt");
	rename("replace.txt", "book.txt");
	printf("\n\nEnter 키를 누르면 이전 메뉴로 돌아감");
	while (1)
	{
		ch = getch();
		if (ch == 13)
			return;
	}
}

// 완료
void BubbleSort(Book *store, int cnt)
{
	Book temp;
	int i, j;
	for (i = 0; i <cnt -1; i++)
	{
		for (j = 0; j < cnt - i - 1; j++)
		{
			if (store[j].year > store[j+1].year)
			{
				temp = store[j];
				store[j] = store[j + 1];
				store[j + 1] = temp;
			}
		}
	}
	for (i = 0; i < cnt; i++)
		printf("%d \n", store[i].year);
}

// 완료
int BorrowSort(Book *store, int cnt)
{
	Book temp;
	int i, j, idx = 0;
	for (i = 0; i < cnt; i++)
	{
		for (j = 0; j < cnt - i; j++)
		{
			if (strcmp(store[j+1].state, "대출") == 0)
			{
				// 대출 도서를 앞으로 옮긴다
				temp = store[j+1];
				store[j + 1] = store[j];
				store[j] = temp;
			}
		}
	}
	for (i = 0; i < cnt; i++)
	{
		if (strcmp(store[i].state, "대출") == 0)
			idx++;
	}
	return idx;
}

// 완료
void Show1(char **search)
{
	int ch, len;
	char arr[LEN];
	printf("1. 청구기호 입력 <최대 영문 6자> \n");
	printf("2. 도서명 입력 <최대 한글 10자> \n");
	printf("3. 제1 저자명 입력 <최대 한글 9자>\n");
	printf("4. 이전 메뉴로 \n\n");
	printf("번호를 입력하고 Enter >> ");
	scanf("%d", &ch);
	CLEAR();
	switch (ch)
	{
	case 1:
		printf("검색할 도서의 청구기호를 입력하고 Enter \n");
		printf("청구기호 입력 <최대 영문 6자리> : ");
		scanf("%s", &arr);
		break;
	case 2:
		printf("검색할 도서의 도서명를 입력하고 Enter \n");
		printf("도서명 입력 <최대 한글 10자리> : ");
		scanf("%s", &arr);
		break;
	case 3:
		printf("검색할 도서의 저자명을 입력하고 Enter \n");
		printf("저자명 입력 <최대 9자리> : ");
		scanf("%s", &arr);
		break;
	case 4:
		strcpy(arr, "ERR");
		break;
	default:
		strcpy(arr, "ERR");
		break;
	}
	len = strlen(arr);
	*search = (char *)malloc(sizeof(char)*len + 1);
	strcpy(*search, arr);
}
