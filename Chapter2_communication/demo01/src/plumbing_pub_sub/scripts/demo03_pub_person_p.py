#! /usr/bin/env python

import rospy
from plumbing_pub_sub.msg import Person
# Same as in cpp

if __name__=="__main__":
    rospy.init_node("uncle")
    pub = rospy.Publisher("chat",Person,queue_size=10)
    p = Person()
    p.name = "Wang"
    p.age = 10
    p.height = 1.85
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        pub.publish(p)
        p.age += 1
        rospy.loginfo("published: %s, %d, %.2f",p.name, p.age, p.height)
        rate.sleep()
