#define Vector3_UP		Vector3(0, 1, 0)
#define Vector3_DOWN	Vector3(0,-1, 0)
#define Vector3_LEFT	Vector3(-1, 0, 0)
#define Vector3_RIGHT	Vector3(1, 0, 0)
#define Vector3_FORWARD	Vector3(0, 0, 1)
#define Vector3_BACK	Vector3(0, 0, -1)
#define Vector3_ONE		Vector3(1, 1, 1)
#define Vector3_ZERO	Vector3(0, 0, 0)

struct Vector3
{	
	double x;
	double y;
	double z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(double x_, double y_, double z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	double& operator[](int id)
	{
		switch(id)
		{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
		}
	}
	
	Vector3& operator=(Vector3& v)
	{
		if(this != &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}
		
		return v;
	}
	
	Vector3 operator+(Vector3& v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	
	Vector3 operator-(Vector3& v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	
	Vector3 operator*(double d)
	{
		return Vector3(x * d, y * d, z * d);
	}
	
	Vector3 operator/(double d)
	{
		return Vector3(x / d, y / d, z / d);
	}
	
	bool operator==(Vector3& v)
	{
		if((*this - v).MagnitudeSquared() < 9.99999944E-11f)
		{
			return true;
		}
		
		return false;
	}
	
	bool operator!=(Vector3& v)
	{
		if((*this - v).MagnitudeSquared() < 9.99999944E-11f)
		{
			return false;
		}
		
		return true;
	}
	
	double Magnitude()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}
	
	double MagnitudeSquared()
	{
		return (x * x) + (y * y) + (z * z);
	}
	
	Vector3 Normalize()
	{
		double mag = this->Magnitude();
		
		return Vector3(x / mag, y / mag, z / mag);
	}

	double Dot(Vector3& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
	
	Vector3 Cross(Vector3& v)
	{
		return Vector3((y * v.z) - (z * v.y),
						(z * v.x) - (x * v.z),
						(x * v.y) - (y * v.x));
	}
	
	double Angle(Vector3& v)
	{
		return acos(this->Dot(v) / (this->Magnitude() * v.Magnitude())) * RADIANOS_PARA_GRAUS;
	}
	
	Vector3 Reflect(Vector3* plano)
	{
		Vector3 normal = (plano[1] - plano[0]).Cross(plano[2] - plano[0]).Normalize();

		return *this - normal * (2.0f * this->Dot(normal));
	}
	
	string toString()
	{
		stringstream  s;
		s << "|" << x << "|" << y << "|" << z << "|\n";
		
		return s.str();
	}
};