#include "stdafx.h"
namespace Error
{
	/*Ñåğèè îøèáîê   0-99		 ñèñòåìíûå îøèáêè ÑÀÍß
					 100-109	 îøèáêè ïàğàìåòğîâ
					 110-119	 îøèáêè îòêğûòèÿ è ÷òåíèÿ ôàéëîâ
	*/
	ERROR errors[ERROR_MAX_ENTRY] =  //òàáëèöà îøèáîê
	{
		ERROR_ENTRY(0,"Íåäîïóñòèìûé êîä îøèáêè"), //êîä îøèáêè âíå äèàïàçîíà 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1,"Ñèñòåìíûé ñáîé"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY(5,"Îøèáêà, ìàêñèìàëüíûé ğàçìåğ òàáëèöû èäåíòèôèêàòîğîâ 4096"),
		ERROR_ENTRY(6,"Òàáëèöà èäåíòèôèêàòîğîâ ïåğåïîëíåíà"),ERROR_ENTRY(7,"Îøèáêà, ìàêñèìàëüíûé ğàçìåğ òàáëèöû ëåêñåì 4096"),ERROR_ENTRY(8,"Òàáëèöà ëåêñåì ïåğåïîëíåíà"), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"Ïàğàìåòğ -in äîëæåí áûòü çàäàí"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Ïğåâûøåíà äëèííà âõîäíîãî ïàğàìàòğà"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Îøèáêà ïğè îòêğûòèè ôàéëà ñ èñõîäíûì êîäîì (-in)"),
		ERROR_ENTRY(111,"Íåäîïóñòèìûé ñèìâîë â èñõîäíîì ôàéëå (-in)"),
		ERROR_ENTRY(112,"Îøèáêà ïğè ñîçäàíèè ôàéëà ïğîòîêîëà (-log)"),
		ERROR_ENTRY(113, "Îøèáêà ïğè îòêğûòèè âûõîäíîãî ôàéëà (-out)"),ERROR_ENTRY(114, "Äâîéíîå îáúÿâëåíèå"),ERROR_ENTRY(115, "Îøèáêà ëåêñè÷åñêîãî àíàëèçà"),
		ERROR_ENTRY(116, "Äëèíà èäåíòèôèêàòîğà áîëüøå 8"),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200,""), ERROR_ENTRY(201,""),ERROR_ENTRY(202,""),ERROR_ENTRY(203,"Èäåíòèôèêàòîğ íå îïğåäåë¸í"), ERROR_ENTRY_NODEF(204),
		ERROR_ENTRY_NODEF5(205), ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),
		ERROR_ENTRY_NODEF50(250), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY(500, "Íåò òî÷êè âõîäà main"), ERROR_ENTRY(501, "Áîëåå îäíîé òî÷êè âõîäà main"), 
		ERROR_ENTRY(502, "Âîçâğàùàåìîå çíà÷åíèå íå ñîîòâåòñâóåò òèïó ôóíêöèè"), 
		ERROR_ENTRY(503, "Êîëè÷åñòâî ïàğàìåòğîâ ôóíêöèè áîëüøå äîïóñòèìîãî"), 
		ERROR_ENTRY(504, "Ïåğåäàâàåìûå ïàğàìåòğû íå ñîîòâåòñâóşò ôóíêöèè"),
		ERROR_ENTRY(505, "Íå ñîîòâåòñâóåò êîëè÷åñòâî ïåğåäàâàåìûõ ïàğàìåòğîâ"), 
		ERROR_ENTRY(506, "Îøèáêà â ïàğàìåòğàõ ôóíêöèè pow"), 
		ERROR_ENTRY(507, "Îøèáêà â ïàğàìåòğàõ ôóíêöèè compare"), 
		ERROR_ENTRY(508, "Ïîïûòêà ñğàâíåíèÿ îïåğàíäîâ íå òèïà ushort"), 
		ERROR_ENTRY(509, "Îøèáêà â ïàğàìåòğå ôóíêöèè print"), 
		ERROR_ENTRY_NODEF10(510), ERROR_ENTRY_NODEF10(520),
		ERROR_ENTRY_NODEF10(530), ERROR_ENTRY_NODEF10(540), ERROR_ENTRY_NODEF10(550), ERROR_ENTRY_NODEF10(560), 
		ERROR_ENTRY_NODEF10(570), ERROR_ENTRY_NODEF10(580), ERROR_ENTRY_NODEF10(590),
		ERROR_ENTRY(600, "Íåâåğíàÿ ñòğóêòóğà ïğîãğàììû"),
		ERROR_ENTRY(601, "Îøèáî÷íàÿ êîíñòğóêöèÿ â ôóíêöèè"),
		ERROR_ENTRY(602, "Îøèáêà â âûğàæåíèè"),
		ERROR_ENTRY(603, "Îøèáêà â ïàğàìåòğàõ ôóíêöèè"),
		ERROR_ENTRY(604, "Îøèáêà â ïàğàìåòğàõ âûçûâàåìîé ôóíêöèè"),
		ERROR_ENTRY(605, "Îøèáî÷íûé îïåğàòîğ"),
		ERROR_ENTRY_NODEF(606),ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690), ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		ERROR error_info ;												// ñîçäàíèå ñòğóêòóğû êîòîğóş íàäî áóäåò âåğíóòü
		if (id > 0 && id < ERROR_MAX_ENTRY)						// ñğàâíèâàíèå äèàïàçîíà
		{ 
			error_info.id = errors[id].id;
			strcpy_s(error_info.message, errors[id].message);
			error_info.inext.col = -1;
			error_info.inext.line = -1;
		}
		else
		{
			error_info.id = errors[0].id;
			strcpy_s(error_info.message, errors[0].message);
		}
		return error_info;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR error_info;												//	ñîçäàíèå ñòğóêòóğó êîòîğóş íàäî áóäåò âåğíóòü
		if (id > 0 && id < ERROR_MAX_ENTRY)						// ñğàâíåíèå äèàïàçîíà
		{
			error_info.id = errors[id].id;
			error_info.inext.col = col;
			error_info.inext.line = line;
			strcpy_s(error_info.message, errors[id].message);
			return error_info;
		}
		else
		{
			error_info.id = 0; // çàíîøó
			error_info.inext.col = -1;
			error_info.inext.line = -1;
			strcpy_s(error_info.message, errors[0].message);
			return error_info;
		}
	}
	;
};