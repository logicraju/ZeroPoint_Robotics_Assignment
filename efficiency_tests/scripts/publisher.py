#!/usr/bin/env python
import time
import rospy
from efficiency_tests.msg import SuperMessage


def publisher():
    pub = rospy.Publisher('topic', SuperMessage, queue_size=10)
    rospy.init_node('publisher_python_node')
    start_time = rospy.get_rostime()
    publish_rate_old = 0
    time_threshold = rospy.get_param("/time_threshold", 10)  # seconds

    while not rospy.is_shutdown():
        publish_rate = rospy.get_param("/rate_value", 10)
        # To Detect if Publish Rate has been changed in the Parameter Server externally
        if(publish_rate != publish_rate_old):  # If changed
            publish_rate_old = publish_rate
            start_time = rospy.get_rostime()
            message_counter = 0
            time_diff = 0

        # Publish messages for 10 seconds (10**9 means converting to nano seconds)
        if(int(str(time_diff)) <= time_threshold * 10**9):
            rate = rospy.Rate(publish_rate)
            current_time = rospy.get_rostime()
            time_diff = current_time - start_time
            message_counter = message_counter+1
            print("Message Count : " + str(message_counter) +
                  " Time Diff: " + str(time_diff))
            msg = SuperMessage()
            msg.data = ' '
            pub.publish(msg)
            rate.sleep()
        else:
            time.sleep(10)


if __name__ == '__main__':
    try:
        publisher()
    except rospy.ROSInterruptException:
        pass
