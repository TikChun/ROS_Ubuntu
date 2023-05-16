#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"
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
    
    // 创建一个坐标点
    geometry_msgs::PointStamped ps_son1;
    ps_son1.header.frame_id="son1";
    ps_son1.header.stamp = ros::Time::now();
    ps_son1.point.x = 1.0;
    ps_son1.point.y = 2.0;
    ps_son1.point.z = 3.0;

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
            geometry_msgs::TransformStamped son1_2_son2 = buf.lookupTransform("son2","son1",ros::Time::now());
            ROS_INFO("son1's relationship with son2: parent: %s, child: %s; shift:(%.2f,%.2f,%.2f)",
                        son1_2_son2.header.frame_id.c_str(),    // son1
                        son1_2_son2.child_frame_id.c_str(),     // son2
                        son1_2_son2.transform.translation.x,
                        son1_2_son2.transform.translation.y,
                        son1_2_son2.transform.translation.z);
            // 坐标系转化
            geometry_msgs::PointStamped ps_son2 = buf.transform(ps_son1,"son2");
            ROS_INFO("In son2: (%.2f,%.2f,%.2f)",ps_son2.point.x,ps_son2.point.y,ps_son2.point.z);            
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