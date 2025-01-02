#include <iostream>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/visualization/pcl_visualizer.h>

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

int main(int argc, char* argv[])
{
  PointCloudT::Ptr cloud(new PointCloudT);
  PointCloudT::Ptr cloud_filtered(new PointCloudT);

  if(argc < 2)
     {
         PCL_ERROR("The file.ply is missing : Provide one ply file.\n!");
         return(-1);
     }


  if (pcl::io::loadPLYFile(argv[1], *cloud) < 0)
  {
    PCL_ERROR("Error loading cloud %s.\n", argv[1]);
    return(-1);
  }
  std::cerr << "Cloud before filtering: " << std::endl;
  std::cerr << *cloud << std::endl;

  // Create the filtering object
  pcl::StatisticalOutlierRemoval<PointT> sor;
  sor.setInputCloud(cloud);
  //The number of neighbors to analyze for each point is set to 50
  sor.setMeanK(50);
  //Points who have a distance larger than 1 standard deviation of the mean distance to the point will be removed
  sor.setStddevMulThresh(1.0);

  sor.filter(*cloud_filtered);
  std::cerr << "Cloud after filtering: " << std::endl;
  std::cerr << *cloud_filtered << std::endl;

/*
  pcl::PCDWriter writer;
  writer.write<pcl::PointXYZ> ("table_scene_lms400_inliers.pcd", *cloud_filtered, false);
*/
  // Visualization
  pcl::visualization::PCLVisualizer viewer("Outlier Removal demo");


  // The color we will be using
  float bckgr_gray_level = 0.0;  // Black
  float txt_gray_lvl = 1.0 - bckgr_gray_level;

 // Visualization
  pcl::visualization::PointCloudColorHandlerCustom<PointT> cloud_in_color_h1( cloud_filtered, (int)255*txt_gray_lvl,
                                            (int)255*txt_gray_lvl, (int)255*txt_gray_lvl);
  viewer.addPointCloud(cloud_filtered, cloud_in_color_h1, "Points Clouds 1");


  sor.setNegative (true);
  sor.filter (*cloud_filtered);
/*
  writer.write<pcl::PointXYZ> ("table_scene_lms400_outliers.pcd", *cloud_filtered, false);
*/
  pcl::visualization::PointCloudColorHandlerCustom<PointT> cloud_in_color_h2( cloud_filtered, (int)255*txt_gray_lvl,
                                            (int)0, (int)0);
  viewer.addPointCloud(cloud_filtered, cloud_in_color_h2, "Points Clouds 2");

  // Set the point size
  viewer.setPointCloudRenderingProperties(
      pcl::visualization::PCL_VISUALIZER_POINT_SIZE,
      3, // Point size
      "Points Clouds 2"
  );
  // Set background color
  viewer.setBackgroundColor(bckgr_gray_level, bckgr_gray_level, bckgr_gray_level);

  // Set camera position and orientation
  viewer.setCameraPosition(-3.68332, 2.94092, 5.71266, 0.289847, 0.921947, -0.256907, 0);
  viewer.setSize(1280, 1024);  // Visualiser window size

  while(!viewer.wasStopped())
    {
      viewer.spinOnce();
    }
  return (0);

}
