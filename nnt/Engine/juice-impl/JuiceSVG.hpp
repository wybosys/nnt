
# ifndef __JUICEIMPL_COCOA_SVG_8BBD0B27C9A94C679D48BA6F280F41A3_H_INCLUDED
# define __JUICEIMPL_COCOA_SVG_8BBD0B27C9A94C679D48BA6F280F41A3_H_INCLUDED

# include "../../Parser/SVGParser.h"

JUICE_BEGIN NNT_BEGIN_NS(svg)

template <typename pathT>
void __callback_load(::nnt::svg::PathParser::Action const* _act, void* ctx)
{
    pathT* path = (pathT*)ctx;
    switch (_act->type)    
    {
        default: 
        {
            trace_msg(@"svg:: unknown action");
        } break;
        case ::nnt::svg::PathParser::PA_MOVETO:
        {
            ::nnt::svg::PathParser::Moveto* act = (::nnt::svg::PathParser::Moveto*)_act;
            path->move_to(act->pt);
        } break;
        case ::nnt::svg::PathParser::PA_LINETO:
        {
            ::nnt::svg::PathParser::Lineto* act = (::nnt::svg::PathParser::Lineto*)_act;
            path->line_to(act->pt);
        } break;
        case ::nnt::svg::PathParser::PA_CURVETO:
        {
            ::nnt::svg::PathParser::Curveto* act = (::nnt::svg::PathParser::Curveto*)_act;
            path->add_curve(act->c1, act->c2, act->pt);
        } break;
        case ::nnt::svg::PathParser::PA_QUADCURVETO:
        {
            ::nnt::svg::PathParser::QuadCurveto* act = (::nnt::svg::PathParser::QuadCurveto*)_act;
            path->add_quadcurve(act->c, act->pt);
        } break;
        case ::nnt::svg::PathParser::PA_CLOSE:
        {
            path->close();
        } break;            
    }
}

template <typename pathT>
static bool load(pathT& path, ::nnt::core::string const& str)
{
    ::nnt::svg::PathParser svg;
    if (!svg.parse(str, __callback_load<pathT>, &path))
        return false;
    return true;
}

NNT_END_NS JUICE_END

# endif