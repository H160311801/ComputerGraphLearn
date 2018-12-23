#pragma once

#include <chrono>
#include <iostream>

using namespace std::chrono;

namespace MyTimeCount {
	typedef system_clock sc;
	void countTime(bool reportTimeCost) {
		//should be used with paired arg true and false
		static sc::time_point before_time;
		if (reportTimeCost) {
			sc::duration cost_time = sc::now() - before_time;
			std::cout << "cost time:" 
				<< double(cost_time.count()) * sc::period::num / sc::period::den 
				<< " seconds." << std::endl;
		}
		else {
			before_time = sc::now();
		}
	}
}
