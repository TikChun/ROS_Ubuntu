#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/Twist.h"

//  换算出 turtle1 相对于 turtle2 的关系
//  计算角速度和线速度并发布



/*
    计算son1与son2的相对关系
    计算son1中的某个坐标点在son2中的坐标值

    1. 包含头文件
    2. 初始化
    3. 创建订阅对象
    4. 解析逻辑
    5. spinonce();
*/

int main(int argc, char *argv[]){
    ros::init(argc,argv,"tfs_sub");
    ros::NodeHandle nh;
    tf2_ros::Buffer buf;
    tf2_ros::TransformListener sub(buf);
    ros::Rate rate(10);
    // 1.创建发布对象
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle2/cmd_vel",100);

    while(ros::ok())
    {
        try
        {
            // 两坐标系相对关系
            /*
                A 相对于 B 的关系

                参数：  1.目标坐标系（B）；2.源坐标系（A）； 3.ros::TIme, 取间隔最短的两个坐标关系帧计算相对关系
                返回值：geometry_msgs::TransformStamped; 源相对于目标坐标系的相对关系
            */
            geometry_msgs::TransformStamped son1_2_son2 = buf.lookupTransform("turtle2","turtle1",ros::Time(0));
            // ROS_INFO("turtle1's relationship with turtle2: parent: %s, child: %s; shift:(%.2f,%.2f,%.2f)",
            //             son1_2_son2.header.frame_id.c_str(),    // turtle2
            //             son1_2_son2.child_frame_id.c_str(),     // turtle1
            //             son1_2_son2.transform.translation.x,
            //             son1_2_son2.transform.translation.y,
            //             son1_2_son2.transform.translation.z);    

            // 2.计算相对速度    
            geometry_msgs::Twist twist;
            // x = 系数 * root(y^2 + x^2)
            // angular z = 系数 * tan-1(对边，邻边)
            twist.linear.x = 0.5 * sqrt(pow(son1_2_son2.transform.translation.x, 2) + pow(son1_2_son2.transform.translation.y, 2));
            twist.angular.z = 4 * atan2(son1_2_son2.transform.translation.y, son1_2_son2.transform.translation.x);


            pub.publish(twist);
        }
        catch(const std::exception& e)
        {
            ROS_INFO("exception: %s",e.what());
        }
        
        

        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}