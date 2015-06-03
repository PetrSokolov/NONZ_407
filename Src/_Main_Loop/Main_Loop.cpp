#include <stdio.h>

#include "__Main_Loop.hpp"
#include "..\_Objects_Definitions\__ObjectsDefinitions.hpp"

using namespace src;
using namespace std;


//------------------------------------------------------------------------------
//  Основной цикл приложения
//------------------------------------------------------------------------------

void MainLoop()
{
 while(1){
//  100 mls --------------------------------------------------------------------
  if (Timer100mls >16660){
    menuEngine.setMenuValue("A");
    menuEngine.findAvailableElements(menuEngine.getMenuValue());                       // Производит поиск доступных элементов меню на данном уровне меню
//    printf("Vector elements = %d\n", menuEngine.getCountOfElements());
//    printf("%s elements = %d\n", menuEngine.getMenuValue(), menuEngine.getCountOfAvailableElements());
//    printf("Variables in container = %d\n", containerOfVariables.getCountOfContents());
    

    printf("RC Message = %d\n", rcDecoder.getMessage());
//    printf("uDc = %f\n", uDC.getValue());
    Timer100mls =0;
  }
//------------------------------------------------------------------------------
  
  }
}

