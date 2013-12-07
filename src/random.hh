/*
 * $File: random.hh
 * $Date: Mon Aug 19 20:32:04 2013 +0000
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include <cstdlib>

class Random {
	public:
		unsigned short seed[3];
		Random() {
			seed[0] = seed[1] = seed[2] = rand();
		}

		int randint() {
			return nrand48(seed);
		}

		int randint(int val_max) {
			return random() * val_max;
		}

		int randrange(int lo, int hi) {
			return lo + randint(hi - lo + 1);
		}

		double random() {
			return erand48(seed);
		}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

