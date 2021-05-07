#include <math.h>
#include "ros/ros.h"
#include "efficiency_tests/custom_msg.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "publisher_cpp_node");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<efficiency_tests::custom_msg>("topic", 1000);
  std::int32_t publish_rate;

  int message_counter = 0, publish_rate_old = 0;;
  ros::Time start_time = ros::Time::now();
  ros::Time end_time = ros::Time::now();
  ros::Duration time_diff = ros::Duration(0);
  ros::Duration time_threshold = ros::Duration(10);  // 10 seconds

  while (ros::ok())
  {
    ros::param::param<std::int32_t>("/rate_value", publish_rate, 1);
    if (publish_rate != publish_rate_old)  // If changed
    {
      publish_rate_old = publish_rate;
      start_time = ros::Time::now();
      message_counter = 0;
      time_diff = ros::Duration(0);
    }

    if (time_diff <= time_threshold)
    {
      end_time = ros::Time::now();
      time_diff = end_time - start_time;
      ros::Rate loop_rate(publish_rate);
      efficiency_tests::custom_msg msg;
      msg.data = " ";
      pub.publish(msg);
      message_counter++;
      ROS_INFO("Message Count: %d : Time_Diff seconds: %d, and nanoseconds: %d", message_counter, time_diff.sec, time_diff.nsec);
      ros::spinOnce();
      loop_rate.sleep();
    }
    else
    {
      ros::Duration(0.1).sleep();
    }
  }
  return 0;
}