#include <iostream>
#include "ActionData.h"
#include "PPM.h"
#include "ColorTable.h"

ActionData::ActionData(  std::istream& is, std::ostream& os  )
        : mIs(is), mOs(os), mDone(false), mGrid(0), mTable(16) {
		mTable.insertGradient(Color(0, 255, 0), Color(255, 0, 255), 0, 15);
}

ActionData::~ActionData() {
	if(mGrid != 0) {
		delete mGrid;
		mGrid = 0;
	}
}

std::istream& ActionData::getIS() {
	return mIs;
}

std::ostream& ActionData::getOS() {
	return mOs;
}

PPM& ActionData::getInputImage1() {
	return mInput_image_1;
}

PPM& ActionData::getInputImage2() {
	return mInput_image_2;
}

PPM& ActionData::getOutputImage() {
	return mOutput_image;
}

bool ActionData::getDone() const {
	return mDone;
}

void ActionData::setDone() {
	mDone = true;
}

NumberGrid& ActionData::getGrid() {
	return *(this->mGrid);
}

void ActionData::setGrid(NumberGrid *grid) {
	if(mGrid != 0) {
		delete mGrid;
		mGrid = 0;
	}
	mGrid = grid;	
}

ColorTable& ActionData::getTable() {
	return mTable;
}

