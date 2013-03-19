
# ifndef __NNT_WTL_INTERFACE_adc3f4892d634a3590dd3f1a964eca24_H_INCLUDED
# define __NNT_WTL_INTERFACE_adc3f4892d634a3590dd3f1a964eca24_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

template <typename T>
class IArray
    : public IObject
{
public:

    virtual void add(T const&) = 0;
    virtual T& at(uint) const = 0;
    virtual usize size() const = 0;
    virtual void clear() = 0;

};

template <typename T, typename ArrT,
typename iT = IArray<T> >
class Arraylize
    : public iT
{
public:

    virtual void add(T const& obj)
    {
        _arr.push_back(obj);
    }

    virtual T& at(uint idx) const
    {
        return (T&)_arr.at(idx);
    }

    virtual usize size() const
    {
        return _arr.size();
    }

    virtual void clear()
    {
        _arr.clear();
    }

protected:

    ArrT _arr;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
