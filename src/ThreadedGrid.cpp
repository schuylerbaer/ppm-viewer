#include "ThreadedGrid.h"

ThreadedGrid::ThreadedGrid() {
}

ThreadedGrid::ThreadedGrid(const int& height, const int& width)
	: NumberGrid(height, width) {
}

ThreadedGrid::~ThreadedGrid() {
}

void ThreadedGrid::calculateAllNumbers() {
	int n_threads = (int)std::thread::hardware_concurrency();
	
	mTasks.resize(getHeight()*getWidth());
	int i = 0;
	int row, column;
	for(row = 0; row < getHeight(); row++) {
		for(column = 0; column < getWidth(); column++) {	
			SingleTask x = SingleTask(row, column);
			mTasks[i] = x;
			i++;
		}
	}

	std::vector<std::thread> threads;
	for(i = 0; i < n_threads; i++) {
		threads.push_back(std::thread(&ThreadedGrid::worker, this));
	}

	for(i = 0; i < n_threads; i++) {
		threads[i].join();
	}
}

void ThreadedGrid::worker() {
	SingleTask y;
	while(mTasks.size() > 0) {
		mLock.lock();
		if(mTasks.size()) {
			y = mTasks.back();
			mTasks.pop_back();
		}
		mLock.unlock();
		setNumber(y.getRow(), y.getColumn(), calculateNumber(y.getRow(), y.getColumn()));
	}
}

SingleTask::SingleTask() {
}

SingleTask::SingleTask(const int& row, const int& column)
	: mRow(row), mColumn(column) {
}

int SingleTask::getRow() {
	return mRow;
}

int SingleTask::getColumn() {
	return mColumn;
}

