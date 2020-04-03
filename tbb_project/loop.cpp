#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <iostream>
#include <time.h>
using namespace std;
using namespace tbb;

float f[100000];

void Foo(float a) {
	cout << a << endl;
}

class ApplyFoo {
	float* const my_a;
public:
	void operator()(const blocked_range<size_t>& r) const {
		float* a = my_a;
		for (size_t i = r.begin(); i != r.end(); ++i)
			Foo(a[i]);
	}

	ApplyFoo(float a[]) :
		my_a(a)
	{}
};

void SerialApplyFoo(float a[], size_t n) {
	for (size_t i = 0; i < n; ++i) {
		Foo(a[i]);
	}
}

void ParallelApplyFoo(float a[], size_t n) {
	parallel_for(blocked_range<size_t>(0, n, 12500), ApplyFoo(a));
}

int main(void) {
	time_t s_start, s_end, p_start, p_end;
	double s_result, p_result;
	for (int i = 0; i < 100000; i++) 
		f[i] = i;

	s_start = time(NULL);
	SerialApplyFoo(f, 100000);
	s_end = time(NULL);
	s_result = (double)(s_end - s_start);

	p_start = time(NULL);
	ParallelApplyFoo(f, 100000);
	p_end = time(NULL);
	p_result = (double)(p_end - p_start);

	cout << "일반시간 : " << s_result << "s" << endl;
	cout << "병렬시간 : " << p_result << "s" << endl;
	return 0;
}