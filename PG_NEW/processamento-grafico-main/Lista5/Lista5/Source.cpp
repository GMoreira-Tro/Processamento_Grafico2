#include "SceneManager.h"

using namespace std;

int main()
{
    SceneManager* sceneManager = new SceneManager();
    sceneManager->initialize(1200, 900, "Akeno MEGAMI <3", 
        "../textures/Akeno-samaS2.jpg");

    sceneManager->run(Ponto3d(1,1,1));
}