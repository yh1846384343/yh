
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
int a[4][4];
int b[4][4];
void muchushihua();
void chushihua();
void i0();
void i1();
void j0();
void j1();
void find(int *i,int *j);
void swap(int *i,int *j);
void display(char c);
int N=1;
int x[5];
int i,j;
void backtrack(int i);
int pan();
int main(void)
{
	printf("深度优先搜索解决八数码难题\n");
	muchushihua();
	chushihua();
	int m;
	for(m=1;m<=4;m++)
		x[m]=0;int t=0;
	find(&i,&j);
	
	backtrack(t);
	printf("没有路径可以到达\n");
	
}

void backtrack(int t)
{
	
	if(N==6)
	{
		printf("到层数了\n");
		return ;
	}

		if(j-1>0&&t!=3)
	{
		printf("%d\n\n",N);
		int i=1;
		j0();
		printf("\n\n");
		display('c');
		if(pan())
		{	printf("找到了\n");system("pause");exit(1);}N++;
		backtrack(i);
		N--;
		j1();
		 
		
		
	}
	if(i-1>0&&t!=4)
	{
		printf("%d\n\n",N);
		int i=2;
		i0();
		display('c');
		if(pan())
		{	printf("找到了\n");system("pause");exit(1);}N++;
		backtrack(i);
		N--;
		i1();
		 

		
	}
	if(j+1<4&&t!=1)
	{
		printf("%d\n\n",N);
		int i=3;
		j1();
		display('c');
		if(pan())
		{	printf("找到了\n");system("pause");exit(1);}N++;
		backtrack(i);
		N--;
		j0();
		
		
	}
	if(i+1<4&&t!=2)
	{
		printf("%d\n\n",N);
		int i=4;
		i1();
		display('c');
		if(pan())
		{	printf("找到了\n");system("pause");exit(1);}N++;
		backtrack(i);
		N--;
		i0();
		
	
		
	}
	

	return ;
	
	
	

}
void display(char c)
{
	printf("转%c圈后\n",c);
	int i,j;
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
		{
			if(b[i][j]==0)
				printf("  ");
			else

			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
}
void chushihua()
{
	printf("请输入您要给的初始矩阵(用0表示空格):\n");
	int i,j;
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
		{
			scanf("%d",&b[i][j]);
		}
		
	}
	printf("您给的结果是:\n");
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
		{
			if(b[i][j]==0)
				printf("  ");
			else

			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
	if(pan())
	{
		printf("您给的就是目标矩阵\n");
		system("pause");
		exit(1);
	}
}
void muchushihua()
{
	printf("目标函数初始化(用0表示空格):\n");
	int i;
	for(i=1;i<=3;i++)
		a[1][i]=i;
	a[2][1]=8;a[2][3]=4;
	a[3][1]=7;a[3][2]=6;a[3][3]=5;
	a[2][2]=0;
	int j;
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
		{
			if(a[i][j]==0)
				printf("  ");
			else

			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
}
void i0()
{
	int m=i-1;
		int n=j;
		swap(&b[i][j],&b[m][n]);
		i=m;
}
void i1()
{
	int m=i+1;
		int n=j;
		swap(&b[i][j],&b[m][n]);
		i=m;
}
void j0()
{
	int n=j-1;
		int m=i;
		swap(&b[i][j],&b[m][n]);
		j=n;
}
void j1()
{
	int n=j+1;
		int m=i;
		swap(&b[i][j],&b[m][n]);
		j=n;
}
void find(int *i,int *j)
{
	*i=1;*j=1;
	int m,n;
	for(m=1;m<=3;m++)
		for(n=1;n<=3;n++)
		{
			if(b[m][n]==0)
			{
				*i=m;*j=n;goto L;
			}
		}
L:;
}
void swap(int *i,int *j)
{
	int t;
	t=*i;
	*i=*j;
	*j=t;
}
int pan()
{
	int i,j;
	for(i=1;i<=3;i++)
		for(j=1;j<=3;j++)
			if(a[i][j]!=b[i][j])
				return 0;
	return 1;
}



