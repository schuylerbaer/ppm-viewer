#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "NumberGrid.h"
#include <iostream>
#include <string>
#include <cmath>

void diagonalQuadPattern( ActionData& action_data ) {
	int height = getInteger(action_data, "Image height? ");
	int width = getInteger(action_data, "Image width? ");
	action_data.getInputImage1().setHeight(height);
	action_data.getInputImage1().setWidth(width);
	action_data.getInputImage1().setMaxColorValue(255);
	
	int midHeight = action_data.getInputImage1().getHeight() / 2;
	int midWidth = action_data.getInputImage1().getWidth() / 2;

	//set reds and greens for top and bottom half
	int row, column;

	for(column = 0; column < action_data.getInputImage1().getWidth(); column++) {
		for(row = 0; row < midHeight; row++) {
			action_data.getInputImage1().setChannel(row, column, 0, 0);
			action_data.getInputImage1().setChannel(row, column, 1, (2 * row + 2 * column) % 256);
		}
		for(row = midHeight; row < action_data.getInputImage1().getHeight(); row++) {
			action_data.getInputImage1().setChannel(row, column, 0, 255);
			action_data.getInputImage1().setChannel(row, column, 1, (2 * row + 2 * column) % 256);
		}
	}

	//set blues for left and right half
	for(row = 0; row < action_data.getInputImage1().getHeight(); row++) {
		for(column = 0; column < midWidth; column++) {
			action_data.getInputImage1().setChannel(row, column, 2, 0);
		}
		for(column = midWidth; column < action_data.getInputImage1().getWidth(); column++) {
			action_data.getInputImage1().setChannel(row, column, 2, 255);
		}
	}
}

void stripedDiagonalPattern( ActionData& action_data ) {
	int height = getInteger(action_data, "Image height? ");
	int width = getInteger(action_data, "Image width? ");
	int max = (height + width) / 3;
	if(max > 255) {
		max = 255;
	}

	action_data.getInputImage1().setHeight(height);
	action_data.getInputImage1().setWidth(width);
	action_data.getInputImage1().setMaxColorValue(max);

	int midHeight = action_data.getInputImage1().getHeight() / 2;

	int row, column;
	for(column = 0; column < action_data.getInputImage1().getWidth(); column++) {
		for(row = 0; row < midHeight; row++) {
			//set red
			action_data.getInputImage1().setChannel(row, column, 0, 0);
			//set green
			action_data.getInputImage1().setChannel(row, column, 1, (row + action_data.getInputImage1().getWidth() - column - 1) % (action_data.getInputImage1().getMaxColorValue() + 1));
			//set blue
			if(column < row) {
				action_data.getInputImage1().setChannel(row, column, 2, 0);
			} else {
				action_data.getInputImage1().setChannel(row, column, 2, action_data.getInputImage1().getMaxColorValue());
			}
		}
		for(row = midHeight; row < action_data.getInputImage1().getHeight(); row++) {
			if(row % 3 == 0) {
				//set red
				action_data.getInputImage1().setChannel(row, column, 0, 0);
				//set green
				action_data.getInputImage1().setChannel(row, column, 1, (row + action_data.getInputImage1().getWidth() - column - 1) % (action_data.getInputImage1().getMaxColorValue() + 1));
				//set blue
				if(column < row) {
					action_data.getInputImage1().setChannel(row, column, 2, 0);
				} else {
					action_data.getInputImage1().setChannel(row, column, 2, action_data.getInputImage1().getMaxColorValue());
				}
			} else {
				//set red
				action_data.getInputImage1().setChannel(row, column, 0, action_data.getInputImage1().getMaxColorValue());
				//set green
				action_data.getInputImage1().setChannel(row, column, 1, (row + action_data.getInputImage1().getWidth() - column - 1) % (action_data.getInputImage1().getMaxColorValue() + 1));
				//set blue
				if(column < row) {
					action_data.getInputImage1().setChannel(row, column, 2, 0);
				} else {
					action_data.getInputImage1().setChannel(row, column, 2, action_data.getInputImage1().getMaxColorValue());
				}
			}
		}
	}
}

void fourSquarePattern( ActionData& action_data ) {
	int size = getInteger(action_data, "Image size? ");
	action_data.getInputImage1().setHeight(size);
	action_data.getInputImage1().setWidth(size);
	action_data.getInputImage1().setMaxColorValue(100);

	int midHeight = action_data.getInputImage1().getHeight() / 2;
	int midWidth = action_data.getInputImage1().getWidth() / 2;

	int row, column;
	//left half
	for(column = 0; column < midWidth; column++) {
		for(row = 0; row < midHeight; row++) {
			action_data.getInputImage1().setChannel(row, column, 0, 100);
			action_data.getInputImage1().setChannel(row, column, 1, 0);
			action_data.getInputImage1().setChannel(row, column, 2, 66);
		}	
		for(row = midHeight; row < action_data.getInputImage1().getHeight(); row++) {
			action_data.getInputImage1().setChannel(row, column, 0, 66);
			action_data.getInputImage1().setChannel(row, column, 1, 33);
			action_data.getInputImage1().setChannel(row, column, 2, 100);
		}
	}

	//right half
	for(column = midWidth; column < action_data.getInputImage1().getWidth(); column++) {
		for(row = 0; row < midHeight; row++) {
			action_data.getInputImage1().setChannel(row, column, 0, 0);
			action_data.getInputImage1().setChannel(row, column, 1, 100);
			action_data.getInputImage1().setChannel(row, column, 2, 33);
		}	
		for(row = midHeight; row < action_data.getInputImage1().getHeight(); row++) {
			action_data.getInputImage1().setChannel(row, column, 0, 33);
			action_data.getInputImage1().setChannel(row, column, 1, 66);
			action_data.getInputImage1().setChannel(row, column, 2, 0);
		}
	}
}

void flagRomaniaPattern( ActionData& action_data ) {
	int height = getInteger(action_data, "Image height? ");
        action_data.getInputImage1().setHeight(height);
        action_data.getInputImage1().setWidth(3 * height / 2);
        action_data.getInputImage1().setMaxColorValue(255);

	int left = action_data.getInputImage1().getWidth() / 3;
	int right = action_data.getInputImage1().getWidth() / 3 * 2; 

	int row, column;
	for(row = 0; row < action_data.getInputImage1().getHeight(); row++) {
		for(column = 0; column < left; column++) {
			action_data.getInputImage1().setChannel(row, column, 0, 0);
			action_data.getInputImage1().setChannel(row, column, 1, 43);
			action_data.getInputImage1().setChannel(row, column, 2, 127);
		}
		for(column = left; column < right; column++) {
			action_data.getInputImage1().setChannel(row, column, 0, 252);
			action_data.getInputImage1().setChannel(row, column, 1, 209);
			action_data.getInputImage1().setChannel(row, column, 2, 22);
		}
		for(column = right; column < action_data.getInputImage1().getWidth(); column++) {
			action_data.getInputImage1().setChannel(row, column, 0, 206);
			action_data.getInputImage1().setChannel(row, column, 1, 17);
			action_data.getInputImage1().setChannel(row, column, 2, 38);
		}
	}
}

void setSize( ActionData& action_data ) {
	int h = getInteger(action_data, "Height? ");
	int w = getInteger(action_data, "Width? ");
	action_data.getInputImage1().setHeight(h);
	action_data.getInputImage1().setWidth(w);
}

void setMaxColorValue( ActionData& action_data ) {
	int m = getInteger(action_data, "Max color value? ");
	action_data.getInputImage1().setMaxColorValue(m);
}

void setChannel( ActionData& action_data ) {
	int r = getInteger(action_data, "Row? ");
	int c = getInteger(action_data, "Column? ");
	int ch = getInteger(action_data, "Channel? ");
	int v = getInteger(action_data, "Value? ");
	action_data.getInputImage1().setChannel(r, c, ch, v);
}

void setPixel( ActionData& action_data ) {
	int r = getInteger(action_data, "Row? ");
	int c = getInteger(action_data, "Column? ");
	int red = getInteger(action_data, "Red? ");
	int green = getInteger(action_data, "Green? ");
	int blue = getInteger(action_data, "Blue? ");
	action_data.getInputImage1().setPixel(r, c, red, green, blue);
}

void clearAll( ActionData& action_data ) {
	int row, column;
	for(row = 0; row < action_data.getInputImage1().getHeight(); row++) {
		for(column = 0; column < action_data.getInputImage1().getWidth(); column++) {
			action_data.getInputImage1().setPixel(row, column, 0, 0, 0);
		}
	}
}

void drawCircle(ActionData& action_data) {
	double center_row = getInteger(action_data, "Center Row? ");
	double center_column = getInteger(action_data, "Center Column? ");
	double radius = getInteger(action_data, "Radius? ");
	int r = getInteger(action_data, "Red? ");
	int g = getInteger(action_data, "Green? ");
	int b = getInteger(action_data, "Blue? ");
	

	int row, column;
	for(row = 0; row < action_data.getInputImage1().getHeight(); row++) {
		for(column = 0; column < action_data.getInputImage1().getWidth(); column++) {
			double rds = (center_row - row) * (center_row - row);
			double cds = (center_column - column) * (center_column - column);
			double sum = rds + cds;
			double dist = std::sqrt(sum);

			if(dist <= radius) {
				action_data.getInputImage1().setPixel(row, column, r, g, b);
			}
		}
	}
}

void drawSquare(ActionData& action_data) {
	double center_row = getInteger(action_data, "Row? ");
	double center_column = getInteger(action_data, "Column? ");
	double size = getInteger(action_data, "Size? ");
	int r = getInteger(action_data, "Red? ");
	int g = getInteger(action_data, "Green? ");
	int b = getInteger(action_data, "Blue? ");

	int row, column;
	for(row = 0; row < action_data.getInputImage1().getHeight(); row++) {
		for(column = 0; column < action_data.getInputImage1().getWidth(); column++) {
			double rdist = abs((center_row - row));
			double cdist = abs((center_column - column));
			double dist = size/2;

			if((rdist <= dist) && (cdist <= dist)) {
				action_data.getInputImage1().setPixel(row, column, r, g, b);
			}
		}
	}
}

void drawBox(ActionData& action_data) {
	int top_row = getInteger(action_data, "Top Row? ");
	int left_column = getInteger(action_data, "Left Column? ");
	int bottom_row = getInteger(action_data, "Bottom Row? ");
	int right_column = getInteger(action_data, "Right Column? ");
	int r = getInteger(action_data, "Red? ");
	int g = getInteger(action_data, "Green? ");
	int b = getInteger(action_data, "Blue? ");
	
	int row, column;
	for(row = top_row; row <= bottom_row; row++) {
		for(column = left_column; column <= right_column; column++) {
			action_data.getInputImage1().setPixel(row, column, r, g, b);
		}
	}
}

void drawTestColorPattern(ActionData& action_data) {
	int h = getInteger(action_data, "Height? ");
	int w = getInteger(action_data, "Width? ");
	int mcv = getInteger(action_data, "Max color value? ");
	
	action_data.getInputImage1().setHeight(h);
	action_data.getInputImage1().setWidth(w);
	action_data.getInputImage1().setMaxColorValue(mcv);
	int row, column;
	for(row = 0; row < h/2; row++) {
		for(column = 0; column < w/2; column++) {
			action_data.getInputImage1().setPixel(row, column, mcv, 0, 0);
		}
	}

	for(row = 0; row < h/2; row++) {
		for(column = w/2; column < w; column++) {
			action_data.getInputImage1().setPixel(row, column, 0, mcv, 0);
		}
	}

	for(row = h/2; row < h; row++) {
		for(column = 0; column < w/2; column++) {
			action_data.getInputImage1().setPixel(row, column, 0, 0, mcv);
		}
	}

	for(row = h/2; row < h; row++) {
		for(column = w/2; column < w; column++) {
			action_data.getInputImage1().setPixel(row, column, mcv/2, mcv/2, mcv/2);
		}
	}
}

void configureGrid(ActionData& action_data) {
	int height = getInteger(action_data, "Grid Height? ");
	int width = getInteger(action_data, "Grid Width? ");
	int max = getInteger(action_data, "Grid Max Value? ");

	action_data.getGrid().setGridSize(height, width);
	action_data.getGrid().setMaxNumber(max);
}

void setGrid(ActionData& action_data) {
	int row = getInteger(action_data, "Grid Row? ");
	int column = getInteger(action_data, "Grid Column? ");
	int value = getInteger(action_data, "Grid Value? ");

	action_data.getGrid().setNumber(row, column, value);
}

void applyGrid(ActionData& action_data) {
	action_data.getGrid().setPPM(action_data.getOutputImage());
}

void setColorTableSize(ActionData& action_data) {
	int size = getInteger(action_data, "Size? ");
	action_data.getTable().setNumberOfColors(size);
}

void setColor(ActionData& action_data) {
	int pos = getInteger(action_data, "Position? ");
	int r = getInteger(action_data, "Red? ");
	int g = getInteger(action_data, "Green? ");
	int b = getInteger(action_data, "Blue? ");

	action_data.getTable()[pos].setRed(r);
	action_data.getTable()[pos].setGreen(g);
	action_data.getTable()[pos].setBlue(b);
}

void setRandomColor(ActionData& action_data) {
	int pos = getInteger(action_data, "Position? ");
	action_data.getTable().setRandomColor(255, pos);
}

void setColorGradient(ActionData& action_data) {
	int first = getInteger(action_data, "First position? ");
	int fr = getInteger(action_data, "First red? ");
	int fg = getInteger(action_data, "First green? ");
	int fb = getInteger(action_data, "First blue? ");
	
	int second = getInteger(action_data, "Second position? ");
	int sr = getInteger(action_data, "Second red? ");
	int sg = getInteger(action_data, "Second green? ");
	int sb = getInteger(action_data, "Second blue? ");

	action_data.getTable().insertGradient(Color(fr, fg, fb), Color(sr, sg, sb), first, second);
}

void applyGridColorTable(ActionData& action_data) {
	action_data.getGrid().setPPM(action_data.getOutputImage(), action_data.getTable());
}

void setFractalPlaneSize(ActionData& action_data) {
	ComplexFractal *cfp = dynamic_cast<ComplexFractal *>(&action_data.getGrid());
	if(cfp != 0) {
		double min_x = getDouble(action_data, "Min X? ");
		double max_x = getDouble(action_data, "Max X? ");
		double min_y = getDouble(action_data, "Min Y? ");
		double max_y = getDouble(action_data, "Max Y? ");

		cfp->setPlaneSize(min_x, max_x, min_y, max_y);
	} else {
		action_data.getOS() << "Not a ComplexFractal object. Can't set plane size.\n";
	}
}

void calculateFractal(ActionData& action_data) {
	int row, column;
	for(row = 0; row < action_data.getGrid().getHeight(); row++) {
		for(column = 0; column < action_data.getGrid().getWidth(); column++) {
			int num = action_data.getGrid().calculateNumber(row, column);
			action_data.getGrid().setNumber(row, column, num);
		}
	}
}

void setJuliaParameters(ActionData& action_data) {
	JuliaSet *jsp = dynamic_cast<JuliaSet *>(&action_data.getGrid());
	if(jsp != 0) {
		double a = getDouble(action_data, "Parameter a? ");
		double b = getDouble(action_data, "Parameter b? ");
		jsp->setParameters(a, b);
	} else {
		action_data.getOS() << "Not a JuliaSet object. Can't set parameters.\n";
	}
}

void setMandelbrotPower(ActionData& action_data) {
	MandelbrotPower *mpp = dynamic_cast<MandelbrotPower *>(&action_data.getGrid());
	if(mpp != 0) {
		double p = getDouble(action_data, "Power? ");
		mpp->setPower(p);
	} else {
		action_data.getOS() << "Not a MandelbrotPower object. Can't set power.\n";
	}
}

void setInvertedColorGradient(ActionData& action_data) {
	int first = getInteger(action_data, "First position? ");
	int fr = getInteger(action_data, "First red? ");
	int fg = getInteger(action_data, "First green? ");
	int fb = getInteger(action_data, "First blue? ");
	
	int second = getInteger(action_data, "Second position? ");

	action_data.getTable().insertInvertedGradient(Color(fr, fg, fb), first, second);
}

void setEasyRandomColorGradient(ActionData& action_data) {
	int first = getInteger(action_data, "First position? ");
	int second = getInteger(action_data, "Second position? ");
	action_data.getTable().insertEasyRandomGradient(first, second);
}

void calculateFractalSingleThread(ActionData& action_data) {
	action_data.getGrid().NumberGrid::calculateAllNumbers();
}
