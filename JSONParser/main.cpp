#include <iostream>
#include <fstream>

#define DEBUG_LASTHOSTNAME 0
#define DEBUG_GOTFPARTY 0
#define DEBUG_THIRDPARTIES 1

// http://www.cplusplus.com/doc/tutorial/files/

/*************************
 * Jonas Berger          *
 * 11.06.2020            *
 * GdI II, Miniprojekt-1 *
 *************************/

using namespace std;

int main() {
    string lastHostname;
    string firstParty;
    string thirdParty;
    string line;
    size_t ende;

    ifstream jsonimport ("rohdaten.json");
    if (jsonimport.is_open()) {
        while ( getline (jsonimport,line) ) { // Gesamten Inhalt der Datei einlesen
            if(line.find("hostname\": \"")!= string::npos) {
                lastHostname = line;
                if(DEBUG_LASTHOSTNAME) {cout << "DEBUG : Found last hostname " << lastHostname.substr(17, lastHostname.size()-19) << endl;};
            }

            if(line == "    \"firstParty\": true,") { // First Parties suchen ("firstParty": true)
                if(DEBUG_GOTFPARTY) {cout << "DEBUG : Got first party ";};
                // First Parties identifizieren (hostname)
                firstParty = lastHostname.substr(17, lastHostname.size()-19); // letzte zwei Zeichen abschneiden, 17+2
                if(DEBUG_GOTFPARTY) {cout << firstParty << endl;};
            }
            // Kanten von First Parties zu Third Parties ausgeben ("thirdParties": [)
            if(line == "    \"thirdParties\": [") { // Third Parties der letzten gefundenen First Party ausgeben
                getline (jsonimport,line);
                if(DEBUG_THIRDPARTIES) {cout << "DEBUG : Third Parties from " << firstParty << " are:" << endl;};
                while(line != "    ]") {
                    thirdParty = line.substr(7); // Anfang wegkuerzen
                    ende = thirdParty.find("\""); // Ende finden, letzte ThirdParty endet mit " statt ",
                    thirdParty = thirdParty.substr(0, ende);
                    getline (jsonimport,line); // naechste Zeile
                    if(DEBUG_THIRDPARTIES) {cout << "DEBUG :  \\-> " << thirdParty << endl;};
                }
                cout << endl;
            }
        }
        jsonimport.close();
    }

    else cout << "Unable to open file";
    return 0;
}
