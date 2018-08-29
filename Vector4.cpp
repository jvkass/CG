#define Vector4_UP		Vector4(0, 1, 0)
#define Vector4_DOWN	Vector4(0,-1, 0)
#define Vector4_LEFT	Vector4(-1, 0, 0)
#define Vector4_RIGHT	Vector4(1, 0, 0)
#define Vector4_FORWARD	Vector4(0, 0, 1)
#define Vector4_BACK	Vector4(0, 0, -1)
#define Vector4_ONE		Vector4(1, 1, 1)
#define Vector4_ZERO	Vector4(0, 0, 0)

#define RADIANOS_PARA_GRAUS 180 / 3.141592653589793238463

struct Vector4
{	
	double x;
	double y;
	double z;
	double w = 1;

	Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	Vector4(double x_, double y_, double z_)
	{
		x = x_;
		y = y_;
		z = z_;
		w = 1;
	}

	double* operator[](int id)
	{
		switch(id)
		{
			case 0:
				return &x;
			case 1:
				return &y;
			case 2:
				return &z;
			case 3:
				return &w;	
		}
	}
	
	Vector4& operator=(Vector4& v)
	{
		if(this != &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}
	}
	
	Vector4 operator+(Vector4& v)
	{
		return Vector4(x + v.x, y + v.y, z + v.z);
	}
	
	Vector4 operator-(Vector4& v)
	{
		return Vector4(x - v.x, y - v.y, z - v.z);
	}
	
	Vector4 operator*(double d)
	{
		return Vector4(x * d, y * d, z * d);
	}
	
	Vector4 operator/(double d)
	{
		return Vector4(x / d, y / d, z / d);
	}
	
	bool operator==(Vector4& v)
	{
		if((*this - v).MagnitudeSquared() < 9.99999944E-11f)
		{
			return true;
		}
		
		return false;
	}
	
	bool operator!=(Vector4& v)
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
	
	Vector4 Normalize()
	{
		double mag = this->Magnitude();
		
		return Vector4(x / mag, y / mag, z / mag);
	}

	double Dot(Vector4& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
	
	Vector4 Cross(Vector4& v)
	{
		return Vector4((y * v.z) - (z * v.y),
						(z * v.x) - (x * v.z),
						(x * v.y) - (y * v.x));
	}
	
	double Angle(Vector4& v)
	{
		return acos(this->Dot(v) / (this->Magnitude() * v.Magnitude())) * RADIANOS_PARA_GRAUS;
	}
	
	Vector4 Reflect(Vector4* plano)
	{
		Vector4 normal = (plano[1] - plano[0]).Cross(plano[2] - plano[0]).Normalize();

		return *this - normal * (2.0f * this->Dot(normal));
	}
	
	string toString()
	{
		stringstream  s;
		s << "|" << x << "|" << y << "|" << z << "|" << w << "|";
		
		return s.str();
	}
};