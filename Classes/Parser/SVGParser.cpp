
# include "Core.h"
# include "SVGParser.h"
# include "../Core/Boost+NNT.h"

# ifdef NNT_MSVC
#   pragma warning (disable: 4244)
# endif

# include <boost/spirit/include/classic.hpp>

NNT_BEGIN_CXX 
NNT_BEGIN_NS(svg)

PathParser::PathParser()
{
    
}

PathParser::~PathParser()
{
    
}

template <typename iterT>
PathParser::Moveto* _load_moveto(iterT& iter, iterT& end)
{
    typedef ::boost::spirit::classic::parse_info<iterT> info_t;
    using ::boost::spirit::classic::real_p;
    using ::boost::spirit::classic::assign;
    using ::boost::spirit::classic::ch_p;
    using ::boost::spirit::classic::parse;
    using ::boost::spirit::classic::space_p;
    
    PathParser::Moveto* ret = new PathParser::Moveto;
    info_t res = parse<>(iter, end,
                         real_p[assign(ret->pt.x)] >> real_p[assign(ret->pt.y)],
                         space_p | ch_p(','));
    if (!res.hit)
    {
        safe_delete(ret);
        return NULL;
    }
    
    iter = res.stop;
    return ret;
}

template <typename iterT>
PathParser::Lineto* _load_lineto(iterT& iter, iterT& end, bool relv, Point& pos)
{
    typedef ::boost::spirit::classic::parse_info<iterT> info_t;
    using ::boost::spirit::classic::real_p;
    using ::boost::spirit::classic::assign;
    using ::boost::spirit::classic::ch_p;
    using ::boost::spirit::classic::parse;
    using ::boost::spirit::classic::space_p;
    
    PathParser::Lineto* ret = new PathParser::Lineto;
    info_t res = parse<>(iter, end,
                         real_p[assign(ret->pt.x)] >> real_p[assign(ret->pt.y)],
                         space_p | ch_p(','));
    if (!res.hit)
    {
        safe_delete(ret);
        return NULL;
    }
    
    if (relv)
    {
        ret->pt += pos;        
    }
    pos = ret->pt;
    
    iter = res.stop;
    return ret;
}

template <typename iterT>
PathParser::Lineto* _load_hlineto(iterT& iter, iterT& end, bool relv, Point& pos)
{
    typedef ::boost::spirit::classic::parse_info<iterT> info_t;
    using ::boost::spirit::classic::real_p;
    using ::boost::spirit::classic::assign;
    using ::boost::spirit::classic::ch_p;
    using ::boost::spirit::classic::parse;
    using ::boost::spirit::classic::space_p;
    
    PathParser::Lineto* ret = new PathParser::Lineto;
    info_t res = parse<>(iter, end,
                         real_p[assign(ret->pt.x)],
                         space_p | ch_p(','));
    if (!res.hit)
    {
        safe_delete(ret);
        return NULL;
    }
    
    if (relv)
    {
        ret->pt += pos;        
    }
    else
    {
        ret->pt.y = pos.y;
    }
    pos = ret->pt;
    
    iter = res.stop;
    return ret;
}

template <typename iterT>
PathParser::Lineto* _load_vlineto(iterT& iter, iterT& end, bool relv, Point& pos)
{
    typedef ::boost::spirit::classic::parse_info<iterT> info_t;
    using ::boost::spirit::classic::real_p;
    using ::boost::spirit::classic::assign;
    using ::boost::spirit::classic::ch_p;
    using ::boost::spirit::classic::parse;
    using ::boost::spirit::classic::space_p;
    
    PathParser::Lineto* ret = new PathParser::Lineto;
    info_t res = parse<>(iter, end,
                         real_p[assign(ret->pt.y)],
                         space_p | ch_p(','));
    if (!res.hit)
    {
        safe_delete(ret);
        return NULL;
    }
    
    if (relv)
    {
        ret->pt += pos;        
    }
    else
    {
        ret->pt.x = pos.x;
    }
    pos = ret->pt;
    
    iter = res.stop;
    return ret;
}

template <typename iterT>
PathParser::Curveto* _load_curveto(iterT& iter, iterT const& end, bool relv, Point& pos)
{
    typedef ::boost::spirit::classic::parse_info<iterT> info_t;
    using ::boost::spirit::classic::real_p;
    using ::boost::spirit::classic::assign;
    using ::boost::spirit::classic::ch_p;
    using ::boost::spirit::classic::parse;
    using ::boost::spirit::classic::space_p;
    
    PathParser::Curveto* ret = new PathParser::Curveto;
    info_t res = parse<>(iter, end,
                         real_p[assign(ret->c1.x)] >> real_p[assign(ret->c1.y)] >>
                         real_p[assign(ret->c2.x)] >> real_p[assign(ret->c2.y)] >>
                         real_p[assign(ret->pt.x)] >> real_p[assign(ret->pt.y)],
                         space_p | ch_p(','));
    if (!res.hit)
    {
        safe_delete(ret);
        return NULL;
    }
    
    if (relv)
    {
        ret->c1 += pos;
        ret->c2 += pos;
        ret->pt += pos;        
    }
    pos = ret->pt;
    
    iter = res.stop;
    return ret;
}

template <typename iterT>
PathParser::QuadCurveto* _load_quadcurveto(iterT& iter, iterT const& end, bool relv, Point& pos)
{
    typedef ::boost::spirit::classic::parse_info<iterT> info_t;
    using ::boost::spirit::classic::real_p;
    using ::boost::spirit::classic::assign;
    using ::boost::spirit::classic::ch_p;
    using ::boost::spirit::classic::parse;
    using ::boost::spirit::classic::space_p;
    
    PathParser::QuadCurveto* ret = new PathParser::QuadCurveto;
    info_t res = parse<>(iter, end,
                         real_p[assign(ret->c.x)] >> real_p[assign(ret->c.y)] >>
                         real_p[assign(ret->pt.x)] >> real_p[assign(ret->pt.y)],
                         space_p | ch_p(','));
    if (!res.hit)
    {
        safe_delete(ret);
        return NULL;
    }
    
    if (relv)
    {
        ret->c += pos;
        ret->pt += pos;        
    }
    pos = ret->pt;
    
    iter = res.stop;
    return ret;
}

template <typename iterT>
PathParser::EllipticalArcto* _load_elliptical(iterT& iter, iterT const& end, bool relv, Point& pos)
{
    typedef ::boost::spirit::classic::parse_info<iterT> info_t;
    using ::boost::spirit::classic::real_p;
    using ::boost::spirit::classic::int_p;
    using ::boost::spirit::classic::assign;
    using ::boost::spirit::classic::ch_p;
    using ::boost::spirit::classic::parse;
    using ::boost::spirit::classic::space_p;
    
    PathParser::EllipticalArcto* ret = new PathParser::EllipticalArcto;
    info_t res = parse<>(iter, end,
                         real_p[assign(ret->rpt.x)] >> real_p[assign(ret->rpt.y)] >>
                         real_p[assign(ret->x_axis_rotation)] >>
                         int_p[assign(ret->large_arc_flag)] >> int_p[assign(ret->sweep_flag)] >>
                         real_p[assign(ret->pt.x)] >> real_p[assign(ret->pt.y)],
                         space_p | ch_p(','));
    if (!res.hit)
    {
        safe_delete(ret);
        return NULL;
    }
    
    if (relv)
    {
        ret->rpt += pos;
        ret->pt += pos;        
    }
    pos = ret->pt;
    
    iter = res.stop;
    return ret;
}

bool PathParser::parse(const core::string & _str, callback_action act, void* ctx)
{                
    core::string::const_iterator iter = _str.begin();
    core::string::const_iterator end = _str.end();
    
    Action* last = NULL;
    Point pos;
    
    while (iter != end)
    {
        char c = *iter++;
        if (c == ' ')
        {
            if (last == NULL) 
            {
                continue;      
            }
            else
            {
                c = last->type;
            }
        }                                
        safe_delete(last);
        
        // if is relv.
        bool relv = false;
        switch (c)
        {
            case PA_MOVETO_RELV:
            case PA_LINETO_RELV:
            case PA_HORLINETO_RELV:
            case PA_VECLINETO_RELV:
            case PA_CURVETO_RELV:
            case PA_SMCURVETO_RELV:
            case PA_QUADCURVETO_RELV:
            case PA_SMQUADCURVETO_RELV:
            case PA_ELLIPTICAL_RELV:
            case PA_CLOSE:
            {
                relv = true;
            } break;
        };
                
        c = ::std::toupper(c);
        switch (c)
        {
            default: {
            } break;
            case PA_MOVETO:
            {
                last = _load_moveto(iter, end);
                if (last)
                {
                    Moveto* act = (Moveto*)last;
                    pos = act->pt;
                }
            } break;
            case PA_LINETO:
            {
                last = _load_lineto(iter, end, relv, pos);
            } break;
            case PA_HORLINETO:                
            {
                last = _load_hlineto(iter, end, relv, pos);
            } break;
            case PA_VECLINETO:                
            {
                last = _load_vlineto(iter, end, relv, pos);
            } break;
            case PA_CURVETO:
            {
                last = _load_curveto(iter, end, relv, pos);
            } break;
            case PA_SMCURVETO:
            {
                //last = _load_curveto(iter, end, relv, pos);
            } break;
            case PA_QUADCURVETO:
            {
                last = _load_quadcurveto(iter, end, relv, pos);
            } break;
            case PA_SMQUADCURVETO:
            {
                //last = _load_quadcurveto(iter, end, relv, pos);
            } break;
            case PA_ELLIPTICAL:
            {
                last = _load_elliptical(iter, end, relv, pos);
            } break;
            case PA_CLOSE:
            {
                last = new Close;
            } break;
        }
        
        if (last == NULL)
            continue;
        
        (*act)(last, ctx);
    }
    
    safe_delete(last);
    return true;
}

NNT_END_NS
NNT_END_CXX
