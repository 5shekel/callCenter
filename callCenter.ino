//call operator simulator
//connected to keypad exmaple
//and mapp[ed to correct keys.
//yair99@gmail
/**************************************
 *
 *  Example for Sparkfun MP3 Shield Library www.billporter.info
 ******************************************/

#include <SPI.h>

//Add the SdFat Libraries
#include <SdFat.h>
#include <SdFatUtil.h>
SdFat sd; // newly required in 1.01.00 and higher

//and the MP3 Shield Library
#include <SFEMP3Shield.h>

//create and name the library object
SFEMP3Shield MP3player;

byte result;
int lang;
char key;
int mv, cn, dy, hr, qt;
int step = 1 ;

char* A_qt[] = {
  "kartis1.mp3", "kartis2.mp3", "kartis3.mp3", "kartis4.mp3",
  "kartis5.mp3", "kartis6.mp3", "kartis7.mp3", "kartis8.mp3", "kartis9.mp3"
};
char* A_qte[] = {
  "kartis1e.mp3", "kartis2e.mp3", "kartis3e.mp3", "kartis4e.mp3",
  "kartis5e.mp3", "kartis6e.mp3", "kartis7e.mp3", "kartis8e.mp3", "kartis9e.mp3"
};
char* A_mv[] = {
  "MVavdm.mp3", "MVglmd.mp3", "MVhazmn.mp3", "MVmstry.mp3", "MVtmz.mp3"
};
char* A_mve[] = {
  "MVavdme.mp3", "MVglmde.mp3", "MVhazmne.mp3", "MVmstrye.mp3", "MVtmze.mp3"
};
char* A_dy[] = {
  "tdyTime.mp3", "tmrTime.mp3"
};
char* A_dye[] = {
  "tdyTimee.mp3", "tmrTimee.mp3"
};
char* A_hr[] = {
  "tm1720.mp3", "tm1520.mp3", "tm1910.mp3", "tm1920.mp3"
};
char* A_hre[] = {
  "tm1720e.mp3", "tm1520e.mp3", "tm1910e.mp3", "tm1920e.mp3"
};
char* A_cn[] = {
  "CNtpz.mp3", "CNmzm.mp3", "CNavtz.mp3", "CNtmz.mp3",
};
char* A_cne[] = {
  "CNtpze.mp3", "CNmzme.mp3", "CNavtze.mp3", "CNtmze.mp3",
};

volatile int STAGE = 1; //for each STAGE we advance this by 1, if you press #. STAGE is reset to 0

////////////////////////////////////////
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {
    'a', '1', '2', '3'
  }
  ,
  {
    '4', '5', '6', '7'
  }
  ,
  {
    '8', '9', '0', '*'
  }
  ,
  {
    '#', 'n', 'o', 'p'
  }
};

byte rowPins[ROWS] = {
  22, 24, 26, 28
}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  30, 32, 34, 36
}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//////////////////////////////////////////////////////////////////////////

void setup() {

  Serial.begin(115200);
  if (!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt(); // newly required in 1.01.00 and higher
  if (MP3player.begin() != 0)    Serial.print(F("ERROR"));
  
    result = MP3player.begin();  //boot up the MP3 Player Shield
    if (result != 0) { //check result, see readme for error codes.
      Serial.print("Error code: ");
      Serial.print(result);
      Serial.println(" when trying to start MP3 player");
    }

    attachInterrupt(2, hookUP, RISING);

    attachInterrupt(3, hookDOWN, LOW);
    Serial.println("init OK");
  }

  void hookUP()
  {
    //MP3player.stopTrack();
    asm volatile ("  jmp 0");
  }

  void hookDOWN()
  {
    MP3player.stopTrack();
    //STAGE=0;
  }


  void loop() {
  //key = keypad.waitForKey();
  //Serial.println(key);

    switch (STAGE) {
      case 0:
        Serial.println("stage 0");
        MP3player.stopTrack();
        STAGE = 1;

      case 1:///////////////////////////////////////////////////////////
        Serial.println("stage 1");
        Serial.println("intro and choose between heb or eng");

        MP3player.playMP3("intro.mp3");
        key = keypad.waitForKey();

        MP3player.stopTrack();

        if (key == 'a') {
          Serial.println("a1- you choose hebrew");
          lang = 1;
          STAGE++;
        }
        else if (key == '2') {
          Serial.println("a2- you choose english");
          lang = 0;
          STAGE++;
        }
        else if (key == '#') {
          Serial.println("a#- reset");
          STAGE = 0;
        }


        break;

      case 2:///////////////////////////////////////////////////////////
        Serial.println("stage 2");
        Serial.println("choose between cinema or movie");

        if (lang) {
          MP3player.playMP3("chooseCM.mp3");
        }
        else if (lang == 0) {
          MP3player.playMP3("choosCMe.mp3");
        }

        key = keypad.waitForKey();

        MP3player.stopTrack();

        if (key == 'a') {
          Serial.println("b1- u choose by cinema");
          STAGE = 3;
        }
        else if (key == '2') {
          Serial.println("b2- u choose by movie");
          STAGE = 4;
        }
        else if (key == '#') {
          Serial.println("b#- reset");
          STAGE = 0;
        }

        break;

      case 3:///////////////////////////////////////////////////////////
        Serial.println("stage 3");
        Serial.println("choose which cinema");

        if (lang) {
          MP3player.playMP3("whichCN.mp3");
        }
        else {
          MP3player.playMP3("whichCNe.mp3");
        }

        key = keypad.waitForKey();
        MP3player.stopTrack();

        if (key == '#') {
          Serial.println("c#- reset");
          STAGE = 0;
        }
        else if (key == 'a') {
          cn = 1;
          if (mv == 0) {
            STAGE++;
          }
          else
          {
            STAGE = 5;
          };
        }
        else if (key == '2') {
          cn = 2;
          if (mv == 0) {
            STAGE++;
          }
          else
          {
            STAGE = 5;
          };
        }
        else if (key == '3') {
          cn = 3;
          if (mv == 0) {
            STAGE++;
          }
          else
          {
            STAGE = 5;
          };
        }
        else if (key == '4') {
          cn = 4;
          if (mv == 0) {
            STAGE++;
          }
          else
          {
            STAGE = 5;
          };
        }

        break;

      case 4:///////////////////////////////////////////////////////////
        Serial.println("stage 4");
        Serial.println("choose which movie");

        if (lang) {
          MP3player.playMP3("whichMV.mp3");
        }
        else {
          MP3player.playMP3("whichMVe.mp3");
        }

        key = keypad.waitForKey();
        MP3player.stopTrack();
        if (key == '#') {
          Serial.println("c#- reset");
          STAGE = 0;
        }
        else if (key == 'a') {
          mv = 1;

          if (cn == 0) {
            STAGE = 3;
          }
          else {
            STAGE++;
          }
        }
        else if (key == '2') {
          mv = 2;
          if (cn == 0) {
            STAGE = 3 ;
          }
          else {
            STAGE++;
          }
        }
        else if (key == '3') {
          mv = 3;
          if (cn == 0) {
            STAGE = 3 ;
          }
          else {
            STAGE++;
          }
        }
        else if (key == '4') {
          mv = 4;
          if (cn == 0) {
            STAGE = 3 ;
          }
          else {
            STAGE++;
          }
        }
        else if (key == '5') {
          mv = 5;
          if (cn == 0) {
            STAGE = 3  ;
          }
          else {
            STAGE++;
          }
        }

        break;

      case 5:///////////////////////////////////////////////////////////
        Serial.println("stage 5");
        Serial.println("choose which day");

        if (lang) {
          MP3player.playMP3("whichDY.mp3");
        }
        else {
          MP3player.playMP3("whichDYe.mp3");
        }

        key = keypad.waitForKey();
        MP3player.stopTrack();

        if (key == 'a') {
          Serial.println("c1- u choose right day");
          dy = 1;
          STAGE++;
        }
        else if (key == '2') {
          Serial.println("c1- u choose right day");
          dy = 2;
          STAGE++;
        }
        else if (key == '3') {
          Serial.println("c2- u choose wrong day");

          if (lang) {
            MP3player.playMP3("notavlb.mp3");
          }
          else {
            MP3player.playMP3("notavlbe.mp3");
          }
          while (MP3player.isPlaying())
          {
            key = keypad.getKey();
          }
          //choose again
          // STAGE++;
        }
        else if (key == '#') {
          Serial.println("c#- reset");
          STAGE = 0;
        }



        break;

      case 6:///////////////////////////////////////////////////////////
        Serial.println("stage 6");
        Serial.println("choose which hour");

        if (lang) {
          MP3player.playMP3("whichHR.mp3");
        }
        else {
          MP3player.playMP3("whichHRe.mp3");
        }

        key = keypad.waitForKey();
        MP3player.stopTrack();

        if (key == '#') {
          Serial.println("c#- reset");
          STAGE = 0;
        }
        else if (key == 'a') {
          hr = 1;
          STAGE++;
        }
        else if (key == '2') {
          hr = 2;
          STAGE++;
        }
        else if (key == '3') {
          hr = 3;
          STAGE++;
        }
        else if (key == '4') {
          hr = 4;
          STAGE++;
        }
        break;

      case 7: ///////////////////////////////////////////////////////////
        Serial.println("stage 7");
        Serial.println("choose which number txts");

        if (lang) {
          MP3player.playMP3("whichNM.mp3");
        }
        else {
          MP3player.playMP3("ewhichNM.mp3");
        }

        key = keypad.waitForKey();
        MP3player.stopTrack();
        if (key == '#') {
          Serial.println("c#- reset");
          STAGE = 0;
        }
        else if (key == 'a') {
          qt = 1;
          STAGE++;
        }
        else if (key == '2') {
          qt = 2;
          STAGE++;
        }
        else if (key == '3') {
          qt = 3;
          STAGE++;
        }
        else if (key == '4') {
          qt = 4;
          STAGE++;
        }
        else if (key == '5') {
          qt = 5;
          STAGE++;
        }
        else if (key == '6') {
          qt = 6;
          STAGE++;
        }
        else if (key == '7') {
          qt = 7;
          STAGE++;
        }
        else if (key == '8') {
          qt = 8;
          STAGE++;
        }
        else if (key == '9') {
          qt = 9;
          STAGE++;
        }
        break;

      case 8: ///////////////////////////////////////////////////////////

        //Serial.println("stage 8 - summery");

        if (!MP3player.isPlaying() && step == 1) {
          Serial.println("@choose");

          if (lang) {
            MP3player.playMP3("uchoose.mp3");
          }
          else {
            MP3player.playMP3("uchoosee.mp3");
          }
          step++;
        }

        if (!MP3player.isPlaying() && step == 2) {
          Serial.println("@qt");

          if (lang) {
            MP3player.playMP3( A_qt[qt - 1]);
          }
          else {
            MP3player.playMP3( A_qte[qt - 1]);
          }


          step++;
        }

        if (!MP3player.isPlaying() && step == 3) {
          Serial.println("@movie");

          if (lang) {
            MP3player.playMP3( "toMv.mp3");
          }
          else {
            MP3player.playMP3( "toMve.mp3");
          }
          step++;
        }

        if (!MP3player.isPlaying() && step == 4) {
          Serial.println("@movie 2");

          if (lang) {
            MP3player.playMP3( A_mv[mv - 1]);
          }
          else {
            MP3player.playMP3( A_mve[mv - 1]);
          }

          step++;
        }
        if (!MP3player.isPlaying() && step == 5) {
          Serial.println("@day");

          if (lang) {
            MP3player.playMP3( A_dy[dy - 1]);
          }
          else {
            MP3player.playMP3( A_dye[dy - 1]);
          }
          step++;
        }
        if (!MP3player.isPlaying() && step == 6) {
          Serial.println("@hour");

          if (lang) {
            MP3player.playMP3( A_hr[hr - 1]);
          }
          else {
            MP3player.playMP3( A_hre[hr - 1]);
          }
          step++;
        }

        if (!MP3player.isPlaying() && step == 7) {
          Serial.println("@cienama");

          if (lang) {
            MP3player.playMP3("atCinm.mp3");
          }
          else {
            MP3player.playMP3("atCinme.mp3");
          }
          step++;
        }

        if (!MP3player.isPlaying() && step == 8) {
          Serial.println("@cienama 2");

          if (lang) {
            MP3player.playMP3( A_cn[cn - 1]);
          }
          else {
            MP3player.playMP3( A_cne[cn - 1]);
          }
          step++;
        }

        if (!MP3player.isPlaying() && step == 9) {
          Serial.println("@win or loose");
          //need to get qt==2 && mv==3 && cn==3 && dy==2 && hr==4
          if (qt == 2 && mv == 3 && cn == 4 && dy == 2 && hr == 4) {
            Serial.println("win");

            if (lang) {
              MP3player.playMP3("win.mp3");
            }
            else {
              MP3player.playMP3("wine.mp3");
            }
            step++;
          }
          else {

            if (lang) {
              MP3player.playMP3("fail.mp3");
            }
            else {
              MP3player.playMP3("failE.mp3");
            }
            Serial.println("fail");
            step++;
          }
        }
        if (!MP3player.isPlaying() && step == 10)
          STAGE = 9;


        //key = keypad.waitForKey();
        if (key == '#') {
          Serial.println("g#- reset");
          STAGE = 0;
        }
        break;

      case 9: ///////////////////////////////////////////////////////////
        Serial.println("stage 8 - END");
        Serial.println("busy signal");
        MP3player.playMP3( "busy.mp3");
        key = keypad.waitForKey();
        if (key == '#') {
          Serial.println("g#- reset");
          STAGE = 0;
        }
        break;
    }

  }














































