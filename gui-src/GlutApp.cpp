#include "GlutApp.h"
#include "glut_app.h"
#include "image_menu.h"
#include "AppData.h"

GlutApp::GlutApp(int height, int width)
  : mData(height, width) {
}

void GlutApp::setSize(int height, int width) {
  mData.setSize(height, width);
  mData.createFractal();
}

int GlutApp::getHeight() const {
  return mData.getHeight();
}
int GlutApp::getWidth() const {
  return mData.getWidth();
}

void GlutApp::display() {
  if(mData.getInteractionMode() == AppData::IM_FRACTAL) {
    displayOutputImage();
  } else if(mData.getInteractionMode() == AppData::IM_COLORTABLE) {
    displayColorTable();
  }
}

void GlutApp::displayOutputImage() {
  PPM& p = mData.getOutputImage();
  double max = static_cast<double>(p.getMaxColorValue());
  double r, g, b;
  int row, column;
  glBegin( GL_POINTS );
  for(row = 0; row < p.getHeight(); row++) {
    for(column = 0; column < p.getWidth(); column++) {
      r = p.getChannel(row, column, 0) / max;
      g = p.getChannel(row, column, 1) / max;
      b = p.getChannel(row, column, 2) / max;
      glColor3d(r, g, b); //3d means three doubles
      glVertex2i(column, p.getHeight()-row-1); //2i means two integers. gl (0, 0) bottom left
    }
  }
  glEnd( );
}

void GlutApp::displayColorTable() {
  PPM& p = mData.getOutputImage();
  double max = static_cast<double>(p.getMaxColorValue());
  double r, g, b;
  int i;
  int row, column;
  glBegin( GL_POINTS );
  for(row = 0; row < p.getHeight(); row++) {
    for(column = 0; column < p.getWidth(); column++) {
      i = column * mData.getColorTable().getNumberOfColors() / mData.getWidth();
      r = mData.getColorTable()[i].getRed() / max;
      g = mData.getColorTable()[i].getGreen() / max;
      b = mData.getColorTable()[i].getBlue() / max;
      glColor3d(r, g, b); //3d means three doubles
      glVertex2i(column, p.getHeight()-row-1); //2i means two integers. gl (0, 0) bottom left
    }
  }
  glEnd( );
}

bool GlutApp::keyboard(unsigned char c) {
  bool display = false;
  switch(c) {
  case 'J':
    mData.createJulia1();
    display = true;
    break;
  case 'j':
    mData.createJulia2();
    display = true;
    break;
  case 'M':
    mData.createMandelbrot1();
    display = true;
    break;
  case 'm':
    mData.createMandelbrot2();
    display = true;
    break;
  case 'C':
    mData.createComplexFractal1();
    display = true;
    break;
  case 'c':
    mData.createComplexFractal2();
    display = true;
    break;
  case 'T':
    mData.setInteractionMode(AppData::IM_COLORTABLE);
    display = true;
    break;
  case 't':
    mData.setInteractionMode(AppData::IM_FRACTAL);
    display = true;
    break;
  case 'b':
    mData.setFractalMode(AppData::M_MANDELBROT);
    mData.createFractal();
    display = true;
    break;
  case 'n':
    mData.setFractalMode(AppData::M_JULIA);
    mData.createFractal();
    display = true;
    break;
  case 'F':
    mData.setFractalMode(AppData::M_COMPLEX);
    mData.createFractal();
    display = true;
    break;
  case '.':
  case '>':
    mData.increaseColorTableSize();
    display = true;
    break;
  case ',':
  case '<':
    mData.decreaseColorTableSize();
    display = true;
    break;
  case 'r':
    if(mData.getInteractionMode() == AppData::IM_COLORTABLE) {
      mData.randomColor1();
      display = true;
    }
    break;
  case 'R':
    if(mData.getInteractionMode() == AppData::IM_COLORTABLE) {
      mData.randomColor2();
      display = true;
    } else if(mData.getInteractionMode() == AppData::IM_FRACTAL) {
      mData.resetPlane();
      mData.createFractal();
      display = true;
    }
    break;
  case 'z':
    mData.zoomIn();
    mData.createFractal();
    display = true;
    break;
  case 'Z':
    mData.zoomOut();
    mData.createFractal();
    display = true;
    break;
  case '+':
  case '=':
    mData.increaseMaxNumber();
    mData.createFractal();
    display = true;
    break;
  case '-':
  case '_':
    mData.decreaseMaxNumber();
    mData.createFractal();
    display = true;
    break;
  default:
    break;
  }
  return display;
}

bool GlutApp::special(unsigned char c) {
  bool display = false;
  switch(c) {
  case GLUT_KEY_LEFT:
    mData.moveLeft();
    mData.createFractal();
    display = true;
    break;
  case GLUT_KEY_RIGHT:
    mData.moveRight();
    mData.createFractal();
    display = true;
    break;
  case GLUT_KEY_DOWN:
    mData.moveDown();
    mData.createFractal();
    display = true;
    break;
  case GLUT_KEY_UP:
    mData.moveUp();
    mData.createFractal();
    display = true;
    break;
  default:
    break;
  }
  return display;
}

bool GlutApp::mouse(int mouse_button, int state, int x, int y) {
  bool display = false;
  bool mode = false;
  if (mData.getInteractionMode() == AppData::IM_FRACTAL && mData.getFractalMode() == AppData::M_MANDELBROT) {
	  mode = true;
  }
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mode) {
    mData.setAB(x, y);
    mData.setFractalMode(AppData::M_JULIA);
    mData.createFractal();
    display = true;
  }
  return display;
}

