
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

typedef enum class __DUMPTYPE__
{
    //dump_type;//TODO
        frame_id 			=0,
        active_sensor_idx 		=1,
        frame_time 			=2,
        sensor_rolling_shutter_skew 	=3,
        exposure_time 			=4,
        sof				=5,
        focus_distance 			=6,
        eis_pre_crop_vIN_fullWidth 	=7,
        eis_pre_crop_vIN_fullHeight 	=8,
        eis_pre_crop_vIN_windowLeft	=9,
        eis_pre_crop_vIN_windowTop	=10,
        eis_pre_crop_vOUT_fullWidth	=11,
        eis_pre_crop_vOUT_fullHeight	=12,
        eis_pre_crop_vOUT_windowWidth	=13,
        eis_pre_crop_vOUT_windowHeight	=14,
        eis_pre_crop_vOUT_windowLeft	=15,
        eis_pre_crop_vOUT_windowTop	=16,
        output_crop_fov_fullWidth	=17,
        output_crop_fov_fullHeight	=18,
        output_crop_fov_windowWidth	=19,
        output_crop_fov_windowHeight	=20,
        output_crop_fov_windowLeft	=21,
        output_crop_fov_windowTop	=22	
} DUMP_TYPE; //此结构表示文件中每列是什么类型的数据


typedef enum class __RESULT__
{
    SUCCESS,
    INVALID_FILE,
    INVALID_PROCESS,
    INVALID_TYPE,
} RESULT;


/**
 * @brief 数据处理类型
 * 
 */
typedef enum  __TYPE__
{
    DUMP,
    VIDEO,
    INVALID
} TYPE;

//@brief dump数据模块map结构中value的结构
typedef struct node{
	TYPE m_type;
	list<float> m_list;
}value;

/**
 * @brief 数据处理最终的返回结果
 * 
 */
typedef struct __RESPONSE__
{
    TYPE type;
    RESULT result;
    // JSON json;//TODO
    //dump数据
    map<int,void*> m_list;	

} RESPONSE;



int main() 
{
    FILE *fp = NULL;
	char* line;
	char* tok;
	char buffer[1024]={0};
	if ((fp = fopen("1.csv", "at+")) != NULL)
	{
        //读取第一行数据，作为map中的key值
		line = fgets(buffer, sizeof(buffer), fp);
		//去掉；
		tok = strtok(line,";");
		cout<<"jingming test tok is"<< tok << endl;
		//此处tok是
		//test fgets
		printf("line is %s",line);
		int oneline_len = strlen(line);
		printf("oneline_len is %d\n",oneline_len);
		//end test
		
		/*
			@brif 将第一行的信息逐一放入map中
		*/
		//TODO
		int i =0;
		tok = strtok(tok, ",");
		while (tok != NULL)//读取第一行数据中有多少项
		{
			printf("%s \n", tok);//将读取到的每一个子串打印出来
			i++;
			tok = strtok(NULL, ",");
		}
		cout<<  "map 中key的个数是" << i << endl;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//初始化map,map范围从0->i;
		map<int,value*>  Map;
		for(int j =0;j<i;j++){
			Map[j] =new value;
			(Map[j])->m_type = DUMP;
			cout<<  "map["<<  j <<"]初始化完成"<< endl ;
		}

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		//从第二行读取数据
	
		while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)//当没有读取到文件末尾时循环继续
		{
            //以逗号为分隔符,strtok函数第一次调用返回被分割的第一个字符串，第二次返回被分割后的第二个...依次类推
			//当返回空说明所有子字符串返回完成
			line = strtok(line, ",");
			int colnum=0;
			while (line != NULL)//读取每一行的数据
			{
				printf("%s ", line);//将读取到的每一个子串打印出来
				//将来子字符串转换成数字TODO
				float a = atof(line);
				//存到map中value*所指向的结构体中的m_list中
					
				if(colnum > 0){	
					Map[colnum-1]->m_list.push_back(a);
				}
				colnum++;
				line = strtok(NULL, ",");
			}
			printf("\n");
		}

		cout <<  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
		//测试map中是否写入正确的值
		map<int,value*>::iterator ite;     //迭代器
		list<float>::iterator ite_list;
		ite=Map.begin();
		int mark =0;
		while(ite != Map.end())
		{
			cout<< ite->first <<endl;
			ite_list = Map[mark]->m_list.begin();
			while(ite_list!=Map[mark]->m_list.end())
			{
					cout << *ite_list<<"	";
					ite_list++;
			}
			mark++;
			ite++;
		}

		fclose(fp);
		fp = NULL;
	}
     return 0;
}
