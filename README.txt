WICHTIG: Um das Program "Inverse Minigolf" in älteren Versionen von minGW compilieren zu können,
ist es Notwendig die Compileroption "-std=c++11" im GCC C++ Compiler und im GCC C Compiler anzugeben.
Dies kann in Eclipse unter den Projekt-Settings -> "C/C++ Build" -> "Settings" -> enstprechende Compiler -> "Miscellaneous" als "Other flags" angegeben werden.

Im Spiel "Inverse Minigolf" kann der Spieler selbst die Minigolfbahn sein. Das Ziel des Spiels ist es den blauen Spielball,
 welcher in der rechten unteren Ecke startet, in das Zielfeld oben links zu leiten. Der Pfeil der von dem Spielball ausgerichtet ist 
 zeigt die Geschwindigkeit und Richtung an in die der Ball rollen wird. Je schneller er rollen wird desto weiter entfernt ist die
 Spitze des Pfeiles. Die Spitze dieses Pfeiles zeigt außerdem in die Richtung in die er startet. Um diees Ziel zu erreichen kann
 der Spieler in der ersten Phase Gegenstände setzen. Dazu gehören die nützlichen Mauern sowie die nicht ganz so hilfreichen
 kleineren (gelben) Bälle und Zylinder. Die kleineren Bälle und Zylinder reflektieren den Spielball. Die kleineren Bälle nehmen diesem
 außerdem Geschwindigkeit weg. Das Hinzufügen der Objekte geschieht durch auswahl des Objektes durch Tastatureingabe: 
Mauern: "M" 
Zylinder: "Z"
Bälle: "B" 
 , zusätzlich muss nach der Auswahl dieser Objekte mit Mausklick die Position des Objektes angegeben werden. Die Mauern benötigen zwei 
 Mausklicks, die jeweils den Anfang der Mauer und das Ende dieser festlegen. Um das Spiel schwierig zu machen, sind die Zylinder vorhanden, 
 die den Spielball reflektieren sowie die kleineren Bälle, die den Spielball ausbremsen können. Am Anfang werden 5 zufälige kleine Bälle platziert 
 sowie Zylinder. Zusätzlich wird ein Zylinder in der Mitte des Spielfelde platziert. 
 Nach dem platzieren der Objekte durch den Spieler, kann das Spiel durch drücken der 
 "Y" (STARTEN)
 Taste gestartet werden. Wenn das Spiel läuft (der Spielball fängt an sich zu bewegen), kann der Spieler mit den WASDQE Tasten das Spielfeld drehen und 
 durch die Pfeiltasten dieses verschieben. durch die ESC Taste kann das Spiel jederzeit beendet werden.
 Wenn der Spielball das Ziel erreicht, wird in der Konsole ausgegeben, dass das Spiel gewonnen wurde. 