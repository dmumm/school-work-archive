# CMake generated Testfile for 
# Source directory: /home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyIexTest
# Build directory: /home/dmumm/4040/demo/openexr-2.5.8_build/PyIlmBase/PyIexTest
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(PyIlmBase.PyIexTest_Python2 "/usr/bin/python2.7" "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyIexTest/pyIexTest.in")
set_tests_properties(PyIlmBase.PyIexTest_Python2 PROPERTIES  ENVIRONMENT "PYTHONPATH=/home/dmumm/4040/demo/openexr-2.5.8_build/python2_7" _BACKTRACE_TRIPLES "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyIexTest/CMakeLists.txt;5;add_test;/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyIexTest/CMakeLists.txt;0;")
add_test(PyIlmBase.PyIexTest_Python3 "/usr/bin/python3.8" "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyIexTest/pyIexTest.in")
set_tests_properties(PyIlmBase.PyIexTest_Python3 PROPERTIES  ENVIRONMENT "PYTHONPATH=/home/dmumm/4040/demo/openexr-2.5.8_build/python3_8" _BACKTRACE_TRIPLES "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyIexTest/CMakeLists.txt;14;add_test;/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyIexTest/CMakeLists.txt;0;")
