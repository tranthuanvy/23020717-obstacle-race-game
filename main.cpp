#include"CommonFunc.h"
#include"BaseObject.h"
#include "GameMap.h"
#include"MainObject.h"
#include"Timer.h"
#include"ThreatObject.h"
#include"Explosion.h"
BaseObject g_background;
bool init() {

    bool success = true;

    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    } else {
        // Thiết lập chất lượng tỉ lệ vẽ texture thành linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        // Tạo cửa sổ
        gWindow = SDL_CreateWindow("Ostacle Race",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            // Tạo renderer với chế độ vsync
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == nullptr) {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            } else {
                // Thiết lập màu vẽ cho renderer
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Khởi tạo tải ảnh PNG
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError()
                              << std::endl;
                    success = false;
                }
            }
        }
    }

    return success;
}
bool loadbkground()
{
    bool ret =g_background.LoadImg("C:/Users/Admin/Pictures/bkground.PNG",gRenderer);
    if (ret ==false)
    {
    std::cout << "Lỗi tải background!" << std::endl;
    return false;
  }
  else{ return true;}

}

 void close() {
     g_background.Free();
     SDL_DestroyRenderer(gRenderer);
      gRenderer = nullptr;


    SDL_DestroyWindow(gWindow);

    gWindow = nullptr;

    IMG_Quit();
    SDL_Quit();
 }
 std::vector<ThreatObject*>MakeThreatList()
 {
     std::vector<ThreatObject*>list_threat;
     ThreatObject* threatobject= new ThreatObject[20];
     for(int i=0;i<20;i++)
     {
         ThreatObject* p_threat=(threatobject+i);
         if(p_threat!=NULL)
         {
             p_threat->LoadImg("C:/Users/Admin/Pictures/threatobject.png",gRenderer);
             p_threat->set_clips();
             p_threat->setxpos(800+i*1200);
             p_threat->setypos(250);

             BulletObject*p_bullet=new BulletObject();
             p_threat->InitBullet(p_bullet,gRenderer);
             list_threat.push_back(p_threat);
         }
     }
     return list_threat;
 }

int main(int argc, char* args[])
{
    Timer time;
  // Khởi tạo SDL
  if (!init())
    {
    std::cout << "Lỗi khởi tạo SDL!" << std::endl;
    return -1;
  }
  if(!loadbkground()){
    std::cout<<" lỗi tại background!"<<std::endl;
    return -1;
  }

    GameMap game_map;
    game_map.LoadMap("map/map01.txt");    // Sử dụng trực tiếp kiểu const char**/
    game_map.LoadTiles(gRenderer);

    MainObject character_game;
    character_game.LoadImg("C:/Users/Admin/Pictures/animal.PNG",gRenderer);
    character_game.set_clips();

    std::vector<ThreatObject*>threat_list =MakeThreatList();

    ExplosionObject exp;
    exp.LoadImg("C:/Users/Admin/Pictures/explosion.png",gRenderer);
    exp.set_clip();

   bool quit = false;
   while (!quit)
    {
       time.start();
       while (SDL_PollEvent(&e) != 0)
         {
             if (e.type == SDL_QUIT) {
             quit = true;
              break;
         }
             character_game.HandelInputAction(e,gRenderer);
    }

      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(gRenderer);
      g_background.renderTexture(gRenderer,NULL);

      map map_data=game_map.getMap();


     character_game.HandleBullet(gRenderer);
     character_game.SetMapxy(map_data.start_x_,map_data.start_y_);
     character_game.DoPlayer(map_data);// tính  toán lại start x, start y có tính toán mới
     character_game.Show(gRenderer);

     game_map.SetMap(map_data);// cap nhat lai vi tri moi tre0
     game_map.DrawMap(gRenderer);

     for(int i=0;i<threat_list.size();i++)
     {
         ThreatObject* p_threat= threat_list.at(i);
         if(p_threat!=NULL)
         {
             p_threat->SetMapxy(map_data.start_x_,map_data.start_y_);
             p_threat->DoPlayer(map_data);
             p_threat->MakeBullet(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);
             p_threat->Show(gRenderer);

             SDL_Rect rect_player= character_game.GetRectFrame();
             bool bCol1=false;
             std::vector<BulletObject*>tBullet_list=p_threat->get_bullet_list();
             for(int j=0;j<tBullet_list.size();j++)
             {
                 BulletObject* pt_bullet=tBullet_list.at(j);
                 if(pt_bullet)
                 {
                     bCol1=SDLCommonFunc::CheckCollision(pt_bullet->GetRect(),rect_player);
                     if(bCol1)
                     {
                         p_threat->RemoveBullet(j);
                         break;//không kiểm tra các viên đạn khác
                     }
                 }
             }
             SDL_Rect rect_threat=p_threat->GetRectFrame();
             bool bCol2=SDLCommonFunc::CheckCollision(rect_player,rect_threat);
            if(bCol1||bCol2)
             {
                if (MessageBoxW(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                 {
                    p_threat->Free() ;
                    close();

                    return 0 ;
                 }
             }
         }
     }

     int frameexpwidth= exp.get_frame_width();
     int frameexpheight= exp.get_frame_height();
     std::vector<BulletObject*>bullet_arr= character_game.get_bullet_list();
     for(int b=0;b<bullet_arr.size();b++)
     {
         BulletObject* p_bullet=bullet_arr.at(b);
         if(p_bullet!=NULL)
         {
             for(int t=0;t<threat_list.size();t++ )
             {
                 ThreatObject* threatobj= threat_list.at(t);
                 if(threatobj!=NULL)
                 {
                     SDL_Rect tRect;
                     tRect.x=threatobj->GetRect().x;
                     tRect.y=threatobj->GetRect().y;
                     tRect.w=threatobj->getwidthframe();
                     tRect.h=threatobj->getheightframe();// lay 1 frame thoi

                     SDL_Rect bRect= p_bullet->GetRect();
                     bool bCol=SDLCommonFunc::CheckCollision(bRect,tRect);
                     if(bCol)
                     {
                       for(int i=0; i<8;i++)
                       {
                           int x_pos=p_bullet->GetRect().x -frameexpheight*0.5;
                           int y_pos= p_bullet->GetRect().y -frameexpheight*0.5;// đạn chạm ở đâu nổ tại đấy

                           exp.set_frame(i);
                           exp.SetRect(x_pos,y_pos);
                           exp.Show(gRenderer);
                       }

                       character_game.RemoveBullet(b);
                       threatobj->Free();
                       threat_list.erase(threat_list.begin()+t);

                     }

                }
             }

         }
     }

      SDL_RenderPresent(gRenderer);

    int real_timer= time.get_ticks();// thoi gian thuc su troi qua
    int time_one_frame =1000/*mili giay*//FRAME_PER_SECOND;


    if(real_timer<time_one_frame)
    {
      int delay_time=time_one_frame-real_timer;

      if(delay_time)
      {
      SDL_Delay(delay_time);
      }
    }

  }

  for(int i=0;i<threat_list.size();i++)
  {
      ThreatObject* p_threat=threat_list.at(i);
      if(p_threat!=NULL)
      {
          p_threat->Free();
          p_threat=NULL;
      }
  }
  threat_list.clear();

  // Dọn dẹp
  close();

  // Trả về 0
  return 0;
}



