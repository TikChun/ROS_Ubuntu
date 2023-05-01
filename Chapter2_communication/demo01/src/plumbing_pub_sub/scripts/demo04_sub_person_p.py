#! /usr/bin/env python
import rospy
from plumbing_pub_sub.msg import Person
# same as in cpp

def Doperson(p):
    rospy.loginfo("Received: %s, %d, %.2f",p.name,p.age,p.height)

if __name__=="__main__":
    rospy.init_node("Li")
    sub = rospy.Subscriber("chat",Person,Doperson,queue_size=10)
    rospy.spin()
