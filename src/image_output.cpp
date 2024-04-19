#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include <iostream>
#include <fstream>

void drawAsciiImage( ActionData& action_data ) {
	int row, column;
	for(row = 0; row < action_data.getOutputImage().getHeight(); row++) {
		for(column = 0; column < action_data.getOutputImage().getWidth(); column++) {
			int r = action_data.getOutputImage().getChannel(row, column, 0);
			int g = action_data.getOutputImage().getChannel(row, column, 1);
			int b = action_data.getOutputImage().getChannel(row, column, 2);
			double strength = (r + g + b) / 765.0;	
			if(strength >= 1.0) {
				action_data.getOS() << "@";
			} else if(strength >= 0.9) {
				action_data.getOS() << "#";
			} else if(strength >= 0.8) {
				action_data.getOS() << "%";
			} else if(strength >= 0.7) {
				action_data.getOS() << "*";
			} else if(strength >= 0.6) {
				action_data.getOS() << "|";
			} else if(strength >= 0.5) {
				action_data.getOS() << "+";
			} else if(strength >= 0.4) {
				action_data.getOS() << ";";
			} else if(strength >= 0.3) {
				action_data.getOS() << "~";
			} else if(strength >= 0.2) {
				action_data.getOS() << "-";
			} else if(strength >= 0.1) {
				action_data.getOS() << ".";
			} else if(strength >= 0.0) {
				action_data.getOS() << " ";
			}
		}
		action_data.getOS() << std::endl;
	}
}

void writeUserImage( ActionData& action_data ) {
	std::ofstream data(getString(action_data, "Output filename? "));
	//if(!data) {
		//action_data.getOS() << data << "could not be written." << std::endl;
	//}
	action_data.getOutputImage().writeStream(data);
	data.close();
}

void copyImage(ActionData& action_data) {
	action_data.getOutputImage() = action_data.getInputImage1();
}

void copyImage1ToImage2(ActionData& action_data) {
	action_data.getInputImage2() = action_data.getInputImage1();
}

void copyImage2ToImage1(ActionData& action_data) {
	action_data.getInputImage1() = action_data.getInputImage2();
}

void readUserImage1( ActionData& action_data ) {
	std::ifstream name(getString(action_data, "Input filename? "));
	//if(!name) {
		//action_data.getOS() << name << "could not be opened." << std::endl;
	//}
	action_data.getInputImage1().readStream(name);
	name.close();
}

void readUserImage2( ActionData& action_data ) {
	std::ifstream name(getString(action_data, "Input filename? "));
	//if(!name) {
		//action_data.getOS() << name << "could not be opened." << std::endl;
	//}
	action_data.getInputImage2().readStream(name);
	name.close();
}

