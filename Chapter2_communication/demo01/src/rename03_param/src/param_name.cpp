#include "ros/ros.h"

int main(int argc, char *argv[]){
    ros::init(argc,argv,"hello");
    ros::NodeHandle nh;

    /*
        演示如何使用ros::param 来设置参数
    */
    // 1.全局
    ros::param::set("/radiusA",100);
    // 2.相对
    ros::param::set("radiusA",100);
    // 3.私有
    ros::param::set("~radiusA",100);
    /*
        使用Nodeandle设置参数
    */
    // 1.全局
    nh.setParam("/radius_nh",1000);
    // 2.相对
    nh.setParam("radius_nh",1000);
    // 3.私有
    ros::NodeHandle nh_private("~");
    nh_private.setParam("radius_nh",1000);
    return 0;
}