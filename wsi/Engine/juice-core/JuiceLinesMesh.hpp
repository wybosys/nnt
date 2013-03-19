
# ifndef __JUICE_LINES_MESH_9FBAE59ABA5A4344AAE5F91035826285_H_INCLUDED
# define __JUICE_LINES_MESH_9FBAE59ABA5A4344AAE5F91035826285_H_INCLUDED

JUICE_BEGIN

template <typename implT, typename typesT>
class LinesMesh
: public Mesh<implT, typesT>
{
    
};

template <typename meshT, typename typesT>
class LinesMeshReadonly
: public MeshReadonly<meshT, typesT>
{
    
};

template <typename implT, typename typesT>
class LinesMeshRender
: public RenderEntity<implT, typesT>
{
 
public:    
    
    template <typename driverT, typename meshT>
    void render(driverT* drv, meshT* mesh, renderinfo*)
    {
        typedef RenderEntity<implT, typesT> render_type;
        typedef meshT mesh_type;
        typedef typename mesh_type::vertex_type vertex_type;
        typedef typename mesh_type::color_type color_type;
        
        usize const cnt_indexies = ::wsi::core::length(mesh->indexies);
        if (cnt_indexies == 0)
            return;        
        
        usize const cnt_vertices = mesh->vertices.size();
        usize const cnt_colors = mesh->colors.size();
                
        drv->set_material(&mesh->material);
        
        drv->add_vertices((typename vertex_type::value_type const*)::wsi::core::pointer(mesh->vertices),
                          cnt_vertices);            
        
        drv->add_indexies(::wsi::core::pointer(mesh->indexies), 
                          cnt_indexies);   
        
        if (cnt_colors)
        {
            drv->add_colors((typename color_type::value_type const*)::wsi::core::pointer(mesh->colors),
                            cnt_colors);
        }
        
        drv->draw_looplines();
        drv->purge_elements();

    }
    
};

template <typename implT, typename typesT>
class FrameLinesMeshRender
: public RenderEntity<implT, typesT>
{    
public:    
    
    typedef typename typesT::material_type material_type;
    
    material_type material;
    
    FrameLinesMeshRender()
    {
        material.lightable = false;
    }
    
    template <typename driverT, typename meshT>
    void render(driverT* drv, meshT* mesh, renderinfo*)
    {
        typedef RenderEntity<implT, typesT> render_type;
        typedef meshT mesh_type;
        typedef typename mesh_type::vertex_type vertex_type;
        typedef typename mesh_type::color_type color_type;
        
        usize const cnt_indexies = ::wsi::core::length(mesh->indexies);
        if (cnt_indexies == 0)
            return;        
        
        usize const cnt_vertices = mesh->vertices.size();
        usize const cnt_colors = mesh->colors.size();
        
        drv->set_material(&material);
        
        drv->add_vertices((typename vertex_type::value_type const*)::wsi::core::pointer(mesh->vertices),
                          cnt_vertices);            
        
        drv->add_indexies(::wsi::core::pointer(mesh->indexies), 
                          cnt_indexies);   
        
        if (cnt_colors)
        {
            drv->add_colors((typename color_type::value_type const*)::wsi::core::pointer(mesh->colors),
                            cnt_colors);
        }
        
        drv->draw_looplines();
        drv->purge_elements();
        
    }
    
};

JUICE_END

# endif