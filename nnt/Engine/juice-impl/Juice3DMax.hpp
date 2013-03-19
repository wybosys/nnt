
# ifndef __JUICEIMPL_3DMAX_0F77305C6A2F4BDAB43B966DBB36C85F_H_INCLUDED
# define __JUICEIMPL_3DMAX_0F77305C6A2F4BDAB43B966DBB36C85F_H_INCLUDED

# include <fstream>

JUICEIMPL_BEGIN 

NNT_BEGIN_NS(ad3dmax)

enum {
    MAINCHUNK = 0x4D4D,
    MASHDATA = 0x3D3D,
    OBJNAME = 0x4000,
    MESH_DATA = 0x4100,
    VERTEX_DATA = 0x4110,
    INDEX_DATA = 0x4120,
    TEXMAP_DATA = 0x4140
};

NNT_END_NS

class Archive3dmax
{
public:
    
    Archive3dmax()
    : _fd(NULL)
    {
        PASS;
    }
    
    ~Archive3dmax()
    {
        this->close();
    }
    
    bool open(::nnt::core::string const& file)
    {
        this->close();
        
        _fd.open(file.c_str(), std::ios::in | std::ios::binary);
        return _fd.is_open();
    }
    
    void close()
    {
        if (_fd.is_open())
        {
            _fd.close();
        }
    }
    
    template <typename meshT>
    bool insert(meshT* mesh)
    {      
        // to begin.
        _fd.seekg(std::ios::beg);
        
        // read file.
        while (false == _fd.eof())
        {
            _fd.read((char*)&_chunk_id, sizeof(_chunk_id));
            _fd.read((char*)&_chunk_len, sizeof(_chunk_len));
            
            switch (_chunk_id)
            {
                case ad3dmax::MAINCHUNK: 
                    break;
                case ad3dmax::MASHDATA:
                    break;
                case ad3dmax::OBJNAME:
                    this->_read_name(mesh);
                case ad3dmax::MESH_DATA:
                    break;
                case ad3dmax::VERTEX_DATA:
                    this->_read_vertex(mesh);
                    break;
                case ad3dmax::INDEX_DATA:
                    this->_read_index(mesh);
                    break;
                case ad3dmax::TEXMAP_DATA:
                    break;
                default:
                    this->_read_default();
                    break;
            }
        }
        
        // update.
        mesh->update();
        
        return true;
    }
    
protected:
    
    template <typename meshT>
    bool _read_vertex(meshT* mesh)
    {
        typedef typename meshT::vertex_type vertex_type;
        _vertex_cnt = mesh->vertices.size();
        
        ushort vertex_len = 0;
        _fd.read((char*)&vertex_len, sizeof(vertex_len));
        if (vertex_len)
        {
            mesh->reserve_vertex(vertex_len);
            mesh->reserve_normal(vertex_len);                                  
            
            float x, y, z;
            vertex_type vex;
            for (uindex idx = 0; idx < vertex_len; ++idx)
            {
                _fd.read((char*)&x, sizeof(float));
                _fd.read((char*)&y, sizeof(float));
                _fd.read((char*)&z, sizeof(float));
                
                vex.x = x;
                vex.y = y;
                vex.z = z;
                
                mesh->vertices.push_back(vex);
                mesh->normals.push_back(vex);
            }
        }
        return true;
    }
    
    template <typename meshT>
    bool _read_index(meshT* mesh)
    {
        short index_len = 0;
        _fd.read((char*)&index_len, sizeof(index_len));
        if (index_len <= 0)
            return false;
        
        mesh->reserve_index(index_len);
        
        ushort p1, p2, p3;
        for (uindex idx = 0; idx < (uindex)index_len; ++idx)
        {
            _fd.read((char*)&p1, sizeof(p1));
            _fd.read((char*)&p2, sizeof(p2));
            _fd.read((char*)&p3, sizeof(p3));
            _fd.seekg(sizeof(ushort), std::ios::cur);
            
            uint idx0 = _vertex_cnt + p1;
            uint idx1 = _vertex_cnt + p2;
            uint idx2 = _vertex_cnt + p3;
            
            mesh->indexies.push_back(idx0);
            mesh->indexies.push_back(idx1);
            mesh->indexies.push_back(idx2);
        }
        return true;
    }
    
    template <typename meshT>
    bool _read_name(meshT* mesh)
    {
        ::nnt::core::string name;
        
        int i = 0;
        char c = 0;
        do
        {
            _fd.read(&c, 1);            
            ++i;
            name += c;
        } while ((c != '\0') && (i < 20));
        
        mesh->name = name;
        
        return true;
    }
    
    void _read_default()
    {
        _fd.seekg(_chunk_len - 6, std::ios::cur);
    }
    
protected:
    
    ::std::ifstream _fd;
    short _chunk_id;
    uint _chunk_len;
    uint _vertex_cnt;
    
};

JUICEIMPL_END

# endif