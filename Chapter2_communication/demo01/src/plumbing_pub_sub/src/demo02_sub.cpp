#include "ros/ros.h"
#include "std_msgs/String.h"
/*
    订阅方：
        1. 包含头文件
            "std_msgs/String.h"
        2. 初始化ROS节点
        3. 创建节点句柄
        4. 创建订阅者对象
        5. 处理订阅到的数据
        6. spin()

*/
void doMsg(const std_msgs::String::ConstPtr &msg){
    // process received message
    ROS_INFO("subscriber: %s",msg->data.c_str());
}


int main(int argc, char *argv[])
{
    // 2
    ros::init(argc,argv,"subscriber");
    // 3
    ros::NodeHandle nh;
    // 4
    ros::Subscriber sub = nh.subscribe("fang",10,doMsg);
    // 6
    ros::spin();

    return 0;
}
