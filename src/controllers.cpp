#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "MenuData.h"
#include "NumberGrid.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include <iostream>
#include <vector>
#include <string>

int assignment1( std::istream& is, std::ostream& os ) {
	ActionData action_data(is, os);
	int value = askQuestions3(action_data);
	return value;
}

int assignment2( std::istream& is, std::ostream& os ) {
	ActionData action_data(is, os);
	diagonalQuadPattern(action_data);	
	copyImage(action_data);
	drawAsciiImage(action_data);
	return 0;
}

int assignment3( std::istream& is, std::ostream& os ) {
	ActionData action_data(is, os);
	stripedDiagonalPattern(action_data);
	copyImage(action_data);
	writeUserImage(action_data);
	return 0;
}

int four_square( std::istream& is, std::ostream& os ) {
	ActionData action_data(is, os);
	fourSquarePattern(action_data);
	copyImage(action_data);
	writeUserImage(action_data);
	return 0;
}

int flag_romania( std::istream& is, std::ostream& os ) {
	ActionData action_data(is, os);
	flagRomaniaPattern(action_data);
	copyImage(action_data);
	writeUserImage(action_data);
	return 0;
}

void showMenu( MenuData& menu_data, ActionData& action_data ) {
	long unsigned int i;
	for(i = 0; i < menu_data.getNames().size(); i++) {
		action_data.getOS() << menu_data.getNames()[i] << ") " << menu_data.getDescription(menu_data.getNames()[i]) << std::endl;
	}
}

void takeAction(const std::string& choice, MenuData& menu_data, ActionData& action_data) {
	ActionFunctionType action = menu_data.getFunction(choice);
	if(action != 0) {
		action(action_data);
	} else if(choice == "menu") {
		showMenu(menu_data, action_data);
	} else {
		action_data.getOS() << "Unknown action '" << choice << "'." << std::endl;
	}
}

void configureMenu( MenuData& menu_data ) {
	std::vector<std::string> names = { "draw-ascii", "write", "copy", "read1", "#", "size", "max-color-value", "channel", "pixel", "clear", "quit", "read2", "+", "+=", "-", "-=", "*", "*=", "/", "/=", "red-gray", "green-gray", "blue-gray", "linear-gray", "circle", "box", "test-pattern", "diagonal-quad", "striped-diagonal", "sepia", "orange", "square", "copy12", "copy21", "grid", "grid-set", "grid-apply", "set-color-table-size", "set-color", "set-random-color", "set-color-gradient", "grid-apply-color-table", "fractal-plane-size", "julia-parameters", "complex-fractal", "julia", "mandelbrot", "mandelbrot-power", "set-mandelbrot-power", "set-inverted-color-gradient", "julia-four", "set-easy-random-color-gradient", "fractal-calculate", "fractal-calculate-single-thread" };

	std::vector<ActionFunctionType> funcs { drawAsciiImage, writeUserImage, copyImage, readUserImage1, commentLine, setSize, setMaxColorValue, setChannel, setPixel, clearAll, quit, readUserImage2, plus, plusEquals, minus, minusEquals, times, timesEquals, divide, divideEquals, grayFromRed, grayFromGreen, grayFromBlue, grayFromLinearColorimetric, drawCircle, drawBox, drawTestColorPattern, diagonalQuadPattern, stripedDiagonalPattern, sepiaFilter, orangeFilter, drawSquare, copyImage1ToImage2, copyImage2ToImage1, configureGrid, setGrid, applyGrid, setColorTableSize, setColor, setRandomColor, setColorGradient, applyGridColorTable, setFractalPlaneSize, setJuliaParameters, setComplexFractal, setJuliaFractal, setMandelbrotFractal, setMandelbrotPowerFractal, setMandelbrotPower, setInvertedColorGradient, setJuliaFourFractal, setEasyRandomColorGradient, calculateFractal, calculateFractalSingleThread };

	std::vector<std::string> descriptions { "Write output image to terminal as ASCII art.", "Write output image to file.", "Copy input image 1 to output image.", "Read file into input image 1.", "Comment to end of line.", "Set the size of input image 1.", "Set the max color value of input image 1.", "Set a channel value in input image 1.", "Set a pixel's 3 values in input image 1.", "Set all pixels to 0,0,0 in input image 1.", "Quit.", "Read file into input image 2.", "Set output image from sum of input image 1 and input image 2.", "Set input image 1 by adding in input image 2.", "Set output image from difference of input image 1 and input image 2.", "Set input image 1 by subtracting input image 2.", "Set output image from input image 1 multiplied by a number.", "Set input image 1 by multiplying by a number.", "Set output image from input image 1 divided by a number.", "Set input image 1 by dividing by a number.", "Set output image by grayscale from red on input image 1.", "Set output image by grayscale from green on input image 1.", "Set output image by grayscale from blue on input image 1.", "Set output image by linear colorimetric grayscale on input image 1.", "Draw a circle shape in input image 1.", "Draw a box shape in input image 1.", "Draw a test pattern in input image 1.", "Draw a diagonal quad pattern in input image 1.", "Draw a striped diagonal pattern in input image 1.", "Set output image from sepia filter on input image 1.", "Set output image from orange filter on input image 1.", "Draw a square shape in input image 1.", "Copy input image 1 to input image 2.", "Copy input image 2 to input image 1.", "Configure the grid.", "Set a single value in the grid.", "Use the grid values to set colors in the output image.", "Change the number of slots in the color table.", "Set the RGB values for one slot in the color table.", "Randomly set the RGB values for one slot in the color table.", "Smoothly set the RGB values for a range of slots in the color table.", "Use the grid values to set colors in the output image using the color table.", "Set the dimensions of the grid in the complex plane.", "Set the parameters of the Julia Set function.", "Choose to make a complex plane.", "Choose to make a Julia set.", "Choose to make a Mandelbrot set.", "Choose to make a Mandelbrot set with the power function.", "Choose a power for the Mandelbrot power function.", "Smoothly set the values for a range of slots in the color table, using a color and its inverse.", "Choose to make a Julia set with the fourth power function.", "Smoothly set the values for a range of slots in the color table, using two random colors.", "Calculate the escape values for the fractal.", "Calculate the escape values for the fractal, single-thread." };

	unsigned long int i;
	for(i = 0; i < names.size(); i++) {
		menu_data.addAction(names[i], funcs[i], descriptions[i]);
	}
}

int imageMenu(std::istream& is, std::ostream& os) {
	ActionData action_data(is, os);
	action_data.setGrid(new ComplexFractal);
	MenuData menu_data;
	configureMenu(menu_data);
	do {
		takeAction(getChoice(action_data), menu_data, action_data);
	}
	while (action_data.getDone() == false && action_data.getIS().good());
	return 0;
}

//assignment 11
void setComplexFractal( ActionData& action_data ) {
	action_data.setGrid(new ComplexFractal);
}

void setJuliaFractal( ActionData& action_data ) {
	action_data.setGrid(new JuliaSet);
}

void setMandelbrotFractal( ActionData& action_data ) {
	action_data.setGrid(new MandelbrotSet);
}

//practice-test
void setMandelbrotPowerFractal(ActionData& action_data) {
	action_data.setGrid(new MandelbrotPower);
}

//test 3
void setJuliaFourFractal(ActionData& action_data) {
	action_data.setGrid(new JuliaSetFour);
}

