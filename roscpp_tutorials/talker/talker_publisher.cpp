#include "ros/ros.h"
#include <sstream>
#include "std_msgs/String.h"

//publisher
void talkPublish(int count, boost::shared_ptr<ros::Publisher> ch_pub_ptr)
{
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
// %Tag(FILL_MESSAGE)%
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();
// %EndTag(FILL_MESSAGE)%

// %Tag(ROSCONSOLE)%
    ROS_INFO("%s", msg.data.c_str());
// %EndTag(ROSCONSOLE)%

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
// %Tag(PUBLISH)%
    ch_pub_ptr->publish(msg);
// %EndTag(PUBLISH)%

}
