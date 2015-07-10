#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*about path*/
typedef struct pathnode
{
	char s[100];
	struct pathnode *next;
	struct pathnode *pr;
}PathNode,*PNode;
typedef struct pathhead
{
	char name[15];
	char time[250];
	char cycle_flag;
	struct pathnode *first;
}Head;
/*about station*/
typedef struct station_node
{
	char *name;
	struct station_node *next;
}Path,*pp;
typedef struct station_head
{
	char s[100];
	pp p;
}Station;
/*about quence */
typedef struct s_date_node
{
	char *stationname;
	int path_adress;
	struct s_date_node *next;
}S_danod,*PS_danod;
typedef struct s_node
{
	PS_danod p;
	struct s_node *next;
}S_node,*PS_node;
typedef struct stack
{
	PS_node *p;
}Stack,*PStack;

int init_path(Head path[]);
int find_pathadress(char s[],Head path[],int num);
void print_wholepath(int n,Head path[]);
int compare_string(char *s1,char *s2);/*1:s1>s2;2:s1<s2;0:s1=s2*/
int init_station(Station sta[],Head path[],int num);
int find_stationadress(Station sta[],int k,char *s);
void print_station(Station sta[],int n);
int kernel(char *begin,char *end,Head path[],Station sta[],int num_path,int num_station);
void init_sta_flag(Station sta[],int num_station);
int Empty_stack(PStack w);
void In_stack(PStack w,PS_node p);
PS_node Out_stack(PStack w);
PStack Init_stack(void);
void free_mem(PS_node out);
void free_stack(PStack w);
void put_result(PS_node mem,Head path[]);
void welcome(void);
char main_menue(void);
void searchpath(Head path[],int num);
void searchstation(Station sta[],int num_station);
void sta_sta(Head path[],Station sta[],int num_path,int num_station);
char claim(void);
void install(FILE *p,FILE *q);
void main(void)
{
	char c,a;
	int num_path,num_station,i;
	Head path[400];
	Station sta[3000];
	char begin[20];
	char end[20];
	char filename[150];
	FILE *first,*p,*q;
	first=fopen("noo.txt","r+");
	p=fopen("source of date.txt","r");
	c=fgetc(first);
	fclose(first);
	switch(c)
	{
	case '1':
		a=claim();
		if(a=='Y')
		{
			printf("Installing...\n");
			q=fopen("filename","w+");
			install(p,q);
			first=fopen("noo.txt","r+");
			fputc('0',first);
		}
		else
		exit(0);
		break;
	case '0':
		;
		break;
	}
	fclose(first);
	for(i=0;i<15;i++)
	{
		welcome();
		system("CLS");
	}
	printf("Initializing date,wait");
	num_path=init_path(path);
	printf("\npath initialized.");
	num_station=init_station(sta,path,num_path);
	printf("\nstation initialized.");
	system("CLS");
	c=main_menue();
	while(c!='q')
	{
	system("CLS");
	switch(c)
	{
	case '1':
		searchpath(path,num_path);
		system("CLS");
		c=main_menue();
		break;
	case '2':
        searchstation(sta,num_station);
		system("CLS");
		c=main_menue();
		break;
	case '3':
		sta_sta(path,sta,num_path,num_station);
		system("CLS");
		c=main_menue();
		break;
	case '4':
		system("CLS");
		c=main_menue();
		break;
	}
	}
	exit(0);
}
int init_path(Head path[])
{
	char c;
	int k;
	int i=0;
	PNode p,q;
	FILE *fp;
	fp=fopen("D://source of date.txt","r");
	c=fgetc(fp);
	while(c!=-1)
	{
		printf(".");
		for(k=0;c!='#';k++)
		{
			path[i].name[k]=c;
			c=fgetc(fp);
		}
		path[i].name[k]=0;
		p=path[i].first=(PNode)malloc(sizeof(PathNode));
		c=fgetc(fp);
		for(k=0;c!=' ';k++)
		{
			p->s[k]=c;
			c=fgetc(fp);
		}
		p->s[k]=0;
		p->pr=NULL;
		c=fgetc(fp);
		while(c!=':')
		{
			q=(PNode)malloc(sizeof(PathNode));
			p->next=q;
			q->pr=p;
			p=q;
			for(k=0;c!=' '&&c!=':';k++)
			{
				p->s[k]=c;
				c=fgetc(fp);
			}
			p->s[k]=0;
			if(c==' ')
			c=fgetc(fp);
		}
		p->next=NULL;
		c=fgetc(fp);
		for(k=0;c!='\n'&&c!=-1;k++)
		{
		path[i].time[k]=c;
		c=fgetc(fp);
		}
		path[i].time[k]=0;
		if(c=='\n')
			c=fgetc(fp);
		i++;
	}
	return i;
}
int find_pathadress(char s[],Head path[],int num)/*-1:no this path;i:the path is the i_th.
                                                   num:the number of the paths.*/
{
	int i,j;
	for(i=0;i<num;i++)
	{
		for(j=0;path[i].name[j]!=0&&s[j]!=0;j++)
			if(s[j]!=path[i].name[j])
				break;
	    if(path[i].name[j]==0&&s[j]==0)
			return i;
	}
	return -1;
}
void print_wholepath(int n,Head path[])
{
	PNode p;
	printf("\nPATH :%s\n",path[n].name);
	printf("infor about this path:%s\n",path[n].time);
	printf("this path pass through these stations in turn :\n");
	p=path[n].first;
	while(p!=NULL)
	{
		if(p->next)
		printf("%s--",p->s);
		else
			printf("%s\n",p->s);
		p=p->next;
	}
	printf("NOTICE! please check if this path is circular,my software is lacking on this aspect!\n");
}
void print_station(Station sta[],int n)
{
	pp p;
	p=sta[n].p;
	printf("these paths pass through %s.\n",sta[n].s);
	while(p!=NULL)
	{
		printf("%s\n",p->name);
		p=p->next;
	}
}
int compare_string(char *s1,char *s2)/*1:s1>s2;2:s1<s2;0:s1=s2*/
{
	int i;
	for(i=0;s1[i]!=0&&s2[i]!=0;i++)
		if(s1[i]>s2[i])
			return 1;
		else if(s1[i]<s2[i])
			return 2;
		else
			;
		if(s1[i]-s2[i]>0)
			return 1;
		else if(s1[i]-s2[i]<0)
			return 2;
		else
			return 0;
}
int init_station(Station sta[],Head path[],int num)
{
	int i,j,m,low,high,mid;
	int k=-1;
	PNode p;
	pp q,r;
	for(i=0;i<num;i++)
	{
		p=path[i].first;
		while(p!=NULL)
		{
			for(j=0;j<=k;j++)
			if(compare_string(p->s,sta[j].s)==0)
			{
				q=sta[j].p;
				while(q)
				{
					if(q->next==NULL)
						break;
					else
						q=q->next;
				}
				r=(pp)malloc(sizeof(Path));
				r->name=path[i].name;
				r->next=NULL;
				q->next=r;
				break;
			}
			if(j>k)
			{
				printf(".");
				low=0;
				high=k;
				while(low<=high)
				{
					mid=(low+high)/2;
					if(compare_string(p->s,sta[mid].s)==2)
						high=mid-1;
					else
						low=mid+1;
				}
				for(m=k;m>=high+1;m--)
					sta[m+1]=sta[m];
				for(m=0;p->s[m]!=0;m++)
					sta[high+1].s[m]=p->s[m];
				sta[high+1].s[m]=0;
				r=(pp)malloc(sizeof(Path));
				r->name=path[i].name;
				r->next=NULL;
				sta[high+1].p=r;
				k++;
			}
			p=p->next;
		}
	}
	return k+1;
}
int find_stationadress(Station sta[],int k,char *s)/*k is the total number of the station.*/
{
	int low,high,mid;
	low=0;
	high=k-1;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(compare_string(sta[mid].s,s)==1)
			high=mid-1;
		if(compare_string(sta[mid].s,s)==2)
			low=mid+1;
		if(compare_string(sta[mid].s,s)==0)
			return mid;
	}
	return -1;
}
int kernel(char *begin,char *end,Head path[],Station sta[],int num_path,int num_station)
{
	int start,j,i,a;
	int temp,counter,pos;
	int min;
	int times=5;
	char flag,b;
	clock_t start1,end1;
	pp p;
	PNode r,q,g;
	PS_node out,OUT,in,v,mem;
	PS_danod in_tail,h,k,x,y,z;
	PStack t,w;
	w=Init_stack();
	v=(PS_node)malloc(sizeof(S_node));
	v->next=NULL;
	v->p=(PS_danod)malloc(sizeof(S_danod));
	v->p->next=NULL;
	v->p->path_adress=-1;
	v->p->stationname=begin;
	In_stack(w,v);
    for(j=0;j<=times;j++)
	{
	i=1;
	min=23344;
	flag=0;
	t=w;
	w=Init_stack();
	start1=clock();
	while(!Empty_stack(t))
	{/*!*/
	end1=clock();
	a=(end1-start1)/CLK_TCK;
	if(a>2)
		break;
	out=Out_stack(t);/*out quence*/
	x=out->p;
	while(x->next!=NULL)
		x=x->next;
	z=x;
	start=find_stationadress(sta,num_station,x->stationname);
	
	p=sta[start].p;
	while(p!=NULL)
	{
	temp=find_pathadress(p->name,path,num_path);
	r=path[temp].first;
	while(r!=NULL)
	{
		if(compare_string(z->stationname,r->s)==0||(find_stationadress(sta,num_station,r->s)==find_stationadress(sta,num_station,begin)&&find_stationadress(sta,num_station,end)!=find_stationadress(sta,num_station,begin)))
			;
		else
		{
		pos=find_stationadress(sta,num_station,r->s);
		in_tail=(PS_danod)malloc(sizeof(S_danod));
		in_tail->path_adress=temp;
		in_tail->stationname=r->s;
		in_tail->next=NULL;
		h=out->p;
		y=x=(PS_danod)malloc(sizeof(S_danod));
		x->path_adress=h->path_adress;
		x->stationname=h->stationname;
		h=h->next;
		while(h!=NULL)
		{
			k=(PS_danod)malloc(sizeof(S_danod));
			x->next=k;
			k->path_adress=h->path_adress;
			k->stationname=h->stationname;
			k->next=NULL;
			x=k;
			h=h->next;
		}
		x->next=in_tail;
		in=(PS_node)malloc(sizeof(S_node));
		in->p=y;
		In_stack(w,in);/*in quence*/
		}
		if(compare_string(r->s,end)==0)
		{/*#*/
		i++;
		OUT=Out_stack(w);
		x=OUT->p;
		counter=0;
		while(x->next!=NULL)/*provide the information that if the path is cycle!*/
		{
		   q=path[x->next->path_adress].first;
		   while((compare_string(q->s,x->stationname)!=0))
		   q=q->next;
	       g=q;
		   while(q!=NULL)
		   {
			  if(compare_string(q->s,x->next->stationname)==0)
				break;
			  q=q->next;
		   }
	       if(q==NULL)
		   {
			 q=g;/*00*/
		     while(q!=NULL)
			 {
			    if(compare_string(q->s,x->next->stationname)==0)
		     		break;
			    q=q->pr;
			    counter++;
			 }
		   }
		   else
			{
				 q=g;
			     while(q!=NULL)
				 {
					  if(compare_string(q->s,x->next->stationname)==0)
						   break;
					  q=q->next;
					  counter++;
				 }
		   }
    	x=x->next;
		}
		if(j==0)
		{
			printf("0 次换乘,乘车路线 %d:",i-1);
			put_result(OUT,path);
		}
    	if(counter<=min)
		{
		 if(!flag)
		 {
			mem=OUT;
			flag=1;
		 }
	   	 else
		 {
			free(mem);
			mem=OUT;
		 }
		min=counter;
		b=i-1;
		}
	    else
	    free_mem(OUT);
	    if(j!=0)
	     break;/*break to r*/
		}/*match with #*/
	   r=r->next;
	}
	   p=p->next;
	}
	p=NULL;
	free_mem(out);
    }/*match with !*/
    if(i==1)
    printf("%d 次换乘到达目的站不能实现.\n",j);
	else
	{
	if(j==0)
	printf("建议选择乘车路线 %d ,沿途经过 %d 站。\n\n",b,min);
	else
	{
		printf("%d 次换乘经过 %d 站,到达目的站.\n",j,min);
		put_result(mem,path);
	}
	}
	if(j!=0&&i!=1)
		break;
}
free_stack(w);
if(j>times)
return 3;/*无法找到路径,考虑公交线路有问题*/
return 0;/*正常完成了函数的功能*/
}
PStack Init_stack(void)
{
	PStack w;
	w=(PStack)malloc(sizeof(Stack));
	if(w)
	{
		w->p=NULL;
		return w;
	}
	else
	{
		printf("Error memory!\n");
	    exit(0);
	}
}
PS_node Out_stack(PStack w)
{
	PS_node p;
	if(w->p==NULL)
	{
		printf("stack is empty!\n");
		exit(0);
	}
	else
	{
		p=w->p;
		w->p=p->next;
		return p;
	}
}
void In_stack(PStack w,PS_node p)
{
	PS_node q;
	q=w->p;
	p->next=q;
	w->p=p;
}
int Empty_stack(PStack w)
{
	if(w->p!=NULL)
		return 0;
	else
		return 1;
}
void free_mem(PS_node out)
{
	PS_danod p,q;
	p=out->p;
	while(p!=NULL)
	{
		q=p;
		p=p->next;
		free(q);
	}
	free(out);
}
void free_stack(PStack w)
{
	PS_node p,t;
	PS_danod q,r;
	p=w->p;
	while(p!=NULL)
	{
		q=p->p;
		while(q!=NULL)
		{
			r=q;
			q=q->next;
			free(r);
		}
		t=p;
		p=p->next;
		free(t);
	}
	free(w);
}
void put_result(PS_node mem,Head path[])
{
	PS_danod x;
	PNode q,g;
	x=mem->p;
	while(x->next!=NULL)/*provide the information that if the path is cycle!*/
	{
	printf("乘坐 %s(%s):",path[x->next->path_adress].name,path[x->next->path_adress].time);
	q=path[x->next->path_adress].first;
	while((compare_string(q->s,x->stationname)!=0))
	q=q->next;
	g=q;
	while(q!=NULL)
	{
	 if(compare_string(q->s,x->next->stationname)==0)
    	break;
	 q=q->next;
	}
	if(q==NULL)
	{
	q=g;/*00*/
	while(q!=NULL)
	{
	if(compare_string(q->s,x->next->stationname)==0)
	{
		printf("%s",q->s);
		 break;
	}
	printf("%s--",q->s);
	q=q->pr;
	}
	}
	else
	{
	q=g;
	while(q!=NULL)
	{
	if(compare_string(q->s,x->next->stationname)==0)
	{
	printf("%s",q->s);
	break;
	}
	printf("%s--",q->s);
	q=q->next;
	}
	}
	if(x->next->next!=NULL)
	printf("\n换乘\n");
	x=x->next;
	}
	printf("\n\n");
}
char main_menue(void)
{
	char c;
	printf("                        ===========BUS SEARCH  1.0===========                  ");
	printf("                                  free software(cjl)\n");
	printf("                              Written by ChenJianglong\n\n\n");
	printf("                     -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
	printf("                    |                                         |\n");
	printf("                    * 1.paths search.                         *\n");
	printf("                    |                                         |\n");
	printf("                    * 2.station search.                       *\n");
	printf("                    |                                         |\n");
	printf("                    * 3.station to station.                   *\n");
    printf("                    |                                         |\n");
	printf("                    * 4.for help.                             *\n");
	printf("                    |                                         |\n");
	printf("                    * input \"q\" for quit.                     *\n");
	printf("                    |                                         |\n");
	printf("                     -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
	printf("                      please input your choice :");
	scanf("%c",&c);
	getchar();
	while(c!='1'&&c!='2'&&c!='3'&&c!='4'&&c!='q')
	{
	    printf("                    >select correct options! :");
		scanf("%c",&c);
		getchar();
	}
	return c;
 }
void welcome(void)
{
	printf("\n\n\n\n\n\n\n\n\n");
	printf("                                  Welcome to!!\n");
	printf("                                BUS SEARCH  1.0");
}
void searchpath(Head path[],int num)
{
	char s[20];
	char c;
	int n;
	printf("      -----------------------  Search paths  -----------------------        free software(cjl)\n");
	printf("                           \"q\" for quit this menue!\n");
	printf(">search paths (Y/q):");
	scanf("%c",&c);
	getchar();
	while(c!='q')
	{
	printf(">input the name of the path :");
	gets(s);
	n=find_pathadress(s,path,num);
	while(n==-1)
	{
		printf("No this path,please check!\n");
		printf(">input the name of the path :");
	    gets(s);
	    n=find_pathadress(s,path,num);
	}
	print_wholepath(n,path);
	printf(">continue searching paths (Y/q):");
	scanf("%c",&c);
	getchar();
	}
}
void searchstation(Station sta[],int num_station)
{
	char s[20];
	char c;
	int n;
	printf("        ---------------------  Search stations  ---------------------         \n");
	printf("                              free software(cjl)\n");
	printf("                           \"q\" for quit this menue!\n");
	printf(">search stations (Y/q):");
	scanf("%c",&c);
	getchar();
	while(c!='q')
	{
		printf(">input the name of the station :");
		gets(s);
		n=find_stationadress(sta,num_station,s);
		while(n==-1)
		{
		printf("No this path,please check!\n");
		printf(">input the name of the station :");
	    gets(s);
	    n=find_stationadress(sta,num_station,s);
		}
		print_station(sta,n);
		printf(">continue searching stations(Y/q):");
	    scanf("%c",&c);
		getchar();
	}
}
void sta_sta(Head path[],Station sta[],int num_path,int num_station)
{
	char begin[20],end[20];
	int m,n;
	char c;
	printf("    ----------------------  Search scheme  ---------------------        \n");
	printf("                          free software(cjl)\n");
	printf("                         \"q\" for quit this menue!\n");
	printf(">find path (Y/q):");
	scanf("%c",&c);
	getchar();
	while(c!='q')
	{
		printf(">input the name of the begin station :");
		gets(begin);
		m=find_stationadress(sta,num_station,begin);
		while(m==-1)
		{
		printf("No this path,please check!\n");
		printf(">input the name of the begin station :");
	    gets(begin);
	    m=find_stationadress(sta,num_station,begin);
		}
		printf(">input the name of the end station :");
		gets(end);
		n=find_stationadress(sta,num_station,end);
		while(n==-1)
		{
		printf("No this path,please check!\n");
		printf(">input the name of the end station :");
	    gets(end);
	    n=find_stationadress(sta,num_station,end);
		}
		if(kernel(begin,end,path,sta,num_path,num_station)==3)
		{
			printf("you should consider that the bus system is wrong.Now,BUS SEARCH 1.0 shouts down!\n");
			exit(0);
		}
		printf(">continue finding paths (Y/q):");
	    scanf("%c",&c);
		getchar();
	}
}
char claim(void)
{
	char c;
	printf("1.This software is free:no commerce for it,you can perfect it without any responsibility .\n \
2.This software is written by C Language entirely.");
    printf("\n\nRecieve or not(Y/N) :");
	scanf("%c",&c);
	while(c!='Y'&&c!='N')
	{
		printf("input \"Y\"or\"N\" :");
		scanf("%c",&c);
	}
	return c;
}
void install(FILE *p,FILE *q)
{
	char c;
	c=fgetc(p);
	while(c!=-1)
	{
		fputc(c,q);
		c=fgetc(p);
	}
	fclose(p);
	fclose(q);
}


