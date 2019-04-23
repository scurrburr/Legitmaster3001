// Der folgende ifdef-Block ist die Standardmethode zum Erstellen von Makros, die das Exportieren
// aus einer DLL vereinfachen. Alle Dateien in dieser DLL werden mit dem NIGGAINTERNALFIX10_EXPORTS-Symbol
// (in der Befehlszeile definiert) kompiliert. Dieses Symbol darf für kein Projekt definiert werden,
// das diese DLL verwendet. Alle anderen Projekte, deren Quelldateien diese Datei beinhalten, sehen
// NIGGAINTERNALFIX10_API-Funktionen als aus einer DLL importiert an, während diese DLL
// mit diesem Makro definierte Symbole als exportiert ansieht.
#ifdef NIGGAINTERNALFIX10_EXPORTS
#define NIGGAINTERNALFIX10_API __declspec(dllexport)
#else
#define NIGGAINTERNALFIX10_API __declspec(dllimport)
#endif

// Diese Klasse wird aus der DLL exportiert.
class NIGGAINTERNALFIX10_API Cniggainternalfix10 {
public:
	Cniggainternalfix10(void);
	// TODO: Methoden hier hinzufügen.
};

extern NIGGAINTERNALFIX10_API int nniggainternalfix10;

NIGGAINTERNALFIX10_API int fnniggainternalfix10(void);
