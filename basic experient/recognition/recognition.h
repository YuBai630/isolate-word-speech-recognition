float distance_matrix[ MAXNFRAME+1 ][ MAXNFRAME+1 ]; // 存储距离矩阵
float distortion_matrix[ MAXNFRAME+1 ][ MAXNFRAME+1 ]; // 存储距离累加矩阵

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

float CalculateDistance( float Vector1[], float Vector2[] ) // Note: 需要自行编写！
{   //计算向量间欧式距离
    //距离初始化为0
	float distance=0;
	//DVECTOR是向量的维数，欧氏距离即计算每一维的距离差的平方和再开根号
	for(int i=1;i<=DVECTOR;i++)
	{
		distance+=pow((Vector1[i]-Vector2[i]),2);
	}
	return sqrt(distance);
}

//re = Run_DTW( TemplateVectors[i], NFTemplate[i], TestVector, NFTest );
//NFTemplate为模板的帧数，NFTest是测试数据的帧数,TemplateV是模板帧，TestV是测试帧
float Run_DTW( float TemplateV[][DVECTOR+1], int NFTemplate, float TestV[][DVECTOR+1], int NFTest )  
{
	float distortion;//最小累计距离
	
	//计算测试文件与模板文件各帧向量间的欧式距离，存放在distance_matrix[][]中
	for(int i=1;i<=NFTest;i++)
	{
		for(int j=1;j<=NFTemplate;j++)
		{
			distance_matrix[i][j]=CalculateDistance(TestV[i],TemplateV[j]);
		}
	}
	
	//distortion_matrix矩阵是累计距离和矩阵
	//矩阵左下角初始化
	distortion_matrix[1][1]=distance_matrix[1][1];
	
	//初始化首行和首列
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
		//根据动态规划递推式进行 行更新
		for(int j=i;j<=NFTest;j++)
		{
			distortion_matrix[j][i]=distance_matrix[j][i]
			                       +min(min(distortion_matrix[j-1][i-1],distortion_matrix[j][i-1]),distortion_matrix[j-1][i]);
		}
		//根据动态规划递推式进行 列更新
		for(int j=i;j<=NFTemplate;j++)
		{
			distortion_matrix[i][j]=distance_matrix[i][j]
			                       +min(min(distortion_matrix[i-1][j-1],distortion_matrix[i][j-1]),distortion_matrix[i-1][j]);
		}
	}
	//右上角即所求的累加距离和
	distortion=distortion_matrix[NFTest][NFTemplate];
	return distortion; // 返回测试数据和模板数据之间的累加距离和
}
