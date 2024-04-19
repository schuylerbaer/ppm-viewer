#include "AppData.h"
#include "image_menu.h"

AppData::AppData(int height, int width) 
  : mHeight(height), mWidth(width),
    mNumColors(256), mColor1(204,255,255), mColor2(0,153,153),
    mA(0.0), mB(0.0),
    mMaxNumber(100),
    mMinX(-2.0), mMaxX(2.0), mMinY(-2.0), mMaxY(2.0),
    mInteractionMode(IM_FRACTAL), mFractalMode(M_JULIA),
    mMenuData(), mActionData(mInputStream, mOutputStream) {
    mActionData.setGrid(new ComplexFractal);   
    configureMenu(mMenuData);
    createJulia1();
}

void AppData::setSize(int height, int width) {
  mHeight = height;
  mWidth = width;
}

int AppData::getHeight() const {
  return mHeight;
}

int AppData::getWidth() const {
  return mWidth;
}

void AppData::createJulia1() {
  mA = -0.4;
  mB = 0.6;
  mMaxNumber = 402;
  mMinX = 0.385492;
  mMaxX = 0.406107;
  mMinY = 0.0238945;
  mMaxY = 0.0445096;

  mNumColors = 414;
  mColor1.setRed(70);
  mColor1.setGreen(124);
  mColor1.setBlue(194);
  mColor2.setRed(242);
  mColor2.setGreen(251);
  mColor2.setBlue(227);
  setColorTable();

  setInteractionMode(AppData::IM_FRACTAL);
  setFractalMode(AppData::M_JULIA);
  createFractal();
}

void AppData::createJulia2() {
  mA = 0.285;
  mB = 0.01;
  mMaxNumber = 1000;
  mMinX = -1.16917;
  mMaxX = 1.16917;
  mMinY = -1.16917;
  mMaxY = 1.16917;

  mNumColors = 256;
  mColor1.setRed(204);
  mColor1.setGreen(255);
  mColor1.setBlue(255);
  mColor2.setRed(5);
  mColor2.setGreen(23);
  mColor2.setBlue(88);
  setColorTable();

  setInteractionMode(AppData::IM_FRACTAL);
  setFractalMode(AppData::M_JULIA);
  createFractal();
}

void AppData::createMandelbrot1() {
  mMaxNumber = 2161;
  mMinX = -0.108809;
  mMaxX = -0.101835;
  mMinY = -0.928889;
  mMaxY = -0.921914;

  mNumColors = 83;
  mColor1.setRed(168);
  mColor1.setGreen(153);
  mColor1.setBlue(15);
  mColor2.setRed(84);
  mColor2.setGreen(17);
  mColor2.setBlue(14);
  setColorTable();

  setInteractionMode(AppData::IM_FRACTAL);
  setFractalMode(AppData::M_MANDELBROT);
  createFractal();
}

void AppData::createMandelbrot2() {
  mMaxNumber = 123;
  mMinX = -0.237211;
  mMaxX = -0.237069;
  mMinY = 0.812991;
  mMaxY = 0.813133;

  mNumColors = 37;
  mColor1.setRed(0);
  mColor1.setGreen(70);
  mColor1.setBlue(124);
  mColor2.setRed(74);
  mColor2.setGreen(236);
  mColor2.setBlue(41);
  setColorTable();

  setInteractionMode(AppData::IM_FRACTAL);
  setFractalMode(AppData::M_MANDELBROT);
  createFractal();
}

void AppData::createComplexFractal1() {
  mMaxNumber = 511;
  mMinX = -0.666408;
  mMaxX = 0.666408;
  mMinY = -0.817395;
  mMaxY = 0.515422;

  mNumColors = 10;
  mColor1.setRed(242);
  mColor1.setGreen(251);
  mColor1.setBlue(227);
  mColor2.setRed(50);
  mColor2.setGreen(13);
  mColor2.setBlue(183);
  setColorTable();

  setInteractionMode(AppData::IM_FRACTAL);
  setFractalMode(AppData::M_COMPLEX);
  createFractal();
}

void AppData::createComplexFractal2() {
  mMaxNumber = 2065;
  mMinX = -0.587833;
  mMaxX = 0.587833;
  mMinY = 0.823802;
  mMaxY = 1.99946;

  mNumColors = 10;
  mColor1.setRed(31);
  mColor1.setGreen(35);
  mColor1.setBlue(30);
  mColor2.setRed(9);
  mColor2.setGreen(224);
  mColor2.setBlue(121);
  setColorTable();

  setInteractionMode(AppData::IM_FRACTAL);
  setFractalMode(AppData::M_COMPLEX);
  createFractal();
}


void AppData::clearStreams() {
  mInputStream.str("");
  mInputStream.clear();
  mOutputStream.str("");
  mOutputStream.clear();
}

void AppData::runCommand(const std::string& choice) {
  takeAction(choice, mMenuData, mActionData);
}

void AppData::setColorTable() {
  std::string choice;

  //////////////////////////////////////////////
  clearStreams();
  choice = "set-color-table-size";
  {
	  std::stringstream tmp;
	  tmp << mNumColors;
	  mInputStream.str(tmp.str());	//copy
  }
  runCommand(choice);

  //////////////////////////////////////////////
  clearStreams();
  choice = "set-color-gradient";
  {
	  std::stringstream tmp;
	  tmp << 0 << " " << mColor1.getRed() << " " << mColor1.getGreen() << " " << mColor1.getBlue() << " "
	      << mNumColors-1 << " " << mColor2.getRed()  << " " << mColor2.getGreen() << " " << mColor2.getBlue();
	  mInputStream.str(tmp.str());
  }
  runCommand(choice);

}

void AppData::decreaseColorTableSize() {
  if(mNumColors > 10) {
    mNumColors /= 1.1;
    setColorTable();
    gridApplyColorTable();
  }
}

void AppData::increaseColorTableSize() {
  if(mNumColors < 1024) {
    mNumColors *= 1.1;
    setColorTable();
    gridApplyColorTable();
  }
}

void AppData::randomColor1() {
  int new_red = rand() % (256);
  int new_green = rand() % (256);
  int new_blue = rand() % (256);
  mColor1.setRed(new_red);
  mColor1.setBlue(new_blue);
  mColor1.setGreen(new_green);

  setColorTable();
  gridApplyColorTable();
}

void AppData::randomColor2() {
  int new_red = rand() % (256);
  int new_green = rand() % (256);
  int new_blue = rand() % (256);
  mColor2.setRed(new_red);
  mColor2.setBlue(new_blue);
  mColor2.setGreen(new_green);

  setColorTable();
  gridApplyColorTable();
}


void AppData::selectJulia() {
  clearStreams();
  runCommand("julia");
}

void AppData::selectMandelbrot() {
  clearStreams();
  runCommand("mandelbrot");
}

void AppData::selectComplexFractal() {
  clearStreams();
  runCommand("complex-fractal");
}


void AppData::juliaParameters(double a, double b) {
  clearStreams();
  {
    std::stringstream tmp;
    tmp << a << " " << b;
    mInputStream.str(tmp.str());
  }
  runCommand("julia-parameters");
}

void AppData::configureGrid(int max) {
  clearStreams();
  {
    std::stringstream tmp;
    tmp << mHeight << " " << mWidth << " " << max;
    mInputStream.str(tmp.str());
  }
  runCommand("grid");
}

void AppData::fractalPlaneSize(double x_min, double x_max, double y_min, double y_max) {
  clearStreams();
  {
    std::stringstream tmp;
    tmp << x_min << " " << x_max << " " << y_min << " " << y_max;
    mInputStream.str(tmp.str());
  }
  runCommand("fractal-plane-size");
}

void AppData::fractalCalculate() {
  clearStreams();
  runCommand("fractal-calculate");
}

void AppData::gridApplyColorTable() {
  clearStreams();
  runCommand("grid-apply-color-table");
}

PPM& AppData::getOutputImage() {
  return mActionData.getOutputImage();
}

ColorTable& AppData::getColorTable() {
  return mActionData.getTable();
}

void AppData::setInteractionMode(InteractionMode mode) {
  mInteractionMode = mode;
}

AppData::InteractionMode AppData::getInteractionMode() const {
  return mInteractionMode;
}

void AppData::zoomIn() {
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  mMinX += dx;
  mMaxX -= dx;
  mMinY += dy;
  mMaxY -= dy;
}

void AppData::zoomOut() {
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  if(mMinX - dx >= -2.0 && mMaxX + dx <= 2.0) {
    if(mMinY - dy >= -2.0 && mMaxY + dy <= 2.0) {
      mMinX -= dx;
      mMaxX += dx;
      mMinY -= dy;
      mMaxY += dy;
    }
  }
}

void AppData::moveLeft() {
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  if(mMinX-dx >= -2.0) {
    mMinX -= dx;
    mMaxX -= dx;
  }
}

void AppData::moveRight() {
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  if(mMinX-dx >= -2.0) {
    mMinX += dx;
    mMaxX += dx;
  }
}

void AppData::moveDown() {
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  if(mMinY-dy >= -2.0) {
    mMinY -= dy;
    mMaxY -= dy;
  }
}

void AppData::moveUp() {
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  if(mMinY-dy >= -2.0) {
    mMinY += dy;
    mMaxY += dy;
  }
}


void AppData::setFractalMode(FractalMode mode) {
  mFractalMode = mode;
}

AppData::FractalMode AppData::getFractalMode() const {
  return mFractalMode;
}

void AppData::increaseMaxNumber() {
  if(mMaxNumber < 2048) {
    mMaxNumber *= 1.1;
  }
}

void AppData::decreaseMaxNumber() {
  if(mMaxNumber > 11) {
    mMaxNumber /= 1.1;
  }
}


void AppData::setAB(int x, int y) {
  ComplexFractal *cfp = dynamic_cast<ComplexFractal *>(&mActionData.getGrid());
  if(mFractalMode == M_MANDELBROT && cfp != 0) {
    mA = mMinX + x * cfp->getDeltaX();
    mB = mMinY + y * cfp->getDeltaY();
  }
}

void AppData::resetPlane() {
  mMinX = -2.0;
  mMaxX = 2.0;
  mMinY = -2.0;
  mMaxY = 2.0;
}

void AppData::createFractal() {
  if(mFractalMode == M_MANDELBROT) {
    selectMandelbrot();
  } else if (mFractalMode == M_JULIA) {
    selectJulia();
    juliaParameters(mA, mB);
  } else if (mFractalMode == M_COMPLEX) {
    selectComplexFractal();
  }
  configureGrid(mMaxNumber);
  fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
  fractalCalculate();
  gridApplyColorTable();
}


