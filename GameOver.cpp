#include"GameOver.h"
GameOver::GameOver()
{

}
GameOver::~GameOver()
{

}



int GameOver::ShowGameOver(SDL_Renderer* des,TTF_Font* font)
{
    BaseObject gBackground;
    bool ret= gBackground.LoadImg("Pics/Menu.png", des);


    SDL_Rect pos[kMenuItemNum1];
    pos[0].x=SCREEN_WIDTH*0.5-210;
    pos[0].y=470;

    pos[1].x=SCREEN_WIDTH*0.5-100;
    pos[1].y=550;





   TextObject text_menu[kMenuItemNum1];

    text_menu[0].SetText("Play AGAIN");
    text_menu[0].SetColor(TextObject::BLACK_TEXT);
    text_menu[0].SetRect( pos[0].x, pos[0].y);
    text_menu[0].LoadRenderText(font,des);


    text_menu[1].SetText("EXIT");
    text_menu[1].SetColor(TextObject::BLACK_TEXT);
    text_menu[1].SetRect( pos[1].x, pos[1].y);
    text_menu[1].LoadRenderText(font,des);


    bool selected[kMenuItemNum1]={0,0};
    int xm=0;
    int ym=0;
    SDL_Event m_event;
    while(true)
    {
    while(SDL_PollEvent(&m_event))
    {
        switch(m_event.type)
        {
          case SDL_QUIT:
           text_menu[0].Free();
           text_menu[1].Free();

             gBackground.Free();
            return 1;
          case SDL_MOUSEMOTION:
            {
              xm=m_event.motion.x;
              ym=m_event.motion.y;

              for(int i=0;i<kMenuItemNum1;i++)
              {
                if (xm >= pos[i].x && xm <= pos[i].x + pos[i].w &&
                        ym >= pos[i].y && ym <= pos[i].y + pos[i].h)
                {
                    if(selected[i]==false)
                    {
                        selected[i]=1;
                        text_menu[i].SetColor(TextObject::RED_TEXT);
                        text_menu[i].LoadRenderText(font, des);
                    }
                }
                else
                {
                    if(selected[i]==true)
                    {
                        selected[i]=0;
                        text_menu[i].SetColor(TextObject::BLACK_TEXT);
                        text_menu[i].LoadRenderText(font,des);
                    }
                }
              }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
                {
                  xm=m_event.button.x;
                  ym=m_event.button.y;

              for(int i=0;i<kMenuItemNum1;i++)
              {
                 if (xm >= pos[i].x && xm <= pos[i].x + pos[i].w &&
                        ym >= pos[i].y && ym <= pos[i].y + pos[i].h)
                {
                    text_menu[0].Free();
                    text_menu[1].Free();
                    gBackground.Free();
                    return i;
                }

              }
            }
                break;
          case SDL_KEYDOWN:
            if(m_event.key.keysym.sym==SDLK_ESCAPE)
            {
                text_menu[0].Free();
                text_menu[1].Free();
                gBackground.Free();
                return 1;
            }
          default:
            break;
        }
   }
      gBackground.renderTexture(des, NULL);

        for (int i = 0; i < kMenuItemNum1; ++i)
        {
            text_menu[i].RenderText(des, pos[i].x, pos[i].y);
            pos[i].w = text_menu[i].GetWidth();
            pos[i].h = text_menu[i].GetHeight();
        }


     SDL_RenderPresent(des);
 }

     return 0;
}