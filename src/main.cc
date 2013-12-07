/*
 * $File: main.cc
 * $Date: Mon Sep 09 16:16:11 2013 +0000
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include <cstdio>
#include "kmeans.hh"
#include "kmeans++.hh"
#include "kmeansII.hh"

#include "datamanip.hh"
#include "common.hh"

#include "tclap/CmdLine.h"

using namespace std;
using namespace TCLAP;

struct Args {
	string algorithm; // kmeans kmeans++ kmeansII
	int concurrency;
	int K;
	int repetition;

	double oversampling_factor;
	double sampling_size_factor;

	string input_file;
	string output_file;
};

Args parse_args(int argc, char *argv[]) {
	Args args;
	try {
		CmdLine cmd("kmeans clustering", ' ', "0.0.1");

		ValueArg<string> arg_algorithm("a", "algorithm", "algorithm to use, either kmeans(0), kmeans++(1) or kmeansII(2)", true, "kmeans", "STRING or NUMBER");
		ValueArg<int> arg_concurrency("w", "concurrency", "number of workers", false, 1, "NUMBER");
		ValueArg<int> arg_K("k", "K", "number of clusters", true, 10, "NUMBER");
		ValueArg<int> arg_repetition("r", "repetition", "times of repeating clustering", false, 1, "NUMBER");
		ValueArg<double> arg_oversampling_factor("f", "oversampling-factor", "oversampling factor, used by KMeansII", false, 0.5, "FLOAT");
		ValueArg<double> arg_sampling_size_factor("s", "sampling-size-factor", "sampling size factor, used by KMeansII, see comments in source code for detail", false, 10, "FLOAT");
		ValueArg<string> arg_input_file("i", "input", "intput file", true, "", "FILE");
		ValueArg<string> arg_output_file("o", "output", "intput file", true, "", "FILE");

		cmd.add(arg_algorithm);
		cmd.add(arg_concurrency);
		cmd.add(arg_K);
		cmd.add(arg_repetition);
		cmd.add(arg_oversampling_factor);
		cmd.add(arg_sampling_size_factor);
		cmd.add(arg_input_file);
		cmd.add(arg_output_file);

		cmd.parse(argc, argv);

#define GET_VALUE(name) args.name = arg_##name.getValue();
		GET_VALUE(algorithm);
		GET_VALUE(concurrency);
		GET_VALUE(K);
		GET_VALUE(repetition);
		GET_VALUE(oversampling_factor);
		GET_VALUE(sampling_size_factor);
		GET_VALUE(input_file);
		GET_VALUE(output_file);

	} catch (ArgException &e) {
		cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
	}
	return args;
}

KMeansSolver *kmeans_factory(const Args &args) {
	if (args.algorithm == "0" || args.algorithm == "kmeans") {
		return new KMeansSolver(args.concurrency);
	} else if (args.algorithm == "1" || args.algorithm == "kmeans++") {
		return new KMeansppSolver(args.concurrency);
	} else if (args.algorithm == "2" || args.algorithm == "kmeansII") {
		return new KMeansIISolver(args.concurrency, args.oversampling_factor, args.sampling_size_factor);
	} else {
		return NULL;
	}
}
int main(int argc, char *argv[]) {
	srand(42); // Answer to The Ultimate Question of Life, the Universe, and Everything
	Args args = parse_args(argc, argv);

	Dataset dataset;
	Labels labels; // dummy
	read_svm_data(args.input_file.c_str(), dataset, labels);

	KMeansSolver *kmeans_solver = kmeans_factory(args);
	vector<Vector> centroids;
	real_t min_cost = numeric_limits<real_t>::max();
	for (int i = 0; i < args.repetition; i ++) {
		vector<Vector> centroids_buf;
		real_t cost = kmeans_solver->cluster(dataset, centroids_buf, args.K);
		if (cost < min_cost) {
			min_cost = cost;
			centroids = centroids_buf;
		}
		printf("repetition %d: ", i);
		printf("cost: %f min_cost: %f\n", cost, min_cost);
	}

	FILE *fout = fopen(args.output_file.c_str(), "w");
	for (auto &point: centroids) {
		for (auto &coord: point)
			fprintf(fout, "%f ", coord);
		fprintf(fout, "\n");
	}
	fclose(fout);
	return 0;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

