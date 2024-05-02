#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "filters/mean.hpp"

ros::Publisher pub;
geometry_msgs::Twist msg_out;
filters::MultiChannelFilterBase<double> * filter = new filters::MultiChannelMeanFilter<double>();
std::vector<double> input, output{0,0,0,0,0,0};

void fncCallback(const geometry_msgs::Twist::ConstPtr& msg_in)
{
	input.clear();
	input.push_back(msg_in->linear.x);
	input.push_back(msg_in->linear.y);
	input.push_back(msg_in->linear.z);
	input.push_back(msg_in->angular.x);
	input.push_back(msg_in->angular.y);
	input.push_back(msg_in->angular.z);
	
	filter->update(input, output);
	
	msg_out.linear.x = output[0];
	msg_out.linear.y = output[1];
	msg_out.linear.z = output[2];
	msg_out.angular.x = output[3];
	msg_out.angular.y = output[4];
	msg_out.angular.z = output[5];
	pub.publish(msg_out);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Twist_mean_filter_node");
  ros::NodeHandle nh; 

  filter->configure(6,"MultiChannelMeanFilterDouble5");
  
  ros::Subscriber sub = nh.subscribe("twist_in", 1000, fncCallback);
  pub = nh.advertise<geometry_msgs::Twist>("twist_out", 1000);
  
  ROS_INFO("Twist mean filter node is running!"); 
  ros::spin();
}
