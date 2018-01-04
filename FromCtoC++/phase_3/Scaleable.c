#include <stdlib.h> 
#include "Scaleable.h"

const char * Color_pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };

void (*static_Scaleable_vTable[])(void) =
{
(void(*)(void))_Scaleable_st_Dtor_virtual,
(void(*)(void))_Scaleable_st_scale_virtual
};

void _SetColor_func_ColorEnum(Color_enum color)
{		
	printf("%s", Color_pallete[color]);
}

void _Scaleable_st_Def_Ctor(_Scaleable_st* const _this)
{
	(*((void(***)(void))_this)) = static_Scaleable_vTable;
}

void _Scaleable_st_Dtor_virtual(_Scaleable_st* const _this){}

void _Scaleable_st_scale_virtual(_Scaleable_st* const _this, double _t)
{
	printf("no implementation of pure virtual function\n");
	exit(EXIT_FAILURE);
}

void _Scaleable_st_Copy_Ctor(_Scaleable_st* const _this, _Scaleable_st* const _other){}


