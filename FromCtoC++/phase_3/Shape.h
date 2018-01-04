#ifndef __MYSHAPE_H__
#define __MYSHAPE_H__

#include "Scaleable.h"

/*class Shape : public Scaleable {*/

//extern func* static_Shape_st_vTable[];

extern int _shape_int_static_numOfShapes;

typedef struct _Shape_st
{
	_Scaleable_st m_shape_base;
	int _shape_st_m_id;
}_Shape_st;


    void _Shape_st_printInventory_static();
/*public:*/
/*	Shape() : m_id(++NumOfShapes) {*/
/*		std::printf("Shape::Shape() - %d\n", m_id); */
/*	}*/
	void _Shape_st_Def_Ctor(_Shape_st* const _this);
/*	*/
/*	~Shape() {*/
/*		draw();*/
/*		--NumOfShapes; */
/*		std::printf("Shape::~Shape - %d\n", m_id);*/
/*	}*/
	void _Shape_st_Dtor_virtual(_Shape_st* const _this);
/*	Shape(const Shape& other) : m_id(++NumOfShapes) {*/
/*		std::printf("Shape::Shape(Shape&) - %d from - %d\n", m_id, other.m_id);*/
/*	}*/
	void _Shape_st_CopyCtor_virtual(_Shape_st* const _this, const _Shape_st* const _other);
/*	virtual void draw() const {*/
/*		std::printf("Shape::draw() - %d\n", m_id);		*/
/*	}*/
	void _Shape_st_draw_const_virtual(const _Shape_st* const _this);

/*	virtual void draw(Color::ColorEnum c) const {*/
/*		std::printf("Shape::draw(c) - %d\n", m_id);*/
/*		Color::setColor(c);*/
/*		draw();*/
/*		Color::setColor(Color::DEFAULT);*/
/*	}*/
	void _Shape_st_draw_const_ColorEnum_virtual(const _Shape_st* const _this, Color_enum _color);
/*	virtual void scale(double f = 1) { */
/*		std::printf("Shape::scale(%f)\n", f);*/
/*	}*/
	void _Shape_st_scale_double_virtual(_Shape_st* const _this, double f);
/*	virtual double area() const { return -1; }*/
	double _Shape_st_area_const_virtual(const _Shape_st* const _this);
	
/*	static void printInventory() {*/
/*		std::printf("Shape::printInventory - %d\n", NumOfShapes);*/
/*	}*/
/*private:*/
/*	static int NumOfShapes;*/
/*	Shape& operator=(const Shape &); // disabled, no implementation provided*/
void _Shape_st_assignment_const_ref__Shape_st(const _Shape_st* const _this , const _Shape_st* const _other);


#endif /* ___MYSHAPE_H____ */

