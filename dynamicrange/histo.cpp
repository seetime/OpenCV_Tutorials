#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

std::string getImageType(int number)
{
    // find type
    int imgTypeInt = number%8;
    std::string imgTypeString;

    switch (imgTypeInt)
    {
        case 0:
            imgTypeString = "8U";
            break;
        case 1:
            imgTypeString = "8S";
            break;
        case 2:
            imgTypeString = "16U";
            break;
        case 3:
            imgTypeString = "16S";
            break;
        case 4:
            imgTypeString = "32S";
            break;
        case 5:
            imgTypeString = "32F";
            break;
        case 6:
            imgTypeString = "64F";
            break;
        default:
            break;
    }

    // find channel
    int channel = (number/8) + 1;

    std::stringstream type;
    type<<"CV_"<<imgTypeString<<"C"<<channel;

    return type.str();
}

void showHistogram(char *title, Mat& img)
{
	char tmpStr[256];
	int bins = 256;             // number of bins
	int nc = img.channels();    // number of channels

	//sprintf(tmpStr, "%s: ", title);
	vector<Mat> hist(nc);       // histogram arrays

	// Initalize histogram arrays
	for (int i = 0; i < hist.size(); i++)
		hist[i] = Mat::zeros(1, bins, CV_32SC1);

	// Calculate the histogram of the image
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			for (int k = 0; k < nc; k++)
			{
				uchar val = nc == 1 ? img.at<uchar>(i,j) : img.at<Vec3b>(i,j)[k];
				hist[k].at<int>(val) += 1;
			}
		}
	}

	// For each histogram arrays, obtain the maximum (peak) value
	// Needed to normalize the display later
	int hmax[3] = {0,0,0};
	for (int i = 0; i < nc; i++)
	{
		for (int j = 0; j < bins-1; j++)
			hmax[i] = hist[i].at<int>(j) > hmax[i] ? hist[i].at<int>(j) : hmax[i];
	}

	const char* wname[3] = { "blue", "green", "red" };
	Scalar colors[3] = { Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255) };

	vector<Mat> canvas(nc);

	// Display each histogram in a canvas
	for (int i = 0; i < nc; i++)
	{
		canvas[i] = Mat::ones(125, bins, CV_8UC3);

		for (int j = 0, rows = canvas[i].rows; j < bins-1; j++)
		{
			line(
				canvas[i], 
				Point(j, rows), 
				Point(j, rows - (hist[i].at<int>(j) * rows/hmax[i])), 
				nc == 1 ? Scalar(200,200,200) : colors[i], 
				1, 8, 0
			);
		}


		sprintf( tmpStr, "%s: %s", title, nc == 1 ? "value" : wname[i]);
		imshow( tmpStr, canvas[i]);
	}
}


int main( int argc, char** argv )
{
    Mat src, dst;
	Mat src_resized, dst_resized;

  char source_window[128] = "Source image ";
  char* equalized_window = "Equalized Image ";

    if( argc != 2 || !(src=imread(argv[1], 1)).data ) {
		printf("No input picture to use.\n");
        return -1;
	}

	strcat( source_window, getImageType(src.type()).c_str());
	

	  /// Convert to grayscale
  cvtColor( src, src, CV_BGR2GRAY );

  showHistogram(source_window, src);

  /// Apply Histogram Equalization
  equalizeHist( src, dst );

  showHistogram(equalized_window, dst);

  /// Display results
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  namedWindow( equalized_window, CV_WINDOW_AUTOSIZE );

  if ( src.size().width > 1920 || src.size().height > 1080 ) {
	  Size newSize(1280,720);
	  cv::resize(src, src_resized, newSize, 0, 0, cv::INTER_CUBIC);
	  imshow( source_window, src_resized );
  } else
	  imshow( source_window, src );

  if ( dst.size().width > 1920 || dst.size().height > 1080 ) {
	  Size newSize(1280,720);
	  cv::resize(dst, dst_resized, newSize, 0, 0, cv::INTER_CUBIC);
	  imshow( equalized_window, dst_resized );
  } else
	  imshow( equalized_window, dst );

  /// Wait until user exits the program
  waitKey(0);
}
