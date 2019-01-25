#include<stdio.h>
int main()
{
	int i,number[10]={0},max,n;
	char ch;
	while((ch=getchar())!='\n')
	{
		i=ch-48;
		number[i]++;
	}
	max=number[9];
	for(i=8;i>=0;i--)
	{
		if(max<number[i])
		{
			max=number[i];
		}
		else
		{
			max = max;
		}
	}
	for(;max>0;max--)
	{
		for(i=9;i>=0;i--)
		{
			if(number[i]==max)
			{
			 	while(number[i]--)
				{
					printf("%d",i);
				}
			}
			else continue;
		}
	}
	return 0;
}
