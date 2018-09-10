//#include<cstdio>
#include<cstring>
#include<iostream>
#include<cctype>
#include<cstdlib>

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
	period p;
	char courtID[100];
	customer c;
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
	period ordered[30]; 
} court;
typedef struct stadium
{
	char name[100];
	char district[100];
	char ID[100];
	court court1, court2;
} stadium;

//函数
int initial(){
    //欢迎界面
    char mode(0);
    cout<<"欢迎使用综合体育场馆管理系统！"<<endl;
    cout<<"请输入您的身份所对应的序号："<<endl;
    cout<<"    1.顾客"<<endl<<"    2.管理员";
    cin>>mode;
    while(mode!='1' || mode!='2')
    {
        cout<<"输入错误！请重新输入："<<endl;
        cin>>mode;
    }
    mode-='1';
    return (int)mode;
}
int guestsignup()
{
    FILE* customerInformation=fopen("customer.txt","a+");//文件
    char customerID1[100],customerID2[100],line[100];
    char filecustomerPassword[100],password2[100];
    char name[100];
    char phone[20];
    char gender[10];
	char age[10];
	char password[10];
	char email[20];
	float balance;
	char district[100];
    int a,b,c,d,i,success,adressnumber;
   
    success=1;
    while(success)
    {
        a=0;
        b=0;
        c=0;
        
        printf("请创建您的账号,账号需由数字和字母组合而成，长度为6位到10位：\n");
        scanf("%s",customerID1);
        
        if(strlen(customerID1)<6||strlen(customerID1)>10) //检查账号的长度
        {
            printf("您输入的账号不符合要求，请重新创建！\n");
            a=1;
        }
        
        for (i=0;i<strlen(customerID1);i++)//检查账号是否都有数字和字母组成
        {
            if(isalpha(customerID1[i]) == 0 && isdigit(customerID1[i]) == 0)
            {
                printf("您输入的账号不符合要求，请重新创建\n");
                c=1;
                break;
            }
            
        }
        if (a==0&&b==0&&c==0)
            success=0;
        else
            success=1;
    }

    printf("请您输入您的姓名\n");
    scanf("%s",name);
    printf("请输入您的性别(男或女）\n");
    scanf("%s",gender);
    printf("请输入您的年龄\n");
    scanf("%s",age);
	
	printf("请选择您的所在地区\n");
	printf("海淀区---1\n");
	printf("西城区---2\n");
	printf("东城区---3\n");
	printf("朝阳区---4\n");
	
    scanf("%d",&adressnumber);
    

    if(adressnumber<<1&&adressnumber>>4)
		printf("请输入正确地区序号");
	else{
		if(adressnumber==1)
			district="海淀区";
		if(adressnumber==2)
			district="西城区";
		if(adressnumber==3)
			district="东城区";
		if(adressnumber==4)
			district="朝阳区";
		} 
    
    success=1;
    while(success)
    {
        success=0;
        int flag1(0),flag2(0);
        printf("请输入您的手机号码（11位）\n");
        scanf("%s",phone);
        
        if(strlen(phone)==11)
            flag1=1;
        for(b=0;b++;b<11)
        {
            if(isdigit(phone[b])!=0)
                flag2=1;
        }
        
        if(flag1!=1&&flag2!=1){
        	printf("您输入的号码有误，请确认后再次输入\n");
        	success=1;
		}else printf("输入成功\n");
    }


    success=1;
    while(success)
    {
        printf("请创建您的密码\n");
        scanf("%s",filecustomerPassword);
        printf("请再次输入您的密码\n");
        scanf("%s",password2);
        if(strcmp(filecustomerPassword,password2)!=0)
            printf("两次输入密码不同，请重新创建密码\n");
        else
            success=0;
    }
    
    success=1;
    while(success)
    {
        printf("请输入您的邮箱：\n"); 
        scanf("%s",email);
        int z=0,b=0,c=0,e=0,f=0,g=0;

        while(email[a]!='\0')
        {
            if (email[a]=='@')
            {
                b=1;
                c=a;//读取出'@'字符所在的位置 
                break;//检验输入的邮箱里是否有'@' 
            }
            else a++;
        }
        while(email[e]!='\0')
        {
            if (email[e]=='.')
            {
                f=1;
                g=e;//读取出'.'字符所在的位置 
                break;//检验输入的邮箱里是否有'.'
            }
            else e++;
        }
            
        if(b==1&&f==1&&g>(c+1)){
        printf("您的邮箱已创建成功！\n");
        success=0;//测试其是否有'@'和'.'，同时'.'是否在'@' 的一位之后 
        }else
        {
            printf("您输入的邮箱有误！\n");
        }	
	}
    printf("注册成功!赠送您1000RMB\n");
    fprintf(customerInformation,"%s %s %s %s %s %s %s %.2f\n",customerID1,name,gender,phone,filecustomerPassword,email,district,1000.00);//写入文件 
    fclose(customerInformation);
    return 0;
}

int main()
{
    if(initial())
    {
        //管理员
        char func(0);
        cout<<"请输入操作对应序号："<<endl;
        cout<<"    1.登录"<<endl;
        cout<<"    2.注册"<<endl;
        cin>>func;
        while(func!='1' || func!='2')
        {
            cout<<"输入错误！请重新输入："<<endl;
            cin>>func;
        }
        func-='1';
        if(func)
        {
            //注册

        } else
        {
            //登录

        }
    } else
    {
        //顾客
                cout<<"请输入操作对应序号："<<endl;
        cout<<"    1.登录"<<endl;
        cout<<"    2.注册"<<endl;
        char func(0);
        cin>>func;
        while(func!='1' || func!='2')
        {
            cout<<"输入错误！请重新输入："<<endl;
            cin>>func;
        }
        func-='1';
        if(func)
        {
            //注册
            guestsignup();
        } else
        {
            //登录

        }
    }
    return 0;
}
