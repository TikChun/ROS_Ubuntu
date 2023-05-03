#include "ros/ros.h"
/*
    修改背景色的参数
*/

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"change_color");
    // THis time, we dont have to use NodeHandler, use ros::param
    ros::param::set("/turtlesim/background_r",0);
    ros::param::set("/turtlesim/background_g",0);
    ros::param::set("/turtlesim/background_b",0);
    return 0;
}