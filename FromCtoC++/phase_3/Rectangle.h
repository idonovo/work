#ifndef __RECTANGLEMY_H__
#define __RECTANGLEMY_H__

#include "Shape.h"

typedef struct _Rectangle_st
{
	_Shape_st m_shape_base;
	int _Rectangle_st_m_a;
	int _Rectangle_st_m_b;

}_Rectangle_st;

//extern func* static_rectangle_st_vTable[];
//class Rectangle: public Shape {
//public:
//	Rectangle() : m_a(1), m_b(1) { 
//		std::printf("Rectangle::Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
//	}
void _Rectangle_st_Def_Ctor(_Rectangle_st* const _this);
//	Rectangle(int a) : m_a(a), m_b(a) { 
//		std::printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", m_id, m_a, m_b);
//	}
void _Rectangle_st_Def_Ctor_Int(_Rectangle_st* const _this, int a);
//	Rectangle(int a, int b) : m_a(a), m_b(b) { 
//		std::printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", m_id, m_a, m_b);
//	}

void _Rectangle_st_Def_Ctor_Int_Int(_Rectangle_st* const _this, int a, int b);
//	Rectangle(const Rectangle &other ) 
//	: m_a(other.m_a), m_b(other.m_b), Shape(other) { 
//		std::printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", m_id, m_a, m_b);
//	}
void _Rectangle_st_CopyCtor_virtual(_Rectangle_st* const _this, const _Rectangle_st* const _other);	
//	~Rectangle() { 
//		std::printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
//	}
void _Rectangle_st_draw_const_virtual(const _Rectangle_st* const _this);
//	void draw() const { 
//		std::printf("Rectangle::draw()  - %d, [%d, %d]\n", m_id, m_a, m_b);
//	}
void _Rectangle_st_Dtor_virtual(_Rectangle_st* const _this);

//    void draw(Color::ColorEnum c) const {
//		std::printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, m_id, m_a, m_b);
//	}

void _Rectangle_st_draw_const_ColorEnum_virtual(const _Rectangle_st* const _this, Color_enum _color);
//	void scale(double f = 4){
//		std::printf("Rectangle::scale(%f)\n", f);
//		m_a *= f;
//		m_b *= f;
//	}
void _Rectangle_st_scale_double_virtual(_Rectangle_st* const _this, double f);
//	double area() const {
//		return m_a * m_b;
//	}
double _Rectangle_st_radius_const(const _Rectangle_st* const _this);
//private:
//	int m_a, m_b;
//};

#endif /* __RECTANGLEMY_H__ */

