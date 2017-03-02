/*******************************************************************
*Name: Brett Bushnell
*File: checkValuesTest.cpp
*Description: This file contains test for the move library which
*contain functions to check the speed, angle, etc.
*Email: bbushnell@email.arizona.edu
*******************************************************************/
#include <gtest/gtest.h>
#include "hw02bushnell/move.h"
//#include "my_gtest/my_multiply.h"
#include <ros/ros.h>



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




int main(int argc, char** argv){
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "check_values_test");
  return RUN_ALL_TESTS();

}
