#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>

#define KEYCODE_R 0x43 
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_Q 0x71
#define KEYCODE_0 0x30

class TeleopTurtle
{
public:
  TeleopTurtle();
  void keyLoop();

private:

  
  ros::NodeHandle nh_;
  double linear_, angular_, l_scale_, a_scale_;
  ros::Publisher twist_pub_;
  
};

TeleopTurtle::TeleopTurtle():
  linear_(0),
  angular_(0),
  l_scale_(2.0),
  a_scale_(2.0)
{
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

  twist_pub_ = nh_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
}

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_turtle");
  TeleopTurtle teleop_turtle;

  signal(SIGINT,quit);

  teleop_turtle.keyLoop();
  
  return(0);
}


void TeleopTurtle::keyLoop()
{
  geometry_msgs::Twist twist;
  ros::Rate loop_rate(5);

  // get the console in raw mode                                                              
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  raw.c_cc[VTIME] = 0;
  raw.c_cc[VMIN] =  0;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use arrow keys to move the turtle.");


  while(ros::ok())
  {
    // get the next event from the keyboard  
      char c;
    int readRtrn = read(kfd, &c, 1);
    if(readRtrn < 0)
    {
      perror("read():");
    }
    else if (readRtrn == 1)
    {

        ROS_DEBUG("value: 0x%02X %d\n", c, readRtrn);

        switch(c)
        {
          case KEYCODE_L:
            ROS_DEBUG("LEFT");
            angular_++;//_ = 1.0;
            break;
          case KEYCODE_R:
            ROS_DEBUG("RIGHT");
            angular_--;// = -1.0;
            break;
          case KEYCODE_U:
            ROS_DEBUG("UP");
            linear_++;// = 1.0;
            break;
          case KEYCODE_D:
            ROS_DEBUG("DOWN");
            linear_--;// = -1.0;
            break;
          case KEYCODE_0:
            ROS_DEBUG("ZERO'd");
            linear_ = 0.0;
            angular_ = 0.0;
            break;
        }
    }
   

    twist.angular.z = a_scale_*angular_;
    twist.linear.x = l_scale_*linear_;
//    ROS_INFO("sending scaling %f %f", twist.angular.z, twist.linear.x);

    twist_pub_.publish(twist);
    ros::spinOnce();
    loop_rate.sleep();
  }


  return;
}



