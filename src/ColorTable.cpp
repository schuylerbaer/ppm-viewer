#include "ColorTable.h"
#include <iostream>

//Color class

Color::Color()
	: mRed(0), mGreen(0), mBlue(0) {
}

Color::Color(const int& red, const int& green, const int& blue)
	: mRed(red), mGreen(green), mBlue(blue) {
}

int Color::getRed( ) const {
	return mRed;
}

int Color::getGreen( ) const {
	return mGreen;
}

int Color::getBlue( ) const {
	return mBlue;
}

int Color::getChannel( const int& channel ) const {
	if(channel == 0) {
		return getRed();
	} else if(channel == 1) {
		return getGreen();
	} else if(channel == 2) {
		return getBlue();
	} else {
		return -1;
	}
}

void Color::setRed( const int& value ) {
	if(value >= 0) {
		mRed = value;
	}
}

void Color::setGreen( const int& value ) {
	if(value >= 0) {
		mGreen = value;
	}
}

void Color::setBlue( const int& value ) {
	if(value >= 0) {
		mBlue = value;
	}
}

void Color::setChannel( const int& channel, const int& value ) {
	if(value >= 0) {
		if(channel == 0) {
			mRed = value;
		} else if(channel == 1) {
			mGreen = value;
		} else if(channel == 2) {
			mBlue = value;
		}
	}
}

void Color::invert( const int& max_color_value ) {
	if(max_color_value >= mRed && max_color_value >= mGreen && max_color_value >= mBlue) {
		mRed = max_color_value - mRed;	
		mGreen = max_color_value - mGreen;	
		mBlue = max_color_value - mBlue;	
	}
}

bool Color::operator==( const Color& rhs ) const {
	if(getRed() == rhs.getRed() && getGreen() == rhs.getGreen() && getBlue() == rhs.getBlue()) {
		return true;
	} else {
		return false;
	}
}

std::ostream& operator<<( std::ostream& os, const Color& color ) {
	os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
	return os;
}

//ColorTable class

ColorTable::ColorTable(const int& num_color) {
	mColors.resize(num_color);
}

int ColorTable::getNumberOfColors( ) const {
	return mColors.size();
}

void ColorTable::setNumberOfColors( const int& num_color ) {
	mColors.resize(num_color);
}

const Color& ColorTable::operator[]( const int& i ) const {
	if(i >= getNumberOfColors() || i < 0) {
		static Color ec( -1, -1, -1 );
		static Color c( -1, -1, -1 );
		c = ec;
		return c;
	} else {
		return mColors[i];
	}
}

Color& ColorTable::operator[]( const int& i ) {
	if(i >= getNumberOfColors() || i < 0) {
		static Color ec( -1, -1, -1 );
		static Color c( -1, -1, -1 );
		c = ec;
		return c;
	} else {
		return mColors[i];
	}
}

void ColorTable::setRandomColor( const int& max_color_value, const int& position ) {
	if(max_color_value >= 0 && position < getNumberOfColors() && position >= 0) {
		int new_red = rand() % (max_color_value + 1);
		int new_green = rand() % (max_color_value + 1);
		int new_blue = rand() % (max_color_value + 1);
		mColors[position].setRed(new_red);
		mColors[position].setGreen(new_green);
		mColors[position].setBlue(new_blue);
	}
}

double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const {
	double rise = y2 - y1;
	double run = x2 - x1;
	return rise / run;
}

double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const {
	return y1 + (slope * (x - x1));
}

void ColorTable::insertGradient( const Color& color1, const Color& color2, const int& position1, const int& position2 ) {
	if(position1 < position2) {
		if(position1 < getNumberOfColors() && position1 >= 0) {
			if(position2 < getNumberOfColors() && position2 >= 0) {
				double r_slope = gradientSlope(color1.getRed(), color2.getRed(), position1, position2);
				double g_slope = gradientSlope(color1.getGreen(), color2.getGreen(), position1, position2);
				double b_slope = gradientSlope(color1.getBlue(), color2.getBlue(), position1, position2);

				int i;
				for(i = position1; i <= position2; i++) {
					int new_red = gradientValue(color1.getRed(), position1, r_slope, i);
					int new_green = gradientValue(color1.getGreen(), position1, g_slope, i);
					int new_blue = gradientValue(color1.getBlue(), position1, b_slope, i);

					mColors[i].setRed(new_red);
					mColors[i].setGreen(new_green);
					mColors[i].setBlue(new_blue);
				}
			}
		}
	}
}

int ColorTable::getMaxChannelValue( ) const {
	int max = 0;

	int i;
	for(i = 0; i < getNumberOfColors(); i++) {
		int r = mColors[i].getRed();
		int g = mColors[i].getGreen();
		int b = mColors[i].getBlue();

		if(r > max) {
			max = r;
		}
		if(g > max) {
			max = g;
		}
		if(b > max) {
			max = b;
		}
	}
	return max;
}

void ColorTable::insertInvertedGradient(const Color& color1, const int& position1, const int& position2) {
	Color color2 = color1;
	color2.invert(255);
	insertGradient( color1, color2, position1, position2 );
}

void ColorTable::insertEasyRandomGradient(const int& position1, const int& position2) {
	if(position1 < position2) {
		if(position1 < getNumberOfColors() && position1 >= 0) {
			if(position2 < getNumberOfColors() && position2 >= 0) {
				setRandomColor(255, position1);
				setRandomColor(255, position2);
				insertGradient(mColors[position1], mColors[position2], position1, position2);
			}
		}
	}
}


