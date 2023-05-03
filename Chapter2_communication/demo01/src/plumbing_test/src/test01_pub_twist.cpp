#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
/*
    发布速度消息
        topic:  /turtle1/cmd_vel
        msgs:   geometry_msgs/Twist

        
*/
int main(int argc, char *argv[])
{
    ros::init(argc,argv,"my_control");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    ros::Rate rate(10);
    geometry_msgs::Twist my_msg;
    
    my_msg.linear.x = 1.0;
    my_msg.linear.y = 0;
    my_msg.linear.z = 0;

    my_msg.angular.z = 1.0;
    my_msg.angular.x = 0;
    my_msg.angular.y = 0;
    while(ros::ok()){
        pub.publish(my_msg);
        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}