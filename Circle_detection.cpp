//
//  main.cpp
//  Opencv3_test002
//
//  Created by Ye172 on 2016/11/2.
//  Copyright © 2016年 Yee172. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
/*头文件有点多，主要是为了确保所有的函数都可以正常的运作*/
using namespace cv;
using namespace std;

/*高斯滤波的宏*/

#define Ksize Size(7,7)//origin Size(7,7)
/*ksize，高斯内核的大小。其中ksize.width和ksize.height可以不同，但他们都必须为正数和奇数*/
#define sigmaX 2//origin 2
#define sigmaY 2//origin 2
/*表示高斯核函数在X、Y方向的的标准偏差*/

/*高斯滤波的宏*/


/*
 霍夫变换的具体步骤为：
 第一阶段：检测圆心
 1.1、对输入图像边缘检测；
 1.2、计算图形的梯度，并确定圆周线，其中圆周的梯度就是它的法线；
 1.3、在二维霍夫空间内，绘出所有图形的梯度直线，某坐标点上累加和的值越大，说明在该点上直线相交的次数越多，也就是越有可能是圆心；
 1.4、在霍夫空间的4邻域内进行非最大值抑制；
 1.5、设定一个阈值，霍夫空间内累加和大于该阈值的点就对应于圆心。
 第二阶段：检测圆半径
 2.1、计算某一个圆心到所有圆周线的距离，这些距离中就有该圆心所对应的圆的半径的值，这些半径值当然是相等的，并且这些圆半径的数量要远远大于其他距离值相等的数量；
 2.2、设定两个阈值，定义为最大半径和最小半径，保留距离在这两个半径之间的值，这意味着我们检测的圆不能太大，也不能太小；
 2.3、对保留下来的距离进行排序；
 2.4、找到距离相同的那些值，并计算相同值的数量；
 2.5、设定一个阈值，只有相同值的数量大于该阈值，才认为该值是该圆心对应的圆半径；
 2.6、对每一个圆心，完成上面的2.1～2.5步骤，得到所有的圆半径。
*/


/*霍夫圆的宏*/

#define dp 1.2//origin 1.5
/*dp为第一阶段所使用的霍夫空间的分辨率，dp=1时表示霍夫空间与输入图像空间的大小一致，dp=2时霍夫空间是输入图像空间的一半，以此类推*/
#define min_dist 50//origin 10
/*minDist为圆心之间的最小距离，如果检测到的两个圆心之间距离小于该值，则认为它们是同一个圆心*/
#define param1 150//origin 200
/*param1为边缘检测时使用Canny算子的高阈值*/
#define param2 80//origin 100
/*param2为步骤1.5和步骤2.5中所共有的阈值*/
#define min_radius 20//origin 0
#define max_radius 0//origin 0
/*所检测到的圆半径的最小值和最大值，0的话应该就是不受限制吧*/

/*霍夫圆的宏*/

#define wait_time 90//origin 30
/*WaitKey的参数，单位为ms，0的话每次按下任意键继续*/



int main()
{
    /*time test codes*/
    
//    clock_t start_time = clock();
    
    /*time test codes*/
    
    /*开起摄像头*/
    
    VideoCapture capture;
    capture.open(0);
    
    /*开起摄像头*/
    
    
    /*调用视频文件*/
    
//    string path = "/Users/apple/Downloads/无人机航拍素材4-ev-0.MOV";
//    VideoCapture capture(path);
    
    /*调用视频文件*/
    
    
    Mat edges;//定义转化的灰度图
    
    if (!capture.isOpened()) return -1;
    
    namedWindow("Camera", CV_WINDOW_NORMAL);
    
    /*time test codes*/
    
//    clock_t end_time = clock();
//    cout << "Running time(start) is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    
    /*time test codes*/
    
    while (1)
    {
        
        /*time test codes*/
        
//        start_time = clock();
        
        /*time test codes*/
        
        
        Mat frame;
        capture >> frame;
        
        if (!frame.data) return -1;
        
        cvtColor(frame, edges, CV_BGR2GRAY);
//        threshold(edges,edges,145,255,THRESH_BINARY);
        GaussianBlur(edges, edges, Ksize, sigmaX, sigmaY);//高斯滤波
        
        vector<Vec3f> circles;
        HoughCircles(edges, circles, CV_HOUGH_GRADIENT, dp, min_dist, param1, param2, min_radius, max_radius);//霍夫圆
        
        for (size_t i = 0; i < circles.size(); i++)
        {
            
            cout << "x: " << cvRound(circles[i][0]) << " y: " << cvRound(circles[i][1]) << endl;//输出圆心的坐标值
            
            /*用于可视化测试*/
            
//            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//            int radius = cvRound(circles[i][2]);
//            circle(frame, center, 3, Scalar(0, 255, 0), -1, 8, 0);//绘制圆心
//            circle(frame, center, radius, Scalar(155, 50, 255), 3, 8, 0);//绘制圆轮廓
            
            /*用于可视化测试*/

        }
        
        
        /*用于可视化测试*/
        
//        imshow("Camera", frame);
        
        /*用于可视化测试*/
        
        
        /*time test codes*/
        
//        end_time = clock();
//        cout << "Running time(working) is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
        
        /*time test codes*/
        
        
        waitKey(wait_time);
        
    }
    
    return 0;
}
