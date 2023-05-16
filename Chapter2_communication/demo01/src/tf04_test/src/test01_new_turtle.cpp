#include "ros/ros.h"
#include "turtlesim/Spawn.h"
/*
    向服务器发送请求，生成一只新乌龟
        topic:  /spawn
        msg;    turtlesim/Spawn
*/
int main(int argc, char *argv[])
{
    ros::init(argc,argv,"service_call");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn spawn;
    spawn.request.x = 1.0;
    spawn.request.y = 4.0;
    spawn.request.theta = M_PI/2;
    spawn.request.name = "turtle2";

    ros::service::waitForService("/spawn"); // wait for server, !!!IMPORTANT!!!
    
    if(client.call(spawn))
    {
        ROS_INFO("successful request, new turtle with name %s",spawn.response.name.c_str());
        return 0;
    }
    ROS_INFO("Failed request");
    return 0;
}