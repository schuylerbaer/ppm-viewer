#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet( ) {
}

MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
	: ComplexFractal(height, width, min_x, max_x, min_y, max_y) {
}

MandelbrotSet::~MandelbrotSet( ) {
}

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const {
	x1 = x0*x0 - y0*y0 + a;
	y1 = 2*x0*y0 + b;
}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const {
	double x1, y1;
	if(a*a + b*b > 4 or getMaxNumber() == 0) {
		return 0;
	}
	calculateNextPoint(0, 0, a, b, x1, y1);
	int i;
	for(i = 0; i < getMaxNumber(); i++) {
		if(x1*x1 + y1*y1 > 4) {
			return i;
		}
		calculateNextPoint(x1, y1, a, b, x1, y1);
	}
	return i;
}

int MandelbrotSet::calculateNumber( const int& row, const int& column ) const {
	if(indexValid(row, column) == true) {
		double x = calculatePlaneXFromPixelColumn(column);
		double y = calculatePlaneYFromPixelRow(row);
		calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
		return calculatePlaneEscapeCount(x, y);
	} else {
		return -1;
	}
}

//practice-test
MandelbrotPower::MandelbrotPower() 
	:	mD(2.0) {
}

MandelbrotPower::~MandelbrotPower() {
}

double MandelbrotPower::getPower() const {
	return mD;
}

void MandelbrotPower::setPower(const double& power) {
	mD = power;
}

void MandelbrotPower::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const {
	double r = std::sqrt( x0 * x0 + y0 * y0 );
	double theta = std::atan2( y0, x0 );
	x1 = (std::pow(r, getPower())) * std::cos(getPower() * theta) + a;
	y1 = (std::pow(r, getPower())) * std::sin(getPower() * theta) + b;
}


