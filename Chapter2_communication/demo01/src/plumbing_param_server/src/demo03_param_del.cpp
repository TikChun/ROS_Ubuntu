#include "ros/ros.h"

/*
    参数删除
    1. ros::NodeHandle
        delParam()
    2. ros::param
        del()
*/

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"param_del_c");
    ros::NodeHandle nh;
    // Method 1
    // if(nh.deleteParam("radius")) ROS_INFO("successful deletion");
    // Method 2
    if(ros::param::del("radius")) ROS_INFO("successful deletion");
    return 0;
}