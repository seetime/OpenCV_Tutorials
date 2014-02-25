void bhCalcHist(const IplImage* srcImage,CvMat* hist,const IplImage* maskImage)
{
    float* pHist = hist->data.fl;
    for (int i=0; i < 256;i++)
        pHist[i] = 0;

    if (maskImage)
    {
        for (int i=0; i < srcImage->height;i++)
        {
            byte* maskP = (byte*) maskImage->imageData + maskImage->widthStep * i;
            byte* srcP = (byte*) srcImage->imageData + srcImage->widthStep * i;
            for (int j=0; j < srcImage->width;j++)
                if (maskP[j] != 0)
            {
                pHist[srcP[j]]++;
            }

        }
    }
    else 
    {
        for (int i=0; i < srcImage->height;i++)
        {
            byte* srcP = (byte*) srcImage->imageData + srcImage->widthStep * i;
            for (int j=0; j < srcImage->width;j++)
            {
                pHist[srcP[j]]++;
            }

        }
    }
}

CvMat* bhGetHist(const IplImage* srcImage,const IplImage* maskImage)
{
    CvMat* resultHist = cvCreateMat(1,256,CV_32FC1);
    bhCalcHist(srcImage,resultHist,maskImage);
    return resultHist;
}

void  bhGetDynamicRange2(const IplImage* srcImage,const IplImage* maskImage, float lowPercent,float highPercent,unsigned char& minRange,unsigned char& maxRange )
{
    CvMat* hist = bhGetHist(srcImage,maskImage);

    float* pHist = hist->data.fl;
    int totalCount;
    if (maskImage != 0 )
        totalCount = cvCountNonZero(maskImage);
    else totalCount = srcImage->width * srcImage->height;

    int lowPercentCount = cvRound( totalCount * lowPercent /100);
    int highPercentCount = cvRound( totalCount * highPercent /100);


    int minRng = 0;
    float curCount = 0;
    int size = 256;


    while ((minRng < size) && (curCount < lowPercentCount))
    {
        curCount += (pHist[minRng]<0)?0:pHist[minRng];
        minRng++;
    }

    int maxRng = size-1;

    curCount = 0;
    while ((maxRng >= 0) && (curCount < highPercentCount))
    {
        curCount += (pHist[maxRng]<0)?0:pHist[maxRng];
        maxRng--;
    }
    if (minRng > maxRng)
    {
        minRng = maxRng;
    }


    minRange = minRng;
    maxRange = maxRng;



    cvReleaseMat(&hist);


}

int main ()
{
    unsigned char minRng ;
    unsigned char maxRng ;

    bhGetDynamicRange2(srcImage,tempMask,0.05,0.05,minRng,maxRng);

    return 0;
}
