#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<queue>
#include<functional>
using namespace std;

#define SIZE 8
typedef unsigned int WeightType;
#define NIL -1

struct HaffNode
{
	WeightType weight;
	int        parent;
	int        leftchild;
	int        rightchild;
};

typedef HaffNode HaffManTree[SIZE * 2];
struct HaffCode
{
	char ch;
	char code[SIZE + 1];
};

typedef HaffCode HaffCoding[SIZE + 1];

void Init_HaffTree(HaffManTree hft)//初始化哈夫曼树
{
	for (int i = 0; i<SIZE * 2; ++i)
	{
		hft[i].weight = NIL;
		hft[i].parent = 0;
		hft[i].leftchild = 0;
		hft[i].rightchild = 0;
	}
	for (int i = 1; i <= SIZE; ++i)
	{
		cin >> hft[i].weight;
	}
}

/*求出权值最小的两个值*/
bool Get2Min(HaffManTree hft, int n, int& index1, int& index2)
{
	int i = 1;
	while (i<n && hft[i].parent != 0) ++i;
	if (i == n) return false;
	for (int j = i + 1; j<n; ++j)
	{
		if (hft[j].parent == 0 && hft[i].weight > hft[j].weight)
		{
			i = j;
		}
	}
	index1 = i;
	hft[i].parent = -1;

	i = 1;
	while (i<n && hft[i].parent != 0) ++i;
	if (i == n) return false;
	for (int j = i + 1; j<n; ++j)
	{
		if (hft[j].parent == 0 && hft[i].weight > hft[j].weight)
		{
			i = j;
		}
	}
	index2 = i;
	hft[i].parent = -1;
	return true;
}


void Create_HaffTree(HaffManTree hft)
{
	struct IndexNode
	{
		int index;
		WeightType w;
		operator WeightType()  const { return w; }
	};

	priority_queue<IndexNode, vector<IndexNode>, greater<IndexNode> > q2min;
	for (int i = 1; i <= SIZE; ++i)
	{
		IndexNode x = { i,hft[i].weight };
		q2min.push(x);
	}
	int k = SIZE + 1;
	while (k < SIZE * 2)
	{
		if (q2min.empty()) break;
		IndexNode m1 = q2min.top(); q2min.pop();
		if (q2min.empty()) break;
		IndexNode m2 = q2min.top(); q2min.pop();
		hft[k].weight = hft[m1.index].weight + hft[m2.index].weight;
		hft[k].leftchild = m1.index;
		hft[k].rightchild = m2.index;
		hft[m1.index].parent = k;
		hft[m2.index].parent = k;
		IndexNode x = { k,hft[k].weight };
		q2min.push(x);
		++k;
	}


	/*
	int index1,index2;
	int i = SIZE+1;
	while(i<SIZE*2)
	{
	if(!Get2Min(hft,i,index1,index2))
	break;
	hft[i].weight = hft[index1].weight + hft[index2].weight;
	hft[i].leftchild = index1;
	hft[i].rightchild = index2;
	hft[index1].parent = i;
	hft[index2].parent = i;
	++i;
	}*/
	/**/
}
void Print_HaffTree(HaffManTree hft)
{
	for (int i = 1; i<SIZE * 2; ++i)
	{
		cout << setw(3) << i;
		cout << setw(4) << hft[i].weight;
		cout << setw(4) << hft[i].parent;
		cout << setw(4) << hft[i].leftchild;
		cout << setw(4) << hft[i].rightchild << endl;
	}
	cout << endl;
}

void Init_HaffCode(HaffCoding hc)
{
	for (int i = 0; i<SIZE + 1; ++i)
	{
		hc[i].ch = '\0';
		memset(hc[i].code, 0, sizeof(char)*(SIZE + 1));
	}
	for (int i = 1; i<SIZE + 1; ++i)
	{
		cin >> hc[i].ch;
	}
}

void Print_HaffCode(HaffCoding hc)
{
	for (int i = 1; i<SIZE + 1; ++i)
	{
		cout << hc[i].ch << "-> " << hc[i].code << endl;
	}
	cout << endl;
}
void Create_HaffCode(HaffManTree hft, HaffCoding hc)
{
	char code[SIZE + 1];
	for (int i = 1; i <= SIZE; ++i)
	{
		int c = i;
		int pa = hft[c].parent;
		int k = SIZE;
		code[k] = '\0';
		while (pa != 0)
		{
			code[--k] = hft[pa].leftchild == c ? '1' : '0';
			c = pa;
			pa = hft[c].parent;
		}
		strcpy(hc[i].code, &code[k]);
	}
}
void main()
{
	/*测试用例：6 11 45 35 24 12 19 10
	A  B  C  D  E  F  G  H */
	HaffManTree hft;
	HaffCoding hc;
	Init_HaffTree(hft);
	Init_HaffCode(hc);
	Create_HaffTree(hft);
	Print_HaffTree(hft);

	Create_HaffCode(hft, hc);
	Print_HaffCode(hc);
}
