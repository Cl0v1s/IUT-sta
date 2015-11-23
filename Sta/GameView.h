#ifndef GameView_H
#define GameView_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "RenderEntity.h"
#include "RenderMenu.h"

class GameView
{
private:
    std::vector<RenderEntity*> entityRenders;
    std::vector<RenderMenu*> menuRenders;
public:
    ~GameView();
    void addEntityRender(RenderEntity* render);
    void addMenuRender(RenderMenu* menu);
    void render();
};




#endif // GameView_H
