#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"
/*
    需要订阅乌龟的位姿信息，转换为相对于世界(窗体)的坐标关系，并发布
        话题：/turtle1/pose
        消息: turtlesim/Pose

        1. 包含头文件
        2. 初始化
        3. 创建订阅对象，订阅话题
        4. 回调函数处理信息，转换为坐标相对关系并发布
        5. spin()
*/

void doPose(const turtlesim::Pose::ConstPtr& pose){
    static tf2_ros::TransformBroadcaster pub;
    geometry_msgs::TransformStamped ts;
    ts.header.frame_id = "world";
    ts.header.stamp = ros::Time::now();
    ts.child_frame_id = "turtle1";
    //  坐标系偏移量设置
    ts.transform.translation.x = pose->x;
    ts.transform.translation.y = pose->y;
    ts.transform.translation.z = 0.0;
    // 四元数
    // pose中的theta即为偏航角度，因乌龟为2D
    tf2::Quaternion qtn;
    qtn.setRPY(0,0,pose->theta);
    ts.transform.rotation.x = qtn.getX();
    ts.transform.rotation.y = qtn.getY();
    ts.transform.rotation.z = qtn.getZ();
    ts.transform.rotation.w = qtn.getW();

    pub.sendTransform(ts);

}

int main(int argc, char *argv[]){
    ros::init(argc,argv,"dynamic_pub");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/turtle1/pose",100,doPose);
    ros::spin();
    return 0;
}