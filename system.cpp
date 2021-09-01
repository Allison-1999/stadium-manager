#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;

//结构体
typedef struct customer
{
	char ID[100];
	char name[100];
	char gender[100];
	char age[100];
	char phone[100];
	char password[100];
	char email[100];
	float balance;
	char district[100];
	char punish[10];
} customer;
typedef struct admin
{
	char ID[100];
	char stadium[100];
	char name[100];
	char gender[100];
	char email[100];
	char password[100];
	char phone[100];
} admin;
typedef struct period
{
	char start[100];
	char end[100];
} period;
typedef struct order
{
	char ID[100];
	char time[100];
	char date[100];
	char start[100];
	char end[100];
	char courtID[100];
	float cost;
	char status[100];
	char IDtime[100];
} order;
typedef struct court
{
	char ID[100];
	char district[100];
	char stadium[100];
	char sport[100];
	char lowage[100];
	char highage[100];
	float fee;
	char intro[100];
	int ordernumber;
	period ordered[30];
} court;
typedef struct stadium
{
	char name[100];
	char district[100];
	char ID[100];
	court court1, court2;
} stadium;
typedef struct courtnumber
{
	char courtID[100];
	int number;
} courtnumber;
typedef struct courtcost
{
	char courtID[100];
	float cost;
} courtcost;
typedef struct courtsort
{
	char ID[100];
	char district;
	char stadium;
	char sport[100];
	char lowage[100];
	char highage[100];
	float fee;
	char intro[100];
	int ordernumber;
} courtsort;
typedef struct sporttype
{
	char sport[100];
	int ordercount;
} sporttype;

//函数
/*int recommend(char id[100]) //推荐场地
{
	char reid[100], retype[100], redistrict[100], recourt[100], refee[100]
		, idt[100], tra[100], district[100], dis[100];
	int score[20], cnt(0), age, high, low, num(0), max = -1000;
	int cnt;
	float fee(0);
	memset(score, 0, sizeof score);
	//Fundamental Recommend (Based on info)
	FILE *customerInformation = fopen("customer.txt", "r");
	if (customerInformation) //文件打开检查
	{
		FILE *courtinfo = fopen("court.txt", "r");
		if (courtinfo) //文件打开检查
		{
			rewind(customerInformation); //文件读取指针初始化
			fscanf(customerInformation, "%s", idt);
			while (strcmp(idt, id)) //文件读入
			{
				fscanf(customerInformation, "%s %s %d %s %s %s %s %s %s"
					, tra, tra, &age, tra, tra, tra, district, tra, tra);
				fscanf(customerInformation, "%s", idt);
			}
			fscanf(customerInformation, "%s %s %d %s %s %s %s %s %s"
				, tra, tra, &age, tra, tra, tra, district, tra, tra);
			rewind(courtinfo);							//文件读取指针初始化
			while (fscanf(courtinfo, "%s", tra) != EOF) //文件读入
			{
				fscanf(courtinfo, "%s %s %s %d %d %f %s"
					, tra, dis, tra, &low, &high, &fee, tra);
				if (!strcmp(dis, district)) //地区匹配
				{
					score[cnt] += 50;
				}
				if (age >= low && age <= high) //年龄匹配
				{
					score[cnt] += 1000;
				}
				score[cnt] -= (int)fee; //价格
				cnt++;
			}
			fclose(courtinfo); //文件关闭
		}
		else
		{
			cout << "File open error!" << endl;
		}
		fclose(customerInformation); //文件关闭
	}
	else
	{
		cout << "File open error!" << endl;
	}

	//Advanced Recommend (Based on history)
	FILE *orderinfo = fopen("order.txt", "r");
	if (orderinfo) //文件打开检查
	{
		FILE *courtinfo = fopen("court.txt", "r");
		if (courtinfo) //文件打开检查
		{
			//冷门&热门
			int times[2][cnt], i(0), courtid(0), ordernumber(0);
			char orderid[100];
			memset(times, 0, sizeof times);
			rewind(courtinfo); //文件读取指针初始化
			while (fscanf(courtinfo, "%d", &times[0][i]) != EOF)
			{
				fscanf(courtinfo, "%s %s %s %s %s %s %s"
					, tra, tra, tra, tra, tra, tra, tra);
				i++;
			}
			rewind(orderinfo); //文件读取指针初始化
			while (fscanf(orderinfo, "%s", tra) != EOF)
			{
				//遍历订单与统计
				ordernumber++;
				fscanf(orderinfo, "%s %d %s %s %s %s %s"
					, tra, &courtid, tra, tra, tra, tra, tra);
				for (int j(0); j < cnt; j++)
				{
					if (courtid == times[0][j])
					{
						times[1][j]++;
					}
				}
			}
			int sum(0); //取平均数
			for (int j(0); j < cnt; j++)
			{
				sum += times[1][j];
			}
			sum /= cnt;
			if (ordernumber)
			{
				for (int j(0); j < cnt; j++) //取残差进行冷热门加分
				{
					score[j] += abs(sum - times[1][j]) * 100 / ordernumber;
				}
			}

			//个人兴趣
			rewind(orderinfo); //文件读取指针初始化
			int total(0);
			for (int j(0); j < cnt; j++)
			{
				times[1][j] = 0;
			}
			while (fscanf(orderinfo, "%s", orderid) != EOF)
			{
				fscanf(orderinfo, "%s %d %s %s %s %s %s"
					, tra, &courtid, tra, tra, tra, tra, tra);
				char *cut;
				cut = orderid;
				while (*cut != ':') //切割顾客ID
					cut++;
				*(cut - 4) = '\0';
				if (!strcmp(id, orderid)) //个人ID匹配与统计
				{
					total++;
					for (int j(0); j < cnt; j++)
					{
						if (times[0][j] == courtid)
							times[1][j]++;
					}
				}
			}
			if (total) //新用户检查
			{
				for (int j(0); j < cnt; j++) //兴趣加分
				{
					score[j] += times[1][j] * 20 / total;
				}
			}
			fclose(courtinfo); //文件关闭
		}
		else
		{
			cout << "File open error!" << endl;
		}
		fclose(orderinfo); //文件关闭
	}
	else
	{
		cout << "File open error!" << endl;
	}
	int i(0);
	while (i < cnt) //寻找最大值
	{
		if (score[i] >= max)
		{
			max = score[i];
			num = i;
		}
		i++;
	}
	FILE *courtinfo = fopen("court.txt", "r");
	rewind(courtinfo); //文件读取指针初始化
	if (courtinfo)	 //推荐场地详细信息读取
	{
		while (num--)
		{
			fscanf(courtinfo, "%s %s %s %s %s %s %s %s"
				, tra, tra, tra, tra, tra, tra, tra, tra);
		}
		fscanf(courtinfo, "%s %s %s %s %s %s %s %s"
			, reid, recourt, redistrict, retype, tra, tra, refee, tra);
		fclose(courtinfo); //文件关闭
	}
	else
	{
		cout << "File open error!" << endl;
	}
	//推荐输出
	printf("推荐场地\t%s\t\t%-14s\t%s\t\t%s\t\t%s\n"
		, reid, retype, redistrict, recourt, refee);
	return 0;
}*/
int mycmp(const void *num1, const void *num2) //快排比较函数
{
	return ((struct courtsort *)num2)->ordernumber 
		- ((struct courtsort *)num1)->ordernumber;
}
int judges(int ns, int *judges, int *judgee, int count) //结束时间判定
{
	int count1 = 0;
	while (count1 < count) //检验预定时间是否已被占用
	{
		if (ns >= *judges && ns < *judgee)
			return 0;
		count1++;
		judges++;
		judgee++;
	}
	return 1;
}
int judgee(int ne, int *judges, int *judgee, int count) //开启时间判定
{
	int debug;
	int count1 = 0;
	while (count1 < count) //检验预定时间是否已被占用
	{
		if (ne > *judges && ne <= *judgee)
			return 0;
		count1++;
		judgee++;
		judges++;
	}
	return 1;
}
int datejudge(int month, int year) //日期判定
{
	if (month == 1 || month == 3 || month == 5 || month == 7 
		|| month == 8 || month == 10 || month == 12)
		return 31;
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		return 29;
	else
		return 28;
}
int agejudge(char *USERID, char *courtid) //年龄准入判定
{
	int cusage, highage, lowage;
	customer inf[100];
	court ecourt[31];
	char stemp[20];
	int count = 0, count1 = 0, count2 = 0, count3 = 0;
	FILE *getinf = fopen("customer.txt", "r"); //打开顾客信息文件
	if (getinf == NULL)
	{
		printf("未查询到顾客有效信息，请检查文件资料的完整性\n");
		system("pause");
		exit(1);
	}
	rewind(getinf);
	while (fscanf(getinf, "%s", inf[count].ID) != EOF)
	{
		fscanf(getinf, "%s %s %s %s %s %s %s %f %s"
			, inf[count].name, inf[count].gender, inf[count].age, inf[count].phone
			, inf[count].password, inf[count].email, inf[count].district
			, &inf[count].balance, inf[count].punish);
		count++;
	}
	fclose(getinf);
	FILE *courtinfo = fopen("court.txt", "r"); //打开场地信息文件
	if (courtinfo == NULL)
	{
		printf("未查询到场地有效信息，请检查文件资料的完整性\n");
		system("pause");
		exit(1);
	}
	rewind(courtinfo);
	while (fscanf(courtinfo, "%s", ecourt[count2].ID) != EOF)
	{
		fscanf(courtinfo, "%s %s %s %s %s %f %s"
			, ecourt[count2].district, ecourt[count2].stadium, ecourt[count2].sport
			, ecourt[count2].lowage, ecourt[count2].highage, &ecourt[count2].fee
			, ecourt[count2].intro);
		count2++;
	}
	fclose(courtinfo);
	while (count1 < count)
	{ //读取用户年龄信息
		if (!strcmp(USERID, inf[count1].ID))
			cusage = atoi(inf[count1].age);
		count1++;
	}
	while (count3 < count2)
	{
		if (!strcmp(courtid, ecourt[count3].ID))
		{
			highage = atoi(ecourt[count3].highage); //读取场地准入年龄信息
			lowage = atoi(ecourt[count3].lowage);
		}
		count3++;
	}
	if (cusage < lowage || cusage > highage) //判断是否允许进入
		return 0;
	return 1;
}
int punjudge(char *USERID) //违约次数判定
{
	customer inf[100];
	char stemp[20];
	int count = 0, count1 = 0;
	FILE *getinf = fopen("customer.txt", "r"); //打开顾客信息文件
	if (getinf == NULL)
	{
		printf("未查询到有效信息，请检查文件资料的完整性\n");
		return 0;
	}
	rewind(getinf);
	while (fscanf(getinf, "%s", inf[count].ID) != EOF)
	{
		fscanf(getinf, "%s %s %s %s %s %s %s %f %s"
			, inf[count].name, inf[count].gender, inf[count].age, inf[count].phone
			, inf[count].password, inf[count].email, inf[count].district
			, &inf[count].balance, inf[count].punish);
		count++;
	}
	fclose(getinf);
	int cuspun;
	while (count1 < count)
	{
		if (!strcmp(USERID, inf[count1].ID)) //读取用户爽约次数信息
			cuspun = atoi(inf[count1].punish);
		count1++;
	}
	if (cuspun >= 3) //判断违约次数
		return 0;
	return 1;
}
int CompareContentnum(const void *data1, const void *data2) //按预定数量对本场馆的所有场地类型进行排序快排函数
{
	sporttype *pContent1 = (sporttype *)data1;
	sporttype *pContent2 = (sporttype *)data2;
	int nRet = pContent1->ordercount - pContent2->ordercount;
	return nRet;
}
int CompareContentsta(const void *data1, const void *data2) //按场馆编号对本场馆的所有场地进行排序快排函数
{
	courtsort *pContent1 = (courtsort *)data1;
	courtsort *pContent2 = (courtsort *)data2;
	int nRet = pContent1->stadium - pContent2->stadium;
	return nRet;
}
int comparecontentsport(const void *a, const void *b) //按运动类型对本场馆的所有场地进行排序快排函数
{
	courtsort *c = (courtsort *)a;
	courtsort *d = (courtsort *)b;
	return strcmp(c->sport, d->sport);
}
int comparecontentdis(const void *data1, const void *data2) //按地区对本场馆的所有场地进行排序快排函数
{
	courtsort *pContent1 = (courtsort *)data1;
	courtsort *pContent2 = (courtsort *)data2;
	int nRet = pContent1->district - pContent2->district;
	return nRet;
}
int comparecontentfee(const void *data1, const void *data2) //按场地租金对本场馆的所有场地进行排序快排函数
{
	courtsort *pContent1 = (courtsort *)data1;
	courtsort *pContent2 = (courtsort *)data2;
	int nRet = pContent1->fee - pContent2->fee;
	return nRet;
}
int comparecontentid(const void *a, const void *b) //按场馆ID对本场馆的所有场地进行排序快排函数
{
	courtsort *c = (courtsort *)a;
	courtsort *d = (courtsort *)b;
	return strcmp(c->ID, d->ID);
}
int CompareContent(const void *data1, const void *data2) //按预定量对本场馆的所有场地进行排序快排函数
{
	sporttype *pContent1 = (sporttype *)data1;
	sporttype *pContent2 = (sporttype *)data2;
	int nRet = pContent1->ordercount - pContent2->ordercount; //排序
	return nRet;
}
int CompareContent2(const void *data1, const void *data2) //按营业额对本场馆的所有场地排序快排函数
{
	courtcost *pContent1 = (courtcost *)data1;
	courtcost *pContent2 = (courtcost *)data2;
	int nRet = pContent1->cost - pContent2->cost; //排序
	return nRet;
}
int periodstatus() //根据是否有空余场地过滤查询结果
{
	int count1 = 0;
	int ordercount[21];
	int count2 = 0;
	int count = 0;
	int count3 = 0;
	int count4 = 1;
	int count5 = 0;
	char date1[100], date2[100];
	int flag1 = 0;
	int num = 0;
	char sport1[100][100];
	char starttime[100];
	char endtime[100];
	char def[30][200];
	char temp;
	char stemp[20];
	int ns, ne, ndate1, ndate2;
	int orderdate[100], orders[100], ordere[100]; //定义临时变量，存储文件中信息
	court ecourt[31];							  //定义结构体数组，存储文件中信息
	order eorder[31];							  //定义结构体数组，存储文件中信息

	FILE *courtinfo = fopen("court.txt", "r"); //定义文件指针，打开文件
	if (courtinfo == NULL)					   //判断文件是否打开成功，输出提示信息
	{
		printf("未查询到有效信息，请检查文件资料的完整性\n");
		system("pause");
		exit(1);
	}
	rewind(courtinfo); //使文件指针的位置指针指向文件开始
	while (fscanf(courtinfo, "%s", ecourt[count2].ID) != EOF)
	{
		fscanf(courtinfo, "%s %s %s %s %s %f %s"
			, ecourt[count2].district, ecourt[count2].stadium, ecourt[count2].sport
			, ecourt[count2].lowage, ecourt[count2].highage, &ecourt[count2].fee
			, ecourt[count2].intro);
		count2++;
	}
	fclose(courtinfo); //关闭文件
	count = 0;
	FILE *orderinfo = fopen("order.txt", "r"); //定义文件指针，打开文件
	if (orderinfo == NULL)					   //判断文件是否打开成功，输出提示信息
	{
		printf("未查询到有效信息，请检查文件资料的完整性\n");
		exit(1);
	}
	rewind(orderinfo); //使文件指针的位置指针指向文件开始
	count2 = 0;

	while (fscanf(orderinfo, "%s", eorder[count2].ID) != EOF) //从文件中读取信息，将信息存储在结构体数组中
	{
		fscanf(orderinfo, "%s %s %s %s %s %s %f"
			, eorder[count2].time, eorder[count2].courtID, eorder[count2].date
			, eorder[count2].start, eorder[count2].end, eorder[count2].status
			, &eorder[count2].cost);
		orderdate[count2] = atoi(eorder[count2].date);
		orders[count2] = atoi(eorder[count2].start);
		ordere[count2] = atoi(eorder[count2].end);
		count2++;
	}
	fclose(orderinfo); //关闭文件

	printf("请输入你要查询的起始时间（只允许整点查询，24小时制，如：20181019 8：00）\n");
	scanf("%s %s", date1, starttime); //接收查询日期信息
	ns = atoi(starttime);			  //将字符串转化为整型数字，赋值
	ndate1 = atoi(date1);			  //将字符串转化为整型数字，赋值
	printf("请输入你要查询的起结束时间（只允许整点查询，24小时制，如：20181019 10：00）\n");
	scanf("%s %s", date2, endtime);							   //接收查询日期信息
	ne = atoi(endtime);										   //将字符串转化为整型数字，赋值
	ndate2 = atoi(date2);									   //将字符串转化为整型数字，赋值
	while (ns < 6 || ns > 20 || ne < 6 || ne > 20 || ne == ns) //判定输入信息是否符合规范
	{
		printf("输入错误，请重新输入\n");
		printf("请输入你要查询的起始时间（只允许整点查询，24小时制，如：20181019 8：00）\n");
		scanf("%s", starttime); //接收查询日期信息
		ns = atoi(starttime);   //将字符串转化为整型数字，赋值
		printf("请输入你要查询的起结束时间（只允许整点查询，24小时制，如：20181019 10：00）\n");
		scanf("%s", endtime); //接收查询日期信息
		ne = atoi(endtime);   //将字符串转化为整型数字，赋值
	}

	for (count3 = 0; count3 < count1; count3++)
		ecourt[count3].ordernumber = 0; //赋值，初始化

	for (count3 = 0; count3 < count2; count3++)
	{
		if (strcmp(eorder[count3].courtID, ecourt[count3].ID) == 0) //比较场地ID，和订单中场地ID
		{
			if (ndate1 < orderdate[count3] && ndate2 > orderdate[count3]) //比较预定日期
				ecourt[count3].ordernumber++;							  //记录预定次数
			if (ndate1 == orderdate[count3] && ns <= orders[count3])
				ecourt[count3].ordernumber++; //记录预定次数
			if (ndate2 == orderdate[count3] && ne >= ordere[count3])
				ecourt[count3].ordernumber++; //记录预定次数
		}
	}
	printf("可预定空余场地：\n");
	for (count3 = 0; count3 < count2; count3++)
	{
		if (ecourt[count3].ordernumber == 0) //判断预定次数
		{
			printf("场地ID：%s\t运动类型:%s\t场地区域:%s\t所属场馆:%s\t租金:%.2f\t年龄上限：%s\t年龄下限:%s\t简介:%s\n"
				,ecourt[count3].ID, ecourt[count3].sport, ecourt[count3].district, ecourt[count3].stadium
				, ecourt[count3].fee,ecourt[count3].highage, ecourt[count3].lowage, ecourt[count3].intro); 
				//打印相关信息
			flag1 = 1;
		}
	}
	if (flag1 != 1) //判断是否有空域场地
		printf("无可预订空余场地!\n");
	return 0;
}
int sporttypesort() //运动类型预定量排序
{
	int count1 = 0;
	int ordercount[21];
	int count2 = 0;
	int count = 0;
	int count3 = 0;
	int count4 = 1;
	int count5 = 0;
	int count6 = 0;
	int count7 = 0;
	int flag1 = 0;
	int num = 0;
	sporttype typecount[31];
	char sport1[100][100];
	char starttime[100];
	char temp;
	int ns, ne;
	court ecourt[31];
	order eorder[31];
	FILE *courtinfo = fopen("court.txt", "r"); //打开场地文件
	if (courtinfo == NULL)
	{
		printf("未查询到有效信息，请检查文件资料的完整性\n");
		return 0;
	}
	rewind(courtinfo);
	while (fscanf(courtinfo, "%s", ecourt[count1].ID) != EOF)
	{
		fscanf(courtinfo, "%s %s %s %s %s %f %s"
			, ecourt[count1].district, ecourt[count1].stadium, ecourt[count1].sport
			, ecourt[count1].lowage, ecourt[count1].highage, &ecourt[count1].fee
			, ecourt[count1].intro);
		count1++;
	}
	fclose(courtinfo);
	count = 0;
	FILE *orderinfo = fopen("order.txt", "r"); //打开订单文件
	if (orderinfo == NULL)
	{
		printf("未查询到有效信息，请检查文件资料的完整性\n");
		return 0;
	}
	rewind(orderinfo);
	while (fscanf(orderinfo, "%s", eorder[count2].ID) != EOF)
	{
		fscanf(orderinfo, "%s %s %s %s %s %f %s"
			, eorder[count2].time, eorder[count2].courtID, eorder[count2].date
			, eorder[count2].start, eorder[count2].end, &eorder[count2].cost
			, eorder[count2].status);
		count2++;
	}
	fclose(orderinfo);
	printf("请输入你要查询的起始时间（只允许整点查询，24小时制）\n"); //请用户输入查询时间段
	scanf("%s", starttime);
	ns = atoi(starttime);
	while (ns < 6 || ns > 20)
	{
		printf("输入错误，请重新输入\n");
		scanf("%s", starttime);
		ns = atoi(starttime);
	}
	ne = ns + 1;
	sprintf(typecount[0].sport, "%s", ecourt[0].sport); //判断所有场馆中的所有场地运动类型
	while (count4 < count1)
	{
		while (count5 < count4 && strcmp(ecourt[count5].sport, ecourt[count4].sport) != 0)
		{ //判断该场地运动类型是否与之前的场地运动类型重复
			count5++;
		}
		if (count5 == count4)
		{
			num++;
			sprintf(typecount[num].sport, "%s", ecourt[count5].sport);
		}
		count4++;
		count5 = 0;
	}
	count = 0;
	while (count < count1) //计算所有场地中的订单数量
	{
		ordercount[count] = 0;
		count3 = 0;
		while (count3 < count2)
		{
			if (!strcmp(ecourt[count].ID, eorder[count3].courtID) && ns >= atoi(eorder[count3].start) && ne <= atoi(eorder[count3].end)) 
				//判断该订单是否包括该时间段
				ordercount[count]++;
			count3++;
		}
		count++;
	}
	while (count6 < num)
	{ //将场地的订单量叠加在相应场地类型中
		count7 = 0;
		typecount[count6].ordercount = 0;
		while (count7 < count1)
		{
			if (!strcmp(ecourt[count7].sport, typecount[count6].sport))
				typecount[count6].ordercount = typecount[count6].ordercount + ordercount[count7];
			count7++;
		}
		count6++;
	}
	qsort(typecount, num, sizeof(sporttype), CompareContentnum); //使用qsort函数按照预定单数排序运动类型排序
	for (count = num - 1; count >= 0; count--)					 //以降序展示给用户
	{
		printf("运动种类:%-10s\t", typecount[count].sport);
		printf("\t预定次数:%d\n", typecount[count].ordercount);
	}
	return 0;
}
int createorder(char *uID) //创建订单
{
	//	char cID[10][100],date[10][100],stime[10][100], etime[10][100];
	//	float money[10];
	int count = 0, count0 = 0, number[3], sign = 0;
	char stemp[20];
	order inf[100];
	FILE *getinf = fopen("orderengage.txt", "r"); //打开订单预备文件
	rewind(getinf);
	while (fscanf(getinf, "%s", inf[count].courtID) != EOF)
	{
		fscanf(getinf, "%s %s %s %f"
			, inf[count].date, inf[count].start, inf[count].end, &inf[count].cost);
		count++;
	}
	fclose(getinf);
	FILE *orderinfo = fopen("order.txt", "a+");
	/* Get current date and time */
	struct tm *now;
	time_t tval;
	tval = time(NULL);
	now = localtime(&tval);
	int year, month, day, nowyear, nowmonth;
	char nID[100], *nstime, *netime, status[100] = {"未确定"}, temp[100];
	while (count0 < count) //将当前时间输入程序
	{
		year = atoi(inf[count0].date) / 10000;
		month = (atoi(inf[count0].date) % 10000 - atoi(inf[count0].date) % 100) / 100;
		day = atoi(inf[count0].date) % 100;
		if ((year == now->tm_year + 1900 && month > now->tm_mon + 1 && day + datejudge(now->tm_mon, year) - now->tm_mday <= 7) || (year == now->tm_year + 1900 && month == now->tm_mon + 1 && day - now->tm_mday <= 7 && day - now->tm_mday >= 0))
		{ //判断用户预定时间是否与预定日期是否相隔一周之内
			nowyear = now->tm_year + 1900;
			nowmonth = now->tm_mon + 1;
			sprintf(nID, "%s%4d:%d:%02d:%d:%02d", uID, now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
					now->tm_hour, now->tm_min);
			fprintf(orderinfo, "%s %4d:%d:%02d:%d:%02d %s %s %s %s %.2f %s\n"
				, nID, now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour
				, now->tm_min, inf[count0].courtID, inf[count0].date, inf[count0].start
				, inf[count0].end, inf[count0].cost, status);
		} //将订单信息录入文件
		else
		{
			number[sign] = count0 + 1;
			sign++;
		}
		count0++;
	}
	fclose(orderinfo);
	if (sign == 0)
		printf("您的%d个场地的订单创建成功\n", count); //提示用户那个订单成功或失败
	else if (sign == 1)
		printf("您的第%d个场地预定时间大于于一周\n", number[0]);
	else if (sign == 2)
		printf("您的第%d个和第%d个场地预定时间大于一周\n", number[0], number[1]);
	else
		printf("您的3个场地预定时间均大于一周\n");
	remove("orderengage.txt");
	FILE *ordercharge = fopen("customer.txt", "r");
	customer charge[100];
	int count3 = 0, count4 = 0, count5 = 0, flag = 0;
	char charges[20][100], expense[100], *ptr;
	rewind(ordercharge); //将用户预定日期时间段录入文件
	while (fscanf(ordercharge, "%s", charge[count3].ID) != EOF)
	{
		fscanf(ordercharge, "%s %s %s %s %s %s %s %f %s"
			, charge[count3].name, charge[count3].gender, charge[count3].age
			, charge[count3].phone, charge[count3].password, charge[count3].email
			, charge[count3].district, &charge[count3].balance, charge[count3].punish);
		count3++;
	}
	fclose(ordercharge);
	for (count4 = 0; count4 < count3; count4++)
	{	
		//相应订单为用户账户余额扣费
		if (strcmp(charge[count4].ID, uID) == 0)
		{
			if (inf[count - 1].cost <= charge[count4].balance)
			{
				//printf("订单创建成功!\n");
				charge[count4].balance -= inf[count - 1].cost;
				flag = 1;
			}
			else
			{
				printf("余额不足!\n"); //若余额不足则提示错误终止预定
			}
		}
	}

	if (flag == 1)
	{
		FILE *ordercharge = fopen("customer.txt", "w");
		for (count5 = 0; count5 < count3; count5++)
			fprintf(ordercharge, "%s %s %s %s %s %s %s %s %.2f %s\n"
				, charge[count5].ID, charge[count5].name, charge[count5].gender
				, charge[count5].age, charge[count5].phone, charge[count5].password
				, charge[count5].email, charge[count5].district, charge[count5].balance
				, charge[count5].punish);
	} //更改用户信息扣费
	fclose(ordercharge);
	return 0;
}
int showcourt(char *USERID) //展示场馆信息并开启创建订单入口
{
	float cost[10];
	int count = 0;
	int count6 = 0;
	int flag = 1, max, count5 = 0, count4 = 0;
	int ordereds[20];
	int orderede[20];
	courtsort ecourt[31];
	order eorder[31];
	char date[30];
	char starttime[10], endtime[10];
	char stemp[100];
	char temp;
	int nchoice1, nchoice2, nchoice3, ns, ne, ndate, nchoice4;
	char choice1[10], choice4[10], choice2[10], choice3[10];
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	char courtid[20];
	char orderdate[20];
	char orderstart[20];
	char orderend[20];
	int dealcount = 0, endofdeal = 0;
	int counta = 0, countb = 0, countc = 0, counting1 = 0, counting2 = 0;
	int counting3 = 0, countings = 0, countingc = 0; 
	//counta--场地，countb--订单，countc--顾客,counting1--总循环1,counting2--总循环2,counting3--总循环3,countings--打印用循环
	int subcounta = 0;	//subcounta--订单提取顾客ID
	int incount;		//创建订单数组以及初始化
	int countingx;
	
	while (!endofdeal && dealcount < 3)	//判断是否完成预定或已预定3个场地
	{
		count = 0;
		count1 = 0;
		printf("请输入你想要预定的日期（格式如20180506）\n"); //读取用户想要预定的日期
		scanf("%s", date);
		ndate = atoi(date);
		while (!ndate || strlen(date) != 8)
		{
			printf("日期输入错误，请重新输入\n");
			scanf("%s", date);
			ndate = atoi(date);
		}
		FILE *orderinfo = fopen("order.txt", "r"); //打开订单文件
		if (orderinfo == NULL)
		{
			printf("未查询到有效信息，请检查文件资料的完整性\n");
			return 0;
		}
		rewind(orderinfo);
		while (fscanf(orderinfo, "%s", eorder[count].ID) != EOF)
		{
			fscanf(orderinfo, "%s %s %s %s %s %f %s"
				, eorder[count].time, eorder[count].courtID, eorder[count].date
				, eorder[count].start, eorder[count].end, &eorder[count].cost
				, eorder[count].status);
			count++;
		}
		fclose(orderinfo);
		FILE *courtinfo = fopen("court.txt", "r"); //打开场地文件
		if (courtinfo == NULL)
		{
			printf("未查询到有效信息，请检查文件资料的完整性\n");
			return 0;
		}
		rewind(courtinfo);
		while (fscanf(courtinfo, "%s", ecourt[count1].ID) != EOF)
		{
			fscanf(courtinfo, "%c%c%c%c%c%s %s %s %f %s"
				, &temp, &ecourt[count1].district, &temp, &ecourt[count1].stadium, &temp
				, ecourt[count1].sport, ecourt[count1].lowage, ecourt[count1].highage
				, &ecourt[count1].fee, ecourt[count1].intro);
			count1++;
		}
		fclose(courtinfo);
		printf("请选择浏览场地的排序方式\n"); //选项菜单
		printf("\t1.按场地区域顺序排序\n");
		printf("\t2.按场馆名称进行排序\n");
		printf("\t3.按租金高低进行排序\n");
		printf("\t4.按预定量高低进行排序\n");
		printf("\t5.按场地ID进行排序\n");
		printf("\t6.按场地类型进行排序\n");
		printf("\t7.根据是否有空余场地过滤查询\n");
		printf("\t0.返回上一级\n");
		flag = 1;
		while (flag)
		{
			scanf("%s", choice4);
			nchoice4 = atoi(choice4);
			while (nchoice4 < 0 || nchoice4 > 7)
			{
				printf("输入错误，请重新输入\n");
				scanf("%s", choice4);
				nchoice4 = atoi(choice4);
			}
			switch (choice4[0])
			{
			case 49:
				qsort(ecourt, count1, sizeof(courtsort), comparecontentdis); 
				//使用qsort函数按照地区对整个结构体数组进行排序
				flag = 0;
				break;
			case 50:
				qsort(ecourt, count1, sizeof(courtsort), CompareContentsta); 
				//使用qsort函数按照场馆对整个结构体数组进行排序
				flag = 0;
				break;
			case 51:
				qsort(ecourt, count1, sizeof(courtsort), comparecontentfee); 
				//使用qsort函数按照租金对整个结构体数组进行排序
				flag = 0;
				break;
			case 52:
			{
				char stemp[20], temp;
				FILE *getcourtinf = fopen("court.txt", "r"); //打开场地文件
				while (fscanf(getcourtinf, "%s", ecourt[counta].ID) != EOF)
				{
					fscanf(getcourtinf, "%c%c%c%c%c %s %s %s %f %s"
						, &temp, &ecourt[counta].district, &temp, &ecourt[counta].stadium
						, &temp, ecourt[counta].sport, ecourt[counta].lowage
						, ecourt[counta].highage, &ecourt[counta].fee, ecourt[counta].intro);
					counta++;
				}
				fclose(getcourtinf);						   //关闭场地文件
				for (incount = 0; incount < counta; incount++) //订单数组初始化
					ecourt[incount].ordernumber = 0;
				order takeorder[100]; //拆分订单文件
				char orderinfo[20][100];
				FILE *getorderinf = fopen("order.txt", "r"); //打开订单文件
				rewind(getorderinf);
				while (fscanf(getorderinf, "%s", takeorder[countb].ID) != EOF)
				{
					fscanf(getorderinf, "%s %s %s %s %s %f %s"
					, takeorder[countb].time, takeorder[countb].courtID, takeorder[countb].date
					, takeorder[countb].start, takeorder[countb].end, &takeorder[countb].cost
					, takeorder[countb].status);
					countb++;
				}
				fclose(getorderinf);	   //关闭订单文件
				while (counting1 < counta) //场地信息遍历
				{
					counting2 = 0;			   //循环初始化
					while (counting2 < countb) //订单信息遍历
					{
						if (strcmp(ecourt[counting1].ID, takeorder[counting2].courtID) == 0) //比较场馆ID和订单中的场馆ID
						{
							ecourt[counting1].ordernumber++; //统计场地订单
						}
						counting2++;
					}
					counting1++;
				}
				qsort(ecourt, counting1, sizeof(struct courtsort), mycmp); //使用qsort函数按照场地预定量对整个结构体数组进行排序
				flag = 0;
				break;
			}
			case 53:
				qsort(ecourt, count1, sizeof(courtsort), comparecontentid); //使用qsort函数按照场地id对整个结构体数组进行排序
				flag = 0;
				break;
			case 54:
				qsort(ecourt, count1, sizeof(courtsort), comparecontentsport); //使用qsort函数按照运动类型对整个结构体数组进行排序
				flag = 0;
				break;
			case 55:
				periodstatus();
			case 48:
				return 0;
			default:
				printf("输入错误请重新输入\n");
			}
		}
		printf("场地序号\t场地ID\t\t运动场类型\t场地区域\t场馆名称\t租金\n"); //向用户展示场地的简要信息
		//recommend(USERID);
		for (count6 = 0; count6 < count1; count6++)
			printf(" %d\t\t%s\t\t%-14s\t%c\t\t%c\t\t%.2f\n"
				, count6 + 1, ecourt[count6].ID, ecourt[count6].sport, ecourt[count6].district
				, ecourt[count6].stadium, ecourt[count6].fee);
		printf("请输入你想了解的场地的的序号\n");
		scanf("%s", choice1);
		nchoice1 = atoi(choice1);
		nchoice1--;
		while (nchoice1 < 0 || nchoice1 > count1)
		{
			printf("输入错误，请重新输入\n");
			scanf("%s", choice1);
			nchoice1 = atoi(choice1);
			nchoice1--;
		}
		while (count4 < count)
		{
			if (!strcmp(date, eorder[count4].date) && !strcmp(ecourt[nchoice1].ID, eorder[count4].courtID)) //读取当天该场地订单的起止时间
			{
				ordereds[count3] = atoi(eorder[count4].start);
				orderede[count3] = atoi(eorder[count4].end);
				count3++;
			}
			count4++;
		}
		printf("场地序号\t场地ID\t\t运动场类型\t场地区域\t场馆名称\t租金\n"); //向用户展示场地详细信息
		printf("%d\t\t%s\t\t%-12s\t%c\t\t%c\t\t%.2f\n"
			, nchoice1 + 1, ecourt[nchoice1].ID, ecourt[nchoice1].sport
			, ecourt[nchoice1].district, ecourt[nchoice1].stadium, ecourt[nchoice1].fee);
		printf("\n适用年龄：%s-%s\n", ecourt[nchoice1].lowage, ecourt[nchoice1].highage);
		printf("简单介绍：\n\t%s\n\n", ecourt[nchoice1].intro);
		printf("时段\t预订情况\n");
		for (count2 = 6; count2 < 22; count2++) //向用户展示该天预订情况
		{
			printf("%-2d-%-2d\t", count2, count2 + 1);
			count5 = 0;
			flag = (count2 >= ordereds[count5] && count2 < orderede[count5]);
			while (count5 < count3 && !flag)
			{
				count5++;
				flag = count2 >= ordereds[count5] && count2 < orderede[count5];
			}
			printf("%d\n", flag);
		}
		if (punjudge(USERID)) //判断用户的爽约次数是否少于3次
		{
			cout << "请输入操作对应序号：" << endl;
			cout << "\t1.预定\n\t2.退出\n\t0.重新查询" << endl;
			scanf("%s", choice2);
			nchoice2 = atoi(choice2);
			while (nchoice2 != 1 && nchoice2 != 0 && nchoice2 != 2)
			{
				printf("输入错误，请重新输入\n");
				scanf("%s", choice2);
				nchoice2 = atoi(choice2);
			}
			if (nchoice2 == 1)
			{
				if (agejudge(USERID, ecourt[nchoice1].ID))
				{
					//printf("%d",agejudge(USERID,ecourt[nchoice1].ID));
					printf("请输入你要预定的起始时间（只允许整点预定，24小时制）\n");
					scanf("%s", starttime);
					ns = atoi(starttime);
					while (ns < 6 || ns > 20 || !judges(ns, ordereds, orderede, count3))
					{ //判断用户想要预定的起始时间是否合乎标准或已被预定
						printf("输入错误，请重新输入\n");
						scanf("%s", starttime);
						ns = atoi(starttime);
					}
					printf("请输入你要预定的结束时间（只允许整点预定，24小时制）\n");
					scanf("%s", endtime);
					ne = atoi(endtime);
					while (ne > 21 || ne <= ns || !judgee(ne, ordereds, orderede, count3))
					{ //判断用户想要预定的结束时间是否合乎标准或已被预定
						printf("输入错误，请重新输入\n");
						scanf("%s", endtime);
						ne = atoi(endtime);
					}
					cost[dealcount] = ecourt[nchoice1].fee * (ne - ns);
					dealcount++;
					printf("请输入操作对应序号：\n");
					printf("\t1.继续预定其他场地\n\t2.完成预定\n"); //判断用户是否想要继续预定
					scanf("%s", choice3);
					nchoice3 = atoi(choice3);
					while (nchoice3 != 2 && nchoice3 != 1)
					{
						printf("输入错误，请重新输入\n");
						scanf("%s", choice3);
						nchoice3 = atoi(choice3);
					}
					if (nchoice3 == 2)
						endofdeal = 1;
					FILE *getinf = fopen("orderengage.txt", "a+");
					fprintf(getinf, "%s %s %d %d %f\n"
						, ecourt[nchoice1].ID, date, ns, ne, cost[dealcount - 1]); 
						//将部分订单信息录入txt
					fclose(getinf);
					count1 = 0;
				}
				else
					printf("您的年龄不适宜该场地，出于安全考虑不允许预定\n"); 
					//若年龄判断不符合就不允许预定
			}
		}
		else if (!punjudge(USERID))
			printf("您当前已爽约3次，禁止再次预约\n"); //若爽约次数超过3次则不允许预定
		if (nchoice2 == 2)
			return 0; //返回menu
					  //选择为0则再次启动
	}
	if (dealcount == 3)
	{
		cout<<"已超出预定限制次数！"<<endl;
	}
	createorder(USERID);
	return 0;
}
int adminshowcourt(char adminstadium) //向管理员展示场馆信息
{
	float cost[10];
	int count = 0;
	int count6 = 0;
	int flag = 1, max, count5 = 0, count4 = 0;
	int checkflag = 1;
	int ordereds[20];
	int orderede[20];
	courtsort ecourt[31];
	order eorder[31];
	char date[30];
	char choice1[10], choice2[10], choice3[10], choice4[10];
	char starttime[10], endtime[10];
	char temp;
	int nchoice1, nchoice2, nchoice3, ns, ne, ndate, nchoice4;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	char courtid[20];
	char orderdate[20];
	char orderstart[20];
	char orderend[20];
	int dealcount = 0, endofdeal = 0;
	FILE *orderinfo = fopen("order.txt", "r"); //打开订单文件
	if (orderinfo == NULL)
	{
		printf("未查询到有效信息，请检查文件资料的完整性\n");
		return 0;
	}
	rewind(orderinfo);
	while (fscanf(orderinfo, "%s", eorder[count].ID) != EOF)
	{
		fscanf(orderinfo, "%s %s %s %s %s %s %f"
			, eorder[count].time, eorder[count].courtID, eorder[count].date
			, eorder[count].start, eorder[count].end, eorder[count].status
			, &eorder[count].cost);
		count++;
	}
	fclose(orderinfo);
	FILE *courtinfo = fopen("court.txt", "r"); //打开场地文件
	if (courtinfo == NULL)
	{
		printf("未查询到有效信息，请检查文件资料的完整性\n");
		return 0;
	}
	rewind(courtinfo);
	while (fscanf(courtinfo, "%s", ecourt[count1].ID) != EOF)
	{
		fscanf(courtinfo, "%c%c%c%c%c %s %s %s %f %s"
			, &temp, &ecourt[count1].stadium, &temp, &ecourt[count1].district, &temp
			, ecourt[count1].sport, ecourt[count1].lowage, ecourt[count1].highage
			, &ecourt[count1].fee, ecourt[count1].intro);
		count1++;
	}
	fclose(courtinfo);
	while (checkflag)
	{
		printf("请输入你想要查询的日期（格式如20180506）\n"); //让用户输入想要查询的日期
		scanf("%s", date);
		ndate = atoi(date);
		while (!ndate || strlen(date) != 8)
		{
			printf("日期输入错误，请重新输入\n");
			scanf("%s", date);
			ndate = atoi(date);
		}
		printf("请选择浏览场地的排序方式\n");
		printf("1.按场地区域顺序排序\n");
		printf("2.按场地ID进行排序\n");
		printf("0.返回上一级\n");
		while (flag)
		{
			scanf("%s", choice4);
			switch (choice4[0])
			{
			case 49:
				qsort(ecourt, count1, sizeof(courtsort), comparecontentdis); 
				//用qsort函数按照场馆地区对结构体数组进行排序
				flag = 0;
				break;
			case 50:
				qsort(ecourt, count1, sizeof(courtsort), comparecontentid); 
				// 用qsort函数按照场地ID对结构体数组进行排序
				flag = 0;
				break;
			case 48:
				return 0;
			default:
				printf("输入错误请重新输入\n");
			}
		}
		printf("场地序号\t场地ID\t\t运动场类型\t场地区域\t场馆名称\t租金\n"); //将简要信息展示给管理员
		for (count6 = 0; count6 < count1; count6++)
			if (ecourt[count6].stadium == adminstadium)
				printf(" %d\t\t%s\t\t%-12s\t%c\t\t%c\t\t%.2f\n"
					, count6 + 1, ecourt[count6].ID, ecourt[count6].sport
					, ecourt[count6].district, ecourt[count6].stadium, ecourt[count6].fee);
		printf("请输入您想查询的场地的的序号\n");
		scanf("%s", choice1);
		nchoice1 = atoi(choice1);
		nchoice1--;
		while (nchoice1 < 0 || nchoice1 > count1)
		{
			printf("输入错误，请重新输入\n");
			scanf("%s", choice1);
			nchoice1 = atoi(choice1);
			nchoice1--;
		}
		while (count4 < count - 1)
		{
			if (!strcmp(date, eorder[count4].date) && !strcmp(ecourt[nchoice1].ID, eorder[count4].courtID))
			{
				ordereds[count3] = atoi(eorder[count4].start);
				orderede[count3] = atoi(eorder[count4].end);
				count3++;
			}
			count4++;
		}
		printf("场地序号\t场地ID\t\t运动场类型\t场地区域\t场馆名称\t租金\n"); //将详细信息展示给管理员
		printf("%d\t\t%s\t\t%-8s\t%c\t\t%c\t\t%.2f\n"
			, nchoice1 + 1, ecourt[nchoice1].ID, ecourt[nchoice1].sport
			, ecourt[nchoice1].district, ecourt[nchoice1].stadium, ecourt[nchoice1].fee);
		printf("适用年龄：%s-%s\n\n", ecourt[nchoice1].lowage, ecourt[nchoice1].highage);
		printf("简单介绍：\n\n%s\n\n", ecourt[nchoice1].intro);
		printf("时段\t预订情况\n");
		for (count2 = 6; count2 < 22; count2++)
		{ //将当天预定情况展示给用户
			printf("%-2d-%-2d\t", count2, count2 + 1);
			count5 = 0;
			while (count5 < count3)
			{
				flag = count2 >= ordereds[count5] && count2 + 1 <= orderede[count5];
				count5++;
			}
			printf("%d\n", flag);
		}
		printf("输入1继续查询，输入0返回上一级\n"); //确认用户是否需要继续查询
		scanf("%s", choice2);
		nchoice2 = atoi(choice2);
		while (nchoice2 != 0 && nchoice2 != 1)
		{
			printf("输入错误，请重新输入\n");
			scanf("%s", choice2);
			nchoice2 = atoi(choice2);
		}
		if (!nchoice2)
			checkflag = 0;
	}
	return 0;
}
int adminshoworder(char adminstadium) //向管理员显示场馆订单信息
{
	char scourtid[41][41];
	order eorder[101];
	courtsort ecourt[31];
	int count = 0, count1 = 0;
	int count2 = 0, count3 = 0;
	int count4 = 0, count5 = 0;
	int flag = 0;
	char temp;
	char stemp[20];
	FILE *orderinfo = fopen("order.txt", "r"); //打开订单文件
	if (orderinfo == NULL)
	{
		printf("未查询到有效信息，请检查文件资料的完整性\n");
		return 0;
	}
	rewind(orderinfo);
	while (fscanf(orderinfo, "%s", eorder[count].ID) != EOF)
	{
		fscanf(orderinfo, "%s %s %s %s %s %f %s"
			, eorder[count].time, eorder[count].courtID, eorder[count].date
			, eorder[count].start, eorder[count].end, &eorder[count].cost
			, eorder[count].status);
		count++;
	}
	fclose(orderinfo);
	FILE *courtinfo = fopen("court.txt", "r"); //打开场地文件
	if (courtinfo == NULL)
	{
		printf("未查询到有效信息，请检查文件资料的完整性\n");
		return 0;
	}
	rewind(courtinfo);
	while (fscanf(courtinfo, "%s", ecourt[count1].ID) != EOF)
	{
		fscanf(courtinfo, "%c%c%c%c%c %s %s %s %f %s"
			, &temp, &ecourt[count1].stadium, &temp, &ecourt[count1].district, &temp
			, ecourt[count1].sport, ecourt[count1].lowage, ecourt[count1].highage
			, &ecourt[count1].fee, ecourt[count1].intro);
		count1++;
	}
	fclose(courtinfo);
	printf("订单ID\t\t\t预定时间\t场地ID\t预定日期\t开始时间\t结束时间\t订单金额\t订单状态\n");

	while (count2 < count1)
	{
		if (ecourt[count2].stadium == adminstadium)
		{ //筛选出管理员所在场馆的所有订单
			strcpy(scourtid[count4], ecourt[count2].ID);
			count4++;
		}
		count2++;
	}
	while (count3 < count)
	{
		while (count5 < count4)
		{
			if (!strcmp(eorder[count3].courtID, scourtid[count5]))
			{ //展示订单信息
				printf("%s\t%s\t%s\t%s\t%s\t\t%s\t\t%.2f\t\t%s\n"
					, eorder[count3].ID, eorder[count3].time, eorder[count3].courtID
					, eorder[count3].date, eorder[count3].start, eorder[count3].end
					, eorder[count3].cost, eorder[count3].status);
				flag = 1;
			}
			count5++;
		}
		count3++;
		count5 = 0;
	}
	if (!flag)
		printf("该场馆无订单\n");
	return 0;
}
int adminmodification(char IDt[100]) //管理员个人信息修改函数
{
	char option2[100];
	option2[0] = '1';
	//变量声明
	while (option2[0] == '1')
	{
		int p = 0, i, flag = 0, flag1 = 1, k, j = 0, first2 = 1, temp, flag4 = 0;
		char option[100];
		char ch1[100], ch2[100], ch3[100], password[100];
		admin inf[100];
		//变量声明
		FILE *adminInformation;
		adminInformation = fopen("admin.txt", "r");
		rewind(adminInformation);
		while (fscanf(adminInformation, "%s %s %s %s %s %s %s"
			, inf[p].ID, inf[p].name, inf[p].gender, inf[p].phone, inf[p].password
			, inf[p].email, inf[p].stadium) != EOF)
		{
			if (strcmp(inf[p].ID, IDt) == 0)
				k = p;
			p++;
		}
		fclose(adminInformation);
		while (flag1 == 1)
		{
			printf("请输入您需修改的信息选项：\n\t1.密码\n\t2.手机号\n\t3.邮箱\n\t4.场馆\n\t5.姓名\n\t6.性别\n");

			scanf("%s", option);

			if (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0 &&
				strcmp(option, "4") != 0 && strcmp(option, "5") != 0 && strcmp(option, "6") != 0)
				printf("请输入正确选项");
			else
			{
				flag1 = 0;

				if (strcmp(option, "1") == 0)
				{
					int success = 1;
					while (success)
					{
						int temp = 1;
						while (temp)
						{
							printf("请创建您的密码(6-10位)\n");
							scanf("%s", password);
							if (strlen(password) < 6 || strlen(password) > 10)
							{
								printf("您的密码长度不符\n");
							}
							else
							{
								printf("请再次输入您的密码\n");
								scanf("%s", inf[k].password);
								temp = 0;
							}
						}
						if (strcmp(inf[k].password, password) != 0 || 0)
							printf("两次输入密码不同，请重新创建密码\n");
						else
							success = 0;
					} //读取新密码并储存
				}
				if (strcmp(option, "2") == 0)
				{
					int success = 1;
					while (success)
					{
						success = 0;
						int flag1(0), flag2(1), b;
						printf("请输入您的手机号码（11位）\n");
						scanf("%s", ch1);
						if (strlen(ch1) == 11)
							flag1 = 1;
						for (b = 0; b < 11; b++)
						{
							if (isdigit(ch1[b]) == 0)
								flag2 = 0;
						}
						if (flag1 != 1 && flag2 != 1)
						{
							printf("您输入的号码有误，请确认后再次输入\n");
							success = 1;
						}
						else
						{
							strcpy(inf[k].phone, ch1);
							printf("您的手机号已修改成功！\n");
						}
					}
				}
				if (strcmp(option, "3") == 0)
				{
					int success = 1;
					while (success)
					{
						printf("请输入您的邮箱：\n");
						scanf("%s", ch1);
						int a = 0, b = 0, c = 0, e = 0, f = 0, g = 0;
						while (ch1[a] != '\0')
						{
							if (ch1[a] == '@')
							{
								b = 1;
								c = a; //读取'@'字符所在的位置
								break; //检验输入的邮箱里是否有'@'
							}
							else
								a++;
						}
						while (ch1[e] != '\0')
						{
							if (ch1[e] == '.')
							{
								f = 1;
								g = e; //读取'.'字符所在的位置
								break; //检验输入的邮箱里是否有'.'
							}
							else
								e++;
						}
						if (c != 0 && b == 1 && f == 1 && g > (c + 1))
						{
							strcpy(inf[k].email, ch1);
							printf("您的邮箱已修改成功！\n");
							success = 0; //测试其是否有'@''.'位置
						}
						else
						{
							printf("您输入的邮箱有误！\n");
						}
					}
				}
				if (strcmp(option, "4") == 0)
				{
					char adressnumber[100];
					int success = 1;
					getchar();
					printf("请选择您的所属场馆:\n");
					printf("\t1.A\n");
					printf("\t2.B\n");
					printf("\t3.C\n");
					cin >> adressnumber;
					while (adressnumber[0] < '1' || adressnumber[0] > '3' || strlen(adressnumber) > 1)
					{
						printf("请输入正确场馆序号");
						cin >> adressnumber;
					}
					if (adressnumber[0] == '1')
						strcpy(inf[k].stadium, "A");
					if (adressnumber[0] == '2')
						strcpy(inf[k].stadium, "B");
					if (adressnumber[0] == '3')
						strcpy(inf[k].stadium, "C");
				}
				if (strcmp(option, "5") == 0)
				{
					printf("请您输入您的姓名\n");
					scanf("%s", ch1);
					strcpy(inf[k].name, ch1);
					printf("您的姓名已修改成功！\n");
				}
				if (strcmp(option, "6") == 0)
				{
					char gendernumber[100];
					getchar();
					printf("请输入您的性别\n");
					printf("\t1.男\n");
					printf("\t2.女\n");
					printf("\t3.保密\n");
					cin >> gendernumber;
					while (gendernumber[0] < '1' || gendernumber[0] > '3' || strlen(gendernumber) > 1)
					{
						printf("请输入正确的性别序号\n");
						cin >> gendernumber;
					}
					if (gendernumber[0] == '1')
						strcpy(inf[k].gender, "男");
					if (gendernumber[0] == '2')
						strcpy(inf[k].gender, "女");
					if (gendernumber[0] == '3')
						strcpy(inf[k].gender, "保密");
					cout << "您的性别已修改成功！" << endl;
				}
			}
		}
		fflush(stdin);
		adminInformation = fopen("admin.txt", "w");
		for (i = 0; i < p; i++)
		{
			fprintf(adminInformation, "%s %s %s %s %s %s %s\n"
				, inf[i].ID, inf[i].name, inf[i].gender, inf[i].phone, inf[i].password
				, inf[i].email, inf[i].stadium);
		} //将修改后的信息和之前的信息录入
		fclose(adminInformation);
		printf("请输入您要进行的选项：\n\t1.继续修改信息\n\t2.返回上一级\n");
		cin >> option2;
		while (option2[0] < '1' || option2[0] > '2')
		{
			printf("请输入正确选项\n");
			cin >> option2;
		}
	}
	return 0;
}
int queryadmin(char ID[100]) //查询管理员个人信息
{
	admin inf[100];
	char ch1[100];
	char option[100];
	int success = 1, first = 1, i = 0, flag = 1;

	while (flag)
	{
		FILE *adminInformation = NULL;
		adminInformation = fopen("admin.txt", "r");

		if (adminInformation == NULL)
		{
			printf("open file failed!\n");
			return -1;
		}
		rewind(adminInformation);
		while (fscanf(adminInformation, "%s", inf[i].ID) != EOF)
		{
			fscanf(adminInformation, "%s %s %s %s %s %s"
				, inf[i].name, inf[i].gender, inf[i].phone, inf[i].password
				, inf[i].email, inf[i].stadium);
			if (strcmp(inf[i].ID, ID) == 0)
			{
				printf("\n您的个人信息为：\n\tID: %s\n\t姓名：%s\n\t性别：%s\n\t手机号：%s\n\t邮箱：%s\n\t场馆：%s\n"
					, inf[i].ID, inf[i].name, inf[i].gender, inf[i].phone, inf[i].email, inf[i].stadium);
				break;
			}
			i++;
		} //提取个人信息
		fclose(adminInformation);
		while (success)
		{
			printf("请输入您要进行的选项：\n\t1.修改信息\n\t2.返回上一级\n");
			scanf("%s", option);
			if (strcmp(option, "1") != 0 && strcmp(option, "2") != 0)
				printf("请输入正确选项\n");
			else
			{
				if (strcmp(option, "1") == 0)
				{
					adminmodification(ID);
					flag = 0;
					break;
				}
				if (strcmp(option, "2") == 0)
				{
					flag = 0;
					break;
				}
			}
		}
	}
	return 0;
}
int stadiumvolume(char adminstadium) //统计场馆营业额
{
	float cost;
	int i = 0, j = 0, k = 0, m = 0, n = 0, h, a, number[100], count;
	order inf[100];
	courtsort inf2[100];
	admin inf3[100];
	char stadium[10];
	char courtID[100][100];
	char stemp[20];
	char temp;
	FILE *orderInformation;
	orderInformation = fopen("order.txt", "r");
	FILE *courtInformation;
	courtInformation = fopen("court.txt", "r");
	rewind(courtInformation);
	while (fscanf(courtInformation, "%s", inf2[j].ID) != EOF) //打开场地信息文件
	{
		fscanf(courtInformation, "%c%c%c%c%c %s %s %s %f %s"
			, &temp, &inf2[j].stadium, &temp, &inf2[j].district, &temp
			, inf2[j].sport, inf2[j].lowage, inf2[j].highage, &inf2[j].fee
			, inf2[j].intro);
		if (inf2[j].stadium == adminstadium)
		{
			strcpy(courtID[m], inf2[j].ID);
			m++;
		}
		j++;
	}
	fclose(courtInformation);
	rewind(orderInformation);
	while (fscanf(orderInformation, "%s", inf[i].ID) != EOF) //打开订单信息文件
	{
		fscanf(orderInformation, "%s %s %s %s %s %f %s"
			, inf[i].time, inf[i].courtID, inf[i].date, inf[i].start, inf[i].end
			, &inf[i].cost, inf[i].status);
		for (n = 0; n < m; n++)
		{
			if (strcmp(inf[i].courtID, courtID[n]) == 0)
			{
				cost = cost + inf[i].cost; //计算营业额
			}
		}
		i++;
	}
	fclose(orderInformation);
	printf("该场馆的营业额为%.2f\n", cost); //展示给用户
	return 0;
}
int bookingvolume_sort(char stadium) //按预定量对本场馆的所有场地进行排序
{
	int i = 0, j = 0, k = 0, m = 0, n = 0, h, a, number[100], count;
	order inf[100];
	court inf2[100];
	admin inf3[100];
	char stemp[20];
	char courtID[100][100];
	char stadiumtemp[100];
	//变量定义
	sprintf(stadiumtemp, "%c", stadium);
	FILE *orderInformation;
	orderInformation = fopen("order.txt", "r");
	FILE *courtInformation;
	courtInformation = fopen("court.txt", "r");
	FILE *adminInformation;
	adminInformation = fopen("admin.txt", "r");
	//打开文件
	rewind(courtInformation); //使文件指针的位置指针指向文件开始
	while (fscanf(courtInformation, "%s", inf2[j].ID) != EOF)
	{
		fscanf(courtInformation, "%s %s %s %s %s %f %s"
			, inf2[j].stadium, inf2[j].district, inf2[j].sport, inf2[j].lowage
			, inf2[j].highage, &inf2[j].fee, inf2[j].intro);
		if (strcmp(stadiumtemp, inf2[j].stadium) == 0) //比较当前管理员所属场馆和文件中场馆信息
		{
			strcpy(courtID[m], inf2[j].ID);

			m++;
		}
		j++;
	}
	//读取文件信息，将信息存储在结构体数组中
	fclose(courtInformation);

	for (h = 0; h < m; h++)
	{
		number[h] = 0;
	}
	rewind(orderInformation); //使文件指针的位置指针指向文件开始
	while (fscanf(orderInformation, "%s", inf[i].ID) != EOF)
	{
		fscanf(orderInformation, "%s %s %s %s %s %f %s"
			, inf[i].time, inf[i].courtID, inf[i].date, inf[i].start, inf[i].end
			, &inf[i].cost, inf[i].status);
		for (n = 0; n < m; n++)
		{
			if (strcmp(inf[i].courtID, courtID[n]) == 0) //比较订单中场馆ID和管理员管理场馆ID
			{
				number[n]++; //记录预定次数
			}
		}
		i++;
	}
	//读取文件信息，将信息存储在结构体数组中
	fclose(orderInformation);
	courtnumber infr[100];

	for (a = 0; a < m; a++)
	{
		strcpy(infr[a].courtID, courtID[a]);
		infr[a].number = number[a];
	}
	//赋值
	qsort(infr, m, sizeof(struct courtnumber), CompareContent); //排序预定次数

	for (count = 0; count < m; count++)
	{
		printf("场地ID:%s\t", infr[count].courtID);
		printf("预定次数:%d\n", infr[count].number);
	}
	//打印相关信息
	return 0;
}
int businessvolume_sort(char stadium) //按营业额对本场馆的所有场地排序
{
	int i = 0, j = 0, k = 0, m = 0, n = 0, h, a, count;
	float number[100];
	order inf[100];
	court inf2[100];
	admin inf3[100];
	char stemp[20];
	char stadiumtemp[100];
	sprintf(stadiumtemp, "%c", stadium);
	char courtID[100][100];
	//变量定义
	FILE *orderInformation;
	orderInformation = fopen("order.txt", "r");
	FILE *courtInformation;
	courtInformation = fopen("court.txt", "r");
	FILE *adminInformation;
	adminInformation = fopen("admin.txt", "r");
	//打开文件
	rewind(courtInformation); //使文件指针的位置指针指向文件开始
	while (fscanf(courtInformation, "%s", inf2[j].ID) != EOF)
	{
		fscanf(courtInformation, "%s %s %s %s %s %f %s"
			, inf2[j].stadium, inf2[j].district, inf2[j].sport, inf2[j].lowage
			, inf2[j].highage, &inf2[j].fee, inf2[j].intro);
		if (strcmp(inf2[j].stadium, stadiumtemp) == 0) //比较当前管理员所属场馆和文件中场馆信息
		{
			strcpy(courtID[m], inf2[j].ID);
			m++;
		}
		j++;
	}
	//读取文件信息，将信息存储在结构体数组中
	fclose(courtInformation);

	for (h = 0; h < m; h++)
	{
		number[h] = 0;
	}
	rewind(orderInformation); //使文件指针的位置指针指向文件开始
	while (fscanf(orderInformation, "%s", inf[i].ID) != EOF)
	{
		fscanf(orderInformation, "%s %s %s %s %s %f %s"
			, inf[i].time, inf[i].courtID, inf[i].date, inf[i].start, inf[i].end
			, &inf[i].cost, inf[i].status);
		for (n = 0; n < m; n++)
		{
			if (strcmp(inf[i].courtID, courtID[n]) == 0) //比较订单中场馆ID和管理员管理场馆ID
			{
				number[n] += inf[i].cost; //计算场地营业金额
			}
		}
		i++;
	}
	//读取文件信息，将信息存储在结构体数组中
	fclose(orderInformation);
	courtcost infr[100];

	for (a = 0; a < m; a++)
	{
		strcpy(infr[a].courtID, courtID[a]);
		infr[a].cost = number[a];
	}
	//赋值
	qsort(infr, m, sizeof(struct courtcost), CompareContent2); //排序营业金额

	for (count = 0; count < m; count++)
	{
		printf("场地ID:%s\t", infr[count].courtID);
		printf("营业金额:%.2f\n", infr[count].cost);
	}
	//打印相关信息
	return 0;
}
int attendencemanage(char adminID[100]) //管理员处理订单完成情况
{
	int flag = 0, first = 0, nowtime, nowmin;
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	int year = 1900 + p->tm_year; //系统当前年份
	int mon = 1 + p->tm_mon;	  //系统当前月份
	int day = p->tm_mday;		  //系统当前日期
	int hour = 8 + p->tm_hour;	//系统当前小时
	int min = p->tm_min;		  //系统当前分钟
	//变量定义
	nowtime = year * 10000 + mon * 100 + day;
	nowmin = hour * 100 + min;

	printf("欢迎进入用户预定到场情况填写界面！\n\n");

	int i = 0, j = 0, k = 0, m = 0, n = 0, h = 0, a;
	int count, flag2, date, hou, success = 1, pun, flag3 = 0;
	char *cut, *custr;
	float number[100];
	order inf[100];
	court inf2[100];
	admin inf3[100];
	customer inf4[100];
	char stemp[20];
	char stadium[10];
	char courtID[100][100];
	char temp[100][100];
	char ordernumber[100];
	char ordernum[10];
	char punID[100];
	//变量定义
	FILE *orderInformation;
	orderInformation = fopen("order.txt", "r");
	FILE *courtInformation;
	courtInformation = fopen("court.txt", "r");
	FILE *adminInformation;
	adminInformation = fopen("admin.txt", "r");
	FILE *customerInformation;
	customerInformation = fopen("customer.txt", "r");
	//打开文件
	rewind(adminInformation); //使文件指针的位置指针指向文件开始
	while (fscanf(adminInformation, "%s", inf3[k].ID) != EOF)
	{
		fscanf(adminInformation, "%s %s %s %s %s %s"
			, inf3[k].name, inf3[k].gender, inf3[k].phone, inf3[k].password
			, inf3[k].email, inf3[k].stadium);
		if (strcmp(inf3[k].ID, adminID) == 0) //比较当前管理员ID和管理员信息中ID
		{
			strcpy(stadium, inf3[k].stadium);
		}
		k++;
	}
	//读取文件信息将信息存储在结构体数组中
	fclose(adminInformation);
	rewind(courtInformation); //使文件指针的位置指针指向文件开始
	while (fscanf(courtInformation, "%s", inf2[j].ID) != EOF)
	{
		fscanf(courtInformation, "%s %s %s %s %s %f %s"
			, inf2[j].stadium, inf2[j].district, inf2[j].sport, inf2[j].lowage
			, inf2[j].highage, &inf2[j].fee, inf2[j].intro);
		if (strcmp(inf2[j].stadium, stadium) == 0) //比较当前管理员所属场馆和场地员信息中场馆
		{
			strcpy(courtID[m], inf2[j].ID);
			m++;
		}
		j++;
	}
	//读取文件信息将信息存储在结构体数组中
	fclose(courtInformation);
	rewind(orderInformation); //使文件指针的位置指针指向文件开始
	while (fscanf(orderInformation, "%s", inf[i].ID) != EOF)
	{
		fscanf(orderInformation, "%s %s %s %s %s %f %s"
			, inf[i].time, inf[i].courtID, inf[i].date, inf[i].start
			, inf[i].end, &inf[i].cost, inf[i].status);
		for (n = 0; n < m; n++)
		{
			flag2 = 0;

			if (strcmp(inf[i].courtID, courtID[n]) == 0) //判断管理员分管场地ID和订单中场地ID
			{
				date = atoi(inf[i].date); //将字符串转化为整形数字
				hou = atoi(inf[i].start); //将字符串转化为整形数字
				hou = hou * 100;

				if (date <= nowtime) //判断系统当前时间和预定开始时间相距24小时
				{
					flag2 = 1;
					if (date == nowtime && nowmin < hou)
						flag2 = 0;
				}

				if (flag2 == 1)
				{
					printf("订单编号：%-30s订单开始日期：%s\t订单开始时间：%s\t订单结束时间：%s\t是否按时到场：%s\n",
						   inf[i].ID, inf[i].date, inf[i].start, inf[i].end, inf[i].status);
					strcpy(temp[h], inf[i].ID);
					h++;
					flag3 = 1;
				}
				//打印相关信息
			}
		}
		i++;
	}

	fclose(orderInformation);
	if (flag3 == 1) //判断是否有可处理订单
	{
		printf("您现在有以上订单需要处理:\n");
		while (success)
		{
			printf("请输入您要操作的订单编号：");
			scanf("%s", ordernumber); //输入订单编号
			for (a = 0; a < h; a++)
			{
				if (strcmp(temp[a], ordernumber) == 0)
				{
					success = 0;
				}
			}

			if (success == 1) //判断输入信息是否规范
				printf("订单编号错误，请重新输入\n");
		}

		i = 0;
		while (flag == 0)
		{
			printf("请选择您要修改成的选项：\n\t1.已完成\n\t2.未完成\n\t3.退出\n");

			scanf("%s", ordernum);

			if (strcmp(ordernum, "1") != 0 && strcmp(ordernum, "2") != 0 && strcmp(ordernum, "3") != 0) //判断输入选项是否符合规范
				printf("请输入正确的修改序号\n");
			else
			{
				if (strcmp(ordernum, "1") == 0)
				{

					orderInformation = fopen("order.txt", "r");
					rewind(orderInformation); //使文件指针的位置指针指向文件开始
					while (fscanf(orderInformation, "%s", inf[i].ID) != EOF)
					{
						fscanf(orderInformation, "%s %s %s %s %s %f %s"
							, inf[i].time, inf[i].courtID, inf[i].date, inf[i].start
							, inf[i].end, &inf[i].cost, inf[i].status);
						if (strcmp(inf[i].ID, ordernumber) == 0) //比较订单编号和文件中订单编号
						{
							printf("修改成功!\n");
							strcpy(inf[i].status, "已完成");
						}
						i++;
					}
					//读取文件
					fclose(orderInformation);
					orderInformation = fopen("order.txt", "w"); //打开文件
					for (k = 0; k < i; k++)
					{
						fprintf(orderInformation, "%s %s %s %s %s %s %.2f %s\n"
							,inf[k].ID, inf[k].time, inf[k].courtID, inf[k].date, inf[k].start
							, inf[k].end, inf[k].cost, inf[k].status);
					}
					//将修改信息写入订单信息文件
					fclose(orderInformation);
				}

				if (strcmp(ordernum, "2") == 0)
				{
					orderInformation = fopen("order.txt", "r");
					rewind(orderInformation); //使文件指针的位置指针指向文件开始
					while (fscanf(orderInformation, "%s", inf[i].ID) != EOF)
					{
						fscanf(orderInformation, "%s %s %s %s %s %f %s"
							, inf[i].time, inf[i].courtID, inf[i].date, inf[i].start
							, inf[i].end, &inf[i].cost, inf[i].status);
						if (strcmp(inf[i].ID, ordernumber) == 0) //比较订单编号和订单信息中订单编号
						{

							printf("修改成功!\n");
							strcpy(inf[i].status, "未完成");
							char IDtemp[100];
							strcpy(IDtemp, inf[i].ID);
							custr = IDtemp;
							cut = IDtemp;
							while (*cut != ':')
							{
								cut++;
							}
							*(cut - 4) = '\0'; //剪切出顾客ID
							strcpy(punID, IDtemp);
							count = i;
						}
						i++;
					}
					fclose(orderInformation);
					orderInformation = fopen("order.txt", "w");
					for (k = 0; k < i; k++)
					{
						fprintf(orderInformation, "%s %s %s %s %s %s %.2f %s\n"
							, inf[k].ID, inf[k].time, inf[k].courtID, inf[k].date
							, inf[k].start, inf[k].end, inf[k].cost, inf[k].status);
					}
					//打印相关信息
					fclose(orderInformation);
					i = 0;
					rewind(customerInformation); //使文件指针的位置指针指向文件开始
					while (fscanf(customerInformation, "%s", inf4[i].ID) != EOF)
					{
						fscanf(customerInformation, "%s %s %s %s %s %s %s %f %s"
							, inf4[i].name, inf4[i].gender, inf4[i].age, inf4[i].phone
							, inf4[i].password, inf4[i].email, inf4[i].district
							, &inf4[i].balance, inf4[i].punish);
						if (strcmp(punID, inf4[i].ID) == 0) //比较顾客ID和订单信息中ID
						{
							printf("该订单违约顾客违约次数加1!\n");
							pun = atoi(inf4[i].punish) + 1;		//违约次数加一
							sprintf(inf4[i].punish, "%d", pun); //将整型数转化为字符串
						}
						i++;
					}
					//读取顾客信息文件
					fclose(customerInformation);
					customerInformation = fopen("customer.txt", "w");
					for (k = 0; k < i; k++)
					{
						fprintf(customerInformation, "%s %s %s %s %s %s %s %s %.2f %s\n"
							,inf4[k].ID, inf4[k].name, inf4[k].gender, inf4[k].age, inf4[k].phone, inf4[k].password
							,inf4[k].email, inf4[k].district, inf4[k].balance, inf4[k].punish);
					}
					//打印相关信息
					fclose(customerInformation);
				}
				if (strcmp(ordernum, "3") == 0)
				{
					break; //跳出循环
				}
				flag = 1;
			}
			fflush(stdin);
		}
	}
	else
	{
		printf("您没有订单需要处理\n");
	}
	return 0;
}
int recharge() //充值
{
	FILE *customerinfo = fopen("customer.txt", "r"); //打开顾客文件
	if (!customerinfo)
	{
		cout << "File open error!" << endl;
	}
	customer target[100];
	int count1 = 0, count2 = 0, temp = 1, temp1 = 1, temp2 = 1;
	float money = 0;
	char str[100], expense[100], *ptr;
	char stemp[20];
	ptr = expense;
	rewind(customerinfo);
	while (fscanf(customerinfo, "%s", target[count1].ID) != EOF) //导入顾客信息
	{
		fscanf(customerinfo, "%s %s %s %s %s %s %s %f %s"
			, target[count1].name, target[count1].gender, target[count1].age
			, target[count1].phone, target[count1].password, target[count1].email
			, target[count1].district, &target[count1].balance, target[count1].punish);
		count1++;
	}
	while (temp != 0) //输入要充值的顾客ID
	{
		temp = 1;
		count2 = 0;
		printf("请输入您的ID\n");
		scanf("%s", str);
		for (count2 = 0; count2 < count1 && temp != 0; count2++)
		{
			temp = strcmp(str, target[count2].ID);
		}
		count2--;
		if (temp != 0)
			printf("ID不存在，请重新输入\n");
	}
	while (temp1 == 1 && temp2 == 1) //输入充值金额
	{
		printf("请输入充值的金额\n");
		scanf("%s", expense);
		temp2 = 0;
		ptr = expense;
		while (*ptr != '\0') //判断顾客充值金额是否正确
		{
			if (!isdigit(*ptr))
				temp2 = 1;
			ptr++;
		}
		if (temp2 == 1)
			printf("充值金额格式错误\n");
		else
		{
			money = atof(expense);
			if (money >= 0) //判断顾客充值金额是否正确
			{
				temp1 = 0;
				target[count2].balance = target[count2].balance + money;
			}
			else
				printf("充值金额不能为负!\n");
		}
	}
	printf("充值成功\n");
	printf("余额为%.2f元\n", target[count2].balance);
	rewind(customerinfo);
	fclose(customerinfo);
	customerinfo = fopen("customer.txt", "w");
	rewind(customerinfo);
	for (count2 = 0; count2 < count1; count2++) //写入充值后的顾客信息
	{
		fprintf(customerinfo, "%s %s %s %s %s %s %s %s %.2f %s\n"
			, target[count2].ID, target[count2].name, target[count2].gender, target[count2].age
			, target[count2].phone, target[count2].password, target[count2].email
			, target[count2].district, target[count2].balance, target[count2].punish);
	}
	fclose(customerinfo);
	return 0;
}
int modification(char IDt[100]) //顾客修改个人信息
{
	char option2[100];
	option2[0] = '1';
	while (option2[0] == '1')
	{
		int p = 0, i, flag = 0, flag1 = 1, k, j = 0, first2 = 1, temp, flag4 = 0;
		char option[100];
		char ch1[100], ch2[100], ch3[100], password[100];
		customer inf[100];
		//变量定义
		FILE *customerInformation;
		customerInformation = fopen("customer.txt", "r");
		//打开文件
		rewind(customerInformation); //使文件指针的位置指针指向文件开始
		while (fscanf(customerInformation, "%s", inf[p].ID) != EOF)
		{
			fscanf(customerInformation, "%s %s %s %s %s %s %s %f %s"
				, inf[p].name, inf[p].gender, inf[p].age, inf[p].phone, inf[p].password
				, inf[p].email, inf[p].district, &inf[p].balance, inf[p].punish);
			if (strcmp(inf[p].ID, IDt) == 0)
				k = p;
			p++;
		}
		//读取顾客信息，将信息存储在结构体数组中
		fclose(customerInformation);
		while (flag1 == 1)
		{
			printf("请输入您需修改的信息选项：\n\t1.密码\n\t2.手机号\n\t3.邮箱\n\t4.地址\n\t5.姓名\n\t6.年龄\n\t7.性别\n");

			scanf("%s", option);

			if (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0 &&
				strcmp(option, "4") != 0 && strcmp(option, "5") != 0 && strcmp(option, "6") != 0 && strcmp(option, "7") != 0) //判断选项信息
				printf("请输入正确选项");
			else
			{
				flag1 = 0;

				if (strcmp(option, "1") == 0)
				{
					int success = 1;
					while (success)
					{
						int temp = 1;
						while (temp)
						{
							printf("请创建您的密码(6-10位)\n");
							scanf("%s", password);
							if (strlen(password) < 6 || strlen(password) > 10) //判断密码长度
							{
								printf("您的密码长度不符\n");
							}
							else
							{
								printf("请再次输入您的密码\n");
								scanf("%s", inf[k].password);
								temp = 0;
							}
						}
						if (strcmp(inf[k].password, password) != 0 || 0) //判断两次密码输入是否相同
							printf("两次输入密码不同，请重新创建密码\n");
						else
							success = 0;
					} //读取新密码并储存
				}
				if (strcmp(option, "2") == 0)
				{
					int success = 1;
					while (success)
					{
						success = 0;
						int flag1(0), flag2(1), b;
						printf("请输入您的手机号码（11位）\n");
						scanf("%s", ch1);
						if (strlen(ch1) == 11) //判断手机号长度
							flag1 = 1;
						for (b = 0; b < 11; b++)
						{
							if (isdigit(ch1[b]) == 0)
								flag2 = 0;
						}
						//判断手机号是否全部为数字
						if (flag1 != 1 && flag2 != 1)
						{
							printf("您输入的号码有误，请确认后再次输入\n");
							success = 1;
						}
						else
						{
							strcpy(inf[k].phone, ch1);
							printf("您的手机号已修改成功！\n");
						}
					}
				}
				if (strcmp(option, "3") == 0)
				{
					int success = 1;
					while (success)
					{
						printf("请输入您的邮箱：\n");
						scanf("%s", ch1);
						int a = 0, b = 0, c = 0, e = 0, f = 0, g = 0;
						while (ch1[a] != '\0')
						{
							if (ch1[a] == '@')
							{
								b = 1;
								c = a; //读取'@'字符所在的位置
								break; //检验输入的邮箱里是否有'@'
							}
							else
								a++;
						}
						while (ch1[e] != '\0')
						{
							if (ch1[e] == '.')
							{
								f = 1;
								g = e; //读取'.'字符所在的位置
								break; //检验输入的邮箱里是否有'.'
							}
							else
								e++;
						}
						if (c != 0 && b == 1 && f == 1 && g > (c + 1))
						{
							strcpy(inf[k].email, ch1);
							printf("您的邮箱已修改成功！\n");
							success = 0; //测试其是否有'@''.'位置
						}
						else
						{
							printf("您输入的邮箱有误！\n");
						}
					}
				}
				if (strcmp(option, "4") == 0)
				{
					char adressnumber[100];
					int success = 1;
					getchar();
					printf("请选择您的所在地区:\n");
					printf("\t1.A\n");
					printf("\t2.B\n");
					printf("\t3.C\n");
					cin >> adressnumber;
					while (adressnumber[0] < '1' || adressnumber[0] > '3' || strlen(adressnumber) > 1)
					{
						printf("请输入正确地区序号：\n");
						cin >> adressnumber;
					}
					//循环直至输入正确地区序号
					if (adressnumber[0] == '1')
						strcpy(inf[k].district, "A");
					if (adressnumber[0] == '2')
						strcpy(inf[k].district, "B");
					if (adressnumber[0] == '3')
						strcpy(inf[k].district, "C");
				}
				if (strcmp(option, "5") == 0)
				{
					printf("请您输入您的姓名：\n");
					scanf("%s", ch1);
					strcpy(inf[k].name, ch1);
					printf("您的姓名已修改成功！\n");
				}
				if (strcmp(option, "6") == 0)
				{
					printf("请输入您的年龄：\n");
					scanf("%s", ch1);
					int flag6 = 1;
					for (int b = 0; b < ch1[b]; b++)
					{
						if (isdigit(ch1[b]) == 0)
							flag6 = 0;
					}
					//判断年龄是否全为数字
					while (flag6 != 1 || strlen(ch1) > 2)
					{
						printf("不合理年龄！\n");
						scanf("%s", ch1);
						flag6 = 1;
						for (int b = 0; b < ch1[b]; b++)
						{
							if (isdigit(ch1[b]) == 0)
								flag6 = 0;
						}
					}
					strcpy(inf[k].age, ch1);
					printf("您的年龄已修改成功！\n");
				}
				if (strcmp(option, "7") == 0)
				{
					char gendernumber[100];
					getchar();
					printf("请输入您的性别\n");
					printf("\t1.男\n");
					printf("\t2.女\n");
					printf("\t3.保密\n");
					cin >> gendernumber;
					while (gendernumber[0] < '1' || gendernumber[0] > '3' || strlen(gendernumber) > 1)
					{
						printf("请输入正确的性别序号\n");
						cin >> gendernumber;
					}
					//循环直至输入正确序号
					if (gendernumber[0] == '1')
						strcpy(inf[k].gender, "男");
					if (gendernumber[0] == '2')
						strcpy(inf[k].gender, "女");
					if (gendernumber[0] == '3')
						strcpy(inf[k].gender, "保密");
					cout << "您的性别已修改成功！" << endl;
				}
			}
		}
		fflush(stdin);
		customerInformation = fopen("customer.txt", "w");
		for (i = 0; i < p; i++)
		{
			fprintf(customerInformation, "%s %s %s %s %s %s %s %s %.2f %s\n"
				, inf[i].ID, inf[i].name, inf[i].gender, inf[i].age, inf[i].phone
				, inf[i].password, inf[i].email, inf[i].district, inf[i].balance, inf[i].punish);
		} //将修改后的信息和之前的信息录入
		fclose(customerInformation);
		printf("请输入您要进行的选项：\n\t1.继续修改信息\n\t2.返回上一级\n");
		cin >> option2;
		while (option2[0] < '1' || option2[0] > '2')
		{
			printf("请输入正确选项\n");
			cin >> option2;
		}
		//循环直至输入正确选项
	}
	return 0;
}
int querycustomer(char ID[100]) //顾客查询个人信息
{
	customer inf[100];
	char ch1[100];
	char option[100];
	int success = 1, first = 1, i = 0, flag = 1;
	//变量定义
	while (flag)
	{
		FILE *customerInformation = NULL;
		customerInformation = fopen("customer.txt", "r");
		//打开文件
		if (customerInformation == NULL)
		{
			printf("open file failed!\n");
			return -1;
		}							 //判断文件是否打开成功
		rewind(customerInformation); //使文件指针的位置指针指向文件开始
		while (fscanf(customerInformation, "%s", inf[i].ID) != EOF)
		{
			fscanf(customerInformation, "%s %s %s %s %s %s %s %f %s"
				, inf[i].name, inf[i].gender, inf[i].age, inf[i].phone, inf[i].password
				, inf[i].email, inf[i].district, &inf[i].balance, inf[i].punish);
			if (strcmp(inf[i].ID, ID) == 0)
			{
				printf("\n您的个人信息为：\n\tID: %s\n\t姓名：%s\n\t性别：%s\n\t年龄：%s\n\t手机号：%s\n\t邮箱：%s\n\t地址：%s\n\t账户余额：%.2f\n\t违约次数：%s\n"
					, inf[i].ID, inf[i].name, inf[i].gender, inf[i].age, inf[i].phone, inf[i].email, inf[i].district, inf[i].balance, inf[i].punish);
			}
			i++;
		} //提取个人信息
		fclose(customerInformation);
		while (success)
		{
			printf("请输入您要进行的选项：\n\t1.修改信息\n\t2.返回上一级\n");
			scanf("%s", option);
			if (strcmp(option, "1") != 0 && strcmp(option, "2") != 0) //判断输入选项是否正确
				printf("请输入正确选项\n");
			else
			{
				if (strcmp(option, "1") == 0)
				{
					modification(ID); //修改个人信息
					flag = 0;
					break;
				}
				if (strcmp(option, "2") == 0)
				{
					flag = 0;
					break;
				}
			}
		}
	}
	return 0;
}
int queryorder(char ID[100]) //顾客查询订单信息
{
	int i = 0, flag = 0;
	order inf[100];
	char stemp[20];
	char IDtemp[100];
	//变量定义
	strcpy(IDtemp, ID);
	FILE *orderInformation;
	orderInformation = fopen("order.txt", "r"); //打开文件
	rewind(orderInformation);					//使文件指针的位置指针指向文件开始
	while (fscanf(orderInformation, "%s", inf[i].ID) != EOF)
	{
		strcpy(ID, IDtemp);
		fscanf(orderInformation, "%s %s %s %s %s %f %s"
			, inf[i].time, inf[i].courtID, inf[i].date, inf[i].start, inf[i].end
			, &inf[i].cost, inf[i].status);
		strcat(ID, inf[i].time);
		if (strcmp(inf[i].ID, ID) == 0) //判断是否为当前用户订单
		{

			printf("\n您的订单信息为：\n\t订单编号: %s\n\t预定时间：%s\n\t预定场地编号：%s\n\t租借场地日期：%s\n\t租借场地开始时间：%s\n\t租借场地结束时间：%s\n\t是否按时到场：%s\n\t订单金额：%.2f\n"
				,inf[i].ID, inf[i].time, inf[i].courtID, inf[i].date, inf[i].start, inf[i].end, inf[i].status, inf[i].cost);
			//打印相应信息
			flag = 1;
		}
		i++;
	}
	if (flag == 0) //判断是否有订单信息
		printf("未找到订单信息\n");
	fclose(orderInformation);
	fflush(stdin);
	return 0;
}
int cancellation(char ID[100]) //顾客取消订单
{
	order inf[100];
	customer inf2[100];
	char ordernumber[100], line[500], idtemp[100];
	int i, j, k, flag = 0, flag2 = 0, flag3 = 0, option, date, nowtime, nowmin, hou, first = 1;
	//变量定义
	FILE *fp_in = NULL, *fp_out = NULL;

	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	char *cut, *custr;
	float money;
	int year = 1900 + p->tm_year;
	int mon = 1 + p->tm_mon;
	int day = p->tm_mday;
	int hour = 8 + p->tm_hour;
	int min = p->tm_min;
	//提取当前系统时间
	nowtime = year * 10000 + mon * 100 + day;
	nowmin = hour * 100 + min;
	printf("请输入您想要取消的订单编号：");
	scanf("%s", ordernumber); //输入订单编号
	strcpy(idtemp, ordernumber);
	fp_in = fopen("order.txt", "r"); //打开文件
	if (fp_in == NULL)				 //判断文件是否打开成功
	{
		printf("open file failed!\n");
		return -1;
	}
	fp_out = fopen("order_temp.txt", "a+");
	if (fp_out == NULL) //判断临时文件是否创建成功
	{
		printf("create tmp file failed!\n");
		return -1;
	}

	rewind(fp_in); //使文件指针的位置指针指向文件开始
	while (fscanf(fp_in, "%s", inf[i].ID) != EOF)
	{
		fscanf(fp_in, "%s %s %s %s %s %f %s"
			, inf[i].time, inf[i].courtID, inf[i].date, inf[i].start, inf[i].end
			, &inf[i].cost, inf[i].status);
		if (strcmp(inf[i].ID, ordernumber) == 0) //判断输入订单编号和订单信息中订单编号是否一致
		{
			flag = 1, j = i;
			date = atoi(inf[i].date);
			hou = atoi(inf[i].end);
			//将字符串转换为整型数字
			hou = hou * 100;
			custr = idtemp;
			cut = idtemp;
			while (*cut != ':')
			{
				cut++;
			}
			*(cut - 4) = '\0';
			//剪切出ID
			money = inf[i].cost;
			if (date > nowtime)
			{
				flag2 = 1;
				if (date == nowtime + 1 && nowmin >= hou)
					flag2 = 0;
			}
			else
			{
				printf("距离订单开始时间不足24小时，不能取消订单!\n");
			}
			//判断订单能否取消
		}
		i++;
	}

	if (fclose(fp_in) != 0)
	{
		printf("close file failed!\n");
		return -2;
	}
	if (fclose(fp_out) != 0)
	{
		printf("close file failed!\n");
		return -2;
	}
	//判断文件是否关闭成功
	if (flag == 0) //判断是否找到预订信息
		printf("未找到相应预订信息\n");
	if (flag == 1 && flag2 == 1) //判断是否可取消预定
	{
		printf("您已成功取消订单，且退款成功\n");
		flag3 = 1;
		fp_out = fopen("order_temp.txt", "w");
		for (k = 0; k < j; k++)
		{
			fprintf(fp_out, "%s %s %s %s %s %s %.2f %s\n"
				,inf[k].ID, inf[k].time, inf[k].courtID, inf[k].date, inf[k].start
				, inf[k].end, inf[k].cost, inf[k].status);
		}
		for (k = j + 1; k < i; k++)
		{
			fprintf(fp_out, "%s %s %s %s %s %s %.2f %s\n"
				,inf[k].ID, inf[k].time, inf[k].courtID, inf[k].date, inf[k].start
				, inf[k].end, inf[k].cost, inf[k].status);
		} //订单重新写入
		if (fclose(fp_out) != 0)
		{
			printf("close file failed!\n");
			return -2;
		}
		remove("order.txt");				   //移除原本订单信息文件
		rename("order_temp.txt", "order.txt"); //重命名文件
	}
	if (flag3 == 1) //判断订单是否取消成功
	{
		FILE *customerInformation = NULL;
		customerInformation = fopen("customer.txt", "r");
		i = 0;
		if (customerInformation == NULL)
		{
			printf("open file failed!\n");
			return -1;
		}							 //判断文件是否打开成功
		rewind(customerInformation); //使文件指针的位置指针指向文件开始
		while (fscanf(customerInformation, "%s", inf2[i].ID) != EOF)
		{
			fscanf(customerInformation, "%s %s %s %s %s %s %s %f %s"
				, inf2[i].name, inf2[i].gender, inf2[i].age, inf2[i].phone
				, inf2[i].password, inf2[i].email, inf2[i].district, &inf2[i].balance
				, inf2[i].punish);

			if (strcmp(inf2[i].ID, idtemp) == 0) //比较顾客信息中顾客ID和当前顾客ID
			{
				inf2[i].balance = inf2[i].balance + money; //退回预定费用到顾客余额
			}
			i++;
		} //提取顾客个人信息
		fclose(customerInformation);

		customerInformation = fopen("customer.txt", "w");
		rewind(customerInformation);
		for (j = 0; j < i; j++)
		{
			fprintf(customerInformation, "%s %s %s %s %s %s %s %s %.2f %s\n"
				, inf2[j].ID, inf2[j].name, inf2[j].gender, inf2[j].age, inf2[j].phone
				, inf2[j].password, inf2[j].email, inf2[j].district, inf2[j].balance
				, inf2[j].punish);
		} //将修改后的信息和之前的信息录入
		fclose(customerInformation);
	}

	return 0;
}
int createcourt() //场地注册
{
	FILE *courtinfo = fopen("court.txt", "a+");
	char courtID1[100];
	char temp;
	char district;
	char stadium[10];
	char sport[100];
	char lowage[20];
	char highage[20];
	char fee[20];
	float nfee;
	char intro[100];
	int success = 1;
	char ch1[100][100];
	char ch2[100][100];
	int a, b, c, i, j = 0, k = 0, flag1 = 0, flag2 = 0, flag3 = 0;
	while (success) //输入ID
	{
		a = 0;
		b = 0;
		c = 0;
		printf("请输入场地的ID，字母与数字混合，6-10位\n");
		scanf("%s", courtID1);
		if (strlen(courtID1) < 6 || strlen(courtID1) > 10) //检查账号的长度
		{
			printf("您输入的ID不符合要求，请重新创建！\n");
			a = 1;
		}
		for (i = 0; i < strlen(courtID1); i++) //检查账号是否都有数字和字母组成
		{
			if (isalpha(courtID1[i]) == 0 && isdigit(courtID1[i]) == 0)
			{
				printf("您输入的ID不符合要求，请重新创建\n");
				c = 1;
				break;
			}
		}
		if (a == 0 && b == 0 && c == 0)
			success = 0;
		else
			success = 1;
	}
	printf("请输入场地所属场馆\n"); //输入场馆序号
	scanf("%s", stadium);
	while ((stadium[0] != 'A' && stadium[0] != 'B' && stadium[0] != 'C') || strlen(stadium) > 1)
	{
		printf("不存在该场馆，请重新输入\n");
		scanf("%s", stadium);
	}
	if (stadium[0] == 'A')
		district = 'A';
	if (stadium[0] == 'B')
		district = 'B';
	if (stadium[0] == 'B')
		district = 'B';
	printf("请输入该场地的运动类型\n"); //输入场地运动类型
	scanf("%s", sport);
	while (flag1 == 0)
	{
		printf("请输入该场地适宜的最低年龄\n");
		scanf("%s", ch1[k]);
		int b;
		if (strlen(ch1[k]) < 3)
			flag3 = 1;
		for (b = 0; b < 20; b++)
		{
			if (isdigit(ch1[k][b]) != 0)
				flag2 = 1;
		}
		if (flag2 != 1 || flag3 != 1)
			printf("不合理的年龄\n");
		else
		{
			strcpy(lowage, ch1[k]);
			flag1 = 1;
		}
		k++;
	}
	flag1 = 0;
	flag2 = 0;
	flag3 = 0;
	while (flag1 == 0)
	{
		printf("请输入该场地适宜的最高年龄\n");
		scanf("%s", ch2[j]);
		int b;
		if (strlen(ch2[j]) < 3)
			flag3 = 1;
		for (b = 0; b < 20; b++)
		{
			if (isdigit(ch2[j][b]) != 0)
				flag2 = 1;
		}
		if (flag2 != 1 || flag3 != 1)
			printf("不合理的年龄\n");
		else
		{
			strcpy(highage, ch2[j]);
			flag1 = 1;
		}
		j++;
	}
	printf("请输入该场地每小时定价\n");
	scanf("%s", fee);
	nfee = atof(fee);
	while (nfee <= 0)
	{
		printf("格式错误，请重新输入\n");
		scanf("%s", fee);
		nfee = atof(fee);
	}
	printf("请输入对该场地的简要介绍\n");
	scanf("%s", intro);
	fprintf(courtinfo, "%s %c %c %s %s %s %.2f %s\n"
		, courtID1, stadium[0], district, sport, lowage, highage, nfee, intro);
	fclose(courtinfo);
	cout << "场地添加成功！" << endl;
	return 0;
}
int encountage() //按年龄层次分析
{
	int counta = 0, countb = 0, countc = 0, counting1 = 0, counting2 = 0;
	int counting3 = 0, countings = 0; 
	//counta--场地，countb--订单，countc--顾客,counting1--总循环1,counting2--总循环2,counting3--总循环3,countings--打印用循环
	int subcounta = 0;										//subcounta--订单提取顾客ID
	int cage[100][4], incount, ages;						//创建年龄数组以及初始化
	for (incount = 0; incount < 100; incount++)				//年龄数组初始化
		memset(cage[incount], 0, sizeof cage[incount]);
	char *custr, *cut;	//custr--提取顾客ID, cut--切割顾客ID
	court takecourt[100]; //拆分场地文件
	char courtinfo[20][100];
	FILE *getcourtinf = fopen("court.txt", "r"); //打开场地文件
	rewind(getcourtinf);
	while (fgets(courtinfo[counta], 1000, getcourtinf) != NULL)
	{
		sscanf(courtinfo[counta], "%s %s %s %s %s %s %f %s"
			, takecourt[counta].ID, takecourt[counta].district, takecourt[counta].stadium
			, takecourt[counta].sport, takecourt[counta].lowage, takecourt[counta].highage
			, &takecourt[counta].fee, takecourt[counta].intro);
		counta++;
	}
	fclose(getcourtinf);  //关闭场地文件
	order takeorder[100]; //拆分订单文件
	char orderinfo[20][100];
	FILE *getorderinf = fopen("order.txt", "r"); //打开订单文件
	rewind(getorderinf);
	while (fgets(orderinfo[countb], 1000, getorderinf) != NULL)
	{
		sscanf(orderinfo[countb], "%s %s %s %s %s %s %f %s"
			, takeorder[countb].ID, takeorder[countb].time, takeorder[countb].courtID
			, takeorder[countb].date, takeorder[countb].start, takeorder[countb].end
			, &takeorder[countb].cost, takeorder[countb].status);
		countb++;
	}
	fclose(getorderinf);		//关闭订单文件
	customer takecustomer[100]; //拆分顾客文件
	char customerinfo[20][100];
	FILE *getcustomerinf = fopen("customer.txt", "r"); //打开顾客文件
	rewind(getcustomerinf);
	while (fgets(customerinfo[countc], 1000, getcustomerinf) != NULL)
	{
		sscanf(customerinfo[countc], "%s""%s""%s""%s""%s""%s""%s""%s""%f""%s"
			,takecustomer[countc].ID,takecustomer[countc].name, takecustomer[countc].gender
			, takecustomer[countc].age, takecustomer[countc].phone,takecustomer[countc].password
			, takecustomer[countc].email, takecustomer[countc].district
			, &takecustomer[countc].balance, takecustomer[countc].punish);
		countc++;
	}
	fclose(getcustomerinf);	//关闭顾客文件
	while (counting1 < counta) //场地信息遍历
	{
		counting2 = 0;			   //循环初始化
		while (counting2 < countb) //订单信息遍历
		{
			if (strcmp(takecourt[counting1].ID, takeorder[counting2].courtID) == 0) 
			//比较场馆ID和订单中的场馆ID
			{
				custr = takeorder[counting2].ID;
				cut = takeorder[counting2].ID;
				while (*cut != ':') //切割顾客ID
					cut++;
				*(cut - 4) = '\0';
				counting3 = 0;			   //循环初始化
				while (counting3 < countc) //顾客信息遍历
				{
					if (strcmp(custr, takecustomer[counting3].ID) == 0) //比较订单中的ID
					{
						ages = atoi(takecustomer[counting3].age);
						if (ages <= 25 && ages > 0) //对用户进行年龄分组
							cage[counting1][0]++;
						if (ages <= 50 && ages > 25)
							cage[counting1][1]++;
						if (ages <= 75 && ages > 50)
							cage[counting1][2]++;
						if (ages <= 100 && ages > 75)
							cage[counting1][3]++;
					}
					counting3++;
				}
			}
			counting2++;
		}
		counting1++;
	}
	printf("场地名称\t1~25岁\t26~50岁\t51~75岁\t76~100岁\n");
	for (countings = 0; countings < counta; countings++)
		printf("%-12s\t%d\t%d\t%d\t%d\n"
			, takecourt[countings].sport, cage[countings][0], cage[countings][1]
			, cage[countings][2], cage[countings][3]);
	return 0;
}
int encountsex() //按性别分析
{
	int counta = 0, countb = 0, countc = 0, counting1 = 0, counting2 = 0, counting3 = 0;
	int countings1 = 0, countings2 = 0; 
	//counta--场地，countb--订单，countc--顾客,counting1--总循环1,counting2--总循环2,counting3--总循环3,countings1--男性用循环,countings2--女性用循环
	int subcounta = 0;																									 //subcounta--订单提取顾客ID
	int csex[100][2], incount = 0, mmax = 0, wmax = 0, mmaxnum = 0, wmaxnum = 0;										 //创建性别数组以及初始化
	char sexs;																											 //顾客性别
	for (incount = 0; incount < 100; incount++)																			 //年龄数组初始化
		memset(csex[incount], 0, sizeof csex[incount]);
	char *custr, *cut;	//custr--提取顾客ID, cut--切割顾客ID
	court takecourt[100]; //拆分场地文件
	char courtinfo[20][100];
	FILE *getcourtinf = fopen("court.txt", "r"); //打开场地文件
	rewind(getcourtinf);
	while (fgets(courtinfo[counta], 1000, getcourtinf) != NULL)
	{
		sscanf(courtinfo[counta], "%s""%s""%s""%s""%s""%s""%f""%s"
			, takecourt[counta].ID, takecourt[counta].district, takecourt[counta].stadium
			, takecourt[counta].sport, takecourt[counta].lowage, takecourt[counta].highage
			, &takecourt[counta].fee, takecourt[counta].intro);
		counta++;
	}
	fclose(getcourtinf);  //关闭场地文件
	order takeorder[100]; //拆分订单文件
	char orderinfo[20][100];
	FILE *getorderinf = fopen("order.txt", "r"); //打开订单文件
	rewind(getorderinf);
	while (fgets(orderinfo[countb], 1000, getorderinf) != NULL)
	{
		sscanf(orderinfo[countb], "%s""%s""%s""%s""%s""%s""%f""%s"
			, takeorder[countb].ID, takeorder[countb].time, takeorder[countb].courtID
			, takeorder[countb].date, takeorder[countb].start, takeorder[countb].end
			, &takeorder[countb].cost, takeorder[countb].status);
		countb++;
	}
	fclose(getorderinf);		//关闭订单文件
	customer takecustomer[100]; //拆分顾客文件
	char customerinfo[20][100];
	FILE *getcustomerinf = fopen("customer.txt", "r"); //打开顾客文件
	rewind(getcustomerinf);
	while (fgets(customerinfo[countc], 1000, getcustomerinf) != NULL)
	{
		sscanf(customerinfo[countc], "%s""%s""%s""%s""%s""%s""%s""%s""%f""%s"
			, takecustomer[countc].ID,takecustomer[countc].name, takecustomer[countc].gender
			, takecustomer[countc].age, takecustomer[countc].phone
			, takecustomer[countc].password, takecustomer[countc].email
			, takecustomer[countc].district, &takecustomer[countc].balance
			, takecustomer[countc].punish);
		countc++;
	}
	fclose(getcustomerinf);	//关闭顾客文件
	while (counting1 < counta) //场地信息遍历
	{
		counting2 = 0;			   //循环初始化
		while (counting2 < countb) //订单信息遍历
		{
			if (strcmp(takecourt[counting1].ID, takeorder[counting2].courtID) == 0) 
			//比较场馆ID和订单中的场馆ID
			{
				subcounta = 0;
				custr = takeorder[counting2].ID;
				cut = takeorder[counting2].ID;
				while (*cut != ':') //切割顾客ID
					cut++;
				*(cut - 4) = '\0';
				counting3 = 0;			   //循环初始化
				while (counting3 < countc) //顾客信息遍历
				{
					if (strcmp(custr, takecustomer[counting3].ID) == 0) //比较订单中的ID
					{
						if (strcmp(takecustomer[counting3].gender, "男")) //对用户进行性别分组
							csex[counting1][0]++;
						if (strcmp(takecustomer[counting3].gender, "女"))
							csex[counting1][1]++;
					}
					counting3++;
				}
			}
			counting2++;
		}
		counting1++;
	}
	mmaxnum = csex[0][0];
	wmaxnum = csex[0][1];
	for (countings1 = 0; countings1 < counta; countings1++)
	{
		if (csex[countings1][0] >= mmaxnum)
		{
			mmax = countings1;
		}
	}
	for (countings2 = 0; countings2 < counta; countings2++)
	{
		if (csex[countings2][1] >= wmaxnum)
		{
			wmax = countings2;
		}
	}
	printf("男性最多的运动：%s\n", takecourt[mmax].sport);
	printf("女性最多的运动：%s\n", takecourt[wmax].sport);
	return 0;
}
int orderstatistic(char stadium) //统计用户预定信息界面
{
	char opera[100];
	char stadiumtemp = stadium;
	//变量定义
	while (1)
	{
		cout << "请输入操作对应序号：" << endl;
		printf("\t1.按预定量对本场馆的所有场地进行排序\n");
		printf("\t2.按营业额对本场馆的所有场地排序\n");
		printf("\t3.统计本场馆总营业额\n");
		printf("\t4.统计不同场地的用户年龄层次分布\n");
		printf("\t5.统计最受男士/女士欢迎的运动\n");
		printf("\t6.按时间段查询不同场地类型利用率\n");
		printf("\t7.返回上一级\n");
		cin >> opera;
		while (opera[0] < '1' || opera[0] > '7' || strlen(opera) > 1)
		{
			cout << "输入错误！请重新输入：" << endl;
			cin >> opera;
		}
		//循环直至输入正确选项
		if (opera[0] == '1')
		{
			stadium = stadiumtemp;
			bookingvolume_sort(stadium); //调用按预定量对本场馆的所有场地进行排序函数
		}
		if (opera[0] == '2')
		{
			stadium = stadiumtemp;
			businessvolume_sort(stadium); //调用按营业额对本场馆的所有场地排序函数
		}
		if (opera[0] == '3')
		{
			stadium = stadiumtemp;
			stadiumvolume(stadium); //调用统计本场馆总营业额函数
		}
		if (opera[0] == '4')
		{
			stadium = stadiumtemp; //调用统计不同场地的用户年龄层次分布函数
			encountage();
		}
		if (opera[0] == '5')
		{
			stadium = stadiumtemp; //调用统计最受男士/女士欢迎的运动分布函数
			encountsex();
		}
		if (opera[0] == '6')
		{
			stadium = stadiumtemp; //调用按时间段查询不同场地类型利用率函数
			sporttypesort();
		}
		if (opera[0] == '7')
		{
			break; //返回上一级
		}
	}
	return 0;
}
int adminsignup() //管理员注册
{
	FILE *admininf = fopen("admin.txt", "a+"); //打开管理员文档
	admin inf;
	admin admininfos[100];
	char password[100];
	char *ptr1, *ptr2, ptr3[100], null, *ptr;
	int flag = 1, temp = 1, flag1 = 0, flag2 = 0, flag3 = 1, flag4 = 0, flag6 = 0;
	int success = 1, first = 0, first2 = 0, h = 0, m = 0, count = 0, flag8 = 1, count1 = 0, count2 = 0;
	char gendernumber[100];
	printf("管理者注册界面\n");
	printf("请创建您的ID（长度为6到10位，字母或数字）\n");
	rewind(admininf);
	while (fscanf(admininf, "%s", admininfos[count1].ID) != EOF) //导入管理员信息
	{
		fscanf(admininf, "%s %s %s %s %s %s"
			, admininfos[count1].name, admininfos[count1].gender, admininfos[count1].phone
			, admininfos[count1].password, admininfos[count1].email, admininfos[count1].stadium);
		count1++;
	}
	do //判断管理员注册ID是否已经存在
	{
		flag = 1;
		flag8 = 0;
		temp = 1;
		scanf("%s", inf.ID);
		ptr1 = inf.ID;
		if (strlen(ptr1) < 6 || strlen(ptr1) > 10)
			flag = 0;
		while (*ptr1 != '\0')
		{
			if (isalnum(*ptr1) == 0)
				temp = 0;
			ptr1++;
		}
		for (count2 = 0; count2 < count1; count2++)
			if (strcmp(inf.ID, admininfos[count2].ID) == 0)
				flag8 = 1;
		if (flag == 0 || temp == 0)
			printf("您输入的ID不符合要求，请重新输入\n");
		if (flag8 == 1)
			printf("该用户ID已存在，请重新输入\n");
	} while (flag == 0 || temp == 0 || flag8 == 1);
	printf("ID创建成功\n");
	printf("请输入您的姓名\n"); //输入管理员姓名
	scanf("%s", inf.name);
	printf("请输入您的性别\n"); //输入管理员性别
	printf("\t1.男\n");
	printf("\t2.女\n");
	printf("\t3.保密\n");
	cin >> gendernumber;
	while (gendernumber[0] < '1' || gendernumber[0] > '3' || strlen(gendernumber) > 1)
	{
		printf("请输入正确的性别序号\n");
		cin >> gendernumber;
	}
	if (gendernumber[0] == '1')
		strcpy(inf.gender, "男");
	if (gendernumber[0] == '2')
		strcpy(inf.gender, "女");
	if (gendernumber[0] == '3')
		strcpy(inf.gender, "保密");

	printf("请输入您的手机号码（11位）\n");
	scanf("%s", inf.phone);
	flag2 = 1;
	for (int b = 0; b < 11; b++)
	{
		if (isdigit(inf.phone[b]) == 0)
			flag2 = 0;
	}
	while (strlen(inf.phone) != 11 || flag2 != 1)
	{
		printf("您输入的号码有误，请确认后再次输入\n");
		scanf("%s", inf.phone);
		flag2 = 1;
		for (int b = 0; b < 11; b++)
		{
			if (isdigit(inf.phone[b]) == 0)
				flag2 = 0;
		}
	}
	printf("输入完成\n");
	char stadiumnumber[100];
	printf("请选择您的所属场馆:\n\t1.A\n\t2.B\n\t3.C\n"); //输入管理员所属场馆
	if (first2 == 0)
		cin >> stadiumnumber;
	while (stadiumnumber[0] < '1' || stadiumnumber[0] > '3' || strlen(stadiumnumber) > 1)
	{
		printf("请输入正确场馆序号\n");
		cin >> stadiumnumber;
	}
	if (stadiumnumber[0] == '1')
		strcpy(inf.stadium, "A");
	if (stadiumnumber[0] == '2')
		strcpy(inf.stadium, "B");
	if (stadiumnumber[0] == '3')
		strcpy(inf.stadium, "C");
	printf("请输入您的邮箱\n"); //输入管理员邮箱
	do
	{
		flag1 = 1;
		flag2 = 1;
		flag6 = 0;
		scanf("%s", inf.email);
		ptr2 = inf.email;
		if (*ptr2 == '@')
			printf("邮箱格式错误，请重新输入\n");
		else
		{
			while (*ptr2 != '\0')
			{
				if (*ptr2 == '@')
				{
					flag1 = 0;
					ptr = inf.email;
					while (ptr != ptr2)
					{

						if (*ptr == '@' || *ptr == '.')
							flag6 = 1;
						ptr++;
					}
				}

				if (*ptr2 == '.')
				{
					flag2 = 0;
				}
				ptr2++;
			}

			if (flag1 == 1 || flag2 == 1 || flag6 == 1)
				printf("邮箱格式错误，请重新输入\n");
		}
		count++;
	} while (flag1 == 1 || flag2 == 1 || flag6 == 1);

	success = 1; //输入管理员密码
	while (success)
	{
		int temp = 1;
		while (temp)
		{
			printf("请创建您的密码(6-10位)\n");
			scanf("%s", password);
			if (strlen(password) < 6 || strlen(password) > 10)
			{
				printf("您的密码长度不符\n");
			}
			else
			{
				printf("请再次输入您的密码\n");
				scanf("%s", inf.password);
				temp = 0;
			}
		}
		if (strcmp(inf.password, password) != 0 || 0)
			printf("两次输入密码不同，请重新创建密码\n");
		else
			success = 0;
	}
	printf("注册成功!\n");
	fprintf(admininf, "%s %s %s %s %s %s %s\n"
		, inf.ID, inf.name, inf.gender, inf.phone, inf.password, inf.email, inf.stadium); 
	//写入管理员注册的信息
	fclose(admininf);
	return 0;
}
char *adminsignin() //管理员登录
{
	char idt[100], pwt[100], rid[100], rpw[100], tra[100];
	FILE *admininf = fopen("admin.txt", "r");
	if (admininf)
	{
		cout << "请输入您的ID(输入“0”以退出）：" << endl;
		cin >> idt;
		rewind(admininf); //文件读取指针初始化
		while (fscanf(admininf, "%s", rid) != EOF && strcmp(idt, rid))
		{
			fscanf(admininf, "%s %s %s %s %s %c", tra, tra, tra, tra, tra, tra);
		}
		//ID检索
		while (strcmp(rid, idt) && strcmp("0", idt))
		{
			cout << "ID不存在，请重新输入(输入“0”以退出）：" << endl;
			cin >> idt;
			rewind(admininf);
			while (fscanf(admininf, "%s", rid) != EOF && strcmp(idt, rid))
			{
				fscanf(admininf, "%s %s %s %s %s %c", tra, tra, tra, tra, tra, tra);
			}
		}
		if (strcmp("0", idt) == 0)
		{
			fclose(admininf);
			return (char *)"0";
		}
		fscanf(admininf, "%s %s %s", tra, tra, tra);
		fscanf(admininf, "%s", rpw);
		cout << "请输入密码(输入“0”以退出）：" << endl;
		cin >> pwt;
		//密码校验
		while (strcmp(pwt, rpw) && strcmp("0", pwt))
		{
			cout << "密码错误，请重新输入(输入“0”以退出）：" << endl;
			cin >> pwt;
		}
		if (strcmp("0", pwt) == 0)
		{
			fclose(admininf);
			return (char *)"0";
		}
		fclose(admininf);
	}
	else
	{
		cout << "File open error!" << endl;
	}
	cout << "登录成功！" << endl;

	return idt;
}
int adminmenu(char id[100]) //管理员菜单
{
	while (1)
	{
		char ope(0);
		cout << "请输入操作对应序号：" << endl;
		cout << "\t1.订单查询" << endl;
		cout << "\t2.订单管理" << endl;
		cout << "\t3.场地管理" << endl;
		cout << "\t4.我的信息" << endl;
		cout << "\t5.注销" << endl;
		cin >> ope;
		while (ope < '1' || ope > '5') //输入检查
		{
			cout << "输入错误！请重新输入：" << endl;
			cin >> ope;
		}
		//读取stadium
		char stadium;
		int count = 0;
		char txtstadium;
		char stemp[100];
		char temp;
		char txtID[100];
		FILE *admininfo = fopen("admin.txt", "r");
		rewind(admininfo); //文件读取指针初始化
		while (fscanf(admininfo, "%s %s %s %s %s %s %c"
			, txtID, stemp, stemp, stemp, stemp, stemp, &txtstadium) != EOF)
		{
			if (strcmp(txtID, id) == 0)
			{
				stadium = txtstadium;
			}
			count++;
		} //获取管理员对应场馆
		while (ope == '1')
		{
			char selection[100];
			cout << "请输入操作对应序号：" << endl;
			cout << "\t1.查看用户预定情况" << endl;
			cout << "\t2.统计用户预定信息" << endl;
			cout << "\t3.返回" << endl;
			cin >> selection;
			while (selection[0] < '1' || selection[0] > '3' || strlen(selection) > 1) //输入检查
			{
				cout << "输入错误！请重新输入：" << endl;
				cin >> selection;
			}
			if (selection[0] == '1')
			{
				adminshoworder(stadium);
			}
			if (selection[0] == '2')
			{
				orderstatistic(stadium);
			}
			if (selection[0] == '3')
			{
				break;
			}
		}
		if (ope == '2')
		{
			attendencemanage(id);
		}
		while (ope == '3')
		{
			char selection[100];
			cout << "请输入操作对应序号：" << endl;
			cout << "\t1.场地查询" << endl;
			cout << "\t2.场地添加" << endl;
			cout << "\t3.返回" << endl;
			cin >> selection;
			while (selection[0] < '1' || selection[0] > '3' || strlen(selection) > 1) //输入检查
			{
				cout << "输入错误！请重新输入：" << endl;
				cin >> selection;
			}
			if (selection[0] == '1')
			{
				adminshowcourt(stadium);
			}
			if (selection[0] == '2')
			{
				createcourt();
			}
			if (selection[0] == '3')
			{
				break;
			}
		}
		if (ope == '4')
		{
			char operation(0);
			cout << "请输入操作对应序号：" << endl;
			cout << "\t1.查看信息" << endl;
			cout << "\t2.修改信息" << endl;
			cout << "\t3.返回" << endl;
			cin >> operation;
			while (operation < '1' || operation > '3') //输入检查
			{
				cout << "输入错误！请重新输入：" << endl;
				cin >> operation;
			}
			if (operation == '1')
			{
				queryadmin(id);
			}
			if (operation == '2')
			{
				adminmodification(id);
			}
			if (operation == '3')
			{
				break;
			}
		}
		if (ope == '5')
		{
			break;
		}
	}
	return 0;
}
int customersignup() //顾客注册
{
	FILE *customerInformation = fopen("customer.txt", "a+"); //打开文件
	char customerID1[100], customerID2[100], line[100];
	char filecustomerPassword[100], password2[100];
	char name[100];
	char phone[20];
	char gender[10];
	char age[10];
	char password[10];
	char email[20];
	char ch1[100];
	float balance;
	char district[100];
	char punish[100];
	int a, b, c, d, i, success, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
	int flag6 = 0, flag7 = 0, first = 0, first2 = 0, flag8 = 1, count1 = 0, count2 = 0;
	char adressnumber[100];
	char gendernumber[100];
	customer customerinfo[100];
	//变量定义
	success = 1;
	while (success)
	{
		a = 0;
		b = 0;
		c = 0;
		rewind(customerInformation); //使文件指针的位置指针指向文件开始
		while (fscanf(customerInformation, "%s", customerinfo[count1].ID) != EOF)
		{
			fscanf(customerInformation, "%s %s %s %s %s %s %s %f %s"
				, customerinfo[count1].name, customerinfo[count1].gender
				, customerinfo[count1].age, customerinfo[count1].phone
				, customerinfo[count1].password, customerinfo[count1].email
				, customerinfo[count1].district, &customerinfo[count1].balance
				, customerinfo[count1].punish);
			count1++;
		}
		//读取文件信息，将顾客信息存储在结构体数组中
		printf("顾客注册界面\n");
		printf("请创建您的ID（长度为6到10位，字母或数字）\n");
		cin >> customerID1;
		while (flag8 == 1)
		{
			flag8 = 0;
			for (count2 = 0; count2 < count1; count2++)
			{
				if (strcmp(customerID1, customerinfo[count2].ID) == 0)
				{
					flag8 = 1;
				}
			}
			if (flag8 == 1)
			{
				printf("该用户ID已存在，请重新输入\n");
				cin >> customerID1;
			}
		}
		//判断输入ID是否和已有ID重复
		if (strlen(customerID1) < 6 || strlen(customerID1) > 10) //检查账号的长度
		{
			printf("您输入的ID不符合要求，请重新输入\n");
			a = 1;
		}
		for (i = 0; i < strlen(customerID1); i++) //检查账号是否都有数字和字母组成
		{
			if (isalpha(customerID1[i]) == 0 && isdigit(customerID1[i]) == 0)
			{
				printf("您输入的ID不符合要求，请重新输入\n");
				c = 1;
				break;
			}
		}
		if (a == 0 && b == 0 && c == 0 && flag8 == 0)
			success = 0;
		else
			success = 1;
	}
	printf("ID创建成功\n");
	printf("请您输入您的姓名\n");
	scanf("%s", name);
	getchar();
	printf("请输入您的性别\n");
	printf("\t1.男\n");
	printf("\t2.女\n");
	printf("\t3.保密\n");
	cin >> gendernumber;
	while (gendernumber[0] < '1' || gendernumber[0] > '3' || strlen(gendernumber) > 1)
	{
		printf("请输入正确的性别序号\n");
		cin >> gendernumber;
	}
	//循环直至输入正确选项
	if (gendernumber[0] == '1')
		strcpy(gender, "男");
	if (gendernumber[0] == '2')
		strcpy(gender, "女");
	if (gendernumber[0] == '3')
		strcpy(gender, "保密");

	printf("请输入您的年龄\n");
	scanf("%s", ch1);
	flag6 = 1;
	for (int b = 0; b < ch1[b]; b++)
	{
		if (isdigit(ch1[b]) == 0)
			flag6 = 0;
	}
	while (flag6 != 1 || strlen(ch1) > 2)
	{
		printf("不合理年龄\n");
		scanf("%s", ch1);
		flag6 = 1;
		for (int b = 0; b < ch1[b]; b++)
		{
			if (isdigit(ch1[b]) == 0)
				flag6 = 0;
		}
	}
	//判断年龄是否均为数字且长度小于3位
	strcpy(age, ch1);

	flag5 = 1;
	printf("请选择您的所在地区:\n");
	printf("\t1.A\n");
	printf("\t2.B\n");
	printf("\t3.C\n");
	cin >> adressnumber;
	while (adressnumber[0] < '1' || adressnumber[0] > '3' || strlen(adressnumber) > 1)
	{
		printf("请输入正确地区序号");
		cin >> adressnumber;
	}
	//循环直至输入正确选项
	if (adressnumber[0] == '1')
		strcpy(district, "A");
	if (adressnumber[0] == '2')
		strcpy(district, "B");
	if (adressnumber[0] == '3')
		strcpy(district, "C");

	printf("请输入您的手机号码（11位）\n");
	scanf("%s", phone);
	flag2 = 1;
	for (int b = 0; b < 11; b++)
	{
		if (isdigit(phone[b]) == 0)
			flag2 = 0;
	}
	//判断手机号是否均为数字
	while (strlen(phone) != 11 || flag2 != 1)
	{
		printf("您输入的号码有误，请确认后再次输入\n");
		scanf("%s", phone);
		flag2 = 1;
		for (int b = 0; b < 11; b++)
		{
			if (isdigit(phone[b]) == 0)
				flag2 = 0;
		}
	}
	//循环直至手机号输入正确
	printf("输入完成\n");

	success = 1;
	while (success)
	{
		int temp = 1;
		while (temp)
		{
			printf("请创建您的密码(6-10位)\n");
			scanf("%s", filecustomerPassword);
			if (strlen(filecustomerPassword) < 6 || strlen(filecustomerPassword) > 10) //判断密码长度是否符合要求
			{
				printf("您的密码长度不符\n");
			}
			else
			{
				printf("请再次输入您的密码\n");
				scanf("%s", password2);
				temp = 0;
			}
		}
		if (strcmp(filecustomerPassword, password2) != 0 || 0) //判断两次密码输入是否一致
			printf("两次输入密码不同，请重新创建密码\n");
		else
			success = 0;
	}
	success = 1;
	while (success)
	{
		printf("请输入您的邮箱：\n");
		scanf("%s", email);
		int a = 0, b = 0, c = 0, e = 0, f = 0, g = 0;

		while (email[a] != '\0')
		{
			if (email[a] == '@')
			{
				b = 1;
				c = a; //读取出'@'字符所在的位置
				break; //检验输入的邮箱里是否有'@'
			}
			else
				a++;
		}
		while (email[e] != '\0')
		{
			if (email[e] == '.')
			{
				f = 1;
				g = e; //读取出'.'字符所在的位置
				break; //检验输入的邮箱里是否有'.'
			}
			else
				e++;
		}
		if (c != 0 && b == 1 && f == 1 && g > (c + 1))
		{
			printf("您的邮箱已创建成功！\n");
			success = 0; //测试其是否有'@'和'.'，同时'.'是否在'@' 的一位之后
		}
		else
		{
			printf("您输入的邮箱有误！\n");
		}
	}

	balance = 1000;		 //余额初始化
	strcpy(punish, "0"); //违约次数初始化。初始值为0
	printf("注册成功!赠送您1000RMB\n");
	fprintf(customerInformation, "%s %s %s %s %s %s %s %s %.2f %s\n"
		, customerID1, name, gender, age, phone, filecustomerPassword, email, district
		, balance, punish); //写入文件
	fclose(customerInformation);
	return 0;
}
char *customersignin() //顾客登陆
{
	char idt[100], pwt[100], rid[100], rpw[100], tra[100];
	FILE *customerInformation = fopen("customer.txt", "r");
	if (customerInformation)
	{
		cout << "请输入您的ID(输入“0”以退出）：" << endl;
		cin >> idt;
		rewind(customerInformation); //文件读取指针初始化
		while (fscanf(customerInformation, "%s", rid) != EOF && strcmp(idt, rid))
		{
			fscanf(customerInformation, "%s %s %s %s %s %s %s %s %s"
				, tra, tra, tra, tra, tra, tra, tra, tra, tra);
		}
		//ID检索
		while (strcmp(rid, idt) && strcmp("0", idt))
		{
			cout << "ID不存在，请重新输入(输入“0”以退出）：" << endl;
			cin >> idt;
			rewind(customerInformation);
			while (fscanf(customerInformation, "%s", rid) != EOF && strcmp(idt, rid))
			{
				fscanf(customerInformation, "%s %s %s %s %s %s %s %s %s"
					, tra, tra, tra, tra, tra, tra, tra, tra, tra);
			}
		}
		if (strcmp("0", idt) == 0)
		{
			fclose(customerInformation);
			return (char *)"0";
		}
		//密码校验
		fscanf(customerInformation, "%s %s %s %s", tra, tra, tra, tra);
		fscanf(customerInformation, "%s", rpw);
		cout << "请输入密码(输入“0”以退出）：" << endl;
		cin >> pwt;
		while (strcmp(pwt, rpw) && strcmp("0", pwt))
		{
			cout << "密码错误，请重新输入(输入“0”以退出）：" << endl;
			cin >> pwt;
		}
		if (strcmp("0", pwt) == 0)
		{
			fclose(customerInformation);
			return (char *)"0";
		}
		fclose(customerInformation);
	}
	else
	{
		cout << "File open error!" << endl;
	}
	cout << "登录成功！" << endl;
	return idt;
}
int customermenu(char id[100]) //顾客菜单
{
	char idtemp[100];
	strcpy(idtemp, id);
	while (1)
	{
		char ope(0);
		cout << "请输入操作对应序号：" << endl;
		cout << "\t1.场地查询" << endl;
		cout << "\t2.我的订单" << endl;
		cout << "\t3.我的信息" << endl;
		cout << "\t4.注销" << endl;
		cin >> ope;
		//输入检查
		while (ope < '1' || ope > '5')
		{
			cout << "输入错误！请重新输入：" << endl;
			cin >> ope;
		}
		if (ope == '1')
		{
			showcourt(id);
		}
		while (ope == '2')
		{
			char operation(0);
			cout << "请输入操作对应序号：" << endl;
			cout << "\t1.查看订单" << endl;
			cout << "\t2.取消预定" << endl;
			cout << "\t3.返回" << endl;
			cin >> operation;
			while (operation < '1' || operation > '3') //输入检查
			{
				cout << "输入错误！请重新输入：" << endl;
				cin >> operation;
			}
			if (operation == '1')
			{
				strcpy(id, idtemp);
				queryorder(id);
			}
			if (operation == '2')
			{
				cancellation(id);
			}
			if (operation == '3')
			{
				break;
			}
		}
		while (ope == '3')
		{
			char operation(0);
			cout << "请输入操作对应序号：" << endl;
			cout << "\t1.账号充值" << endl;
			cout << "\t2.查看信息" << endl;
			cout << "\t3.修改信息" << endl;
			cout << "\t4.返回" << endl;
			cin >> operation;
			while (operation < '1' || operation > '3') //输入检查
			{
				cout << "输入错误！请重新输入：" << endl;
				cin >> operation;
			}
			if (operation == '1')
			{
				recharge();
			}
			if (operation == '2')
			{
				querycustomer(id);
			}
			if (operation == '3')
			{
				modification(id);
			}
			if (operation == '4')
			{
				break;
			}
		}
		if (ope == '4')
		{
			break;
		}
	}
	return 0;
}
int main()
{
	cout << "欢迎使用综合体育场馆管理系统！" << endl;
	while (1)
	{
		//身份选择
		char mode[100];
		cout << "请输入您的身份所对应的序号：" << endl;
		cout << "\t1.管理员" << endl
			 << "\t2.顾客" << endl;
		cout << "\t3.退出程序" << endl;
		cin >> mode;
		while ((mode[0] != '1' && mode[0] != '2' && mode[0] != '3') || strlen(mode) > 1) //输入检查
		{
			cout << "输入错误！请重新输入：" << endl;
			cin >> mode;
		}

		//管理员
		while (mode[0] == '1')
		{
			char func[100];
			cout << "请输入操作对应序号：" << endl;
			cout << "\t1.登录" << endl;
			cout << "\t2.注册" << endl;
			cout << "\t3.返回" << endl;
			cin >> func;
			while ((func[0] != '1' && func[0] != '2' && func[0] != '3') || strlen(func) > 1)
			{
				cout << "输入错误！请重新输入：" << endl;
				cin >> func;
			}
			if (func[0] == '1')
			{
				char id[100];
				if (strcpy(id, adminsignin()) && id[0] != '0')
					adminmenu(id);
			}
			if (func[0] == '2')
			{
				adminsignup();
			}
			if (func[0] == '3')
				break;
		}

		//顾客
		while (mode[0] == '2')
		{
			cout << "请输入操作对应序号：" << endl;
			cout << "\t1.登录" << endl;
			cout << "\t2.注册" << endl;
			cout << "\t3.返回" << endl;
			char func[100];
			cin >> func;
			while ((func[0] != '1' && func[0] != '2' && func[0] != '3') || strlen(func) > 1)
			{
				cout << "输入错误！请重新输入：" << endl;
				cin >> func;
			}
			if (func[0] == '1')
			{
				char id[100];
				if (strcpy(id, customersignin()) && id[0] != '0')
				{
					customermenu(id);
				}
			}
			if (func[0] == '2')
			{
				customersignup();
			}
			if (func[0] == '3')
				break;
		}
		if (mode[0] == '3')
		{
			cout << "感谢使用使用综合体育场馆管理系统！" << endl;
			break;
		}
	}
	return 0;
}
