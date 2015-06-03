//#####################################################################################
//	Файл				__IDisplayed.h
//	Название:		Интерфейс работы с дисплеем
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 май 20 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################


//=====================================================================================
//  Интерфейс работы с дисплеем.
//=====================================================================================
class IDisplayed{
  public:
    virtual void Display (char* string);
    virtual void DisplayOff (void);
};

