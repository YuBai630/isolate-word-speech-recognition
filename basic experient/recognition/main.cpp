#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int MAXNFRAME = 300; // max number of frames һ����Ƶ�������300֡����Լ3000ms
const int DVECTOR = 39; // dimension of a frame ÿһ֡��һ��39άMFCC������ʾ

#include "binaryRead.h"
#include "recognition.h"

float TemplateVectors[10][ MAXNFRAME+1 ][ DVECTOR+1 ]; // �洢10��template��֡����
int NFTemplate[10]; // number of frames in each template vector �洢10��template���Ե�֡��
/*
ģ��ƥ�� ʵ�ֲ������ݺ�ģ������֮���ƥ���㷨���ò��ֶ�Ӧ ����������
float CalculateDistance( float Vector1[], float Vector2[] )
float Run_DTW( float TemplateV[][DVECTOR+1], int NFTemplate, float TestV[][DVECTOR+1], int NFTest )
���ߵ���ǰ�߼���֡����֮���ŷʽ���롣
����������Ҫ���Լ�������� �� ��ı�д
*/
int main( int argc, char *argv[] )
{
	string TestFileList = "test_filelist.txt"; // test list ���������б�

	/*----------------��ȡģ������---------------------*/
	string TemplateFolder = "template";
	for( int i=0; i<10; i++ )
	{
		ostringstream number;
		number << i;
		string template_file = TemplateFolder + '\\' +  number.str() + "_template.mfc";
		NFTemplate[i] = ReadHtk( template_file, TemplateVectors[i] );
	}

	/*----------------��ȡ�������ݲ��ֱ���ģ�����ƥ��---------------*/
	string *fileInfos = new string [100];
	int nfiles = get_strs_from_file( TestFileList, fileInfos ); // ��ȡ�����ļ��б�����fileInfos����
	float TestVector[MAXNFRAME+1][DVECTOR+1]; // �洢test��֡����
	int NFTest = 0; // �洢test��֡��
	for( int j=1; j<=nfiles; j++ )
	{
		float re = 0;
		int k = 1;
		float result = 1e+38f; //��ʾ������
		NFTest = ReadHtk( fileInfos[j], TestVector );
		for( int i=0; i<10; i++ )
		{// ����������������10��ģ�����ƥ�䣬��¼ƥ�������С����һ��
			re = Run_DTW( TemplateVectors[i], NFTemplate[i], TestVector, NFTest );
			//NFTemplate[i]Ϊģ���֡����NFTest�ǲ������ݵ�֡��
			if( result > re )
			{
				//cout<<"result:    "<<result<<"     re:    "<<re<<endl;
				result = re;
				k = i;
			}
		}
		cout << fileInfos[j] << '\t' << k << endl;
	}
	delete [] fileInfos;
	return 0;
}
