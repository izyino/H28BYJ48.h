Para facilitar o desenvolvimento de aplicações a serem hospedadas na placa PCI CTRL-H28BYJ48, foi criada uma biblioteca de nome H28BYJ48.h, disponível em https://github.com/izyino/H28BYJ48.h a qual dispõe das seguintes funções:
--------------------------------------------------------------------------------------------------------

#include <H28BYJ48.h>

para incluir a biblioteca ao programa. Dependendo de onde a biblioteca estiver gravada, pode-se usar alternativamente o formato #include “H28BYJ48.h”


--------------------------------------------------------------------------------------------------------
PCI_UG_Tx x(t0);

comando construtor que deve ser informado logo após o include, sendo t0 uma variável do tipo uint8_t que define o tipo de motor conectado a CN1, sendo possível os seguintes valores:

0 – Para motor DC<br>
1 – Para motor 28byj-48, 2048 passos por volta, baixo torque, baixo consumo<br>
2 – Para motor 28byj-48, 2048 passos por volta, alto torque, alto consumo<br>
3 – Para motor 28byj-48, 4096 passos por volta, médio torque, médio consumo<br>

--------------------------------------------------------------------------------------------------------
x.begin();

inicializa as diversas funções da biblioteca. Deve ser colocado na sessão de setup de todos os programas que se utilizem da biblioteca 

--------------------------------------------------------------------------------------------------------
x.runStep(steps, velstep, cwstep);

comando que ativa o motor de passo, de forma automática e assíncrona, conforme as seguintes variáveis:

steps – variável uint32_t contendo o número de passos a movimentar

velstep – variável unint8_t que define a velocidade da movimentação, em RPM (Rotações Por Minuto). Valores entre 1 e 16 são geralmente aceitáveis

cwstep – variável booleana que define o sentido da movimentação, sendo “true” para sentido horário e “false” para sentido anti-horário 

--------------------------------------------------------------------------------------------------------
x.stepstogo();

esta função retorna no formato uint32_t o número de passos ainda restantes para que o motor chegue ao seu destino. Zero significa que o motor já chegou ao seu último destino e já encontra-se parado. Antes de comandar qualquer movimentação deve-se consultar esta função para ter certeza que o motor encontra-se parado

--------------------------------------------------------------------------------------------------------
x.runDC(n, time, veldc, cwdc);

comando que ativa o motor DC, de forma automática e assíncrona, conforme as seguintes variáveis:

n – variável uint8_t com número do motor DC que será movimentado (0 ou 1):<br>
Se	n=0,	o motor DC deverá estar conectado aos pinos 1 e 2 do CN1<br>
Se	n=1,	o motor DC deverá estar conectado aos pinos 3 e 4 do CN1<br>
 
time – variável uint32_t contendo o tempo em milisegundos que o motor DC ficará ativado

velDC – variável unint8_t que define a velocidade da movimentação, em termos de  porcentagem entre 0 e 100. Sendo 0=0% motor parado, 100=100% motor com velocidade máxima.

cwDC – variável booleana que define o sentido da movimentação, sendo “true” para sentido horário e “false” para sentido anti-horário 

--------------------------------------------------------------------------------------------------------

x.timetogo(n);

esta função retorna no formato uint32_t, em milisegundos, o tempo ainda restante para que o motor DC n complete o último comando runDC. Se retornar zero significa que o motor DC n já está parado. Antes de comandar qualquer movimentação do motor DC n deve-se consultar esta função para ter certeza que o mesmo se encontra parado

--------------------------------------------------------------------------------------------------------
x.beep(bnum, bdur, bfreq, binter);

comando que ativa a emissão de beeps sonoros, de forma automática e assíncrona, conforme as seguintes variáveis:

bnum – variável inteira que especifica o número de beeps a serem emitidos

bdur – variável inteira que especifica a duração de cada beep, em milisegundos 

bfreq – variável inteira que especifica a freqüência dos beeps, em Hertz (Hz)

binter – variável inteira que especifica a duração da pausa entre os beeps, em milisegundos 

--------------------------------------------------------------------------------------------------------
x.led(lnum, ldur, linter);

comando que ativa piscadas do Led, de forma automática e assíncrona, conforme as seguintes variáveis:

lnum – variável inteira que especifica o número de piscadas a serem emitidas

ldur – variável inteira que especifica a duração do Led acesso em cada piscada, em milisegundos 

linter – variável inteira que especifica a duração do Led apagado em cada piscada, em milisegundos 

--------------------------------------------------------------------------------------------------------
x.setms(yms);

comando para inicializar o contador de milisegundos com o valor informado pela variável yms do tipo uint32_t. Imediatamente após inicializado, o contador começa ser subtraído de 1 a cada milisegundo

--------------------------------------------------------------------------------------------------------
x.getms();

esta função retorna no formato uint32_t o estado antes do contador de milisegundos previamente inicializado pelo comando x.setms. Serve como alternativa para a função delay(), de forma assíncrona

--------------------------------------------------------------------------------------------------------
x.stopStep();

esta função interrompe o movimento do motor de passo

--------------------------------------------------------------------------------------------------------
x.stopDC(n);

esta função interrompe o movimento do motor DC n (n=0 ou 1)

--------------------------------------------------------------------------------------------------------
x.stopBeep();

esta função interrompe a emissão de beeps sonoros

--------------------------------------------------------------------------------------------------------
x.stopLed();

esta função interrompe as piscadas do Led<br>


############################################################################################<br>
Exemplos de utilização da biblioteca<br>

No início do programa:<br>
#include <H28BYJ48.h><br>
H28BYJ48 x(2);<br>

na sessão do setup:<br>
x.begin();<br>

--------------------------------------------------------------------------------------------------------
//movimenta o motor de passo (conectado em CN1), tipo 28BYJ-48, <br>
//velocidade 3, sentido horário, 2048 passos:<br>

//função principal:<br>
x.runStep(2048, 3, true);<br>
//o motor começa a se movimentar imediatamente após a função runStep ser executada<br>

//para saber se o motor de passo n.0 já chegou ao destino, fazer<br>
if (x.stepstogo()>0) {ainda não chegou ao destino. Está em movimento...};<br>

//a qualquer momento o movimento do motor de passo n.0 pode ser interrompido<br>
x.stopStep();<br>


--------------------------------------------------------------------------------------------------------
//movimenta o motor DC n.0 (conectado aos pinos 1 e 2 do CN1),<br>
//velocidade 75%, sentido anti-horário, durante 15segundos:<br>

//função principal:<br>
x.runDC(0, 15000, 75, false);<br>
//o motor começa a se movimentar imediatamente após a função runDC ser executada<br>

//para saber se o motor DC nº0 ainda está girando ou já esta parado, fazer<br>
if (x.timetogo(0)>0) {ainda não terminou o último comando runDC. Está em movimento...};<br>

//a qualquer momento o movimento do motor DC n.0 pode ser interrompido<br>
x.stopDC(0);


--------------------------------------------------------------------------------------------------------
//emite 10 beeps de 2KHz de 0,5s com pausa interbeeps de 0,25s:<br>

//função principal:<br>
x.beep(10, 500, 2000, 250);<br>
//os beeps começam a ser emitidos imediatamente após a função beep ser executada<br>

//a qualquer momento a emissão dos beeps sonoros pode ser interrompida<br>
x.stopBeep();<br>


--------------------------------------------------------------------------------------------------------
//pisca o Led 50 vezes com 0,25s aceso seguido de 0,10s apagado: <br>

//função principal:<br>
x.led(50, 250, 100);<br>
//o Led começa a piscar imediatamente após a função led ser executada<br>

//a qualquer momento as piscadas do Led podem ser interrompidas<br>
x.stopLed();<br>


--------------------------------------------------------------------------------------------------------
//contagem de 4 segundos, de forma assíncrona:<br>

//função principal:<br>
x.setms(4000);<br>
while (x.getms()>0){enquanto espera 4s, pode fazer coisas…}<br>
//a variável x.xms começa a ser decrementada a cada um milisegundo imediatamente após ter sido inicializada pela função setms<br>

############################################################################################<br>
