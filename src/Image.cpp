#include "Image.h"
#include <vector>

Image::Image()
	: mHeight(0), mWidth(0) {
	mPixels.resize(mHeight * mWidth * 3);
}	

Image::Image(const int& height, const int& width)
	: mHeight(height), mWidth(width) {
	mPixels.resize(mHeight * mWidth * 3);
}

int Image::getHeight( ) const {
	return mHeight;
}

int Image::getWidth( ) const {
	return mWidth;
}

bool Image::indexValid(  const int& row,  const int& column,  const int& channel  ) const {
	if(row >= 0 && row < mHeight && column >= 0 && column < mWidth && channel >= 0 && channel < 3) {
		return true;
	}
	else {
		return false;
	}
}

int Image::index(  const int& row,  const int& column,  const int& channel  ) const {
	return (row * mWidth * 3 + column * 3) + channel;
}

int Image::getChannel( const int& row, const int& column, const int& channel ) const {
	if(indexValid(row, column, channel) == true) {
		int pixel = index(row, column, channel);
		int value = mPixels[pixel];
		return value;
	} else {
		return -1;
	}
}

void Image::setHeight( const int& height ) {
	if(height >= 0) {
		mHeight = height;
		mPixels.resize(mHeight * mWidth * 3);
	}
}	

void Image::setWidth( const int& width ) {
	if(width >= 0) {
		mWidth = width;
		mPixels.resize(mHeight * mWidth * 3);
	}
}	

void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
	if(indexValid(row, column, channel) == true) {
		int index = (row * mWidth * 3 + column * 3) + channel;
		mPixels[index] = value;
	}
}	
	

