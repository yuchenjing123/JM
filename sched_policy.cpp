/* ************************************************************************
 *       Filename:  sched_method.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2020年06月10日 17时22分39秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  YOUR NAME (荆 明), 
 *        Company:  
 * ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <assert.h>
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

//显示当前调度策略的线程优先级范围
static void show_thread_priority(pthread_attr_t& attr,int policy){
	int priority = sched_get_priority_max(policy);   //获得成功返回最大优先级号，获取失败返回-1
	assert(priority != -1);  //获取成功继续执行
	cout<<  "max_priority="<< priority  <<endl;

	priority = sched_get_priority_min(policy);
	assert(priority != -1);
	cout << "min_priority="<< priority <<endl;

}

//获得线程优先级
static int get_thread_priority(pthread_attr_t& attr){
	struct sched_param param;

	int rs = pthread_attr_getschedparam(&attr,&param);
	assert(rs  == 0);
	cout<< "priority="<<param.sched_priority<<endl;
	return param.sched_priority;

}

//设置线程调度策略
static void set_thread_policy(pthread_attr_t& attr,int policy){
	int rs = pthread_attr_setschedpolicy(&attr,policy);
	assert(rs == 0);
	get_thread_policy(attr);

}




int main(){
	pthread_attr_t attr;   //线程属性
	sched_param sched; //调度策略
	

	sched.sched_priority = 50;
	int rs;               //初始化线程的返回值
	
	rs = pthread_attr_init(&attr);  //初始化线程属性
	
	assert(rs == 0);  //如果不等于０则退出
	rs = pthread_attr_setschedparam(&attr,&sched);

	int policy = get_thread_policy(attr);
	
	
	cout<<"显示当前优先级配置"<<endl;
	show_thread_priority(attr,policy);
	
	cout<<"显示fifo调度策略的优先级配置"<<endl;
	show_thread_priority(attr,SCHED_FIFO);
    
	cout<<"显示RR调度策略的优先级配置"<<endl;
	show_thread_priority(attr,SCHED_RR);
	
	
	cout<<"设置当前线程优先级"<<endl;
	cout<<"显示当前线程的优先级"<<endl;
	int priority = get_thread_priority(attr);
	cout<< "优先级为"<<priority<<endl;

	cout<<"设置线程调度策略为RR"<<endl;
	set_thread_policy(attr,SCHED_RR);
	policy = get_thread_policy(attr);

	rs = pthread_attr_destroy(&attr);
	assert(rs==0);//销毁线程属性
	


	return 0;
}


