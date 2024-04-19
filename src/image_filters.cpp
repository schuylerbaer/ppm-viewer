#include "image_menu.h"
#include "ActionData.h"
#include "PPM.h"

void plusEquals( ActionData& action_data ) {
	action_data.getInputImage1() += action_data.getInputImage2();
	return;
}

void minusEquals( ActionData& action_data ) {
	action_data.getInputImage1() -= action_data.getInputImage2();
	return;
}

void timesEquals( ActionData& action_data ) {
	double factor = getDouble(action_data, "Factor? ");
	action_data.getInputImage1() *= factor; 
	return;
}

void divideEquals( ActionData& action_data ) {
	double factor = getDouble(action_data, "Factor? ");
	action_data.getInputImage1() /= factor; 
	return;
}

void plus( ActionData& action_data ) {
	action_data.getOutputImage() = action_data.getInputImage1() + action_data.getInputImage2();
	return;
}

void minus( ActionData& action_data ) {
	action_data.getOutputImage() = action_data.getInputImage1() - action_data.getInputImage2();
	return;
}

void times( ActionData& action_data ) {
	double factor = getDouble(action_data, "Factor? ");
	action_data.getOutputImage() = action_data.getInputImage1() * factor; 
	return;
}

void divide( ActionData& action_data ) {
	double factor = getDouble(action_data, "Factor? ");
	action_data.getOutputImage() = action_data.getInputImage1() / factor; 
	return;
}

void grayFromRed(ActionData& action_data) {
	action_data.getInputImage1().grayFromRed(action_data.getOutputImage());
	return;
}

void grayFromGreen(ActionData& action_data) {
	action_data.getInputImage1().grayFromGreen(action_data.getOutputImage());
	return;
}

void grayFromBlue(ActionData& action_data) {
	action_data.getInputImage1().grayFromBlue(action_data.getOutputImage());
	return;
}

void grayFromLinearColorimetric(ActionData& action_data) {
	action_data.getInputImage1().grayFromLinearColorimetric(action_data.getOutputImage());
	return;
}

void sepiaFilter(ActionData& action_data){
	action_data.getInputImage1().sepiaFilter(action_data.getOutputImage());
	return;
}

void orangeFilter(ActionData& action_data) {
	action_data.getInputImage1().orangeFilter(action_data.getOutputImage());
	return;
}
