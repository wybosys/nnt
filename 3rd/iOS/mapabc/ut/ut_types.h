
//_________________________________Copyright (c) 2009,Mapabc Co.,Ltd_____________________________
//                                       All rights reserved.
// 
//   文件名称：ut_types.h
//   文件标识：见配置管理计划书
//   描    述：公共类型定义
// 
//   当前版本：1.0
//   作    者：Duan Sijiu(张小刚整理)
//   完成日期：2010.05.20
//_______________________________________________________________________________________________

#ifndef _UT_TYPES_H_
#define _UT_TYPES_H_

#include <stdlib.h>
#include <string.h>

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $$$$$$$$$$$$$$$$$$$$common$$$$$$$$$$$$$$$$$$$$$

#if defined WIN32 || WINCE
	typedef __int64				S_INT64;
	typedef unsigned __int64	U_INT64;
#define	ATOI64(val) _atoi64(val)
#elif defined (LINUX_PC) || defined (LINUX_PDA) || defined (ANDROID_PHONE) || defined (SYMBIAN_PHONE)
	typedef long long			S_INT64;
	typedef unsigned long long	U_INT64;
	#define	ATOI64(val)	strtoll(val, NULL, 10)
	typedef long long __int64;
#endif

#if defined WIN32 || WINCE
    #define STDCALL __stdcall* 
#elif defined (LINUX_PC) || defined (LINUX_PDA) || defined (ANDROID_PHONE) || defined (SYMBIAN_PHONE)
    #define STDCALL *
#endif

#define MAXLEN_OF_PATH  256 // 路径最大长度


#define IN
#define OUT
#define INOUT

template <class _T>
class TPNT
	{
	public:
		TPNT():X(0),Y(0)           {}
		TPNT(_T x, _T y)           { X = x; Y = y; }
		inline void SetPnt(_T x, _T y)    { X = x; Y = y; }
		inline bool operator == (TPNT &A) { return X == A.X && Y == A.Y; }
		inline bool operator != (TPNT &A) { return X != A.X || Y != A.Y; }
		//inline void operator =  (TPNT &A) { X=A.X; Y=A.Y; }
		inline void operator =  (TPNT A) { X=A.X; Y=A.Y; }
		inline void Offset(_T dx, _T dy) { X+=dx; Y+=dy; }
		inline void Offset(TPNT &A) { Offset(A.X,A.Y); }
		inline TPNT operator + (TPNT &A) { return TPNT(X + A.X, Y + A.Y); }
		inline TPNT operator += (TPNT &A) { X+=A.X; Y+=A.Y; return *this; }
		inline TPNT operator - (TPNT &A) { return TPNT(X - A.X, Y - A.Y); }
		inline TPNT operator -= (TPNT &A) { X-=A.X; Y-=A.Y; return *this; }
	public:
		_T X, Y;
	};
typedef TPNT<double> DPNT;
typedef TPNT<float>  FPNT;
typedef TPNT<int>    IPNT;
typedef TPNT<long>   LPNT;
typedef IPNT MPOINT;
typedef FPNT MFPOINT;
typedef DPNT MDPOINT;
typedef IPNT MSUFFIX;
typedef FPNT MLONLAT;
typedef FPNT MPROJECTLONLAT;// 投影坐标 米

template <class _T>
class TSIZE
	{
	public:
		TSIZE():W(0),H(0)           {}
		TSIZE(_T w, _T h)           { W = w; H = h; }
		inline void SetSize(_T w, _T h)    { W = w; H = h; }
		inline bool operator == (TSIZE &A) { return W == A.W && H == A.H; }
		inline bool operator != (TSIZE &A) { return W != A.W || H != A.H; }
		inline void operator =  (TSIZE &A) { W=A.W; H=A.H; }
		inline TSIZE operator + (TSIZE &A) { return TSIZE(W+A.W, H+A.H); }
		inline TSIZE operator += (TSIZE &A) { W+=A.W; H+=A.H; return *this; }
		inline TSIZE operator - (TSIZE &A) { return TSIZE(W-A.W, H-A.H); }
		inline TSIZE operator -= (TSIZE &A) { W-=A.W; H-=A.H; return *this; }
	public:
		_T W, H;
	};
typedef TSIZE<double> DSIZE;
typedef TSIZE<float>  FSIZE;
typedef TSIZE<int>    ISIZE;
typedef TSIZE<long>   LSIZE;
typedef ISIZE MSIZE;

template <class _T>
class TRECT
{
public:
	inline void operator =  (TRECT &A) { Left=A.Left; Right=A.Right; Top=A.Top; Bottom=A.Bottom; }
	inline bool operator == (TRECT &A) { return Left==A.Left && Right==A.Right && Top==A.Top && Bottom==A.Bottom; }
	inline bool operator < (TRECT &A) 
	{ 
		if(Left==A.Left && Right==A.Right && Top==A.Top )
		{
			return Bottom<A.Bottom;
		}
		else if(Left==A.Left && Right==A.Right){
			return Top<A.Top;
		}
		else if(Left==A.Left){
			return Right<A.Right;
		}
		else {
			return Left<A.Left;
		}
	}
	inline bool operator > (TRECT &A) 
	{ 
		if(Left==A.Left && Right==A.Right && Top==A.Top )
		{
			return Bottom>A.Bottom;
		}
		else if(Left==A.Left && Right==A.Right){
			return Top>A.Top;
		}
		else if(Left==A.Left){
			return Right>A.Right;
		}
		else {
			return Left>A.Left;
		}
	}
	
	_T Left;
	_T Right;
	_T Top;
	_T Bottom;
};

typedef TRECT<int> IRECT;
typedef TRECT<float> FRECT;
typedef IRECT MRECT;
typedef FRECT MFRECT;
/*
struct MFRECT // 浮数矩形框
{
	float fLeft;
	float fRight;
	float fTop;
	float fBottom;
};*/

/*
template <class _T>
class TRECT
	{
	public:
		TRECT(){}
		TRECT(TPNT<_T> pnt, TSIZE<_T> size) { PNT = pnt; SIZE = size; }
		TRECT(_T x, _T y, _T w, _T h) { PNT.X = x; PNT.Y = y; SIZE.W = w; SIZE.H = h;}
		inline void SetRect(TPNT<_T> pnt, TSIZE<_T> size)    { PNT = pnt; SIZE = size; }
		inline bool operator == (TRECT &A) { return PNT == A.PNT && SIZE == A.SIZE; }
		inline bool operator != (TRECT &A) { return PNT != A.PNT || SIZE != A.SIZE; }
		inline void operator =  (TRECT &A) { PNT=A.PNT; SIZE=A.SIZE; }
		inline TRECT<_T> GetBound(){return TRECT<_T>(0,0,SIZE.W-PNT.X,SIZE.H-PNT.Y);}
		inline TPNT<_T> GetCenter(){return TPNT<_T>(PNT.X+SIZE.W/2, PNT.Y+SIZE.H/2);}
		
		inline TRECT operator += (TPNT<_T> pnt) { PNT+=pnt; return *this; }
		inline TRECT operator -= (TPNT<_T> pnt) { PNT-=pnt; return *this; }
		
	public:
		TPNT<_T> PNT;
		TSIZE<_T> SIZE;
	};
*/
///*
// 修改类型
template <class _T>
class TRECT2
{
public:
	_T xmin, ymin, xmax, ymax;

	void SetData(_T _xmin,_T _ymin,_T _xmax,_T _ymax) { xmin=_xmin; ymin=_ymin;xmax=_xmax;ymax=_ymax;};
	bool operator == (TRECT2 &A) { return xmin == A.xmin && ymin == A.ymin && xmax == A.xmax && ymax == A.ymax; }
	bool operator != (TRECT2 &A) { return xmin != A.xmin || ymin != A.ymin || xmax != A.xmax || ymax != A.ymax; }
    _T width()  { return xmax-xmin;}
    _T height() { return ymax-ymin;}
  
};

//typedef TRECT<double> DRECT;
//typedef TRECT<float>  FRECT;
//typedef TRECT<int>    IRECT;
//typedef TRECT<long>   LRECT;
typedef TRECT2<long>  LRECT2; // 修改类型
//*/
/////////////////////////////////////////////////////
// Functions:
/*
template <class _T> inline bool _IS_PNT_IN_RECT( TPNT<_T> pnt, TRECT<_T> rect ) 
{ 
	if(pnt.X < rect.PNT.X || pnt.X > rect.PNT.X + rect.SIZE.W)
		return false;
	if(pnt.Y < rect.PNT.Y || pnt.Y > rect.PNT.Y + rect.SIZE.H)
		return false;
	return true;
}*/

template <class _T> inline void SAFE_DELETE(_T* &p) 
{ 
	if(p) {delete p;  p=0; }
}

#include "ut_std.h"

#endif
//______________________________________________文件结束__________________________________________
