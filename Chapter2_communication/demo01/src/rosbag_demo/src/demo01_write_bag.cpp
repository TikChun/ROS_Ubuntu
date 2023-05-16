#include "ros/ros.h"
#include "rosbag/bag.h"
#include "std_msgs/String.h"

/*
    使用 rosbag 向磁盘文件写出数据（话题+数据）

    1. 导包
    2. 初始化
    3. 创建rosbag对象
    4. 打开文件流
    5. 写数据
    6. 关闭文件流
*/

int main(int argc, char *argv[]){
    ros::init(argc,argv,"bag_write");
    ros::NodeHandle nh;
    // 3
    rosbag::Bag bag;
    // 4
    bag.open("hello.bag",rosbag::BagMode::Write);
    // 5
    std_msgs::String msg;
    msg.data = "hello xxx";
    /*
        参数1：话题
        参数2：时间戳
        参数3：消息
    */
    bag.write("/chatter",ros::Time::now(),msg);
    // 6
    bag.close();
    return 0;
}