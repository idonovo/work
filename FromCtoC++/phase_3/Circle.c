#include "Circle.h"

void (*static_circle_st_vTable[])(void)=
{
(void(*)(void))_Circle_st_Dtor_virtual,
(void(*)(void))_Circle_st_scale_double_virtual, 
(void(*)(void))_Circle_st_draw_const_virtual,
(void(*)(void))_Shape_st_draw_const_ColorEnum_virtual, 
(void(*)(void))_Circle_st_area_const_virtual
};

void _Circle_st_Def_Ctor(_Circle_st* const _this)
{
	_Shape_st_Def_Ctor((_Shape_st*)_this);
	(*((void(***)(void)) _this)) = static_circle_st_vTable;
	_this->m_Circle_st_radius = 1;
	printf("Circle::Circle() - %d, r:%f\n", ((_Shape_st*)_this)->_shape_st_m_id, _this->m_Circle_st_radius);
}
//	Circle(double r) : m_radius(r) { 
//		std::printf("Circle::Circle(double) - %d, r:%f\n", m_id, m_radius); 
//	}
void _Circle_st_Def_Ctor_Double(_Circle_st* const _this, double r)
{
	_Shape_st_Def_Ctor((_Shape_st*)_this);
	(*((void(***)(void))_this))= static_circle_st_vTable;
	_this->m_Circle_st_radius = r;
	printf("Circle::Circle(double) - %d, r:%f\n", ((_Shape_st*)_this)->_shape_st_m_id, _this->m_Circle_st_radius);
}
//	Circle(const Circle& other)
//	: Shape(other), m_radius(other.m_radius) { 
//		std::printf("Circle::Circle(Circle&) - %d, r:%f\n", m_id, m_radius);
//	}
void _Circle_st_CopyCtor_virtual(_Circle_st* const _this, const _Circle_st* const _other)
{
	_Shape_st_CopyCtor_virtual((_Shape_st*)_this, (_Shape_st*)_other);
	(*((void(***)(void))_this)) = static_circle_st_vTable;
	_this->m_Circle_st_radius = _other->m_Circle_st_radius;
	printf("Circle::Circle(Circle&) - %d, r:%f\n", ((_Shape_st*)_this)->_shape_st_m_id, _this->m_Circle_st_radius);
}
//	~Circle() { 
//		std::printf("Circle::~Circle() - %d, r:%f\n", m_id, m_radius); 
//	}
	void _Circle_st_Dtor_virtual(_Circle_st* const _this)
	{
		printf("Circle::~Circle() - %d, r:%f\n",  ((_Shape_st*)_this)->_shape_st_m_id, _this->m_Circle_st_radius);
		_Shape_st_Dtor_virtual((_Shape_st*)_this);
	}
	
//	void draw() const { 
//		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
//	}

	void _Circle_st_draw_const_virtual(const _Circle_st* const _this)
	{
		printf("Circle::draw()  - %d, r:%f\n",  ((_Shape_st*)_this)->_shape_st_m_id, _this->m_Circle_st_radius);
	}
	
//	void scale(double f = 2) {
//		std::printf("Circle::scale(%f)\n", f);
//		m_radius *= f;
//	}
	void _Circle_st_scale_double_virtual(_Circle_st* const _this, double f)
	{
		printf("Circle::scale(%f)\n", f);
		_this->m_Circle_st_radius *= f;
	}
	
//	double area() const {
//		return m_radius * m_radius * 3.1415;	
//	}
double _Circle_st_area_const_virtual(const _Circle_st* const _this)
{
	return _this->m_Circle_st_radius * _this->m_Circle_st_radius * 3.1415;
}
//	double radius() const { 
//		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
//		return m_radius;
//	}
double _Circle_st_radius_const(const _Circle_st* const _this)
{
	printf("Circle::draw()  - %d, r:%f\n",  ((_Shape_st*)_this)->_shape_st_m_id, _this->m_Circle_st_radius);
	return _this->m_Circle_st_radius;
}
