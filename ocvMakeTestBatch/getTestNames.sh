./opencv_perf_calib3d --gtest_list_tests --gtest_filter=*OCL* | grep OCL_ > perf_calib3d.txt
./opencv_perf_core --gtest_list_tests --gtest_filter=*OCL* | grep OCL_ > perf_core.txt
./opencv_perf_imgproc --gtest_list_tests --gtest_filter=*OCL* | grep OCL_ > perf_imgproc.txt
./opencv_perf_stitching --gtest_list_tests --gtest_filter=*OCL* | grep OCL_ > perf_stitching.txt


./opencv_test_calib3d --gtest_list_tests --gtest_filter=*OCL* | grep OCL_ > test_calib3d.txt
./opencv_test_core --gtest_list_tests --gtest_filter=*OCL* | grep OCL_ > test_core.txt
./opencv_test_imgproc --gtest_list_tests --gtest_filter=*OCL* | grep OCL_ > test_imgproc.txt
./opencv_test_stitching --gtest_list_tests --gtest_filter=*OCL* | grep OCL_ > test_stitching.txt
