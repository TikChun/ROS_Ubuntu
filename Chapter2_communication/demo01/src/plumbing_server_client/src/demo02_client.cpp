#include "ros/ros.h"
#include "plumbing_server_client/Addints.h"
/*
    Client
    1. 包含头文件
    2. 初始化ROS节点
    3. 创建节点句柄
    4. 创建一个客户端对象
    5. 提交请求并处理响应
*/

int main(int argc, char *argv[])
{
    if(argc != 3) return 1; //input checking
    // 2
    ros::init(argc,argv,"Jack");
    // 3
    ros::NodeHandle nh;
    // 4
    ros::ServiceClient client = nh.serviceClient<plumbing_server_client::Addints>("addInts");
    // 5
    plumbing_server_client::Addints ai;
    ai.request.num1 = atoi(argv[1]);  // rosrun xxxx xxxx num1 num2, argv[0] = name_of_function
    ai.request.num2 = atoi(argv[2]);  // better to have them checked
    //client.waitForExistence();  // *wait for the server*
    ros::service::waitForService("addInts");    // same as above, two options
    if (client.call(ai)){   // Send out the message, and get reply
        ROS_INFO("Operation success");
        ROS_INFO("Result: %d",ai.response.sum);
        return 0;
    }
    ROS_INFO("Opeartion Failed");
    return 0;
}