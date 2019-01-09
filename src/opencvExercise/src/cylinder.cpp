#include <ros/ros.h>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/image_encodings.h>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;

cv_bridge::CvImagePtr cv_ptr;
using namespace cv;

class ImageConverter
{
private:
    ros::NodeHandle nh_;
    //用于将msg信息转换为openCV中的Mat数据
    image_transport::ImageTransport it_;
    //订阅摄像头发布的信息
    image_transport::Subscriber image_sub_;
public:
    ImageConverter()
    : it_(nh_)
    {
        //设置订阅摄像机
        image_sub_ = it_.subscribe("/usb_cam/image_raw", 1, &ImageConverter::imageCb, this);
    }

    ~ImageConverter(){
    }

    //收到摄像机后的回调函数
    void imageCb(const sensor_msgs::ImageConstPtr& msg){
        try{
            //将收到的消息使用cv_bridge转移到全局变量图像指针cv_ptr中，其成员变量image就是Mat型的图片
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }

        catch (cv_bridge::Exception& e){
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
        //处理图片信息
        myCode();
    }
    //你的代码可以移植在此处
    int myCode(){   
        Mat img=cv_ptr->image;
        cv::imshow("win",img);
        return 0;
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_converter");
    ImageConverter ic;
    cv::Mat image;
    image = cv::imread ( argv[1] ); //cv::imread函数读取指定路径下的图像
    //循环等待
    ros::spin();
    return 0;
}
