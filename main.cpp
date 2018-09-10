#include<cstdio>
#include<cstring>
#include<iostream>
#include<cctype>

using namespace std;

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

int main()
{
    if(initial())
    {
        //管理员
        char func(0);
        cout<<"请输入操作对应序号："<<endl;
        cout<<"    1.登陆"<<endl;
        cout<<"    2.注册"<<endl;
        cin>>func;
    while(func!='1' || func!='2')
    {
        cout<<"输入错误！请重新输入："<<endl;
        cin>>func;
    }
    func-='1';
    } else
    {
        //顾客
                cout<<"请输入操作对应序号："<<endl;
        cout<<"    1.登陆"<<endl;
        cout<<"    2.注册"<<endl;
    }
    return 0;
}
