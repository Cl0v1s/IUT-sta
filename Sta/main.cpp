/**
Copyright 2015 Frances Damien, Portron Clovis

Licensed under the Creative Commons, Version 3.0 unported;
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Musics are made by D.Biggiogero (http://0r4.tumblr.com/)
**/

#include "Game.h"

using namespace std;

int main()
{
    View::Initialize();
    Game::initialize();
    Game::destroy();
    View::Destroy();
    return 0;
}







