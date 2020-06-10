/* ************************************************************************
 *       Filename:  mmanager.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2020年06月09日 13时54分35秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  YOUR NAME (荆 明), 
 *        Company:  
 * ************************************************************************/

#include "mmanager.h"

MM::MM(int num , int blocksize){
	//初始化内存管理节点
	if(num<=0 || blocksize<=0){
		printf("input err\n");
		exit(1);
	}
	//分配初始内存管理空间
	this->pMmanager=(mmanager*)malloc(sizeof(mmanager));
	if(NULL == this->pMmanager){
		printf("malloc err\n");
		exit(1);
	}
	//将mmanager清零
	memset(this->pMmanager,0,sizeof(mmanager));
	this->pMmanager->count = num;
	this->pMmanager->blocksize = blocksize;
	
	//申请第一个内存块
	memblock* temp1 = NULL;  //用于保存节点地址
	memblock* temp2 = NULL;  //temp2用于备份temp1的值
	char* block;             //block中指向内存块的指针
	int n = 0;				//链表节点初始为0
	

	temp1 = (memblock*)malloc(LEN); //申请第一个block
	if(temp1 == NULL){
		printf("temp1%d malloc err\n",n+1);
		exit(1);
	}
	memset(temp1,0,LEN);
	
	block = (char*)malloc(blocksize); //开辟内存块
	if(block == NULL){
		printf("first block malloc err \n");
		exit(1);
	}
	memset(block,0,blocksize);
	temp1->pMem = block;
	temp1->blocknum = 0;  //块编号从0开始
	this->pMmanager->firstaddr = block;
	temp2 = temp1;
	
	//继续增加block
	while(n< num){
		
			n = n+1;  //n此时表示第几个块
			if(n==1){	//如果只有一个节点，将链表头指向block1
				this->pMmanager->pHead = temp1;
				temp2->pNext = NULL;
			}
			else{
				temp2->pNext = temp1;
			} 
			temp2 = temp1;
			//temp1用于创建，temp2用于保存上次的节点地址
			temp1 = (memblock*)malloc(LEN);  //新block
			if(temp1 == NULL){
				printf("temp1 %d malloc err\n",n+1);
				exit(1);
			}
			
			memset(temp1,0,LEN);

			block = (char*)malloc(blocksize);

			if(NULL == block){
				printf("block %d malloc err\n",n+1);
				exit(1);
			
			}


			memset(block,0,blocksize);
			temp1->pMem = block;
			temp1->blocknum = n-1;
			
	}

	temp2->pNext = NULL;
	this->pMmanager->lastaddr = temp2->pMem+blocksize;

	free(temp1);
	temp1 = NULL;
}

MM::~MM(){
	//销毁内存块和内存管理
	if(this->pMmanager == NULL){
		printf("Destroy memery ok");
	}
	memblock* p1 = this->pMmanager->pHead;
	memblock* p2 = p1;
		
	while(p1!=NULL){
		p2=p1;
		p1 = p1->pNext;
		free(p2->pMem);
		p2->pMem = NULL;
		free(p2);
	}
	this->pMmanager->pHead = NULL;
	this->pMmanager->pHead2 = NULL;
	free(this->pMmanager);
	this->pMmanager = NULL;
}

memblock*  MM::Getblock(){
	if((this->pMmanager)==NULL) return NULL;
	if(this->pMmanager->usedCount == this->pMmanager->count){
		printf("get block err ! pool Full\n");
		return NULL;
	}	
	if(this->pMmanager== NULL || this->pMmanager->pHead == NULL){
		printf("pool empty\n");
		return NULL;
	}
	memblock* p = this->pMmanager->pHead;
	this->pMmanager->pHead = p->pNext;
	p->pNext= NULL;
	this->pMmanager->usedCount++;
	return p;
}

int MM::Releaseblock(memblock* pmemblock){
	if( pmemblock == NULL){
		printf("have no memeryblock\n");
		return ERR;
	}
	if( pmemblock->pMem == NULL){
		printf("have no memory space \n");
		return ERR;
	}
	free(pmemblock->pMem);
	free(pmemblock);
	return OK;  //OK代表释放成功

}
