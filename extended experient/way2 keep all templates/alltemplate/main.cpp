#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int MAXNFRAME = 300; // max number of frames 一段音频最多允许300帧，即约3000ms
const int DVECTOR = 39; // dimension of a frame 每一帧用一个39维MFCC向量表示

#include "binaryRead.h"
#include "recognition.h"

float TemplateVectors[2072][ MAXNFRAME+1 ][ DVECTOR+1 ]; // 存储2072个template的帧数据
int NFTemplate[2072]; // number of frames in each template vector 存储2072个template各自的帧数
int tem[2072];//tem[i]表示第i+1个模板文件所对应的正确语音数字
int test[2500];//test[i]表示第i+1个测试文件所对应的正确语音数字
int rig[11];
int wro[11];
int right_sum=0;
int wrong_sum=0;
int main( int argc, char *argv[] )
{
    memset(tem,0,sizeof(tem));
    memset(test,0,sizeof(test));
    memset(rig,0,sizeof(rig));
    memset(wro,0,sizeof(wro));
	string TestFileList = "test_filelist.txt"; // test list 测试数据列表
	string TrainFileList = "train_filelist.txt"; // train list 训练数据列表
	string *path=new string[2100];
	//训练数据列表中每行存入path数组
	int n_template=get_strs_from_file( TrainFileList, path );
	for( int i=1; i<=n_template; i++ )
	{
		string template_file = path[i];
		cout<<template_file<<endl;
		//将每个训练数据都设置为模板文件。
		NFTemplate[i-1] = ReadHtk( template_file, TemplateVectors[i-1] );
		
		//对tem[]数组赋值
		int flag;
        for(int w=0;w<path[i].length();w++)
        {
            if(path[i][w]=='_')
            {
                flag=w;
                break;
            }
        }
        char t1=path[i][flag-1];
        char t2=path[i][flag-2];
        int num;
        if(t2!='\\')
        {
            num=10;
        }
        else
        {
            num=t1-'0';
        }
        tem[i-1]=num;
	}
	delete []path;


	string *fileInfos = new string [2500];
	int nfiles = get_strs_from_file( TestFileList, fileInfos ); // 读取测试文件列表，存入fileInfos矩阵
	float TestVector[MAXNFRAME+1][DVECTOR+1]; // 存储test的帧数据
	int NFTest = 0; // 存储test的帧数
	//对test[]数组赋值
	for(int j=1;j<=nfiles;j++)
    {
        int flag;
        for(int w=0;w<fileInfos[j].length();w++)
        {
            if(fileInfos[j][w]=='_')
            {
                flag=w;
                break;
            }
        }
        char t1=fileInfos[j][flag-1];
        char t2=fileInfos[j][flag-2];
        int num;
        if(t2!='\\')
        {
            num=10;
        }
        else
        {
            num=t1-'0';
        }
        test[j]=num;
    }
	
	//进行识别匹配
	for( int j=1; j<=nfiles; j++ )
	{
		float re = 0;
		int k = 1;
		float result = 1e+38f; //表示最大的数
		NFTest = ReadHtk( fileInfos[j], TestVector );
		for( int i=0; i<2072; i++ )
		{// 将测试数据依次与2072个模板进行匹配，记录匹配距离最小的那一个
			re = Run_DTW( TemplateVectors[i], NFTemplate[i], TestVector, NFTest );
			//NFTemplate[i]为模板的帧数，NFTest是测试数据的帧数
			if( result > re )
			{
				result = re;
				k = tem[i];
			}
		}
		if(k==test[j] )
        {
            rig[k]++;
            right_sum++;
        }
        else
        {
            wro[test[j]]++;
            wrong_sum++;
        }
		cout << fileInfos[j] << '\t' << k << endl;

	}
	delete [] fileInfos;
	for(int i=0;i<=10;i++)
    {
        cout<<i<<'\t'<<"right:"<<rig[i]<<'\t'<<"wrong:"<<wro[i]<<'\t'<<"right score:"<<float(float(rig[i])/(rig[i]+wro[i]))<<endl;
    }
    cout<<endl;
    cout<<"right_sum:"<<right_sum<<'\t'<<"wrong_sum:"<<wrong_sum<<'\t'<<"right score:"<<float(float(right_sum)/(right_sum+wrong_sum))<<endl;

	return 0;
}




