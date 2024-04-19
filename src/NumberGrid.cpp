#include "NumberGrid.h"
#include "ColorTable.h"

NumberGrid::NumberGrid()
	: mHeight(300), mWidth(400), mMax_value(255) {
	mGrid.resize(mHeight * mWidth, 0);
}

NumberGrid::NumberGrid( const int& height, const int& width )
	: mHeight(height), mWidth(width), mMax_value(255) {
	mGrid.resize(mHeight * mWidth, 0);
}

NumberGrid::~NumberGrid() {
}

int NumberGrid::getHeight( ) const {
	return mHeight;
}

int NumberGrid::getWidth( ) const {
	return mWidth;
}

int NumberGrid::getMaxNumber( ) const {
	return mMax_value;
}

void NumberGrid::setMaxNumber( const int& number ) {
	if(number >= 0) {
		mMax_value = number;
	}
}

const std::vector< int >& NumberGrid::getNumbers( ) const {
	return mGrid;
}

int NumberGrid::index( const int& row, const int& column ) const {
	return (row * mWidth) + column;
}

bool NumberGrid::indexValid( const int& row, const int& column ) const {
	if(row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
		return true;
	}
	else {
		return false;
	}
}

bool NumberGrid::numberValid( const int& number ) const {
	if(number >= 0 && number <= mMax_value) {
		return true;
	}
	return false;
}

int NumberGrid::getNumber( const int& row, const int& column ) const {
	if(indexValid(row, column) == true) {
		int indexx = index(row, column);
		int value = mGrid[indexx];
		return value;
	}
	return -1;
}

void NumberGrid::setNumber( const int& row, const int& column, const int& number ) {
	if(indexValid(row, column) && numberValid(number)) {
		int indexx = index(row, column);
		mGrid[indexx] = number;
	}
}

void NumberGrid::setPPM( PPM& ppm ) const {
	ppm.setHeight(mHeight);
	ppm.setWidth(mWidth);
	ppm.setMaxColorValue(63);

	int row, column;
	for(row = 0; row < ppm.getHeight(); row++) {
		for(column = 0; column < ppm.getWidth(); column++) {
			int num = getNumber(row, column);
			if(num == 0) {
				ppm.setPixel(row, column, 0, 0, 0);
			} else if(num == mMax_value) {
				ppm.setPixel(row, column, 63, 31, 31);
			} else if(num % 8 == 0) {
				ppm.setPixel(row, column, 63, 63, 63);
			} else if(num % 8 == 1) {
				ppm.setPixel(row, column, 63, 31, 31);
			} else if(num % 8 == 2) {
				ppm.setPixel(row, column, 63, 63, 31);
			} else if(num % 8 == 3) {
				ppm.setPixel(row, column, 31, 63, 31);
			} else if(num % 8 == 4) {
				ppm.setPixel(row, column, 0, 0, 0);
			} else if(num % 8 == 5) {
				ppm.setPixel(row, column, 31, 63, 63);
			} else if(num % 8 == 6) {
				ppm.setPixel(row, column, 31, 31, 63);
			} else if(num % 8 == 7) {
				ppm.setPixel(row, column, 63, 31, 63);
			}
		}
	}
}

void NumberGrid::setPPM( PPM& ppm, const ColorTable& colors ) const {
	if(colors.getNumberOfColors() >= 2) {
		ppm.setHeight(mHeight);
		ppm.setWidth(mWidth);
		ppm.setMaxColorValue(colors.getMaxChannelValue());

		int row, column;
		for(row = 0; row < ppm.getHeight(); row++) {
			for(column = 0; column < ppm.getWidth(); column++) {
				int num = getNumber(row, column);
				if(num == getMaxNumber()) {
					int r = colors[colors.getNumberOfColors()-1].getRed();
					int g = colors[colors.getNumberOfColors()-1].getGreen();
					int b = colors[colors.getNumberOfColors()-1].getBlue();
					ppm.setPixel(row, column, r, g, b);
				} else {
					int r = colors[num % colors.getNumberOfColors()].getRed();
					int g = colors[num % colors.getNumberOfColors()].getGreen();
					int b = colors[num % colors.getNumberOfColors()].getBlue();
					ppm.setPixel(row, column, r, g, b);
				}
			}
		}
	}
}
		
void NumberGrid::setGridSize( const int& height, const int& width ) {
	if(height >= 2 && width >= 2) {
		mHeight = height;
		mWidth = width;
		mGrid.resize(height * width);
	}
}

void NumberGrid::calculateAllNumbers() {
	int row, column;
	for(row = 0; row < getHeight(); row++) {
		for(column = 0; column < getWidth(); column++) {
			setNumber(row, column, calculateNumber(row, column));
		}
	}
}

