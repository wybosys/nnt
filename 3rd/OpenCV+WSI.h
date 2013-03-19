
# ifndef __WSI_OPENCV_2102983466DA404B8D90F10637049AB5_H_INCLUDED
# define __WSI_OPENCV_2102983466DA404B8D90F10637049AB5_H_INCLUDED

# ifdef MIN
# undef MIN
# endif

# include "opencv/cv.h"
# include "opencv/highgui.h"
# include "cvimage+wsi.h"

# define wcvReleaseImage(img) { if (img) { cvReleaseImage(&img); } }
# define wcvReleaseMemStorage(store) { if (store) { cvReleaseMemStorage(&store); } }
# define wcvReleaseMat(mat) { if (mat) { cvReleaseMat(&mat); } }
# define wcvRelease(ptr) { if (ptr) { cvRelease((void**)&ptr); } }

static bool CvRectIsEqual(CvRect l, CvRect r) {
    return (l.x == r.x && l.y == r.y && l.width == r.width && l.height == r.height);
}

static int cvSeqCmpByClockwise(const void *_a,const void *_b,void *_cog)
{
    CvPoint* a = (CvPoint*)_a;
    CvPoint* b = (CvPoint*)_b;
    CvPoint2D32f *cog=(CvPoint2D32f *)_cog;
    
    float aa=cvFastArctan((float)(a->y)-cog->y,cog->x-(float)(a->x));
    float ba=cvFastArctan((float)(b->y)-cog->y,cog->x-(float)(b->x));
    
    return(aa < ba ? 1 : aa > ba ? -1 : 0);
}

# define cvPointDistanceQ(l, r) ( ((l).x - (r).x) * ((l).x - (r).x) + ((l).y - (r).y) * ((l).y - (r).y) )
# define cvPointDistance(l, r) cvSqrt(cvPointDistanceQ(l, r))

static void apaptive_white_leveling(const CvArr* src,
                             CvArr* dst,
                             double middle_value,
                             int adaptive_method,
                             int threshold_type,
                             int block_size,
                             double param1)
{
    CV_FUNCNAME( "apaptive_white_leveling" );
    CvMat src_stub, dst_stub;
    CvMat *srcMat,*dstMat,*mean,*mask;
    
    __BEGIN__
    if( adaptive_method != CV_ADAPTIVE_THRESH_MEAN_C &&
       adaptive_method != CV_ADAPTIVE_THRESH_GAUSSIAN_C )
        CV_ERROR( CV_StsBadArg,
                 "Only CV_ADAPTIVE_THRESH_MEAN_C and CV_ADAPTIVE_THRESH_GAUSSIAN_C "
                 "adaptive method are acceptable" );
    
    if( threshold_type != CV_THRESH_BINARY &&
       threshold_type != CV_THRESH_BINARY_INV )
        CV_ERROR( CV_StsBadArg, "Only CV_TRESH_BINARY and CV_THRESH_BINARY_INV "
                 "threshold types are acceptable" );
    
    srcMat=cvGetMat(src, &src_stub );
    dstMat=cvGetMat(dst, &dst_stub );
    
    if( !CV_ARE_CNS_EQ( srcMat, dstMat ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );
    
    if( CV_MAT_TYPE(dstMat->type) != CV_8UC1 )
        CV_ERROR( CV_StsUnsupportedFormat, "" );
    
    if( !CV_ARE_SIZES_EQ( srcMat, dstMat ) )
        CV_ERROR( CV_StsUnmatchedSizes, "" );
    
    mean=cvCreateMat(srcMat->rows,srcMat->cols,CV_8UC1);
    mask=cvCreateMat(srcMat->rows,srcMat->cols,CV_8UC1);
    
    cvSmooth( srcMat, mean, adaptive_method == CV_ADAPTIVE_THRESH_MEAN_C ?
             CV_BLUR : CV_GAUSSIAN, block_size, block_size );
    cvSubS(mean,cvRealScalar(param1),mean);
    cvAbsDiff(srcMat,mean,dstMat);
    cvCmp(srcMat,mean,mask,CV_CMP_GT);
    cvAddS(dstMat,cvRealScalar(middle_value),dstMat,mask);
    cvNot(mask,mask);
    cvSubRS(dstMat,cvRealScalar(middle_value),dstMat,mask);
    
    if(threshold_type!=CV_THRESH_BINARY)
        cvNot(dstMat,dstMat);
    
    cvReleaseMat( &mask );
    cvReleaseMat( &mean );
    
    __END__
    
}

# endif