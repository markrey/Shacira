/******************************************************************************
*  Alignement
*
*  Linux:   Datei target.h
*           Unter Linux kann man zwar die Compileroption -Fpack_struct angeben,
*           um alle Strukturen ohne L�cher anzulegen, wie es vom IQT teileweise
*           zwingend vorgesehen ist (Datentr�ger, Host), doch dann werden auch
*           die Strukturen aus den Standardincludefiles so angeleget, w�hrend
*           sie von der C-Library ungepackt verwendet werden. Dies f�hrt zu
*           schwer auffindbaren Fehlern. Leider gibt es auch keine M�glichkeit,
*           das Packen im einzelnen zu verhindern (__attribute((align)) wirkt
*           nicht auf die einzelnen Elemente einer Struktur.
*           Als L�sung bleibt nur, das IQT komplett ohne -Fpack_struct zu
*           �bersetzen, und die einzelnen Strukturen als gepackt zu definieren,
*           wo dies erforderlich ist. Dies geschieht mit dem unten definierten
*           Makro STRUCT_PACKED.
*           Das Makro STRUCT_PACKED wirkt nur auf eine einzelne Struktur/Union
*           und wird unmittelbar nach der schlie�enden geschweiften Klammer der
*           Strukturdeklaration aufgerufen:
*              typedef struct {...} STRUCT_PACKED name;
*           STRUCT_PACKED wirkt nur auf die einzelnen Elemente einer Struktur
*           und nicht auf untergeordnete Strukturelemente. Enth�lt eine Sturktur
*           weitere structs, so m�ssen diese auch wieder mit STRUCT_PACKED
*           deklariert werden!
*
*  Windows: Dateien packstart.h, packstop.h
*           Unter Windows wird das Packen von Strukturen mit einem Compiler-
*           schalter (pragma) ein- und ausgeschaltet. Diese Compilerschalter 
*           m�ssen vor und nach der zu packenden Struktur aufgerufen werden.
*           Da sich das Pragma nicht in einem define verstecken l�sst, mu�
*           man zu diesem Zweck jeweils ein Includefile aufrufen, das das
*           pragma enth�lt:
*              include <packstart.h>
*              typedef struct {...} name;
*              include <packstop.h>
*
*  Das Ein- und Ausschalten des Packens von Strukturen geschieht also auf den
*  verschiedenen Systemem mit zwei unterschiedlichen Methoden. Einmal durch
*  eine Erweiterung der Deklaration von Strukturen (siehe Linux), das andere
*  mal durch Compilerschalter (siehe Windows). Um portabel zu bleiben, m�ssen
*  beide Methoden gleichzeitig angewendet werden, wobei alternativ nur die
*  jeweils passende davon eingeschaltet ist:
*              include <packstart.h>
*              typedef struct {...} STRUCT_PACKED name;
*              include <packstop.h>
*
******************************************************************************/

#if defined __WIN32__
#pragma pack(1)   // Strukturen auf 1-Byte-Grenzen packen
#endif


