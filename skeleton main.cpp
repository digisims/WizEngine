#include "wizGame.h"
#include "wizInputManager.h"
#include "wizFontManager.h"
#include "wizTextureManager.h"
#include "wizMeshManager.h"
#include "wizSoundManager.h"
#include "wizSpriteSheetManager.h"
#include "wizMaterialManager.h"

#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    srand ( time(NULL) );

    wizGame::initialize(60, 16);
    wizInputManager::initialize();
    wizTextureManager::initialize();
    wizSoundManager::initialize();
    wizGame::run();
    wizTextureManager::destroy();
    wizSoundManager::destroy();
    wizInputManager::destroy();
    wizFontManager::destroy();
    wizMaterialManager::destroy();
    wizSpriteSheetManager::destroy();
    wizGame::destroy();

	return 1;
}
