#include<digit.h>
#include<math.h>

void Start();

int main()
{
    Start();
    while (1) {
        string command;
        cout << ">>����ͼƬ��:";
        cin >> command;

        if (command == "stop") {
            return 1;
        }

        /*1.����ͼ��img*/
        Mat img = imread("img/" + command + ".jpg");
        if (img.data == NULL) {
            cout << "error: ͼƬ������Ѽ" << endl;
            cout << endl;
            continue;
        }
        //��ʼ����digit
        Digit digit(img);

        /*2.Ԥ����*/
        //�Ҷȴ���͸�˹ģ��
        Mat gray_img, gauiss_img;
        cvtColor(img, gray_img, COLOR_RGB2GRAY);
        GaussianBlur(gray_img, gauiss_img, Size(3, 3), 1.1);

        //��ֵ��
        Mat threshold_img;
        threshold(gauiss_img, threshold_img, 200, 255, THRESH_BINARY);

        //�����ʹ���,��ʴ����
        Mat kernel1 = getStructuringElement(MORPH_RECT, Size(4, 4));
        dilate(threshold_img, threshold_img, kernel1);
        Mat kernel2 = getStructuringElement(MORPH_RECT, Size(13, 13));
        erode(threshold_img, threshold_img, kernel2);

        namedWindow("test", WINDOW_NORMAL);
        imshow("test", threshold_img);

        /*3.��ȡ��������ĵ�*/
        //���������,Ҳ���Ǽ���������ܵĸ���
        vector<vector<Point>> contours;
        findContours(threshold_img, contours, 1, 1);
        drawContours(img, contours, -1, (0, 0, 255));

        img.at<Vec3b>(digit.ic)[0] = 255;
        img.at<Vec3b>(digit.ic)[1] = 0;
        img.at<Vec3b>(digit.ic)[2] = 0;

        //��ȡ������������ĵ�λ��
        digit.FindPoint(contours,img);

        img.at<Vec3b>(digit.c)[0] = 0;
        img.at<Vec3b>(digit.c)[1] = 0;
        img.at<Vec3b>(digit.c)[2] = 0;

        namedWindow("result", WINDOW_NORMAL);
        imshow("result", img);

        /*4.��ȡ��������*/
        if (digit.IsOneFourSevenEight()) {
            digit.Printme();
        }
        else {
            digit.GetFeature();

            digit.IsNumber();//�Ա���������
            digit.Printme();//��ӡ�����ܸ���, ���������ͼ�����������
        }
        //digit.GetFeature();

        //digit.IsNumber();//�Ա���������
        //digit.Printme();//��ӡ�����ܸ���, ���������ͼ�����������
        
        cout << "info: ��ͼƬ���ڰ��������,�Լ���" << endl;
        cout << endl;
        waitKey(0);
        destroyAllWindows();
    }
}

void Start() {
    cout << "-------zzz�Ľ����ҵ-------" << endl;
    cout << "Ctrl+C �رճ���" << endl;
    cout << "stop �رճ���" << endl;

    cout << "Info: ע����ն�ȡͼƬ��·��" << endl;
    cout << endl;
}
