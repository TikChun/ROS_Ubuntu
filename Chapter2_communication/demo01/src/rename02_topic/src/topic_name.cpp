#include "ros/ros.h"
#include "std_msgs/String.h"

/*
    演示不同类型的话题名称设计
*/

int main(int argc, char *argv[]){
    ros::init(argc,argv,"hello");
    // ros::NodeHandle nh;

    //  设置不同类型的话题
    // 1.全局 --- 话题名称以 / 开头，与节点没有任何关系,也可以设置自己的命名空间
    // ros::Publisher pub = nh.advertise<std_msgs::String>("/chatter",1000);
    // ros::Publisher pub = nh.advertise<std_msgs::String>("/yyy/chatter",1000);

    // 2.相对 --- 非 / 开头
    // ros::Publisher pub = nh.advertise<std_msgs::String>("chatter",1000);
    // ros::Publisher pub = nh.advertise<std_msgs::String>("yyy/chatter",1000);

    // 3.私有 --- 创建特定 NodeHandle
    ros::NodeHandle nh("~");
    // ros::Publisher pub = nh.advertise<std_msgs::String>("chatter",1000);
    ros::Publisher pub = nh.advertise<std_msgs::String>("yyy/chatter",1000);

    // 全局话题的优先级更高

    while(ros::ok()){

    }
    return 0;
}