#include "hw02bushnell/move.h"
#include <math.h>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"




/*One issue is the car flips, so I'm guessing speed is too high. Set to be constant and check if withing allowed limit*/


double checkSpeed(double speed){
	if(speed > 4.0){
		ROS_INFO("Input speed exceeds max speed of 3. Setting Speed to 3");
		return 4.0; //we will set this as the max speeds
	}
	else if (speed < 0.0){
		ROS_INFO("Speed cannot be negative, setting to 0");
		return 0.0;
	}
	else{
		return speed;
	}
}






