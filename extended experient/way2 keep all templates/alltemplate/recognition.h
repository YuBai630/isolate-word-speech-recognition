float distance_matrix[ MAXNFRAME+1 ][ MAXNFRAME+1 ]; // �洢�������
float distortion_matrix[ MAXNFRAME+1 ][ MAXNFRAME+1 ]; // �洢�����ۼӾ���

int get_strs_from_file( string filename, string strs[] )
{
	ifstream fin( filename.c_str() );
	if( !fin )
	{
		cout << "file read error!" << endl;
		exit(-1);
	}

	int nstr=1;
	while( !fin.eof() )
	{
		getline( fin, strs[nstr++] );
	}
	fin.close();

	while( "" == strs[nstr-1] )nstr--;

	return nstr-1;
}

float CalculateDistance( float Vector1[], float Vector2[] ) // Note: ��Ҫ���б�д��
{// ����������ŷʽ����
	float distance=0;
	for(int i=1;i<=DVECTOR;i++)
	{
		distance+=pow((Vector1[i]-Vector2[i]),2);
	}
	return sqrt(distance);
}

//re = Run_DTW( TemplateVectors[i], NFTemplate[i], TestVector, NFTest );
//NFTemplateΪģ���֡����NFTest�ǲ������ݵ�֡��,TemplateV��ģ��֡��TestV�ǲ���֡
float Run_DTW( float TemplateV[][DVECTOR+1], int NFTemplate, float TestV[][DVECTOR+1], int NFTest )   // Note: ��Ҫ���б�д��
{
	float distortion;
	for(int i=1;i<=NFTest;i++)
	{
		for(int j=1;j<=NFTemplate;j++)
		{
			distance_matrix[i][j]=CalculateDistance(TestV[i],TemplateV[j]);
		}
	}
	distortion_matrix[1][1]=distance_matrix[1][1];
	for(int i=2;i<=NFTest;i++)
	{
		//distortion_matrix[1][i]=distortion_matrix[1][i-1]+distance_matrix[1][i];
		distortion_matrix[i][1]=distortion_matrix[i-1][1]+distance_matrix[i][1];
	}
	for(int i=2;i<=NFTemplate;i++)
	{
		distortion_matrix[1][i]=distortion_matrix[1][i-1]+distance_matrix[1][i];
	}
	for(int i=2;i<=min(NFTest,NFTemplate);i++)
	{
		//�и���
		for(int j=i;j<=NFTest;j++)
		{
			distortion_matrix[j][i]=distance_matrix[j][i]
			                       +min(min(distortion_matrix[j-1][i-1],distortion_matrix[j][i-1]),distortion_matrix[j-1][i]);
		}
		//�и���
		for(int j=i;j<=NFTemplate;j++)
		{
			distortion_matrix[i][j]=distance_matrix[i][j]
			                       +min(min(distortion_matrix[i-1][j-1],distortion_matrix[i][j-1]),distortion_matrix[i-1][j]);
		}
	}
	distortion=distortion_matrix[NFTest][NFTemplate];

	return distortion; // ���ز������ݺ�ģ������֮����ۼӾ����
}

//��һ������ӳ���ϵ��DTW����
void Run_DTW2( float TemplateV[][DVECTOR+1], int NFTemplate, float TestV[][DVECTOR+1], int NFTest )   // Note: ��Ҫ���б�д��
{
	for(int i=1;i<=NFTest;i++)
	{
		for(int j=1;j<=NFTemplate;j++)
		{
			distance_matrix[i][j]=CalculateDistance(TestV[i],TemplateV[j]);
		}
	}
	distortion_matrix[1][1]=distance_matrix[1][1];
	for(int i=2;i<=NFTest;i++)
	{
		//distortion_matrix[1][i]=distortion_matrix[1][i-1]+distance_matrix[1][i];
		distortion_matrix[i][1]=distortion_matrix[i-1][1]+distance_matrix[i][1];
	}
	for(int i=2;i<=NFTemplate;i++)
	{
		distortion_matrix[1][i]=distortion_matrix[1][i-1]+distance_matrix[1][i];
	}
	for(int i=2;i<=min(NFTest,NFTemplate);i++)
	{
		//�и���
		for(int j=i;j<=NFTest;j++)
		{
			distortion_matrix[j][i]=distance_matrix[j][i]
			                       +min(min(distortion_matrix[j-1][i-1],distortion_matrix[j][i-1]),distortion_matrix[j-1][i]);
		}
		//�и���
		for(int j=i;j<=NFTemplate;j++)
		{
			distortion_matrix[i][j]=distance_matrix[i][j]
			                       +min(min(distortion_matrix[i-1][j-1],distortion_matrix[i][j-1]),distortion_matrix[i-1][j]);
		}
	}
	
	//cout<<"check3"<<endl;
	//distortion=distortion_matrix[NFTest][NFTemplate];
	//maps[NFTemplate]=NFTest;
	for(int i=1;i<=39;i++)
	{
		TestV[NFTemplate][i]=TestV[NFTest][i];
		TestV[1][i]=TestV[1][i];
	}
	int i=NFTest;int j=NFTemplate;
	while(1)
	{
		if((i<=1)&&(j<=1))
		{
			break;
		}
		if(min(min(distortion_matrix[i-1][j-1],distortion_matrix[i][j-1]),distortion_matrix[i-1][j])==distortion_matrix[i-1][j-1])
		{
			for(int k=1;k<=39;k++)
			{
				TestV[j-1][k]=TestV[i-1][k];
			}
			j=j-1;
			i=i-1;
		}
		else if(min(min(distortion_matrix[i-1][j-1],distortion_matrix[i][j-1]),distortion_matrix[i-1][j])==distortion_matrix[i][j-1])
		{
			for(int k=1;k<=39;k++)
			{
				TestV[j-1][k]=TestV[i][k];
			}
			j=j-1;
		}
		else
		{
			for(int k=1;k<=39;k++)
			{
				TestV[j][k]=TestV[i-1][k];
			}
			i=i-1;
		}
		//cout<<"i,j:"<<i<<" "<<j;
	}
	//return distortion; // ���ز������ݺ�ģ������֮����ۼӾ����
}
