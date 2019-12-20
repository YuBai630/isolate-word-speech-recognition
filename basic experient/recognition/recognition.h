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
{   //����������ŷʽ����
    //�����ʼ��Ϊ0
	float distance=0;
	//DVECTOR��������ά����ŷ�Ͼ��뼴����ÿһά�ľ�����ƽ�����ٿ�����
	for(int i=1;i<=DVECTOR;i++)
	{
		distance+=pow((Vector1[i]-Vector2[i]),2);
	}
	return sqrt(distance);
}

//re = Run_DTW( TemplateVectors[i], NFTemplate[i], TestVector, NFTest );
//NFTemplateΪģ���֡����NFTest�ǲ������ݵ�֡��,TemplateV��ģ��֡��TestV�ǲ���֡
float Run_DTW( float TemplateV[][DVECTOR+1], int NFTemplate, float TestV[][DVECTOR+1], int NFTest )  
{
	float distortion;//��С�ۼƾ���
	
	//��������ļ���ģ���ļ���֡�������ŷʽ���룬�����distance_matrix[][]��
	for(int i=1;i<=NFTest;i++)
	{
		for(int j=1;j<=NFTemplate;j++)
		{
			distance_matrix[i][j]=CalculateDistance(TestV[i],TemplateV[j]);
		}
	}
	
	//distortion_matrix�������ۼƾ���;���
	//�������½ǳ�ʼ��
	distortion_matrix[1][1]=distance_matrix[1][1];
	
	//��ʼ�����к�����
	for(int i=2;i<=NFTest;i++)
	{
		distortion_matrix[i][1]=distortion_matrix[i-1][1]+distance_matrix[i][1];
	}
	for(int i=2;i<=NFTemplate;i++)
	{
		distortion_matrix[1][i]=distortion_matrix[1][i-1]+distance_matrix[1][i];
	}
	
	for(int i=2;i<=min(NFTest,NFTemplate);i++)
	{
		//���ݶ�̬�滮����ʽ���� �и���
		for(int j=i;j<=NFTest;j++)
		{
			distortion_matrix[j][i]=distance_matrix[j][i]
			                       +min(min(distortion_matrix[j-1][i-1],distortion_matrix[j][i-1]),distortion_matrix[j-1][i]);
		}
		//���ݶ�̬�滮����ʽ���� �и���
		for(int j=i;j<=NFTemplate;j++)
		{
			distortion_matrix[i][j]=distance_matrix[i][j]
			                       +min(min(distortion_matrix[i-1][j-1],distortion_matrix[i][j-1]),distortion_matrix[i-1][j]);
		}
	}
	//���ϽǼ�������ۼӾ����
	distortion=distortion_matrix[NFTest][NFTemplate];
	return distortion; // ���ز������ݺ�ģ������֮����ۼӾ����
}
