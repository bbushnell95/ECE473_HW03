/**************************************************************************************************
*Name: Brett Bushnell
*File: move.h
*Description: Heaer file for move function for the to make the turtle in turtlesim move in a spiral
*Email: bbushnell@email.arizona.edu	
***************************************************************************************************/


#ifndef MOVE_H
#define MOVE_H

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"


void move(double speed, double theta, int rate, ros::Publisher velocity_publisher, turtlesim::Pose turtle_position);
double checkSpeed(double speed);

#endif //MOVE_H
