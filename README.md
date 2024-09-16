# ***opencv_project***

*By 9.17  7:02*

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

## 结果

- 代码 详见 [main.cpp](./src/main.cpp)
- 由于图片过多，不再此处一一展示
- 详见 [resources](./resources/)