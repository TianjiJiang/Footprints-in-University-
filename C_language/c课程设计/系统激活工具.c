#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#define LENLB sizeof(struct LBook)
#define LENLR sizeof(struct LReader) 
#define LENB sizeof(struct Book)
#define LENR sizeof(struct Reader) 
#define error 100//报错显示 

//数据存储处理 

struct Book//图书数据结构 !
{
	char NO[40] ;//图书编号 
	char name[100];//书名 
	char writer[50];//作者 
	int year;//出版年份 
	float price;//单价 
	int innstore;//入藏 
	int all;//图书总数 
};
struct BorrowBook //借阅图书数据结构体 ！
{
	int enable; //单元是否有效 1为有效 0无效 
	int NO[40];//借阅图书编号 
	int year[2];//0：借阅年份，1：归还年份 
	int month[2];//0：借阅月份，1：归还月份 
	int day[2];//0：借阅日期，1：归还日期 
};
struct Reader  //读者数据结构体 !
{
	int NO[40];//读者编号 
	char ID[30];//读者账号
	char Password[30]; //读者密码 
	char name[20];//读者姓名 
	char sclass[20];//读者班级 
	struct BorrowBook BorrowBooks[5]; //读者借阅信息 
	int needpro;//读者待被处理事件(0:无，1:缴纳欠款，2：信息错误） 
};
struct LBook  //图书数据双向链表 !
{
	struct LBook *last;
	struct Book info;
	struct LBook *next;
	
};
struct LReader  //图书数据双向链表 !
{
	struct LReader *last;
	struct Reader info;
	struct LReader *next;	 
};

//全局变量

struct Reader ActReader;//当前读者 或读者搜索样本 
int ReaderPos=-1;//读者所在文件位置，初值为无效值 
struct LBook *Bhead=NULL;//图书链表头 
struct LBook *p1, *p2;
char options;//用户操作选择
struct Book TempBook;//图书搜索样本
 
 

 
 

int Isstreq(char *str1,char *str2)//字符串相等判断 
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
	while(flag==0)//注册 
	{
		int i;//循环变量 
		struct Reader TempReader;//
		flag=1; //flag用于判断对出方式，flag为1则正常退出，否则break 
		while(flag==1)//输入不重复的ID 
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
					printf("用户名重复，请重新输入");
					break;	
				}
				printf("I'm here with %d!!!!!!! and %d\n",flag,i);
			}
			printf("I'm here and out with %d!!!!!!!\n",flag);
			fclose(f);
		} 
		flag=0; //恢复判断flag原功能 
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
		for(i=0;i<5;i++)//借阅信息初始化 
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

int save(int i) //保存文件图书，i控制保存类型(1为读者，2为图书) ,p为数据位置 
{
	if(i==1)//图书数据 
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
struct LBook* creat()//输入字符时候q退出，数字时候0退出 
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

