#include<digit.h>
#include<math.h>


int main()
{
    Digit digit;

    Mat img = imread("img/8-1.jpg"); //载入图像到test
    digit.ic.x = img.cols / 2; 
    digit.ic.y = img.rows / 2;
    digit.threshold = 20;
    Mat gray_img; 
    cvtColor(img, gray_img, COLOR_RGB2GRAY);
    Mat gauiss_img;
    GaussianBlur(gray_img, gauiss_img, Size(5, 5), 7.1);

    //Mat erode_img;
    //erode(gauiss_img, erode_img, 5);
    Mat threshold_img;
    threshold(gauiss_img, threshold_img, 200, 255, THRESH_BINARY);



    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(threshold_img, threshold_img,kernel);



    namedWindow("test", WINDOW_NORMAL);
    imshow("test", threshold_img);
    //
    vector<vector<Point>> contours;
    findContours(threshold_img, contours, 1,1);
    drawContours(img, contours, -1, (0, 0, 255));

    digit.num = contours.size();
    img.at<Vec3b>(digit.ic)[0] = 255;
    img.at<Vec3b>(digit.ic)[1] = 0;
    img.at<Vec3b>(digit.ic)[2] = 0;

    Rect a;
    double dis = 10000;
    for (int i = 0; i < contours.size(); i++) {
   
        a = boundingRect(contours[i]);
        digit.p[i].x = a.x + a.width / 2;
        digit.p[i].y = a.y + a.height / 2;
        cout << digit.p[i].x<<" " << digit.p[i].y << endl;
        //寻找中心点坐标

        if (dis > pow(digit.p[i].x - digit.ic.x, 2) + pow(digit.p[i].y - digit.ic.y, 2)) {
            dis = pow(digit.p[i].x - digit.ic.x, 2) + pow(digit.p[i].y - digit.ic.y, 2);
            digit.c.x = digit.p[i].x;
            digit.c.y = digit.p[i].y;
        }

        rectangle(img, a, (255, 0, 0));

        img.at<Vec3b>(digit.p[i]) = (255, 0, 0);
    }

    img.at<Vec3b>(digit.c)[0] = 0;
    img.at<Vec3b>(digit.c)[1] = 0;
    img.at<Vec3b>(digit.c)[2] = 255;
    //
    //for (int i = 0; i < digit.num; i++) {
    //    if (digit.p[i].y > digit.c.y) {
    //        digit.p_info[i][0] = DOWN;
    //    }
    //    else if (digit.p[i].y < digit.c.y) {
    //        digit.p_info[i][0] = UP;
    //    }
    //    //
    //    if (digit.p[i].x < digit.c.x - digit.threshold) {
    //        digit.p_info[i][1] = Left;
    //    }
    //    else if (digit.p[i].x > digit.c.x + digit.threshold) {
    //        digit.p_info[i][1] = Right;
    //    }
    //    else {
    //        digit.p_info[i][1] = Middle;
    //    }     
    //}
    digit.Where();

    int c = 4;
    cout << digit.p[c].x << " " << digit.p[c].y << endl;
    cout << digit.p_info[c][0] << " " << digit.p_info[c][1] << endl;

    img.at<Vec3b>(digit.p[c])[0] = 0;
    img.at<Vec3b>(digit.p[c])[1] = 0;
    img.at<Vec3b>(digit.p[c])[2] = 255;


    digit.IsOneFourSevenEight();


    namedWindow("result", WINDOW_NORMAL);
    imshow("result", img);
    
    waitKey(0);
    return 0;
}
