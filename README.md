# Overview
This package is an extension of HW01 and HW02. It incorporates rostests, and fixes some bugs while moving the catvehicle.

## Limitations
Although the car is now moving safely and in a circular pattern, it will not make a perfect spiral, as well as the tire angles always being max 

## Goals
The goal of this package is to meet the requirements set forth in the HW03 pdf for ECE473: Software Engineering Concepts at the University of Arizona

# Installation
To install, place this package into the catkin workspace that also has the catvehicle package in it. Then in command prompt, change directories to the workspace. i.e. $cd nameOfDirectory
Then, run catkin_make to build the packages. i.e. $catkin_make
This will build the packages and then you are ready to go. 

## Tutorial
To run the check_values_test.test rostest:
	1. $source devel/setup.bash
	2. $rostest hw02bushnell check_values_test.test
-OR-
	1. $source devel/setup.bash
	2. catkin_make run_tests
	
	
## Conclusions 
There are many things that go into making the catvehicle move int he way you want it, and simply just moving code over that worked on one system will not neceesary
work on another.

# About
hw02bushnell is a fullfillment of HW02 and HW03 for ECE473. There are three launch files in the launch folder, turtleSpiral.launch, remap_turtle.launch, and part3.launch.
These can be run using roslaunch. There is one test file check_values_test.test, this can be run with either rostest or catkin_make run_tests commands. 

# Video
https://youtu.be/nLNBBErl7jc

# License
The BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted 
provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions 
  and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of 
  conditions and the following disclaimer in the documentation and/or other materials provided 
  with the distribution.

# Authors
Brett Bushnell <bbushnell@email.arizona.edu>
