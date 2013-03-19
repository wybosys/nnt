
# ifndef __JUICE_D9D8EF13B0D5460A8329B58BBFAC4F45_H_INCLUDED
# define __JUICE_D9D8EF13B0D5460A8329B58BBFAC4F45_H_INCLUDED

# include "juice-core/JuiceCore.hpp"
# include "juice-core/JuiceObject.hpp"
# include "juice-core/JuicePoll.hpp"
# include "juice-core/JuiceAlgo.hpp"
# include "juice-core/JuiceTypes.hpp"
# include "juice-core/JuiceEntity.hpp"
# include "juice-core/JuiceLight.hpp"
# include "juice-core/JuiceTexture.hpp"
# include "juice-core/JuiceMaterial.hpp"
# include "juice-core/JuiceMesh.hpp"
# include "juice-core/JuiceContainer.hpp"
# include "juice-core/JuiceScreenManager.hpp"
# include "juice-core/JuiceDriver.hpp"
# include "juice-core/JuiceTree.hpp"
# include "juice-core/JuiceCamera.hpp"
# include "juice-core/JuiceOpenGLDriver.hpp"
# include "juice-core/JuiceCococaDriver.hpp"
# include "juice-core/JuiceInteractive.hpp"
# include "juice-core/JuiceCLI.hpp"
# include "juice-core/JuicePhysics.hpp"
# include "juice-core/JuiceLinesMesh.hpp"
# include "juice-core/JuiceTriangleMesh.hpp"
# include "juice-core/JuiceSpirit.hpp"
# include "juice-core/JuiceCollision.hpp"

JUICE_BEGIN

typedef struct {
    
    typedef float   value_type;
    typedef ColorRGBA<float>  color_type;
    typedef Vertex3d<float> vertex_type;
    typedef Matrix3d<float> matrix_type;
    typedef BoundingBox<vertex_type> bounding_type;
    
# ifdef OPENGLES
    typedef ubyte index_type;
# else
    typedef uint index_type;
# endif
    
    typedef ::wsi::core::vector<vertex_type> vertices_type;
    typedef ::wsi::core::vector<index_type> indexies_type;
    typedef ::wsi::core::vector<color_type> colors_type;
    typedef ::wsi::core::vector<renderentity_wrapper> entities_type;
    typedef Rect<Vertex2d<value_type>, Size2d<value_type> > viewport_type;
    
} Types3d;

JUICE_END

# endif
