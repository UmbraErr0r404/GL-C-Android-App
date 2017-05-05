//------------------------------------------------------------------------------
// Comment block goes here
//------------------------------------------------------------------------------

#include "vbot.h"

// Don't rewrite or override this one! 
bool VBot::InitGraphics()
{
   try
   {
      // Call to Virtual function that sets up the vertex and color data
      // This will be auto-generated for you by the CreateBotData program.
      // Follow the instructions in that auto-generated file.
      SetUpData();

      // Set up the Virtual Buffer Objects to load the vertex and color data.
      glGenBuffers(1, &vboVertexHandle);
      glBindBuffer(GL_ARRAY_BUFFER, vboVertexHandle);
      glBufferData(GL_ARRAY_BUFFER, 2 * numPoints * sizeof(GLfloat),
         vertices, GL_STATIC_DRAW);
      glGenBuffers(1, &vboColorHandle);
      glBindBuffer(GL_ARRAY_BUFFER, vboColorHandle);
      glBufferData(GL_ARRAY_BUFFER, 4 * numPoints * sizeof(GLubyte),
         colors, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);    // unbind the array buffer
      return true;
   }
   catch (...)
   {
      return false;
   }
}

// Don't rewrite or override this one! 
void VBot::Draw()
{ 
   // Translate to the postion for the VBot
   glLoadIdentity();
   glTranslatef(xPos, yPos, 0);

   // Set up the pointers for Vertices and Colors
   // Bind the buffer, then set up the pointer for that buffer.
   glBindBuffer(GL_ARRAY_BUFFER, vboVertexHandle);
   glVertexPointer(2, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, vboColorHandle);
   glColorPointer(4, GL_UNSIGNED_BYTE, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);    // unbind the array buffer

   // Enable the vertex and color states, draw, then disable.
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glDrawArrays(GL_POINTS, 0, numPoints);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
}

// Don't rewrite or override this one! 
bool VBot::CollidedWith ( VBot * b ) const
{
   if (b == NULL)
      return false;

   return   ( xPos + width ) >= b->xPos
         && ( b->xPos + b->width ) >= xPos
         && ( yPos + height ) >= b->yPos
         && ( b->yPos + b->height ) >= yPos;

}

// Don't override this one, but you can modify 
// what's here it if you want.
// Make sure you have good reasons for any changes!
void VBot::DoBattleWith ( VBot * b )
{
   int mine = EnergyToFightWith();
   int yours = b->EnergyToFightWith();
   if( mine == yours )
   {
      energy = energy - mine / 2;
      b->energy = b->energy - yours / 2;
   }
   else if ( mine > yours )
   {
      if ( b->energy > 1 )
      {
         b->energy = b->energy - yours;
         energy = energy + yours / 2;
      }
      else
      {
         b->energy = b->energy - 1;
         energy = energy + 1;
      }
   }
   else
   {
      if ( energy > 1 )
      {
         energy = energy - mine;
         b->energy = b->energy + mine / 2;
      }
      else
      {
         b->energy = b->energy + 1;
         energy = energy - 1;
      }
   }
}

