
# include "Core.h"
# include "Linear.h"
# include "Graphic+NNT.h"

NNT_BEGIN_C

BOOL CGLineIsHov(CGLine const* line) {
    return line->start.y == line->end.y;
}

BOOL CGLineIsVec(CGLine const* line) {
    return line->start.x == line->end.x;
}

BOOL CGLineIsIntersect(CGLine const* src, CGLine const* des) {
    if (CGLineIsHov(src) && CGLineIsHov(des))
        return NO;
    if (CGLineIsVec(src) && CGLineIsVec(des))
        return NO;    
    return YES;
}

real CGLineLength(CGLine const* line) {
    real x = (line->start.x - line->end.x);
    x *= x;
    real y = (line->start.y - line->end.y);
    y *= y;
    real r = x + y;
    r = sqrtf(r);
    return r;
}

real CGLineLengthQ(CGLine const* line) {
    real x = (line->start.x - line->end.x);
    x *= x;
    real y = (line->start.y - line->end.y);
    y *= y;
    real r = x + y;
    return r;
}

BOOL CGLineIsPointInPrec(CGLine const* line, CGPoint const* pt, real prec) {
    BOOL suc = NO;
    if (line->isSegment) {
        real len = CGLineLength(line);
        CGLine tmp_line;
        tmp_line.start = line->start;
        tmp_line.end = *pt;
        real tmp_0 = CGLineLength(&tmp_line);
        tmp_line.start = line->end;
        real tmp_1 = CGLineLength(&tmp_line);
        real sum = tmp_0 + tmp_1;
        sum = len - sum;    
        suc = (-prec < sum && sum < prec);
    } else if (line->isRadial) {
        CGLine tmp_line;
        tmp_line.start = line->start;
        tmp_line.end = *pt;
        tmp_line.isSegment = YES;
        suc = CGLineIsPointInPrec(&tmp_line, &line->end, prec);
        if (suc == NO) {
            tmp_line.end = line->end;
            suc = CGLineIsPointInPrec(&tmp_line, pt, prec);
        }
    } else {
        real k = CGLineK(line);
        real c = line->start.y - k * line->start.x;
        real v = pt->x * k + c;
        v = pt->y - v;
        suc = (-prec < v && v < prec);
    }
    return suc;
}

BOOL CGLineIsPointIn(CGLine const* line, CGPoint const* pt) {
    return CGLineIsPointInPrec(line, pt, kLinearPrecision);
}

CGPoint CGLineIntersect(CGLine const* src, CGLine const* des) {
    CGPoint ret;
    
    if (CGLineIsVec(src)) {
        real kdes = CGLineK(des);
        real cdes = des->start.y - kdes * des->start.x;
        ret.x = src->start.x;
        ret.y = kdes * ret.x + cdes;
    } else if (CGLineIsVec(des)) {
        real ksrc = CGLineK(src);
        real csrc = src->start.y - ksrc * src->start.x;
        ret.x = des->start.x;
        ret.y = ksrc * ret.x + csrc;
    } else {
        real kdes = CGLineK(des);
        real ksrc = CGLineK(src);
        real cdes = des->start.y - kdes * des->start.x;
        real csrc = src->start.y - ksrc * src->start.x;;
        ret.x = (cdes - csrc) / (ksrc - kdes);
        ret.y = kdes * ret.x + cdes;
    }
    
    return ret;
}

real CGLineK(CGLine const* line) {
    real dy = (line->end.y - line->start.y);
    real dx = (line->end.x - line->start.x);
    return dy / dx;
}

CGLine CGRectIntersect(CGRect const* rect, CGLine const* line) {
    CGLine ret;
    CGRectLines lines = CGRectGetLines(rect);
    
    ret.start = CGPointZero;
    ret.end = CGPointZero;
    ret.isValid = FALSE;
    int suc = 0;
    
    if (CGLineIsIntersect(&lines.t, line)) {
        CGPoint pt = CGLineIntersect(&lines.t, line);
        if (CGLineIsPointIn(line, &pt)) {
            if (suc) { 
                ret.end = pt;
            } else {
                ret.start = pt;
                suc += 1;
            }
        }
    }
    
    if (CGLineIsIntersect(&lines.l, line)) {
        CGPoint pt = CGLineIntersect(&lines.l, line);
        if (CGLineIsPointIn(line, &pt)) {
            if (suc) { 
                ret.end = pt;
            } else {
                ret.start = pt;
                suc += 1;
            }
        }
    }
    
    if (CGLineIsIntersect(&lines.r, line)) {
        CGPoint pt = CGLineIntersect(&lines.r, line);
        if (CGLineIsPointIn(line, &pt)) {
            if (suc) { 
                ret.end = pt;
            } else {
                ret.start = pt;
                suc += 1;
            }
        }
    }
    
    if (CGLineIsIntersect(&lines.b, line)) {
        CGPoint pt = CGLineIntersect(&lines.b, line);
        if (CGLineIsPointIn(line, &pt)) {
            if (suc) { 
                ret.end = pt;
            } else {
                ret.start = pt;
                suc += 1;
            }
        }
    }
    
    ret.isValid = suc == 2;

    return ret;
}

CGRectLines CGRectGetLines(CGRect const* rect) {
    CGPoint lt = rect->origin;
    CGPoint rt = CGRectRightTop(rect);
    CGPoint lb = CGRectRightBottom(rect);
    CGPoint rb = CGRectRightBottom(rect);
    CGRectLines ret;
    ret.t.start = lt; ret.t.end = rt;
    ret.l.start = lt; ret.l.end = lb;
    ret.b.start = lb; ret.b.end = rb;
    ret.r.start = rt; ret.r.end = rb;
    return ret;
}

CGLine CGLineRotate(CGLine const* line, real rad) {
    CGLine ret;
    ret.isSegment = line->isSegment;
    ret.isRadial = line->isRadial;
    
    if (CGLineIsHov(line) && CGLineIsVec(line)) {
        ret.start = line->start;
        ret.end = CGPointMake(-line->end.y, line->end.x);
    } else {
        /*ret.start = line->start;
        real k = CGLineK(line);
        real tht = atanf(k);
        tht += rad;
        k = tanf(tht);*/
    }
    
    return ret;
}

CGPoint CGLineCenter(CGLine const* line) {
    CGPoint ret;
    ret.x = (line->end.x - line->start.x) * .5f;
    ret.y = (line->end.y - line->start.y) * .5f;
    return ret;
}

NNT_END_C
