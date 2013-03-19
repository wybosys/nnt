
# ifndef __WSI_UIKIT_COVERDRAWER_137199117BEE411C999FE5587B822A37_H_INCLUDED
# define __WSI_UIKIT_COVERDRAWER_137199117BEE411C999FE5587B822A37_H_INCLUDED

# import "UICoverDrawerItem.h"
# import "UIControl+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UICoverDrawer);
WSIDECL_EXTERN_CLASS(UICoverDrawerItem);
WSIDECL_EXTERN_CLASS(WCGLineStyle);
WSIDECL_EXTERN_CLASS(WCGFill);

@protocol UICoverDrawerDataSource <NSObject>
@optional

//! get number of covers.
- (uint)coverdrawerNumberCovers:(UICoverDrawer*)cd;

//! get drawer item for index.
- (UICoverDrawerItem*)coverdrawerCover:(UICoverDrawer*)cd idx:(uint)idx;

@end

@protocol UICoverDrawerDelegate <NSObject>
@optional

//! while add item.
- (void)coverdrawerItemAdded:(UICoverDrawer*)cd item:(UICoverDrawerItem*)item;

//! while drag at begin.
- (void)coverdrawerItemDragBegin:(UICoverDrawer*)cd item:(UICoverDrawerItem*)item touchs:(NSSet*)touchs;

//! while dragging.
- (void)coverdrawerItemDragging:(UICoverDrawer*)cd item:(UICoverDrawerItem*)item touchs:(NSSet*)touchs;

//! while drag at end.
- (void)coverdrawerItemDragEnd:(UICoverDrawer*)cd item:(UICoverDrawerItem*)item touchs:(NSSet*)touchs;

//! while select changed.
- (void)coverdrawerItemSelectedChanged:(UICoverDrawer*)cd cur:(UICoverDrawerItem*)curitem pas:(UICoverDrawerItem*)pasitem; 

@end

WSIDECL_PRIVATE_HEAD(UICoverDrawer);

@interface UICoverDrawer : WSIUIControl {
            
    //! datasource & delegate.
    id <UICoverDrawerDataSource> dataSource;
    id <UICoverDrawerDelegate> delegate;
    BOOL isDataSourceNeedRelease;
    BOOL isDelegateNeedRelease;
    
    //! number of covers.
    uint numberCovers;
    
    //! current cover item.
    UICoverDrawerItem *currentCover;
    
    //! limit show covers on screen.
    uint maxCoversOnScreen;
    uint minCoversOnScreen;
    
    //! geometry.
    real padding_left, padding_right, padding_top, padding_bottom;
    
    //! size for content.
    CGSize contentSize;
    
    //! view deepth
    real viewportDepth;
    
    //! view distance.
    real viewportDistance;
    
    //! view angle.
    real viewportAngle;
    
    //! if ring enable, if covers will not mit end.
    BOOL enableRing;
            
    //! space for items.
    real itemSpacing;
    
    //! default image for item.
    UIImage *itemDefaultImage;
    
    //! if item is draggable, default is YES.
    BOOL itemDraggable;
    
    //! angle for item.
    point3df itemAngle, itemAngleStep, itemPositionStep;
    
    //! scrollable, default is YES.
    BOOL itemsScrollable;
    
    //! zpos step.
    real itemZPosStep;
    
    //! zpos.
    real itemZPosition;
        
    //! dragging item
    UICoverDrawerItem *draggingItem;
    
    //! dragging damp.
    real draggingDamp;
    
    WSIDECL_PRIVATE(UICoverDrawer);
}

@property (nonatomic, assign) id <UICoverDrawerDataSource>    dataSource;
@property (nonatomic, assign) id <UICoverDrawerDelegate>      delegate;
@property (nonatomic)         BOOL                            isDataSourceNeedRelease;
@property (nonatomic)         BOOL                            isDelegateNeedRelease;

@property (nonatomic, assign) UICoverDrawerItem*              currentCover;
@property (nonatomic)         uint                            numberCovers;

@property (nonatomic)         uint                            maxCoversOnScreen;
@property (nonatomic)         uint                            minCoversOnScreen;

@property (nonatomic)         real                            padding_left, padding_right, padding_top, padding_bottom;
@property (nonatomic)         CGSize                          contentSize;

@property (nonatomic)         real                            viewportDepth;
@property (nonatomic)         real                            viewportDistance;
@property (nonatomic)         real                            viewportAngle;

@property (nonatomic, assign) BOOL                            enableRing;

@property (nonatomic)         real                            itemSpacing;
@property (nonatomic, retain) UIImage                        *itemDefaultImage;
@property (nonatomic)         BOOL                            itemDraggable;
@property (nonatomic)         point3df                        itemAngle, itemAngleStep, itemPositionStep;
@property (nonatomic)         real                            itemZPosition, itemZPosStep;

@property (nonatomic)         BOOL                            itemsScrollable;

@property (nonatomic, assign) UICoverDrawerItem              *draggingItem;
@property (nonatomic, assign) real                            draggingDamp;

//! @function insert item
- (UICoverDrawerItem*)insertItem:(UICoverDrawerItem*)item idx:(uint)idx;
- (UICoverDrawerItem*)appendItem:(UICoverDrawerItem*)item;

//! @function count of items
- (uint)count;

//! @function count on screen
- (uint)countOnScreen;

//! @function get item
- (UICoverDrawerItem*)itemAtIndex:(uint)idx;

//! @function clear
- (void)clear;

//! @function item index
- (uint)indexOfItem:(UICoverDrawerItem const*)item;

//! @function content position
- (CGPoint)contentPosition;

//! @function set select
- (void)selectItem:(UICoverDrawerItem*)item animated:(BOOL)animated;

//! @function move
- (void)moveIn:(BOOL)animated;
- (void)moveOut:(BOOL)animated;

//! @function reload data
- (void)reloadData;

//! @function relayout data.
- (void)relayoutData;

//! calc item's rect.
- (CGRect)calcItemRect:(UICoverDrawerItem*)item;

//! calc item's transform.
- (CATransform3D)calcItemTransform:(UICoverDrawerItem*)item;

@end

WSI_END_HEADER_OBJC

# endif