#ifndef __B_H__
#define __B_H__





#include <iostream>
using namespace std;

typedef void(*Foot)(int);

extern "C" Foot FindFunc(const string& name);

extern "C"  void Add(int num);

extern "C"  void Mult(int num);

extern "C"  void AddAndMult(int num);
#endif /* __B_H__ */

