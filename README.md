# ***opencv_project***

*By 9.17  7:02*
*Update by 9.18*

---

## 概述

- 之前在b站观看过高宁录制的一期[培训视频](https://www.bilibili.com/video/BV1JzWeemEWL/?share_source=copy_web&vd_source=932a3dd36ca446e5817068a0a0f671b7)，并落实了视频里的作业
- 故在这次任务之前也算浅浅研究了一点
- 因而这次任务对我来说相对轻松

## 学习过程

- 由于大多函数都略有了解，便把写代码任务交给了GPT
    - [咨询记录](https://chatgpt.com/share/66e8af17-a0a8-800f-a51e-55f7f44eacc8)
- 本人主要的学习时间花费在研究函数上
    - 函数功能及名称
    - 各参数意义
- ***Something Special***
    - 文件结构： 将 main.cpp 放置在一个新的文件夹下，可以保证从 main.cpp 和 OpenCV_Project 一个编写一个运行时访问 resources 文件夹的路径一致
    - 此处可以采用位运算合并图像
        ```cpp
        return mask1 | mask2;
        ```
    - 此处设置参数为 -1 可以画出全部轮廓
        ```cpp
        drawContours(contourImg, contours, -1, Scalar(0, 255, 0), 2);
        ```
    - 使用 git push 时忽略 build 文件夹
        - 新建一个 .gitignore 文件
        - 在文件内加入 /build/

## 函数功能&参数

- ***所涉及到的所有函数均可以 Ctrl + 左键 在 .hpp 文件中查看*** 

- 图片的基本类型为 Mat 矩阵
    - 矩阵中每一个元素一般为 unchar 类型，储存单通道
    - 或者多元向量，用于储存三通道图片或四通道
- imread("filename")
    - 参数为文件的地址
    - 返回一个 Mat 类的变量
- cvtcolor(input,output,code)
    - 输入矩阵，通过引用的方式输出矩阵，转换参数
    - 具体参数可以查看 ColorConversionCodes
    - 常用 RGB BGR HSV GRAY
- imwrite("filename",input)
    - 保存文件地址 需保存的变量
- blur(input,output,Size(x,y))
    - 输入输出矩阵
    - Size 类型为二元组，一般用于记录图片 rows&cols
    - 此处为记录核的大小
- GaussianBlur(input,output,Size(x,y),sgmX,sgmY=(0.0))
    - 前参数同上
    - > sigmaX – Gaussian kernel standard deviation in X direction;
    - > sigmaY – Gaussian kernel standard deviation in Y direction; if sigmaY is zero, it is set to be equal to sigmaX, if both sigmas are zeros, they are computed from ksize.width and ksize.height, respectively (see #getGaussianKernel for details); to fully control the result regardless of possible future modifications of all this semantics, it is recommended to specify all of ksize, sigmaX, and sigmaY.
    - ~~后面这两个参数大概是在说核的函数取值？~~
- findContours(input,contours,mode,method)
    - 输出的 contours 为 vector<vector<Point>> 类型
    - mode 代表检索轮廓的模式，有最外层，有父子结构等
    - ~~详见 enum RetrievalModes~~
    - method 代表检索轮廓的方法
    - ~~详见 enum ContourApproximationModes~~
- drawContours(output,contours,contoursIdx,Scalar(b,g,r),thickness,linetype)
    - contoursIdx 轮廓编号
    - *esp.* 为 -1 时，画出全部轮廓
    - Scalar(b,g,r) 为颜色参量
- boundingRect(contours[i])
    - 第 i 个轮廓的 boundingbox
- rectangle(output,boundingBox,Scalar(b,g,r),thickness,linetype)
    - 画出 boundingbox
    - 也可以用于画圆形？
- contourArea(contours[i])
    - 轮廓 i 的面积
- threshold(input,output,thresh,maxval,type)
    - thresh 分界值
    - output channels 不变
- getStructuringElement(shape,Size(x,y))
- dilate(input,output,element);
- erode(input,output,element);
- floodFill(in&output,Point(x,y),Scalar(b,g,r))
    - 输入与输出同矩阵
    - Point(x,y) 起始点
- circle(in&output,pt1(x,y),pt2(x,y),Scalar(b,g,r),thickness,linetype)
    - 同 rectangle()
- putText(in&output,"text",pt(x,y),fontface,fontscale,Scalar(b,g,r),thickness,linetype)
- getRotationMatrix2D(center,rate)
    - 中心点，缩放比例
- warpAffine(input,output,rotationMat,Size(x,y))
    - rotationMat 旋转矩阵
    - Size(x,y) 输出图像大小

## 结果

- 代码 详见 [main.cpp](./src/main.cpp)
- 由于图片过多，不再此处一一展示
- 详见 [resources](./resources/)