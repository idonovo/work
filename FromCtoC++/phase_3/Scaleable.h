#ifndef __SCALEABLE_H__
#define __SCALEABLE_H__

#include <stdio.h>
#include <stdlib.h> 

//typedef void(*func)(void);
//struct Color {
//	enum ColorEnum { RED, GREEN, DEFAULT };
//	static void setColor(ColorEnum color){		
//		static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
//		std::puts(pallete[color]);
//	}
//};


extern const char* Color_pallete[];

typedef enum Color_enum
{ 
	RED, 
	GREEN, 
	DEFAULT 
}Color_enum;

void _SetColor_func_ColorEnum(Color_enum color);
/*class Scaleable {*/
/*public:*/
/*	virtual ~Scaleable() { }	*/
/*	virtual void scale(double) = 0;*/
/*};*/

typedef struct _Scaleable_st
{
	void (*(*vTable))();
}_Scaleable_st;

void _Scaleable_st_Def_Ctor(_Scaleable_st* const _this);

void _Scaleable_st_Copy_Ctor(_Scaleable_st* const _this, _Scaleable_st* const _other);

void _Scaleable_st_Dtor_virtual(_Scaleable_st* const _this);

void _Scaleable_st_scale_virtual(_Scaleable_st* const _this, double _t);



#endif /* __SCALEABLE_H__ */

