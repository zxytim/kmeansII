/*
 * $File: kmeans++.hh
 * $Date: Mon Sep 09 13:57:54 2013 +0000
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "dataset.hh"
#include "kmeans.hh"

/**
 * A KMeans++ clustering algorithm
 */
class KMeansppSolver : public KMeansSolver {
	public:
		/**
		 * number of parallel workers.
		 */
		KMeansppSolver(int concurrency);

		/**
		 * cluster point in dataset into K partitions
		 * situation when K <= dataset.size() should be correctly dealt with
		 */
		virtual real_t cluster(const Dataset &dataset, std::vector<Vector> &centroids, int K);
		virtual real_t cluster_weighted(const Dataset &dataset, const std::vector<real_t> &weight,
				std::vector<Vector> &centroids, int K);
		virtual real_t cluster_weighted(const std::vector<Vector> &dataset, const std::vector<real_t> &weight,
				std::vector<Vector> &centroids, int K);

};


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

