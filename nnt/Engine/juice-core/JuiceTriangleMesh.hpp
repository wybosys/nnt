
# ifndef __JUICE_TRIANGLEMESH_AC1CA5A03F6B44A7AD43FEFD0DBC10B4_H_INCLUDED
# define __JUICE_TRIANGLEMESH_AC1CA5A03F6B44A7AD43FEFD0DBC10B4_H_INCLUDED

JUICE_BEGIN

template <typename implT, typename typesT>
class TriangleMesh
: public Mesh<implT, typesT>
{
    typedef Mesh<implT, typesT> super;
    
public:
    
    typedef typename super::vertex_type vertex_type;
    typedef typename super::color_type color_type;
    typedef Triangle3d<vertex_type> triangle_type;
    
    void add_triangle(vertex_type const& v0, vertex_type const& v1, vertex_type const& v2)
    {
        typename vertex_type::index_type cur = this->vertices.size();
        this->vertices.push_back(v0);
        this->vertices.push_back(v1);
        this->vertices.push_back(v2);      
        this->indexies.push_back(cur++);
        this->indexies.push_back(cur++);
        this->indexies.push_back(cur++);
    }
    
    void add_triangle(vertex_type const& v0, color_type const& c0, 
                      vertex_type const& v1, color_type const& c1,
                      vertex_type const& v2, color_type const& c2)
    {
        typename vertex_type::index_type cur = this->vertices.size();
        this->vertices.push_back(v0);
        this->vertices.push_back(v1);
        this->vertices.push_back(v2);      
        this->colors.push_back(c0);
        this->colors.push_back(c1);
        this->colors.push_back(c2);
        this->indexies.push_back(cur++);
        this->indexies.push_back(cur++);
        this->indexies.push_back(cur++);
    }
    
    void add_triangle(triangle_type const& triangle)
    {
        this->add_triangle(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
    }
    
};

template <typename implT, typename typesT>
class TriangleMeshRender
: public RenderEntity<implT, typesT>
{
public:    
    typedef RenderEntity<implT, typesT> render_type;    
        
    template <typename driverT, typename meshT>
    void render(driverT* drv, meshT* mesh, renderinfo* info)
    {        
        typedef meshT mesh_type;
        typedef typename mesh_type::vertex_type vertex_type;
        typedef typename mesh_type::color_type color_type;
        
        usize const cnt_indexies = mesh->indexies.size();
        if (cnt_indexies == 0)
            return;                
        
        usize const cnt_vertices = mesh->vertices.size();
        usize const cnt_colors = mesh->colors.size();
        usize const cnt_normals = mesh->normals.size();
        
        // set color.
        drv->set_material(&mesh->material);
        
        // add vertex.
        drv->add_vertices((typename vertex_type::value_type const*)::wsi::core::pointer(mesh->vertices),
                          cnt_vertices);
        
        // add normal.
        if (cnt_normals)
        {
            drv->add_normals((typename vertex_type::value_type const*)::wsi::core::pointer(mesh->normals),
                             cnt_normals);
        }
        
        // add color.
        if (cnt_colors)
        {
            drv->add_colors((typename color_type::value_type const*)::wsi::core::pointer(mesh->colors),
                            cnt_colors);
        }
        
        // add index.
        drv->add_indexies(::wsi::core::pointer(mesh->indexies), 
                          cnt_indexies);
        
        // draw triangle.
        drv->draw_triangles();
        
        // purge for next render.
        drv->purge_elements();
    }
    
};

JUICE_END

# endif