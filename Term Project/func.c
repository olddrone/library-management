#include "Head.h"

void Interface()				// ȭ�� ���
{
	int ch;
	while (TRUE)
	{
		CLEAR();
		printf("���� ���� program \n\n");
		printf("1. ���� ��� \n");
		printf("2. ���� ��Ȳ \n");
		printf("3. ���� �˻� \n");
		printf("4. ���� ���� \n");
		printf("5. ���� �ݳ� \n");
		printf("6. ���� \n\n");

		printf("��ȣ�� �Է��ϰ� Enter > ");
		scanf("%d", &ch);
		switch (ch)

		{
		case 1:
			printf("1�� �Է�");
			RegistBook();
			break;
		case 2:
			printf("2�� �Է�");
			StateBook();
			break;
		case 3:
			printf("3�� �Է�");
			SearchBook();
			break;
		case 4:
			printf("4�� �Է�");
			BorrowBook();
			break;
		case 5:
			printf("5�� �Է�");
			ReturnBook();
			break;
		case 6:
			printf("���α׷��� �����մϴ�.");
			return;
		default:
			printf("���� �ٽ� �Է��ϼ���");
			break;
		}
	}
}

// 1. ���� ��� // �Ϸ�
void RegistBook()		
{
	Bool ch = TRUE;
	Book *book;
	FILE *f = fopen("book.txt", "ab");
	if (f == NULL)
	{
		puts("������ ���µ� ���� \n");
		return;
	}
	while (ch)
	{
		book = (Book *)malloc(sizeof(Book));
		CLEAR();
		printf("���� ��� \n\n");
		printf("û�� ��ȣ �Է� <�ִ� ���� 6��>  : ");
		scanf("%s", book->num);
		printf("������ �Է�    <�ִ� �ѱ� 10��> : ");
		scanf("%s", book->name);
		printf("���ڸ� �Է�    <�ִ� �ѱ� 9��>  : ");
		scanf("%s", book->writer);
		printf("����� �Է�    <�ִ� �ѱ� 7��>  : ");
		scanf("%s", book->publish);
		printf("���ǳ⵵ �Է�  <���� 4��>       : ");
		scanf("%d", &book->year);
		strcpy(book->state, "����");

		fprintf(f, "%s %s %s %s %d %s \n", book->num , book->name, book->writer, book->publish, book->year, book->state);

		puts("���� �Ϸ�");
		free(book);
		printf("��� �Է��Ͻðڽ��ϱ�?[1. ���, 0. ����] : ");
		scanf("%d", &ch);
		if (ch == FALSE)
			break;
		else
			continue;
	}
	fclose(f);
}   

// 2. ���� ��Ȳ // �Ϸ�
void StateBook()
{
	int i = 0, cnt, idx;				// �ݺ��� ���� �ε���
	int ch, CH = TRUE;			// ����
	Book store[LEN];			// ���� ������ ����

	FILE *f = fopen("book.txt", "rb");
	if (f == NULL)
	{
		puts("������ ���µ� ���� \n");
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
	printf("���� ��Ȳ\n\n");
	printf("������ ��Ȳ ��±��� �߿��� ���� \n\n");
	printf("1. ���� ��� \n");
	printf("2. ���� �⵵ \n");
	printf("3. ���� ���� \n");
	printf("4. ���� �޴��� \n\n");
	printf("��ȣ�� �Է��ϰ� Enter >> ");
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

			printf("���� ������ �������� �ʽ��ϴ�.\n enter�� ������ ���� �޴��� ���ư�");
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
		printf("�߸��Է��ϼ̽��ϴ�.");
		return;
	}

	CLEAR();
	printf("���� ��� ��Ȳ : �� %d�� \n\n", i);
	printf("û����ȣ                  ����                     ����                    �����                  ���ǳ⵵       ����\n");
	printf("======================================================================================================================\n"); 
	for (idx = 0; idx < i; idx++)
		printf("%-20s     %-20s       %-20s      %-20s      %-6d    %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);
	printf("\n\nEnter Ű�� ������ ���� �޴��� ���ư�");
	while (1)
	{
		ch = getch();
		if (ch == 13)
			return;
	}
}

// 3, ���� �˻� // �Ϸ�
void SearchBook()
{
	int i = 0, ch, idx = 0;
	char *search = NULL;
	Book store[LEN];
	FILE *f = fopen("book.txt", "rb");
	if (f == NULL)
	{
		puts("������ ���µ� ���� \n");
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
	printf("�����˻�\n\n");
	Show1(&search);
	if (strcmp(search, "ERR") == 0)
	{
		free(search);
		fclose(f);
		return;
	}
	printf("\n�˻����\n");
	printf("û����ȣ                  ����                     ����                    �����                  ���ǳ⵵       ����\n");
	printf("======================================================================================================================\n");
	for (idx = 0; idx < i; idx++)
	{
		if (strcmp(search, store[idx].name) == 0 OR strncmp(search, store[idx].num, strlen(search)) == 0 OR strcmp(search, store[idx].writer) == 0)
		{
			printf("%-20s     %-20s       %-20s      %-20s      %-6d    %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);
		}
	}
	printf("\n\nEnter Ű�� ������ ���� �޴��� ���ư�");
	free(search);
	fclose(f);
	while (1)
	{
		ch = getch();
		if (ch == 13)
			return;
	}
}

// 4. ���� ���� // �Ϸ�
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
		puts("������ ���µ� ���� \n");
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
	printf("���� ���� \n\n");
	printf("������ ������ �׸� ���� \n\n");
	Show1(&search);
	if (strcmp(search, "ERR") == 0)
	{
		free(search);
		fclose(f);
		fclose(f2);
		return;
	}
	printf("\n�˻����\n");
	printf("û����ȣ                  ����                     ����                    �����                  ���ǳ⵵       ����\n");
	printf("======================================================================================================================\n");
	for (idx = 0; idx < i; idx++)
	{
		if (strcmp(search, store[idx].name) == 0 OR strncmp(search, store[idx].num,strlen(search)) == 0 OR strcmp(search, store[idx].writer) == 0)
		{
			printf("%-20s     %-20s       %-20s      %-20s      %-6d    %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);

			printf("\n\n�� ������ �����Ϸ��� 1��, ��Ҵ� 0�� �Է� >");
			scanf("%d", &ch);
			if (ch == 1)
			{
				strcpy(store[idx].state, "����");
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
	printf("\n\nEnter Ű�� ������ ���� �޴��� ���ư�");
	while (1)
	{
		ch = getch();
		if (ch == 13)
			return;
	}
}

// 5 .���� �ݳ� // �Ϸ�
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
		puts("������ ���µ� ���� \n");
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
	printf("���� �ݳ� \n\n");
	printf("�ݳ��� ������ û����ȣ<6�ڸ�> �Է� �� Enter >");
	scanf("%s", &search);
	printf("û����ȣ                  ����                     ����                    �����                  ���ǳ⵵       ����\n");
	printf("======================================================================================================================\n");
	for (idx = 0; idx < i; idx++)
	{
		if (strncmp(search, store[idx].num,strlen(search)) == 0)
		{
			printf("%-20s     %-20s       %-20s      %-20s      %-6d    %s \n", store[idx].num, store[idx].name, store[idx].writer, store[idx].publish, store[idx].year, store[idx].state);

			printf("\n\n�� �ݳ��Ϸ��� 1��, ��Ҵ� 0�� �Է� >");
			scanf("%d", &ch);
			if (ch == 1)
			{
				strcpy(store[idx].state, "����");
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
	printf("\n\nEnter Ű�� ������ ���� �޴��� ���ư�");
	while (1)
	{
		ch = getch();
		if (ch == 13)
			return;
	}
}

// �Ϸ�
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

// �Ϸ�
int BorrowSort(Book *store, int cnt)
{
	Book temp;
	int i, j, idx = 0;
	for (i = 0; i < cnt; i++)
	{
		for (j = 0; j < cnt - i; j++)
		{
			if (strcmp(store[j+1].state, "����") == 0)
			{
				// ���� ������ ������ �ű��
				temp = store[j+1];
				store[j + 1] = store[j];
				store[j] = temp;
			}
		}
	}
	for (i = 0; i < cnt; i++)
	{
		if (strcmp(store[i].state, "����") == 0)
			idx++;
	}
	return idx;
}

// �Ϸ�
void Show1(char **search)
{
	int ch, len;
	char arr[LEN];
	printf("1. û����ȣ �Է� <�ִ� ���� 6��> \n");
	printf("2. ������ �Է� <�ִ� �ѱ� 10��> \n");
	printf("3. ��1 ���ڸ� �Է� <�ִ� �ѱ� 9��>\n");
	printf("4. ���� �޴��� \n\n");
	printf("��ȣ�� �Է��ϰ� Enter >> ");
	scanf("%d", &ch);
	CLEAR();
	switch (ch)
	{
	case 1:
		printf("�˻��� ������ û����ȣ�� �Է��ϰ� Enter \n");
		printf("û����ȣ �Է� <�ִ� ���� 6�ڸ�> : ");
		scanf("%s", &arr);
		break;
	case 2:
		printf("�˻��� ������ ������ �Է��ϰ� Enter \n");
		printf("������ �Է� <�ִ� �ѱ� 10�ڸ�> : ");
		scanf("%s", &arr);
		break;
	case 3:
		printf("�˻��� ������ ���ڸ��� �Է��ϰ� Enter \n");
		printf("���ڸ� �Է� <�ִ� 9�ڸ�> : ");
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
