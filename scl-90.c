/*

要点
1.二级权限           2.用户基本信息        3.答题成绩       
4.做题输入方法 '1~5' 5.整体界面            6.函数模块化
7.文件储存与读取     
基本结构体
1.测试用户信息表
2.测试成绩信息
基本函数
*/
#include "stdio.h"
#include "conio.h"
#include "string.h"
#include "malloc.h"
#include "time.h"
typedef struct UserScore
{
	int QES[90];
	int SumScore;
	int Female_Num;
	int Male_Num;
	double Somatization;//躯体化1，4，12，27，40，42，48，49，52，53，56，58
	double Obsessive_Compulsive;//3，9，10，28，38，45，46，51，55，65
	double Interpersonal_Sensitivity;//6，21，34，36，37，41，61，69，73
	double Depression;//5，14，15，20，22，26，29，30，3l，32，54，7l，79
	double Anxiety;//2，17，23，33，39，57，72，78，80，86
	double Hostility;//11，24，63，67，74，8l
	double Photic_Anxiety;//13，25，47，50，70，75，82
	double Paranoididefition;//8，18，43，68，76，83
	double Psychotieism;//7，16，35，62，77，84，85，87，88，90
	double Others;//19，44，59，60，64，66，89
	double Male_Average;//(总分-阴性项目数)/阳性项目数
	char Severity_YN;
}UserScore;
typedef struct TestUser
{
	char name[40];
	char sex;
	int age;
	UserScore *score;
	struct TestUser *next;
}TestUser;

char *Question[90]={
"头痛",
"神经过敏，心中不踏实",
"头脑中有不必要的想法或字句盘旋",
"头晕或晕倒",
"对异性的兴趣减退",
"对旁人责备求全",
"感到别人能控制您的思想",
"责怪别人制造麻烦",
"忘性大",
"担心自己的衣饰整齐及仪态的端正",
"容易烦恼和激动",
"胸痛",
"害怕空旷的场所或街道",
"感到自己的精力下降，活动减慢",
"想结束自己的生命",
"听到旁人听不到的声音",
"发抖",
"感到大多数人都不可信任",
"胃口不好",
"容易哭泣",
"同异性相处时感到害羞不自在",
"感到受骗，中了圈套或有人想抓住您",
"无缘无故地突然感到害怕",
"自己不能控制地大发脾气",
"怕单独出门",
"经常责怪自己",
"腰痛",
"感到难以完成任务",
"感到孤独",
"感到苦闷",
"过分担忧",
"对事物不感兴趣",
"感到害怕",
"您的感情容易受到伤害",
"旁人能知道您的私下想法",
"感到别人不理解您、不同情您",
"感到人们对您不友好，不喜欢您",
"做事必须做得很慢以保证做得正确",
"心跳得很厉害",
"恶心或胃部不舒服",
"感到比不上他人",
"肌肉酸痛",
"感到有人在监视您、谈论您",
"难以入睡",
"做事必须反复检查",
"难以做出决定",
"怕乘电车、公共汽车、地铁或火车",
"呼吸有困难",
"一阵阵发冷或发热",
"因为感到害怕而避开某些东西、场合或活动",
"脑子变空了",
"身体发麻或刺痛",
"喉咙有梗塞感",
"感到前途没有希望",
"不能集中注意力",
"感到身体的某一部分软弱无力",
"感到紧张或容易紧张",
"感到手或脚发重",
"想到死亡的事",
"吃得太多",
"当别人看着您或谈论您时感到不自在",
"有一些不属于您自己的想法",
"有想打人或伤害他人的冲动",
"醒得太早",
"必须反复洗手、点数",
"睡得不稳不深",
"有想摔坏或破坏东西的想法",
"有一些别人没有的想法",
"感到对别人神经过敏",
"在商店或电影院等人多的地方感到不自在",
"感到任何事情都很困难",
"一阵阵恐惧或惊恐",
"感到公共场合吃东西很不舒服",
"经常与人争论",
"单独一人时神经很紧张",
"别人对您的成绩没有做出恰当的评价",
"即使和别人在一起也感到孤单",
"感到坐立不安心神不定",
"感到自己没有什么价值",
"感到熟悉的东西变成陌生或不像是真的",
"大叫或摔东西",
"害怕会在公共场合晕倒",
"感到别人想占您的便宜",
"为一些有关性的想法而很苦恼",
"您认为应该因为自己的过错而受到惩罚",
"感到要很快把事情做完",
"感到自己的身体有严重问题",
"从未感到和其他人很亲近",
"感到自己有罪",
"感到自己的脑子有毛病"
};
//Questions
int InterfacialOutput();//界面输出函数
int MainIndex(char e,TestUser *ListHead);//主索引函数
int TestUserCreate();//测试用户创建函数 
int QuestionAnswer(UserScore *sco);//回答问题函数
char TestUserLogin();//新用户注册或已测试用户登录界面
int AUserLogin();
int TestedUserLogin();//已测试用户搜索函数
int NumTestResultOutput(TestUser *,int);//查找出的指定用户成绩输出
int TestUserListOutput(TestUser *);//管理员用户列表
int FirstFileRead(TestUser *);//文件读
int FinishFileWrite(TestUser *);//文件写
int TestResultOutput(TestUser *);//用户成绩输出
int QESOutPut(TestUser *);//单独题目成绩输出
int GResultOutput(TestUser *);
int AResultOutput(TestUser *);
int DataDelete(TestUser*,int);//指定用户数据删除

int InterfacialOutput(TestUser *ListHead)
{
	fflush(stdin);
	system("cls");
	printf("------------------------------------------\n");
	printf("欢迎使用SCL-90心理测试系统\n\n\n");
	printf("测试用户登录请键入 ‘1’\n");
	printf("--管理员登录请键入 ‘2’\n");
	printf("----退出系统请键入 ‘e’\n\n");
	char Index;
	int re;
	Index=getch();//Index存储，并向主索引调用Index
	re=MainIndex(Index,ListHead);
	while(!re)//当re为0的时候，代表Index输入不正确，
	{
		Index=getch();	
		re=MainIndex(Index,ListHead);	
	}
	if(re==1)return 0;//当re为1的时候，代表一次使用完毕，返回主界面。
	if(re==2)return 1;//当re为2的时候，代表程序使用完毕退出系统。
}

int MainIndex(char e,TestUser *ListHead)
{
	char logselect;//用于在测试用户登录界面存储选择
	int select;//用于存储各项操作的选择
	switch(e)
	{
		case '1':
		{
			logselect=TestUserLogin();//进入测试用户注册登录界面
			switch(logselect)//测试用户登录界面各个分支选择
			{
				case 's'://已测试用户搜索自己成绩
				{
					select=TestedUserLogin(ListHead);//搜索成功返回序号，失败或取消返回0
					if(select)NumTestResultOutput(ListHead,select);
					else return 1;
				}
				case 'o':return 1;//返回上一层
				case 'n'://新用户登录并开始测试
				{
					TestUserCreate(ListHead);
					QuestionAnswer(ListHead->next->score);
					while(!GResultOutput(ListHead->next))
						//在用户选择返回主菜单前持续输出
						GResultOutput(ListHead->next);
					return 1;
				}
			}
			break;
		}
		case '2'://管理员选项
		{
			if(AUserLogin())
				select=TestUserListOutput(ListHead);//成绩列表输出并返回操作变量
			//如果select为零，则代表返回上一层，否则输出相应数据
			else return 1;
			if(select)
				while(select&&(!NumTestResultOutput(ListHead,select)))
					select=TestUserListOutput(ListHead);
			return 1;
			break;
		}
		case 'e':return 2;break;//退出程序选择，返回2
		default ://输入错误情况
			printf("键入错误，请重新键入\n");
			return 0;
	}
	return 1;
}
int QuestionAnswer(UserScore *sco)
{
	system("cls");
	sco->SumScore=0;
	sco->Female_Num=0;
	sco->Male_Num=0;
	sco->Severity_YN=0;
	int i;
	for (i = 0; i < 90; ++i)
	{
		fflush(stdin);
		system("cls");
		printf("问题%d：%s\n",i+1,Question[i]);
		printf("请根据自身情况输入数字：1-没有 2-很轻 3-中等 4-偏重 5-严重\n");
		int grade;
		while(fflush(stdin), scanf("%d", &grade) != 1)
		    printf("输入有误，请按格式输入数字 1~5!\n");
		while(!(grade>=1&&grade<=5))
		{
			printf("输入有误，请按格式输入数字 1~5\n");
			while(fflush(stdin), scanf("%d", &grade) != 1)
		   		printf("输入有误，请按格式输入数字 1~5!\n");
		}
		sco->QES[i]=grade;
		sco->SumScore+=grade;
		if(grade==1)//阴性项目
			sco->Female_Num++;
		else if(grade==2)//阳性项目
			sco->Male_Num++;
		else //严重项目，将存储是否严重的变量赋值y代表yes
		{
			sco->Male_Num++;
			sco->Severity_YN='y';
		}
	}
	sco->Somatization=(double)(	sco->QES[1-1]+sco->QES[4-1]+sco->QES[12-1]+
						sco->QES[27-1]+sco->QES[40-1]+sco->QES[42-1]+
						sco->QES[48-1]+sco->QES[49-1]+sco->QES[52-1]+
						sco->QES[53-1]+sco->QES[56-1]+sco->QES[58-1])/12;
	sco->Obsessive_Compulsive=(double)(	sco->QES[3-1]+sco->QES[9-1]+sco->QES[10-1]+
								sco->QES[28-1]+sco->QES[38-1]+sco->QES[45-1]+
								sco->QES[46-1]+sco->QES[51-1]+sco->QES[55-1]+sco->QES[65-1])/10;
	sco->Interpersonal_Sensitivity=(double)(sco->QES[6-1]+sco->QES[21-1]+sco->QES[34-1]+
									sco->QES[36-1]+sco->QES[37-1]+sco->QES[41-1]+
									sco->QES[61-1]+sco->QES[69-1]+sco->QES[73-1])/9;
	sco->Depression=(double)(	sco->QES[5-1]+sco->QES[14-1]+sco->QES[15-1]+
						sco->QES[20-1]+sco->QES[22-1]+sco->QES[26-1]+
						sco->QES[29-1]+sco->QES[30-1]+sco->QES[3l-1]+
						sco->QES[32-1]+sco->QES[54-1]+sco->QES[7l-1]+sco->QES[79-1])/13;
	sco->Anxiety=(double)(	sco->QES[2-1]+sco->QES[17-1]+sco->QES[23-1]+
					sco->QES[33-1]+sco->QES[39-1]+sco->QES[57-1]+
					sco->QES[72-1]+sco->QES[78-1]+sco->QES[80-1]+sco->QES[86-1])/10;

	sco->Hostility=(double)(	sco->QES[11-1]+sco->QES[24-1]+sco->QES[63-1]+
						sco->QES[67-1]+sco->QES[74-1]+sco->QES[8l-1])/6;
	sco->Photic_Anxiety=(double)(	sco->QES[13-1]+sco->QES[25-1]+sco->QES[47-1]+
							sco->QES[50-1]+sco->QES[70-1]+sco->QES[75-1]+sco->QES[82-1])/7;
	sco->Paranoididefition=(double)(sco->QES[8-1]+sco->QES[18-1]+sco->QES[43-1]+
							sco->QES[68-1]+sco->QES[76-1]+sco->QES[83-1])/6;
	sco->Psychotieism=(double)(	sco->QES[7-1]+sco->QES[16-1]+sco->QES[35-1]+
						sco->QES[62-1]+sco->QES[77-1]+sco->QES[84-1]+
						sco->QES[85-1]+sco->QES[87-1]+sco->QES[88-1]+sco->QES[90-1])/10;
	sco->Others=(double)(	sco->QES[19-1]+sco->QES[44-1]+sco->QES[59-1]+
					sco->QES[60-1]+sco->QES[64-1]+sco->QES[66-1]+sco->QES[89-1])/7;
	sco->Male_Average=(double)(sco->SumScore-sco->Female_Num)/sco->Male_Num;//阳性平均
	if(sco->Severity_YN=='n')//是否属于严重情况进行判定
	{
		if(sco->SumScore>160)sco->Severity_YN='y';
		else if(sco->Male_Num>43)sco->Severity_YN='y';
	}
}

int TestResultOutput(TestUser *tester)
{
	fflush(stdin);
	system("cls");
	printf("------------------------------------------------\n");	
	printf("个人信息\n");
	printf("姓名:%s\n",tester->name);
	printf("性别:%c\n",tester->sex);
	printf("年龄:%d\n\n",tester->age);
	printf("--------成绩------------------------------------\n");
	printf("----总分数:%-8d\n",tester->score->SumScore);
	printf("阴性项目数:%-8d\n",tester->score->Female_Num);
	printf("阳性项目数:%-8d\n",tester->score->Male_Num);
	printf("阳性平均数:%1.2f\n",tester->score->Male_Average);
	if(tester->score->Severity_YN=='y')//判定是否严重
		printf("某一项较为严重或者有较多项呈现阳性，应做进一步阳性筛查\n\n\n");
	printf("--------以下是各项因子分数----------------------\n");
	printf("躯体化(Somatization):                   %5.2f\n",tester->score->Somatization);
	printf("强迫症状(Obsessive  Compulsive:         %5.2f\n",tester->score->Obsessive_Compulsive);
	printf("人际关系敏感(interpersonal sensitivity):%5.2f\n",tester->score->Interpersonal_Sensitivity);
	printf("抑郁(depression):                       %5.2f\n",tester->score->Depression);
	printf("焦虑(anxiety):                          %5.2f\n",tester->score->Anxiety);
	printf("敌对(hostility):                        %5.2f\n",tester->score->Hostility);
	printf("恐怖(Photic anxiety):                   %5.2f\n",tester->score->Photic_Anxiety);
	printf("偏执(Paranoididefition):                %5.2f\n",tester->score->Paranoididefition);
	printf("精神病性(psychotieism):                 %5.2f\n",tester->score->Psychotieism);
	printf("附加项目(additionalitems):              %5.2f\n",tester->score->Others);
	printf("----------------------------------------\n");
	return 1;
}
int GResultOutput(TestUser *tester)//测试用户成绩输出后的引导界面
{
	if(TestResultOutput(tester))
	{
		printf("按 ‘e’返回主菜单，按‘s’查看单独题目成绩\n");
		char out=getch();
		while(out!='e'&&out!='s')
			out=getch();
		if(out=='s')
		{
			QESOutPut(tester);
			return 0;
		}
		return 1;
	}
}
int QESOutPut(TestUser *tester)//单独题目成绩输出
{
	system("cls");
	int i;
	for ( i = 0; i < 90; ++i)
	{
		printf("问题%d：%s\n",i+1,Question[i]);
		printf("分数：%d\n",tester->score->QES[i]);
	}
	printf("按‘e’返回上一层\n");
	char out=getch();
	while(out!='e')
		out=getch();
	return 1;
}

char TestUserLogin()//测试用户登录界面，索引
{
	printf("-------------用户登录--------\n");
	printf("新用户注册并开始测试请键入 ‘1’\n");
	printf("--已测试用户成绩查看请键入 ‘2’\n");
	printf("----------返回上一层请键入 ‘e’\n");
	char select;
	select=getch();
	while(!(select=='1'||select=='2'||select=='e'))
	{
		printf("选择有误，请重新选择\n");
		select=getch();
	}
	if(select=='1')
		select='n';
	else if (select=='2')
		select='s';
	else if(select=='e')
		select='o';
	return select;
}

int TestUserCreate(TestUser * ListHead)
{
	TestUser *new=(TestUser *)malloc(sizeof(TestUser));
	new->score=(UserScore *)malloc(sizeof(UserScore));
	printf("-------请输入个人信息-------\n\n\n");
	printf("姓名：");
	gets(new->name);
	printf("性别,男性请键入 ‘m’ 女性请键入‘f’\n");
	new->sex=getch();
	while(!(new->sex=='f'||new->sex=='m'))
	{
		printf("输入有误，重新选择\n");
		new->sex=getch();
	}
	printf("%c\n",new->sex);
	printf("年龄：");
	while(fflush(stdin), scanf("%d", &new->age)!= 1)
		printf("输入有误，请以数字输入真实年龄！\n");
	while(new->age>100||new->age<1)
	{
		printf("输入有误，请以数字输入真实年龄\n");
		while(fflush(stdin), scanf("%d", &new->age) != 1)
			printf("输入有误，请以数字输入真实年龄！\n");
	}
	new->next=ListHead->next;
	ListHead->next=new;
	printf("记录完成，按任意键开始实验\n");
	getch();
	return 1;
}//测试用户创建函数
int TestedUserLogin(TestUser *ListHead)//已测试用户搜索函数
{
	system("cls");
	printf("-------------------------------------\n");
	if(ListHead->next)
	{		
		char name[50];
		int num=0,i=1;
		printf("请输入您的姓名：");
		gets(name);
		fflush(stdin);
		TestUser *p=ListHead->next;
		for(;p;p=p->next,i++)
			if(!strcmp(name,p->name))num=i;//搜索并返回序号
		if(!num)
		{
			printf("无此用户数据，请检查输入，按任意键返回上一层\n");
			getch();
		}
		return num;//返回序号
	}
	else 
	{
		printf("数据为空！按任意键返回主菜单\n");
		getch();
		return 0;//搜索失败返回零
	}
}
int AUserLogin()
{
	system("cls");
	printf("-----------------------------\n");
	printf("请输入管理员密码：\n");
	int code;
	scanf("%d",&code);
	if (code!=123)
	{
		printf("密码输入错误！按任意键返回主界面\n");
		getch();
		return 0;
	}
	else return 1;
}
int TestUserListOutput(TestUser *ListHead)//列表输出用户信息
{
	system("cls");
	TestUser *p;
	int i=1,select;
	if(ListHead->next)
	{
		for(p=ListHead->next,i=1;p;p=p->next,i++)
		{
			printf("%d.%s  年龄:%d",i,p->name,p->age);
			(p->sex=='m')?printf("性别:男\n"):printf("性别:女\n");
		}
		i--;
		printf("--------------------------------------------\n");
		printf("请输入要查看成绩的用户序号 1~%d\n,返回上一层请输入‘0’\n",i);
		for (;;)  //保证输入有效的判定
		{
			fflush(stdin);
			if((scanf("%d",&select)!=1)||(!(select>=0&&select<=i)))
			{
				printf("输入有误，请按格式输入数字序号 1~%d\n",i);
				continue;
			}
			else break;
		fflush(stdin);
		return select;
		}
	}
	else
	{
		printf("数据库中无数据！按任意键返回主菜单\n");
		getch();
		return 0;
	}
}
int NumTestResultOutput(TestUser *ListHead,int num)
{
	TestUser *p=ListHead;
	int i,select;
	for(i=0;i!=num;i++)p=p->next;
	select=AResultOutput(p);//管理员输出函数并返回操作变量
	while(!select)select=AResultOutput(p);//为零则代表退出
	if(select==2)
	{
		DataDelete(ListHead,num);//为2则执行删除操作
		return 0;
	}
	return 1;
}
int AResultOutput(TestUser *tester)
{
	if(TestResultOutput(tester))
	{
		printf("按 ‘e’返回主菜单，按‘s’查看单独题目成绩,按‘d’删除该条数据\n"); 
		char select=getch();
		while(select!='e'&&select!='s'&&select!='d')
			select=getch();
		if(select=='s')
		{
			QESOutPut(tester);
			return 0;
		}
		if(select=='d')return 2;
		return 1;
	}
}
int DataDelete(TestUser* ListHead,int num)
{
	TestUser *p=ListHead,*q;
	int i;
	for(i=0;i!=num-1;i++)p=p->next;
	q=p->next;
	p->next=q->next;
	free(q->score);
	free(q);
	printf("删除成功，按任意键返回上一次\n");
	getch();
	return 1;
}

int FirstFileRead(TestUser *ListHead)
{
	printf("-----------------------------------\n");
	printf("正在读取文件\n\n");
	FILE *data=fopen("data","rb");
	if(data==NULL)
	{
		data=fopen("data","wb");
		if(!fclose(data))
			printf("检测到无数据记录文件,创建新文件成功\n");
	}
	else
	{
		printf("检测到数据记录文件！\n");
		int result=0;
		do
		{
			TestUser *p=(TestUser *)malloc(sizeof(TestUser));
			result=fread(p,sizeof(TestUser),1,data);
			if(result==1)
			{
				p->score=(UserScore *)malloc(sizeof(UserScore));
				if(fread(p->score,sizeof(UserScore),1,data)!=1)
				{
					printf("读取出错！\n");
					getch();
					exit(0);
				}
				p->next=ListHead->next;
				ListHead->next=p;
			}
			else free(p);
		}while(result==1);
		if(ListHead->next)printf("读取数据成功\n");
		else printf("数据文件内没有用户数据\n");
	}
	printf("-----------------------------------\n");
	printf("按任意键进入程序\n");
	getch();
	return 1;
}
int FinishFileWrite(TestUser *ListHead)
{
	FILE *data=fopen("data","wb");
	if(ListHead->next)
	{
		TestUser *p=ListHead->next;
		for(;p;p=p->next)
		{
			if(fwrite(p,sizeof(TestUser),1,data)!=1)
				{printf("保存过程中出错！\n");break;}
			if(fwrite(p->score,sizeof(UserScore),1,data)!=1)
				{printf("保存过程中出错！\n");break;}
		}
	printf("-----------------------------------\n");
	printf("保存数据成功,按任意键结束程序\n");
	}
	else printf("无数据可储存，按任意键结束\n");
	fclose(data);
	getch();
	return 1;
}
int main()
{
	TestUser *ListHead=(TestUser *)malloc(sizeof(TestUser));
	ListHead->next=NULL;
	FirstFileRead(ListHead);
	while(!(InterfacialOutput(ListHead)))
		InterfacialOutput(ListHead);
	FinishFileWrite(ListHead);
	return 0;
}

