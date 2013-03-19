
# ifndef __JUICE_CAMERA_5126199469094C5AABCBF68BFFC07B75_H_INCLUDED
# define __JUICE_CAMERA_5126199469094C5AABCBF68BFFC07B75_H_INCLUDED

JUICE_BEGIN

static const real CAMERA_INFINITE = 9999;

template <typename implT, typename typesT>
class Camera
: public RefObject<implT>
{
public:
    
    typedef typename typesT::vertex_type vertex_type;
    typedef typename typesT::viewport_type viewport_type;
    typedef typename typesT::matrix_type matrix_type;   
    typedef Line<vertex_type> line_type;
    
public:
    
    Camera()
    {
        _mat.set_identity();
    }
    
    void set_viewport(viewport_type const& vp)
    {
        _viewport = vp;
        jimpl->_update();
    }
    
    viewport_type const& viewport() const
    {
        return _viewport;
    }
    
    void set_position(vertex_type const& pt)
    {
        _position = pt;
        jimpl->_update();
    }
    
    vertex_type const& position() const
    {
        return _position;
    }
    
    void set_target(vertex_type const& pt)
    {
        _target = pt;
        jimpl->_update();
    }
    
    vertex_type const& target() const
    {
        return _target;
    }
    
    template <typename unnT>
    void see(unnT* unn, typename unnT::empty_type* typ = NULL)
    {
        jimpl->_see(unn, typ);
    }
    
    template <typename pointT>
    pointT location_in(pointT const& _pt)
    {
        pointT pt;
        pt.x = _pt.x;
        pt.y = _viewport.size.h - _pt.y;
        
        typename viewport_type::vertex_type center = _viewport.center();
        pt.x -= center.x;
        pt.y -= center.y;
        
        pt.x -= _position.x;
        pt.y -= _position.y;
        
        return pt;
    }
    
    //! make a line from near to far.
    template <typename pointT>
    line_type nfline(pointT const& _pt);
    
protected:
    
    //! update matrix or other.
    void _update();
    
    template <typename meshT>
    void _see(meshT* mesh, empty_mesh_type* = NULL)
    {
        PASS;
    }
    
    template <typename drvT>
    void _see(drvT* drv, empty_driver_type* = NULL)
    {
        // set viewport to driver.
        drv->set_viewport(_viewport);        
        
        // set camera.
        drv->mult_matrix(this->_transform());
    }
    
    template <typename treeT>
    void _see(treeT* tree, empty_tree_type* = NULL)
    {
        PASS;
    }
    
    template <typename entityT>
    void _see(entityT* entity, empty_renderentity_type* = NULL)
    {
        PASS;
    }
    
    matrix_type _transform() const
    {
        matrix_type ret;
        ret.set_translate(this->_position);
        ret *= this->_mat;
        return ret;
    }
    
protected:
    
    vertex_type _position, _target;
    viewport_type _viewport;
    matrix_type _mat;
    
};

template <typename implT, typename typesT>
class CameraFlat
: public Camera<implT, typesT>
{
    JUICE_SUPER(Camera<implT MCOMMA typesT>);
    
public:  
    
    enum { ORTHO = true }; 
    
    typedef typename super::vertex_type vertex_type;
    typedef typename super::viewport_type viewport_type;
    typedef typename super::line_type line_type;
    typedef typename super::matrix_type matrix_type;
    
    CameraFlat()
    {
        this->_position = vertex_type(0, 0, CAMERA_INFINITE);
        this->_target = vertex_type(0, 0, -CAMERA_INFINITE);
    }    
    
public:
    
    template <typename pointT>
    line_type nfline(pointT const& _pt)
    {
        line_type line;
        line.start.x = line.end.x = _pt.x;
        line.start.y = line.end.y = _pt.y;
        line.start.z = this->_position.z;
        line.end.z = this->_target.z;
        return line;
    }
        
protected:
    
    void _update()
    {   
        real w_2 = this->_viewport.size.w * .5f;
        real h_2 = this->_viewport.size.h * .5f;
        real r = this->_viewport.origin.x + w_2 + this->_position.x;
        real l = this->_viewport.origin.x - w_2 + this->_position.x;
        real t = this->_viewport.origin.y + h_2 + this->_position.y;
        real b = this->_viewport.origin.y - h_2 + this->_position.y;
        real n = this->_position.z;
        real f = this->_target.z;
        
        Orthogonal<matrix_type> ortho(n, f, l, r, t, b);        
        this->_mat = ortho.mat;
    }
    
};

template <typename implT, typename typesT>
class CameraEye
: public CameraFlat<implT, typesT>
{
    JUICE_SUPER(CameraFlat<implT MCOMMA typesT>);
    JUICE_FRIEND(Camera<implT MCOMMA typesT>);
    
public:
    
    enum { ORTHO = false }; 
    
    typedef typename super::vertex_type vertex_type;
    typedef typename super::viewport_type viewport_type;   
    typedef typename super::line_type line_type;
    typedef typename super::matrix_type matrix_type;
    
    CameraEye()
    {
        this->_position = vertex_type(0, 0, 0);
        this->_target = vertex_type(0, 0, 0);
        this->_angle = M_PI_2;
    }      
    
public:
    
    template <typename pointT>
    line_type nfline(pointT const& _pt)
    {
        line_type line;
        line.start.x = line.end.x = _pt.x;
        line.start.y = line.end.y = _pt.y;
        line.start.z = this->_position.z;
        line.end.z = this->_target.z;
        return line;
    }
    
protected:
    
    real _angle;
    
    void _update()
    {   
        this->_mat.set_identity();
        
        real w_2 = this->_viewport.size.w * .5f;
        real h_2 = this->_viewport.size.h * .5f;
        real r = this->_viewport.origin.x + w_2;
        real l = this->_viewport.origin.x - w_2;
        real t = this->_viewport.origin.y + h_2;
        real b = this->_viewport.origin.y - h_2;    
        
        if (this->_angle == 0)
            return;
        
        real ag_2 = this->_angle * .5f;
        real n = h_2 * atan(ag_2);
        real f = this->_position.z - this->_target.z;
        
        Frustum<matrix_type> frustum(this->_angle, n, f, l, r, t, b);
        this->_mat = frustum.mat;
    }
    
};

JUICE_END

# endif