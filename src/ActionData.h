#ifndef _ACTIONDATA_H_
#define _ACTIONDATA_H_
#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"
#include "ComplexFractal.h"
#include <iostream>

class ActionData {
public:
	ActionData(std::istream& is, std::ostream& os);
	~ActionData();

	std::istream& getIS();
	std::ostream& getOS();
	PPM& getInputImage1();
	PPM& getInputImage2();
	PPM& getOutputImage();
	bool getDone() const;
	void setDone();
	NumberGrid& getGrid();
	void setGrid(NumberGrid *grid);
	ColorTable& getTable();

private:
	std::istream& mIs;
	std::ostream& mOs;
	PPM mInput_image_1; 
	PPM mInput_image_2; 
	PPM mOutput_image; 
	bool mDone;
	NumberGrid *mGrid;
	ColorTable mTable;
};

#endif /* _ACTIONDATA_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
