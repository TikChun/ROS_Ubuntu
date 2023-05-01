#include "ros/ros.h"
#include "plumbing_pub_sub/Person.h"

/*

1. 包含头文件
2. 初始化ROS节点
3. 创建节点句柄
4. 创建发布者对象
5. 编写发布逻辑和数据

*/


int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ROS_INFO("Publisher:");
    // 2
    ros::init(argc,argv,"class");
    // 3
    ros::NodeHandle nh;
    // 4
    ros::Publisher pub = nh.advertise<plumbing_pub_sub::Person>("chat",10);
    // 5
    plumbing_pub_sub::Person person;
    person.name = "Jack";
    person.age = 1;
    person.height = 1.73;
    ros::Rate rate(1);
    while (ros::ok())
    {
        pub.publish(person);
        ROS_INFO("Sent message: %s, %d, %.2f",person.name.c_str(),person.age,person.height);
        rate.sleep();
        person.age += 1;
        ros::spinOnce();    // Recommended
    }
    
    
    return 0;
}