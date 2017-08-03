#include "camera_robot_calibration/camera_robot_calibration.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "camera_robot_calibration_node");
    ros::NodeHandle n;

    camera_robot_calibration::CALIBRATOR::Ptr my_calibrator;
    my_calibrator.reset(new camera_robot_calibration::CALIBRATOR);

    while(ros::ok() &&
          my_calibrator->get_global_parameters().get_number_of_validated_points() <
          my_calibrator->get_global_parameters().get_number_of_points()){

        ROS_WARN("TEST: Inside the while loop!!");
        ros::spinOnce();
        my_calibrator->acquire_points();

        ROS_INFO("press ENTER for next point ...");
        std::cin.ignore();
    }

    bool result = my_calibrator->solve_for_transformation_matrix();
    if(result){
        ROS_INFO_STREAM("Position is: " << my_calibrator->get_global_parameters().get_transformation_position());
        ROS_INFO_STREAM("Quaternion angles are: " << my_calibrator->get_global_parameters().get_transformation_quaternion_vector());
        ROS_WARN("*************************************");
        ROS_INFO_STREAM("RPY angles are: " << my_calibrator->get_global_parameters().get_transformation_RPY());
        ROS_WARN("*************************************");

        Eigen::Matrix4d trans_matrix = my_calibrator->get_global_parameters().get_transformation_matrix();

        ROS_INFO_STREAM("Transformation matrix is: " << "\n" <<
                        trans_matrix(0, 0) << ", " << trans_matrix(0, 1) << ", " << trans_matrix(0, 2) << ", " << trans_matrix(0, 3) << ",\n " <<
                        trans_matrix(1, 0) << ", " << trans_matrix(1, 1) << ", " << trans_matrix(1, 2) << ", " << trans_matrix(1, 3) << ",\n " <<
                        trans_matrix(2, 0) << ", " << trans_matrix(2, 1) << ", " << trans_matrix(2, 2) << ", " << trans_matrix(2, 3) << ",\n " <<
                        trans_matrix(3, 0) << ", " << trans_matrix(3, 1) << ", " << trans_matrix(3, 2) << ", " << trans_matrix(3, 3));
        ROS_WARN("*************************************");
        return 0;
    }
    else
        ROS_WARN("No calibration results, redo it please !!");
    return 0;
}
