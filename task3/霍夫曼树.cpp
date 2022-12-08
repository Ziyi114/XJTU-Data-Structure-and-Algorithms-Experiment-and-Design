//霍夫曼树.cpp : 此文件包含 "main、weigh、Select、HuffmanCoding、PutCode、HuffmanDeCoding" 函数。程序执行将在此处开始并结束。
//该程序用于对输入字符进行霍夫曼编码，输出密码，遍历霍夫曼树并对给定的密码进行解码并输出

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

//动态分配数组存储霍夫曼树
typedef struct
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
	unsigned int status;//在Select函数调用结点后改变，用以显示是否被调用
}HTNode, * HuffmanTree;

//动态分配数组存储霍夫曼编码表
typedef char** HuffmanCode;

//用来对字符中各字符所占权值进行求解
void weigh(char* s, char** letters, unsigned int& n, unsigned int** Weight, unsigned int lenth)
{
    int i = 0, j = 0, k = 0;//循环变量
	char* L = (char*)malloc((lenth + 1) * sizeof(char));//暂时存储字符串中出现过的字符
	unsigned int* W = (unsigned int*)malloc((lenth + 1) * sizeof(unsigned int)); //暂时存储字符串中出现过的字符的权重
	L[0] = '0';		//0号位置空
	W[0] = 0;
	n = 0;
	for (i = 0; i < lenth; i++)
	{
		k = 0;
		for (j = 1; j <= n; j++)//检索当前字符是否出现过
		{
			if (s[i] == L[j])
			{
				W[j]++;
				k = 1;
				break;//若出现过，权值+1，检索下一字符
			}
		}
		if (k == 0)//若未出现过，加入L中，对应权值为1
		{
			n++;
			L[n] = s[i];
			W[n] = 1;
		}
	}
	if (!*Weight)
		* Weight = (unsigned int*)malloc(n * sizeof(unsigned int));
	if (!*letters)
		* letters = (char*)malloc(n * sizeof(char));
	char c;
	int pos = 1;
	for (i = 0; i < n; i++)//依次从L中取出ASCII最小的字符和对应权值
	{
		for (c = L[pos], j = 1; j <= n; j++)
		{
			if ((int)L[j] < (int)c)
			{
				c = L[j];
				pos = j;
			}
		}
		(*letters)[i] = L[pos];
		(*Weight)[i] = W[pos];
		L[pos] = (char)127;//已取出的字符替换为ASCII的最大值127
	}
	free(L); 
	free(W);//结束后释放空间
}

//用以选出parent为0的weight最小的两个结点s1，s2
void Select(HuffmanTree& HT, unsigned int pos, unsigned int& s1, unsigned int& s2)
{
	unsigned int i = 1, k = 1, temp = 0;
	for (i = 1; i <= pos && k <= 2; i++)
	{
		if (HT[i].parent == 0)
		{
			if (k == 1)
			{
				s1 = i; k++;
			}
			else
			{
				s2 = i; k++;
			}
		}
	}
	if (HT[s1].weight > HT[s2].weight)
	{
		temp = s1;
		s1 = s2;
		s2 = temp;
	}
	while (i <= pos)
	{
		if (HT[i].parent == 0)
			if ((HT[i].weight < HT[s2].weight) && (HT[i].weight < HT[s1].weight) && i != s1 && i != s2)
			{
				s2 = s1; s1 = i;
			}
			else if ((HT[i].weight < HT[s2].weight) && (HT[i].weight >= HT[s1].weight) && i != s1 && i != s2)
				s2 = i;
		++i;
	}
}

//建立霍夫曼树并求编码
void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, unsigned int& n, unsigned int* Weight)
{
	//建立霍夫曼树
	HuffmanTree  p = NULL;
	unsigned int m = 0, s1 = 0, s2 = 0, i = 0;
	if (n <= 1)//如果字符串有一个字符重复构成，无法编码
	{
		printf("ERROR_02");
		exit(-1);
	}
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++Weight)
		* p = { *Weight,0,0,0,0 };
	for (; i <= m; ++i, ++p)
		* p = { 0,0,0,0,0 };
	for (i = n + 1; i <= m; ++i)
	{
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	//无栈非递归遍历霍夫曼树，求霍夫曼编码
	char* cd = (char*)malloc(n * sizeof(char));
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	unsigned x = m, cdlen = 0;
	int k = 0;
	for (i = 1; i <= m; ++i) 
		HT[i].status = 0;
	while (x)
	{
		if (HT[x].status == 0)
		{
			if (HT[x].lchild) k = 2;
			else k = 0;
			printf("%d %d %d\n", HT[x].weight, cdlen + 1, k);
			HT[x].status = 1;
			if (HT[x].lchild != 0)
			{
				x = HT[x].lchild;
				cd[cdlen++] = '0';
			}
			else if (HT[x].rchild == 0)
			{
				HC[x] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				HT[x].status = 2;
				strcpy_s(HC[x], cdlen + 1, cd);
			}
		}
		else if (HT[x].status == 1)
		{
			HT[x].status = 2;
			if (HT[x].rchild != 0)
			{
				x = HT[x].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{
			HT[x].status = 0;
			x = HT[x].parent;
			--cdlen;
		}
	}
}

//该函数用于输出密码
void PutCode(char* s, char* letter, HuffmanCode& HC, unsigned int lenth, unsigned int n)
{
	unsigned int i = 0, j = 0;
	for (i = 0; i < lenth; i++)
		for (j = 0; j <= n; j++)
			if (s[i] == letter[j])
			{
				printf("%s", HC[j + 1]);
				break;
			}
	printf(" ");
}

//该函数用于霍夫曼树的解码
void HuffmanDeCoding(char* s, HuffmanTree& HT, char* letter, unsigned int n)
{
	int x = 2 * n - 1, last = 0, i = 0, lenth = strlen(s);
	while (*s)
	{
		if (*s == '0')	x = HT[x].lchild;
		else if (*s == '1')  x = HT[x].rchild;
		else { printf("\nERROR_03"); exit(-1); }//码文中有非0，1的数字，译码错误

		if (HT[x].lchild == 0)
		{
			printf("%c", letter[x - 1]);
			last = x;
			x = 2 * n - 1;
		}
		s++;
	}
	if (HT[last].lchild != 0)
	{
		printf("\nERROR_03");
		exit(-1);
	}//码文最后几位不代表一个字符，译码错误
}

int main(int argc, char* argv[])
{
	if (!(argc == 3))//检查命令行参数输入
	{
		printf("ERROR_01");
		return -1;
	}
	HuffmanTree HT = NULL;
	HuffmanCode HC = NULL;
	char* letter = NULL;                         //letter字符数组按ASCII码升序存储字符串中出现的字符
	unsigned int* Weight = NULL;                //Weight数组中对应存储letter中字符的权值
	unsigned int lenth = strlen(argv[1]);
	unsigned int n = 0;                        //n为字符数组按ASCII码升序存储字符串中出现的字符的个数
	if (lenth < 20)                           //检查字符串长度
	{
		printf("ERROR_02");
		return -1;
	}
	weigh(argv[1], &letter, n, &Weight, lenth);
	HuffmanCoding(HT, HC, n, Weight);
	PutCode(argv[1], letter, HC, lenth, n);
	HuffmanDeCoding(argv[2], HT, letter, n);

	free(letter); free(Weight); free(HT); free(HC);
	return 1;
}