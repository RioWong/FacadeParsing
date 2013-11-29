#ifndef PCLIB_H_
#define PCLIB_H

#include "pcl\point_types.h"
#include "pcl\io\pcd_io.h"

#include <iostream>
#include <vector>

typedef pcl::PointXYZ				PointType1;
typedef pcl::PointXYZRGB			PointType2;
typedef pcl::PointCloud<PointType1> CloudType1;
typedef pcl::PointCloud<PointType2> CloudType2;

class pclib
{
public:
	pclib(void);
	~pclib(void);

	// I/O operations
	static bool load_cloudType1_from_pcd(const std::string& filePath, CloudType1::Ptr);
	static bool load_cloudType2_from_pcd(const std::string& filePath, CloudType2::Ptr);
	static bool load_cloudType1_from_txt(const std::string& filePath, CloudType1::Ptr);
	static bool load_cloudType2_from_txt(const std::string& filePath, CloudType2::Ptr);

	//static bool save_pcd(CloudType1::Ptr cloud, const std::string& filePath);
	static bool transfer_txt_to_pcd_type(const std::string& txtPath, const std::string& pcdPath, bool rgb = false); 
	static bool transfer_pcd_to_txt_type(const std::string& pcdPath, const std::string& txtPath, bool rgb = false); 

	// visualization
	static void render_cloudType1(CloudType1::Ptr cloud);
	static void render_cloudType2(CloudType2::Ptr cloud);

	/// filter
	static CloudType1::Ptr my_downsample(CloudType1::Ptr inputCloud,
		double size_x, double size_y, double size_z);

	static CloudType1::Ptr radius_outliers_removal(CloudType1::Ptr inputCloud, 
		double radius, int min_neighbors);

	static CloudType1::Ptr passThrough_filter(
		CloudType1::Ptr inputCloud,		// input cloud
		const std::string& axe,			//  filter field name is which coordinate? can be: "x", "y" or "z"
		double minLimits,				// min range
		double maxLimits,				// max range
		bool inside = true);			// inside or outside a given user range.

	static CloudType1::Ptr statiscal_outlier_removal(
		CloudType1::Ptr inputCloud,
		int num_neighbors,	//  The number of neighbors to analyze for each point
		double stddevmul = 1.0, // all points who have a distance larger than @stddevmul@ standard deviation of the mean distance 
		// to teh query point will be marked as outliers and removed.
		bool inliers = true
		);

	// segmentation
	static CloudType2::Ptr region_growing_segemtation_by_normal(
		CloudType1::Ptr cloud,	// ���� 
		int nKSearch,			// ʹ�ö��ٸ�����㷨����������
		double minClusterSize = 0.001,		// �ָ���ɺ�С�ڶ��ٵľ���Ҫ����������ռcloud�İٷֱȼ��㣩
		double maxClusterSize = 0.2,		// �ָ���ɺ󣬴��ڶ��ٵľ���Ҫ����������ռcloud�İٷֱȼ��㣩
		int nNeighbors = 30,					// ��������ʱ�����Ƕ��ٸ��ھӣ�

		// ����������ĽǶ��ݲ��λΪ���ȣ�
		double smoothnessThreshold = (7.0 / 180.0 * M_PI), 
		// �������֮��������ĽǶȲ�С���ݲ��Ҫ�Ƚ����ʵĲ���
		double curvatureThreshold = 1.0
		);


	static CloudType1::Ptr random_sample_consensus(CloudType1::Ptr cloud_in, 
		double distanceThreshold, int maxIters, double probility);
};

#endif // PCLIB_H