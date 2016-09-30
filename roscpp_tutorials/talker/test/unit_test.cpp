#include <gtest/gtest.h>
#include "ros/ros.h"
#include <ros/package.h>

int g_argc;
char** g_argv;


TEST(LoadCalibration, CalibrationSuccessfullyRead)
{
  ros::NodeHandle nh;
  //TODO TestNode is an possible class from a library to handle the details of this node.
  //TestNode tstNode(boost::make_shared<ros::NodeHandle>(nh), "test");


//  EXPECT_TRUE(blah);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
