
# include "Core.h"
# include "Openssl+NNT.p.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(openssl)

Bio::Bio()
{
    bio = BIO_new(BIO_s_mem());
}

Bio::Bio(BIO_METHOD* mtd)
{
    bio = BIO_new(mtd);
}

Bio::~Bio()
{
    clear();
}

Bio::Bio(core::data const& da)
: bio(NULL)
{
    set(da);
}

void Bio::clear()
{
    if (bio == NULL)
        return;
    
    BIO_free(bio);
    bio = NULL;
}

Bio& Bio::operator = (core::data const& da)
{
    set(da);
    return *this;
}

void Bio::set(core::data const& da)
{
    clear();
    
    bio = BIO_new(BIO_s_mem());
    BIO_write(bio, da.bytes(), da.length());
}

Bio::operator BIO* () const
{
    return (BIO*)bio;
}

NNT_END_NS
NNT_END_CXX
