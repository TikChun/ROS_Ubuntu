#include "ros/ros.h"

/*
    参数的新增与修改
    设置机器人的共享参数，类型，半径
        再修改半径
    
1.  ros::NodeHandle
        setParam()
2.  ros::param
        set()


*/

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"set_param_c");
    ros::NodeHandle nh;
    // Create
    // Method 1
    // nh.setParam("type","Yellow_Car");
    // nh.setParam("radius",0.15);
    // Method 2
    ros::param::set("type","Yello_Car");
    ros::param::set("radius",0.15);

    // Modify
    // Method 1
    // nh.setParam("radius",0.2);
    // Method 2
    ros::param::set("radius",0.2);
    ROS_INFO("radius = %.2f",nh.param<double>("radius",-1));
    return 0;
}