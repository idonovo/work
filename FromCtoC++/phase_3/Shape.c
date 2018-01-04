
#include "Shape.h"

int _shape_int_static_numOfShapes;

void (*static_Shape_st_vTable[])(void)=
{
(void(*)(void))_Shape_st_Dtor_virtual,
(void(*)(void))_Shape_st_scale_double_virtual, 
(void(*)(void))_Shape_st_draw_const_virtual,
(void(*)(void))_Shape_st_draw_const_ColorEnum_virtual, 
(void(*)(void))_Shape_st_area_const_virtual
};
/*class Shape : public Scaleable {*/


/*public:*/
/*	Shape() : m_id(++NumOfShapes) {*/
/*		std::printf("Shape::Shape() - %d\n", m_id); */
/*	}*/
	void _Shape_st_Def_Ctor(_Shape_st* const _this)
	{
		_Scaleable_st_Def_Ctor((_Scaleable_st*)_this);
		(*((void(***)(void))_this))= static_Shape_st_vTable;
		_this->_shape_st_m_id = (++_shape_int_static_numOfShapes);	
		printf("Shape::Shape() - %d\n",_this->_shape_st_m_id);
	}

/*	*/
/*	~Shape() {*/
/*		draw();*/
/*		--NumOfShapes; */
/*		std::printf("Shape::~Shape - %d\n", m_id);*/
/*	}*/
	void _Shape_st_Dtor_virtual(_Shape_st* const _this)
	{
		_Shape_st_draw_const_virtual(_this);
		--_shape_int_static_numOfShapes;
		printf("Shape::~Shape - %d\n", _this->_shape_st_m_id);
	}
/*	Shape(const Shape& other) : m_id(++NumOfShapes) {*/
/*		std::printf("Shape::Shape(Shape&) - %d from - %d\n", m_id, other.m_id);*/
/*	}*/
	void _Shape_st_CopyCtor_virtual(_Shape_st* const _this, const _Shape_st* const _other)
	{
		_Scaleable_st_Def_Ctor((_Scaleable_st*)_this);
		(*((void(***)(void))_this))= static_Shape_st_vTable;
		_this->_shape_st_m_id = (++_shape_int_static_numOfShapes);
		printf("Shape::Shape(Shape&) - %d from - %d\n", _this->_shape_st_m_id, _other->_shape_st_m_id);
	}
/*	virtual void draw() const {*/
/*		std::printf("Shape::draw() - %d\n", m_id);		*/
/*	}*/
	void _Shape_st_draw_const_virtual(const _Shape_st* const _this)
	{
		printf("Shape::draw() - %d\n", _this->_shape_st_m_id);
	}

/*	virtual void draw(Color::ColorEnum c) const {*/
/*		std::printf("Shape::draw(c) - %d\n", m_id);*/
/*		Color::setColor(c);*/
/*		draw();*/
/*		Color::setColor(Color::DEFAULT);*/
/*	}*/
	void _Shape_st_draw_const_ColorEnum_virtual(const _Shape_st* const _this, Color_enum _color)
	{
		printf("Shape::draw() - %d\n", _this->_shape_st_m_id);
		_SetColor_func_ColorEnum(_color);
		_Shape_st_draw_const_virtual(_this);
		_SetColor_func_ColorEnum(DEFAULT);
	}
/*	virtual void scale(double f = 1) { */
/*		std::printf("Shape::scale(%f)\n", f);*/
/*	}*/
	void _Shape_st_scale_double_virtual(_Shape_st* const _this, double f)
	{
		printf("Shape::scale(%f)\n", f);
	}
/*	virtual double area() const { return -1; }*/
	double _Shape_st_area_const_virtual(const _Shape_st* const _this)
	{
		return -1;
	}
	
/*	static void printInventory() {*/
/*		std::printf("Shape::printInventory - %d\n", NumOfShapes);*/
/*	}*/

void _Shape_st_printInventory_static()
{
	printf("Shape::printInventory - %d\n", _shape_int_static_numOfShapes);
}	
/*private:*/
/*	static int NumOfShapes;*/
/*	Shape& operator=(const Shape &); // disabled, no implementation provided*/
	//void _Shape_st_assignment_const_ref__Shape_st(const _Shape_st* const _this , const _Shape_st* const _other);


/*protected:*/
/*	 int m_id;*/
/*};*/

/*int Shape::NumOfShapes = 0;*/


