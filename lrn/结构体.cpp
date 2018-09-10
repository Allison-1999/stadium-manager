#include<stdio.h>
#include<string.h>


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


