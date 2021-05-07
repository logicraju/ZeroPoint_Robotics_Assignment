#!/usr/bin/env python
import rospy
from efficiency_tests.msg import SuperMessage

publish_rate_old = 0
message_counter = 0


def callback(data):
    global publish_rate_old, message_counter, start_time
    publish_rate = rospy.get_param("/rate_value", 10)
    if(publish_rate != publish_rate_old):  # If changed
            publish_rate_old = publish_rate
            message_counter = 0

    if(len(data.data) != 0):
        message_counter = message_counter+1
        current_time = rospy.get_rostime()
        print("Message Count : " + str(message_counter))


def listener():
    rospy.init_node('subscriber_python_node')
    rospy.Subscriber("topic", SuperMessage, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
