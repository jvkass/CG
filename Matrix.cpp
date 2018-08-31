struct Matrix
{	
	int width;
	int height;
	
	double** matrix;
	
	Matrix(int w, int h)
	{
		width = w;
		height = h;
		
		matrix = new double*[width];
		
		for (int i = 0; i < width; ++i)
		{
			matrix[i] = new double[height];
		}
		
		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				matrix[i][j] = 0;
			}
		}
	}
	
	double* operator[](int id)
	{
		return matrix[id];
	}
	
	Matrix operator=(Matrix& m)
	{
		Matrix ma(width, height);
		
		if(width != m.width || height != m.height)
		{
			return ma;
		}
		
		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				ma[i][j] = m[i][j];
			}
		}
		
		return ma;
	}
	
	Matrix operator+(Matrix& m)
	{
		if(width != m.width || height != m.height)
		{
			return Matrix(width, height);
		}
		
		Matrix ma(width, height);
		
		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				ma[i][j] = matrix[i][j] + m[i][j];
			}
		}
		
		return ma;
	}
	
	Matrix operator-(Matrix& m)
	{
		if(width != m.width || height != m.height)
		{
			return Matrix(width, height);
		}
		
		Matrix ma(width, height);
		
		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				ma[i][j] = matrix[i][j] - m[i][j];
			}
		}
		
		return ma;
	}
	
	Matrix operator*(double d)
	{
		Matrix ma(width, height);
		
		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				ma[i][j] = matrix[i][j] * d;
			}
		}
		
		return ma;
	}
	
	Matrix operator*(Matrix m)
	{
		if(height != m.width)
		{
			return Matrix(width, height);
		}
		
		Matrix ma(width, height);
		
		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				for(int k = 0; k < m.height; ++k)
				{
					ma[i][j] += matrix[i][k] * m[k][j];
				}
			}
		}
		
		return ma;
	}
	
	Vector3 operator*(Vector3 v)
	{
		if(height != 4 || width != 4)
		{
			return Vector3(v.x, v.y, v.z);
		}
		
		Vector4 ve(v.x, v.y, v.z);
		
		for(int i = 0; i < width; ++i)
		{
			ve[i] = (v.x * matrix[i][0]) + (v.y * matrix[i][1]) + (v.z * matrix[i][2]);
		}
		
		return Vector3(ve.x, ve.y, ve.z);
	}
	
	Vector4 operator*(Vector4 v)
	{
		if(height != 4 || width != 4)
		{
			return Vector4(v.x, v.y, v.z);
		}
		
		Vector4 ve(v.x, v.y, v.z);
		
		for(int i = 0; i < width; ++i)
		{
			ve[i] = (v.x * matrix[i][0]) + (v.y * matrix[i][1]) + (v.z * matrix[i][2]);
		}
		
		return Vector4(ve.x, ve.y, ve.z);
	}
	
	Matrix operator/(double d)
	{
		Matrix ma(width, height);
		
		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				ma[i][j] = matrix[i][j] / d;
			}
		}
		
		return ma;
	}
	
	Matrix Transpose()
	{
		Matrix ma(height, width);
		
		for(int i = 0; i < height; ++i)
		{
			for(int j = 0; j < width; ++j)
			{
				ma[i][j] = matrix[j][i];
			}
		}
		
		return ma;
	}
	
	string toString()
	{
		stringstream  s;
		
		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				s << "|" << matrix[i][j] <<  "|";
			}
			
			s << "\n";
		}
		
		return s.str();
	}
};