#include "image_menu.h"
#include "ActionData.h"
#include <iostream>
#include <string>

std::string getString(ActionData& action_data, const std::string& prompt) {
	std::string value;
	action_data.getOS() << prompt;
	action_data.getIS() >> value;
	return value;
}

int getInteger(ActionData& action_data, const std::string& prompt) {
	int value;
	action_data.getOS() << prompt;
	action_data.getIS() >> value;
	return value;
}

double getDouble(ActionData& action_data, const std::string& prompt) {
	double value;
	action_data.getOS() << prompt;
	action_data.getIS() >> value;
	return value;
}

int askQuestions3(ActionData& action_data) {
	std::string favColor = getString(action_data, "What is your favorite color? ");
	int favInteger = getInteger(action_data, "What is your favorite integer? ");
	double favNumber = getDouble(action_data, "What is your favorite number? ");

	if (favInteger > 0) {
		for (int i = 1; i <= favInteger; i++) {
			action_data.getOS() << i << " " << favColor << " " << favNumber << std::endl;
		}
	}

	return favInteger;
}

std::string getChoice( ActionData& action_data ) {
	return getString(action_data, "Choice? ");
}

void commentLine( ActionData& action_data ) {
	unsigned char c;

	while(action_data.getIS().good()) {
		if(action_data.getIS().peek() == '\n') {	//if next char is newline, read one more time (for unit test)
			action_data.getIS().read((char *) &c, 1);
			return;
		}
		action_data.getIS().read((char *) &c, 1);
	}
	return;
}

void quit(ActionData& action_data) {
	action_data.setDone();
	return;
}

