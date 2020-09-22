#include<iostream>
#include<queue>
#include<cmath>
using namespace std;

typedef struct node
{
	int a[3][3];
	int value;   //value  ��ʾf(n)=d(n)+w(n)
	int height;  //��������ǰ�ڵ�ĸ߶�
	int from;   //��ʾ�ýڵ����ɺ����ƶ����ã�1���ƣ�2���ƣ�3���ƣ�4����
	char path[1000];     //����ǰ������·��
	friend bool operator < (const node &t1,const node &t2)
	{
		return t1.value>t2.value;   //��Сֵ����
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
				if(a[i][j]==0)    //�ո���Ϊ9�����ں���Ƚ���value
					a[i][j]=9;
			}
		}
		flag=0;
		height=0;
	}
	
	bool eightcan()    //�жϰ���������ɷ��н�
	{
		/*
		�жϸ����������Ƿ��ܹ�ͨ�����޴��ƶ����ﵽĿ��״̬��
		�㷨֧�֣�
		����ָ��Less(k),k��ʾ�ھŹ����е�ĳ������,k��ȡֵ��Χ��1~9,Less(k)
		��ʾΪk���ھŹ���λ��֮���kС�����ֵĸ�����k=0ʱ���Զ�ת����k=9��
		������������
		1 0 3
		7 2 4
		6 8 5
		Less(1)=0,Less(9)=7,Less(3)=1,Less(7)=4,Less(2)=0,Less(4)=0
		Less(6)=1,Less(8)=0,Less(5)=0
		�趨i,j��ʾ�ո�λ���ھŹ����е�λ�ã�������i=1,j=2��
		�ж������Ƿ�������޴��ƶ��õ����������
		k=1:9;
		(sum(Less(k))+i+j)%2==0
		*/
		int b[9];                    //����ά����ת����һά������ڲ���
		int i,j,k,x,y;               //i,j,kΪ���Ʊ�����x,y��ʾ�ո�λ�õĺ�������������
		//��ά����תһά����
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
		//��k=1:9;sum(Less(k))+i+j	
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
		/*���ýڵ��f(n)=d(n)+w(n)���ڹ���ʱ�Ѿ���d(n)�����
		Ϊn.height,��n.value<<=n.height,w(n)��ʾ�ýڵ���Ŀ��״̬�ڵ�
		��ͬ�ĸ���*/
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
		if(!eightcan())            //�жϸ������Ƿ��ܹ��ﵽĿ��״̬
		{
			cout<<"���������޷��ƶ��õ�Ŀ��״̬"<<endl;
			return 0;
		}
		int i,j,x,y;
		priority_queue<node> q;     //��������Ȩ���У���valueֵ��С�����ȳ���
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
		if(resultOK(p_first)==1)     //�����ʼ״̬��ΪĿ��״ֱ̬�����
		{
			height=p_first.height;
			path[0]=p_first.path[0];
			path[1]=p_first.path[1];
			return 1;
		}
		q.push(p_first);
		while(q.empty()==false)
		{	
			//��õ�ǰ��չ�ڵ�Ŀո�λ��
			for(i=0;i<3;i++)
			{
				for(j=0;j<3;j++)
					if(q.top().a[i][j]==9)
					{
						x=i;y=j;
					}
			}
			//�����ƶ�����
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
		/*�ո����Ʋ�����������һ��node����ָ��*/
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
		/*�ո����Ʋ�����������һ��node����ָ��*/
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
		/*�ո����Ʋ�����������һ��node����ָ��*/
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
		/*�ո����Ʋ�����������һ��node����ָ��*/
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
	
	int resultOK(node p)     //�ж��Ƿ�ﵽĿ��״̬
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
	
	void show(node p)    //��ʾp�ڵ��е�����
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

	int returnheight()    //�����������ڵ����ȼ��ƶ���Ŀ��״̬��Ҫ�ƶ��Ĵ���
	{
		return height;
	}

	void showpath()    //��ʾ�����ƶ��ո���ԴﵽĿ��״̬
	{
		int i=1;
		if(path[i]==0)
		{
			cout<<"�����ƶ�"<<endl;
			return;
		}
		while(path[i]!=0)
		{
			switch(path[i])
			{
			case '1':cout<<"�ո�����"<<endl;break;
			case '2':cout<<"�ո�����"<<endl;break;
			case '3':cout<<"�ո�����"<<endl;break;
			case '4':cout<<"�ո�����"<<endl;break;
			}
			i++;
		}
	}

private:
	int a[3][3];          //ԭʼ�İ�������������
	int flag;             //�����Ƿ��˳����еı�־��1��Ϊ�ҵ��𰸣��˳����У�0���෴
	char path[1000];      //path��������ƶ��Ĳ���
	int height;           //�����ƶ���Ŀ��״̬���ƶ�����
};

int main()
{
	int n,m;
	cout<<"********************************"<<endl;
	cout<<"-------����������������-------"<<endl;
	cout<<"********************************"<<endl;
	while(1)
	{
		cout<<"��ѡ��ʹ�÷�ʽ:1.�������롢2.�˳�"<<endl;
		cin>>n;
		if(n==1)
		{
			cout<<"��������Ҫ��������:"<<endl;
			eightnum a;
			if(a.solution()==0)
				continue;
			while(1)
			{
				cout<<"��ѡ����Ҫ�Ĳ���:1.��ʾ�ƶ��Ĵ�����2.��ʾ�ƶ����衢3.�ص����˵�"<<endl;
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