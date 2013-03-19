
# import "Core.h"
# import "NGBase.h"
# import "../Math/Math+NNT.h"

NNT_BEGIN_OBJC

CGPoint CGRectCenterPoint(CGRect const* rc) {
    CGPoint pt;
    pt.x = rc->origin.x + rc->size.width * .5f;
    pt.y = rc->origin.y + rc->size.height * .5f;
    return pt;
}

CGPoint CGRectCenterPoint2(CGRect rc) {
    CGPoint pt;
    pt.x = rc.origin.x + rc.size.width * .5f;
    pt.y = rc.origin.y + rc.size.height * .5f;
    return pt;
}

real CGPaddingGetWidth(CGPadding const* pd) {
    return pd->right + pd->left;
}

real CGPaddingGetHeight(CGPadding const* pd) {
    return pd->bottom + pd->top;
}

const CGPadding CGPaddingZero = {0, 0, 0, 0};
const CGMargin CGMarginZero = {0, 0, 0, 0};

CGFloat CGRectBottom(CGRect rc) {
    return rc.origin.y + rc.size.height;
}

CGPoint CGRectRightTop(CGRect const* rc) {
    CGPoint pt = rc->origin;
    pt.x += rc->size.width;
    return pt;
}

CGPoint CGRectRightTop2(CGRect rc) {
    CGPoint pt = rc.origin;
    pt.x += rc.size.width;
    return pt;
}

CGPoint CGRectRightBottom(CGRect const* rc) {
    CGPoint pt = rc->origin;
    pt.x += rc->size.width;
    pt.y += rc->size.height;
    return pt;
}

CGPoint CGRectRightBottom2(CGRect rc) {
    CGPoint pt = rc.origin;
    pt.x += rc.size.width;
    pt.y += rc.size.height;
    return pt;
}

CGPoint CGRectLeftBottom(CGRect const* rc) {
    CGPoint pt = rc->origin;
    pt.y += rc->size.height;
    return pt;
}

CGPoint CGRectLeftBottom2(CGRect rc) {
    CGPoint pt = rc.origin;
    pt.y += rc.size.height;
    return pt;
}

CGPoint CGRectLeftCenter(CGRect const* rc) {
    CGPoint pt = rc->origin;
    pt.y += rc->size.height * .5f;
    return pt;
}

CGPoint CGRectLeftCenter2(CGRect rc) {
    CGPoint pt = rc.origin;
    pt.y += rc.size.height * .5f;
    return pt;
}

CGPoint CGRectRightCenter(CGRect const* rc) {
    CGPoint pt = CGRectRightTop(rc);
    pt.y += rc->size.height * .5f;
    return pt;
}

CGPoint CGRectRightCenter2(CGRect rc) {
    CGPoint pt = CGRectRightTop(&rc);
    pt.y += rc.size.height * .5f;
    return pt;
}

CGPoint CGRectTopCenter(CGRect const* rc) {
    CGPoint pt = rc->origin;
    pt.x += rc->size.width * .5f;
    return pt;
}

CGPoint CGRectTopCenter2(CGRect rc) {
    CGPoint pt = rc.origin;
    pt.x += rc.size.width * .5f;
    return pt;
}

CGPoint CGRectBottomCenter(CGRect const* rc) {
    CGPoint pt = CGRectLeftBottom(rc);
    pt.x += rc->size.width * .5f;
    return pt;
}

CGPoint CGRectBottomCenter2(CGRect rc) {
    CGPoint pt = CGRectLeftBottom(&rc);
    pt.x += rc.size.width * .5f;
    return pt;
}

CGRect CGRectDeflateCenter(CGRect src, CGFloat x, CGFloat y) {
    return CGRectMake(src.origin.x + x, src.origin.y + y,
                      src.size.width - x - x, src.size.height - y - y);
}

CGRect CGRectDeflateCenterR(CGRect src, CGFloat x, CGFloat y) {
    real hx = src.size.width * x * .5f;
    real hy = src.size.height * y * .5f;
    return CGRectMake(src.origin.x + hx, src.origin.y + hy,
                      src.size.width - hx - hx, src.size.height - hy - hy);
}

CGPadding CGPaddingMake(real t, real b, real l, real r) {
    CGPadding ret = {t, b, l, r};
    return ret;
}

CGMargin CGMarginMake(real t, real b, real l, real r) {
    CGMargin ret = {t, b, l, r};
    return ret;
}

CGRect CGRectSwap(CGRect const* rc) {
    CGRect ret;
    ret.origin.x = rc->origin.y;
    ret.origin.y = rc->origin.x;
    ret.size.width = rc->size.height;
    ret.size.height = rc->size.width;
    return ret;
}

CGRect  CGRectAddWidth2(CGRect rc, CGFloat val) {
    rc.size.width += val;
    return rc;
}

CGRect  CGRectAddHeight2(CGRect rc, CGFloat val) {
    rc.size.height += val;
    return rc;
}

CGRect  CGRectAddX2(CGRect rc, CGFloat val) {
    rc.origin.x += val;
    return rc;
}

CGRect  CGRectAddY2(CGRect rc, CGFloat val) {
    rc.origin.y += val;
    return rc;
}

CGRect  CGRectAdd2(CGRect rc, CGFloat x, CGFloat y, CGFloat w, CGFloat h) {
    rc.origin.x += x;
    rc.origin.y += y;
    rc.size.width += w;
    rc.size.height += h;
    return rc;
}

CGRect CGRectMoveCenter(CGRect src, CGPoint pt) {
    CGPoint spt = CGRectCenterPoint(&src);
    real off_x = spt.x - pt.x;
    real off_y = spt.y - pt.y;
    src.origin.x -= off_x;
    src.origin.y -= off_y;
    return src;
}

CGRect  CGRectSetRatioPadding(CGRect rc, CGPadding pd) {
    real dl = rc.size.width * pd.left;
    real dr = rc.size.width * pd.right;
    real dt = rc.size.height * pd.top;
    real db = rc.size.height * pd.bottom;
    return CGRectAdd2(rc, dl, dt, -dl - dr, -dt - db);
}

CGRect  CGRectToSquare(CGRect const* rc) {
    CGPoint pt_center = CGRectCenterPoint(rc);
    CGRect rect = *rc;
    rect.size.width = MIN(rect.size.width, rect.size.height);
    rect.size.height = rect.size.width;
    return CGRectMoveCenter(rect, pt_center);
}

CGRect  CGRectToSquare2(CGRect rc) {
    CGPoint pt_center = CGRectCenterPoint(&rc);
    rc.size.width = MIN(rc.size.width, rc.size.height);
    rc.size.height = rc.size.width;
    return CGRectMoveCenter(rc, pt_center);
}

BOOL CGPointEqualWithPrecise(CGPoint l, CGPoint r, int precise) {
    real distance = distance_points2d(l.x, l.y, r.x, r.y);
    return distance < precise;
}

CGRect CGRectContract(CGRect rect, CGFloat dx, CGFloat dy) {
    return CGRectMake(rect.origin.x, rect.origin.y, rect.size.width - dx, rect.size.height - dy);
}

CGRect CGRectShift(CGRect rect, CGFloat dx, CGFloat dy) {
    return CGRectOffset(CGRectContract(rect, dx, dy), dx, dy);
}

CGRect CGRectInsetWithInset(CGRect rect, UIEdgeInsets insets) {
    return CGRectMake(rect.origin.x + insets.left, rect.origin.y + insets.top,
                      rect.size.width - (insets.left + insets.right),
                      rect.size.height - (insets.top + insets.bottom));
}

CGRect CGRectMakeRectByCenter(CGRect const* pt, CGFloat width, CGFloat height) {
    CGPoint center = CGRectCenterPoint(pt);
    CGRect rc = CGRectMake(0, 0, width, height);
    return CGRectMoveCenter(rc, center);
}

CGRect CGRectMakeRectByCenter2(CGRect rc, CGFloat width, CGFloat height) {
    return CGRectMakeRectByCenter(&rc, width, height);
}

CGRect CGRectDeflateR(CGRect src, CGFloat l, CGFloat r, CGFloat t, CGFloat b) {
    CGRect rc;
    rc.origin.x = src.origin.x + src.size.width * l;
    rc.origin.y = src.origin.y + src.size.height * t;
    rc.size.width = src.size.width - src.size.width * l - src.size.width * r;
    rc.size.height = src.size.height - src.size.height * t - src.size.height * b;
    return rc;
}

CGRect CGRectOffsetR(CGRect rect, CGFloat rw, CGFloat rh) {
    rect.origin.x += rect.size.width * rw;
    rect.origin.y += rect.size.height * rh;
    return rect;
}

CGRect CGRectBound(CGRect rect, BOOL max) {
    CGFloat val = max ? MAX(rect.size.width, rect.size.height) : MIN(rect.size.width, rect.size.height);
    rect.size.width = rect.size.height = val;
    return rect;
}

NNT_END_OBJC
