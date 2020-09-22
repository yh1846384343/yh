#include<iostream>
#include<queue>
#include<cmath>
using namespace std;

typedef struct node
{
	int a[3][3];
	int value;   //value  表示f(n)=d(n)+w(n)
	int height;  //搜索到当前节点的高度
	int from;   //表示该节点是由何种移动所得，1左移，2右移，3上移，4下移
	char path[1000];     //保存前面搜索路径
	friend bool operator < (const node &t1,const node &t2)
	{
		return t1.value>t2.value;   //最小值优先
	}
}node,*nodelist;

class eightnum
{
public:
	eightnum()
	{
		int i,j;
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				cin>>a[i][j];
				if(a[i][j]==0)    //空格处置为9，便于后面比较求value
					a[i][j]=9;
			}
		}
		flag=0;
		height=0;
	}
	
	bool eightcan()    //判断八数码问题可否有解
	{
		/*
		判断给出的排列是否能够通过有限次移动，达到目标状态。
		算法支持：
		首先指定Less(k),k表示在九宫格中的某个数字,k的取值范围是1~9,Less(k)
		表示为k所在九宫格位置之后比k小的数字的个数。k=0时，自动转换成k=9。
		在下列排列中
		1 0 3
		7 2 4
		6 8 5
		Less(1)=0,Less(9)=7,Less(3)=1,Less(7)=4,Less(2)=0,Less(4)=0
		Less(6)=1,Less(8)=0,Less(5)=0
		设定i,j表示空格位置在九宫格中的位置，此例中i=1,j=2。
		判断排列是否可在有限次移动得到解的条件是
		k=1:9;
		(sum(Less(k))+i+j)%2==0
		*/
		int b[9];                    //将二维数组转化成一维数组便于操作
		int i,j,k,x,y;               //i,j,k为控制变量，x,y表示空格位置的横坐标与纵坐标
		//二维数组转一维数组
		k=0;
		for(i=0;i<3;i++)              
		{
			for(j=0;j<3;j++)
			{
				b[k]=a[i][j];
				if(a[i][j]==9)
				{
					x=i+1;
					y=j+1;
				}
				k++;
			}
		}
		//求k=1:9;sum(Less(k))+i+j	
		int sum=x+y;                  	
		for(i=0;i<9;i++)
		{
			for(j=i;j<9;j++)
			{
				if(b[j]<b[i])
					sum++;
			}
		}
		if(sum%2==0)
			return true;
		else
			return false;		
	}
	
	int f(node now_node)    
	{
		/*求解该节点的f(n)=d(n)+w(n)，在构造时已经将d(n)求出，
		为n.height,且n.value<<=n.height,w(n)表示该节点与目标状态节点
		不同的个数*/
		int i,j;
		int value=0;
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
				if(now_node.a[i][j]!=i*3+j+1)
				{
					value++;
				}
		}
		return value+now_node.value;
	}
	
	int solution()
	{
		if(!eightcan())            //判断该排列是否能够达到目标状态
		{
			cout<<"该种排列无法移动得到目标状态"<<endl;
			return 0;
		}
		int i,j,x,y;
		priority_queue<node> q;     //构造优先权队列，以value值最小的优先出队
		node p_first;
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
				p_first.a[i][j]=a[i][j];
		}
		p_first.value=0;
		p_first.height=0;
		p_first.from=0;
		p_first.path[0]=48;
		p_first.path[1]=0;
		p_first.value=f(p_first);
		if(resultOK(p_first)==1)     //如果初始状态即为目标状态直接输出
		{
			height=p_first.height;
			path[0]=p_first.path[0];
			path[1]=p_first.path[1];
			return 1;
		}
		q.push(p_first);
		while(q.empty()==false)
		{	
			//获得当前扩展节点的空格位置
			for(i=0;i<3;i++)
			{
				for(j=0;j<3;j++)
					if(q.top().a[i][j]==9)
					{
						x=i;y=j;
					}
			}
			//进行移动操作
			if(y-1>=0 && q.top().from!=2)
				q.push(*moveleft(q.top(),x,y));
			if(flag==1)
				break;
			if(y+1<=2 && q.top().from!=1)
				q.push(*moveright(q.top(),x,y));
			if(flag==1)
				break;
			if(x-1>=0 && q.top().from!=4)
				q.push(*moveup(q.top(),x,y));
			if(flag==1)
				break;
			if(x+1<=2 && q.top().from!=3)
				q.push(*movedown(q.top(),x,y));
			if(flag==1)
				break;
			q.pop();
		}
		return 1;
	}
	
	node* moveleft(node n,int x,int y)
	{
		/*空格左移操作，并返回一个node类型指针*/
		nodelist p=new node();
		int i,j,temp;
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				p->a[i][j]=n.a[i][j];
			temp=p->a[x][y];
			p->a[x][y]=p->a[x][y-1];
			p->a[x][y-1]=temp;
			p->from=1;
			p->height=n.height+1;
			for(i=0;i<=n.height;i++)
				p->path[i]=n.path[i];
			p->path[p->height]=p->from+48;
			p->value=p->height;
			p->value=f(*p);
			if(resultOK(*p)==1)
			{
				height=p->height;
				p->path[p->height+1]=0;
				j=0;
				while(p->path[j]!=0)
				{
					path[j]=p->path[j];
					j++;
				}
				path[j]=0;
				flag=1;
			}
			return p;
	}
	
	node* moveright(node n,int x,int y)
	{
		/*空格右移操作，并返回一个node类型指针*/
		nodelist p=new node();
		int i,j,temp;
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				p->a[i][j]=n.a[i][j];
			temp=p->a[x][y];
			p->a[x][y]=p->a[x][y+1];
			p->a[x][y+1]=temp;
			p->from=2;
			p->height=n.height+1;
			for(i=0;i<=n.height;i++)
				p->path[i]=n.path[i];
			p->path[p->height]=p->from+48;
			p->value=p->height;
			p->value=f(*p);
			if(resultOK(*p)==1)
			{
				height=p->height;
				p->path[p->height+1]=0;
				j=0;
				while(p->path[j]!=0)
				{
					path[j]=p->path[j];
					j++;
				}
				path[j]=0;
				flag=1;
			}
			return p;
	}
	
	node* moveup(node n,int x,int y)
	{
		/*空格上移操作，并返回一个node类型指针*/
		nodelist p=new node();
		int i,j,temp;
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				p->a[i][j]=n.a[i][j];
			temp=p->a[x][y];
			p->a[x][y]=p->a[x-1][y];
			p->a[x-1][y]=temp;
			p->from=3;
			p->height=n.height+1;
			for(i=0;i<=n.height;i++)
				p->path[i]=n.path[i];
			p->path[p->height]=p->from+48;
			p->value=p->height;
			p->value=f(*p);
			if(resultOK(*p)==1)
			{
				height=p->height;
				p->path[p->height+1]=0;
				j=0;
				while(p->path[j]!=0)
				{
					path[j]=p->path[j];
					j++;
				}
				path[j]=0;
				flag=1;
			}
			return p;
	}
	
	node* movedown(node n,int x,int y)
	{
		/*空格下移操作，并返回一个node类型指针*/
		nodelist p=new node();
		int i,j,temp;
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				p->a[i][j]=n.a[i][j];
			temp=p->a[x][y];
			p->a[x][y]=p->a[x+1][y];
			p->a[x+1][y]=temp;
			p->from=4;
			p->height=n.height+1;
			for(i=0;i<=n.height;i++)
				p->path[i]=n.path[i];
			p->path[p->height]=p->from+48;
			p->value=p->height;
			p->value=f(*p);	
			if(resultOK(*p)==1)
			{
				height=p->height;
				p->path[p->height+1]=0;
				j=0;
				while(p->path[j]!=0)
				{
					path[j]=p->path[j];
					j++;
				}
				path[j]=0;
				flag=1;
			}
			return p;
	}
	
	int resultOK(node p)     //判断是否达到目标状态
	{
		int i,j;
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
				if(p.a[i][j]!=i*3+j+1)
					return 0;
		}
		return 1;
	}
	
	void show(node p)    //显示p节点中的排列
	{
		int i,j;
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				if(p.a[i][j]==9)
					cout<<"0 ";
				else
					cout<<p.a[i][j]<<" ";
			}
			cout<<endl;
		}
	}

	int returnheight()    //返回搜索到节点的深度即移动到目标状态需要移动的次数
	{
		return height;
	}

	void showpath()    //显示怎样移动空格可以达到目标状态
	{
		int i=1;
		if(path[i]==0)
		{
			cout<<"无需移动"<<endl;
			return;
		}
		while(path[i]!=0)
		{
			switch(path[i])
			{
			case '1':cout<<"空格左移"<<endl;break;
			case '2':cout<<"空格右移"<<endl;break;
			case '3':cout<<"空格上移"<<endl;break;
			case '4':cout<<"空格下移"<<endl;break;
			}
			i++;
		}
	}

private:
	int a[3][3];          //原始的八数码问题数据
	int flag;             //用于是否退出队列的标志，1即为找到答案，退出队列，0则相反
	char path[1000];      //path保存的是移动的步骤
	int height;           //保存移动到目标状态的移动次数
};

int main()
{
	int n,m;
	cout<<"********************************"<<endl;
	cout<<"-------八数码问题解决程序-------"<<endl;
	cout<<"********************************"<<endl;
	while(1)
	{
		cout<<"请选择使用方式:1.求解八数码、2.退出"<<endl;
		cin>>n;
		if(n==1)
		{
			cout<<"请输入需要求解的排列:"<<endl;
			eightnum a;
			if(a.solution()==0)
				continue;
			while(1)
			{
				cout<<"请选择需要的操作:1.显示移动的次数、2.显示移动步骤、3.回到主菜单"<<endl;
				cin>>m;
				if(m==1)
					cout<<a.returnheight()<<endl;
				if(m==2)
					a.showpath();
				if(m==3)
					break;
			}
		}
		if(n==2)
			break;
	}
	return 0;
}