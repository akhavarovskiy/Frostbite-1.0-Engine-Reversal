#ifndef __FB_VECFUNC_H__
#define __FB_VECFUNC_H__

fb::Vec3::Vec3(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->pad = 0.0f;
};

fb::Vec3::~Vec3(void)
{

};

fb::Vec3::Vec3(Vec3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.y;
	this->pad = 0;
}

fb::Vec3::Vec3(float v)
{
	this->x = v;
	this->y = v;
	this->z = v;
	this->pad = 0;
};

fb::Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->pad = 0;
}
/*
	inline fb::Vec3 fp::Vec3::operator - (void)
	{
		return Vec3(-this->x, -this->y, -this->z);
	}

	inline Vec3 Vec3::operator + (void)
	{
		return Vec3(+this->x, +this->y, +this->z);
	}

	inline Vec3 Vec3::operator * (float s)
	{
		return Vec3(x * s, y * s, z * s);
	}

	inline Vec3 Vec3::operator / (float s)
	{
		return Vec3(x / s, y / s, z / s);
	}

	inline Vec3 & Vec3::operator *= (float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	inline Vec3 & Vec3::operator /= (float s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	inline Vec3 Vec3::operator - (Vec3 r)
	{
		return Vec3(x - r.x, y - r.y, z - r.z);
	}

	inline Vec3 Vec3::operator + (Vec3 r)
	{
		return Vec3(x + r.x, y + r.y, z + r.z);
	}

	inline Vec3 & Vec3::operator -= (Vec3 r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}

	inline Vec3 & Vec3::operator += (Vec3 r)
	{
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;
	}

	inline Vec3 Vec3::operator * (Vec3 r)
	{
		return Vec3(x * r.x, y * r.y, z * r.z);
	}

	inline Vec3 Vec3::operator / (Vec3 r)
	{
		return Vec3(x / r.x, y / r.y, z / r.z);
	}

	inline Vec3 & Vec3::operator *= (Vec3 r)
	{
		x *= r.x;
		y *= r.y;
		z *= r.z;
		return *this;
	}

	inline Vec3 & Vec3::operator /= (Vec3 r)
	{
		x /= r.x;
		y /= r.y;
		z /= r.z;
		return *this;
	}

	inline Vec3 & Vec3::operator = (Vec3 v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		return *this;
	}

	inline Vec3  & Vec3::operator = (float v)
	{
		this->x = v;
		this->y = v;
		this->z = v;
	}

	inline float & Vec3::operator[]( unsigned int i ) 
	{
		return data[i];
	}
	
	bool Vec3::operator == ( Vec3 r ) 
	{
		return (x == r.x && y == r.y && z == r.z);
	}
		
	bool Vec3::operator != ( Vec3 r ) 
	{
		return (x != r.x && y != r.y && z != r.z);			
	}
	
	float Vec3::len( void ) 
	{
		return sqrt(( x * x ) + ( y * y ) + ( z * z ));
	}
		
	void Vec3::normalize( void ) 
	{
		float v = sqrt(x * x + y * y + z * z);
		if( v != 0.0f )
		{
			x *= 1.0f/v;
			y *= 1.0f/v;
			z *= 1.0f/v;
		}
	}*/
//}
#endif