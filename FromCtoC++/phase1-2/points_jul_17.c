#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//#define PHASE (2)

/***** Phase 1 *****{{ */
/*#if PHASE >= 1*/
/*class Point2D*/
/*{*/
/*public:*/
/*	Point2D();*/
/*	Point2D(double _x, double _y);*/

/*	double GetX() const;*/
/*	double GetY() const;*/
/*	double Distance(const Point2D& _other) const;*/

/*	Point2D &operator+=(const Point2D& _other);*/
/*	Point2D &operator*=(double _factor);*/

/*private:*/
/*	double m_x;*/
/*	double m_y;		*/
/*};*/


typedef struct Point2D
{
	double m_x;
	double m_y;	
}Point2D;


/*Point2D::Point2D()*/
/*: m_x(0), m_y(0)*/
/*{*/
/*}*/

void CtorDefPoint2D(Point2D* const _this)
{
	_this->m_x = 0;
	_this->m_y = 0;
	return;
}

/*Point2D::Point2D(double _x, double _y)*/
/*: m_x(_x), m_y(_y)*/
/*{*/
/*}*/

void CtorPoint2D(Point2D* const _this, double _x, double _y)
{
	_this->m_x = _x;
	_this->m_y = _y;
	return;
}

void Ctor_Copy_Point2D(Point2D* const _this, const Point2D* const _copy)
{
	_this->m_x = _copy->m_x;
	_this->m_y = _copy->m_y;
	return;
}

/*inline double Point2D::GetY() const*/
/*{*/
/*	return m_y;*/
/*}*/

const double Point2DGetY(const Point2D* const _this)
{
	return _this->m_x;
}

const double Point2DGetX(const Point2D* const _this)
{
	return _this->m_y;
}
/*double Point2D::Distance(const Point2D& _other) const*/
/*{*/
/*	double dx = m_x - _other.m_x;*/
/*	double dy = m_y - _other.m_y;*/
/*	return sqrt(dx * dx + dy * dy);*/
/*}*/

double Point2D_Distance(const Point2D* const _this, const Point2D* const _other)
{
	double dx = _this->m_x - _other->m_x;
	double dy = _this->m_y - _other->m_y;
	return sqrt(dx * dx + dy * dy);
}

/*Point2D& Point2D::operator+=(const Point2D& _other)*/
/*{*/
/*	m_x += _other.m_x;*/
/*	m_y += _other.m_y;*/
/*	*/
/*	return *this;*/
/*}*/

Point2D* Point2DAdditionAssignment(Point2D* const _this, const Point2D* const _other)
{
	_this->m_x += _other->m_x;
	_this->m_y += _other->m_y;
	return _this;
}

/*Point2D& Point2D::operator*=(double _factor)*/
/*{*/
/*	m_x *= _factor;*/
/*	m_y *= _factor;	*/
/*	return *this;*/
/*}*/

Point2D* Point2D_Multipule(Point2D* const _this, double _factor)
{
	_this->m_x *= _factor;
	_this->m_y *= _factor;	
	return _this;
}

/* }} ***** Phase 1 *****/


/*----------------------------------------------------------------*/
/***** Phase 2 *****{{ */

/*void pointless()*/
/*{*/
/*	Point2D p0;*/
/*	Point2D p1(0,10);*/
/*	printf("distance p0 --> p1 == %f\n", p0.Distance(p1));*/

/*	Point2D dxy(+4, -7);*/
/*	p1 += dxy;*/
/*	printf("%f, %f\n", p1.GetX(), p1.GetY());*/
/*	printf("now distance p0 --> p1 == %f\n", p0.Distance(p1));*/
/*}*/

void pointless()
{
	Point2D p0, dxy;
	CtorDefPoint2D(&p0);
	Point2D p1;
	CtorPoint2D(&p1, 0,10);
	printf("distance p0 --> p1 == %f\n", Point2D_Distance(&p0, &p1));
	
	CtorPoint2D(&dxy, +4, -7); 
	Point2DAdditionAssignment(&p1, &dxy);
	printf("%f, %f\n", Point2DGetX(&p1), Point2DGetY(&p1));
	printf("now distance p0 --> p1 == %f\n", Point2D_Distance(&p0, &p1));
}


//#endif

/*/ }} ***** Phase 1 *****/

typedef struct NamedPoint2D
{
	Point2D 	m_Point2D;
	const char*	m_name;
}NamedPoint2D;

/*class NamedPoint2D : public Point2D*/
/*{*/
/*public:*/
/*	NamedPoint2D(const char *_name = "origin");*/
	void NamedPoint2D_CTOR_namedPoint2D(NamedPoint2D* const _this);
	void NamedPoint2D_CTOR_namedPoint2D_char_ptr(NamedPoint2D* const _this, const char *_name);
/*	NamedPoint2D(double _x, double _y, const char *_name = "anonymous Point");*/
	void NamedPoint2D_CTOR_namedPoint2D_double_double(NamedPoint2D* const _this, double _x, double _y);
	void NamedPoint2D_CTOR_namedPoint2D_char_ptr_double_double(NamedPoint2D* const _this, double _x, double _y, const char *_name);
/*	NamedPoint2D(const Point2D& point, const char *_name = "anonymous Point");*/
	void NamedPoint2D_CTOR_namedPoint2D_Point2D_ref(NamedPoint2D* const _this, const Point2D* const _base);
	void NamedPoint2D_CTOR_namedPoint2D_Point2D_ref_char_ptr(NamedPoint2D* const _this, const Point2D* const _base, const char *_name);
	
/*	const char *GetName() const;*/
	const char * NamedPoint2D_GetName(const NamedPoint2D* const _this);
	double NamedPoint2D_Distance_Point2D_ptr(const NamedPoint2D* const _this, const Point2D* const _other);
	double NamedPoint2D_Distance_NamedPoint2D_ptr(const NamedPoint2D* const _this, const NamedPoint2D* const _other);
/*private:*/
/*	const char *m_name;	*/
/*};*/


/*NamedPoint2D(const char*_name = "origin")*/

void NamedPoint2D_CTOR_namedPoint2D(NamedPoint2D* const _this)
{
	NamedPoint2D_CTOR_namedPoint2D_char_ptr( _this, "origin"); 
	return;
}

void NamedPoint2D_CTOR_namedPoint2D_char_ptr(NamedPoint2D* const _this, const char *_name)
{
	CtorDefPoint2D(&_this->m_Point2D);
	_this->m_name = _name;
	return;
}


/*NamedPoint2D::NamedPoint2D(double _x, double _y, const char *_name)*/
/*: m_name(_name), Point2D(_x, _y)*/
/*{*/
/*}*/

void NamedPoint2D_CTOR_namedPoint2D_double_double(NamedPoint2D* const _this, double _x, double _y)
{
	NamedPoint2D_CTOR_namedPoint2D_char_ptr_double_double(_this, _x, _y, "anonymous Point");
}

void NamedPoint2D_CTOR_namedPoint2D_char_ptr_double_double(NamedPoint2D* const _this, double _x, double _y, const char *_name)
{
	CtorPoint2D(&_this->m_Point2D, _x, _y);
	_this->m_name = _name;
}

/*NamedPoint2D::NamedPoint2D(const Point2D& _point, const char *_name)*/
/*: m_name(_name), Point2D(_point)*/
/*{*/
/*}*/
void NamedPoint2D_CTOR_namedPoint2D_Point2D_ref(NamedPoint2D* const _this, const Point2D* const _base)
{
	NamedPoint2D_CTOR_namedPoint2D_Point2D_ref_char_ptr(_this, _base, "anonymous Point");
}

void NamedPoint2D_CTOR_namedPoint2D_Point2D_ref_char_ptr(NamedPoint2D* const _this, const Point2D* const _base, const char *_name)
{
	Ctor_Copy_Point2D(&_this->m_Point2D, _base);
	_this->m_name = _name;
}

/*const char *NamedPoint2D::GetName() const*/
/*{*/
/*	return m_name;*/
/*}*/

const char * NamedPoint2D_GetName(const NamedPoint2D* const _this)
{
	return _this->m_name;
}

double NamedPoint2D_Distance_Point2D_ptr(const NamedPoint2D* const _this, const Point2D* const _other)
{
    return Point2D_Distance(&_this->m_Point2D, _other);
}

double NamedPoint2D_Distance_NamedPoint2D_ptr(const NamedPoint2D* const _this, const NamedPoint2D* const _other)
{
    return Point2D_Distance(&_this->m_Point2D, &_other->m_Point2D);
}

/*//----------------------------------------------------------------*/
const int s_curvature = 1;

typedef struct Rectangle
{
	NamedPoint2D m_a;
	Point2D m_b;	
}Rectangle;


/*class Rectangle*/
/*{*/
/*public:*/
/*	Rectangle(const Point2D& _a, const Point2D& _b, const char *_name = "anonymous Rectangle");*/
	void Rectangle_Ctor_Point2D_ptr_Point2D_ptr(Rectangle* const _this, const Point2D* const _a, const Point2D* const _b);
	void Rectangle_Ctor_Point2D_ptr_Point2D_ptr_char_ptr(Rectangle* const _this, const Point2D* const _a, const Point2D* const _b, const char *_name);
/*	const char *GetName() const;*/

	const char *Rectangle_GetName(const Rectangle* const _this);
/*	double CalcArea() const;*/

	double Rectangle_CalcArea(const Rectangle* const _this);
/*private:*/
/*	NamedPoint2D m_a;*/
/*	Point2D m_b;*/
/*	static const int s_curvature = 1;	*/
/*};*/


/*Rectangle::Rectangle(const Point2D& _a, const Point2D& _b, const char *_name)*/
/*: m_a(_a, _name), m_b(_b)*/
/*{*/
/*}*/

void Rectangle_Ctor_Point2D_ptr_Point2D_ptr_char_ptr(Rectangle* const _this, const Point2D* const _a, const Point2D* const _b, const char *_name)
{
	NamedPoint2D_CTOR_namedPoint2D_char_ptr(&_this->m_a, _name);
	Ctor_Copy_Point2D(&_this->m_b, _b);
}

void Rectangle_Ctor_Point2D_ptr_Point2D_ptr(Rectangle* const _this, const Point2D* const _a, const Point2D* const _b)
{
	Rectangle_Ctor_Point2D_ptr_Point2D_ptr_char_ptr(_this, _a, _b, "anonymous Point");
}

/*const char *Rectangle::GetName() const*/
/*{*/
/*	return m_a.GetName();*/
/*}*/

const char *Rectangle_GetName(const Rectangle* const _this)
{
	return NamedPoint2D_GetName(&_this->m_a);
}


/*double Rectangle::CalcArea() const*/
/*{*/
/*	Point2D p1(m_a.GetX(), m_b.GetY());*/
/*	double sideA = m_a.Distance(p1);*/
/*	double sideB = m_a.Distance(Point2D(m_b.GetX(), m_a.GetY()));*/
/*	return sideA * sideB * s_curvature;*/
/*}*/
double Rectangle_CalcArea(const Rectangle* const _this)
{
	Point2D p1, p2;
	double sideA, sideB; 
	
	CtorPoint2D(&p1, Point2DGetX(&_this->m_a.m_Point2D), Point2DGetY(&_this->m_b));
	sideA = NamedPoint2D_Distance_Point2D_ptr(&_this->m_a, &p1); 
	CtorPoint2D(&p2, Point2DGetX(&_this->m_b),Point2DGetY(&_this->m_a.m_Point2D));
	sideB = NamedPoint2D_Distance_Point2D_ptr(&_this->m_a, &p2);
	return sideA * sideB * s_curvature;
}

/*//----------------------------------------------------------------*/

/*void dog()*/
/*{*/
/*	NamedPoint2D home(5,7, "home");*/
/*	Point2D point(home);*/
/*	NamedPoint2D dog(point);*/

/*	dog *= 2;*/
/*	printf("Distance from %s to %s is %f\n", home.GetName(), dog.GetName(), home.Distance(dog));*/
/*}*/

void namedPoint2D_Dog()
{
    NamedPoint2D home, dog;
    Point2D point;
    NamedPoint2D_CTOR_namedPoint2D_char_ptr_double_double(&home, 5, 7, "home");
    Ctor_Copy_Point2D(&point, &home.m_Point2D);
    NamedPoint2D_CTOR_namedPoint2D_Point2D_ref(&dog, &point);
    Point2D_Multipule(&dog.m_Point2D, 2);
    printf("Distance from %s to %s is %f\n", NamedPoint2D_GetName(&home), NamedPoint2D_GetName(&dog), NamedPoint2D_Distance_NamedPoint2D_ptr(&home, &dog));

}

/*void area()*/
/*{*/
/*	Point2D p0;*/
/*	Point2D p1(12,12);*/
/*	Rectangle r(p0, p1);*/
/*	*/
/*	printf("The area of %s is %f\n", r.GetName(), r.CalcArea());*/
/*	printf("rectangle size %zu", sizeof(r));*/
/*}*/

/*#endif*/
/* }} ***** Phase 2 *****/

void Rectangle_Area()
{
    Point2D p0, p1;
    Rectangle r;
    
    CtorDefPoint2D(&p0);
    CtorPoint2D(&p1, 12, 12);
    Rectangle_Ctor_Point2D_ptr_Point2D_ptr(&r, &p0, &p1);
    printf("The area of %s is %f\n",  Rectangle_GetName(&r), Rectangle_CalcArea(&r));
    printf("rectangle size %zu\n", sizeof(r));
}
/*//----------------------------------------------------------------*/

/*int main()*/
/*{*/
/*#if PHASE >= 1*/
/*	pointless();*/
/*#endif*/

/*#if PHASE >= 2*/
/*	dog();*/
/*	area();*/
/*#endif*/

/*	return 0;*/
/*}*/

int main()
{
//#if PHASE >= 1*/
	pointless();
//#endif*/
	NamedPoint2D x;
	NamedPoint2D_CTOR_namedPoint2D(&x);
	printf("%s", x.m_name);
//}
/*#if PHASE >= 2*/
/*	dog();*/
    namedPoint2D_Dog();
    Rectangle_Area();

	return 0;
}
