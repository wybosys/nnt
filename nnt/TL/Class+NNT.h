
# ifndef __NNT_TL_CLASS_9ddeac7c15224d098cf76f389fd06dd9_H_INCLUDED
# define __NNT_TL_CLASS_9ddeac7c15224d098cf76f389fd06dd9_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)
NNT_BEGIN_NS(pmp)

// polymorphisms
// pseudo-code
// class A
// { public:
//   A();
//   void run(int);
//
//   pmp_begin
//   pmp_function(void, run, (int))
//   pmp_end
// }
//
// class B : public A
// { public:
//   B();
//   void run(int);
//
//   pmp_begin
//   pmp_end
//  }
//  A()
//  {
//   pmp_impl(run);
//  }
//  B()
//  {
//   pmp_impl(run);
//  }
//
//  A* obj = new B;
//  pmp_call(obj, run(0)); // will run B::run(0)
//

template <typename L, typename R>
void _pmp_set(L& l, R r)
{
    l = (L&)r;
}

# define pmp_begin(cls) \
    typedef cls _pmp_class_type;

# define pmp_end

# define pmp_function(ret, name, pmt) \
    typedef ret (_pmp_class_type::*_pmp_func_##name##_type)pmt; \
    _pmp_func_##name##_type _pmp_func_##name;

# define pmp_call(obj, name, pmt) \
    (obj->*(obj->_pmp_func_##name))pmt;

# define pmp_impl(name) \
    ::nnt::ntl::pmp::_pmp_set(this->_pmp_func_##name, &_pmp_class_type::name);

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif
