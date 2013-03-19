/***********************************************************************/
/*                                                                     */
/* IASRect.hpp                                                         */
/* ADMRect object wrapper class                                         */
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

#ifndef __IASRect_hpp__
#define __IASRect_hpp__

/*
 * Includes
 */
 
#ifndef __ASTypes__
#include "ASTypes.h"
#endif

/*
 * Wrapper Class
 */

class IASRect : public ADMRect
{
public:	
	IASRect();
	IASRect(const ADMRect& rect);
	IASRect(const ADMPoint& a);
	IASRect(const ADMPoint& a, const ADMPoint& b);
	IASRect(int left, int top, int right, int bottom);
	
	int Width() const;
	int Height() const;
	
	ASBoolean IsEmpty() const;
	void SetEmpty();
	
	ASBoolean IsNormalized() const;	
	void Normalize();

	int Area() const;
	
	ADMPoint Center() const;
	
	ASBoolean Contains(const ADMPoint& p) const;
	ASBoolean Contains(const ADMRect& r) const;
	
	ASBoolean Overlaps(const ADMRect& r) const;
	
	IASRect& operator ++ ();
	IASRect& operator -- ();
	IASRect operator ++ (int);
	IASRect operator -- (int);
	IASRect& operator += (int n);
	IASRect& operator -= (int n);
	
	IASRect& operator += (ADMPoint& p);
	IASRect& operator -= (ADMPoint& p);
	
	IASRect& operator = (ADMPoint& p);
	
	void Inset(int h, int v);
	void Inflate(int h, int v);
	void Offset(int h, int v);
	
	void Union(const ADMPoint& a);
	void Union(const ADMRect& a);
	void Union(const ADMRect& a, const ADMRect& b);
	
	void Intersect(const ADMRect& a);
	void Intersect(const ADMRect& a, const ADMRect& b);
	
	void Center(const ADMRect& centerRect);
	
	friend inline ASBoolean operator == (const ADMRect& a, const ADMRect& b);
	friend inline ASBoolean operator != (const ADMRect& a, const ADMRect& b);

// Doesn't work in CodeWarrior 1.4.  Anyone know why?  DRL 4/22/96	
//	friend inline ADMRect operator + (const IASRect& a, const IASPoint& b);
//	friend inline ADMRect operator + (const IASPoint& a, const IASRect& b);
//	friend inline ADMRect operator - (const IASRect& a, const IASPoint& b);
//	friend inline ADMRect operator - (const IASPoint& a, const IASRect& b);
};

inline IASRect::IASRect() 					
{
}

inline IASRect::IASRect(const ADMRect& rect) 
{ 
	left = rect.left;
	top = rect.top;
	right = rect.right;
	bottom = rect.bottom; 
}

inline IASRect::IASRect(const ADMPoint& a)	
{ 
	left = right = a.h; 
	top = bottom = a.v; 
}

inline IASRect::IASRect(const ADMPoint& a, const ADMPoint& b)
{
	if (a.h < b.h)
	{
		left = a.h;
		right = b.h;
	}
	else
	{
		left = b.h;
		right = a.h;
	}
	
	if (a.v < b.v)
	{
		top = a.v;
		bottom = b.v;
	}
	else
	{
		top = b.v;
		bottom = a.v;
	}
}

inline IASRect::IASRect(int left, int top, int right, int bottom)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

inline int IASRect::Width()	const				
{ 
	return right - left; 
}

inline int IASRect::Height() const			
{ 
	return bottom - top; 
}

inline ASBoolean IASRect::IsEmpty()	const		
{ 
	return top == bottom && right == left; 
}

inline void IASRect::SetEmpty()				
{ 
	left = top = right = bottom = 0; 
}

inline ASBoolean IASRect::IsNormalized() const
{
	return left <= right && top <= bottom;
}

inline void IASRect::Normalize()
{
	if (left > right) 
	{
		int saveLeft = left; left = right; right = saveLeft;
	}
	if (top > bottom)
	{
		int saveTop = top; top = bottom; bottom = saveTop;
	}
}

inline int IASRect::Area() const					
{ 
	return Width() * Height(); 
}

inline ADMPoint IASRect::Center() const
{
	ADMPoint center;
	
	center.h = left + Width() / 2;
	center.v = top + Height() / 2;
	
	return center;
}

inline ASBoolean IASRect::Contains(const ADMPoint& p) const
{
	return left <= p.h && right >= p.h && top <= p.v && bottom >= p.v;
}

inline ASBoolean IASRect::Contains(const ADMRect& r) const
{
	return left <= r.left && right >= r.left && top <= r.top && bottom >= r.top &&
		   left <= r.right && right >= r.right && top <= r.bottom && bottom >= r.bottom;
}

inline ASBoolean IASRect::Overlaps(const ADMRect& r) const
{
	return  right  >= r.left && left <= r.right  && 
		    bottom >= r.top  && top  <= r.bottom;
}

inline IASRect& IASRect::operator ++ ()
{ 
	left--; 
	top--; 
	right++; 
	bottom++; 
	
	return *this; 
}

inline IASRect& IASRect::operator -- ()		
{ 	
	left++; 
	top++; 
	right--; 
	bottom--; 
	
	return *this; 
}

inline IASRect IASRect::operator ++ (int)
{ 
	left--; 
	top--; 
	right++; 
	bottom++; 
	
	return *this; 
}

inline IASRect IASRect::operator -- (int)		
{ 
	left++; 
	top++; 
	right--; 
	bottom--; 
	
	return *this; 
}

inline IASRect& IASRect::operator += (int n)	
{ 
	left -= n; 
	top -= n; 
	right += n; 
	bottom += n; 
	
	return *this; 
}

inline IASRect& IASRect::operator -= (int n)
{ 
	left += n; 
	top += n; 
	right -= n; 
	bottom -= n; 
	
	return *this; 
}

inline IASRect& IASRect::operator += (ADMPoint& p)	
{ 
	left += p.h; 
	top += p.v; 
	right += p.h; 
	bottom += p.v; 
	
	return *this; 
}

inline IASRect& IASRect::operator -= (ADMPoint& p)
{ 
	left -= p.h; 
	top -= p.v; 
	right -= p.h; 
	bottom -= p.v; 
	
	return *this; 
}

	
inline IASRect& IASRect::operator = (ADMPoint& p)
{
	left = right = p.h;
	top = bottom = p.h;
	
	return *this;
}

inline ASBoolean operator == (const ADMRect& a, const ADMRect& b)
{
	return a.left == b.left &&
		   a.top == b.top &&
		   a.right == b.right &&
		   a.bottom == b.bottom;
}

inline ASBoolean operator != (const ADMRect& a, const ADMRect& b)
{
	return a.left != b.left ||
		   a.top != b.top ||
		   a.right != b.right ||
		   a.bottom != b.bottom;
}

inline void IASRect::Inset(int h, int v)
{ 
	left += h; 
	top += v; 
	right -= h; 
	bottom -= v; 
}	

inline void IASRect::Inflate(int h, int v)
{ 
	left -= h; 
	top -= v; 
	right += h; 
	bottom += v; 
}	

inline void IASRect::Offset(int h, int v)
{ 
	left += h; 
	top += v; 
	right += h; 
	bottom += v; 
}	

inline void IASRect::Union(const ADMPoint& a)
{
	if (left > a.h)
		left = a.h;
	if (top > a.v)
		top = a.v;
	if (right < a.h)
		right = a.h;
	if (bottom < a.v)
		bottom = a.v; 
}

inline void IASRect::Union(const ADMRect& a)
{
	if (left > a.left)
		left = a.left;
	if (top > a.top)
		top = a.top;
	if (right < a.right)
		right = a.right;
	if (bottom < a.bottom)
		bottom = a.bottom; 
}

inline void IASRect::Union(const ADMRect& a, const ADMRect& b)
{
	if (b.left > a.left)
		left = a.left;
	else
		left = b.left;
	if (b.top > a.top)
		top = a.top;
	else
		top = b.top;
	if (b.right < a.right)
		right = a.right;
	else
		right = b.right;
	if (b.bottom < a.bottom)
		bottom = a.bottom;
	else
		bottom = b.bottom; 
}

inline void IASRect::Intersect(const ADMRect& a)
{
	if (left < a.left)
		left = a.left;
	if (top < a.top)
		top = a.top;
	if (right > a.right)
		right = a.right;
	if (bottom > a.bottom)
		bottom = a.bottom;
		
	if (!Overlaps(a))
		SetEmpty();	
}

inline void IASRect::Intersect(const ADMRect& a, const ADMRect& b)
{
	if (b.left < a.left)
		left = a.left;
	else
		left = b.left;
	if (b.top < a.top)
		top = a.top;
	else
		top = b.top;
	if (b.right > a.right)
		right = a.right;
	else
		right = b.right;
	if (b.bottom > a.bottom)
		bottom = a.bottom;
	else
		bottom = b.bottom;			
	if (!Overlaps(a))
		SetEmpty();	
} 

inline void IASRect::Center(const ADMRect& centerRect)
{
	Offset(centerRect.left + ((centerRect.right - centerRect.left) - Width()) / 2,
		   centerRect.top + ((centerRect.bottom - centerRect.top) - Height()) / 2);
}

/*
 * Doesn't work in CodeWarrior 1.4.  Anyone know why?  DRL 4/22/96.
inline ADMRect operator + (const IASRect& a, const IASPoint& b)
{
	return IASRect(a.left + b.h, a.top + b.v, a.right + b.h, a.bottom + b.v);
}

inline ADMRect operator + (const IASPoint& a, const IASRect& b)
{
	IASRect r;
	
	r.left = b.left + a.h;
	r.top = b.top + a.v;
	r.right = b.right + a.h;
	r.bottom = b.bottom + a.v;
	
	return r;
}

inline ADMRect operator - (const IASRect& a, const IASPoint& b)
{
	IASRect r;
	
	r.left = a.left - b.h;
	r.top = a.top - b.v;
	r.right = a.right - b.h;
	r.bottom = a.bottom - b.v;
	
	return r;
}

inline ADMRect operator - (const IASPoint& a, const IASRect& b)
{
	IASRect r;
	
	r.left = b.left - a.h;
	r.top = b.top - a.v;
	r.right = b.right - a.h;
	r.bottom = b.bottom - a.v;
	
	return r;
}
*/

#endif
