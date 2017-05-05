//---------------------------------------------------------------------------
// Author: Clifton
//
//
//---------------------------------------------------------------------------
// TODO: Put a file comment block at the top


// This is a 7-segment display type of approach to creating digits.
// They are very crude, but good enough for our purposes.

#include "IntegerDisplay.h"

// Sets the size and spacing of a digit display.
#define MAX_X  10
#define MAX_Y  14
#define SPACING 5

IntegerDisplay * IntegerDisplay::_instance = NULL;

IntegerDisplay::IntegerDisplay()
{
   InitSegs();
}

IntegerDisplay * IntegerDisplay::Instance()
{
   if (_instance == NULL)
      _instance = new IntegerDisplay();
   return _instance;
}

void IntegerDisplay::DisplayIntAt(int xPos, int yPos, unsigned int val,
   float scale, uint8_t red, uint8_t green, uint8_t blue)
{
   // Set the Color.  255 is the alpha
   glColor4ub(red, green, blue, 255);

   if (val >= NUMDIGS)
      DisplayIntAt(xPos - scale * (MAX_X + SPACING), 
         yPos, val / NUMDIGS, scale, red, green, blue);
   DisplayDigitAt(xPos, yPos, val % NUMDIGS, scale, red, green, blue);
}

// Draws a rectangle around an int displayed with the same 
// first four parameters.
void IntegerDisplay::DrawBoundingRect(int xPos, int yPos, unsigned int val, float scale,
   uint8_t red, uint8_t green, uint8_t blue)
{
   int topY = yPos - scale * SPACING;               // A little above the number
   int bottomY = yPos + scale * (MAX_Y + SPACING);  // A little below the number
   int rightX = xPos + scale * (MAX_X + SPACING);   // A little to the right of the last digit

   int numDigits = 0;
   if (val == 0)
      numDigits = 1;
   else
   {
      int num = val;
      while (num > 0)
      {
         ++numDigits;
         num /= 10;
      }
   }
   --numDigits;  // xPos is already at relative (0,0) for the left-most digit, so only need to account for the others.
   int leftX = xPos - numDigits * scale * (MAX_X + SPACING) - 2 * SPACING;  // A little to the left of the left-most digit

   short verts[] = { leftX, bottomY, leftX, topY, rightX, topY, rightX, bottomY };
   glLineWidth(3.0);  // You can change this if you like thicker lines.  I didn't want to add another param.
   glColor4ub(red, green, blue, 255);
   glVertexPointer(2, GL_SHORT, 0, verts);
   glLoadIdentity();
   glEnableClientState(GL_VERTEX_ARRAY);
   glDrawArrays(GL_LINE_LOOP, 0, 4);
   glEnableClientState(GL_VERTEX_ARRAY);
}

void IntegerDisplay::DrawLine(int x1, int y1, int x2, int y2, float width,
   uint8_t red, uint8_t green, uint8_t blue)
{
   short verts[] = { x1, y1, x2, y2 };
   glLineWidth(width);
   glColor4ub(red, green, blue, 255);
   glLoadIdentity();
   glVertexPointer(2, GL_SHORT, 0, verts);
   glEnableClientState(GL_VERTEX_ARRAY);
   glDrawArrays(GL_LINES, 0, 2);
   glEnableClientState(GL_VERTEX_ARRAY);
}


void IntegerDisplay::DisplayDigitAt(int xPos, int yPos, int digit, 
   float scale, uint8_t red, uint8_t green, uint8_t blue)
{
   // Translate to the postion for Digit
   glLoadIdentity();
   glTranslatef(xPos, yPos, 0);
   glScalef(scale, scale, 1);

   // Set the pointer to the vertices
   glVertexPointer(2, GL_FLOAT, 0, vertices + digitOffsets[digit]);

   // Enable the vertex states, draw, then disable.
   glEnableClientState(GL_VERTEX_ARRAY);
   glDrawArrays(GL_LINES, 0, numVerts[digit]);
   glDisableClientState(GL_VERTEX_ARRAY);
}


 /*  Assume the following and draw the appropriate segments to make a digit

      (0,0)   |--------------| (MAX_X,0)
              |              |
              |              |
              |              |
              |              |
 (0,MAX_Y/2)  |--------------| (MAX_X,MAX_Y/2) 
              |              |
              |              |
              |              |
              |              |
   (0,MAX_Y)  |--------------|  (MAX_X,MAX_Y)
   
*/

static GLfloat digitVerts[] =
{
   // Zero
   0, 0, MAX_X, 0,
   MAX_X, 0, MAX_X, MAX_Y,
   MAX_X, MAX_Y, 0, MAX_Y,
   0, MAX_Y, 0, 0,

   // One:  This is the only digit that will violate
   //       the 7-segment format and instead go down the middle.
   MAX_X / 2, 0, MAX_X / 2, MAX_Y,

   // Two
   0, 0, MAX_X, 0,
   MAX_X, 0, MAX_X, MAX_Y / 2,
   MAX_X, MAX_Y / 2, 0, MAX_Y / 2,
   0, MAX_Y / 2,  0, MAX_Y,
   0, MAX_Y, MAX_X, MAX_Y,

   // Three
   MAX_X, 0, MAX_X, MAX_Y,
   0, 0, MAX_X, 0,
   0, MAX_Y / 2, MAX_X, MAX_Y / 2,
   0, MAX_Y, MAX_X, MAX_Y,

   // Four
   0, 0, 0, MAX_Y / 2, 
   0, MAX_Y / 2, MAX_X, MAX_Y / 2,
   MAX_X, 0, MAX_X, MAX_Y,

   // Five
   MAX_X, 0, 0, 0,
   0, 0, 0, MAX_Y / 2,
   0, MAX_Y / 2, MAX_X, MAX_Y / 2,
   MAX_X, MAX_Y / 2, MAX_X, MAX_Y,
   MAX_X, MAX_Y, 0, MAX_Y,

    // Six
   MAX_X, 0, 0, 0, 
   0, 0, 0, MAX_Y,
   0, MAX_Y, MAX_X, MAX_Y,
   MAX_X, MAX_Y, MAX_X, MAX_Y / 2,
   MAX_X, MAX_Y / 2, 0, MAX_Y / 2,

   // Seven
   0, 0, MAX_X, 0,
   MAX_X, 0, MAX_X, MAX_Y,

   // Eight
   // TODO: You make this one.  Do it in 5 segments.   -----------------------------------------------------------------------
   0, 0, MAX_X, 0, 
   MAX_X, 0, MAX_X, MAX_Y,
   MAX_X, MAX_Y, 0, MAX_Y,
   0, MAX_Y, 0, 0,
   0, MAX_Y / 2, MAX_X, MAX_Y / 2,

   // Nine
   MAX_X, 0, 0, 0,
   0, 0, 0, MAX_Y / 2,
   0, MAX_Y / 2, MAX_X, MAX_Y / 2,
   MAX_X, 0, MAX_X, MAX_Y
};


void IntegerDisplay::InitSegs()
{
   vertices = digitVerts;
   
   // Set these manually using the Digits data.
   // This could be done more generally, but that is more work.
   numVerts[0] = 8;
   numVerts[1] = 2;
   numVerts[2] = 10;
   numVerts[3] = 8;
   numVerts[4] = 6;
   numVerts[5] = 10;
   numVerts[6] = 10;
   numVerts[7] = 4;
   numVerts[8] = 10;
   numVerts[9] = 8;

   // Set digitOffsets for each digit and also set totalVerts
   totalVerts = 0;
   for (int i = 0; i < NUMDIGS; i++)
   {
      digitOffsets[i] = 2 * totalVerts;
      totalVerts += numVerts[i];
   }

}