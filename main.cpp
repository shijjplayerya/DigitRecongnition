#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
    Mat test = imread("E:/zhyp1/Pictures/������Ӱ��/��������/��ˮӡ.jpg"); //����ͼ��test
    imshow("test", test);
    waitKey(0);
    return 0;
}
