#include <iostream>
#include <atomic>

#include <boost/thread.hpp>
#include <boost/timer.hpp>


namespace boost_mutex_vs_atomic {
    class bench_boost_mutex {
        size_t x;
        size_t iteration_count;
        boost::thread_group threads;
        mutable boost::mutex wait;
        boost::timer timer;


        public:
            bench_boost_mutex(size_t thread_count,
                              size_t iteration_count)
                : x(0)
                , iteration_count(0) {
                this->iteration_count = iteration_count;
                for (size_t i = 0; i < thread_count; ++i) {
				    threads.create_thread( boost::bind(&bench_boost_mutex::do_test, this) );
                }
            }

            void do_test() {
                for(size_t i = 0; i < iteration_count; ++i) { 
                    {
                        boost::mutex::scoped_lock lock(wait);
                        ++x;
                    }
                }
            }
            ~bench_boost_mutex() {
			    threads.join_all();
                std::cerr << "bench_boost_mutex: x = " << x << ", elapsed time is " << timer.elapsed()
                          << "\n";
		    }
    };

    class bench_no_lock {
        size_t x;
        size_t iteration_count;
        boost::thread_group threads;
        boost::timer timer;


        public:
            bench_no_lock(size_t thread_count,
                              size_t iteration_count)
                : x(0)
                , iteration_count(0) {
                this->iteration_count = iteration_count;
                for (size_t i = 0; i < thread_count; ++i) {
				    threads.create_thread( boost::bind(&bench_no_lock::do_test, this) );
                }
            }

            void do_test() {
                for(size_t i = 0; i < iteration_count; ++i) { 
                    ++x;
                }
            }
            ~bench_no_lock() {
			    threads.join_all();
                std::cerr << "bench_no_lock: x = " << x << ", elapsed time is " << timer.elapsed()
                          << "\n";
		    }
    };

    class bench_atomic {
        std::atomic_size_t x;
        size_t iteration_count;
        boost::thread_group threads;
        boost::timer timer;


        public:
            bench_atomic(size_t thread_count,
                              size_t iteration_count)
                : x(0)
                , iteration_count(0) {
                this->iteration_count = iteration_count;
                for (size_t i = 0; i < thread_count; ++i) {
				    threads.create_thread( boost::bind(&bench_atomic::do_test, this) );
                }
            }

            void do_test() {
                for(size_t i = 0; i < iteration_count; ++i) { 
                    ++x;
                }
            }
            ~bench_atomic() {
			    threads.join_all();
                std::cerr << "bench_atomic: x = " << x << ", elapsed time is " << timer.elapsed()
                          << "\n";
		    }
    };

}


int main() {
    const size_t thread_count = 4;
    const size_t iteration_count = 10000000;

    {
        boost_mutex_vs_atomic::bench_boost_mutex bench(thread_count, iteration_count);
    }
    {
        boost_mutex_vs_atomic::bench_atomic bench(thread_count, iteration_count);
    }
    {
        boost_mutex_vs_atomic::bench_no_lock bench(thread_count, iteration_count);
    }
    return 0;
}
