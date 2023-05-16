#include "ros/ros.h"
#include "rosbag/bag.h"
#include "std_msgs/String.h"
#include "rosbag/view.h"


int main(int argc, char *argv[]){

    ros::init(argc,argv,"rosbag_read");
    ros::NodeHandle nh;
    rosbag::Bag bag;
    bag.open("hello.bag",rosbag::BagMode::Read);

    for (auto && m: rosbag::View(bag))  // Important
    {
        std::string topic = m.getTopic();
        ros::Time time = m.getTime();
        std_msgs::StringPtr p = m.instantiate<std_msgs::String>();
        ROS_INFO("RECEIVED MESG: topic: %s, time: %.2f, msg: %s",topic.c_str(),time.toSec(),p->data.c_str());
    }
    

    bag.close();
    return 0;
}