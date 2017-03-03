/*******************************************************************
*Name: Brett Bushnell
*File: checkValuesTest.cpp
*Description: This file contains test for the move library which
*contain functions to check the speed, angle, etc.
*Email: bbushnell@email.arizona.edu
*******************************************************************/
#include <gtest/gtest.h>
#include <math.h>
#include "hw02bushnell/move.h"
//#include "my_gtest/my_multiply.h"
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"


class CallbackHandler1
{
public:
  CallbackHandler1()
  : result(0.0)
  { }

  void callback(const geometry_msgs::Twist::ConstPtr& msg)
  {
    result = msg->linear.x;
  }

  double result;

};

class CallbackHandler
{
public:
	CallbackHandler()
	: result(0.0)
	{}
	
	void callback(const turtlesim::Pose::ConstPtr& msg)
	{
		result = msg->linear_velocity;
	}
	
	double result;
};



TEST(NodeCase, CheckCatVehicleLinearVel){
	ros::NodeHandle nh;
	ros::Rate loop_rate(1);
	double result;
	
	CallbackHandler mCallbackHandler;
	//Define the subscriber
	ros::Subscriber result_sub = nh.subscribe("/turtle1/pose", 100, &CallbackHandler::callback, &mCallbackHandler);
	loop_rate.sleep();
	usleep(200000);

	//set param withing allowable limit
	nh.setParam("speed", 0.0);
	EXPECT_EQ(mCallbackHandler.result, 0.0);	

	nh.setParam("speed", 2.0);
	EXPECT_LE(mCallbackHandler.result, 2.0);

	nh.setParam("speed", 4.0);
	EXPECT_LE(mCallbackHandler.result, 4.0);

	//now for over and under the speed
	nh.setParam("speed", -1.0);
	EXPECT_EQ(mCallbackHandler.result, 0.0);

	//over the allowable speed
	nh.setParam("speed", 5.0);
	EXPECT_LE(mCallbackHandler.result, 4.0);

}

TEST(LibraryCase, CheckSpeedTest){
	double result = 0;
	double maxSpeed = 4.0;
	
	//check if speed is equal to zero PASS means result = 0
	result = checkSpeed(0.0);
	EXPECT_EQ(result, 0.0);
	
	//check when speed equal to 1-4 Pass if result = value we pass through
	result = checkSpeed(3.0);
	EXPECT_EQ(result,3.0);

	//If there is a decimal
	result = checkSpeed(2.45);
	EXPECT_EQ(result, 2.45);

	//Check negative number, Pass if result = 0
	result = checkSpeed(-1.0);
	EXPECT_EQ(result, 0.0);

	//Check Speed > 4, Pass if result = 4
	result = checkSpeed(5.0);
	EXPECT_EQ(result, maxSpeed);

	//Some really big number
	result = checkSpeed(100000);
	EXPECT_EQ(result, maxSpeed);
}

TEST(LibraryCase, CheckRTest){
	double x0 = 0;
	double y0 = 0;
	double x1 = 0;
	double y1 = 0;
	double result;
	double expected;
	
	
	//double calculateR(double currentX, double currentY, double initialX, double initialY)
	//when everything is zero
	result = calculateR(x1, y1, x0, y0);
	EXPECT_EQ(result, 0.0);

	//Now some when both x1 and y1 are positive and equal, and x0, y0 = 0
	y1 = 3.0;
	x1 = 3.0;
	
	expected = sqrt(pow(x1 - x0, 2) + pow(y1-y0,2));
	result = calculateR(x1, y1, x0, y0);
	EXPECT_EQ(result, expected);

	//Now whe x1 and y1 are different but positive, x0, y0 still equal to 0
	y1 = 3.0;
	x1 = 9.0;
	
	expected = sqrt(pow(x1 - x0, 2) + pow(y1-y0,2));
	result = calculateR(x1, y1, x0, y0);
	EXPECT_EQ(result, expected);

	//Now x1 and y1 are the same negative number, x0, y1 still 0
	y1 = -3.0;
	x1 = -3.0;
	
	expected = sqrt(pow(x1-x0,2) + pow(y1-y0,2));
	result = calculateR(x1, y1, x0, y0);
	EXPECT_EQ(result, expected);

	//x1 and y1 now different negative numbers, x0, y1 still 0
	y1 = -3.0;
	x1 = -9.0;

	expected = sqrt(pow(x1 - x0, 2) + pow(y1-y0,2));
	result = calculateR(x1,y1, x0, y0);
	EXPECT_EQ(result, expected);

	//x1 is positive, y1 is negative however \x1\ = \y1\, and x0 = y0 = 0
	
	y1 = -3.0;
	x1 = 3.0;
	
	expected = sqrt(pow(x1 - x0, 2) + pow(y1-y0,2));
	result = calculateR(x1,y1, x0, y0);
	EXPECT_EQ(result, expected);

	//x1 is positive, y1 is negative however \x1\ != \y1\ and x0 = y0 = 0
	y1 = -3.0;
	x1 = 9.0;


	expected = sqrt(pow(x1 - x0, 2) + pow(y1-y0,2));
	result = calculateR(x1,y1, x0, y0);
	EXPECT_EQ(result, expected);


/*********************Do all the same tests, but now x0 != y0***************************************/ 

	//Now some when both x1 and y1 are positive and equal
	y1 = 3.0;
	x1 = 3.0;
	y0 = 5.4;
	x0 = 1.2;
	
	expected = sqrt(pow(x1 - x0, 2) + pow(y1-y0,2));
	result = calculateR(x1, y1, x0, y0);
	EXPECT_EQ(result, expected);

	//Now whe x1 and y1 are different but positive
	y1 = 3.0;
	x1 = 9.0;
	
	expected = sqrt(pow(x1 - x0, 2) + pow(y1-y0,2));
	result = calculateR(x1, y1, x0, y0);
	EXPECT_EQ(result, expected);

	//Now x1 and y1 are the same negative number
	y1 = -3.0;
	x1 = -3.0;
	
	expected = sqrt(pow(x1-x0,2) + pow(y1-y0,2));
	result = calculateR(x1, y1, x0, y0);
	EXPECT_EQ(result, expected);

	//x1 and y1 now different negative numbers
	y1 = -3.0;
	x1 = -9.0;

	expected = sqrt(pow(x1 - x0, 2) + pow(y1-y0,2));
	result = calculateR(x1,y1, x0, y0);
	EXPECT_EQ(result, expected);

	//x1 is positive, y1 is negative however \x1\ = \y1\
	
	y1 = -3.0;
	x1 = 3.0;
	
	expected = sqrt(pow(x1 - x0, 2) + pow(y1-y0,2));
	result = calculateR(x1,y1, x0, y0);
	EXPECT_EQ(result, expected);

	//x1 is positive, y1 is negative however \x1\ != \y1\ 
	y1 = -3.0;
	x1 = 9.0;


	expected = sqrt(pow(x1 - x0, 2) + pow(y1-y0,2));
	result = calculateR(x1,y1, x0, y0);
	EXPECT_EQ(result, expected);

}	




int main(int argc, char** argv){
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "check_values_test");

  return RUN_ALL_TESTS();

}
