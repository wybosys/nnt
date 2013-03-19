/***********************************************************************/
/*                                                                     */
/* IASPoint.hpp                                                        */
/* ADMPoint object wrapper class                                        */
/*                                                                     */
/* Copyright 1996-1999 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* Patents Pending                                                     */
/*                                                                     */
/* NOTICE: All information contained herein is the property of Adobe   */
/* Systems Incorporated. Many of the intellectual and technical        */
/* concepts contained herein are proprietary to Adobe, are protected   */
/* as trade secrets, and are made available only to Adobe licensees    */
/* for their internal use. Any reproduction or dissemination of this   */
/* software is strictly forbidden unless prior written permission is   */
/* obtained from Adobe.                                                */
/*                                                                     */
/* Started by Dave Lazarony, 03/26/1996                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IASPoint_hpp__
#define __IASPoint_hpp__

/*
 * Includes
 */
 
#ifndef __ASTypes__
#include "ASTypes.h"
#endif

/*
 * Wrapper Class
 */

class IASPoint : public ADMPoint
{
public:	
	IASPoint();
	IASPoint(const ADMPoint& p);
	IASPoint(int h, int v);
	
	friend inline ASBoolean operator == (const ADMPoint& a, const ADMPoint& b);
	friend inline ASBoolean operator != (const ADMPoint& a, const ADMPoint& b);
	
	friend inline ADMPoint operator + (const ADMPoint& a, const ADMPoint& b);
	friend inline ADMPoint operator - (const ADMPoint& a, const ADMPoint& b);

	friend inline ADMPoint operator * (const ADMPoint& p, int s);
	friend inline ADMPoint operator * (int s, const ADMPoint& p);

	friend inline ADMPoint operator / (const ADMPoint& p, int s);

	friend inline ADMPoint operator - (const ADMPoint& p);

	void operator = (const ADMPoint& p);
	void operator += (const ADMPoint& p);
	void operator -= (const ADMPoint& p);

	void operator *= (int s);
	void operator /= (int s);
};

inline IASPoint::IASPoint()
{
}

inline IASPoint::IASPoint(const ADMPoint& p)	
{ 
	h = p.h; 
	v = p.v; 
}

inline IASPoint::IASPoint(int h, int v)
{ 
	this->h = h; this->v = v; 
}

inline ASBoolean operator == (const ADMPoint& a, const ADMPoint& b)
{
	return a.h == b.h && a.v == b.v;
}
	

inline ASBoolean operator != (const ADMPoint& a, const ADMPoint& b)
{
	return a.h != b.h || a.v != b.v;
}

inline ADMPoint operator + (const ADMPoint& a, const ADMPoint& b)
{
	return IASPoint(a.h + b.h, a.v + b.v);
}

inline ADMPoint operator - (const ADMPoint& a, const ADMPoint& b)
{
	return IASPoint(a.h - b.h, a.v - b.v);
}

inline ADMPoint operator * (const ADMPoint& p, int s)
{
	return IASPoint(p.h * s, p.v * s);
}

inline ADMPoint operator * (int s, const ADMPoint& p)
{
	return IASPoint(p.h * s, p.v * s);
}

inline ADMPoint operator / (const ADMPoint& p, int s)
{
	return IASPoint(p.h / s, p.v / s);
}

inline ADMPoint operator - (const ADMPoint& p)
{
	return IASPoint(-p.h, -p.v);
}

inline void IASPoint::operator = (const ADMPoint& p) 
{
	h = p.h;
	v = p.v;
}

inline void IASPoint::operator += (const ADMPoint& p) 
{ 
	h += p.h;
	v += p.v; 
}

inline void IASPoint::operator -= (const ADMPoint& p) 
{ 
	h -= p.h; 
	v -= p.v; 
}

inline void IASPoint::operator *= (int s)
{ 
	h *= s;
	v *= s; 
}

inline void IASPoint::operator /= (int s)
{
	h /= s;
	v /= s; 
}

#endif
