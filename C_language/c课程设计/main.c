#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#define LENB sizeof(struct Book)
#define LENR sizeof(struct Reader)
#define LENLB sizeof(struct LBook)
#define LENLR sizeof(struct LReader)
#define BORROWDAYS 20 //<20

//�ṹ����

struct Book //ͼ�����ݽṹ��!
{
	char NO[40];	 //ͼ����
	char name[100];  //����
	char writer[50]; //����
	int year;		 //�������
	float price;	 //����
	int innstore;	//���
	int all;		 //ͼ������
};
struct BorrowBook //����ͼ�����ݽṹ�� ��
{
	int enable;   //��Ԫ�Ƿ���Ч 1Ϊ��Ч 0��Ч
	char NO[40];  //����ͼ����
	int year[2];  //0��������ݣ�1���黹���
	int month[2]; //0�������·ݣ�1���黹�·�
	int day[2];   //0���������ڣ�1���黹����
};
struct Reader //�������ݽṹ�� !
{
	char NO[40];					  //���߱��
	char ID[30];					  //�����˺�
	char Password[30];				  //��������
	char name[20];					  //��������
	char sclass[20];				  //���߰༶
	struct BorrowBook BorrowBooks[5]; //���߽�����Ϣ
	int needpro;					  //���ߴ��������¼�(-1:�Ѿ�����Ƿ�� 0:�ޣ�1:����Ƿ�2����Ϣ����
};
struct LBook //ͼ������˫������ !
{
	struct LBook *last;
	struct Book info;
	struct LBook *next;
};
struct LReader //ͼ������˫������ !
{
	struct LReader *last;
	struct Reader info;
	struct LReader *next;
};

//ȫ�ֱ���

struct Reader ActReader;	  //��ǰ���� �������������
struct LReader *Rhead = NULL; //��������ͷ
struct LReader *rp1, *rp2;	//���ߵ�ǰָ��
struct LBook *Bhead = NULL;   //ͼ������ͷ
struct LBook *bp1, *bp2;	  //ͼ�鵱ǰָ�� ��bp1Ϊ�����ָ��
char options = '*';			  //�û�����ѡ��,��ʼΪ'*'
int ReaderPos = -1;			  //���������ļ�λ�ã���ֵΪ��Чֵ

//��������

void addlb(struct LBook *front, struct LBook *add) //ͼ��������� !
{
	if (front->next == NULL)
	{
		add->last = front;
		front->next = add;
	}
	else
	{
		front->next->last = add;
		add->next = front->next;
		add->last = front;
		front->next = add;
	}
}
void cBhead(struct LBook *NewHead) //ͼ������ɾ��ͷ !
{
	NewHead->last = NULL;
	NewHead->next = Bhead;
	Bhead->last = NewHead;
	Bhead = NewHead;
}
void dellb(struct LBook *del) //ͼ������ɾ�� !
{
	if (del->next == NULL)
	{
		del->last->next = NULL;
		free(del);
	}
	else if (del->last == NULL)
	{
		Bhead = del->next;
		Bhead->last = NULL;
		free(del);
	}
	else
	{
		del->last->next = del->next;
		del->next->last = del->last;
		free(del);
	}
}
void addlr(struct LReader *front, struct LReader *add) //����������� !
{ 
	if (front->next == NULL)
	{
		add->last = front;
		front->next = add;
	}
	else
	{
		front->next->last = add;
		add->next = front->next;
		add->last = front;
		front->next = add;
	}
}
void cRhead(struct LReader *NewHead) //��������ͷ��
{
	NewHead->last = NULL;
	NewHead->next = Rhead;
	Rhead->last = NewHead;
	Rhead = NewHead;
}
void dellr(struct LReader *del) //��������ɾ�� !
{
	if (del->next == NULL)
	{
		del->last->next = NULL;
		free(del);
	}
	else if (del->last == NULL)
	{
		Rhead = del->next;
		Rhead->last = NULL;
		free(del);
	}
	else
	{
		del->last->next = del->next;
		del->next->last = del->last;
		free(del);
	}
}

//ϵͳͨ�ú���

struct tm *gettime() //���ʱ�䣡
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	return p;
}
int Isstreq(char *str1, char *str2) //�ַ�������жϣ�
{
	int i;
	int result = 1;
	for (i = 0; !(*str1 == '\0' && *str2 == '\0'); str1++, str2++)
	{
		if (*str1 != *str2)
		{
			result = 0;
			break;
		}
	}
	return result;
}
void xy(int x, int y) //���������ʾ !
{
	COORD pos = {x, y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
int searchb() //ͼ������
{
	while (1) //����ѭ��
	{
		char seachstr[40];
		while (1) //��ȷ����ѭ��
		{
			system("cls");
			xy(47, 6);
			printf("       ͼ������       ");
			xy(47, 7);
			printf("----------------------");

			xy(47, 9);
			printf("1.����");

			xy(47, 11);
			printf("2.����");

			xy(47, 13);
			printf("b.����");

			xy(47, 15);
			printf("----------------------");

			xy(47, 17);
			printf("��ѡ��������ʽ��\t");
			scanf("%c", &options);
			fflush(stdin);
			if (options == '1' || options == '2' || options == 'b')
				break;
			xy(47, 17);
			printf("                                          ");
			xy(47, 17);
			printf("��������Чѡ�");
			sleep(1);
			xy(47, 17);
			printf("                                          ");
		}
		if (options == '1') //������
		{
			while (1)
			{
				int num = 0;
				int j = 0;
				char cexit[5] = "exit";
				system("cls");
				xy(19, 4);
				printf("                                 ͼ  ��  ��  Ϣ                             ");
				xy(19, 5);
				printf("----------------------------------------------------------------------------");
				xy(19, 6);
				printf("���");
				xy(27, 6);
				printf("ͼ����");
				xy(39, 6);
				printf("����");
				xy(47, 6);
				printf("����");
				xy(55, 6);
				printf("�������");
				xy(67, 6);
				printf("�۸�");
				xy(75, 6);
				printf("�ڹ�����");
				xy(19, 16);
				printf("----------------------------------------------------------------------------");
				xy(19, 17);
				printf("������������(����exit�˳�)\t");
				scanf("%s", seachstr);
				fflush(stdin);
				bp1 = Bhead;
				if (Isstreq(cexit, seachstr))
					break;
				while (1) //����
				{
					int flag = 0; //�Ƿ�ƥ��
					int i = 0;
					int start = 0;
					j = 0;									  //ƥ���ַ���ʹ�ü�����������
					while (bp1->info.name[i + start] != '\0') //ƥ�����
					{

						if (bp1->info.name[i + start] == seachstr[j])
						{
							i++;
							j++;
						}
						else
						{
							start++;
							i = 0;
							j = 0;
						}
						if (seachstr[j] == '\0')
						{
							flag = 1;
							break;
						}
					}
					if (bp1->next == NULL)
						break;
					if (flag == 0) //��ƥ�䣬��һ��
					{
						if (bp1->next == NULL)
							break;
						bp1 = bp1->next;
						continue;
					}
					else //ƥ�����
					{
						num++;
						xy(19, 6 + num);
						printf("%d", num);
						xy(27, 6 + num);
						printf("%s", bp1->info.NO);
						xy(39, 6 + num);
						printf("%s", bp1->info.name);
						xy(47, 6 + num);
						printf("%s", bp1->info.writer);
						xy(55, 6 + num);
						printf("%d", bp1->info.year);
						xy(67, 6 + num);
						printf("%.2f", bp1->info.price);
						xy(75, 6 + num);
						printf("%d", bp1->info.innstore);
						if (bp1->next == NULL)
							break;
						bp1 = bp1->next;
					}
				}
				bp1 = Bhead;
				xy(19, 17);
				printf("                                                ");
				xy(19, 17);
				printf("������ɣ�");
				sleep(1);
				xy(19, 17);
				printf("                                                   ");
				xy(19, 17);
				printf("�����������\t");
				scanf("%c", &options);
				fflush(stdin);
				options = '1';
			}
		}
		if (options == '2') //������
		{
			while (1)
			{
				int j;
				int num = 0;
				int flag = 0;
				char cexit[5] = "exit";
				system("cls");
				xy(19, 4);
				printf("                                 ͼ  ��  ��  Ϣ                             ");
				xy(19, 5);
				printf("----------------------------------------------------------------------------");
				xy(19, 6);
				printf("���");
				xy(27, 6);
				printf("ͼ����");
				xy(39, 6);
				printf("����");
				xy(47, 6);
				printf("����");
				xy(55, 6);
				printf("�������");
				xy(67, 6);
				printf("�۸�");
				xy(75, 6);
				printf("�ڹ�����");
				xy(19, 16);
				printf("----------------------------------------------------------------------------");
				xy(19, 17);
				printf("����������ȫ����(����exit�˳�)\t");
				scanf("%s", seachstr);
				fflush(stdin);
				if (Isstreq(cexit, seachstr))
					break;
				while (1)
				{
					//�Ƿ�ƥ��
					if (Isstreq(bp1->info.writer, seachstr))
					{
						flag = 1;
					}
					if (flag == 0) //��ƥ�䣬��һ��
					{
						if (bp1->next == NULL)
							break;
						bp1 = bp1->next;
						continue;
					}
					else //ƥ�����
					{
						num++;
						xy(19, 6 + num);
						printf("%d", num);
						xy(27, 6 + num);
						printf("%s", bp1->info.NO);
						xy(39, 6 + num);
						printf("%s", bp1->info.name);
						xy(47, 6 + num);
						printf("%s", bp1->info.writer);
						xy(55, 6 + num);
						printf("%d", bp1->info.year);
						xy(67, 6 + num);
						printf("%.2f", bp1->info.price);
						xy(75, 6 + num);
						printf("%d", bp1->info.innstore);
						flag = 0;
					}
					if (bp1->next == NULL)
						break;
					bp1 = bp1->next;
				}
				bp1 = Bhead;
				xy(19, 17);
				printf("                                                ");
				xy(19, 17);
				printf("������ɣ�");
				sleep(1);
				xy(19, 17);
				printf("                                                   ");
				xy(19, 17);
				printf("�����������\t");
				scanf("%c", &options);
				fflush(stdin);
				options = '2';
			}
		}
		if (options == 'b')
		{
			options = '*';
			break;
		}
	}
}
void save(int i) //�����ļ�ͼ�飬i���Ʊ�������(1Ϊȫ�����ߣ�0Ϊͼ��,2λ��������)!
{
	if (i == 0) //ͼ������
	{
		FILE *sf;
		struct LBook *head;
		head = Bhead;
		sf = fopen("books.dat", "wb");
		rewind(sf);
		while (head != NULL)
		{
			fwrite(&head->info, LENB, 1, sf);
			head = head->next;
		}
		fclose(sf);
	}
	else if (i == 1)
	{
		FILE *sf;
		struct LReader *head;
		head = Rhead;
		sf = fopen("readers.dat", "wb");
		rewind(sf);
		while (head != NULL)
		{
			fwrite(&head->info, LENR, 1, sf);
			head = head->next;
		}
		fclose(sf);
	}
	else
	{
		FILE *sf;
		struct LReader *head;
		head = Rhead;
		sf = fopen("readers.dat", "rb+");
		rewind(sf);
		fseek(sf, ReaderPos * LENR, 0);
		fwrite(&ActReader, LENR, 1, sf);
		fclose(sf);
	}
}
void read(FILE *f, int LEND) //��ȡ�����ļ� ,fΪ�����ļ�ָ�룬LENDΪ�������ݳ���!
{
	if (LEND == LENB)
	{
		int i;
		int n = 0;
		bp2 = bp1 = (struct LBook *)malloc(LENLB);
		rewind(f);
		fread(&bp1->info, LEND, 1, f);
		for (i = 1; !feof(f); i++)
		{
			n++;
			if (n == 1)
			{
				bp1->last = NULL;
				Bhead = bp1;
			}
			else
			{
				bp2->next = bp1;
				bp1->last = bp2;
			}
			bp2 = bp1;
			bp1 = (struct LBook *)malloc(LENLB);
			fseek(f, i * LENB, 0);
			fread(&bp1->info, LENB, 1, f);
		}
		free(bp1);
		bp1 = bp2;
		bp2->next = NULL;
	}
	else if (LEND == LENR)
	{
		int i;
		int n = 0;
		rp2 = rp1 = (struct LReader *)malloc(LENLR);
		rewind(f);
		fread(&rp1->info, LENR, 1, f);
		for (i = 1; !feof(f); i++)
		{
			n++;
			if (n == 1)
			{
				rp1->last = NULL;
				Rhead = rp1;
			}
			else
			{
				rp2->next = rp1;
				rp1->last = rp2;
			}
			rp2 = rp1;
			rp1 = (struct LReader *)malloc(LENLR);
			fseek(f, i * LENR, 0);
			fread(&rp1->info, LENR, 1, f);
		}
		free(rp1);
		rp1 = rp2;
		rp2->next = NULL;
	}
}
void singoneBlink() //��ݴӴ�С��˳��洢! bp1Ϊ�����ӵ�Ԫָ�룡
{
	int flag = 0; //δ����Ϊ0
	bp2 = Bhead;
	while (bp2->next != NULL)
	{
		if (Bhead->info.year < bp1->info.year)
		{
			cBhead(bp1);
			flag = 1;
			break;
		}
		if ((bp2->info.year >= bp1->info.year) && (bp2->next->info.year < bp1->info.year))
		{
			addlb(bp2, bp1);
			flag = 1;
			break;
		}
		bp2 = bp2->next;
	}
	if (flag == 0)
		addlb(bp2, bp1);
	bp2 = Bhead; //���صȴ���һ�ε���
}
void creatonebook() //��������ͼ�飬��singonelinkһ��ʹ��!
{
	int flag;
	bp1 = (struct LBook *)malloc(LENLB);

	//���벻�ظ���NO
	flag = 1; //flag�����ж϶Գ���ʽ��flagΪ1�������˳�������break
	bp2 = Bhead;
	system("cls");
	xy(47, 6);
	printf("         ͼ����Ϣ         ");
	xy(47, 7);
	printf("--------------------------");

	xy(47, 9);
	printf("ͼ����:");

	xy(47, 11);
	printf("����:");

	xy(47, 13);
	printf("ͼ������:");

	xy(47, 15);
	printf("ͼ�鵥��:");

	xy(47, 17);
	printf("�������:");

	xy(47, 19);
	printf("ͼ������:");

	xy(47, 21);
	printf("---------------------------");
	while (flag == 1)
	{
		xy(56, 9);
		scanf("%s", bp1->info.NO);
		fflush(stdin);
		for (; flag = (bp2->next != NULL); bp2 = bp2->next)
		{
			if (Isstreq(bp2->info.NO, bp1->info.NO))
			{
				xy(56, 9);
				printf("                                         ");
				xy(56, 9);
				printf("ͼ�����ظ�������������!");
				sleep(1);
				xy(56, 9);
				printf("                                         ");
				break;
			}
		}
	}
	bp2 = Bhead;

	xy(52, 11);
	scanf("%s", bp1->info.name);
	fflush(stdin);
	xy(56, 13);
	scanf("%s", bp1->info.writer);
	fflush(stdin);
	xy(56, 15);
	scanf("%f", &bp1->info.price);
	fflush(stdin);
	xy(56, 17);
	scanf("%d", &bp1->info.year);
	fflush(stdin);
	xy(56, 19);
	scanf("%d", &bp1->info.all);
	fflush(stdin);
	bp1->info.innstore = bp1->info.all;
	bp1->last = bp1->next = NULL;
	singoneBlink();
}
int IsBookOverate(int i) //�жϵ�n-1�����Ƿ���!
{
	int result = 0;
	struct tm *ntime;
	ntime = gettime();
	if (ActReader.BorrowBooks[i].enable == 1)
	{
		if (ActReader.BorrowBooks[i].year[1] < (ntime->tm_year + 1900)) //������
		{
			result = 1;
		}
		else
		{
			if ((ActReader.BorrowBooks[i].month[1] < 1 + ntime->tm_mon) && (ActReader.BorrowBooks[i].year[1] == (ntime->tm_year + 1900))) //������
			{
				result = 1;
			}
			else
			{
				if ((ActReader.BorrowBooks[i].day[1] < ntime->tm_mday) && (ActReader.BorrowBooks[i].month[1] == 1 + ntime->tm_mon)) //������
				{
					result = 1;
				}
			}
		}
	}
	return result;
}
void ReaderPrePro() //������ϢԤ���� ������Ƿ����Ϣ!
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if (ActReader.needpro == -1)
		{
			ActReader.needpro = 0;
			break;
		}
		if (IsBookOverate(i))
			ActReader.needpro = 1;
		break;
	}
}
struct LBook *NO2Book(char *NO) //����ͼ��������!
{
	struct LBook *result = NULL;
	bp1 = Bhead;
	while (1)
	{
		if (Isstreq(bp1->info.NO, NO))
		{
			result = bp1;
			break;
		}
		if (bp1->next == NULL)
			break;
		bp1 = bp1->next;
	}
	bp1 = Bhead;
	return result;
}
struct LReader *NO2Reader(char *NO) //����ͼ��������!
{
	struct LReader *result = NULL;
	while (1)
	{
		if (Isstreq(rp1->info.NO, NO))
		{
			result = rp1;
			break;
		}
		if (rp1->next == NULL)
			break;
		rp1 = rp1->next;
	}
	rp1 = Rhead;
	return result;
}
void filldeadline(int i) //�Զ����ͼ��黹����!
{
	int days = BORROWDAYS;
	int dayslist[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	dayslist[1] += ((ActReader.BorrowBooks[i].year[0] % 4 == 0) && (ActReader.BorrowBooks[i].year[0] % 100 != 0) || (ActReader.BorrowBooks[i].year[0] % 400 == 0));
	if (dayslist[ActReader.BorrowBooks[i].month[0]] - days - ActReader.BorrowBooks[i].day[0] >= 0)
	{
		ActReader.BorrowBooks[i].year[1] = ActReader.BorrowBooks[i].year[0];
		ActReader.BorrowBooks[i].month[1] = ActReader.BorrowBooks[i].month[0];
		ActReader.BorrowBooks[i].day[1] = ActReader.BorrowBooks[i].day[0] + days;
	}
	else
	{
		if (ActReader.BorrowBooks[i].month[0] + 1 <= 12)
		{
			ActReader.BorrowBooks[i].year[1] = ActReader.BorrowBooks[i].year[0];
			ActReader.BorrowBooks[i].month[1] = ActReader.BorrowBooks[i].month[0] + 1;
			ActReader.BorrowBooks[i].day[1] = ActReader.BorrowBooks[i].day[0] + days - dayslist[ActReader.BorrowBooks[i].month[0]];
		}
		else
		{
			ActReader.BorrowBooks[i].year[1] = ActReader.BorrowBooks[i].year[0] + 1;
			ActReader.BorrowBooks[i].month[1] = 1;
			ActReader.BorrowBooks[i].day[1] = ActReader.BorrowBooks[i].day[0] + days - dayslist[ActReader.BorrowBooks[i].month[0]];
		}
	}
}
void freelReader() //�ͷŶ��������ڴ�!
{
	rp2 = Rhead->next;
	while (rp1->next == NULL)
	{
		rp1 = rp2->next;
		free(rp2);
		rp2 = rp1;
	}
	free(rp1);
	rp1 = rp2 = Rhead;
	Rhead = NULL;
}
void showbooks() //��ʾͼ�飡
{
	int j = 0;
	bp1 = Bhead;
	system("cls");
	xy(19, 4);
	printf("                                 ͼ  ��  ��  Ϣ                                 ");
	xy(19, 5);
	printf("--------------------------------------------------------------------------------");
	xy(19, 6);
	printf("���");
	xy(27, 6);
	printf("ͼ����");
	xy(39, 6);
	printf("����");
	xy(47, 6);
	printf("����");
	xy(55, 6);
	printf("�������");
	xy(67, 6);
	printf("�۸�");
	xy(75, 6);
	printf("�ڹ�����");

	while (1)
	{
		int flag = 0;
		int w = 0;
		while (1)
		{
			j++;
			w++;
			xy(19, 6 + w);
			printf("                                                                              "); //�������
			if (flag == 0)
			{
				xy(19, 6 + w);
				printf("%d", j);
				xy(27, 6 + w);
				printf("%s", bp1->info.NO);
				xy(39, 6 + w);
				printf("%s", bp1->info.name);
				xy(47, 6 + w);
				printf("%s", bp1->info.writer);
				xy(55, 6 + w);
				printf("%d", bp1->info.year);
				xy(67, 6 + w);
				printf("%.2f", bp1->info.price);
				xy(75, 6 + w);
				printf("%d", bp1->info.innstore);
			}

			if (w >= 10)
				break;
			if (bp1->next == NULL)
				flag = 1;
			else
				bp1 = bp1->next;
		}
		xy(19, 17);
		printf("--------------------------------------------------------------------------------");
		if (bp1->next == NULL)
		{
			xy(19, 18);
			printf("                                                ");
			xy(19, 18);
			printf("�����������\t");
			scanf("%d", &w);
			fflush(stdin);
			break;
		}
		else
		{
			xy(19, 18);
			printf("                                                ");
			xy(19, 18);
			printf("��0.����\t����.��һҳ\t");
			scanf("%d", &w);
			fflush(stdin);
			bp1 = bp1->next;
			if (w == 0)
				break;
		}
	}
	bp1 = Bhead;
}
void showreaders() //��ʾ���ߣ�
{
	int j = 0;
	system("cls");
	xy(19, 4);
	printf("                                 ��  ��  ��  Ϣ                             ");
	xy(19, 5);
	printf("----------------------------------------------------------------------------");
	xy(19, 6);
	printf("���");
	xy(28, 6);
	printf("���߱��");
	xy(41, 6);
	printf("����");
	xy(50, 6);
	printf("�༶");
	xy(59, 6);
	printf("�Ƿ��Ƿ�����δ��");
	while (1)
	{
		int flag = 0;
		int w = 0;
		while (1)
		{
			j++;
			w++;
			xy(19, 6 + j);
			printf("                                                                              "); //�������
			if (flag == 0)
			{
				xy(19, 6 + w);
				printf("%d", j);
				xy(28, 6 + w);
				printf("%s", rp1->info.NO);
				xy(41, 6 + w);
				printf("%s", rp1->info.name);
				xy(50, 6 + w);
				printf("%s", rp1->info.sclass);
				if (rp1->info.needpro == 1)
				{
					xy(59, 6 + w);
					printf("��");
				}
				else
				{
					xy(59, 6 + w);
					printf("��");
				}
			}
			if (w >= 10)
				break;
			if (rp1->next == NULL)
				flag = 1;
			else
				rp1 = rp1->next;
		}
		xy(19, 17);
		printf("----------------------------------------------------------------------------");
		if (rp1->next == NULL)
		{
			xy(19, 18);
			printf("                                              ");
			xy(19, 18);
			printf("�����������\t");
			scanf("%d", &w);
			fflush(stdin);
			break;
		}
		else
		{
			xy(19, 18);
			printf("                                            ");
			xy(19, 18);
			printf("0.����\t����.��һҳ\t");
			scanf("%d", &w);
			fflush(stdin);
			rp1 = rp1->next;
			if (w == 0)
				break;
		}
	}
	rp1 = Rhead;
}

// ϵͳ������

void login() //��¼,ע��,���ߵ�¼���� 1 ������Ա���� 0
{
	int winshow = 0;
	FILE *f;	  //open readers.dat
	int flag = 1; //0ע��    ����  1��½
	while (ReaderPos == -1)
	{

		xy(47, 6);
		printf("     ��ӭ����LMS      ");
		xy(47, 7);
		printf("----------------------");

		xy(47, 9);
		printf("   1.��¼");

		xy(47, 11);
		printf("   0.ע��");

		xy(47, 13);
		printf("----------------------");
		xy(47, 14);
		while (1) //�����Ч����
		{
			scanf("%d", &flag);
			fflush(stdin);
			if ((flag == 1) || (flag == 0))
				break;
			else
			{
				xy(47, 14);
				;
				printf(" ������0��1��");
				sleep(1);
				xy(47, 14);
				;
				printf("                  ");
				xy(47, 14);
				;
			}
		}

		while (flag == 1) //��¼ __����Ψһ����__ͨ���ı�ReaderPos
		{
			int i;			   //�ļ�����λ��
			char ID[30];	   //�����˺�
			char Password[30]; //��������
			system("cls");
			xy(47, 6);
			printf("       ��   ¼       ");
			xy(47, 7);
			printf("---------------------");

			xy(47, 9);
			printf("�����û���:");

			xy(47, 11);
			printf("��������:");

			xy(47, 13);
			printf("----------------------");
			xy(58, 9);
			scanf("%s", ID);
			fflush(stdin);
			xy(56, 11);
			scanf("%s", Password);
			fflush(stdin);
			f = fopen("readers.dat", "rb"); //--------------------------------------try catch
			rewind(f);
			for (i = 0; !feof(f); i++)
			{
				fseek(f, i * LENR, 0);
				fread(&ActReader, LENR, 1, f);
				if (Isstreq(ActReader.ID, ID) && Isstreq(ActReader.Password, Password))
				{
					ReaderPos = i;
					break;
				}
			}
			if (ReaderPos != -1)
				break; //��ɵ�¼ ���˳�
			fclose(f);
			xy(47, 14);
			printf("��Ǹ�������û������������");
			sleep(1);
		}

		while (flag == 0) //ע��
		{
			int i; //ѭ������
			struct Reader TempReader;
			system("cls");
			xy(47, 6);
			printf("       ע   ��       ");
			xy(47, 7);
			printf("---------------------");

			xy(47, 9);
			printf("�����û���:");

			xy(47, 11);
			printf("��������:");

			xy(47, 13);
			printf("����ѧ��:");

			xy(47, 15);
			printf("��������:");

			xy(47, 17);
			printf("���İ༶:");

			xy(47, 19);
			printf("----------------------");

			//���벻�ظ���ID
			flag = 1; //flag�����ж϶Գ���ʽ��flagΪ1�������˳�������break
			while (flag == 1)
			{

				xy(58, 9);
				scanf("%s", TempReader.ID);
				fflush(stdin);
				f = fopen("readers.dat", "rb"); //--------------------------------------try catch
				rewind(f);
				for (i = 0; flag = (!feof(f)); i++)
				{
					fseek(f, i * LENR, 0);
					fread(&ActReader, LENR, 1, f);
					if (Isstreq(ActReader.ID, TempReader.ID))
					{
						xy(58, 9);
						printf("�û����ظ�������������!");
						sleep(1);
						xy(58, 9);
						printf("                           ");
						xy(58, 9);
						break;
					}
				}
				fclose(f);
			}
			flag = 0;
			//�ָ��ж�flagԭ����

			xy(56, 11);
			scanf("%s", TempReader.Password);
			fflush(stdin);

			//���벻�ظ���NO
			flag = 1; //flag�����ж϶Գ���ʽ��flagΪ1�������˳�������break
			while (flag == 1)
			{
				xy(56, 13);
				scanf("%s", TempReader.NO);
				fflush(stdin);
				f = fopen("readers.dat", "rb"); //--------------------------------------try catch
				rewind(f);
				for (i = 0; flag = (!feof(f)); i++)
				{
					fseek(f, i * LENR, 0);
					fread(&ActReader, LENR, 1, f);
					if (ActReader.NO == TempReader.NO)
					{
						xy(56, 13);
						printf("ѧ���ظ����������������!");
						sleep(1);
						xy(56, 13);
						printf("                                 ");
						xy(56, 13);
						break;
					}
				}
				fclose(f);
			}
			flag = 0;
			//�ָ��ж�flagԭ����

			xy(56, 15);
			scanf("%s", TempReader.name);
			fflush(stdin);
			xy(56, 17);
			scanf("%s", TempReader.sclass);
			fflush(stdin);
			TempReader.needpro = 0;
			for (i = 0; i < 5; i++) //������Ϣ��ʼ��
			{
				TempReader.BorrowBooks[i].enable = 0;
			}
			f = fopen("readers.dat", "ab");
			fwrite(&TempReader, LENR, 1, f);
			fclose(f);
			xy(47, 20);
			printf("ע��ɹ���");
			sleep(3);
			system("cls");
			flag = 1;
		}
	}
}
void readerpro() //���߷��� 
{
	int i; //��������
	options = '*';
	ReaderPrePro(); //������ϢԤ����
	while (1)
	{
		system("cls");
		xy(38, 6);
		printf(" �װ��� %s �����ã�", ActReader.name);
		xy(38, 7);
		printf("-----------------------------------------------");

		xy(38, 9);
		printf("1.�鿴������Ϣ");

		xy(38, 11);
		printf("2.�鿴ͼ��������");

		xy(38, 13);
		printf("3.�鿴ͼ��");

		xy(38, 15);
		printf("4.ͼ�����");

		xy(38, 17);
		printf("5.ͼ��黹");

		xy(38, 19);
		printf("6.����ͼ��");

		xy(38, 21);
		printf("7.�˳�");

		xy(38, 23);
		printf("-----------------------------------------------");
		xy(38, 24);
		scanf("%c", &options);
		fflush(stdin);
		switch (options)
		{
		case '1': //�鿴������Ϣ
		{
			//��ʾ
			system("cls");
			xy(47, 6);
			printf("       ������Ϣ       ");
			xy(47, 7);
			printf("----------------------");

			xy(47, 9);
			printf("�����û���: %s", ActReader.ID);

			xy(47, 11);
			printf("����ѧ��: %s", ActReader.NO);

			xy(47, 13);
			printf("��������: %s", ActReader.name);

			xy(47, 15);
			printf("���İ༶: %s", ActReader.sclass);

			xy(47, 17);
			printf("Ƿ�����:");

			xy(47, 19);
			printf("----------------------");
			xy(47, 20);
			if (ActReader.needpro == 0 || ActReader.needpro == -1)
			{
				xy(56, 17);
				printf(" ��Ƿ��");
				xy(47, 20);
			}
			else if (ActReader.needpro == 1)
			{
				xy(56, 17);
				printf(" ��Ƿ���¼��");
				xy(47, 20);
			}
			xy(47, 20);
			printf("�����������\t");
			//��һ������
			scanf("%c", &options);
			fflush(stdin);
			options = '*';
			break;
		}
		case '2': //�鿴ͼ��������
		{
			int j = 0;
			system("cls");
			xy(18, 4);
			printf("                                 ͼ  ��  ��  ��  ��  Ϣ                             ");
			xy(18, 5);
			printf("------------------------------------------------------------------------------------");
			xy(18, 6);
			printf("���");
			xy(26, 6);
			printf("ͼ����");
			xy(38, 6);
			printf("����");
			xy(46, 6);
			printf("����");
			xy(54, 6);
			printf("�������");
			xy(66, 6);
			printf("�۸�");
			xy(74, 6);
			printf("��������");
			xy(86, 6);
			printf("�黹����");
			xy(98, 6);
			printf("��ע");
			for (i = 0; i < 5; i++) //ͼ����Ϣ���
			{

				if (ActReader.BorrowBooks[i].enable == 1)
				{
					struct LBook *tempp;
					j++;
					tempp = NO2Book(ActReader.BorrowBooks[i].NO);
					xy(18, 6 + 2 * j);
					printf("%d", j);
					xy(26, 6 + 2 * j);
					printf("%s", ActReader.BorrowBooks[i].NO);
					xy(38, 6 + 2 * j);
					printf("%s", tempp->info.name);
					xy(46, 6 + 2 * j);
					printf("%s", tempp->info.writer);
					xy(54, 6 + 2 * j);
					printf("%d", tempp->info.year);
					xy(66, 6 + 2 * j);
					printf("%.2f", tempp->info.price);
					xy(74, 6 + 2 * j);
					printf("%d-%d-%d", ActReader.BorrowBooks[i].year[0], ActReader.BorrowBooks[i].month[0], ActReader.BorrowBooks[i].day[0]);
					xy(86, 6 + 2 * j);
					printf("%d-%d-%d", ActReader.BorrowBooks[i].year[1], ActReader.BorrowBooks[i].month[1], ActReader.BorrowBooks[i].day[1]);
					if (IsBookOverate(i))
					{
						xy(98, 7 + 6 + 2 * j);
						printf("�������ޣ�");
					}
				}
			}
			xy(18, 17);
			printf("------------------------------------------------------------------------------------");
			xy(18, 18);
			printf("���κμ�����\t");
			scanf("%c", &options);
			options = '*';
			break;
		}
		case '3': //�鿴ͼ�� \\�����������
		{
			showbooks();
			options = '*';
			break;
		}
		case '4': //���� ��Ƿ��ɽ� ������ͼ������
		{
			int i;	 //ѭ������
			int j = 0; //��������
			system("cls");
			xy(38, 6);
			printf("             ͼ�����              ");
			xy(38, 7);
			printf("----------------------------------");
			//�ж��Ƿ�Ƿ��
			if (ActReader.needpro == 1)
			{
				xy(38, 9);
				printf("������Ƿ��δ�����뽻��Ƿ�����飡");
				xy(38, 11);
				printf("----------------------------------");
				xy(38, 13);
				printf("���κμ�����\t");
				scanf("%c", &options);
				options = '*';
				break;
			}

			while (1) //�������������屾
			{
				struct tm *ntime;
				char NO[40];
				char cexit[5] = "exit";
				j = 0;
				//�ж��Ƿ����//j��¼����λ��
				while (i < 5) //�ж��Ƿ����
				{
					if (ActReader.BorrowBooks[i].enable == 1)
						j++;
					else
					{
						j = i;
						break;
					}
					i++;
				}
				i = 0;

				if (j == 5) //������ʾ
				{
					xy(38, 9);
					printf("���Ѿ��������屾�飡��ʱ���ܽ��飡");
					xy(38, 11);
					printf("----------------------------------");
					xy(38, 13);
					printf("���κμ�����\t");
					scanf("%c", &options);
					options = '*';
					break;
				}
				while (1)//ȷ���н���Ȩ��
				{
					system("cls");
					xy(38, 6);
					printf("             ͼ�����              ");
					xy(38, 7);
					printf("----------------------------------");
					xy(38, 9);
					printf("������ͼ���ţ�(�˳�������exit)");
					xy(38, 11);
					printf("----------------------------------");
					xy(38, 13);
					scanf("%s", NO);
					if (Isstreq(NO, cexit))
						break;
					bp1 = NO2Book(NO);
					if (bp1 == NULL)
					{
						xy(38, 13);
						printf("                                 ");
						xy(38, 13);
						printf("��Ǹ���޴�ͼ����Ϣ��");
						sleep(1);
						xy(38, 13);
						printf("                                 ");
						continue;
					}
					else if (bp1->info.innstore == 0)
					{
						xy(38, 13);
						printf("                                 ");
						xy(38, 13);
						printf("��Ǹ����ͼ�����޹ݲأ�");
						sleep(1);
						xy(38, 13);
						printf("                                 ");
						continue;
					}
					else //���Խ���
					{
						ActReader.BorrowBooks[j].enable = 1;
						strcpy(ActReader.BorrowBooks[j].NO, NO);
						bp1->info.innstore -= 1;
						ntime = gettime();
						ActReader.BorrowBooks[j].year[0] = 1900 + ntime->tm_year;
						ActReader.BorrowBooks[j].month[0] = 1 + ntime->tm_mon;
						ActReader.BorrowBooks[j].day[0] = ntime->tm_mday;
						filldeadline(j);
						bp1 = Bhead;
						options = '*';
						xy(38, 13);
						printf("                                 ");
						xy(38, 13);
						printf("������ɣ�");
						sleep(1);
						xy(38, 13);
						printf("                                 ");
						break;
					}
				}
				if (Isstreq(NO, cexit))
				{
					options = '*';
					break;
				}
			}
			options = '*';
			break;
		}
		case '5': //���顢Ƿ��ɻ���
		{
			char NO[40];
			int i;
			system("cls");
			xy(38, 6);
			printf("                 ͼ��黹                 ");
			xy(38, 7);
			printf("------------------------------------------");
			if (ActReader.needpro == 1) //�ж��Ƿ�Ƿ��
			{
				xy(38, 9);
				printf("������Ƿ��δ�����뽻��Ƿ����飡");
				xy(38, 11);
				printf("----------------------------------");
				xy(38, 13);
				printf("���κμ�����\t");
				scanf("%c", &options);
				options = '*';
				break;
			}
			while (1) //�����Ч���� �� �˳�
			{
				char cexit[5] = "exit";
				xy(38, 9);
				printf("����������Ҫ�黹ͼ���ţ�(����exit����)");
				xy(38, 11);
				printf("------------------------------------------");
				xy(38, 12);
				printf("                                                  ");
				xy(38, 12);
				scanf("%s", NO);
				fflush(stdin);
				if (Isstreq(NO, cexit))
				{
					options = '*';
					break;
				}
				for (i = 0; i < 5; i++)
				{
					if (ActReader.BorrowBooks[i].enable == 1 && Isstreq(NO, ActReader.BorrowBooks[i].NO))
					{
						NO2Book(NO)->info.innstore += 1;
						ActReader.BorrowBooks[i].enable = 0;
						xy(38, 12);
						printf("                                                  ");
						xy(38, 12);
						printf("����ɹ���");
						sleep(1);
						xy(38, 12);
						printf("                                                  ");
						break;
					}
				}
				if (i == 5)
				{
					xy(38, 12);
					printf("                                                  ");
					xy(38, 12);
					printf("��Ǹ������δ���Ĵ��飡");
					sleep(1);
					xy(38, 12);
					printf("                                                  ");
				}
			}
			if (options == '*')
				break;
		}
		case '6': //����ͼ��
		{
			searchb();
			break;
		}
		case '7': //�˳�
		{
			save(0);
			save(2);
			ReaderPos = -1;
			break;
		}
		}
		if (ReaderPos == -1)
			break;
	}
}
void adminpro() //����Ա���񡢡�������ͼ�飬�޸�ͼ�����ݣ��޸Ķ������ݣ�ɾ�����ָ�ͼ����Ϣ
{
	FILE *f;
	//�ļ�Ԥ����

	f = fopen("readers.dat", "rb");
	read(f, LENR);
	fclose(f);
	rp1 = rp2 = Rhead;

	while (1)
	{
		system("cls");
		xy(38, 6);
		printf(" ����Աͬ־ �����ã�");
		xy(38, 7);
		printf("-----------------------------------------------");

		xy(38, 9);
		printf("1.����ͼ����Ϣ");

		xy(38, 11);
		printf("2.���������Ϣ");

		xy(38, 13);
		printf("e.�˳�");

		xy(38, 15);
		printf("-----------------------------------------------");

		while (1)
		{
			xy(38, 16);
			scanf("%c", &options);
			fflush(stdin);
			if (options == '1' || options == '2' || 'e')
				break;
			else
			{
				xy(38, 16);
				printf("                                            ");
				xy(38, 16);
				printf("��������Чѡ�");
				sleep(1);
				xy(38, 16);
				printf("                                            ");
			}
		}
		if (options == '1') //����ͼ��
		{
			while (1) //�����Ч����
			{
				system("cls");
				xy(38, 6);
				printf("                  ͼ�����ģʽ                  ");
				xy(38, 7);
				printf("------------------------------------------------");

				xy(38, 9);
				printf("1.��������");

				xy(38, 11);
				printf("2.�鿴/�޸�ͼ����Ϣ");

				xy(38, 13);
				printf("b.����");

				xy(38, 15);
				printf("-----------------------------------------------");

				xy(38, 16);
				scanf("%c", &options);
				fflush(stdin);
				if (options == '1' || options == '2' || options == 'b')
					break;
				else
				{
					xy(38, 16);
					printf("                                            ");
					xy(38, 16);
					printf("��������Чѡ�");
					sleep(1);
					xy(38, 16);
					printf("                                            ");
				}
			}
			if (options == 'b') //����
				break;
			if (options == '1') //��������
			{
				while (1)
				{
					creatonebook();
					bp1 = Bhead;
					xy(47, 22);
					printf("                                         ");
					xy(47, 22);
					printf("����ɹ���");
					sleep(1);
					xy(47, 22);
					printf("                                         ");
					xy(47, 22);
					printf("�����������\tb.����");
					scanf("%c", &options);
					fflush(stdin);
					if (options == 'b') //����
					{
						options = '*';
						break;
					}
				}
			}
			if (options == '2') //�鿴/�޸�ͼ����Ϣ
			{
				system("cls");
				xy(30, 10);
				printf("��ʾ�������޸���ϢӦ���˳��鿴ģʽ");
				sleep(2);
				showbooks(); //��ʾͼ����Ϣ
				xy(19, 18);
				printf("                                                                   ");
				xy(19, 18);
				printf("���Ƿ���Ҫ�޸�ͼ����Ϣ��1.�޸�ͼ����Ϣ\t���������.����");
				xy(19, 19);
				scanf("%c", &options);
				fflush(stdin);
				if (options == '1')
				{
					char NO[40];
					while (1) //����ͼ����,���ض�Ӧָ��λ��
					{
						char cexit[5] = "exit";
						xy(19, 19);
						printf("                                                                   ");
						xy(19, 18);
						printf("                                                                   ");
						xy(19, 18);
						printf("������ͼ���ţ�(����exit�˳�)");
						xy(19, 19);
						scanf("%s", NO);
						fflush(stdin);
						if (Isstreq(NO, cexit)) //�˳�
						{
							bp1 = NULL;
							break;
						}
						bp1 = NO2Book(NO);
						if (bp1 == NULL) //���޴��鴦��
						{
							xy(19, 19);
							printf("                                                                   ");
							xy(19, 18);
							printf("                                                                   ");
							xy(19, 18);
							printf("��Ǹ���޴�ͼ����Ϣ��");
							sleep(1);
							xy(19, 18);
							printf("                                                                   ");
							xy(19, 19);
							continue;
						}
						else
						{
							break;
						}
					}
					if (bp1 == NULL) //�˳��޸Ĳ��֣���ԭָ��λ��
					{
						bp1 = Bhead;
						break;
					}
					/////bp1������ָ���޸Ĳ���
					system("cls");
					xy(19, 4);
					printf("                                 ͼ  ��  ��  Ϣ                                 ");
					xy(19, 5);
					printf("--------------------------------------------------------------------------------");
					xy(19, 7);
					printf("ͼ����");
					xy(31, 7);
					printf("����");
					xy(39, 7);
					printf("����");
					xy(47, 7);
					printf("�������");
					xy(59, 7);
					printf("�۸�");
					xy(67, 7);
					printf("�ڹ�����");
					xy(79, 7);
					printf("�������");
					xy(91, 7);
					printf("������");

					xy(19, 9);
					printf("%s", bp1->info.NO);
					xy(31, 9);
					printf("%s", bp1->info.name);
					xy(39, 9);
					printf("%s", bp1->info.writer);
					xy(47, 9);
					printf("%d", bp1->info.year);
					xy(59, 9);
					printf("%.2f", bp1->info.price);
					xy(67, 9);
					printf("%d", bp1->info.innstore);
					xy(79, 9);
					printf("%d", bp1->info.all - bp1->info.innstore);
					xy(91, 9);
					printf("%d", bp1->info.all);
					xy(19, 11);
					printf("--------------------------------------------------------------------------------");
					xy(19, 12);
					printf("��ѡ��Ҫ���еĲ���\t1.ɾ��ͼ�顢\t2.����ͼ����Ϣ\t����.�˳�");
					xy(19, 13);
					scanf("%c", &options);
					fflush(stdin);
					switch (options)
					{
					case '1': //ɾ��ͼ��
					{
						struct Book delBook; //ɾ��ͼ�黺�� 
						FILE *f;
						f = fopen("recover.dat", "ab");
						fseek(f, 0, 2);
						fwrite(bp1, LENB, 1, f);
						fclose(f);
						delBook = bp1->info;
						dellb(bp1);
						bp1 = Bhead;
						options = '*';
						xy(19, 13);
						printf("                                                                ");
						xy(19, 12);
						printf("                                                                ");
						xy(19, 12);
						printf("ɾ����ɣ�");
						sleep(1);
						printf("�Ƿ�ȷ���޸ģ�\t�����.ȷ��\tu.����");
						scanf("%c", &options);
						fflush(stdin);
						if (options == 'u')
						{
							bp1 = (struct LBook *)malloc(LENLB);
							bp1->info = delBook;
							singoneBlink();
							xy(19, 13);
							printf("                                                                ");
							xy(19, 12);
							printf("                                                                ");
							xy(19, 12);
							printf("������ɣ�");
							sleep(1);
						}
						break;
					}
					case '2': //����ͼ����Ϣ
					{
						//ɾ��ͼ��
						FILE *f;
						f = fopen("recover.dat", "ab");
						fseek(f, 0, 2);
						fwrite(bp1, LENB, 1, f);
						fclose(f);
						dellb(bp1);
						bp1 = Bhead;
						//����ͼ��
						creatonebook();
						bp1 = Bhead;
						xy(19, 13);
						printf("                                                                ");
						xy(19, 12);
						printf("                                                                ");
						xy(19, 12);
						printf("�޸���ɣ�");
						sleep(1);
						break;
					}
					}
					options = '*';
					bp1 = Bhead;
				}
				options = '*';
			}
		}
		else if (options == '2') //�������
		{

			while (1) //�����Ч����
			{
				system("cls");
				xy(47, 6);
				printf("��ѡ�����������Ĳ�����");
				xy(47, 7);
				printf("----------------------");

				xy(47, 9);
				printf("1.�޸Ķ�����Ϣ");

				xy(47, 11);
				printf("2.�鿴������Ϣ");

				xy(47, 13);
				printf("b.����");

				xy(47, 15);
				printf("----------------------");
				xy(47, 16);
				scanf("%c", &options);
				fflush(stdin);

				if (options == '1' || options == '2' || options == 'b')
					break;
				else
				{
					xy(47, 16);
					printf("��������Чѡ�");
					sleep(1);
					xy(47, 16);
					printf("                  ");
					xy(47, 16);
				}
			}
			if (options == 'b') //����
				break;
			if (options == '1') //�޸Ķ�����Ϣ
			{
				char NO[40];
				system("cls");
				xy(30, 10);
				printf("��ʾ�������޸���ϢӦ���˳��鿴ģʽ");
				sleep(2);
				showreaders();
				while (1) //��ö��߱��
				{
					char cexit[5] = "exit";
					xy(19, 19);
					printf("                                                                   ");
					xy(19, 18);
					printf("                                                                   ");
					xy(19, 18);
					printf("��������߱�ţ�(����exit�˳�)");
					xy(19, 19);
					scanf("%s", NO);
					fflush(stdin);
					rp1=Rhead; 
					if(Isstreq(NO, cexit))
					{
						rp1=NULL;
						break;
					}
					rp1 = NO2Reader(NO);
					//rp1���ÿ�ʼ
					
					if (rp1 == NULL)
					{
						xy(19, 19);
						printf("                                                                   ");
						xy(19, 18);
						printf("                                                                   ");
						xy(19, 18);
						printf("��Ǹ���޴˶�����Ϣ��");
						sleep(1);
						xy(19, 18);
						printf("                                                                   ");
						continue;
					}
					else
						break;
				}
				if(rp1==NULL)
				{
					rp1=Rhead;
					break;
				}
				system("cls");
				xy(19, 4);
				printf("                                 ��  ��  ��  Ϣ                             ");
				xy(19, 5);
				printf("----------------------------------------------------------------------------");
				xy(28, 6);
				printf("���߱��");
				xy(41, 6);
				printf("����");
				xy(50, 6);
				printf("�༶");
				xy(59, 6);
				printf("�Ƿ��Ƿ�����δ��");

				xy(28, 8);
				printf("%s", rp1->info.NO);
				xy(41, 8);
				printf("%s", rp1->info.name);
				xy(50, 8);
				printf("%s", rp1->info.sclass);
				if (rp1->info.needpro == 1)
				{
					xy(59, 8);
					printf("����Ƿ��");
				}
				else
				{
					xy(59, 8);
					printf("������Ƿ��");
				}
				xy(19, 10);
				printf("----------------------------------------------------------------------------");
				xy(19, 11);
				printf("��ѡ��Ҫ���еĲ�����\t1.�������ڻ���\t2.�޸Ķ�����Ϣ\t����.�˳�\t");
				scanf("%c", &options);
				fflush(stdin);
				switch (options)
				{
				case '1':
				{
					rp1->info.needpro = -1;

					system("cls");
					xy(19, 4);
					printf("                                 ��  ��  ��  Ϣ                             ");
					xy(19, 5);
					printf("----------------------------------------------------------------------------");

					xy(28, 6);
					printf("���߱��");
					xy(41, 6);
					printf("����");
					xy(50, 6);
					printf("�༶");
					xy(59, 6);
					printf("�Ƿ��Ƿ�����δ��");

					xy(28, 8);
					printf("%s", rp1->info.NO);
					xy(41, 8);
					printf("%s", rp1->info.name);
					xy(50, 8);
					printf("%s", rp1->info.sclass);
					if (rp1->info.needpro == 1)
					{
						xy(59, 8);
						printf("����Ƿ��");
					}
					else
					{
						xy(59, 8);
						printf("������Ƿ��");
					}
					xy(19, 10);
					printf("----------------------------------------------------------------------------");
					xy(19, 11);
					printf("��ѡ��Ҫ���еĲ�����\t1.�������ڻ���\t2.�޸Ķ�����Ϣ\t����.�˳�\t");
					xy(19, 11);
					printf("                                                                                                ");
					xy(19, 11);
					printf("��ɣ�");
					sleep(2);
					break;
				}
				case '2':
				{
					system("cls");
					xy(47, 6);
					printf("       ��Ϣ�޸�       ");
					xy(47, 7);
					printf("---------------------");

					xy(47, 9);
					printf("��������:");

					xy(47, 11);
					printf("���İ༶:");

					xy(47, 13);
					printf("----------------------");
					xy(56, 9);
					scanf("%s", rp1->info.name);
					fflush(stdin);
					xy(56, 11);
					scanf("%s", rp1->info.sclass);
					fflush(stdin);
					xy(47, 14);
					printf("�޸ĳɹ�!");
					sleep(1);
					options = '*';
					break;
				}
				}
			}
			if (options == '2') // չʾ������Ϣ
			{
				showreaders();
			}
		}
		if (options == 'e')
		{
			options = '*';
			ReaderPos = -1;
			break;
		}
	}
	save(1); //������Ϣ
	save(0);
	freelReader();
}

//main����

void main() //���ڽ���ϵͳ,�������̹��� 
{
	int i = 0;
	int j = 0;
	float k = 0.0;
	int in = 0; //ͳ�Ʊ���
	FILE *f;
	//�ļ�Ԥ����
	f = fopen("books.dat", "rb");
	read(f, LENB);
	fclose(f);
	//��ӭ����
	bp1 = bp2 = Bhead;
	
	xy(47, 6);
	printf("��ӭ����LMS");
	xy(47, 7);
	printf("----------------------");
	xy(47, 9);
	printf("ѧ�ţ�0101170216") ;
	xy(47, 11);
	printf("�����������");
	xy(47, 13);
	printf("�༶���Զ���1703");
	xy(47, 15);
	printf("----------------------");
	xy(47, 16);
	printf("��ȴ�����...");
	sleep(5);
	system("cls");
	while (1)
	{
		i++;
		j += bp1->info.all;
		k += (float)bp1->info.all * bp1->info.price;
		in += bp1->info.innstore;
		if (bp1->next == NULL)
			break;
		bp1 = bp1->next;
	}
	xy(47, 6);
	printf("��ͼ��ݽ���:");
	xy(47, 8);
	printf("���ݲ��鹲%d��", i);
	xy(47, 10);
	printf("���ݲ��鹲%d��", j);
	xy(47, 12);
	printf("���ݲ����ܼ�ֵ%.2fԪ", k);
	xy(47, 14);
	printf("����Ŀǰ�����%d��", in);
	for (i = 4; i >= 0; i--) //��̬��ʾ��ӭ
	{
		xy(45 + 10 * (i + 1), 4 - (i + 1));
		printf("                                                                                                           ");
		xy(45 + 10 * i, 4 - i);
		printf("��ӭ����ͼ��ݹ���ϵͳ��");
		sleep(1);
	}
	sleep(2); 
	//����ϵͳ
	while (1) //
	{
		system("cls");
		if (ReaderPos == -1)
			login(); //�������в�������������ģʽ (���߻��ǹ���Ա)
		if (ReaderPos != 0)
			readerpro(); // ���߽���
		if (ReaderPos == 0)
			adminpro(); // ����Ա����
	}
}
