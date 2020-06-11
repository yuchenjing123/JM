/* ************************************************************************
 *       Filename:  direnttest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2020年06月11日 13时31分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <dirent.h>
#include <iostream>
using namespace std;
#include <string.h>

int main(){
	DIR* pdir;
	dirent* pdirent;
	pdir = opendir("./input");
	char str[80]={0};
	
	while((pdirent = readdir(pdir))!=NULL){
		if(strcmp(pdirent->d_name,".")==0||strcmp(pdirent->d_name,"..")==0) continue;
		strcpy(str,"./input/");
		strcat(str,pdirent->d_name);	
		
		cout<<str<<endl;
	}
	closedir(pdir);
	

	return 0;
}


