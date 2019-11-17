#include<stdio.h>
#define infinity 999
void dijkstra(int n,int cost[100][100],int s[100],int p[100],int d[100],int src,int dest)
{
	int i,j,u,v,min;	
	for(i=0;i<n;i++)
	{
		d[i]=cost[src][i];
		p[i]=src;
		s[i]=0;
	}
	s[src]=1;
	for(i=0;i<n;i++)
	{
		u=-1;
		min=999;
		for(j=0;j<n;j++)
		if(s[j]==0 && (d[j]<min))
		{
			min=d[j];
			u=j;
		}
		if(u==-1)return;
		if(u==dest)return;
		s[u]=1;
		for(v=0;v<n;v++)
		if(s[v]==0 && (d[u]+cost[u][v]<d[v]))
		{
			d[v]=cost[u][v]+d[u];
			p[v]=u;
		}
	}	
}
void main()
{
	int n,cost[100][100],src,dest,i,j,s[100],p[100],d[100];
	printf("Enter the number of vertices\n");
	scanf("%d",&n);
	printf("Enter the adjacency matrix\n");
	printf("Enter 999 for no edge\n");
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	scanf("%d",&cost[i][j]);
	printf("Enter source node\n");
	scanf("%d",&src);
	for(dest=0;dest<n;dest++)
	{
		dijkstra(n,cost,s,p,d,src,dest);
		if(d[dest]==999)
		printf("\nNode %d is not reachable from %d",src,dest);
		else
		{
			printf("\nThe path from %d to %d is ",src,dest);
			i=dest;
			while(i!=src)
			{
				printf("%d<-",i);
				i=p[i];
			}
			printf("%d",i);
			printf("\nDistance = %d\n",d[dest]);
		}
	}
}
