# CMake generated Testfile for 
# Source directory: /Users/ntoniolo/base/scop/cJSON
# Build directory: /Users/ntoniolo/base/scop/cJSON/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "/Users/ntoniolo/base/scop/cJSON/build/cJSON_test")
subdirs("tests")
subdirs("fuzzing")
