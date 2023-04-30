
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sstream"
/*
    发布方：
        1. 包含头文件
            "std_msgs/String.h"
        2. 初始化ROS节点
        3. 创建节点句柄
        4. 创建发布者对象
        5. 编写发布逻辑和数据
*/


int main(int argc, char *argv[])
{
    //2.
    ros::init(argc,argv,"sender");
    //3
    ros::NodeHandle nh;
    //4
    ros::Publisher pub = nh.advertise<std_msgs::String>("fang",10);
    //5
    //10hz sending frequency
    //
    std_msgs::String msg;

    ros::Rate rate(10); //10hz

    int count = 0; //index

    while(ros::ok())
    {
        count ++;
        std::stringstream ss;
        //concate string and num
        ss << "hello --->" <<count;
        msg.data = ss.str();

        //msg.data = "hello";
        pub.publish(msg);
        //log
        ROS_INFO("publish info: %s", ss.str().c_str());
        rate.sleep();
        // ros::spinOnce();
    }

    return 0;
}