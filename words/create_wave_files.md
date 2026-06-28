# Wave Files erstellen

Die Basis ist die Steuerdatei "vocabulary.text". Sie enthält alle Worte, die in WAV-Files gewandelt werden sollen.
Zeilen die mit "---" beginnen, zeigen den Start einer Gruppe. Der Aufbau der Zeile ist

---zh0/KEY_NUMBERS
nach "---" folgen zwei Zeichen, die den Key für die Gruppe bilden. Danach folgt eine Zahl, die den Startindex für die Gruppe bildet. Der Index wird für jedes Mitglied der Gruppe um eins erhöht. Im Beispiel also zh0.wav, zh1.wav, zh2.wav ...... Nach dem optionalen "/" folgt der Name einer Konstanten, die in "vocabulary.h" für diese Gruppe definiert wird.

Es folgen die Zeilen für die Mitglieder der Gruppe. Die Zeilen beginnen mit dem Wort, das gesprochen werden soll. Auch hier kann nach einem optionalen "/" der Name einer Konstanten für das Wort angegeben werden. 

Mit dem Programm TTS.exe können ausgehend von der Steuerdatei die benötigten WAV-Files generiert werden. 
Das Programm benötigt die folgenden Einstellungen:
**Steuerdatei:** Pfad zur Steuerdatei
**Zielverzeichnis WAV Dateien:** Pfad zu einem Verzeichnis in dem die WAV-Dateien abgelegt werden sollen
**Zielverzeichnis Headerfile:** Pfad zu einem Verzeichnis in dem das Headerfile vocabulary.h abgelegt werden soll
**Stimme:** Eine Auswahlbox um eine Stimme aus dem Betriebssystem auszuwählen. Damit alle installiertn Stimmen nutzbar sind, muss in der Windows-Powershell folgender Befehl ausgeführt werden

*reg copy "HKLM\SOFTWARE\Microsoft\Speech&#95;OneCore\Voices\Tokens" "HKLM\SOFTWARE\Microsoft\Speech\Voices\Tokens" /s /f* 

**Sprachtest:** Hier kann ein beliebiger Text eingegeben werden. Mit dem Knopf "Test" wird der Text  mit der gewählten Stimme gesprochen.
Mit dem Knopf "Files erzeugen" werden die WAV Files und das Headerfile in den gewählten Directories erzeugt.

Die so erzeugten WAV Files haben am Anfang und Ende kurze Stille Phasen, was sich beim hintereinander Sprechen ungünstig auswirkt.
Mit dem Programm [Audacity ](https://https://www.google.com/url?sa=i&source=web&rct=j&url=https://www.audacityteam.org/download/&ved=2ahUKEwjLofDxxaqVAxVAnf0HHQt4K7sQy_kOeggIAggACAoQAg&opi=89978449&cd&psig=AOvVaw0p7vX4DVDlHOrpErRksB4i&ust=1782757106872000)können mit dem Makro "Stille_entfernen" die WAV Dateien verkürzt werden. Der Makro kann vom File "Stille_entfernen.txt" aus diesem Repository importiert werden. Die verkürzten WAV Dateien werden im Verzeichnis "C:\Users\User\Documents\Audacity\macro-output" gespeichert.


