/*��Ŀ��
�㷨�����ݽṹʵ���� 2.7 ���һ����������
��ʵ������
���Ϊ1 - n�� n ���˰�˳ʱ�뷽��Χ��һȦ���ӵ�һ���˿�ʼ��˳ʱ�뷽���� 1 ��ʼ���������� m ʱֹͣ���ڱ��� m ���Ǹ��˵����ҵ������˳��У�������˳ʱ�뷽����һ���˿�ʼ���´� 1 �����������ȥ�����������Ϸ���������� 3 ��������Ϸ��ֹ����һ�������������������˱��
����������
�����һ��Ϊ T ���������ȥ�� T ����ԣ� 0 < T < =10
����ȥ T �У�ÿ������������ n �� m�� 0 < n��m < =1000
���������
����ÿ�����룬��һ�������������������˱�ţ�����������������������ÿո������������С��������  
*/
/*ʹ��ѭ��˫������
��Ҫbug���ھ���header��ʱ��
��code��������header�����ķ���*/
#include<stdio.h>
#include<stdlib.h>
typedef int ListItem;
typedef struct node *link;//˫������ָ������
/*˫����������*/ 
typedef struct node{
	ListItem element;//����Ԫ�� 
	link left,right;//��ڵ㡢�ҽڵ� 
}Node;
link NewNode(){
	return (link)malloc(sizeof(Node));
}
void ItemShow(ListItem x){
	printf("%d ",x);
}
/*ѭ��˫����ṹ*/
typedef struct dlist *List;//ѭ��˫����ָ������
typedef struct dlist{
	int n;//��
	link header,curr;//����ָ�룬��ǰ���
}Dlist;
/*����ѭ��˫����*/
List ListInit(){
	List L = (List)malloc(sizeof *L);
	link y = NewNode();
	y->left = y;
	y->right = y;
	L->header = y;
	L->n=0;
	return L;
}
/*�ӵ�һ��Ԫ�ؿ�ʼ���ɨ�裬ֱ���ҵ���k��Ԫ��*/
ListItem ListRetrieve(int k,List L){
	if(k<1||k>L->n)exit(1);//Խ��
	if(k==L->n)return L->header->left->element;
	link p=L->header->right;
	int i;
	for(i=1;i<k;i++)p=p->right;
	return p->element; 
}
/*����ɨ���ֱ���ҵ�Ԫ��x*/
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
/*����Ԫ��*/
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
/*ɾ��Ԫ��*/
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
/*�����*/
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
				}//����header
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
