/*
    boost::filesystem::remove does not throw on missing file.
    Same for std::filesystem: If p did not exist, this function returns false and does not report an error. 
    However underlying OS ::unlink() and ::remove() return -1.
*/

#include <iostream>
#include <filesystem>
#define BOOST_LOG_DYN_LINK 1
#include <boost/filesystem.hpp>

#include <errno.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    /* Remove twice just in case it existed before test. */
    boost::filesystem::remove("/tmp/test_file.txt");
    /* Second remove - no throw */
    boost::filesystem::remove("/tmp/test_file.txt");

    /* c++ library also does not throw */
    std::filesystem::remove("/tmp/test_file.txt");

    std::cout << "unlink: " << ::unlink("/tmp/test_file.txt") << ": " << ::strerror(errno) << std::endl;
    std::cout << "remove: " << ::remove("/tmp/test_file.txt") << ": " << ::strerror(errno) << std::endl;

    return 0;
}
