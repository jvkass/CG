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
		Matrix ma(width, height);
		
		if(width != m.width || height != m.height)
		{
			return ma;
		}
		
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
		Matrix ma(width, height);
		
		if(width != m.width || height != m.height)
		{
			return ma;
		}
		
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
		Matrix ma(width, height);
		
		if(height != m.width)
		{
			return ma;
		}
		
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
		Vector4 ve(v.x, v.y, v.z);
		
		if(height != 4 || width != 4)
		{
			return v;
		}
		
		for(int i = 0; i < width; ++i)
		{
			*ve[i] = (v.x * matrix[i][0]) + (v.y * matrix[i][1]) + (v.z * matrix[i][2]);
		}
		
		return Vector3(ve.x, ve.y, ve.z);
	}
	
	Vector4 operator*(Vector4 v)
	{
		Vector4 ve(v.x, v.y, v.z);
		
		if(height != 4 || width != 4)
		{
			return v;
		}
		
		for(int i = 0; i < width; ++i)
		{
			*ve[i] = (v.x * matrix[i][0]) + (v.y * matrix[i][1]) + (v.z * matrix[i][2]);
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
	
	Vector3 Translate(Vector3 v)
	{
		if(height != 4 || width != 4)
		{
			return v;
		}
		
		return Vector3(v.x + (matrix[0][3] * matrix[0][0]), v.y + (matrix[1][3] * matrix[1][1]), v.z + (matrix[2][3] * matrix[2][2]));
	}
	
	Vector4 Translate(Vector4 v)
	{
		if(height != 4 || width != 4)
		{
			return v;
		}
		
		return Vector4(v.x + (matrix[0][3] * matrix[0][0]), v.y + (matrix[1][3] * matrix[1][1]), v.z + (matrix[2][3] * matrix[2][2]));
	}
	
	Vector3 Scale(Vector3 v)
	{
		if(height != 4 || width != 4)
		{
			return v;
		}
		
		return Vector3(v.x * matrix[0][0], v.y * matrix[1][1], v.z * matrix[2][2]);
	}
	
	Vector4 Scale(Vector4 v)
	{
		if(height != 4 || width != 4)
		{
			return v;
		}
		
		return Vector4(v.x * matrix[0][0], v.y * matrix[1][1], v.z * matrix[2][2]);
	}
	
	Vector3 Rotate(Vector3 v, double angle, char axis)
	{
		if(height != 4 || width != 4)
		{
			return v;
		}
		
		angle = angle * GRAUS_PARA_RADIANOS;
		
		switch(axis)
		{
			case 'x':
				matrix[0][0] = 1;
				matrix[0][1] = 0;
				matrix[0][2] = 0;
				
				matrix[1][0] = 0;
				matrix[1][1] = cos(angle);
				matrix[1][2] = -sin(angle);
				
				matrix[2][0] = 0;
				matrix[2][1] = sin(angle);
				matrix[2][2] = cos(angle);
				break;
			case 'y':
				matrix[0][0] = cos(angle);
				matrix[0][1] = 0;
				matrix[0][2] = sin(angle);
				
				matrix[1][0] = 0;
				matrix[1][1] = 1;
				matrix[1][2] = 0;
				
				matrix[2][0] = -sin(angle);
				matrix[2][1] = 0;
				matrix[2][2] = cos(angle);
				break;
			case 'z':
				matrix[0][0] = cos(angle);
				matrix[0][1] = -sin(angle);
				matrix[0][2] = 0;
				
				matrix[1][0] = sin(angle);
				matrix[1][1] = cos(angle);
				matrix[1][2] = 0;
				
				matrix[2][0] = 0;
				matrix[2][1] = 0;
				matrix[2][2] = 1;
				break;
		}
		
		matrix[3][3] = 1;
		
		Vector3 ve = *this * v;
		
		return Vector3(ve.x, ve.y, ve.z);
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