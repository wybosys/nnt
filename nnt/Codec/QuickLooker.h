
# ifndef __WSI_QUICKLOOKER_A09E72C5AAD54471AA161D43CF0B5CCD_H_INCLUDED
# define __WSI_QUICKLOOKER_A09E72C5AAD54471AA161D43CF0B5CCD_H_INCLUDED

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(QuickLookerController);

@interface QuickLookerController : WSIUIViewController {
    
    NSArray* _documents;
    
    WSIDECL_PRIVATE(QuickLookerController);
}

@property (nonatomic, retain) NSArray* documents;
@property NSInteger currentPreviewItemIndex;

- (void)reloadData;

@end

# ifdef WSI_CXX

_CXXCONTROLLER_DECL(QuickLookerController);

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(sys)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
