#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <queue>
//#include <stack>
//#include <ctype.h>
//#include <fstream>
//#include <cstring>
//#include <sstream>
//#include <cstdio>
//#include <iomanip>
//#include <vector>
//#include <algorithm>
//#include <Windows.h>
//#pragma GCC optimize(2)

using namespace std;

typedef long long int ll;
#define MAX 100000000
const ll inf = 0x3f3f3f3f;
void Test(){cout<<'!'<<endl;}
//46685
int cantor(int in[]);
void rcantor(int in, int a[]);//alter
void pin(int in,int zero);

int at1[9] = {0}, at2[9] = {0};
int jc[9] = {1,1,2,6,24,120,720,5040,40320};
int map[362890] = {0};
queue<int>next;
queue<int>lev;
int l;

int main()
{
//	freopen("in.txt","r",stdin);
	ios::sync_with_stdio(false);
	int i;
	memset(map,-1,sizeof(map));
	
	for(i = 0; i < 9; i++) at1[i] = getchar() - '0';
	next.push(cantor(at1));
	lev.push(0);
	while(next.size())
	{
		if(map[46685] != -1)
		{
			cout<<map[46685]<<endl;
			return 0;
		}
		
		int t = next.front();
		l = lev.front();
		next.pop();
		lev.pop();
		
		map[t] = l;
		rcantor(t, at1);
		
		int zero(0);
		for(i = 0; i < 9; i++)
		{if(at1[i] == 0) zero = i;}
		
		switch(zero)
		{
			case 0:
				{pin(1,zero);pin(3,zero);break;}
			case 1:
				{pin(0,zero);pin(2,zero);pin(4,zero);break;}
			case 2:
				{pin(1,zero);pin(5,zero);break;}
			case 3:
				{pin(0,zero);pin(6,zero);pin(4,zero);break;}
			case 4:
				{pin(1,zero);pin(3,zero);pin(5,zero);pin(7,zero);break;}
			case 5:
				{pin(8,zero);pin(2,zero);pin(4,zero);break;}
			case 6:
				{pin(3,zero);pin(7,zero);break;}
			case 7:
				{pin(6,zero);pin(8,zero);pin(4,zero);break;}
			case 8:
				{pin(7,zero);pin(5,zero);break;}
		}
		
	}
	
	return (0);
}

void pin(int in,int zero)//dicide judge or not
{
	int i;
	for(i = 0; i < 9; i++)
	{
		if(i == in)
		{
			at2[i] = at1[zero];
		}
		else if(i == zero)
		{
			at2[i] = at1[in];
		}
		else
		{
			at2[i] = at1[i];
		}
	}
	
	int s;
	s = cantor(at2);
//	if(s > 326890)
//	{
//		for(i = 0; i < 9; i++) cout<<at2[i];
//		cout<<' '<<s<<endl;
//	}
	if(map[s] == -1)
	{
		next.push(s);
		lev.push(l + 1);
	}
}

int cantor(int in[])//canter expansion
{
	int i, j;
	int a[9];
	memset(a,0,sizeof(a));
	
	for(i = 0; i < 9; i++)
	{
		for(j = i; j < 9; j++)
		{
			if(in[j] < in[i]) a[i]++;
		}
	}
	
	int s(0);
	for(i = 0; i < 9; i++)
	{
		s += a[i] * jc[8-i];
	}
	
	return s;
}

void rcantor(int in, int a[])//alter canter
{
	int lown(0);
	int i, j;
	int use[9] = {0}; 
	for(i = 0; i < 9; i++)
	{
		
		lown = in / jc[8 - i];
		in -= jc[8 - i] * lown;
		
		int t(0);
		for(j = 0; j < 9; j++)
		{
			if(lown == t && use[j] == 0)
			{
				a[i] = j;
				use[j] = 1;
				break;
			}
			else if(use[j] == 0)
			{
				t++;
			}
		}
	}
}








