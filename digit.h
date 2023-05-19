#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

enum Info {UP,DOWN,Middle, Left, Right,NONE};
const bool Feature[10][7] = {
    {0,1,1,1,1,1,1},
    {0,0,0,1,1,0,0},
    {1,0,1,1,0,1,1},//2
    {1,0,1,1,1,1,0},
    {1,1,0,1,1,0,0},
    {1,1,1,0,1,1,0},//5
    {1,1,1,0,1,1,1},
    {0,0,1,1,1,0,0},//7
    {1,1,1,1,1,1,1},
    {1,1,1,1,1,1,0}

};

class Digit {
public:
    int num;
    int result;
    cv::Point c;//数码管的中心
    cv::Point ic;//图像整体的中心

    cv::Point p[7];//所有点
    Info p_info[7][2];
    int threshold;

    bool feature[7];

    Digit(Mat& img);
    void FindPoint(vector<vector<Point>>& contours, Mat &img);
    void Where();

    bool IsOneFourSevenEight();
    void GetFeature();
    void IsNumber();

    void Printme();
};

Digit::Digit(Mat& img) {
    num = 0;
    result = 10;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 2; j++) {
            p_info[i][j] = NONE;
        }
        feature[i] = 0;
    }

    threshold = 30;

    ic.x = img.cols / 2;
    ic.y = img.rows / 2;
    c.x = ic.x;
    c.y = ic.y;
}

//函数功能:录入数码管中心坐标
void Digit::FindPoint(vector<vector<Point>>& contours, Mat &img) {
    Rect a;
    double dis = 225;
    num = 0;
    for (int i = 0; i < contours.size(); i++) {

        a = boundingRect(contours[i]);
        if (a.area() < 300)
            continue;

        p[num].x = a.x + a.width / 2;
        p[num].y = a.y + a.height / 2;
        //cout << p[num].x << " " << p[num].y << endl;
        //寻找中心点坐标

        if (dis > pow(p[num].x - ic.x, 2) + pow(p[num].y - ic.y, 2)) {
            dis = pow(p[num].x - ic.x, 2) + pow(p[num].y - ic.y, 2);
            c.x = p[num].x;
            c.y = p[num].y;
        }

        rectangle(img, a,Scalar(0,0,255));

        img.at<Vec3b>(p[num]) = (255, 0, 0);
        num++;
    }
    //标记每个点对应的数码管序号
    Where();
}

//函数功能:标记每个数码管中心点大致位置,例如如果在右上,p_info={UP,Right}
void Digit::Where() {

    for (int i = 0; i < num; i++) {
        if (p[i].y > c.y+10) {
            p_info[i][0] = DOWN;
        }
        else if (p[i].y < c.y-10) {
            p_info[i][0] = UP;
        }
        else {
            p_info[i][0] = Middle;
        }
        //
        if (p[i].x < c.x - threshold) {
            p_info[i][1] = Left;
        }
        else if (p[i].x > c.x + threshold) {
            p_info[i][1] = Right;
        }
        else {
            p_info[i][1] = Middle;
        }
    }
}

//函数功能:根据高亮数码管的个数直接判断是否为数字1,4,7或8
bool Digit::IsOneFourSevenEight() {
    switch (num)
    {
    case 2:
        result = 1; return true;
    case 3:
        result = 7; return true;
    case 4:
        result = 4; return true;
    case 7:
        result = 8; return true;
    default:
        return false;
        break;
    }
}

//函数功能:根据p_info,得到图片的特征向量
void Digit::GetFeature() {
    for (int i = 0; i < num; i++) {
        Info f1 = p_info[i][0], f2 = p_info[i][1];
        //中心
        if (f1 == Middle && f2 == Middle) {
            feature[0] = 1;
        }
        else if (f1 == UP && f2 == Left) {
            feature[1] = 1;
        }
        else if (f1 == UP && f2 == Middle) {
            feature[2] = 1;
        }
        else if (f1 == UP && f2 == Right) {
            feature[3] = 1;
        }
        else if (f1 == DOWN && f2 == Right) {
            feature[4] = 1;
        }
        else if (f1 == DOWN && f2 == Middle) {
            feature[5] = 1;
        }
        else if (f1 == DOWN && f2 == Left) {
            feature[6] = 1;
        }
    }
}

//函数功能:与每一个数字的特征向量进行比对
void Digit::IsNumber() {
    
    for (int i = 0; i < 10; i++) {
        int a=0;//
        for (int j = 0; j < 7; j++) {
            a += feature[j] ^ Feature[i][j];
        }

        if (a == 0) {
            result = i;
            break;
        }
    }
}

//函数功能:打印重要信息到命令行
void Digit::Printme() {
    //cout << "------PrintResult-----" << endl;
    cout << " 图中电亮的数码管个数: " << num;
    if (!IsOneFourSevenEight()) {
        cout << endl;
        cout << " 图片特征向量:";
        for (int i = 0; i < 7; i++) {
            cout << " " << feature[i];
        }
    }
    cout << endl;

    if (result == 10) {
        cout << " 无法识别图片!!!" << endl;
    }
    else {
        cout << " 图片识别结果是: " << result << endl;

    }

}

