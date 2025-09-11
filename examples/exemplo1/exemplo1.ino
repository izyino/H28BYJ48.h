
//
// Exemplo n.1 de utilização da biblioteca H28BYJ48.h
// emite beeps e piscadas de led, e movimentos repetitivos
// -----------------------------------------------------------
// Pressupõe um motor de passo 28byj-48 ou até dois motores DC
// (o n.0 nos pinos 1 e 2 de CN1 e o n.1 pinos 3 e 4 de CN1) 
// -----------------------------------------------------------
//


#include <H28BYJ48.h>

H28BYJ48 x(2);                           //0 indica motor(es) DC em CN1 
                                         //1,2 ou 3=indica motor de passo em CN1

bool sent=false;
uint32_t voltas;

void setup() {
  x.begin();
  Serial.begin(115200);
}

void loop() {

  if (x.xtipostep==0){                    //se há motor(es) DC conectado(s)
    x.beep(2, 200, 2000, 100);            //emite 2 beep de 200ms cada, 2000Hz, intervalo entre eles de 100ms 
    x.led(20, 100, 50);                   //pisca o LED 20 vezes com 100ms aceso e 50ms apagado

    if (x.timetogo(0)==0){                //se o motor DC 0 estiver parado,
      x.runDC(0, 2500, 100, 1);           //ativa motor DC 0 por 2,5s, vel 100%
    }  
    if (x.timetogo(1)==0){                //se o motor DC 1 estiver parado,
      x.runDC(1, 5000, 75, 0);            //ativa motor DC 1 por 5s, vel 50%
    }
  }  

  if (x.xtipostep!=0){                    //se há motor de passo conectado
    if (x.stepstogo()==0){                //e se o motor de passo já chegou ao seu último destino (está parado)
      x.beep(2, 200, 2000, 100);          //emite 2 beep de 200ms cada, 2000Hz, intervalo entre eles de 100ms 
      x.led(20, 100, 50);                 //pisca o LED 20 vezes com 100ms aceso e 50ms apagado
      sent=!sent;                         //inverte o sentido, voltas entre 1 e 10
      voltas=random(1, 11)*2048;          //velocidade entre 2 e 12 RPM, e começa a girar
      x.runStep(voltas, random(2,13), sent);   
    }  
  }
   
  x.setms(6000);
  while(x.getms()>0){}                    //apenas exemplo de espera não blocante (6 segundos)
}

