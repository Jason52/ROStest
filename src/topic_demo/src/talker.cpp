#include <ros/ros.h>
#include <topic_demo/gps.h>

int main(int argc,char** argv){
    ros::init(argc,argv,"talker");	//解析参数，命名节点
    ros::NodeHandle nh;			//创建句柄，实例化node
    topic_demo::gps msg;		//创建gps消息
    msg.x=1.0;
    msg.y=2.0;
    msg.state="working";
    ros::Publisher pub = nh.advertise<topic_demo::gps>("gps_info",1);
    pub.publish(msg);//发布消息
    ros::Rate loop_rate(1.0);
    
    while(ros::ok){
	msg.x=1.03*msg.x;
	msg.y=1.08*msg.y;
        ROS_INFO("Talker:GPS:x=%f,y=%f",msg.x,msg.y);	//输出屏幕msg
        pub.publish(msg);
	loop_rate.sleep();//定义发布频率，sleep
    }
    return 0;
}
