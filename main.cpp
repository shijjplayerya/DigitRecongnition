#include<digit.h>
#include<math.h>

void Start();

int main()
{
    Start();
    while (1) {
        string command;
        cout << ">>输入图片名:";
        cin >> command;

        if (command == "stop") {
            return 1;
        }

        /*1.载入图像到img*/
        Mat img = imread("img/" + command + ".jpg");
        if (img.data == NULL) {
            cout << "error: 图片不存在鸭" << endl;
            cout << endl;
            continue;
        }
        //初始化类digit
        Digit digit(img);

        /*2.预处理*/
        //灰度处理和高斯模糊
        Mat gray_img, gauiss_img;
        cvtColor(img, gray_img, COLOR_RGB2GRAY);
        GaussianBlur(gray_img, gauiss_img, Size(3, 3), 1.1);

        //二值化
        Mat threshold_img;
        threshold(gauiss_img, threshold_img, 200, 255, THRESH_BINARY);

        //先膨胀处理,后腐蚀处理
        Mat kernel1 = getStructuringElement(MORPH_RECT, Size(4, 4));
        dilate(threshold_img, threshold_img, kernel1);
        Mat kernel2 = getStructuringElement(MORPH_RECT, Size(13, 13));
        erode(threshold_img, threshold_img, kernel2);

        namedWindow("test", WINDOW_NORMAL);
        imshow("test", threshold_img);

        /*3.提取数码管中心点*/
        //检测封闭区域,也就是检测高亮数码管的个数
        vector<vector<Point>> contours;
        findContours(threshold_img, contours, 1, 1);
        drawContours(img, contours, -1, (0, 0, 255));

        img.at<Vec3b>(digit.ic)[0] = 255;
        img.at<Vec3b>(digit.ic)[1] = 0;
        img.at<Vec3b>(digit.ic)[2] = 0;

        //提取高亮数码管中心点位置
        digit.FindPoint(contours,img);

        img.at<Vec3b>(digit.c)[0] = 0;
        img.at<Vec3b>(digit.c)[1] = 0;
        img.at<Vec3b>(digit.c)[2] = 0;

        namedWindow("result", WINDOW_NORMAL);
        imshow("result", img);

        /*4.提取特征向量*/
        if (digit.IsOneFourSevenEight()) {
            digit.Printme();
        }
        else {
            digit.GetFeature();

            digit.IsNumber();//对比特征向量
            digit.Printme();//打印高亮管个数, 特征向量和检测结果到命令窗口
        }
        //digit.GetFeature();

        //digit.IsNumber();//对比特征向量
        //digit.Printme();//打印高亮管个数, 特征向量和检测结果到命令窗口
        
        cout << "info: 在图片窗口按下任意键,以继续" << endl;
        cout << endl;
        waitKey(0);
        destroyAllWindows();
    }
}

void Start() {
    cout << "-------zzz的结课作业-------" << endl;
    cout << "Ctrl+C 关闭程序" << endl;
    cout << "stop 关闭程序" << endl;

    cout << "Info: 注意对照读取图片的路径" << endl;
    cout << endl;
}
