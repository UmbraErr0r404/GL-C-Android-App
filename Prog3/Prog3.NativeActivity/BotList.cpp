#include "BotList.h"

BotList::BotList()
{
   BotArray[MAX_NUM_BOTS]; 
}

BotList::~BotList()
{
   for(int i = 0; i < numElements; i++)
      delete BotArray[numElements];
   delete BotArray;
}

void BotList::Add(const VBot *& aBotP)
{
   if( numElements < MAX_NUM_BOTS)
      BotArray[numElements++]; 
}

void BotList::DoBattles()
{

}
