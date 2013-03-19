
# import "Core.h"
# import "UISettingsItems.h"
# import "UISettingsReader.h"
# import "UILabel+NNT.h"

NNT_BEGIN_OBJC

# define UISettingsDefaultRect CGRectMake(0, 0, 100, 0)
# define UISettingsDefaultTextRect CGRectMake(0, 0, 0, 30)

@implementation UISettingsSwitch

@synthesize key = _key;

- (void)dealloc {
    zero_release(_key);
    [super dealloc];
}

@end

@implementation UISettingsSlider

@synthesize key = _key;

- (void)dealloc {
    zero_release(_key);
    [super dealloc];
}

@end

@implementation UISettingsTextField

@synthesize key = _key;

- (void)dealloc {
    zero_release(_key);
    [super dealloc];
}

@end

@implementation UIToggleTableCell

@synthesize label=_label, toggle=_toggle;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {    
    [super setSelected:selected animated:animated];    
    // Configure the view for the selected state
}

- (void)dealloc {
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalValueChanged)
NNTEVENT_END

- (void)layoutSubviews {
    [super layoutSubviews];
    
    CGRect rc = self.bounds;
    
	CGSize labelSize = [_label sizeThatFits:rc.size];
	labelSize.width = MAX(labelSize.width, _label.bounds.size.width);
    CGPoint labelOrigin = rc.origin;
    labelOrigin.y = (rc.size.height - labelSize.height) * .5f;
    labelOrigin.x = labelOrigin.y;
    
    CGRect labelFrame = _label.frame;
    labelFrame.origin = labelOrigin;
    labelFrame.size = labelSize;
    _label.frame = labelFrame;
        
	CGRect toggleFrame = _toggle.frame;
    toggleFrame.origin.x = _toggle.superview.frame.size.width - toggleFrame.size.width - kIASKSpacing;
    toggleFrame.origin.y = (rc.size.height - toggleFrame.size.height) * .5f;
        
	_toggle.frame = toggleFrame;
}

+ (id)cell {
    UIToggleTableCell *cell = [[UIToggleTableCell alloc] init];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    NNTUILabel *lbl = [[NNTUILabel alloc] initWithFrame:UISettingsDefaultRect];
    cell.label = lbl;
    lbl.font = [UIFont boldSystemFontOfSize:16];
    [cell.contentView addSubview:lbl];
    [lbl release];
    
    UISettingsSwitch *swh = [[UISettingsSwitch alloc] init];
    cell.toggle = swh;
    [cell.contentView addSubview:swh];
    [swh release];
    
    [swh connect:kSignalValueChanged sig:kSignalValueChanged obj:cell];
    
    return [cell autorelease];
}

@end

@implementation UITitleValueTableCell

@dynamic title, value;

- (UILabel*)title {
    return self.textLabel;
}

- (UILabel*)value {
    return self.detailTextLabel;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
	// left align the value if the title is empty
	if (!self.textLabel.text.length) {
		self.textLabel.text = self.detailTextLabel.text;
		self.detailTextLabel.text = nil;
		if ([self.reuseIdentifier isEqualToString:kIASKPSMultiValueSpecifier]) {
			self.textLabel.font = [UIFont systemFontOfSize:[UIFont labelFontSize]];
			self.textLabel.textColor = self.detailTextLabel.textColor;
		}
	}    	
	
	CGSize viewSize =  [self.textLabel superview].frame.size;
	
	// set the left title label frame
	CGFloat labelWidth = [self.textLabel sizeThatFits:CGSizeZero].width;
	CGFloat minValueWidth = (self.detailTextLabel.text.length) ? kIASKMinValueWidth + kIASKSpacing : 0;
	labelWidth = MIN(labelWidth, viewSize.width - minValueWidth - kIASKPaddingLeft -kIASKPaddingRight);
	CGRect labelFrame = CGRectMake(kIASKPaddingLeft, 0, labelWidth, viewSize.height -2);
	self.textLabel.frame = labelFrame;
	
	// set the right value label frame
	if (self.detailTextLabel.text.length) {
		CGRect valueFrame = CGRectMake(kIASKPaddingLeft + labelWidth + kIASKSpacing,
									   0,
									   viewSize.width - (kIASKPaddingLeft + labelWidth + kIASKSpacing) - kIASKPaddingRight,
									   viewSize.height -2);
		self.detailTextLabel.frame = valueFrame;
	}
}

+ (id)cell {
    UITitleValueTableCell *cell = [[UITitleValueTableCell alloc] init];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    return [cell autorelease];
}

@end

@implementation UITextFieldTableCell

@synthesize label=_label,
textField=_textField;

- (void)layoutSubviews {
    [super layoutSubviews];
    CGRect rc = self.bounds;
    
	CGSize labelSize = [_label sizeThatFits:CGSizeZero];
	labelSize.width = MIN(labelSize.width, _label.bounds.size.width);
    CGPoint labelOrigin = rc.origin;
    labelOrigin.y = (rc.size.height - labelSize.height) * .5f;
    labelOrigin.x = labelOrigin.y;
    
    CGRect labelFrame = _label.frame;
    labelFrame.origin = labelOrigin;
    labelFrame.size = labelSize;
    _label.frame = labelFrame;
    
	CGRect textFieldFrame = _textField.frame;
	textFieldFrame.origin.x = _label.frame.origin.x + MAX(kIASKMinLabelWidth, labelSize.width) + kIASKSpacing;
    textFieldFrame.origin.y = _label.frame.origin.y;
	if (!_label.text.length)
		textFieldFrame.origin.x = _label.frame.origin.x;
	textFieldFrame.size.width = _textField.superview.frame.size.width - textFieldFrame.origin.x - _label.frame.origin.x;
	_textField.frame = textFieldFrame;    
    //_textField.textAlignment = UITextAlignmentRight;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {    
    [super setSelected:selected animated:animated];    
    // Configure the view for the selected state
}

- (void)dealloc {
    [super dealloc];
}

+ (id)cell {
    UITextFieldTableCell *cell = [[UITextFieldTableCell alloc] init];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    NNTUILabel *lbl = [[NNTUILabel alloc] initWithFrame:UISettingsDefaultRect];
    cell.label = lbl;
    [cell.contentView addSubview:lbl]; 
    [lbl release];
    UISettingsTextField *txf = [[UISettingsTextField alloc] initWithFrame:UISettingsDefaultTextRect];
    cell.textField = txf;    
    txf.textAlignment = UITextAlignmentRight;
    [cell.contentView addSubview:txf];
    [txf release];
    return [cell autorelease];
}

@end

@implementation UISliderTableCell

@synthesize slider=_slider, 
minImage=_minImage, 
maxImage=_maxImage;

- (void)layoutSubviews {
    [super layoutSubviews];
	CGRect  sliderBounds    = _slider.bounds;
    CGPoint sliderCenter    = _slider.center;
    const double superViewWidth = _slider.superview.frame.size.width;
    
    sliderCenter.x = superViewWidth / 2;
    sliderBounds.size.width = superViewWidth - kIASKSliderNoImagesPadding * 2;
	_minImage.hidden = YES;
	_maxImage.hidden = YES;
    
	// Check if there are min and max images. If so, change the layout accordingly.
	if (_minImage.image && _maxImage.image) {
		// Both images
		_minImage.hidden = NO;
		_maxImage.hidden = NO;
        sliderBounds.size.width  = superViewWidth - kIASKSliderImagesPadding * 2;
	}
	else if (_minImage.image) {
		// Min image
		_minImage.hidden = NO;
		sliderCenter.x    += (kIASKSliderImagesPadding - kIASKSliderNoImagesPadding) / 2;
		sliderBounds.size.width  = superViewWidth - kIASKSliderNoImagesPadding - kIASKSliderImagesPadding;
	}
	else if (_maxImage.image) {
		// Max image
		_maxImage.hidden = NO;
		sliderCenter.x    -= (kIASKSliderImagesPadding - kIASKSliderNoImagesPadding) / 2;
		sliderBounds.size.width  = superViewWidth - kIASKSliderNoImagesPadding - kIASKSliderImagesPadding;
	}
	
	_slider.bounds = sliderBounds;
    _slider.center = sliderCenter;
}	

- (void)dealloc {
	_minImage.image = nil;
	_maxImage.image = nil;
    [super dealloc];
}

- (void)prepareForReuse {
	_minImage.image = nil;
	_maxImage.image = nil;
}

@end

NNT_END_OBJC