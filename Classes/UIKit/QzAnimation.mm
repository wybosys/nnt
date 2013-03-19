
# import "Core.h"
# import "QzAnimation.h"

WSI_BEGIN_OBJC

@implementation __cxxobject_qzanimation

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalAnimationStart)
WSIEVENT_SIGNAL(kSignalAnimationStop)
WSIEVENT_END

- (void)animationDidStart:(CAAnimation *)anim {
    [self emit:kSignalAnimationStart];
}

- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag {    
    [self emit:kSignalAnimationStop];
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(qz)

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

WSI_END_NS
WSI_END_CXX
