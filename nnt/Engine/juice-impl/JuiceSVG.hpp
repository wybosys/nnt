
# ifndef __JUICEIMPL_COCOA_SVG_8BBD0B27C9A94C679D48BA6F280F41A3_H_INCLUDED
# define __JUICEIMPL_COCOA_SVG_8BBD0B27C9A94C679D48BA6F280F41A3_H_INCLUDED

# include "../../Parser/SVGParser.h"

JUICE_BEGIN WSI_BEGIN_NS(svg)

template <typename pathT>
void __callback_load(::wsi::svg::PathParser::Action const* _act, void* ctx)
{
    pathT* path = (pathT*)ctx;
    switch (_act->type)    
    {
        default: 
        {
            trace_msg(@"svg:: unknown action");
        } break;
        case ::wsi::svg::PathParser::PA_MOVETO:
        {
            ::wsi::svg::PathParser::Moveto* act = (::wsi::svg::PathParser::Moveto*)_act;
            path->move_to(act->pt);
        } break;
        case ::wsi::svg::PathParser::PA_LINETO:
        {
            ::wsi::svg::PathParser::Lineto* act = (::wsi::svg::PathParser::Lineto*)_act;
            path->line_to(act->pt);
        } break;
        case ::wsi::svg::PathParser::PA_CURVETO:
        {
            ::wsi::svg::PathParser::Curveto* act = (::wsi::svg::PathParser::Curveto*)_act;
            path->add_curve(act->c1, act->c2, act->pt);
        } break;
        case ::wsi::svg::PathParser::PA_QUADCURVETO:
        {
            ::wsi::svg::PathParser::QuadCurveto* act = (::wsi::svg::PathParser::QuadCurveto*)_act;
            path->add_quadcurve(act->c, act->pt);
        } break;
        case ::wsi::svg::PathParser::PA_CLOSE:
        {
            path->close();
        } break;            
    }
}

template <typename pathT>
static bool load(pathT& path, ::wsi::core::string const& str)
{
    ::wsi::svg::PathParser svg;
    if (!svg.parse(str, __callback_load<pathT>, &path))
        return false;
    return true;
}

WSI_END_NS JUICE_END

# endif