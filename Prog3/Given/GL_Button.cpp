// TODO: Put a file comment block at the top


#include "GL_Button.h"
#include "IntegerDisplay.h"

// Sets the size.
#define BUTTON_WIDTH  20
#define BUTTON_HEIGHT 28

// Render as two triangles
static GLfloat btnVerts[] =
{
   0, 0, 0, BUTTON_HEIGHT, BUTTON_WIDTH, 0,
   BUTTON_WIDTH, 0, 0, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT,
};


GL_Button::GL_Button(int posX, int posY, int digitDisp, float scale,
   uint8_t rfg, uint8_t gfg, uint8_t bfg,
   uint8_t rbg, uint8_t gbg, uint8_t bbg) : xPos(posX), yPos(posY),
   rFG(rfg), gFG(gfg), bFG(bfg), rBG(rbg), gBG(gbg), bBG(bbg),
    digitDisplay(digitDisp), scaleAmt(scale)
{
   numVerts = sizeof(btnVerts) / sizeof(GLfloat) / 2;
}

bool GL_Button::PressInside(int x, int y)
{
   return x >= xPos && y >= yPos &&
      x < (xPos + scaleAmt * BUTTON_WIDTH) &&
      y < (yPos + scaleAmt * BUTTON_HEIGHT);
}

// 
void GL_Button::Draw()
{
   // Translate to the postion for Button and scale if requseted
   glLoadIdentity();
   glTranslatef(xPos, yPos, 0);
   glScalef(scaleAmt, scaleAmt, 1);

   // Set the background color.  Leave Alpha at 255
   glColor4ub(rBG, gBG, bBG, 255);

   // Set the pointer to the vertices
   glVertexPointer(2, GL_FLOAT, 0, btnVerts);

   // Enable the vertex states, draw, then disable.
   glEnableClientState(GL_VERTEX_ARRAY);
   glDrawArrays(GL_TRIANGLES, 0, numVerts);
   glDisableClientState(GL_VERTEX_ARRAY);

   // Draw the digit as the button Caption
   IntegerDisplay::Instance()->DisplayIntAt(xPos + 
      scaleAmt * BUTTON_WIDTH / 4,
      yPos + scaleAmt * BUTTON_HEIGHT / 4, digitDisplay, scaleAmt,
      rFG, gFG, bFG);
}

