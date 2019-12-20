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

const int MAXNFRAME = 300; // max number of frames һ����Ƶ�������300֡����Լ3000ms
const int DVECTOR = 39; // dimension of a frame ÿһ֡��һ��39άMFCC������ʾ

#include "binaryRead.h"
#include "recognition.h"

float TemplateVectors[2072][ MAXNFRAME+1 ][ DVECTOR+1 ]; // �洢2072��template��֡����
int NFTemplate[2072]; // number of frames in each template vector �洢2072��template���Ե�֡��
int tem[2072];//tem[i]��ʾ��i+1��ģ���ļ�����Ӧ����ȷ��������
int test[2500];//test[i]��ʾ��i+1�������ļ�����Ӧ����ȷ��������
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
	string TestFileList = "test_filelist.txt"; // test list ���������б�
	string TrainFileList = "train_filelist.txt"; // train list ѵ�������б�
	string *path=new string[2100];
	//ѵ�������б���ÿ�д���path����
	int n_template=get_strs_from_file( TrainFileList, path );
	for( int i=1; i<=n_template; i++ )
	{
		string template_file = path[i];
		cout<<template_file<<endl;
		//��ÿ��ѵ�����ݶ�����Ϊģ���ļ���
		NFTemplate[i-1] = ReadHtk( template_file, TemplateVectors[i-1] );
		
		//��tem[]���鸳ֵ
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
	int nfiles = get_strs_from_file( TestFileList, fileInfos ); // ��ȡ�����ļ��б�����fileInfos����
	float TestVector[MAXNFRAME+1][DVECTOR+1]; // �洢test��֡����
	int NFTest = 0; // �洢test��֡��
	//��test[]���鸳ֵ
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
	
	//����ʶ��ƥ��
	for( int j=1; j<=nfiles; j++ )
	{
		float re = 0;
		int k = 1;
		float result = 1e+38f; //��ʾ������
		NFTest = ReadHtk( fileInfos[j], TestVector );
		for( int i=0; i<2072; i++ )
		{// ����������������2072��ģ�����ƥ�䣬��¼ƥ�������С����һ��
			re = Run_DTW( TemplateVectors[i], NFTemplate[i], TestVector, NFTest );
			//NFTemplate[i]Ϊģ���֡����NFTest�ǲ������ݵ�֡��
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




