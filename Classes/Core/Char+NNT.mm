
# import "Core.h"
# import "Char+NNT.h"

NNT_BEGIN_OBJC

NSString* chinese2pinyin(unichar ch) {
    NSString* str = @"";
    if (ch < 0xA1) {
        str = [NSString stringWithCharacters:&ch length:1];
    } else {
        
        short_b8* b8 = (short_b8*)&ch;
        int charasc = (byte)b8->_0 * 256 + (byte)b8->_1 - 65536;
        if (charasc > 0 && charasc < 0xA1) {
            str = [NSString stringWithCharacters:&ch length:1];
        } else if (charasc < -20319 || charasc > -10247) {
            PASS;
        } else {
            for (int i = CH2PY_TABLE_SIZE - 1; i >= 0; --i) {
                if (gs_pinyin_code[i] <= charasc) {
                    str = [NSString stringWithCString:gs_pinyin_string[i] encoding:NSASCIIStringEncoding];
                    break;
                }
            }
        }
    }
    
    return str;
}

NSArray* chinese2pinyin_stream(void const* __buf, size_t len) {
    NSMutableArray* ret = [[NSMutableArray alloc] initWithCapacity:len];
    byte const* buf = (byte const*)__buf;
    NSString *lstchn = nil, *lsten = nil;
    for (uindex idx = 0; idx < len; ++idx, ++buf) {
        byte one = *buf;
        if (one < 0xA1) {
            if (lstchn) {
                [ret addObject:lstchn];
                lstchn = nil;
            }
            
            NSString* tmp = chinese2pinyin(one);
            if (tmp == nil)
                tmp = @"";
            
            if (lsten == nil)
                lsten = tmp;
            else 
                lsten = [lsten stringByAppendingString:tmp];
        } else {
            if (lsten) {
                [ret addObject:lsten];
                lsten = nil;
            }
            unichar one = *(unichar const*)buf;
            NSString* tmp = chinese2pinyin(one);
            if (tmp == nil)
                tmp = @"";

            if (lstchn == nil)
                lstchn = tmp;
            else 
                lstchn = [lstchn stringByAppendingString:tmp];
            
            ++buf;
            ++idx;
        }
    }
    if (lsten) {
        [ret addObject:lsten];
    }
    if (lstchn) {
        [ret addObject:lstchn];
    }
    return [ret autorelease];
}

NNT_END_OBJC