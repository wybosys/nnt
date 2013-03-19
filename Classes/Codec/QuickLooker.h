
# ifndef __NNT_QUICKLOOKER_A09E72C5AAD54471AA161D43CF0B5CCD_H_INCLUDED
# define __NNT_QUICKLOOKER_A09E72C5AAD54471AA161D43CF0B5CCD_H_INCLUDED

# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(QuickLookerController);

@interface QuickLookerController : NNTUIViewController {
    
    NSArray* _documents;
    
    NNTDECL_PRIVATE(QuickLookerController);
}

@property (nonatomic, retain) NSArray* documents;
@property NSInteger currentPreviewItemIndex;

- (void)reloadData;

@end

# ifdef NNT_CXX

_CXXCONTROLLER_DECL(QuickLookerController);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(sys)

class QuickLooker
: public ui::SimpleController<QuickLooker,
_CXXCONTROLLER(QuickLookerController),
UIView>
{
    typedef ui::SimpleController<QuickLooker,
    _CXXCONTROLLER(QuickLookerController),
    UIView> super;
    
public:
    
    QuickLooker()
    {
        PASS;
    }
    
    virtual ~QuickLooker()
    {
        PASS;
    }
    
    template <typename itemsT>
    void set_items(itemsT const& items)
    {
        wtl::const_pointer<itemsT> ptr(items);
        this->_self.documents = *ptr;
    }
    
    void reload()
    {
        [this->_self reloadData];
    }
    
    void set_selection(uint idx)
    {
        this->_self.currentPreviewItemIndex = idx;
    }
    
    uint selection() const
    {
        return this->_self.currentPreviewItemIndex;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
