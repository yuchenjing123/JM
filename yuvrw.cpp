/* ************************************************************************
 *       Filename:  yuvwr.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2020年06月09日 09时11分50秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  YOUR NAME (荆 明), 
 *        Company:  
 * ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>
#include <stdio.h>
using namespace std;

#define ImageSize 76032*2
typedef struct node{
	int blocknum;
	char* pMem;
	struct node* pNext;
}memblock;

//获取输入目录下文件的个数
int getdir_filenum()
{
	int n=0;
	DIR* pdir;
	dirent* pdirent;
	pdir = opendir("./input");
	
	while((pdirent = readdir(pdir))!=NULL){
		if(strcmp(pdirent->d_name,".")==0||strcmp(pdirent->d_name,"..")==0) continue;
			n++;
		}
	closedir(pdir);
	return n;
}

//此函数可以获得线程的调度策略
static int get_thread_policy(pthread_attr_t& attr){
	int policy;  //用来接收调度策略
	int rs = pthread_attr_getschedpolicy(&attr,&policy);
	assert(rs==0);
	switch(policy){
		case  SCHED_FIFO:
			cout<< "policy=FIFO"<<endl;
			break;
		case  SCHED_RR:
			cout<< "policy = SCHED_RR"<< endl;
			break;
		case  SCHED_OTHER:
			cout << "policy = SCHED_OTHER"<< endl;
			break;
		default :
			cout <<"policy = UNKNOW"<< endl;
			break;
	}
	return policy;
}

//设置线程调度策略
static void set_thread_policy(pthread_attr_t& attr,int policy){
	int rs = pthread_attr_setschedpolicy(&attr,policy);
	assert(rs == 0);
	get_thread_policy(attr);
}

//获取文件大小
long filesize(FILE* pFile){
	long curpos,length;
	curpos = ftell(pFile);
	fseek(pFile,0L,SEEK_END);
	length = ftell(pFile);
	fseek(pFile,curpos,SEEK_SET);
	return length;
}

//读取input线程
static void* r_thread(void* arg){
	//解析线程参数
	memblock* p = (memblock*)arg;
	printf("rthread start\n");
	cout<< "开始读取yuv文件" <<endl;

	//修改线程调度策略为先进先出模式
	pthread_attr_t attr;
	get_thread_policy(attr);	
	set_thread_policy(attr,SCHED_FIFO);
	//从./input文件夹读取数据2.yuv并且写入block
	DIR* pdir;
	dirent* pdirent;
	pdir = opendir("./input/");
	char str[80]={0};
	//打开文件后开始读数据，并写入存储空间
	while((pdirent = readdir(pdir))!=NULL){
		if(strcmp(pdirent->d_name,".")==0||strcmp(pdirent->d_name,"..")==0) continue;

		FILE* pFile;
		int n =0;          //读到的字节数
		size_t readednum =0;  //每次读到的字节数
		long FileSize=0;
		strcpy(str,"./input/");
		strcat(str,pdirent->d_name);	
		pFile = fopen(str,"rb");
		FileSize = filesize(pFile); //获取文件大小
		cout<< "文件大小是"<< FileSize<< endl;
		while(n<FileSize){
			if((readednum=fread(p->pMem,1,1,pFile))<1)
			break;
			p->pMem = p->pMem+readednum;
			n= n+readednum;
		}
		cout<<"读取了"<<n << "个字节"<< endl;
		if(n == FileSize){
			cout<< "读取文件成功"<<endl;
		}
		else{
			cout<< "读取文件失败"<< endl;
	
		}
			FileSize = 0;
			n =0;
			readednum=0;
			cout<<str<<endl;
		if(pFile){
			fclose(pFile);
			pFile = NULL;
		}
	}
	closedir(pdir);
}

//写入output的工作线程
static void* w_thread(void* arg){	
	memblock* p = (memblock*)arg;
	cout<<"wthread start"<<endl;
	cout<<"开始处理yuv数据"<<endl;
	//修改线程的调度策略为SCHED_RR时间片轮转
	pthread_attr_t attr;	
	get_thread_policy(attr);	
	set_thread_policy(attr,SCHED_RR);
	//从block中读取数据并写入输出文件
	//获取文件个数
	int filenum = getdir_filenum();
	cout<<"文件个数为"<< filenum <<endl;
	FILE* pfile;
	pfile = fopen("./input/1.yuv","rb");
	long  FileSize = filesize(pfile);
	if(pfile){
		fclose(pfile);
		pfile = NULL;
	}
	cout << "w_文件大小为"<< FileSize << endl;
 	while(filenum>0){
		
		char str[50]={0};
		sprintf(str,"./output/%d.yuv",filenum);


		pfile = fopen(str,"wb");
		
		int n =0;//记录读出来的字节数
		while(n<FileSize){
			if(fwrite(p->pMem,1,1,pfile)<1) break;
			p->pMem = p->pMem+1;
			n++;
		}
		filenum--;
		cout<<"写入了"<< n <<"个字节" <<endl;
			if(pfile){
				fclose(pfile);
				pfile = NULL;
			}
	}

}


int main(int argc,char** argv){
	//记录读写线程的线程ID
	pthread_t r_threadId = 0;
	pthread_t w_threadId = 0;
	//使用堆区内存空间,初始化block
	memblock* pblock = (memblock*)malloc(sizeof(memblock));
	memset(pblock,0,sizeof(memblock));
	//开辟的块中内存大小根据输入数据决定输入数据是176*144像素
	//内存大小最小为176*144*3 可以这好存储yub444格式的图像
	pblock->pMem=(char*)malloc(ImageSize);
	if(pblock->pMem == NULL){
		cout<< "block get err "<<endl;
	}
	memset(pblock->pMem,0,ImageSize);
	pblock->blocknum =1;
	pblock->pNext = NULL;	
	//创建文件读写线程
	//返回值是0说明创建线程成功，非零失败
	//使用线程参数将block的地址传递到线程函数中	
	if(pthread_create(&r_threadId,NULL,r_thread,(void*)pblock)!=0){
		printf("创建读线程失败\n");
	}
	if(pthread_create(&w_threadId,NULL,w_thread,(void*)pblock)!=0){
		cout<<"创建写线程失败"<<endl;	
	}
	cout<<"读线程ID是"<<r_threadId<<endl;
	cout<<"写线程ID是"<<w_threadId<<endl;
	//等待读写线程结束
	if(pthread_join(w_threadId,NULL)==0)
		if(pthread_join(r_threadId,NULL)==0)
	return 0;
}

