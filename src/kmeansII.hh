/*
 * $File: kmeansII.hh
 * $Date: Mon Sep 09 13:58:10 2013 +0000
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "dataset.hh"
#include "kmeans.hh"

/**
 * A KMeans++ clustering algorithm
 */
class KMeansIISolver : public KMeansSolver {
	public:
		/**
		 * oversampling factor and number of parallel workers.
		 * see **Scalable K-Means++** for explanation, although the definition
		 * is not quite the same: l_orig = l_here * K
		 *
		 * number of rounds for sampling is not presented here, as
		 * it is substituted by sampling_size_factor, by which means as long as
		 * the number of points sampled is less than size_factor * K,
		 * we'll continue sampling.
		 */
		KMeansIISolver(int concurrency, real_t oversampling_factor = 2.0, real_t sampling_size_factor = 2.0);

		/**
		 * cluster point in dataset into K partitions
		 * situation when K <= dataset.size() should be correctly dealt with
		 */
		virtual real_t cluster(const Dataset &dataset, std::vector<Vector> &centroids, int K);

	protected:
		real_t oversampling_factor,
			   size_factor;

};


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

