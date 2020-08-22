 /************************************************************************
 *       Filename:  test.c
 *    Description:  
 *        Version:  1.0
 *        Created:  21/04/20 10:13:13
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (荆 明), 
 *        Company:  
 * ************************************************************************/

#include <iostream>
#include "./mmanager.h"
using namespace std;
int main(){

	MM* pmanager = NULL;
	pmanager = new MM(4,1024);
	if(pmanager == NULL){
		cout<< "create err" <<endl;
	}
	else{
		cout<< "create ok" << endl;
	}
	cout<<"内存块数量"<< pmanager->pMmanager->count <<"块大小是"<< pmanager->pMmanager->blocksize <<"使用个数为"<< pmanager->pMmanager->usedCount<<endl;
	memblock* pmemblock = pmanager->Getblock();
	cout<< "内存块的编号为" << pmemblock->blocknum << endl;
	cout<<"内存块数量"<< pmanager->pMmanager->count <<"块大小是"<< pmanager->pMmanager->blocksize <<"使用个数为"<< pmanager->pMmanager->usedCount<<endl;
    if(pmanager->Releaseblock(pmemblock)==ERR)
	{
		cout<<"release block err"<< endl;
	}
	else{
		cout<< "release block ok" <<endl;
	}
	
	delete pmanager;


	return 0;
}


