#include <gtest/gtest.h>
#include "ros/ros.h"
#include <ros/package.h>

int g_argc;
char** g_argv;

TEST(LoadCalibration, CalibrationSuccessfullyRead)
{
  ros::NodeHandle nh;
  //TODO TestNode is an possible class from a library to handle the details of this node.
//  TestNode tstNode(boost::make_shared<ros::NodeHandle>(nh), "test");


//  EXPECT_TRUE(blah);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);

  // TODO we only need to spin if we actually want to pub/sub. If we just want to run tests on a unit basis,
  // then we can skip this
  g_argc = argc;
  g_argv = argv;
  ros::init(g_argc, g_argv, "test");

  boost::thread spinner(boost::bind(&ros::spin));

  int res = RUN_ALL_TESTS();
  spinner.interrupt();
  spinner.join();

  return res;
}
