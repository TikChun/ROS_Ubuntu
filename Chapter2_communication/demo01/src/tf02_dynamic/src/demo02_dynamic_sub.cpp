#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

/*
    订阅发布的坐标系相对关系，传入一个坐标点，调用TF实现转换
    1.包含头文件
    2.初始化
    3.创建订阅对象
    4.组织一个坐标点数据
    5.转换算法，调用TF内置实现
    6.输出转换结果
*/

int main(int argc, char *argv[]){
    ros::init(argc,argv,"static_sub");
    ros::NodeHandle nh;

    tf2_ros::Buffer buf;    // 先创造一个buffer
    tf2_ros::TransformListener listener(buf);   // 创建监听对象
    
    geometry_msgs::PointStamped ps;
    // 参考的坐标系
    ps.header.frame_id="turtle1";
    // 时间辍
    ps.header.stamp = ros::Time(0); // 防止因时间对不上而出异常
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;
    // 坐标点设置完成

    /*
    terminate called after throwing an instance of 'tf2::LookupException'
    what():  "base_link" passed to lookupTransform argument target_frame does not exist. 
    已放弃 (核心已转储)
    
    在调用transform()前，坐标系的相对关系仍未收到

    solution:   
    1. ros::Duration(2).sleep(); 执行休眠
    2. 异常处理 
    */
   
    ros::Rate rate(10);
    while (ros::ok())
    {
        try
        {
            // 将ps转换为相对于base link的坐标点
            geometry_msgs::PointStamped ps_out;
            ps_out = buf.transform(ps,"world"); //#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

            ROS_INFO("translated coord: (%.2f,%.2f,%.2f),reference: %s",ps_out.point.x, ps_out.point.y, ps_out.point.z, ps_out.header.frame_id.c_str());
        }
        catch(const std::exception& e)
        {
            ROS_INFO("EXCEPTION: %s",e.what());
        }
        rate.sleep();
        ros::spinOnce();
        
    }
    


    return 0;
}