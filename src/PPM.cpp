#include "PPM.h"

PPM::PPM( )
	: Image( ), mMax_color_value(1) {
}

PPM::PPM(  const int& height, const int& width  )
	: Image(height, width), mMax_color_value(1) {
}

int PPM::getMaxColorValue( ) const {
	return mMax_color_value;
}

bool PPM::valueValid( const int& value ) const {
	if(value >= 0 && value <= mMax_color_value) {
		return true;
	} else {
		return false;
	}
}

void PPM::setMaxColorValue( const int& max_color_value ) {
	if(max_color_value >= 1 && max_color_value <= 255) {
		mMax_color_value = max_color_value;
	}
}

void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
	if(valueValid(value) == true) {
		Image::setChannel(row, column, channel, value);
	}
}

void PPM::setPixel( const int& row, const int& column, const int& red, const int& green, const int& blue ) {
	setChannel(row, column, 0, red);
	setChannel(row, column, 1, green);
	setChannel(row, column, 2, blue);
}

void PPM::writeStream(std::ostream& os) const {
	os << "P6 " << getWidth() << " " << getHeight() << " " << getMaxColorValue() << "\n";
	int row, column;
	for(row = 0; row < getHeight(); row++) {
		for(column = 0; column < getWidth(); column++) {
			unsigned char r = getChannel(row, column, 0);
			unsigned char g = getChannel(row, column, 1);
			unsigned char b = getChannel(row, column, 2);
			os.write((char *) &r, sizeof(r));
			os.write((char *) &g, sizeof(g));
			os.write((char *) &b, sizeof(b));
		}
	}
}

void PPM::readStream(std::istream& is) {
	std::string format;
	int width;
	int height;
	int maxColorValue;
	unsigned char trash;
	is >> format >> width >> height >> maxColorValue;
	setWidth(width);
	setHeight(height);
	setMaxColorValue(maxColorValue);
	is.read((char *) &trash, 1);
	for(int row = 0; row < height; row++) {
		for(int column = 0; column < width; column++) {
			unsigned char r;
			unsigned char g;
			unsigned char b;
			is.read((char *) &r, 1);
			is.read((char *) &g, 1);
			is.read((char *) &b, 1);
			setChannel(row, column, 0, r);
			setChannel(row, column, 1, g);
			setChannel(row, column, 2, b);
		}
	}
}

bool PPM::operator==( const PPM& rhs ) const {
	int lhs_pixels = this->getHeight() * this->getWidth() * 3;
	int rhs_pixels = rhs.getHeight() * rhs.getWidth() * 3;
	if(lhs_pixels == rhs_pixels) {
		return true;
	}
	else {
		return false;
	}
}

bool PPM::operator!=( const PPM& rhs ) const {
	int lhs_pixels = this->getHeight() * this->getWidth() * 3;
	int rhs_pixels = rhs.getHeight() * rhs.getWidth() * 3;
	if(lhs_pixels != rhs_pixels) {
		return true;
	}
	else {
		return false;
	}
}

bool PPM::operator<( const PPM& rhs ) const {
	int lhs_pixels = this->getHeight() * this->getWidth() * 3;
	int rhs_pixels = rhs.getHeight() * rhs.getWidth() * 3;
	if(lhs_pixels < rhs_pixels) {
		return true;
	}
	else {
		return false;
	}
}

bool PPM::operator<=( const PPM& rhs ) const {
	int lhs_pixels = this->getHeight() * this->getWidth() * 3;
	int rhs_pixels = rhs.getHeight() * rhs.getWidth() * 3;
	if(lhs_pixels <= rhs_pixels) {
		return true;
	}
	else {
		return false;
	}
}

bool PPM::operator>( const PPM& rhs ) const {
	int lhs_pixels = this->getHeight() * this->getWidth() * 3;
	int rhs_pixels = rhs.getHeight() * rhs.getWidth() * 3;
	if(lhs_pixels > rhs_pixels) {
		return true;
	}
	else {
		return false;
	}
}

bool PPM::operator>=( const PPM& rhs ) const {
	int lhs_pixels = this->getHeight() * this->getWidth() * 3;
	int rhs_pixels = rhs.getHeight() * rhs.getWidth() * 3;
	if(lhs_pixels >= rhs_pixels) {
		return true;
	}
	else {
		return false;
	}
}

PPM& PPM::operator+=( const PPM& rhs ) {
	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			int new_r = this->getChannel(row, column, 0) + rhs.getChannel(row, column, 0);
			int new_g = this->getChannel(row, column, 1) + rhs.getChannel(row, column, 1);
			int new_b = this->getChannel(row, column, 2) + rhs.getChannel(row, column, 2);

			if(new_r > this->getMaxColorValue()) {
				new_r = this->getMaxColorValue();
			}
			if(new_g > this->getMaxColorValue()) {
				new_g = this->getMaxColorValue();
			}
			if(new_b > this->getMaxColorValue()) {
				new_b = this->getMaxColorValue();
			}

			this->setPixel(row, column, new_r, new_g, new_b);
		}
	}
	return *this;
}

PPM& PPM::operator-=( const PPM& rhs ) {
	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			int new_r = this->getChannel(row, column, 0) - rhs.getChannel(row, column, 0);
			int new_g = this->getChannel(row, column, 1) - rhs.getChannel(row, column, 1);
			int new_b = this->getChannel(row, column, 2) - rhs.getChannel(row, column, 2);

			if(new_r < 0) {
				new_r = 0;
			}
			if(new_g < 0) {
				new_g = 0;
			}
			if(new_b < 0) {
				new_b = 0;
			}

			this->setPixel(row, column, new_r, new_g, new_b);
		}
	}
	return *this;
}

PPM& PPM::operator*=( const double& rhs ) {
	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			double new_r = this->getChannel(row, column, 0) * rhs;
			double new_g = this->getChannel(row, column, 1) * rhs;
			double new_b = this->getChannel(row, column, 2) * rhs; 

			if(new_r > this->getMaxColorValue()) {
				new_r = this->getMaxColorValue();
			}
			if(new_g > this->getMaxColorValue()) {
				new_g = this->getMaxColorValue();
			}
			if(new_b > this->getMaxColorValue()) {
				new_b = this->getMaxColorValue();
			}

			if(new_r < 0) {
				new_r = 0;
			}
			if(new_g < 0) {
				new_g = 0;
			}
			if(new_b < 0) {
				new_b = 0;
			}

			this->setPixel(row, column, new_r, new_g, new_b);
		}
	}
	return *this;
}

PPM& PPM::operator/=( const double& rhs ) {
	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			double new_r = this->getChannel(row, column, 0) / rhs;
			double new_g = this->getChannel(row, column, 1) / rhs;
			double new_b = this->getChannel(row, column, 2) / rhs;

			if(new_r > this->getMaxColorValue()) {
				new_r = this->getMaxColorValue();
			}
			if(new_g > this->getMaxColorValue()) {
				new_g = this->getMaxColorValue();
			}
			if(new_b > this->getMaxColorValue()) {
				new_b = this->getMaxColorValue();
			}

			if(new_r < 0) {
				new_r = 0;
			}
			if(new_g < 0) {
				new_g = 0;
			}
			if(new_b < 0) {
				new_b = 0;
			}

			this->setPixel(row, column, new_r, new_g, new_b);
		}
	}
	return *this;
}

PPM PPM::operator+( const PPM& rhs ) const {
	PPM new_ppm(this->getHeight(), this->getWidth());
	new_ppm.setMaxColorValue(this->getMaxColorValue());

	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			int new_r = this->getChannel(row, column, 0) + rhs.getChannel(row, column, 0);
			int new_g = this->getChannel(row, column, 1) + rhs.getChannel(row, column, 1);
			int new_b = this->getChannel(row, column, 2) + rhs.getChannel(row, column, 2);

			if(new_r > this->getMaxColorValue()) {
				new_r = this->getMaxColorValue();
			}
			if(new_g > this->getMaxColorValue()) {
				new_g = this->getMaxColorValue();
			}
			if(new_b > this->getMaxColorValue()) {
				new_b = this->getMaxColorValue();
			}

			new_ppm.setPixel(row, column, new_r, new_g, new_b);
		}
	}
	return new_ppm;
}

PPM PPM::operator-( const PPM& rhs ) const {
	PPM new_ppm(this->getHeight(), this->getWidth());
	new_ppm.setMaxColorValue(this->getMaxColorValue());

	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			int new_r = this->getChannel(row, column, 0) - rhs.getChannel(row, column, 0);
			int new_g = this->getChannel(row, column, 1) - rhs.getChannel(row, column, 1);
			int new_b = this->getChannel(row, column, 2) - rhs.getChannel(row, column, 2);

			if(new_r < 0) {
				new_r = 0;
			}
			if(new_g < 0) {
				new_g = 0;
			}
			if(new_b < 0) {
				new_b = 0;
			}

			new_ppm.setPixel(row, column, new_r, new_g, new_b);
		}
	}
	return new_ppm;
}

PPM PPM::operator*( const double& rhs ) const {
	PPM new_ppm(this->getHeight(), this->getWidth());
	new_ppm.setMaxColorValue(this->getMaxColorValue());

	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			double new_r = this->getChannel(row, column, 0) * rhs;
			double new_g = this->getChannel(row, column, 1) * rhs;
			double new_b = this->getChannel(row, column, 2) * rhs;

			if(new_r > this->getMaxColorValue()) {
				new_r = this->getMaxColorValue();
			}
			if(new_g > this->getMaxColorValue()) {
				new_g = this->getMaxColorValue();
			}
			if(new_b > this->getMaxColorValue()) {
				new_b = this->getMaxColorValue();
			}

			if(new_r < 0) {
				new_r = 0;
			}
			if(new_g < 0) {
				new_g = 0;
			}
			if(new_b < 0) {
				new_b = 0;
			}

			new_ppm.setPixel(row, column, new_r, new_g, new_b);
		}
	}
	return new_ppm;
}

PPM PPM::operator/( const double& rhs ) const{
	PPM new_ppm(this->getHeight(), this->getWidth());
	new_ppm.setMaxColorValue(this->getMaxColorValue());

	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			double new_r = this->getChannel(row, column, 0) / rhs;
			double new_g = this->getChannel(row, column, 1) / rhs;
			double new_b = this->getChannel(row, column, 2) / rhs;

			if(new_r > this->getMaxColorValue()) {
				new_r = this->getMaxColorValue();
			}
			if(new_g > this->getMaxColorValue()) {
				new_g = this->getMaxColorValue();
			}
			if(new_b > this->getMaxColorValue()) {
				new_b = this->getMaxColorValue();
			}

			if(new_r < 0) {
				new_r = 0;
			}
			if(new_g < 0) {
				new_g = 0;
			}
			if(new_b < 0) {
				new_b = 0;
			}

			new_ppm.setPixel(row, column, new_r, new_g, new_b);
		}
	}
	return new_ppm;
}

void PPM::grayFromChannel( PPM& dst, const int& src_channel ) const {
	dst.setMaxColorValue(this->getMaxColorValue());
	dst.setHeight(this->getHeight());
	dst.setWidth(this->getWidth());

	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			int r = this->getChannel(row, column, 0);
			int g = this->getChannel(row, column, 1);
			int b = this->getChannel(row, column, 2);

			if(src_channel == 0) {
				dst.setPixel(row, column, r, r, r);
			} else if(src_channel == 1) {
				dst.setPixel(row, column, g, g, g);
			} else if(src_channel == 2) {
				dst.setPixel(row, column, b, b, b);
			}
		}
	}
}

void PPM::grayFromRed( PPM& dst ) const {
	grayFromChannel(dst, 0);
	return;
}

void PPM::grayFromGreen( PPM& dst ) const {
	grayFromChannel(dst, 1);
	return;
}

void PPM::grayFromBlue( PPM& dst ) const {
	grayFromChannel(dst, 2);
	return;
}

double PPM::linearColorimetricPixelValue( const int& row, const int& column ) const {
	int r = this->getChannel(row, column, 0);
	int g = this->getChannel(row, column, 1);
	int b = this->getChannel(row, column, 2);
	double lcv = 0.2126*r + 0.7152*g + 0.0722*b;
	return lcv;
}

void PPM::grayFromLinearColorimetric( PPM& dst ) const {
	dst.setMaxColorValue(this->getMaxColorValue());
	dst.setHeight(this->getHeight());
	dst.setWidth(this->getWidth());

	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			double lcv = linearColorimetricPixelValue(row, column);
			dst.setPixel(row, column, lcv, lcv, lcv);
		}
	}
}

void PPM::sepiaFilter( PPM& dst ) const {
	dst.setMaxColorValue(this->getMaxColorValue());
	dst.setHeight(this->getHeight());
	dst.setWidth(this->getWidth());

	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			double new_red = 0.393*this->getChannel(row, column, 0) + 0.769*this->getChannel(row, column, 1) + 0.189*this->getChannel(row, column, 2);
			double new_green = 0.349*this->getChannel(row, column, 0) + 0.686*this->getChannel(row, column, 1) + 0.168*this->getChannel(row, column, 2);
			double new_blue = 0.272*this->getChannel(row, column, 0) + 0.534*this->getChannel(row, column, 1) + 0.131*this->getChannel(row, column, 2);

			if(new_red > dst.getMaxColorValue()) {
				new_red = dst.getMaxColorValue();
			}

			if(new_green > dst.getMaxColorValue()) {
				new_green = dst.getMaxColorValue();
			}

			if(new_blue > dst.getMaxColorValue()) {
				new_blue = dst.getMaxColorValue();
			}

			dst.setPixel(row, column, new_red, new_green, new_blue);
		}
	}
}

void PPM::orangeFilter(PPM& dst) const {
	dst.setMaxColorValue(this->getMaxColorValue());
	dst.setHeight(this->getHeight());
	dst.setWidth(this->getWidth());

	int row, column;
	for(row = 0; row < this->getHeight(); row++) {
		for(column = 0; column < this->getWidth(); column++) {
			int new_red = 2*(2*this->getChannel(row, column, 0)+this->getChannel(row, column, 1))/3;
			int new_green = 2*(2*this->getChannel(row, column, 0)+this->getChannel(row, column, 1))/6;
			int new_blue = this->getChannel(row, column, 2)/2;

			if(new_red > dst.getMaxColorValue()) {
				new_red = dst.getMaxColorValue();
			}

			if(new_green > dst.getMaxColorValue()) {
				new_green = dst.getMaxColorValue();
			}

			if(new_blue > dst.getMaxColorValue()) {
				new_blue = dst.getMaxColorValue();
			}

			dst.setPixel(row, column, new_red, new_green, new_blue);
		}
	}
}



