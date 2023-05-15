#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define UP 1;
#define DOWN 2;

#define Left 1;
#define Right 2;
#define Middle 3;

class Digit {
public:
    int num;
    cv::Point c;//����ܵ�����
    cv::Point ic;//ͼ�����������

    cv::Point p[7];//���е�
    int p_info[7][2];
    int threshold;

    bool feature[7];
    void Where();
    void IsOneFourSevenEight();
    void GetFeature();
};

void Digit::Where() {
    for (int i = 0; i < num; i++) {
        if (p[i].y > c.y) {
            p_info[i][0] = DOWN;
        }
        else if (p[i].y < c.y) {
            p_info[i][0] = UP;
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
void Digit::IsOneFourSevenEight() {
    switch (num)
    {
    case 2:
        cout << "������1" << endl; break;
    case 3:
        cout << "������7" << endl; break;
    case 4:
        cout << "������4" << endl; break;
    case 7:
        cout << "������8" << endl; break;
    default:
        break;
    }
}

void Digit::GetFeature() {
    for (int i = 0; i < num; i++) {

    }
}