#include <camera_robot_calibration.hpp>
#include <crustcrawler_mover_utils/crustcrawler_mover_utils/crustcrawler_mover.hpp>
//#include <camera_robot_calibration/camera_robot_calibration.hpp>
//#include <crustcrawler_mover_utils/crustcrawler_mover.hpp>
#include <moveit/move_group_interface/move_group.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "automatic_calibration_test_node");
    ros::NodeHandle n;

    crustcrawler_mover::CRUSTCRAWLER_Mover::Ptr _crustcrawler_mover;
    _crustcrawler_mover.reset(new crustcrawler_mover::CRUSTCRAWLER_Mover(n));

    double  x_min = 0.0, x_max = 0.4,
            y_min = -0.4, y_max = 0.4,
            z_min = 0.0, z_max = 0.6;

    geometry_msgs::Pose target;
    target.orientation.w = 0.8;
    target.orientation.x = 0.0;
    target.orientation.y = 0.6;
    target.orientation.z = 0.0;

    tf::Quaternion _q;
    geometry_msgs::PoseStamped front_pose;
    front_pose.header.frame_id = "base";
    front_pose.header.stamp = ros::Time::now();

    front_pose.pose.position.x = 0.2;
    front_pose.pose.position.y = 0.0;
    front_pose.pose.position.z = 0.0;
    _q.setEuler(0.0, 0.0, M_PI/2);
    front_pose.pose.orientation.w = _q.getW();
    front_pose.pose.orientation.x = _q.getX();
    front_pose.pose.orientation.y = _q.getY();
    front_pose.pose.orientation.z = _q.getZ();

    _crustcrawler_mover->add_world_object("front_table", front_pose, {0.5, 1.5, 0.01});

    geometry_msgs::PoseStamped back_pose;
    back_pose.header.frame_id = "base";
    back_pose.header.stamp = ros::Time::now();

    back_pose.pose.position.x = -0.1;
    back_pose.pose.position.y = 0.0;
    back_pose.pose.position.z = 0.5;
    _q.setEuler(0.0, 0.0, M_PI/2);
    back_pose.pose.orientation.w = _q.getW();
    back_pose.pose.orientation.x = _q.getX();
    back_pose.pose.orientation.y = _q.getY();
    back_pose.pose.orientation.z = _q.getZ();

    _crustcrawler_mover->add_world_object("back_wall", back_pose, {0.01, 1.5, 1.0});

    ROS_INFO("press ENTER to go to the calibration ...");
    std::cin.ignore();
    ros::Rate my_rate(1);

    while(ros::ok() ){
        ROS_WARN("TEST: Inside the while loop!!");
        ros::spinOnce();
        bool found_plan = false;
        moveit::planning_interface::MoveGroup::Plan the_plan;
        while(!found_plan){
            target.position.x = (x_max - x_min) * (double)rand() / RAND_MAX + x_min;
            target.position.y = (y_max - y_min) * (double)rand() / RAND_MAX + y_min;
            target.position.z = (z_max - z_min) * (double)rand() / RAND_MAX + z_min;

            _crustcrawler_mover->group->setPoseTarget(target);
            if(_crustcrawler_mover->group->plan(the_plan)){
                _crustcrawler_mover->group->execute(the_plan);
                found_plan = true;
            }

        }
        my_rate.sleep();
        ROS_INFO("press ENTER for next point ...");
        std::cin.ignore();
    }
    return 0;
}
