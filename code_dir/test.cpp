#include <map>
#include <list>
#include <set>
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
}
#endif

typedef enum test{
			DUMP
}test_t;

//@brief dump数据模块map结构中value的结构
typedef struct node{
	test_t m_type;
	list<float> m_list;
}value;



int main(){
	map<int,value*>  Map;
	
	int i =0;
			Map[i] =new value;
			(Map[i])->m_type = DUMP;
			cout<< "(Map[i])->m_type is "<< (Map[i])->m_type << endl;
			(Map[i])->m_list.push_back(1.00);
			list<float>::iterator ite ;
			ite = Map[i]->m_list.begin();
			cout<< *ite  << endl;

			cout << "test point " << endl;
			map<int,value*>*  pMap = new map<int,value*>;
			cout << "new success"<<endl;
			(*pMap)[0] = new value;
			(*pMap)[0]->m_type = DUMP;
			cout <<(*pMap)[i]->m_type<<endl; 
	return 0;
}
