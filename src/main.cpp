#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 提取红色区域的辅助函数
Mat extractRedRegion(const Mat &hsv)
{
    Mat mask1, mask2;
    // 提取红色的区域（HSV颜色空间下红色的范围）
    inRange(hsv, Scalar(0, 100, 100), Scalar(10, 255, 255), mask1);
    inRange(hsv, Scalar(160, 100, 100), Scalar(180, 255, 255), mask2);
    // 位运算合并
    return mask1 | mask2;
}

int main()
{
    // 读取图像
    Mat img = imread("../resources/test_image.png");
    if (img.empty())
    {
        cout << "无法读取图像！" << endl;
        return -1;
    }

    // 转换颜色空间
    // 转换为灰度图
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    imwrite("../resources/gray.png", gray);

    // 转换为 HSV 图像
    Mat hsv;
    cvtColor(img, hsv, COLOR_BGR2HSV);
    imwrite("../resources/hsv.png", hsv);

    // 应用滤波操作
    // 均值滤波
    Mat meanFiltered;
    blur(img, meanFiltered, Size(5, 5));
    imwrite("../resources/meanFlt.png", meanFiltered);

    // 高斯滤波
    Mat gaussianFiltered;
    GaussianBlur(img, gaussianFiltered, Size(5, 5), 0);
    imwrite("../resources/gaussianFlt.png", gaussianFiltered);

    // 先高斯滤波后再转HSV（减噪，提升稳定性）
    Mat gflt2hsv;
    cvtColor(gaussianFiltered, gflt2hsv, COLOR_BGR2HSV);
    imwrite("../resources/gflt2hsv.png", gflt2hsv);

    // 特征提取
    // 提取红色颜色区域 (HSV 方法)
    Mat redMask = extractRedRegion(gflt2hsv);
    imwrite("../resources/redMask.png", redMask);

    // 寻找红色的外轮廓
    vector<vector<Point>> contours;
    findContours(redMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 绘制红色的外轮廓
    Mat contourImg = img.clone();
    drawContours(contourImg, contours, -1, Scalar(0, 255, 0), 2);
    imwrite("../resources/contourImg.png", contourImg);

    // 寻找红色的 bounding box
    Mat boundingBoxImg = img.clone();
    for (size_t i = 0; i < contours.size(); i++)
    {
        Rect boundingBox = boundingRect(contours[i]);
        rectangle(boundingBoxImg, boundingBox, Scalar(255, 0, 0), 2);

        // 计算轮廓面积
        double area = contourArea(contours[i]);
        cout << "轮廓 " << i << " 的面积: " << area << endl;
    }
    imwrite("../resources/boundingBoxImg.png", boundingBoxImg);

    // 提取高亮颜色区域并进行图形学处理
    // 灰度化
    Mat highlightGray;
    cvtColor(img, highlightGray, COLOR_BGR2GRAY);
    imwrite("../resources/highlightGray.png", highlightGray);

    // 二值化
    Mat binary;
    threshold(highlightGray, binary, 200, 255, THRESH_BINARY);
    imwrite("../resources/binary.png", binary);

    // 膨胀
    Mat dilated;
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(binary, dilated, element);
    imwrite("../resources/dilated.png", dilated);

    // 腐蚀
    Mat eroded;
    erode(dilated, eroded, element);
    imwrite("../resources/eroded.png", eroded);

    // 漫水填充
    Mat floodFilled = eroded.clone();
    floodFill(floodFilled, Point(0, 0), Scalar(255));
    imwrite("../resources/floodFilled.png", floodFilled);

    // 图像绘制
    // 绘制任意圆形、方形和文字
    Mat drawingImg = img.clone();
    circle(drawingImg, Point(500, 500), 500, Scalar(0, 0, 255), 5);
    rectangle(drawingImg, Point(400, 400), Point(1000, 1000), Scalar(255, 0, 0), 3);
    putText(drawingImg, "OpenCV", Point(200, 1000), FONT_HERSHEY_SIMPLEX, 10, Scalar(0, 255, 0), 2);
    imwrite("../resources/drawingImg.png", drawingImg);

    // 对图像进行处理
    // 图像旋转 35 度
    Mat rotatedImg;
    Point2f center((img.cols - 1) / 2.0, (img.rows - 1) / 2.0);
    Mat rotationMatrix = getRotationMatrix2D(center, 35, 1.0);
    warpAffine(img, rotatedImg, rotationMatrix, img.size());
    imwrite("../resources/rotatedImg.png", rotatedImg);

    // 图像裁剪为左上角 1/4
    Rect roi(0, 0, img.cols / 2, img.rows / 2);
    Mat croppedImg = img(roi);
    imwrite("../resources/croppedImg.png", croppedImg);

    // 显示结果图像
    imshow("原始图像", img);
    imshow("灰度图像", gray);
    imshow("HSV 图像", hsv);
    imshow("均值滤波", meanFiltered);
    imshow("高斯滤波", gaussianFiltered);
    imshow("滤后转 HSV", gflt2hsv);
    imshow("红色区域掩码", redMask);
    imshow("红色轮廓", contourImg);
    imshow("红色 Bounding Box", boundingBoxImg);
    imshow("灰度化", highlightGray);
    imshow("二值化", binary);
    imshow("膨胀后图像", dilated);
    imshow("腐蚀后图像", eroded);
    imshow("Flood Fill 图像", floodFilled);
    imshow("绘制的图形和文字", drawingImg);
    imshow("旋转后的图像", rotatedImg);
    imshow("裁剪后的图像", croppedImg);
    waitKey(0);
    return 0;
}
