/* ************************************************************************
 *       Filename:  mmanager.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2020年06月09日 12时50分00秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  YOUR NAME (荆 明), 
 *        Company:  
 * ************************************************************************/

#ifndef MMANAGER_H
#define MMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define blockSize sizeof(memblock)


typedef struct node{
	char* pMem;
	struct node* pNext;

}memblock;

typedef struct node2{
		int count ; //block个数
		int usedCount ; //使用的block个数
		int blocksize ; //内存块的大小
		char* firstaddr; //开始地址
		char* lastaddr ; //结束地址
		memblock* pHead ; //链表头
		memblock* pTail ; //链表尾
}mmanager;

class MM{
	public:
		MM(int num,int blocksize); //构造函数中创建内存池
		~MM();//析构函数中销毁内存池
	public:
		mmanager * pMmanager;
		char* Getblock(mmanager** pMmanager);
		int Releaseblock(mmanager** pMmanager);
		
};


#endif


