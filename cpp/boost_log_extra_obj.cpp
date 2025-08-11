/*
 * Boost log does not create extra objects when not necessary, e.g. system log
 * level is greater than log level in message.
 */
#include <iostream>
#define BOOST_LOG_DYN_LINK 1
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>

struct X
{
	X() { std::cout << "Extra object created" << std::endl; }

	operator int() const { return 42; }
};

int
main(int argc, char *argv[])
{
	const boost::log::trivial::severity_level log_level =
	        (argc > 1) ? boost::log::trivial::error
	                   : boost::log::trivial::trace;

	std::cerr << "Using log level " << log_level << std::endl;

	boost::log::core::get()->set_filter(boost::log::trivial::severity >=
	                                    log_level);

	BOOST_LOG_TRIVIAL(debug) << X{};

	return 0;
}
