#include "ros/ros.h"
#include "efficiency_tests/custom_msg.h"

int message_counter = 0, publish_rate_old = 0;
std::int32_t publish_rate;
void callback(const efficiency_tests::custom_msg::ConstPtr& msg)
{
  ros::param::param<std::int32_t>("/rate_value", publish_rate, 1);
  if(publish_rate != publish_rate_old)  // If changed
  {
    publish_rate_old = publish_rate;
    message_counter = 0;
  }

  if(msg->data.length() > 0)
  {
    //Means, data is not empty
    message_counter++;
    ROS_INFO("Message Count : %d" , message_counter);
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subscriber_cpp_node");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("topic", 1000, callback);
  ros::spin();

  return 0;
}