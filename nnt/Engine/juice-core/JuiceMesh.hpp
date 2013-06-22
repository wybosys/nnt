
# ifndef __JUICE_MESH_1D319F257ADB46C8A6533AB91FCA2551_H_INCLUDED
# define __JUICE_MESH_1D319F257ADB46C8A6533AB91FCA2551_H_INCLUDED

JUICE_BEGIN

typedef struct {} empty_mesh_type;

template <typename implT, typename typesT>
class Mesh
{
public:
    typedef empty_mesh_type empty_type;
    
    enum { READONLY = false };
    
    typedef typename typesT::vertex_type vertex_type;
    typedef typename typesT::color_type color_type;
    typedef typename typesT::vertices_type vertices_type;
    typedef typename typesT::colors_type colors_type;
    typedef typename typesT::indexies_type indexies_type;
    typedef typename typesT::material_type material_type;
    typedef typename typesT::bounding_type bounding_type;
    
    void reserve_vertex(usize sz)
    {
        vertices.reserve(vertices.size() + sz);
    }
    
    void reserve_index(usize sz)
    {
        indexies.reserve(indexies.size() + sz);
    }
    
    void reserve_normal(usize sz)
    {
        normals.reserve(normals.size() + sz);
    }
    
    void reserve_color(usize sz)
    {
        colors.reserve(colors.size() + sz);
    }    
    
    void update()
    {
        // regen bounding.
        bounding.reset();
        typename indexies_type::const_iterator each = indexies.begin();
        while (each != indexies.end())
        {
            vertex_type const& vex = vertices.at(*each);
            bounding.add(vex);
            ++each;
        }
    }
    
public:
    
    //! position.
    vertices_type vertices;    
    
    //! indesies.
    indexies_type indexies;
    
    //! normal of face.
    vertices_type normals;
    
    //! color of vertex.
    colors_type colors;

    //! material.
    material_type material;
    
    //! name.
    ::nnt::core::string name;
    
    //! bbx.
    bounding_type bounding;
    
};

template <typename meshT, typename typesT>
class MeshReadonly
{
public:
    
    typedef meshT mesh_type;
    
    enum { READONLY = true };
    
    MeshReadonly(mesh_type const& mesh)
    : _mesh(mesh),
    vertices(_mesh.vertices),
    indexies(_mesh.indexies),
    normals(_mesh.normals),
    colors(_mesh.colors),
    material(_mesh.material)
    {
        PASS;
    }
    
public:
        
    typedef typename mesh_type::vertex_type vertex_type;
    typedef typename mesh_type::vertices_type vertices_type;
    typedef typename typesT::color_type color_type;    
    typedef typename mesh_type::colors_type colors_type;
    typedef typename mesh_type::indexies_type indexies_type;
    typedef typename mesh_type::material_type material_type;
    
    vertices_type const& vertices;    
    indexies_type const& indexies;
    vertices_type const& normals;
    colors_type const& colors;    
    material_type const& material;
    
protected:
    mesh_type const& _mesh;
};

JUICE_END

# endif