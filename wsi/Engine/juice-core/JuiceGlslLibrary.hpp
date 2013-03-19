
# ifndef __JUICE_GLSL_LIBRARY_C0117320F9A24A24B7D6956390D2BC02_H_INCLUDED
# define __JUICE_GLSL_LIBRARY_C0117320F9A24A24B7D6956390D2BC02_H_INCLUDED

# ifdef WSI_GCC
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunused-variable"
# endif

JUICE_BEGIN WSI_BEGIN_NS(glsl)

typedef ::wsi::core::string GLSL_TYPE;

# define GLSL_CODE(name) \
static GLSL_TYPE name =
# define GLSL_CODE_END "}";

# define glsl_source_position "PosSrc"
# define glsl_dest_position "PosDes"
# define glsl_source_color "ColorSrc"
# define glsl_dest_color "ColorDes"
# define glsl_projection_matrix "MatProj"
# define glsl_modelview_matrix "MatModelView"
# define glsl_equal " = "
# define glsl_multiply " * "
# define glsl_end ";"
# define glsl_attribute "attribute"
# define glsl_vec4 " vec4 "
# define glsl_mat4 " mat4 "
# define glsl_uniform "uniform"
# define glsl_varying "varying"
# define glsl_lowp " lowp "

# define GLSL_POSITION "gl_Position"
# define GLSL_FRAGMENTCOLOR "gl_FragColor"
# define GLSL_MAIN "void main(void) {"

GLSL_CODE(direct_vextex)
glsl_attribute glsl_vec4 glsl_source_position glsl_end
glsl_attribute glsl_vec4 glsl_source_color glsl_end
glsl_varying glsl_vec4 glsl_dest_color glsl_end
glsl_uniform glsl_mat4 glsl_projection_matrix glsl_end
glsl_uniform glsl_mat4 glsl_modelview_matrix glsl_end
GLSL_MAIN
glsl_dest_color glsl_equal glsl_source_color glsl_end
GLSL_POSITION glsl_equal glsl_projection_matrix glsl_multiply glsl_modelview_matrix glsl_multiply glsl_source_position glsl_end
GLSL_CODE_END;

GLSL_CODE(direct_fragment)
glsl_varying glsl_lowp glsl_vec4 glsl_dest_color glsl_end
GLSL_MAIN
GLSL_FRAGMENTCOLOR glsl_equal glsl_dest_color glsl_end
GLSL_CODE_END

# ifdef OPENGLES_2

# endif

# ifdef OPENGLES_1

# endif

WSI_END_NS JUICE_END

# pragma GCC diagnostic pop

# endif