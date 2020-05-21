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

//结构数组

struct Book //图书数据结构体!
{
	char NO[40];	 //图书编号
	char name[100];  //书名
	char writer[50]; //作者
	int year;		 //出版年份
	float price;	 //单价
	int innstore;	//入藏
	int all;		 //图书总数
};
struct BorrowBook //借阅图书数据结构体 ！
{
	int enable;   //单元是否有效 1为有效 0无效
	char NO[40];  //借阅图书编号
	int year[2];  //0：借阅年份，1：归还年份
	int month[2]; //0：借阅月份，1：归还月份
	int day[2];   //0：借阅日期，1：归还日期
};
struct Reader //读者数据结构体 !
{
	char NO[40];					  //读者编号
	char ID[30];					  //读者账号
	char Password[30];				  //读者密码
	char name[20];					  //读者姓名
	char sclass[20];				  //读者班级
	struct BorrowBook BorrowBooks[5]; //读者借阅信息
	int needpro;					  //读者待被处理事件(-1:已经缴纳欠款 0:无，1:缴纳欠款，2：信息错误）
};
struct LBook //图书数据双向链表 !
{
	struct LBook *last;
	struct Book info;
	struct LBook *next;
};
struct LReader //图书数据双向链表 !
{
	struct LReader *last;
	struct Reader info;
	struct LReader *next;
};

//全局变量

struct Reader ActReader;	  //当前读者 或读者搜索样本
struct LReader *Rhead = NULL; //读者链表头
struct LReader *rp1, *rp2;	//读者当前指针
struct LBook *Bhead = NULL;   //图书链表头
struct LBook *bp1, *bp2;	  //图书当前指针 ，bp1为创建活动指针
char options = '*';			  //用户操作选择,初始为'*'
int ReaderPos = -1;			  //读者所在文件位置，初值为无效值

//链表处理构架

void addlb(struct LBook *front, struct LBook *add) //图书链表添加 !
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
void cBhead(struct LBook *NewHead) //图书链表删换头 !
{
	NewHead->last = NULL;
	NewHead->next = Bhead;
	Bhead->last = NewHead;
	Bhead = NewHead;
}
void dellb(struct LBook *del) //图书链表删除 !
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
void addlr(struct LReader *front, struct LReader *add) //读者链表添加 !
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
void cRhead(struct LReader *NewHead) //读者链表换头！
{
	NewHead->last = NULL;
	NewHead->next = Rhead;
	Rhead->last = NewHead;
	Rhead = NewHead;
}
void dellr(struct LReader *del) //读者链表删除 !
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

//系统通用函数

struct tm *gettime() //获得时间！
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	return p;
}
int Isstreq(char *str1, char *str2) //字符串相等判断！
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
void xy(int x, int y) //用于输出显示 !
{
	COORD pos = {x, y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
int searchb() //图书搜索
{
	while (1) //搜索循环
	{
		char seachstr[40];
		while (1) //正确输入循环
		{
			system("cls");
			xy(47, 6);
			printf("       图书搜索       ");
			xy(47, 7);
			printf("----------------------");

			xy(47, 9);
			printf("1.书名");

			xy(47, 11);
			printf("2.作者");

			xy(47, 13);
			printf("b.返回");

			xy(47, 15);
			printf("----------------------");

			xy(47, 17);
			printf("请选择搜索方式：\t");
			scanf("%c", &options);
			fflush(stdin);
			if (options == '1' || options == '2' || options == 'b')
				break;
			xy(47, 17);
			printf("                                          ");
			xy(47, 17);
			printf("请输入有效选项！");
			sleep(1);
			xy(47, 17);
			printf("                                          ");
		}
		if (options == '1') //按书名
		{
			while (1)
			{
				int num = 0;
				int j = 0;
				char cexit[5] = "exit";
				system("cls");
				xy(19, 4);
				printf("                                 图  书  信  息                             ");
				xy(19, 5);
				printf("----------------------------------------------------------------------------");
				xy(19, 6);
				printf("序号");
				xy(27, 6);
				printf("图书编号");
				xy(39, 6);
				printf("书名");
				xy(47, 6);
				printf("作者");
				xy(55, 6);
				printf("出版年份");
				xy(67, 6);
				printf("价格");
				xy(75, 6);
				printf("在馆数量");
				xy(19, 16);
				printf("----------------------------------------------------------------------------");
				xy(19, 17);
				printf("请输入书名：(输入exit退出)\t");
				scanf("%s", seachstr);
				fflush(stdin);
				bp1 = Bhead;
				if (Isstreq(cexit, seachstr))
					break;
				while (1) //搜索
				{
					int flag = 0; //是否匹配
					int i = 0;
					int start = 0;
					j = 0;									  //匹配字符串使用计数变量归零
					while (bp1->info.name[i + start] != '\0') //匹配过程
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
					if (flag == 0) //不匹配，下一个
					{
						if (bp1->next == NULL)
							break;
						bp1 = bp1->next;
						continue;
					}
					else //匹配输出
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
				printf("搜索完成！");
				sleep(1);
				xy(19, 17);
				printf("                                                   ");
				xy(19, 17);
				printf("输入任意继续\t");
				scanf("%c", &options);
				fflush(stdin);
				options = '1';
			}
		}
		if (options == '2') //按作者
		{
			while (1)
			{
				int j;
				int num = 0;
				int flag = 0;
				char cexit[5] = "exit";
				system("cls");
				xy(19, 4);
				printf("                                 图  书  信  息                             ");
				xy(19, 5);
				printf("----------------------------------------------------------------------------");
				xy(19, 6);
				printf("序号");
				xy(27, 6);
				printf("图书编号");
				xy(39, 6);
				printf("书名");
				xy(47, 6);
				printf("作者");
				xy(55, 6);
				printf("出版年份");
				xy(67, 6);
				printf("价格");
				xy(75, 6);
				printf("在馆数量");
				xy(19, 16);
				printf("----------------------------------------------------------------------------");
				xy(19, 17);
				printf("请输入作者全名：(输入exit退出)\t");
				scanf("%s", seachstr);
				fflush(stdin);
				if (Isstreq(cexit, seachstr))
					break;
				while (1)
				{
					//是否匹配
					if (Isstreq(bp1->info.writer, seachstr))
					{
						flag = 1;
					}
					if (flag == 0) //不匹配，下一个
					{
						if (bp1->next == NULL)
							break;
						bp1 = bp1->next;
						continue;
					}
					else //匹配输出
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
				printf("搜索完成！");
				sleep(1);
				xy(19, 17);
				printf("                                                   ");
				xy(19, 17);
				printf("输入任意继续\t");
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
void save(int i) //保存文件图书，i控制保存类型(1为全部读者，0为图书,2位单个读者)!
{
	if (i == 0) //图书数据
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
void read(FILE *f, int LEND) //读取整个文件 ,f为读入文件指针，LEND为输入数据长度!
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
void singoneBlink() //年份从大到小的顺序存储! bp1为待链接单元指针！
{
	int flag = 0; //未连接为0
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
	bp2 = Bhead; //返回等待下一次调用
}
void creatonebook() //创建单本图书，与singonelink一起使用!
{
	int flag;
	bp1 = (struct LBook *)malloc(LENLB);

	//输入不重复的NO
	flag = 1; //flag用于判断对出方式，flag为1则正常退出，否则break
	bp2 = Bhead;
	system("cls");
	xy(47, 6);
	printf("         图书信息         ");
	xy(47, 7);
	printf("--------------------------");

	xy(47, 9);
	printf("图书编号:");

	xy(47, 11);
	printf("书名:");

	xy(47, 13);
	printf("图书作者:");

	xy(47, 15);
	printf("图书单价:");

	xy(47, 17);
	printf("出版年份:");

	xy(47, 19);
	printf("图书总数:");

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
				printf("图书编号重复，请重新输入!");
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
int IsBookOverate(int i) //判断第n-1本书是否超期!
{
	int result = 0;
	struct tm *ntime;
	ntime = gettime();
	if (ActReader.BorrowBooks[i].enable == 1)
	{
		if (ActReader.BorrowBooks[i].year[1] < (ntime->tm_year + 1900)) //超过年
		{
			result = 1;
		}
		else
		{
			if ((ActReader.BorrowBooks[i].month[1] < 1 + ntime->tm_mon) && (ActReader.BorrowBooks[i].year[1] == (ntime->tm_year + 1900))) //超过月
			{
				result = 1;
			}
			else
			{
				if ((ActReader.BorrowBooks[i].day[1] < ntime->tm_mday) && (ActReader.BorrowBooks[i].month[1] == 1 + ntime->tm_mon)) //超过日
				{
					result = 1;
				}
			}
		}
	}
	return result;
}
void ReaderPrePro() //读者信息预处理 、处理欠款信息!
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
struct LBook *NO2Book(char *NO) //根据图书编号找书!
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
struct LReader *NO2Reader(char *NO) //根据图书编号找书!
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
void filldeadline(int i) //自动填充图书归还日期!
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
void freelReader() //释放读者链表内存!
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
void showbooks() //显示图书！
{
	int j = 0;
	bp1 = Bhead;
	system("cls");
	xy(19, 4);
	printf("                                 图  书  信  息                                 ");
	xy(19, 5);
	printf("--------------------------------------------------------------------------------");
	xy(19, 6);
	printf("序号");
	xy(27, 6);
	printf("图书编号");
	xy(39, 6);
	printf("书名");
	xy(47, 6);
	printf("作者");
	xy(55, 6);
	printf("出版年份");
	xy(67, 6);
	printf("价格");
	xy(75, 6);
	printf("在馆数量");

	while (1)
	{
		int flag = 0;
		int w = 0;
		while (1)
		{
			j++;
			w++;
			xy(19, 6 + w);
			printf("                                                                              "); //清理该行
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
			printf("按任意键返回\t");
			scanf("%d", &w);
			fflush(stdin);
			break;
		}
		else
		{
			xy(19, 18);
			printf("                                                ");
			xy(19, 18);
			printf("按0.返回\t其他.下一页\t");
			scanf("%d", &w);
			fflush(stdin);
			bp1 = bp1->next;
			if (w == 0)
				break;
		}
	}
	bp1 = Bhead;
}
void showreaders() //显示读者！
{
	int j = 0;
	system("cls");
	xy(19, 4);
	printf("                                 读  者  信  息                             ");
	xy(19, 5);
	printf("----------------------------------------------------------------------------");
	xy(19, 6);
	printf("序号");
	xy(28, 6);
	printf("读者编号");
	xy(41, 6);
	printf("姓名");
	xy(50, 6);
	printf("班级");
	xy(59, 6);
	printf("是否是否逾期未还");
	while (1)
	{
		int flag = 0;
		int w = 0;
		while (1)
		{
			j++;
			w++;
			xy(19, 6 + j);
			printf("                                                                              "); //清理该行
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
					printf("√");
				}
				else
				{
					xy(59, 6 + w);
					printf("×");
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
			printf("按任意键返回\t");
			scanf("%d", &w);
			fflush(stdin);
			break;
		}
		else
		{
			xy(19, 18);
			printf("                                            ");
			xy(19, 18);
			printf("0.返回\t其他.下一页\t");
			scanf("%d", &w);
			fflush(stdin);
			rp1 = rp1->next;
			if (w == 0)
				break;
		}
	}
	rp1 = Rhead;
}

// 系统处理构架

void login() //登录,注册,读者登录返回 1 ，管理员返回 0
{
	int winshow = 0;
	FILE *f;	  //open readers.dat
	int flag = 1; //0注册    还是  1登陆
	while (ReaderPos == -1)
	{

		xy(47, 6);
		printf("     欢迎来到LMS      ");
		xy(47, 7);
		printf("----------------------");

		xy(47, 9);
		printf("   1.登录");

		xy(47, 11);
		printf("   0.注册");

		xy(47, 13);
		printf("----------------------");
		xy(47, 14);
		while (1) //获得有效输入
		{
			scanf("%d", &flag);
			fflush(stdin);
			if ((flag == 1) || (flag == 0))
				break;
			else
			{
				xy(47, 14);
				;
				printf(" 请输入0或1！");
				sleep(1);
				xy(47, 14);
				;
				printf("                  ");
				xy(47, 14);
				;
			}
		}

		while (flag == 1) //登录 __函数唯一出口__通过改变ReaderPos
		{
			int i;			   //文件遍历位置
			char ID[30];	   //读者账号
			char Password[30]; //读者密码
			system("cls");
			xy(47, 6);
			printf("       登   录       ");
			xy(47, 7);
			printf("---------------------");

			xy(47, 9);
			printf("您的用户名:");

			xy(47, 11);
			printf("您的密码:");

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
				break; //完成登录 ，退出
			fclose(f);
			xy(47, 14);
			printf("抱歉，您的用户名或密码错误！");
			sleep(1);
		}

		while (flag == 0) //注册
		{
			int i; //循环变量
			struct Reader TempReader;
			system("cls");
			xy(47, 6);
			printf("       注   册       ");
			xy(47, 7);
			printf("---------------------");

			xy(47, 9);
			printf("您的用户名:");

			xy(47, 11);
			printf("您的密码:");

			xy(47, 13);
			printf("您的学号:");

			xy(47, 15);
			printf("您的姓名:");

			xy(47, 17);
			printf("您的班级:");

			xy(47, 19);
			printf("----------------------");

			//输入不重复的ID
			flag = 1; //flag用于判断对出方式，flag为1则正常退出，否则break
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
						printf("用户名重复，请重新输入!");
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
			//恢复判断flag原功能

			xy(56, 11);
			scanf("%s", TempReader.Password);
			fflush(stdin);

			//输入不重复的NO
			flag = 1; //flag用于判断对出方式，flag为1则正常退出，否则break
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
						printf("学号重复或错误，请重新输入!");
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
			//恢复判断flag原功能

			xy(56, 15);
			scanf("%s", TempReader.name);
			fflush(stdin);
			xy(56, 17);
			scanf("%s", TempReader.sclass);
			fflush(stdin);
			TempReader.needpro = 0;
			for (i = 0; i < 5; i++) //借阅信息初始化
			{
				TempReader.BorrowBooks[i].enable = 0;
			}
			f = fopen("readers.dat", "ab");
			fwrite(&TempReader, LENR, 1, f);
			fclose(f);
			xy(47, 20);
			printf("注册成功！");
			sleep(3);
			system("cls");
			flag = 1;
		}
	}
}
void readerpro() //读者服务 
{
	int i; //计数变量
	options = '*';
	ReaderPrePro(); //读者信息预处理
	while (1)
	{
		system("cls");
		xy(38, 6);
		printf(" 亲爱的 %s ，您好！", ActReader.name);
		xy(38, 7);
		printf("-----------------------------------------------");

		xy(38, 9);
		printf("1.查看个人信息");

		xy(38, 11);
		printf("2.查看图书借阅情况");

		xy(38, 13);
		printf("3.查看图书");

		xy(38, 15);
		printf("4.图书借阅");

		xy(38, 17);
		printf("5.图书归还");

		xy(38, 19);
		printf("6.搜索图书");

		xy(38, 21);
		printf("7.退出");

		xy(38, 23);
		printf("-----------------------------------------------");
		xy(38, 24);
		scanf("%c", &options);
		fflush(stdin);
		switch (options)
		{
		case '1': //查看读者信息
		{
			//显示
			system("cls");
			xy(47, 6);
			printf("       您的信息       ");
			xy(47, 7);
			printf("----------------------");

			xy(47, 9);
			printf("您的用户名: %s", ActReader.ID);

			xy(47, 11);
			printf("您的学号: %s", ActReader.NO);

			xy(47, 13);
			printf("您的姓名: %s", ActReader.name);

			xy(47, 15);
			printf("您的班级: %s", ActReader.sclass);

			xy(47, 17);
			printf("欠款情况:");

			xy(47, 19);
			printf("----------------------");
			xy(47, 20);
			if (ActReader.needpro == 0 || ActReader.needpro == -1)
			{
				xy(56, 17);
				printf(" 无欠款");
				xy(47, 20);
			}
			else if (ActReader.needpro == 1)
			{
				xy(56, 17);
				printf(" 有欠款记录！");
				xy(47, 20);
			}
			xy(47, 20);
			printf("按任意键返回\t");
			//进一步操作
			scanf("%c", &options);
			fflush(stdin);
			options = '*';
			break;
		}
		case '2': //查看图书借阅情况
		{
			int j = 0;
			system("cls");
			xy(18, 4);
			printf("                                 图  书  借  阅  信  息                             ");
			xy(18, 5);
			printf("------------------------------------------------------------------------------------");
			xy(18, 6);
			printf("序号");
			xy(26, 6);
			printf("图书编号");
			xy(38, 6);
			printf("书名");
			xy(46, 6);
			printf("作者");
			xy(54, 6);
			printf("出版年份");
			xy(66, 6);
			printf("价格");
			xy(74, 6);
			printf("借阅日期");
			xy(86, 6);
			printf("归还期限");
			xy(98, 6);
			printf("备注");
			for (i = 0; i < 5; i++) //图书信息输出
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
						printf("超过期限！");
					}
				}
			}
			xy(18, 17);
			printf("------------------------------------------------------------------------------------");
			xy(18, 18);
			printf("按任何键返回\t");
			scanf("%c", &options);
			options = '*';
			break;
		}
		case '3': //查看图书 \\仅仅按年份排
		{
			showbooks();
			options = '*';
			break;
		}
		case '4': //借书 ，欠款不可借 ，含有图书搜索
		{
			int i;	 //循环变量
			int j = 0; //计数变量
			system("cls");
			xy(38, 6);
			printf("             图书借阅              ");
			xy(38, 7);
			printf("----------------------------------");
			//判断是否欠款
			if (ActReader.needpro == 1)
			{
				xy(38, 9);
				printf("您尚有欠款未还，请交清欠款后借书！");
				xy(38, 11);
				printf("----------------------------------");
				xy(38, 13);
				printf("按任何键返回\t");
				scanf("%c", &options);
				options = '*';
				break;
			}

			while (1) //正常借书和最多五本
			{
				struct tm *ntime;
				char NO[40];
				char cexit[5] = "exit";
				j = 0;
				//判断是否借满//j记录空闲位置
				while (i < 5) //判断是否借满
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

				if (j == 5) //借满提示
				{
					xy(38, 9);
					printf("您已经借阅满五本书！暂时不能借书！");
					xy(38, 11);
					printf("----------------------------------");
					xy(38, 13);
					printf("按任何键返回\t");
					scanf("%c", &options);
					options = '*';
					break;
				}
				while (1)//确认有借书权限
				{
					system("cls");
					xy(38, 6);
					printf("             图书借阅              ");
					xy(38, 7);
					printf("----------------------------------");
					xy(38, 9);
					printf("请输入图书编号：(退出请输入exit)");
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
						printf("抱歉，无此图书信息！");
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
						printf("抱歉，该图书暂无馆藏！");
						sleep(1);
						xy(38, 13);
						printf("                                 ");
						continue;
					}
					else //可以借书
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
						printf("借书完成！");
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
		case '5': //还书、欠款不可还书
		{
			char NO[40];
			int i;
			system("cls");
			xy(38, 6);
			printf("                 图书归还                 ");
			xy(38, 7);
			printf("------------------------------------------");
			if (ActReader.needpro == 1) //判断是否欠款
			{
				xy(38, 9);
				printf("您尚有欠款未还，请交清欠款后还书！");
				xy(38, 11);
				printf("----------------------------------");
				xy(38, 13);
				printf("按任何键返回\t");
				scanf("%c", &options);
				options = '*';
				break;
			}
			while (1) //获得有效输入 或 退出
			{
				char cexit[5] = "exit";
				xy(38, 9);
				printf("请输入您需要归还图书编号：(输入exit返回)");
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
						printf("还书成功！");
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
					printf("抱歉，您并未借阅此书！");
					sleep(1);
					xy(38, 12);
					printf("                                                  ");
				}
			}
			if (options == '*')
				break;
		}
		case '6': //搜索图书
		{
			searchb();
			break;
		}
		case '7': //退出
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
void adminpro() //管理员服务、、、增加图书，修改图书数据，修改读者数据，删除，恢复图书信息
{
	FILE *f;
	//文件预读入

	f = fopen("readers.dat", "rb");
	read(f, LENR);
	fclose(f);
	rp1 = rp2 = Rhead;

	while (1)
	{
		system("cls");
		xy(38, 6);
		printf(" 管理员同志 ，您好！");
		xy(38, 7);
		printf("-----------------------------------------------");

		xy(38, 9);
		printf("1.管理图书信息");

		xy(38, 11);
		printf("2.管理读者信息");

		xy(38, 13);
		printf("e.退出");

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
				printf("请输入有效选项！");
				sleep(1);
				xy(38, 16);
				printf("                                            ");
			}
		}
		if (options == '1') //管理图书
		{
			while (1) //获得有效输入
			{
				system("cls");
				xy(38, 6);
				printf("                  图书管理模式                  ");
				xy(38, 7);
				printf("------------------------------------------------");

				xy(38, 9);
				printf("1.加入新书");

				xy(38, 11);
				printf("2.查看/修改图书信息");

				xy(38, 13);
				printf("b.返回");

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
					printf("请输入有效选项！");
					sleep(1);
					xy(38, 16);
					printf("                                            ");
				}
			}
			if (options == 'b') //返回
				break;
			if (options == '1') //加入新书
			{
				while (1)
				{
					creatonebook();
					bp1 = Bhead;
					xy(47, 22);
					printf("                                         ");
					xy(47, 22);
					printf("加入成功！");
					sleep(1);
					xy(47, 22);
					printf("                                         ");
					xy(47, 22);
					printf("任意键继续，\tb.返回");
					scanf("%c", &options);
					fflush(stdin);
					if (options == 'b') //返回
					{
						options = '*';
						break;
					}
				}
			}
			if (options == '2') //查看/修改图书信息
			{
				system("cls");
				xy(30, 10);
				printf("提示：若想修改信息应先退出查看模式");
				sleep(2);
				showbooks(); //显示图书信息
				xy(19, 18);
				printf("                                                                   ");
				xy(19, 18);
				printf("您是否需要修改图书信息？1.修改图书信息\t其他任意键.返回");
				xy(19, 19);
				scanf("%c", &options);
				fflush(stdin);
				if (options == '1')
				{
					char NO[40];
					while (1) //输入图书编号,返回对应指针位置
					{
						char cexit[5] = "exit";
						xy(19, 19);
						printf("                                                                   ");
						xy(19, 18);
						printf("                                                                   ");
						xy(19, 18);
						printf("请输入图书编号：(输入exit退出)");
						xy(19, 19);
						scanf("%s", NO);
						fflush(stdin);
						if (Isstreq(NO, cexit)) //退出
						{
							bp1 = NULL;
							break;
						}
						bp1 = NO2Book(NO);
						if (bp1 == NULL) //无无此书处理
						{
							xy(19, 19);
							printf("                                                                   ");
							xy(19, 18);
							printf("                                                                   ");
							xy(19, 18);
							printf("抱歉，无此图书信息！");
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
					if (bp1 == NULL) //退出修改部分，还原指针位置
					{
						bp1 = Bhead;
						break;
					}
					/////bp1工作，指向修改部分
					system("cls");
					xy(19, 4);
					printf("                                 图  书  信  息                                 ");
					xy(19, 5);
					printf("--------------------------------------------------------------------------------");
					xy(19, 7);
					printf("图书编号");
					xy(31, 7);
					printf("书名");
					xy(39, 7);
					printf("作者");
					xy(47, 7);
					printf("出版年份");
					xy(59, 7);
					printf("价格");
					xy(67, 7);
					printf("在馆数量");
					xy(79, 7);
					printf("借出数量");
					xy(91, 7);
					printf("总数量");

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
					printf("请选择要进行的操作\t1.删除图书、\t2.更新图书信息\t其他.退出");
					xy(19, 13);
					scanf("%c", &options);
					fflush(stdin);
					switch (options)
					{
					case '1': //删除图书
					{
						struct Book delBook; //删除图书缓存 
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
						printf("删除完成！");
						sleep(1);
						printf("是否确认修改？\t任意键.确定\tu.撤销");
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
							printf("撤销完成！");
							sleep(1);
						}
						break;
					}
					case '2': //更新图书信息
					{
						//删除图书
						FILE *f;
						f = fopen("recover.dat", "ab");
						fseek(f, 0, 2);
						fwrite(bp1, LENB, 1, f);
						fclose(f);
						dellb(bp1);
						bp1 = Bhead;
						//创建图书
						creatonebook();
						bp1 = Bhead;
						xy(19, 13);
						printf("                                                                ");
						xy(19, 12);
						printf("                                                                ");
						xy(19, 12);
						printf("修改完成！");
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
		else if (options == '2') //管理读者
		{

			while (1) //获得有效输入
			{
				system("cls");
				xy(47, 6);
				printf("请选择您接下来的操作：");
				xy(47, 7);
				printf("----------------------");

				xy(47, 9);
				printf("1.修改读者信息");

				xy(47, 11);
				printf("2.查看读者信息");

				xy(47, 13);
				printf("b.返回");

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
					printf("请输入有效选项！");
					sleep(1);
					xy(47, 16);
					printf("                  ");
					xy(47, 16);
				}
			}
			if (options == 'b') //返回
				break;
			if (options == '1') //修改读者信息
			{
				char NO[40];
				system("cls");
				xy(30, 10);
				printf("提示：若想修改信息应先退出查看模式");
				sleep(2);
				showreaders();
				while (1) //获得读者编号
				{
					char cexit[5] = "exit";
					xy(19, 19);
					printf("                                                                   ");
					xy(19, 18);
					printf("                                                                   ");
					xy(19, 18);
					printf("请输入读者编号：(输入exit退出)");
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
					//rp1作用开始
					
					if (rp1 == NULL)
					{
						xy(19, 19);
						printf("                                                                   ");
						xy(19, 18);
						printf("                                                                   ");
						xy(19, 18);
						printf("抱歉，无此读者信息！");
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
				printf("                                 读  者  信  息                             ");
				xy(19, 5);
				printf("----------------------------------------------------------------------------");
				xy(28, 6);
				printf("读者编号");
				xy(41, 6);
				printf("姓名");
				xy(50, 6);
				printf("班级");
				xy(59, 6);
				printf("是否是否逾期未还");

				xy(28, 8);
				printf("%s", rp1->info.NO);
				xy(41, 8);
				printf("%s", rp1->info.name);
				xy(50, 8);
				printf("%s", rp1->info.sclass);
				if (rp1->info.needpro == 1)
				{
					xy(59, 8);
					printf("逾期欠款");
				}
				else
				{
					xy(59, 8);
					printf("无逾期欠款");
				}
				xy(19, 10);
				printf("----------------------------------------------------------------------------");
				xy(19, 11);
				printf("请选择要进行的操作：\t1.读者逾期还款\t2.修改读者信息\t其他.退出\t");
				scanf("%c", &options);
				fflush(stdin);
				switch (options)
				{
				case '1':
				{
					rp1->info.needpro = -1;

					system("cls");
					xy(19, 4);
					printf("                                 读  者  信  息                             ");
					xy(19, 5);
					printf("----------------------------------------------------------------------------");

					xy(28, 6);
					printf("读者编号");
					xy(41, 6);
					printf("姓名");
					xy(50, 6);
					printf("班级");
					xy(59, 6);
					printf("是否是否逾期未还");

					xy(28, 8);
					printf("%s", rp1->info.NO);
					xy(41, 8);
					printf("%s", rp1->info.name);
					xy(50, 8);
					printf("%s", rp1->info.sclass);
					if (rp1->info.needpro == 1)
					{
						xy(59, 8);
						printf("逾期欠款");
					}
					else
					{
						xy(59, 8);
						printf("无逾期欠款");
					}
					xy(19, 10);
					printf("----------------------------------------------------------------------------");
					xy(19, 11);
					printf("请选择要进行的操作：\t1.读者逾期还款\t2.修改读者信息\t其他.退出\t");
					xy(19, 11);
					printf("                                                                                                ");
					xy(19, 11);
					printf("完成！");
					sleep(2);
					break;
				}
				case '2':
				{
					system("cls");
					xy(47, 6);
					printf("       信息修改       ");
					xy(47, 7);
					printf("---------------------");

					xy(47, 9);
					printf("您的姓名:");

					xy(47, 11);
					printf("您的班级:");

					xy(47, 13);
					printf("----------------------");
					xy(56, 9);
					scanf("%s", rp1->info.name);
					fflush(stdin);
					xy(56, 11);
					scanf("%s", rp1->info.sclass);
					fflush(stdin);
					xy(47, 14);
					printf("修改成功!");
					sleep(1);
					options = '*';
					break;
				}
				}
			}
			if (options == '2') // 展示读者信息
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
	save(1); //保存信息
	save(0);
	freelReader();
}

//main函数

void main() //用于进入系统,总体流程构架 
{
	int i = 0;
	int j = 0;
	float k = 0.0;
	int in = 0; //统计变量
	FILE *f;
	//文件预读入
	f = fopen("books.dat", "rb");
	read(f, LENB);
	fclose(f);
	//欢迎界面
	bp1 = bp2 = Bhead;
	
	xy(47, 6);
	printf("欢迎来到LMS");
	xy(47, 7);
	printf("----------------------");
	xy(47, 9);
	printf("学号：0101170216") ;
	xy(47, 11);
	printf("姓名：蒋天济");
	xy(47, 13);
	printf("班级：自动化1703");
	xy(47, 15);
	printf("----------------------");
	xy(47, 16);
	printf("请等待五秒...");
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
	printf("本图书馆介绍:");
	xy(47, 8);
	printf("本馆藏书共%d种", i);
	xy(47, 10);
	printf("本馆藏书共%d本", j);
	xy(47, 12);
	printf("本馆藏书总价值%.2f元", k);
	xy(47, 14);
	printf("本馆目前入藏有%d本", in);
	for (i = 4; i >= 0; i--) //动态显示欢迎
	{
		xy(45 + 10 * (i + 1), 4 - (i + 1));
		printf("                                                                                                           ");
		xy(45 + 10 * i, 4 - i);
		printf("欢迎进入图书馆管理系统！");
		sleep(1);
	}
	sleep(2); 
	//进入系统
	while (1) //
	{
		system("cls");
		if (ReaderPos == -1)
			login(); //设置运行参数，返回运行模式 (读者还是管理员)
		if (ReaderPos != 0)
			readerpro(); // 读者进入
		if (ReaderPos == 0)
			adminpro(); // 管理员进入
	}
}
