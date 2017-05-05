//---------------------------------------------------------------------------
// Author: Clifton
//
//
//---------------------------------------------------------------------------

// TODO: Put a file comment block at the top, 
// class comment on the class, and method comment blocks on each.


// This uses a 7-segment type approach.
// It uses the singleton pattern.
// Make call as: IntegerDisplay::Instance()->DisplayIntAt(....


#ifndef __INTEGER_DISPLAY_H
#define __INTEGER_DISPLAY_H

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class IntegerDisplay
{
public:
   static void Initialize() { delete _instance; _instance = NULL; }
   static IntegerDisplay * Instance();
   void DisplayIntAt(int xPos, int yPos, unsigned int val, float scale = 1.0,
      uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255);

   // Draws a rectangle around an int displayed with the same 
   // first four parameters.
   void DrawBoundingRect(int xPos, int yPos, unsigned int val, float scale = 1.0,
      uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255);

   // Draws a line segment. Doesn't really belong in an integer package,
   // but with a line, you can make anything!
   void DrawLine(int x1, int y1, int x2, int y2, float width = 1.0,
      uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255);


private:

   // Private constructor.  Can't directly make instances.
   IntegerDisplay();               

   static IntegerDisplay * _instance;

   static const int NUMDIGS = 10;
   GLfloat * vertices;             // All the vertices for all the digits
   int digitOffsets[NUMDIGS];      // Offset for digit into vertices
   int totalVerts;                 // Total number of all the vertices
   int numVerts[NUMDIGS];          // Number of vertices for each digit
   
   void InitSegs();
   
   void DisplayDigitAt(int xPos, int yPos, int digit, float scale, 
      uint8_t red, uint8_t green, uint8_t blue);
};

#endif

