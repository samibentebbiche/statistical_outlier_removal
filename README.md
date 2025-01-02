# Statistical Outlier Removal (SOR) Filter

This repository demonstrates the use of the **Statistical Outlier Removal** filter with the Point Cloud Library (PCL) to clean noisy point clouds. The SOR filter removes outliers by analyzing the distribution of point distances to their neighbors and filtering out points that deviate significantly from the mean distance.

## Build
```
  mkdir build
  cd build
  cmake ..
  make
```
