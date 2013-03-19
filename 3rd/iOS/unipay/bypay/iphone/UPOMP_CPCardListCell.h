//
//  CPCardListCell.h
//  UPOMP
//
//  Created by pei xunjun on 11-9-29.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMPCell.h"

@interface UPOMP_CPCardListCell : UPOMP_CPCell <UITextFieldDelegate,UIPickerViewDelegate,UIPickerViewDataSource>{
	UIButton *button;
	UIPickerView *pickerView;
	UITextField *field;
	NSMutableArray *cardsList;
	int selecetIndex;
}

@end
