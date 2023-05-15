#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
    Mat test = imread("E:/zhyp1/Pictures/雁阵摄影部/春天主题/加水印.jpg"); //载入图像到test
    imshow("test", test);
    waitKey(0);
    return 0;
}
