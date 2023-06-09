#!  /user/bin/env python

import rospy
from std_msgs.msg import String # 消息类型

"""
1.  导入包
2.  初始化ros节点
3.  创建发布者对象
4.  编写发布逻辑和发布数据
"""


if __name__=="__main__":

    # 2
    rospy.init_node("sender")   # 传入节点名称
    # 3
    pub = rospy.Publisher("car",String,queue_size=10)
    # 4
    msg = String()
    rate = rospy.Rate(1)    # frequency
    count = 0
    rospy.sleep(3)  # avoid package lost at the start
    while not rospy.is_shutdown():
        count += 1
        msg.data = "hello: " + str(count)
        pub.publish(msg)
        rospy.loginfo("published data: %s",msg.data)
        rate.sleep()    
