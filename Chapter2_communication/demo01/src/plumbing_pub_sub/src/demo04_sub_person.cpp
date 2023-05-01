#include "ros/ros.h"
#include "plumbing_pub_sub/Person.h"
/*
1. 包含头文件
2. 初始化ROS节点
3. 创建节点句柄
4. 创建订阅者对象
5. 处理数据
6. spin()
*/

void DoPerson(const plumbing_pub_sub::Person::ConstPtr& person){
    ROS_INFO("Received: Name: %s, Age: %d, Height: %.2f",person->name.c_str(),person->age,person->height);
}


int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ROS_INFO("Subscriber:");
    // 2
    ros::init(argc,argv,"student");
    // 3
    ros::NodeHandle nh;
    // 4
    ros::Subscriber sub = nh.subscribe("chat",10,DoPerson);
    // 6
    ros::spin();
    return 0;
}