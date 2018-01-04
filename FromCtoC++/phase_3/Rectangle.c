#include "Rectangle.h"

void (*static_rectangle_st_vTable[])(void)=
{
(void(*)(void))_Rectangle_st_Dtor_virtual,
(void(*)(void))_Rectangle_st_scale_double_virtual, 
(void(*)(void))_Rectangle_st_draw_const_virtual,
(void(*)(void))_Rectangle_st_draw_const_ColorEnum_virtual, 
(void(*)(void))_Rectangle_st_radius_const
};
//class Rectangle: public Shape {
//public:
//	Rectangle() : m_a(1), m_b(1) { 
//		std::printf("Rectangle::Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
//	}
void _Rectangle_st_Def_Ctor(_Rectangle_st* const _this)
{
	_Shape_st_Def_Ctor((_Shape_st*)_this);
	(*((void(***)(void))_this))= static_rectangle_st_vTable;
	_this->_Rectangle_st_m_a = 1;
	_this->_Rectangle_st_m_b = 1;
	printf("Rectangle::Rectangle() - %d, [%d, %d]\n", ((_Shape_st*)_this)->_shape_st_m_id, _this->_Rectangle_st_m_a, _this->_Rectangle_st_m_b);

}
//	Rectangle(int a) : m_a(a), m_b(a) { 
//		std::printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", m_id, m_a, m_b);
//	}
void _Rectangle_st_Def_Ctor_Int(_Rectangle_st* const _this, int a)
{
	_Shape_st_Def_Ctor((_Shape_st*)_this);
	(*((void(***)(void))_this))= static_rectangle_st_vTable;
	_this->_Rectangle_st_m_a = a;
	_this->_Rectangle_st_m_b = a;
	printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", ((_Shape_st*)_this)->_shape_st_m_id, _this->_Rectangle_st_m_a, _this->_Rectangle_st_m_b);
}
//	Rectangle(int a, int b) : m_a(a), m_b(b) { 
//		std::printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", m_id, m_a, m_b);
//	}

void _Rectangle_st_Def_Ctor_Int_Int(_Rectangle_st* const _this, int a, int b)
{
	_Shape_st_Def_Ctor((_Shape_st*)_this);
	(*((void(***)(void))_this))= static_rectangle_st_vTable;
	_this->_Rectangle_st_m_a = a;
	_this->_Rectangle_st_m_b = b;
	printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", ((_Shape_st*)_this)->_shape_st_m_id, _this->_Rectangle_st_m_a, _this->_Rectangle_st_m_b);
	
}
//	Rectangle(const Rectangle &other ) 
//	: m_a(other.m_a), m_b(other.m_b), Shape(other) { 
//		std::printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", m_id, m_a, m_b);
//	}
void _Rectangle_st_CopyCtor_virtual(_Rectangle_st* const _this, const _Rectangle_st* const _other)
{
	_Shape_st_CopyCtor_virtual((_Shape_st*)_this, (_Shape_st*)_other);
	(*((void(***)(void))_this))= static_rectangle_st_vTable;
	_this->_Rectangle_st_m_a = _other->_Rectangle_st_m_a;
	_this->_Rectangle_st_m_b = _other->_Rectangle_st_m_b;
	printf("Rectangle::Rectangle(Rectangle&)  - %d, [%d, %d]\n", ((_Shape_st*)_this)->_shape_st_m_id, _this->_Rectangle_st_m_a, _this->_Rectangle_st_m_b);

}
//	~Rectangle() { 
//		std::printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
//	}

void _Rectangle_st_Dtor_virtual(_Rectangle_st* const _this)
{
	printf("Rectangle::~Rectangle()  - %d, [%d, %d]\n", ((_Shape_st*)_this)->_shape_st_m_id, _this->_Rectangle_st_m_a, _this->_Rectangle_st_m_b);
	_Shape_st_Dtor_virtual((_Shape_st*)_this);
}
//	void draw() const { 
//		std::printf("Rectangle::draw()  - %d, [%d, %d]\n", m_id, m_a, m_b);
//	}
void _Rectangle_st_draw_const_virtual(const _Rectangle_st* const _this)
{
	printf("Rectangle::draw() - %d, [%d, %d]\n", ((_Shape_st*)_this)->_shape_st_m_id, _this->_Rectangle_st_m_a, _this->_Rectangle_st_m_b);
}
//    void draw(Color::ColorEnum c) const {
//		std::printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, m_id, m_a, m_b);
//	}
void _Rectangle_st_draw_const_ColorEnum_virtual(const _Rectangle_st* const _this, Color_enum _color)
{
	printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", _color, ((_Shape_st*)_this)->_shape_st_m_id, _this->_Rectangle_st_m_a, _this->_Rectangle_st_m_b);	
}
//	void scale(double f = 4){
//		std::printf("Rectangle::scale(%f)\n", f);
//		m_a *= f;
//		m_b *= f;
//	}
void _Rectangle_st_scale_double_virtual(_Rectangle_st* const _this, double f)
{
	printf("Rectangle::scale(%f)\n", f);
	_this->_Rectangle_st_m_a *= f;
	_this->_Rectangle_st_m_b *= f;
}
//	double area() const {
//		return m_a * m_b;
//	}
double _Rectangle_st_radius_const(const _Rectangle_st* const _this)
{
	return _this->_Rectangle_st_m_a * _this->_Rectangle_st_m_b;
}
//private:
//	int m_a, m_b;
//};

