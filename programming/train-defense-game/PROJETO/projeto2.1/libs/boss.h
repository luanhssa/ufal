#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED




int MOVEMD_BOSS(int x)
{
    if(x>1234)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int MOVEME_BOSS(int x)
{
    if(x-1>0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void MOVIMENTOX_BOSS(int Personagem , int ini_atual ,OBJETO_MOVEL *inimigo,int qt_ini ,OBJETO_MOVEL *tiro,int qt_tiro)
{
	int MOVIMENTO=0;
	int i;
	int DIRECAO = 0;
	int y=0, k;

	for (i=0;i<qt_tiro;i++)
	{
		if(tiro[i].estado==EST_ATIVO)
		{
			if(tiro[i].x>=inimigo[ini_atual].x-7 && tiro[i].x<=inimigo[ini_atual].x+96+4)
			{
				MOVIMENTO=1;
				break;
			}
		}
	}

	if(MOVIMENTO==1)
	{
		for(i=0;i<qt_tiro;i++)
		{
			if(tiro[i].estado==EST_ATIVO)
			{
				if(y < tiro[i].y && tiro[i].y > inimigo[ini_atual].y && tiro[i].x>=inimigo[ini_atual].x-7 && tiro[i].x<=inimigo[ini_atual].x+96+4)
				{
					y = tiro[i].y;
					if(tiro[i].x>inimigo[ini_atual].x+45)
					{
						DIRECAO=-1;
						break;
					}
					else
					{
					   DIRECAO=1;
					   break;
					}
				}
			}
		}
		MOVIMENTO=0;
		for(i=0;i<qt_ini;i++)
        {
            if(i!=ini_atual)
            {
                if(inimigo[ini_atual].y<=inimigo[i].y+54&&inimigo[ini_atual].y>=inimigo[i].y-54)
                {
                    if((inimigo[i].x>inimigo[ini_atual].x-96&&inimigo[i].x<inimigo[ini_atual].x+130))
                    {
                        if(inimigo[i].x>inimigo[ini_atual].x)
                        {
                            MOVIMENTO;
                        }
                        else
                        {
                            MOVIMENTO+=1;
                        }
                    }
                }
            }
        }
        if(MOVIMENTO==0)
        {
            if(DIRECAO>0&&MOVEMD_BOSS(inimigo[ini_atual].x))
            {
                inimigo[ini_atual].x+=1;
            }
            else if(DIRECAO<0&&MOVEME_BOSS(inimigo[ini_atual].x))
            {
                inimigo[ini_atual].x-=1;
            }
        }
        else if(MOVIMENTO>0&&MOVEMD_BOSS(inimigo[ini_atual].x))
        {
            inimigo[ini_atual].x+=1;
        }
        else if(MOVIMENTO<0&&MOVEME_BOSS(inimigo[ini_atual].x))
        {
            inimigo[ini_atual].x-=1;
        }



	}
 	else
	{
        DIRECAO=0;
        for(i=0;i<qt_ini;i++)
        {
            if(i!=ini_atual)
            {
                if(inimigo[ini_atual].y<=inimigo[i].y+54&&inimigo[ini_atual].y>=inimigo[i].y-54)
                {
                    if((inimigo[i].x>inimigo[ini_atual].x-96&&inimigo[i].x<inimigo[ini_atual].x+130))
                    {
                        if(inimigo[i].x>inimigo[ini_atual].x)
                        {
                            DIRECAO-=1;
                        }
                        else
                        {
                            DIRECAO+=1;
                        }
                    }
                }
            }
        }
        if(!(DIRECAO==0))
        {
            if(DIRECAO>0&&MOVEMD_BOSS(inimigo[ini_atual].x))
            {
                inimigo[ini_atual].x+= 2;
            }
            else if(MOVEME_BOSS(inimigo[ini_atual].x))
            {
                inimigo[ini_atual].x+= -2;
            }
        }
        else
        {
            if(inimigo[ini_atual].x<Personagem&&MOVEMD_BOSS(inimigo[ini_atual].x))
            {
                inimigo[ini_atual].x+= 2;
            }
            else if(inimigo[ini_atual].x>Personagem&&MOVEME_BOSS(inimigo[ini_atual].x))
            {
                inimigo[ini_atual].x+= -2;
            }
        }
		inimigo[ini_atual].x+= 0;
	}
}


int MOVIMENTOY_BOSS(int Personagem , int ini_atual ,OBJETO_MOVEL *inimigo,int qt_ini)
{
	int MOVIMENTO=0;
	int i;
	int DIRECAO = 0;
	int y=0;

   if(Personagem>inimigo[ini_atual].x)
   {
      if(inimigo[ini_atual].y>=191)
      {
         if((410-inimigo[ini_atual].y)>(Personagem-inimigo[ini_atual].x))
         {
            DIRECAO-=1;
         }
      }
      if(inimigo[ini_atual].y<=299)
      {
         if((410-inimigo[ini_atual].y)<Personagem-inimigo[ini_atual].x)
         {
            DIRECAO+=1;
         }
      }
   }
   else if(Personagem<inimigo[ini_atual].x)
   {
      if(inimigo[ini_atual].y>=191)
      {
         if((410-inimigo[ini_atual].y)>(inimigo[ini_atual].x-Personagem))
         {
            DIRECAO-=1;
         }
      }
      if(inimigo[ini_atual].y<=299)
      {
         if((410-inimigo[ini_atual].y)<inimigo[ini_atual].x-Personagem)
         {
            DIRECAO+=1;
         }
      }
   }

   if(DIRECAO>0)
   {
         return 2;
   }
   else if(DIRECAO<0)
   {
         return -2;
   }
   else
   {
      return 0;
   }


}
#endif // BOSS_H_INCLUDED
