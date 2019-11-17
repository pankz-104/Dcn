#include<stdio.h>
#include<stdlib.h>
#define bktsz 700
int c = 0;
int count = 0;
void bktip (int a,int b,int i)
{
	if(a>bktsz-c)
	{
		printf("bucket overflow and non-conforming packet\n");
	}
	else
	{
		sleep(1);
		while(a>b)
		{
			printf("%d bytes outputted\n",b);
			a = a-b;
			sleep(1);
			count ++;
		}
		if(a>0)
		{
			c = c+a;
			if(count == 0)
			{
				printf("last %d bytes outputted\n",c);
				c = 0;
				printf("%d byte stored\n",c);
			}
			else{
				if(c==b)
				{
					printf("%d bytes stored is outputted\n",b);
					c = 0;	
				}
				if(c>b)
				{	
					printf("%d bytes stored is outputted\n",b);
					c = c-b;
					printf("%d bytes stored\n",c);
				}
				else
					printf("%d bytes stored\n",c);	
					printf("coinforming packet");
			}
		}
		if((i==5) && (c!=0))
		{
			printf("%d bytes stored is outputted\n",c);
		}
	}
}
int main()
{
	int opr,psz,i;
	printf("output rate:\n");
	scanf("%d",&opr);
	for(i=1;i<=5;i++)
	{
		printf("enter the packet size:\n");
		scanf("%d",&psz);
		printf("packet number %d packet size %d\n",i,psz);
		bktip(psz,opr,i);
	}
}


