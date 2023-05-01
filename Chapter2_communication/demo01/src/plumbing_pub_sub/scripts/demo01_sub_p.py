#!  /user/bin/env pyhton
import rospy
from std_msgs.msg import String
"""
1.  导入包
2.  初始化ros节点
3.  创建订阅者对象
4.  回调函数处理数据
5.  spin()
"""

def doMsg(msg):
    rospy.loginfo("received: %s",msg.data)

if __name__ == "__main__":
    # 2
    rospy.init_node("subscriber")
    # 3
    sub = rospy.Subscriber("car",String,doMsg,queue_size=10)
    # 4
    #5
    rospy.spin()