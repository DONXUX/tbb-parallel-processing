#include <iostream>
#include <tbb/task_scheduler_init.h>
using namespace std;
using namespace tbb;

int main(int argc, char* argv[]) {
	int nthread = strtol(argv[0], 0, 0);
	task_scheduler_init init(task_scheduler_init::deferred);
	if (nthread >= 1) {
		cout << "Task �ʱ�ȭ" << endl;
		init.initialize(nthread);
	}

	if (nthread >= 1) 
		init.terminate();

	return 0;
}