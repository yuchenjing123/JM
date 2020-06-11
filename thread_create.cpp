/* ************************************************************************
 *       Filename:  thread_creat.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2020年06月09日 09时11分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
using namespace std;



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

static void* start_thread(void* arg){

	cout<<"thread start"<<endl;
	//获取线程属性
	pthread_attr_t attr;
	
	

	get_thread_policy(attr);
	
	set_thread_policy(attr,SCHED_FIFO);

	get_thread_policy(attr);


    cout<< "线程结束" << endl;
}


int main(int argc,char** argv){
	

	pthread_t threadId = 0;
	if(pthread_create(&threadId,NULL,start_thread,NULL)!=0){
		printf("线程创建失败\n");
	}
	cout<<"线程 id 是" << threadId <<endl;

	while(1){
		sleep(1);
	}
	return 0;
}

