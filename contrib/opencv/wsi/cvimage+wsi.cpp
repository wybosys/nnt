
# include "Core.h"
# include "opencv/cv.h"
# include "opencv/highgui.h"
# include "cvimage+wsi.h"
# include "../modules/highgui/grfmt_base.hpp"

//WSI_BEGIN_CXX

using namespace cv;

extern vector<ImageDecoder> decoders;
extern vector<ImageEncoder> encoders;
 
ImageDecoder findDecoderByData(byte const* __data, usize __len)
{
    size_t i, maxlen = 0;
    for( i = 0; i < decoders.size(); i++ )
    {
        size_t len = decoders[i]->signatureLength();
        maxlen = std::max(maxlen, len);
    }
    
    string signature(maxlen, ' ');
    memcpy(&signature[0], __data, maxlen);
    signature = signature.substr(0, maxlen);
    
    for( i = 0; i < decoders.size(); i++ )
    {
        if( decoders[i]->checkSignature(signature) )
            return decoders[i]->newDecoder();
    }
    
    return ImageDecoder();
}

/*
IplImage* cvLoadImageFromData(byte const* __data, usize __len)
{        
    return NULL;
}
 */

//WSI_END_CXX
