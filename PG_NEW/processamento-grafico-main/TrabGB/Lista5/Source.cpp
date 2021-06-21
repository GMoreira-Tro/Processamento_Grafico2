#include <Windows.h>
#include <conio.h>
#include "SceneManager.h"

using namespace std;

int main()
{
    cout << "Escolha seu sprite :3!!" << endl;
    cout << "1 - Akeno (deusa do meu coração)" << endl;
    cout << "2 - A mulher lá da foto" << endl;
    cout << "3 - SAMsung" << endl;
    cout << "4 - muro" << endl;
    
    char choice;
    string path;
    
    while (true)
    {
        choice = _getch();
        if (choice == '1')
        {
            path = "../textures/Akeno-samaS2.jpg";
            break;
        }
        else if (choice == '2')
        {
            path = "../textures/gasosa.png";
            break;
        }
        else if (choice == '3')
        {
            path = "../textures/sam.jpg";
            break;
        }
        else if (choice == '4')
        {
            path = "../textures/wall.jpg";
            break;
        }
    }

    SceneManager* sceneManager = new SceneManager();
    sceneManager->initialize(1200, 900, "Akeno MEGAMI <3", 
       path);

    sceneManager->run(Ponto3d(1,1,1));
}