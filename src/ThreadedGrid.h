#ifndef _THREADGRID_H_
#define _THREADGRID_H_

#include "NumberGrid.h"
#include <vector>
#include <mutex>
#include <thread>

class SingleTask {
public:
	SingleTask();
	SingleTask(const int& row, const int& column);
	int getRow();
	int getColumn();
private:
	int mRow;
	int mColumn;
};

class ThreadedGrid : public NumberGrid {
public:
	ThreadedGrid();
	ThreadedGrid(const int& height, const int& width);
	virtual ~ThreadedGrid();
	virtual void calculateAllNumbers();
	virtual void worker();

private:
	std::vector<SingleTask> mTasks;
	std::mutex mLock;
};


#endif /* _THREADEDGRID_H_ */
/* Local Variables: */
/* mode:c++ 	    */
/* End:		    */
