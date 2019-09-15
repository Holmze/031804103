/*题目：
算法与数据结构实验题 2.7 大家一起来报数Ⅱ
★实验任务
编号为1 - n的 n 个人按顺时针方向围坐一圈，从第一个人开始按顺时针方向自 1 开始报数，报到 m 时停止，在报到 m 的那个人的左右的两个人出列，从他在顺时针方向下一个人开始重新从 1 报数，如此下去。如果还在游戏的人数少于 3 个，则游戏终止。在一行内输出最后留下来的人编号
★数据输入
输入第一行为 T ，代表接下去有 T 组测试， 0 < T < =10
接下去 T 行，每行两个数代表 n 和 m， 0 < n，m < =1000
★数据输出
对于每个输入，在一行内输出最后留下来的人编号，如果有两个人留下来，则用空格隔开，并按从小到大排序。  
*/
/*使用循环双链表解决
主要bug出在经过header的时候
本code采用了遇header跳过的方法*/
#include<stdio.h>
#include<stdlib.h>
typedef int ListItem;
typedef struct node *link;//双链表结点指针类型
/*双链表结点类型*/ 
typedef struct node{
	ListItem element;//表中元素 
	link left,right;//左节点、右节点 
}Node;
link NewNode(){
	return (link)malloc(sizeof(Node));
}
void ItemShow(ListItem x){
	printf("%d ",x);
}
/*循环双链表结构*/
typedef struct dlist *List;//循环双链表指针类型
typedef struct dlist{
	int n;//表长
	link header,curr;//表首指针，当前结点
}Dlist;
/*创建循环双链表*/
List ListInit(){
	List L = (List)malloc(sizeof *L);
	link y = NewNode();
	y->left = y;
	y->right = y;
	L->header = y;
	L->n=0;
	return L;
}
/*从第一个元素开始向后扫描，直至找到第k个元素*/
ListItem ListRetrieve(int k,List L){
	if(k<1||k>L->n)exit(1);//越界
	if(k==L->n)return L->header->left->element;
	link p=L->header->right;
	int i;
	for(i=1;i<k;i++)p=p->right;
	return p->element; 
}
/*线性扫描表，直至找到元素x*/
int ListLocate(ListItem x,List L){
	int i = 1;
	link p = L->header->right;
	L->header->element = x;
	while(p->element!=x){
		p=p->right;
		i++;
	}
	return((p==L->header)?0:i);
} 
/*插入元素*/
void ListInsert(int k,ListItem x,List L){
	if(k<0||k>L->n)exit(1);
	link p = L->header;
	if(k==L->n)p = L->header->left;
	else{
		int i;
		for(i=1;i<k;i++)p=p->right;
	}
	link y = NewNode();
	y->element = x;
	y->left = p;
	y->right = p->right;
	p->right->left = y;
	p->right = y;
	L->n++;
}
/*删除元素*/
ListItem ListDelete(int k,List L){
	if(k<1||k>L->n)exit(1);
	link p = L->header;
	if(k==L->n)p = L->header->left;
	else {
		int i;
		for(i=1;i<=k;i++)p = p->right;
	}
	p->left->right = p->right;
	p->right->left = p->left;
	ListItem x = p->element;
	free(p);
	L->n--;
	return x;
}
/*输出表*/
void PrintList(List L){
	link p;
	for(p=L->header->right;p!=L->header;p=p->right)ItemShow(p->element);
}
int main(){
	int T,n[10],m[10],i,j;
	scanf("%d",&T);
	for(i=0;i<T;i++){
		scanf("%d %d",&n[i],&m[i]);
	}
	for(j=0;j<T;j++){
		List L = ListInit();
		L->header->element=-1;
		//printf("%d",L->header->right->left->element);
		for(i=0;i<n[j];i++){
			ListInsert(i,i+1,L);
		}
		link p=L->header;
		for(;L->n>=3;){
			for(i=0;i<m[j];i++){
				p=p->right;
				int flag = p->element;
				//printf("flag = %d,left is %d,right is%d\n",flag,p->left->element,p->right->element);
				if(p->element==L->header->element){
					p=p->right;
				//	printf("jump header\n");
				}//跳过header
			}
			
			int kleft,kright;
			
			kleft = p->left->element;
			//printf("*1 ");
			int left_lacate=ListLocate(kleft,L);
			if(left_lacate==0) left_lacate = L->n;
			//printf("left_element=%d,left_locate=%d ",kleft,left_lacate);
			ListDelete(left_lacate,L);
			//printf("*2 ");
			
			kright = p->right->element;
			//printf("*3 ");
			int right_lacate=ListLocate(kright,L);
			if(right_lacate==0) right_lacate =1;
			//printf("right_element=%d,right_locate=%d ",kright,right_lacate);
			ListDelete(right_lacate,L);
			//printf("*4 \n");
			
			//printf("now p is %d,delete %d and %d\n",p->element,kleft,kright);
			//printf("now p is %d,delete %d and %d\n",p->element,ListRetrieve(ListLocate(kleft,L),L),ListRetrieve(ListLocate(kright,L),L));
			//printf("%d",ListRetrieve(ListLocate(kleft,L),L)==kleft);
		}
		PrintList(L);
		printf("\n");
	}
	return 0;
}
