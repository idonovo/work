#ifndef __CIRCLEMY_H__
#define __CIRCLEMY_H__

#include "Shape.h"

typedef struct _Circle_st
{
	_Shape_st m_shape_base;
	double m_Circle_st_radius;
}_Circle_st;

//extern func* static_circle_st_vTable[];
//class Circle : public Shape {	
//public:
//	Circle() : m_radius(1) { 
//		std::printf("Circle::Circle() - %d, r:%f\n", m_id, m_radius); 
//	}
	void _Circle_st_Def_Ctor(_Circle_st* const _this);
//	Circle(double r) : m_radius(r) { 
//		std::printf("Circle::Circle(double) - %d, r:%f\n", m_id, m_radius); 
//	}
	void _Circle_st_Def_Ctor_Double(_Circle_st* const _this, double r);
//	Circle(const Circle& other)
//	: Shape(other), m_radius(other.m_radius) { 
//		std::printf("Circle::Circle(Circle&) - %d, r:%f\n", m_id, m_radius);
//	}
	void _Circle_st_CopyCtor_virtual(_Circle_st* const _this, const _Circle_st* const _other);
//	~Circle() { 
//		std::printf("Circle::~Circle() - %d, r:%f\n", m_id, m_radius); 
//	}
	void _Circle_st_Dtor_virtual(_Circle_st* const _this);
//	void draw() const { 
//		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
//	}

	void _Circle_st_draw_const_virtual(const _Circle_st* const _this);
//	void scale(double f = 2) {
//		std::printf("Circle::scale(%f)\n", f);
//		m_radius *= f;
//	}
	void _Circle_st_scale_double_virtual(_Circle_st* const _this, double f);
//	double area() const {
//		return m_radius * m_radius * 3.1415;	
//	}
double _Circle_st_area_const_virtual(const _Circle_st* const _this);
//	double radius() const { 
//		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
//		return m_radius;
//	}
double _Circle_st_radius_const(const _Circle_st* const _this);
//private:
//	double m_radius;
//};
#endif /* __CIRCLEMY_H__ */

