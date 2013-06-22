
# ifndef __JUICE_COLLISION_5F1C549653C0447398DBAA88C96B1360_H_INCLUDED
# define __JUICE_COLLISION_5F1C549653C0447398DBAA88C96B1360_H_INCLUDED

JUICE_BEGIN

template <typename lineT, typename boundingT>
bool bounding_collision(lineT const& line, boundingT const& bounding)
{
    bool bofs[6], bofe[6];
    
    typedef boundingT bounding_type;
    
    bofs[0] = line.start.x < bounding.pts[bounding_type::FRONT_LEFT_TOP].x;
    bofs[1] = line.start.x > bounding.pts[bounding_type::FRONT_RIGHT_TOP].x;
    bofs[2] = line.start.y < bounding.pts[bounding_type::FRONT_LEFT_BOTTOM].y;
    bofs[3] = line.start.y > bounding.pts[bounding_type::FRONT_LEFT_TOP].y;
    bofs[4] = line.start.z > bounding.pts[bounding_type::FRONT_LEFT_TOP].z;
    bofs[5] = line.start.z < bounding.pts[bounding_type::BACK_LEFT_TOP].z;
    
    bofe[0] = line.end.x < bounding.pts[bounding_type::FRONT_LEFT_TOP].x;
    bofe[1] = line.end.x > bounding.pts[bounding_type::FRONT_RIGHT_TOP].x;
    bofe[2] = line.end.y < bounding.pts[bounding_type::FRONT_LEFT_BOTTOM].y;
    bofe[3] = line.end.y > bounding.pts[bounding_type::FRONT_LEFT_TOP].y;
    bofe[4] = line.end.z > bounding.pts[bounding_type::FRONT_LEFT_TOP].z;
    bofe[5] = line.end.z < bounding.pts[bounding_type::BACK_LEFT_TOP].z;
    
    bool sta = false;
    for (uint i = 0; i < sizeof(bofs); ++i)
        sta |= bofs[i] & bofe[i];
    
    return sta == false;
};

JUICE_END

# endif