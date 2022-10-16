
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  //seteo LCD

int boton = 7;  // el pin del botón
int vida = 3; //cantidad de vidas iniciales
int puntos = 0;
int high = 0; //high score
int x = 2; //posicion Mileva
int abajo = 1;  //fila piso
int arriba = 0; //fila salto
int v = 500;  //velocidad inicial
int start = 0; //bool

//sprites Mileva
byte mileva1a[] = {B00000, B00000, B01000, B01000, B00111, B00111, B00101, B01001};//cola
byte mileva2a[] = {B00000, B01000, B01110, B01110, B11000, B11000, B10100, B01010};//cabeza
byte mileva1b[] = {B00000, B00000, B10000, B01000, B00111, B00111, B00101, B00110};//cola
byte mileva2b[] = {B00000, B01000, B01110, B01110, B11000, B11000, B10100, B10100};//cabeza

//gatito

byte gato1a[] = {B00000, B00000, B00000, B10100, B11100, B11100, B01111, B01010};
byte gato1b[] = {B00000, B00000, B00000, B10100, B11100, B11101, B01110, B01010};

//sprites fijos
byte vidas[] = {B00000, B01010, B10101, B10001, B01010, B00100, B00000, B00000};
byte gameover[] = {B00000, B01110, B10101, B11011, B01110, B01110, B00000, B00000};

///////////////////////// SETUP /////////////////////////
void setup() {
//lcd
  lcd.init();
  lcd.backlight();
  
//boton
  pinMode(boton, INPUT);
  
//mileva 
  lcd.createChar(0, mileva1a);
  lcd.createChar(1, mileva2a);
  lcd.createChar(2, mileva1b);
  lcd.createChar(3, mileva2b);
    
//otros
  lcd.createChar(4,vidas);
  lcd.createChar(5,gameover);

//gatito
  lcd.createChar(6,gato1a);
  lcd.createChar(7,gato1b);
}

///////////////////////// LOOP /////////////////////////

void loop() {
  
  int v = 500;
  while (start == 0 ){
    titulo();
    if (digitalRead(boton)){
      start = 1;
    }
  }
  juego();
}

///////////////////////// Pantalla de inicio /////////////////////////

void titulo(){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("MILE vs CATS");
  lcd.setCursor(3, 1);
  lcd.print("press button");
  lcd.setCursor(0, 1);
  lcd.write(0);
  lcd.setCursor(1, 1);
  lcd.write(1);
  lcd.setCursor(15,0);
  lcd.write(6);
  delay(500);
  lcd.setCursor(0, 1);
  lcd.write(2);
  lcd.setCursor(1, 1);
  lcd.write(3);
  lcd.setCursor(15,0);
  lcd.write(7);
  delay(500);

  }

////////////////////// Juego /////////////////////////////


void caminar(int gato_x,int gato_y,int y, int v){
  
  if (v <300){
    lcd.setCursor(gato_x,gato_y);
    lcd.write(6);
    lcd.setCursor(x, y);
    lcd.write(0);
    lcd.setCursor(x+1, y);
    lcd.write(1);
    delay(150);
    }else{
    lcd.setCursor(gato_x,gato_y);
    lcd.write(6);  
    lcd.setCursor(x, y);
    lcd.write(0);
    lcd.setCursor(x+1, y);
    lcd.write(1);
    delay(150);
    lcd.setCursor(x, y);
    lcd.write(2);
    lcd.setCursor(x+1, y);
    lcd.write(3);
    lcd.setCursor(gato_x,gato_y);
    lcd.write(7);
    delay(150);
    }
  }

void choque(int gato_x, int gato_y, int y){
  if (gato_x == x+1 && gato_y == y){
    lcd.setCursor(gato_x,gato_y);
    lcd.write(5);
    lcd.setCursor(gato_x-1,gato_y);
    lcd.write(5);
    delay(500);
    lcd.clear();
    if (vida >1){
        vida -= 1;
        juego();
      } else {
        lcd.setCursor(3,0);
        lcd.print("Game Over");
        lcd.setCursor(3,1);
        lcd.print("Final: "+ String(puntos));
        delay(2000);
        if (high < puntos){
              high = puntos;
        }
        puntos = 0;
        start = 0;
        vida = 3;
        v = 500;
        loop();
      }
    }
  }


  
void juego(){
  
      lcd.clear();
      //posicion del gatito    
      int gato_x = random(9,15);
      int gato_y = 1;
      while(gato_x >=1){
        lcd.setCursor(5,0);
        lcd.print("S:"+String(puntos));
        lcd.setCursor(10,0);
        lcd.print("H:"+String(high));
        if (vida == 3){
          lcd.setCursor(14,0);
          lcd.write(4);
          lcd.setCursor(15,0);
          lcd.write(4);
        }  else  if (vida == 2){
          lcd.setCursor(15,0);
          lcd.write(4);
        }
        int push = digitalRead(boton);
        int y = abajo;
        if (push == HIGH){
          y = arriba;
          }
        caminar(gato_x,gato_y,y,v);
        choque(gato_x,gato_y,y);
        gato_x -=1;
        lcd.clear();
      }
     puntos += 1;
     v -= 50; 
  }
 
