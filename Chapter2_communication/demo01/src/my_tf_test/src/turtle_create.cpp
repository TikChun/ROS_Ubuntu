#include "ros/ros.h"
#include "turtlesim/Spawn.h"

int main(int argc, char *argv[]){
    ros::init(argc,argv,"create_turtle");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn msg;
    msg.request.name = "turtle2";
    msg.request.theta = 0.0;
    msg.request.x = 2.0;
    msg.request.y = 2.0;

    ros::service::waitForService("/spawn");

    if(client.call(msg)){
        // operation success
        ROS_INFO("We have successfully create a turtle");
        return 0;
    }
    ROS_INFO("We failed to create a turtle");
    return 0;
}