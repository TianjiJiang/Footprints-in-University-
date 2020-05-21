#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#define LENLB sizeof(struct LBook)
#define LENLR sizeof(struct LReader) 
#define LENB sizeof(struct Book)
#define LENR sizeof(struct Reader) 
#define error 100//������ʾ 

//���ݴ洢���� 

struct Book//ͼ�����ݽṹ !
{
	char NO[40] ;//ͼ���� 
	char name[100];//���� 
	char writer[50];//���� 
	int year;//������� 
	float price;//���� 
	int innstore;//��� 
	int all;//ͼ������ 
};
struct BorrowBook //����ͼ�����ݽṹ�� ��
{
	int enable; //��Ԫ�Ƿ���Ч 1Ϊ��Ч 0��Ч 
	int NO[40];//����ͼ���� 
	int year[2];//0��������ݣ�1���黹��� 
	int month[2];//0�������·ݣ�1���黹�·� 
	int day[2];//0���������ڣ�1���黹���� 
};
struct Reader  //�������ݽṹ�� !
{
	int NO[40];//���߱�� 
	char ID[30];//�����˺�
	char Password[30]; //�������� 
	char name[20];//�������� 
	char sclass[20];//���߰༶ 
	struct BorrowBook BorrowBooks[5]; //���߽�����Ϣ 
	int needpro;//���ߴ��������¼�(0:�ޣ�1:����Ƿ�2����Ϣ���� 
};
struct LBook  //ͼ������˫������ !
{
	struct LBook *last;
	struct Book info;
	struct LBook *next;
	
};
struct LReader  //ͼ������˫������ !
{
	struct LReader *last;
	struct Reader info;
	struct LReader *next;	 
};

//ȫ�ֱ���

struct Reader ActReader;//��ǰ���� ������������� 
int ReaderPos=-1;//���������ļ�λ�ã���ֵΪ��Чֵ 
struct LBook *Bhead=NULL;//ͼ������ͷ 
struct LBook *p1, *p2;
char options;//�û�����ѡ��
struct Book TempBook;//ͼ����������
 
 

 
 

int Isstreq(char *str1,char *str2)//�ַ�������ж� 
{
	int result=1;
	for(;!(*str1=='\0'&& *str2=='\0');str1++,str2++)
	{
		if(*str1!=*str2)
		{
			result=0;
			break;
		}
	}
	return result;
}
int regester()
{
	FILE *f;
	int flag=0;
	while(flag==0)//ע�� 
	{
		int i;//ѭ������ 
		struct Reader TempReader;//
		flag=1; //flag�����ж϶Գ���ʽ��flagΪ1�������˳�������break 
		while(flag==1)//���벻�ظ���ID 
		{
			printf("please input your ID:\n");
			scanf("%s",TempReader.ID);
			fflush(stdin);
			f=fopen("text.dat","rb");//--------------------------------------try catch	
			rewind(f);
			for(i=0;flag=(!feof(f));i++)
			{
				printf("I'm here!!!!!!!\n");
				fseek(f,i*LENR,0);
				fread(&ActReader,LENR,1,f);
				printf("%s\n",ActReader.ID);
				if(Isstreq(ActReader.ID,TempReader.ID))
				{
					printf("�û����ظ�������������");
					break;	
				}
				printf("I'm here with %d!!!!!!! and %d\n",flag,i);
			}
			printf("I'm here and out with %d!!!!!!!\n",flag);
			fclose(f);
		} 
		flag=0; //�ָ��ж�flagԭ���� 
		printf("please input your Password:\n");
		scanf("%s",TempReader.Password);
		fflush(stdin);
		printf("please input your NO:\n");
		scanf("%d",&TempReader.NO);
		fflush(stdin);
		printf("please input your name:\n");
		scanf("%s",TempReader.name);
		fflush(stdin);
		printf("please input your Class:\n");
		scanf("%s",TempReader.sclass);
		fflush(stdin);
		TempReader.needpro=0;
		for(i=0;i<5;i++)//������Ϣ��ʼ�� 
		{
			TempReader.BorrowBooks[i].enable=0; 
		} 
		f=fopen("text.dat","ab");//--------------------------------------try catch	
		rewind(f);
		fseek(f,0,2);
		fwrite(&TempReader,LENR,1,f);
		fclose(f);
		printf("successfully regestered!\n");
		flag=1; 
	}
}

int save(int i) //�����ļ�ͼ�飬i���Ʊ�������(1Ϊ���ߣ�2Ϊͼ��) ,pΪ����λ�� 
{
	if(i==1)//ͼ������ 
	{
		FILE *f;
		struct LBook* head;
		head=Bhead; 
		f=fopen("text.dat","wb");
		rewind(f);
		while (head!=NULL)
		{
			fwrite(&head->info,LENR,1,f);
			head=head->next;
		}	
		fclose(f);
		return 0;
	}
	if(i==0)
	{
	
	}
} 
struct LBook* creat()//�����ַ�ʱ��q�˳�������ʱ��0�˳� 
{
	int n=0;
	p2=p1=(struct LBook *) malloc(LENLB);
		printf("please input books NO:\n");
		scanf("%s",&p1->info.NO);
		fflush(stdin);
		printf("please input books name:\n");
		scanf("%s",&p1->info.name);
		fflush(stdin);
		printf("please input books writer:\n");
		scanf("%s",&p1->info.writer);
		fflush(stdin);
		printf("please input books price:\n");
		scanf("%f",&p1->info.price);
		fflush(stdin);
		printf("please input books publish year:\n");
		scanf("%d",&p1->info.year);
		fflush(stdin);
		printf("please input books total number:\n");
		scanf("%d",&p1->info.all);
		fflush(stdin);
		p1->info.innstore=p1->info.all;
	while(1)
	{
		n++;
		if(n==1) 
		{
			p1->last=NULL; 
			Bhead=p1;
		}
		else 
		{
			p2->next=p1;
			p1->last=p2;
		}
		p2=p1;
		p1=(struct LBook*)malloc(LENLB);
		printf("please input books NO:\n");
		scanf("%s",p1->info.NO);
		fflush(stdin);
		if(p1->info.NO[0]=='q') break;	
		printf("please input books name:\n");
		scanf("%s",p1->info.name);
		fflush(stdin);
		if(p1->info.name[0]=='q') break;
		printf("please input books writer:\n");
		scanf("%s",p1->info.writer);
		fflush(stdin);
		if(p1->info.writer[0]=='q') break;
		printf("please input books price:\n");
		scanf("%f",&p1->info.price);
		fflush(stdin);
		if(p1->info.price==-1) break;
		printf("please input books publish year:\n");
		scanf("%d",&p1->info.year);
		fflush(stdin);
		if(p1->info.year==-1) break;
		printf("please input books total number:\n");
		scanf("%d",&p1->info.all);
		fflush(stdin);
		if(p1->info.all==-1) break;
		p1->info.innstore=p1->info.all;
	}
	free(p1);
	p1=p2;
	p2->next=NULL;
	return (Bhead);
}
struct LBook* readf(FILE *f,int LEN1)
{
	
	int i;
	int n=0;
	p2=p1=(struct LBook *) malloc(LEN1);
	rewind(f);
	fread(&p1->info,LENB,1,f);
	printf("%s\n%s\n%s\n%f\n%d\n",p1->info.NO,p1->info.name,p1->info.writer,p1->info.price,p1->info.innstore);
	for (i=1;!feof(f);i++)
	{
		n++;
		if(n==1) Bhead=p1;
		else p2->next=p1;
		p2=p1;
		p1=(struct LBook *) malloc(LEN1);
		fseek(f,i*LENB,0);
		fread(&p1->info,LENB,1,f);
		printf("%s\n%s\n%s\n%f\n%d\n",p1->info.NO,p1->info.name,p1->info.writer,p1->info.price,p1->info.innstore);
	}
	free(p1);
	p1=p2;
	p2->next=NULL;
	printf("%s\n%s\n%s\n%f\n%d\n",p1->info.NO,p1->info.name,p1->info.writer,p1->info.price,p1->info.innstore);
	return (Bhead);
}
void gotoxy(int x, int y)
{
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}



char options;
void text__switch()
{
	printf("-----%c-----\n",options);
	scanf("%c",&options);
	fflush(stdin);
} 
void main()
{
	
	FILE *sf;
	struct LBook *bp1;
	bp1 = (struct LBook *)malloc(LENLB);
	printf("please input books NO:\n");
	scanf("%s", bp1->info.NO);
	fflush(stdin);
	printf("please input books name:\n");
	scanf("%s", bp1->info.name);
	fflush(stdin);
	printf("please input books writer:\n");
	scanf("%s", bp1->info.writer);
	fflush(stdin);
	printf("please input books price:\n");
	scanf("%f", &bp1->info.price);
	fflush(stdin);
	printf("please input books publish year:\n");
	scanf("%d", &bp1->info.year);
	fflush(stdin);
	printf("please input books total number:\n");
	scanf("%d", &bp1->info.all);
	fflush(stdin);
	bp1->info.innstore = bp1->info.all;
	bp1->last = bp1->next = NULL;
		
		sf = fopen("books.dat", "ab");
		rewind(sf);
		fwrite(&bp1->info, LENB, 1, sf);
		printf("ok!");
}

