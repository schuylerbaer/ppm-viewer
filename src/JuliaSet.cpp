#include "JuliaSet.h"

JuliaSet::JuliaSet( )
	: mA(-0.650492), mB(-0.478235) {
}

JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b )
	: ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA(a), mB(b) {
}

JuliaSet::~JuliaSet( ) {
}

double JuliaSet::getA( ) const {
	return mA;
}

double JuliaSet::getB( ) const {
	return mB;
}

void JuliaSet::setParameters( const double& a, const double& b ) {
	if(a >= -2.0 and b >= -2.0 and a <= 2.0 and b <= 2.0) {
		mA = a;
		mB = b;
	}
}

void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const {
	x1 = x0*x0 - y0*y0 + getA();
	y1 = 2*x0*y0 + getB();
}

int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const {
	double x1, y1;
	if(x0*x0 + y0*y0 > 4 or getMaxNumber() == 0) {
		return 0;
	}
	calculateNextPoint(x0, y0, x1, y1);
	int i;
	for(i = 1; i < getMaxNumber(); i++) {
		if(x1*x1 + y1*y1 > 4) {
			return i;
		}
		calculateNextPoint(x1, y1, x1, y1);
	}
	return i;
}

int JuliaSet::calculateNumber( const int& row, const int& column ) const {
	if(indexValid(row, column) == true) {
		double x = calculatePlaneXFromPixelColumn(column);
		double y = calculatePlaneYFromPixelRow(row);
		calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
		return calculatePlaneEscapeCount(x, y);
	} else {
		return -1;
	}
}


//Test3

JuliaSetFour::JuliaSetFour() {
}

JuliaSetFour::~JuliaSetFour() {
}

void JuliaSetFour::calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const {
	x1 = x0*x0*x0*x0 - 6*x0*x0*y0*y0 + y0*y0*y0*y0 + getA();
	y1 = 4*x0*x0*x0*y0 - 4*x0*y0*y0*y0 + getB();
}





