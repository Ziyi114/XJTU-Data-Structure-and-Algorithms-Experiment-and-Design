// 无向图最短路径.cpp : 此文件包含 "main、reverse、shortpath、path、expo" 函数。程序执行将在此处开始并结束。
//该程序用于给定两个地点，求出两点间最短路程，并输出

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  MAX	13   //有13个顶点
#define  INF   1000

//定义图的结构
typedef struct {
	char   	    vexs[MAX];               //顶点数组
	int	       	adj[MAX][MAX];           //邻接矩阵
	int 		vexnum = 13;             //顶点数
	int 		arcnum = 18;             //边数
} graph;

int pa[MAX];         //保存最短路

//该函数用于求解两点间最短路径
int shortpath(graph m, char start, char terminal) 
{
	int i, k;
	int min;
	int u = 0;
	int dist[13];   //  最短路径
	int mark[13];   //   标记数组
	for (i = 0; i < m.vexnum; i++)
	{
		mark[i] = 0;
		dist[i] = m.adj[start][i];
	}
	dist[start] = 0;
	mark[start] = 1;          // 标记起点
	for (k = 0; k < m.vexnum; k++) 
	{
		min = INF;
		for (i = 0; i < m.vexnum; i++) 
		{
			if (mark[i] == 0 && min > dist[i]) 
			{
				min = dist[i];
				u = i;
			}
		}
		mark[u] = 1;      //标记u点        
		for (i = 0; i < m.vexnum; i++) 
		{
			if (mark[i] == 0 && dist[i] > dist[u] + m.adj[u][i]) 
			{
				pa[i] = u;
				dist[i] = dist[u] + m.adj[u][i];      //更新
			}
		}
	}
	return dist[terminal];
}

//该函数用于将汉字转化为数字
int reverse(char* x)
{
	char a[10] = "北门", b[10] = "饮水思源", c[10] = "传送门3", d[10] = "传送门1";
	char e[10] = "腾飞塔", f[10] = "传送门4", g[10] = "图书馆", h[10] = "传送门2";
	char i[10] = "宪梓堂", j[10] = "教学主楼", k[10] = "西迁馆", l[10] = "活动中心", m[10] = "南门";//定义字符串将各个地点定义出
	if (strcmp(a, x) == 0) return 0;
	else if (strcmp(b, x) == 0) return 1;
	else if (strcmp(c, x) == 0) return 2;
	else if (strcmp(d, x) == 0) return 3;
	else if (strcmp(e, x) == 0) return 4;
	else if (strcmp(f, x) == 0) return 5;
	else if (strcmp(g, x) == 0) return 6;
	else if (strcmp(h, x) == 0) return 7;
	else if (strcmp(i, x) == 0) return 8;
	else if (strcmp(j, x) == 0) return 9;
	else if (strcmp(k, x) == 0) return 10;
	else if (strcmp(l, x) == 0) return 11;
	else if (strcmp(m, x) == 0) return 12;
	else return 13;
}

//该函数用于将数转化为汉字并输出
void expo(int num)
{
	switch (num)
	{
	case 0:
		printf("北门");
		break;
	case 1:
		printf("饮水思源");
		break;
	case 2:
		printf("传送门3");
		break;
	case 3:
		printf("传送门1");
		break;
	case 4:
		printf("腾飞塔");
		break;
	case 5:
		printf("传送门4");
		break;
	case 6:
		printf("图书馆");
		break;
	case 7:
		printf("传送门2");
		break;
	case 8:
		printf("宪梓堂");
		break;
	case 9:
		printf("教学主楼");
		break;
	case 10:
		printf("西迁馆");
		break;
	case 11:
		printf("活动中心");
		break;
	case 12:
		printf("南门");
		break;
	}
}

//该函数用于求出最短路径
void path(int v0, int v1)       //v0出发，v1终点
{
	void expo(int a);
	int j;
	int  p2[100] = { 0 };
	int t = 0, k;
	j = v1;
	while (pa[j] != -1) 
	{
		p2[t++] = pa[j];
		j = pa[j];
	}
	expo(v0);
	printf("->");
	for (k = t - 1; k >= 0; k--) 
	{
		expo(p2[k]);
		printf("->");
	}
	expo(v1);
}

int main(int argc, char* argv[])
{
	if (argc != 3) 
	{
		printf("ERROR_01");
		return 0;
	}//如果命令行参数错误，返回，并输出ERROR_01
	graph m;
	int i, j;
	for (i = 0; i < MAX; i++) 
	{
		m.vexs[i] = i + 1;
	}
	for (i = 0; i < MAX; i++) 
	{
		for (j = 0; j < MAX; j++) 
		{
			if (i == j) 
			{
				m.adj[i][j] = 0;
			}
			else m.adj[i][j] = INF;
		}
	}
	m.adj[0][1] = m.adj[1][0] = 18;
	m.adj[0][2] = m.adj[2][0] = 22;
	m.adj[1][4] = m.adj[4][1] = 19; 
	m.adj[1][3] = m.adj[3][1] = 27;
	m.adj[2][4] = m.adj[4][2] = 4;
	m.adj[3][6] = m.adj[6][3] = 4;
	m.adj[4][5] = m.adj[5][4] = 32;
	m.adj[4][6] = m.adj[6][4] = 23;
	m.adj[5][8] = m.adj[8][5] = 4;
	m.adj[6][7] = m.adj[7][6] = 4;
	m.adj[6][9] = m.adj[9][6] = 15;
	m.adj[7][12] = m.adj[12][7] = 21;
	m.adj[7][10] = m.adj[10][7] = 43;
	m.adj[8][9] = m.adj[9][8] = 8;
	m.adj[8][12] = m.adj[12][8] = 14;
	m.adj[9][11] = m.adj[11][9] = 21;
	m.adj[10][12] = m.adj[12][10] = 20;
	m.adj[11][12] = m.adj[12][11] = 30;//对邻接矩阵赋值
	int ch1, ch2;
	int length;
	ch1 = reverse(argv[1]);
	ch2 = reverse(argv[2]);
	for (i = 0; i < MAX; i++) 
	{
		pa[i] = -1;
	}
	if (ch1 != 13 && ch2 != 13) 
	{       //判断输入的参数是否为顶点
		length = shortpath(m, ch1, ch2);
		path(ch1, ch2);
		printf("\n%d", length);
	}
	else printf("ERROR_02");
	return 0;
}