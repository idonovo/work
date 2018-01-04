#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"

_Circle_st Shape_draw_Circle_unit;
int init_circle;
//void report(const Shape& s) {
//	std::puts("-----report-----");
//	s.draw(); 
//	Shape::printInventory();
//	std::puts("-----report-----");
//}

void _Shape_report(const _Shape_st* const _this)
{
	puts("-----report-----");
	void(*ff)(const _Shape_st* const) = (void(*)(const _Shape_st* const)) (((_Scaleable_st*)_this)->vTable[2]);
	ff(_this);
	_Shape_st_printInventory_static();
	puts("-----report-----");
}

//inline void draw(Shape& obj) { 
//	std::puts("-----draw(Shape&)-----");
//	obj.scale();
//	obj.draw();	
//	std::puts("-----draw(Shape&)-----");
//}

void _Shape_draw(const _Shape_st* const _this)
{ 
	puts("-----draw(Shape&)-----");
	(*(void(***)(const _Shape_st* const _this , double f))(_this))[1](_this, 1);
	//void(*ff)(_Shape_st* const _this , double f) = (void(*)(_Shape_st* const _this , double f)) (((_Scaleable_st*)_this)->vTable[1]);
	//ff(_this, 1);
	(*(void(***)(const _Shape_st* const _this))(_this))[2](_this);
	//void(*ff1)(const _Shape_st* const) = (void(*)(const _Shape_st* const)) (((_Scaleable_st*)_this)->vTable[2]);
	//ff1(_this);
	
	puts("-----draw(Shape&)-----");
}

//void draw(Circle c) { 
//	std::puts("-----draw(Circle)-----");

//	static Circle unit(1);
//	
//	unit.draw();
//	unit.scale(3);
//	c.draw(); 
//	std::puts("-----draw(Circle)-----");
//}

void _Shape_draw_Circle(const _Circle_st* const c)
{ 
	_Circle_st temp;
	_Circle_st_CopyCtor_virtual(&temp, c);
	puts("-----draw(Circle)-----");
	if(!init_circle)
	{
	_Circle_st_Def_Ctor_Double(&Shape_draw_Circle_unit, 1);
		++init_circle;
	}
	_Circle_st_draw_const_virtual(&Shape_draw_Circle_unit);
	printf("Circle::scale(%f)\n", 3.0);
	Shape_draw_Circle_unit.m_Circle_st_radius *= 3;
	_Circle_st_draw_const_virtual(&temp);
	puts("-----draw(Circle)-----");
	_Circle_st_Dtor_virtual(&temp);
}

//void doObjArray(){
//	Shape objects[] = {
//	    Circle(),
//	    Rectangle(4),
//	    Circle(9)
//	};

//    for(int i = 0; i < 3; ++i) 
//		objects[i].draw();
//}

void _Shape_do_ObjArray()
{

	_Circle_st temp_cir_1, temp_cir_2;
	_Rectangle_st temp_rec;
	_Shape_st array[3];
	
	_Circle_st_Def_Ctor(&temp_cir_1);
	_Shape_st_CopyCtor_virtual(&array[0], (_Shape_st*)&temp_cir_1);
	_Circle_st_Dtor_virtual(&temp_cir_1);
	
	_Rectangle_st_Def_Ctor_Int(&temp_rec, 4);
_Shape_st_CopyCtor_virtual(&array[1], (_Shape_st*)&temp_rec);
	_Rectangle_st_Dtor_virtual(&temp_rec);
	
	_Circle_st_Def_Ctor_Double(&temp_cir_2, 9);
	_Shape_st_CopyCtor_virtual(&array[2], 	(_Shape_st*)&temp_cir_2);
	_Circle_st_Dtor_virtual(&temp_cir_2);

    for(int i = 0; i < 3; ++i)
    {
		void(*ff)(const _Shape_st* const) = (void(*)(const _Shape_st* const)) (((_Scaleable_st*)&array[i])->vTable[2]);
	ff(&array[i]);
    }
    
	_Shape_st_Dtor_virtual(&array[2]);
	_Shape_st_Dtor_virtual(&array[1]);
	_Shape_st_Dtor_virtual(&array[0]);
}


//void disappear() {
//	std::puts("-----disappear-----");

//	Circle defaultCircle();

//	std::puts("-----disappear-----");
//}

void _Shape_disappear() {
	puts("-----disappear-----");
	_Circle_st defaultCircle();
	puts("-----disappear-----");
}

//template <class T>
//double diffWhenDoubled(T& shape){
//	double a0 = shape.area();
//	shape.scale(2);
//	double a1 = shape.area();
//	return a1 - a0;
//}

double _Shape_Templated_diffWhenDoubled(_Shape_st* const _T)
{
	double a0 = (*(double(***)(_Shape_st* const _T))(_T))[4](_T);
	//double(*ff1)(const _Shape_st* const _this) = (double(*)(const _Shape_st* const _this)) (((_Scaleable_st*)_T)->vTable[4]);
	//double a0 = ff1((_Shape_st* const)_T);

	//void(*ff2)(_Shape_st* const _this , double f) = (void(*)(_Shape_st* const _T , double f)) (((_Scaleable_st*)_T)->vTable[1]);
	//ff2((_Shape_st* const)_T, 2);
	(*(void(***)(_Shape_st* const _T , double f))(_T))[1](_T, 2);
	double a1 =(*(double(***)(_Shape_st* const _T))(_T))[4](_T);
	//double a1 = ff1((_Shape_st* const)_T);
	return a1 - a0;
}

//void doPointerArray(){
//	std::puts("-----doPointerArray-----");
//	Shape *array[] =  {
//	    new Circle(),
//	    new Rectangle(3),
//	    new Circle(4)
//	};

//    for(int i = 0; i < 3; ++i){ 
//		array[i]->scale();
//		array[i]->draw();
//	}

//	std::printf("area: %f\n", diffWhenDoubled(*array[2]));

//    for(int i = 0; i < 3; ++i) { 
//		delete array[i]; 
//		array[i] = 0; 
//	}

//	std::puts("-----doPointerArray-----");
//}

void _Shape_doPointerArray()
{
	puts("-----doPointerArray-----");
	int i;
	_Circle_st* a_circlePtr; 
	_Rectangle_st* b_recPtr;
	_Circle_st* c_circlePtr;
	_Shape_st* array[3];
	
	a_circlePtr = malloc(1*sizeof(_Circle_st));
	_Circle_st_Def_Ctor(a_circlePtr);
	array[0] = (_Shape_st*)a_circlePtr;
	
	b_recPtr = malloc(1*sizeof(_Rectangle_st));
	_Rectangle_st_Def_Ctor_Int(b_recPtr, 3);
	array[1] = (_Shape_st*)b_recPtr;
	
	c_circlePtr = malloc(1*sizeof(_Circle_st));
	_Circle_st_Def_Ctor_Double(c_circlePtr, 4);
	array[2] = (_Shape_st*)c_circlePtr;

	for (i = 0; i < 3; i += 1)
	{
		(*(void(***)(_Shape_st* const _T , double f))(array[i]))[1](array[i], 1);
		//void(*ff1)(_Shape_st* const _this , double f) = (void(*)(_Shape_st* const _T , double f)) (((_Scaleable_st*)array[i])->vTable[1]);
		//ff1((_Shape_st* const)array[i], 1);
		(*(void(***)(_Shape_st* const _T))(array[i]))[2](array[i]);
		//void(*ff2)(const _Shape_st* const) = (void(*)(const _Shape_st* const)) (((_Scaleable_st*)array[i])->vTable[2]);
		//ff2(array[i]);
	}

	printf("area: %f\n", _Shape_Templated_diffWhenDoubled((_Shape_st* )c_circlePtr));
	
	for (i = 0; i < 3; i += 1)
	{
		(*(void(***)(_Shape_st* const _this))(array[i]))[0](array[i]);
		//void(*ff1)(_Shape_st* const _this) = (void(*)(_Shape_st* const _T)) (((_Scaleable_st*)array[i])->vTable[0]);
		//ff1((_Shape_st* const)array[i]);
		free(array[i]);
	}
	
	puts("-----doPointerArray-----");
}

//void dispose(Rectangle* p){
//  delete[] p;
//}

void _Rectangle_dispose(_Rectangle_st** _p, int _size)
{
	for (int i = _size -1 ; i >= 0; --i)
	{
		//void(*ff)(const _Shape_st* const) = (void(*)(const _Shape_st* const)) (((_Scaleable_st*)_p[i])->vTable[0]);
		//ff((_Shape_st*)_p[i]);
		(*(void(***)(_Shape_st* const _this))(_p[i]))[0]((_Shape_st*)_p[i]);
		free(_p[i]);
	}
	free(_p);
}

//class Empty {
//public:
//    Empty(int id = 0) { std::printf("Empty::Empty(%d)\n", id); }
//   ~Empty() { std::puts("Empty::~Empty()");}	
//};
typedef struct _Empty_st 
{
    char _Empty_st_char;
}_Empty_st;

void _Empty_st_Ctor_def(_Empty_st* const _obj, int id)
{
    printf("Empty::Empty(%d)\n", id);
    return;
}

void _Empty_st_Dtor(_Empty_st* const _obj)
{

    puts("Empty::~Empty()");
    return;
}

//class EmptyEmpty  : public Empty{
	//int m_i;

//public:
	//EmptyEmpty(int id) : m_i(id){
		// std::printf("EmptyEmpty::EmptyEmpty(%d)\n", m_i); 
	//}
//};

typedef struct _EmptyEmpty_st 
{
    int _Empty_st_m_i;
}_EmptyEmpty_st;

void _EmptyEmpty_st_Ctor_def(_EmptyEmpty_st* const _obj, int id)
{
    _Empty_st_Ctor_def((_Empty_st*)_obj, 0);
    _obj->_Empty_st_m_i = id;
    printf("EmptyEmpty::EmptyEmpty(%d)\n", _obj->_Empty_st_m_i); 
}

void _EmptyEmpty_st_Dtor_(_EmptyEmpty_st* const _obj)
{
    _Empty_st_Dtor((_Empty_st*)_obj);
}

//class EmptyBag {
//	Empty e1
;
//	Empty e2;
//	EmptyEmpty ee;
//public: 
//	EmptyBag() : e2(2), e1(1), ee(2) {
//		std::puts("EmptyBag::EmptyBag()");
//	}
//	~EmptyBag(){
//		std::puts("EmptyBag::~EmptyBag");
//	}	
//};
typedef struct _EmptyBag_st
{
    _Empty_st    m_empty_st_e1;
    _Empty_st    m_empty_st_e2;
    _EmptyEmpty_st m_empty_st_ee;
    
}_EmptyBag_st;

void _EmptyBag_st_Ctor_def(_EmptyBag_st* const _this)
{
    _Empty_st_Ctor_def(&_this->m_empty_st_e1, 1);
    _Empty_st_Ctor_def(&_this->m_empty_st_e2, 2);
    _EmptyEmpty_st_Ctor_def(&_this->m_empty_st_ee, 2);
    puts("EmptyBag::EmptyBag()");
}

void _EmptyBag_st_Dtor(_EmptyBag_st* const _this)
{
    puts("EmptyBag::~EmptyBag");
    _EmptyEmpty_st_Dtor_(&_this->m_empty_st_ee);
    _Empty_st_Dtor(&_this->m_empty_st_e2);
    _Empty_st_Dtor(&_this->m_empty_st_e1);
}

int main (int argc, char *argv[])
{
	int i;
	printf("---------------Start----------------\n");
    _Circle_st c;
    _Circle_st_Def_Ctor(&c);
	_Rectangle_st s;
	_Rectangle_st_Def_Ctor_Int(&s, 4);
	printf("0.-------------------------------\n");		
	_Shape_draw_Circle(&c);

	printf("+..............\n");		
	_Shape_draw_Circle(&c);

	printf("+..............\n");		
    _Shape_draw((_Shape_st*)&s);

	printf("+..............\n");		
	_Shape_report((_Shape_st*)&c);

	printf("1.-------------------------------\n");
	
	_Shape_doPointerArray();

	printf("2.-------------------------------\n");
	
    _Shape_do_ObjArray();
	
	printf("3.-------------------------------\n");
	
    _Shape_st_printInventory_static();
    _Circle_st c2;
    _Circle_st_CopyCtor_virtual(&c2, &c);
    _Shape_st_printInventory_static();

	printf("4.-------------------------------\n");
	
	_Circle_st olympics[5];
	
	for (i = 0; i < 5; i += 1)
	{
	    _Circle_st_Def_Ctor(&olympics[i]);
	}
	printf("olympic diff %f\n", _Shape_Templated_diffWhenDoubled((_Shape_st*)&olympics[1]));

	printf("5.-------------------------------\n");

    _Rectangle_st** fourRectangles= malloc(4*sizeof(_Rectangle_st*));
    for(i = 0; i < 4; i += 1)
    {
    	fourRectangles[i] = malloc(1*sizeof(_Rectangle_st));
    	_Rectangle_st_Def_Ctor(fourRectangles[i]);
    }
    _Rectangle_dispose(fourRectangles, 4);

	printf("6.-------------------------------\n");

	_EmptyBag_st eb;
	_EmptyBag_st_Ctor_def(&eb);
	
	printf("Empty things are: %zu %zu %zu", sizeof(_Empty_st), sizeof(_EmptyEmpty_st), sizeof(_EmptyBag_st));
	
	printf("7.-------------------------------\n");
	_Shape_disappear();	

	printf("---------------END----------------\n");
	
	_EmptyBag_st_Dtor(&eb);
	for (i = 4; i >= 0; --i)
	{
	    _Circle_st_Dtor_virtual(&olympics[i]);    
	}
	_Circle_st_Dtor_virtual(&c2);
	_Rectangle_st_Dtor_virtual(&s);
	_Circle_st_Dtor_virtual(&c);
	_Circle_st_Dtor_virtual(&Shape_draw_Circle_unit);
	return 0;
}

