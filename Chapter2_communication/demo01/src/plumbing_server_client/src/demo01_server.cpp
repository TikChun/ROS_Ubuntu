#include "ros/ros.h"
#include "plumbing_server_client/Addints.h"
/*
    SERVER
    1. 包含头文件
    2. 初始化ROS节点
    3. 创建节点句柄
    4. 创建一个服务对象
    5. 处理请求并产生响应
    6. spin()
*/

bool doNums(plumbing_server_client::Addints::Request &request, plumbing_server_client::Addints::Response &response){
    // 1处理请求
    int num1 = request.num1;
    int num2 = request.num2;
    ROS_INFO("num1: %d, num2: %d",num1, num2);
    // 2.组织逻辑
    int sum = num1 + num2;
    response.sum = sum;
    ROS_INFO("sum: %d ",sum);
    return true;
}

int main(int argc, char *argv[])
{
    // 2
    ros::init(argc,argv,"Company"); // Unique node name
    // 3
    ros::NodeHandle nh;
    // 4
    ros::ServiceServer server = nh.advertiseService("addInts",doNums);
    ROS_INFO("Server: waiting for connection");
    // 6
    ros::spin();
    return 0;
}