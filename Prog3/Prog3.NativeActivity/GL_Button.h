//---------------------------------------------------------------------------
// Author: Clifton
// GL code for creating and managing a graphical button.
//---------------------------------------------------------------------------

#ifndef __GL_BUTTON_H
#define __GL_BUTTON_H

//---------------------------------------------------------------------------
// This class creats a graphical button for an android app to a given
// location, given digit, and customably scale and color.
//---------------------------------------------------------------------------
class GL_Button
{
public:
   
   GL_Button(int posX, int posY, int digitDisp, float scale = 1.0,
      uint8_t rfg = 255, uint8_t gfg = 255, uint8_t bfg = 255, 
      uint8_t rbg = 100, uint8_t gbg = 100, uint8_t bbg = 100);
   
   void Draw();
   bool PressInside(int x, int y);

private:
   int xPos, yPos;              // Position of the button
   uint8_t rFG, gFG, bFG;       // Foreground color
   uint8_t rBG, gBG, bBG;       // Background color
   int digitDisplay;            // Digit to display as the caption
   float scaleAmt;              // How much to scale the button
   int numVerts;                // Total number of all the vertices
};

#endif

