#include "ros/ros.h"
#include "turtlesim/Pose.h"
/*
    订阅乌龟的位置动态信息

*/
void doPose(const turtlesim::Pose::ConstPtr &pose){
    ROS_INFO("Turtle Dynamic: coordinate(%.2f, %.2f), Direction(%.2f), Velocity: %.2f, Angular Velocity: %.2f",
            pose->x, pose->y, pose->theta, pose->linear_velocity, pose->angular_velocity);
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"sub_pose");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("turtle1/pose",100,doPose);
    ros::spin();
    return 0;
}