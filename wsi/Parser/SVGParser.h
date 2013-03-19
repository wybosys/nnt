
# ifndef __WSI_PARSER_SVG_A9AB25A52E1747AF8F8E75012807B9AA_H_INCLUDED
# define __WSI_PARSER_SVG_A9AB25A52E1747AF8F8E75012807B9AA_H_INCLUDED

WSI_BEGIN_HEADER_CXX WSI_BEGIN_NS(svg)

struct Point
{
    Point() : x(0), y(0) {}
    
    real x, y;
    
    Point& operator += (Point const& r)
    {
        x += r.x;
        y += r.y;
        return *this;
    }
    
};

class PathParser
{
protected:
    
    enum PATH_ACTION_RELV
    {
        PA_MOVETO_RELV = 'm', // M = moveto relv
        PA_LINETO_RELV = 'l', // L = lineto relv
        PA_HORLINETO_RELV = 'h', // H = horizontal lineto relv
        PA_VECLINETO_RELV = 'v', // V = vertical lineto relv
        PA_CURVETO_RELV = 'c', // C = curveto relv
        PA_SMCURVETO_RELV = 's', // S = smooth curveto relv
        PA_QUADCURVETO_RELV = 'q', // Q = quadratic Belzier curve relv
        PA_SMQUADCURVETO_RELV = 't', // T = smooth quadratic Belzier curveto relv
        PA_ELLIPTICAL_RELV = 'a', // A = elliptical Arc relv
        PA_CLOSE_RELV = 'z', // Z = closepath relv
    };
    
public:    
    
    enum PATH_ACTION 
    {        
        PA_MOVETO = 'M', // M = moveto
        PA_LINETO = 'L', // L = lineto
        PA_HORLINETO = 'H', // H = horizontal lineto
        PA_VECLINETO = 'V', // V = vertical lineto
        PA_CURVETO = 'C', // C = curveto
        PA_SMCURVETO = 'S', // S = smooth curveto
        PA_QUADCURVETO = 'Q', // Q = quadratic Belzier curve
        PA_SMQUADCURVETO = 'T', // T = smooth quadratic Belzier curveto
        PA_ELLIPTICAL = 'A', // A = elliptical Arc
        PA_CLOSE = 'Z', // Z = closepath        
    };    
    
    struct Action
    {
        Action() : pre(0), next(0) {}
        Action* pre;
        Action* next;
        PATH_ACTION type;
    };
    
    struct Moveto : Action
    {
        Moveto() { type = PA_MOVETO; }
        Point pt;
    };
    
    struct Lineto : Action
    {
        Lineto() { type = PA_LINETO; }
        Point pt;
    };
    
    struct Curveto : Action
    {
        Curveto() { type = PA_CURVETO; }
        Point c1, c2, pt;
    };
    
    struct QuadCurveto: Action
    {
        QuadCurveto() { type = PA_QUADCURVETO; }
        Point c, pt;
    };
    
    struct EllipticalArcto: Action
    {
        EllipticalArcto() { type = PA_ELLIPTICAL; }
        Point rpt, pt;
        real x_axis_rotation;
        int large_arc_flag;
        int sweep_flag;
    };
    
    struct Close : Action
    {
        Close() { type = PA_CLOSE; }
    };
    
    PathParser();
    ~PathParser();
    
    typedef void (*callback_action)(Action const*, void* ctx);
    
    //! parse with callback.
    bool parse(core::string const&, callback_action, void* ctx);
    
};

WSI_END_NS WSI_END_HEADER_CXX

# endif