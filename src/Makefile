# target_file: dependency1 dependency2 ...
# tab command
CXX      := g++
CXXFLAGS := -std=c++11
CXXFLAGS := $(CXXFLAGS) -Wall -Wpedantic -Wextra -Werror

all: hello questions_3 ascii_image image_file four_square flag_romania ppm_menu

hello: hello.o
	$(CXX) $(CXXFLAGS) -o $@ $^

questions_3: questions_3.o controllers.o user_io.o Image.o image_output.o image_drawing.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^

ascii_image: ascii_image.o controllers.o user_io.o Image.o image_output.o image_drawing.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^

image_file: PPM.o image_output.o image_drawing.o controllers.o image_file.o user_io.o Image.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^

four_square: PPM.o image_output.o image_drawing.o controllers.o user_io.o Image.o four_square.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^

flag_romania: PPM.o image_output.o image_drawing.o controllers.o user_io.o Image.o flag_romania.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^

ppm_menu: PPM.o image_output.o image_drawing.o controllers.o user_io.o Image.o ppm_menu.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^

hello.o: hello.cpp
	$(CXX) $(CXXFLAGS) -c $<

questions_3.o: questions_3.cpp
	$(CXX) $(CXXFLAGS) -c $<

controllers.o: controllers.cpp
	$(CXX) $(CXXFLAGS) -c $<

user_io.o: user_io.cpp
	$(CXX) $(CXXFLAGS) -c $<

ascii_image.o: ascii_image.cpp
	$(CXX) $(CXXFLAGS) -c $<

Image.o: Image.cpp
	$(CXX) $(CXXFLAGS) -c $<

image_output.o: image_output.cpp
	$(CXX) $(CXXFLAGS) -c $<

image_drawing.o: image_drawing.cpp
	$(CXX) $(CXXFLAGS) -c $<

PPM.o: PPM.cpp
	$(CXX) $(CXXFLAGS) -c $<

image_file.o: image_file.cpp
	$(CXX) $(CXXFLAGS) -c $<

four_square.o: four_square.cpp
	$(CXX) $(CXXFLAGS) -c $<

flag_romania.o: flag_romania.cpp
	$(CXX) $(CXXFLAGS) -c $<

ActionData.o: ActionData.cpp
	$(CXX) $(CXXFLAGS) -c $<

MenuData.o: MenuData.cpp
	$(CXX) $(CXXFLAGS) -c $<

ppm_menu.o: ppm_menu.cpp
	$(CXX) $(CXXFLAGS) -c $<

image_filters.o: image_filters.cpp
	$(CXX) $(CXXFLAGS) -c $<

NumberGrid.o: NumberGrid.cpp
	$(CXX) $(CXXFLAGS) -c $<

ColorTable.o: ColorTable.cpp
	$(CXX) $(CXXFLAGS) -c $<

ComplexFractal.o: ComplexFractal.cpp
	$(CXX) $(CXXFLAGS) -c $<

JuliaSet.o: JuliaSet.cpp
	$(CXX) $(CXXFLAGS) -c $<

MandelbrotSet.o: MandelbrotSet.cpp
	$(CXX) $(CXXFLAGS) -c $<

ThreadedGrid.o: ThreadedGrid.cpp
	$(CXX) $(CXXFLAGS) -c $<
clean:
	-rm -f *.o *~
	-rm -f hello questions_3 ascii_image image_file four_square flag_romania ppm_menu
