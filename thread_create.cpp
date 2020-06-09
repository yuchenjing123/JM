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
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

static void* start_thread(void* arg){

	printf("thread start\n");

}


int main(int argc,char** argv){
	pthread_t threadId = 0;
	cout<<threadId <<endl;
	if(pthread_create(&threadId,NULL,start_thread,NULL)!=0){
		printf("线程创建失败\n");
	}
	cout<< threadId <<endl;

	while(1){
		sleep(1);
	}
	return 0;
}

