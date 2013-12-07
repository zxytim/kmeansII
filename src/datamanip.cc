/*
 * $File: datamanip.cc
 * $Date: Sun Sep 08 16:43:31 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "datamanip.hh"

#include "common.hh"

#include <cstdio>
#include <cstdlib>

using namespace std;

static const int BUF_SIZE = 65536;

void read_svm_data(const char *fpath, Dataset &dataset, Labels &labels) {
	FILE *fin = fopen(fpath, "r");
	dataset.resize(0);
	labels.resize(0);

	char *buf = new char[BUF_SIZE];
	while (fgets(buf, BUF_SIZE, fin) == buf) {
		Instance x;
		char *ptr;
		for (ptr = buf; *ptr; ptr ++) {
			if (*ptr == ' ' || *ptr == '\n' || *ptr == '\r') {
				*ptr = 0;
				int label = atoi(buf);
				/*
				if (label != 0 && label != 1) {
					printf("!!!!%d\n", label);
				}
				*/
				labels.push_back(label);
				*ptr = ' ';
				break;
			}
		}
		char *last = ptr;
		int ind = -1;
		double val;
		for (; ; ptr ++) {
			if (*ptr == ' ' || *ptr == '\n' || *ptr == '\r' || *ptr == 0) {
				if (ind != -1) {
					char orig = *ptr;
					*ptr = 0;
					val = atof(last);
					x.push_back(make_pair(ind, val));
					*ptr = orig;
					ind = -1;
				}
				last = ptr + 1;
			} else if (*ptr == ':') {
				*ptr = 0;
				ind = atoi(last);
				last = ptr + 1;
				*ptr = ':';
			}
			if (*ptr == 0)
				break;
		}
		dataset.push_back(x);
	}
	fclose(fin);
}

void print_instance(FILE *fout, const Instance &instance) {
	for (auto item: instance)
		fprintf(fout, "%d:%lf ", item.first, item.second);
}

void print_data(FILE *fout, const Dataset &dataset) {
	for (auto instance: dataset) {
		print_instance(fout, instance);
		fprintf(fout, "\n");
	}
}

void print_data(FILE *fout, const Dataset &dataset, const Labels &labels) {
	assert(dataset.size() == labels.size());
	For(i, dataset.size()) {
		fprintf(fout, "%d ", labels[i]);
		print_instance(fout, dataset[i]);
		fprintf(fout, "\n");
	}
}

void print_data(FILE *fout, const Dataset &dataset, const RealLabels &labels) {
	assert(dataset.size() == labels.size());
	For(i, dataset.size()) {
		fprintf(fout, "%f ", labels[i]);
		print_instance(fout, dataset[i]);
		fprintf(fout, "\n");
	}
}

void print_labels(FILE *fout, const Labels &labels) {
	for (auto i: labels)
		fprintf(fout, "%d\n", i);
}

void print_labels(FILE *fout, const RealLabels &labels) {
	for (auto i: labels)
		fprintf(fout, "%f\n", i);
}


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

