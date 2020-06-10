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

#define LEN sizeof(memblock)

#define OK 1     //操作成功
#define ERR 0	 //操作失败

typedef struct node{
	int blocknum;  //内存块的编号
	char* pMem;	//指向内存块存储空间的指针
	struct node* pNext;     //此类型节点的指针

}memblock;

typedef struct node2{
		int count ; //block个数
		int usedCount ; //已使用的block个数
		int blocksize ; //每个内存块对应的存储空间的大小
		char* firstaddr; //块起始地址
		char* lastaddr ; //块结束地址
		memblock* pHead ; //链表头用于写入数据
		
}mmanager;

class MM{
	public:
		MM(int num,int blocksize); //构造函数中创建内存池
		~MM();//析构函数中销毁内存池
	public:
		mmanager * pMmanager;
		memblock* Getblock();
		int Releaseblock(memblock* pmemblock);
		
};


#endif


