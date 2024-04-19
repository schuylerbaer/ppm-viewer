#ifndef _APPDATA_H_
#define _APPDATA_H_

#include "ActionData.h"
#include "MenuData.h"
#include <sstream>

class AppData {
public:
  enum InteractionMode { IM_FRACTAL, IM_COLORTABLE };
  enum FractalMode { M_MANDELBROT, M_JULIA, M_COMPLEX };

  AppData(int height, int width);
  void setSize(int height, int width);
  int getHeight() const;
  int getWidth() const;

  void createJulia1();
  void createJulia2();
  void createMandelbrot1();
  void createMandelbrot2();
  void createComplexFractal1();
  void createComplexFractal2();

  void clearStreams();
  void runCommand(const std::string& choice);

  void setColorTable();
  void decreaseColorTableSize();
  void increaseColorTableSize();
  void randomColor1();
  void randomColor2();

  void selectJulia();
  void selectMandelbrot();
  void selectComplexFractal();
  void juliaParameters(double a, double b);
  void configureGrid(int max);
  void fractalPlaneSize(double x_min, double x_max, double y_min, double y_max);
  void fractalCalculate();
  void gridApplyColorTable(); 

  PPM& getOutputImage();
  ColorTable& getColorTable();

  void setInteractionMode(InteractionMode mode);
  InteractionMode getInteractionMode() const;

  void zoomIn();
  void zoomOut();
  void moveLeft();
  void moveRight();
  void moveDown();
  void moveUp();

  void setFractalMode(FractalMode mode);
  FractalMode getFractalMode() const;

  void increaseMaxNumber();
  void decreaseMaxNumber();

  void setAB(int x, int y);
  void resetPlane();

  void createFractal();

protected:
  int mHeight, mWidth;
  int mNumColors;
  Color mColor1, mColor2;
  double mA, mB;
  int mMaxNumber;
  double mMinX, mMaxX, mMinY, mMaxY;
  InteractionMode mInteractionMode;
  FractalMode mFractalMode;

  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  MenuData mMenuData;
  ActionData mActionData;
};

#endif /* _APPDATA_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
