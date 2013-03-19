
# import "Core.h"
# import "QzAnimation.h"

NNT_BEGIN_OBJC

@implementation __cxxobject_qzanimation

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalAnimationStart)
NNTEVENT_SIGNAL(kSignalAnimationStop)
NNTEVENT_END

- (void)animationDidStart:(CAAnimation *)anim {
    [self emit:kSignalAnimationStart];
}

- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag {    
    [self emit:kSignalAnimationStop];
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(qz)

Transcation::Transcation()
{
    Transcation::Begin();
}

Transcation::~Transcation()
{
    Transcation::Commit();
}

void Transcation::Begin()
{
    [CATransaction begin];
}

void Transcation::Commit()
{
    [CATransaction commit];
}

void Transcation::Flush()
{
    [CATransaction flush];
}

void Transcation::Lock()
{
    [CATransaction lock];
}

void Transcation::Unlock()
{
    [CATransaction unlock];
}

Transcation::ValuePair Transcation::At(ns::String const& key)
{
    ValuePair ret;
    ret.key = key;
    ret.obj = [CATransaction valueForKey:key];
    return ret;
}

Transcation::ValuePair& Transcation::ValuePair::operator = (id obj)
{
    [CATransaction setValue:obj forKey:key];
    this->obj = obj;
    return *this;
}

NNT_END_NS
NNT_END_CXX
