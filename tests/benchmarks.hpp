#ifndef BENCHMARKS_HPP
# define BENCHMARKS_HPP

#include <ctime>
#include <sys/time.h>

#define MAXRAM (std::numeric_limits<int>::max())
#define MAXSIZE ((std::size_t)MAXRAM / sizeof(int))
#define MAXSIZE_MAP ((std::size_t)MAXRAM / 128)


static unsigned long _ratio = 100;

class timer
{
public:
    timer()
    {
    	(void) _ratio;
		reset();
    };

public:
    long get_time()
    {
    	struct timeval now;
    	struct timeval diff;

    	gettimeofday(&now, NULL);
    	timersub(&now, &stamp, &diff);

    	return diff.tv_sec * 1000 + diff.tv_usec / 1000;
    }

    void reset()
    {
    	gettimeofday(&stamp, NULL);
    }

private:
    struct timeval stamp;
};

static timer	t;

//static unsigned long _ratio = 100000;

#endif
