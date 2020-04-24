/* 
 * Tema 1 - EGC - FlappyBird
 * Mircea Alexandru-Alin
 * 332CA
 */

Nu am introdus folder-ul libs in arhiva deoarece avea singur 27MB.
In caz de probleme pot arata la prezentare.
tema este in /Laboratoare/Tema1/ si sn FlappyBird

 In joc sunt 5 mesh-uri: 2 pentru coloane (cea de sus si cea de jos), 
 doua pentru pasare (da din aripi) si una de fundal. Pasarea e plasata
 in partea stanga si se misca pe axa y in jos. Pentru a o ridica apasati space.
 Animatia pentru pasare am realizat-o schimband mesh-ul pasarii pentru 10 frame-uri
 dupa ce este apasata tasta space, pentru a da senzatia ca da din aripi atunci
 cand se ridica( si se si reseteaza unchiul de inclinare).
 Coloanele le-am implementat ca un singur obiect pentru coloana de sus si cea de jos.
 acestea se misca simultan, inaltimea fiind calculata random si scalata cu acea valoare.

 Coliziunile sunt calculate daca se suprapun valorile xy ale pasarii cu cele ale coloanelor
 (adica daca coloana intra in aria x a pasarii, verifica inaltimile coloanelor cu ale pasarii
 luand oin considerare inaltimea pasarii si scale-ul coloanelor... look it up in code, 
 cred ca se intelege mai bine asa decat explic eu...).

 Dupa fiecare coloana trecuta creste scorul(dar si viteza), iar jocul se termina atunci cand pasarea
  cade sau se loveste de una dintre coloane. Atunci se reseteaza jocul.

  Formele si culorile le-am ales dorind o tema montana, coloanele sa fie stanci, 
iar pasarea sa fie un vultur cu cap alb.

Disclaimer: am incercat sa fac jocul mai usor de jucat pentru mine, 
pentru ca nu reusesc sa fac mai mult de 2 puncte in jocul original,
astfel aducndu-mi o mica implinire sufleteasca. 