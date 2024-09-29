#include <Servo.h>  // Incluindo biblioteca Servo

Servo servo;  // Criando Objeto Servo, para controle do Servo Motor

uint32_t TempLuzFreio, TempPiscaAlerta, TempSetaDireita, TempSetaEsquerda, pisca_tensao, temp;  // Variáveis necessárias para contagem de tempo em milis segundos (substitui a função delay) - (variáveis uint32_t são inteiros de 32 bits sem sinal)

int JoyAX = 255, JoyAY = 255;  // Variáveis Globais para receberem os valores dos eixo X e Y do JoyStick A
int JoyBX = 90, JoyBY = 90;    // Variáveis Globais para receberem os valores dos eixo X e Y do JoyStick B
// As variáveis JoyAX e JoyBY não serão utilizadas neste código

// Variáveis Globais para auxiliar na identificação de quando um botão foi pressionado no celular
boolean Farol_Ativo = 0;
boolean Pisca_Ativo = 0;
boolean SetaD_Ativo = 0;
boolean SetaE_Ativo = 0;
boolean LuzRe_Ativo = 0;
boolean LuzFreio_Ativo = 0;

float tensao = 0;

int Velocidade = 2;

// Variável Global para armazenar os caracteres que o arduino receber do celular via módulo bluetooth
char DadosRecebidos;


void setup() {

  Serial.begin(9600);  // Inicializando comunicação Serial Padrão nas portas 0 e 1 do arduino
  Serial.println("PROJETO FUSCA BLUETOOTH RC");
  servo.attach(2);  // Informando que o servo motor está conectado ao pino digital 7 do Arduino

  pinMode(3, OUTPUT);   // Leds - Farol
  pinMode(5, OUTPUT);   // Ponte H
  pinMode(6, OUTPUT);   // Ponte H
  pinMode(7, OUTPUT);   // Led - Seta Esquerda Dianteira
  pinMode(8, OUTPUT);   // Led - Seta Direita Dianteira
  pinMode(9, OUTPUT);   // Led - Lanterna / Luz de Freio / Luz de Ré / Seta Direita Trazeira
  pinMode(10, OUTPUT);  // Led - Lanterna / Luz de Freio / Luz de Ré / Seta Esquerda Trazeira


  Serial.println("*.kwl");
  Serial.println("clear_panel()");
  Serial.println("set_grid_size(10,5)");
  Serial.println("add_text(5,1,medium,L,Volts,255,0,0,)");
  Serial.println("add_text(4,1,medium,R,4.02,255,0,0,T)");
  Serial.println("add_text(3,2,large,L,PROJETO GOL RC,245,240,245,)");
  Serial.println("add_text(4,3,large,C,            ARDUINO PARA MODELISMO,245,240,245,)");
  Serial.println("add_text(3,4,small,L,       www.ArduinoParaModelismo.com,245,240,245,)");
  Serial.println("add_button(2,4,11,G,g)");
  Serial.println("add_button(9,0,5,H,h)");
  Serial.println("add_button(9,4,16,E,e)");
  Serial.println("add_button(8,0,4,I,i)");
  Serial.println("add_button(1,0,22,X,x)");
  Serial.println("add_button(0,0,21,Z,z)");
  Serial.println("add_switch(7,4,1,P,p,0,0)");
  Serial.println("add_switch(0,4,1,F,f,0,0)");
  Serial.println("add_free_pad(7,1,10,170,0,50,C,D)");
  Serial.println("add_free_pad(0,1,0,510,0,50,A,B)");
  Serial.println("add_gauge(2,0,4,0,100,75,Z,3.5v,4.2v,10,10)");
  Serial.println("add_buzzer(6,1,1,S,a,false,100.00)");
  Serial.println("add_led(3,1,1,L,0,255,0)");
  Serial.println("set_panel_notes(,,,)");
  Serial.println("run()");
  Serial.println("*");





  void loop() {

    //delay(15);
    DadosRecebidos = Serial.read();  // Variável DadosRecebidos armazena os dados recebidos da comunicação serial entre o celular e o Módulo Bluetooth

    if (DadosRecebidos > 0) {  // Se a variável DadosRecebidos for maior que 0, signigica que alguma informação esta chegando na Serial
      //Serial.println(DadosRecebidos);  // Mostra no Monitor Serial os dados recebidos do celular via Bluetooth
    }
    // JOYSTICK A ACELERAÇÃO
    //  JoyAX = 255;
    //  JoyAY = 255;
    // Neste trecho de código vamos tratar os dados recebidos via Bluetooth para do joystick virtual A (vamos usar apenas o eixo Y para controle de aceleração do motor)
    // Formato de dados enviados pelo Aplicativo: AX222,Y222B
    if (DadosRecebidos == 'A') {           // Verifica se o caractere recebido do celular é igual a 'A' Maiúsculo
      JoyAX = Serial.parseInt();           // Se sim, faz aconversão dos caractéres enviados após o 'A' para inteiro (converte os números de char para int) e armazena na variável JoyBX
      while (DadosRecebidos != 'B') {      // Enquanto os caracteres recebidos não forem iguais a 'B'
        if (Serial.available()) {          // Se houver atividade na comunicação serial (se o celular estiver enviado dodos para o Arduino)
          DadosRecebidos = Serial.read();  // Variável DadosRecebidos armazena os próximos dados enviados pelo celular via bluetooth
          if (DadosRecebidos == 'Y') {     // Se o caractere recebido do celular for igual a 'Y' Maiúsculo
            JoyAY = Serial.parseInt();     // A variável JoyBY recebe a aconversão dos caractéres enviados após o 'Y' para inteiro (converte os números de char para int)
          }
        }
      }

    }

    if (DadosRecebidos == 'C') {           // Verifica se o caractere recebido do celular é igual a 'C' Maiúsculo
      JoyBX = Serial.parseInt();           // Se sim, faz aconversão dos caractéres enviados após o 'C' para inteiro (converte os números de char para int) e armazena na variável JoyBX
      while (DadosRecebidos != 'D') {      // Enquanto os caracteres recebidos não forem iguais a 'D'
        if (Serial.available()) {          // Se houver atividade na comunicação serial (se o celular estiver enviado dados para o Arduino)
          DadosRecebidos = Serial.read();  // Variável DadosRecebidos armazena os próximos dados enviados pelo celular via bluetooth
          if (DadosRecebidos == 'Y') {     // Se o caractere recebido do celular for igual a 'Y' Maiúsculo
            JoyBY = Serial.parseInt();     // A variável JoyBY recebe a aconversão dos caractéres enviados após o 'Y' para inteiro (converte os números de char para int)
          }
        }
      }
    }




    // CONTROLE DE DIREÇÃO (SERVO MOTOR)
    servo.write(JoyBX);  // Configura a posição do Servo de acordo com a posição do joystick (valor da variável JoyBX)



    // CONTROLE DE ACELERAÇÃO, FRENTE, RÉ E PARADO
    // Para a elaboração do controle de aceleração, frente e ré foram levados em consideração as configurações feitas no aplicativo,
    // que envia o valor minimo de 0 e o valor máximo 510, tendo o valor central do envio em 255

    int aux = 0;  // variável para auxiliar na converasão dos valores do joystick para o padrão PWM de 0 a 255

    if (JoyAY <= 250) {  // FRENTE - quando o bastão do joystick virtual é empurado para cima (posição central é = 255, todo para cima = 0)

      if (Velocidade == 1) {
        aux = map(JoyAY, 250, 0, 20, 190);  // Velocidade 01 - LENTA
      } else {
        aux = map(JoyAY, 250, 0, 20, 255);  // Velocidade 02 - RÁPIDA
      }
      // Controle da Ponte H
      analogWrite(5, LOW);            // ativa pino ponte H com valor LOW para que o veículo se movimente para frente
      analogWrite(6, aux);            // ativa pino ponte H com o valor da variável Pot (controle de aceleração)
      Serial.print(" Frente PWM: ");  // Mostra no Monitor Serial
      Serial.println(aux);            // Mostra no Monitor Serial os valores de aux
      TempLuzFreio = millis();        // variável TempSetaDireita recebe o tempo atual
      // Luz de Ré
      digitalWrite(10, LOW);

    }

    else if (JoyAY >= 260) {  // RÉ - quando o bastão do joystick virtual é empurado para baixo (posição central é = 255, todo para baixo = 510)
      if (Velocidade == 1) {
        aux = map(JoyAY, 260, 510, 20, 190);  // Velocidade 01 - LENTA
      } else {
        aux = map(JoyAY, 260, 510, 20, 255);  // Velocidade 02 - RÁPIDA
      }
      // Controle da Ponte H
      analogWrite(5, aux);  // ativa pino ponte H com o valor da variável Pot (controle de aceleração)
      analogWrite(6, LOW);  // ativa pino ponte H com valor LOW para que o veículo se movimente para trás

      //Serial.print(" Re PWM: "); // Mostra no Monitor Serial
      //Serial.println(aux); // Mostra no Monitor Serial os valores de aux

      // Luz de Ré
      digitalWrite(10, HIGH);

      TempLuzFreio = millis();  // variável TempSetaDireita recebe o tempo atual
    }

    else {                  // MOTOR PARADO
      analogWrite(5, LOW);  // desativa as duas portas da ponte h
      analogWrite(6, LOW);  // desativa as duas portas da ponte h

      // Luz de Ré
      digitalWrite(10, LOW);

      // GERENCIA CONTROLE DA LUZ DE FREIO, SETAS, LENTERNA E PISCA ALERTA DO FUSCA
      // if ((Pisca_Ativo == LOW) && (SetaD_Ativo == LOW) && (SetaE_Ativo == LOW)) {
      // Verifica se as variáveis indicando atividade do pisca, seta direita e seta esquerda estão todas desativadas.
      if (millis() - TempLuzFreio < 50) {
        // Se o tempo decorrido desde a última atualização da luz de freio for menor que 150 milissegundos:
        // digitalWrite(9, LOW);
        //  Serial.println(" luz freio apagado - 150");
        // Apaga os LEDs conectados aos pinos 9 e 10 e imprime uma mensagem indicando a condição.
      } else if ((millis() - TempLuzFreio > 50) && (millis() - TempLuzFreio < 650)) {
        // Se o tempo decorrido estiver entre 300 e 1000 milissegundos:
        if (Farol_Ativo == LOW) {
          digitalWrite(9, HIGH);
          Serial.println(" luz freio aceso - 1000");
        } else {
          digitalWrite(9, LOW);
          Serial.println(" luz freio apagada - 1000");
        }
        // Acende os LEDs conectados aos pinos 9 e 10 e imprime uma mensagem indicando a condição.
      } else if ((millis() - TempLuzFreio > 650) && (millis() - TempLuzFreio < 1250)) {
        // Se o tempo decorrido estiver entre 1000 e 1500 milissegundos:
        digitalWrite(9, LOW);
        Serial.println(" luz freio apagado - 1000 a 1500");
        // Apaga os LEDs conectados aos pinos 9 e 10 e imprime uma mensagem indicando a condição.
      }
      // }
    }



    //if (DadosRecebidos == 'Z') {
      //Velocidade = 1;
      //tone(4, 400, 100);
    //}
    //if (DadosRecebidos == 'X') {
      //Velocidade = 2;
      //tone(4, 400, 100);
      //delay(100);
      //tone(4, 200, 100);
    //}




    // FAROL e LANTERNA
    if (DadosRecebidos == 'F') {
      // Se o caractere recebido for 'F':
      digitalWrite(3, HIGH);                       // Liga o farol
      Farol_Ativo = HIGH;                          // Atualiza o estado do farol para ativo
      Serial.println(" Botão Farol Pressionado");  // Imprime uma mensagem indicando que o botão do farol foi pressionado
    }

    if (DadosRecebidos == 'f') {
      // Se o caractere recebido for 'f':
      digitalWrite(3, LOW);  // Desliga o farol
      Farol_Ativo = LOW;     // Atualiza o estado do farol para inativo

      // Lanternas
      //  if ((Pisca_Ativo == LOW) && (SetaD_Ativo == LOW) && (SetaE_Ativo == LOW)) {
      // Se nenhum pisca ou seta estiver ativo:
      //  digitalWrite(9, LOW);   // Desliga a lanterna direita
      //}
      Serial.println(" Botão Farol Pressionado");  // Imprime uma mensagem indicando que o botão do farol foi pressionado
    }

    if (Farol_Ativo == HIGH) {
      // Se o farol estiver ativo e nenhum pisca ou seta estiver ativo:
      digitalWrite(9, HIGH);  // Liga a lanterna direita
    }
    ////////////////////
    if (Farol_Ativo == LOW) {
      // Se o farol estiver ativo e nenhum pisca ou seta estiver ativo:
      digitalWrite(9, LOW);  // Liga a lanterna direita
    }
    ////////////////////////
    // Pisca FAROL
    if (DadosRecebidos == 'G') {
      // Se o caractere recebido for 'G':
      digitalWrite(3, !Farol_Ativo);   // Inverte o estado do farol
      Serial.println(DadosRecebidos);  // Imprime o caractere recebido
    }

    if (DadosRecebidos == 'g') {
      // Se o caractere recebido for 'g':
      digitalWrite(3, Farol_Ativo);    // Mantém o estado atual do farol
      Serial.println(DadosRecebidos);  // Imprime o caractere recebido
    }



    // PISCA-ALERTA
    if (DadosRecebidos == 'P') {
      // Se o caractere recebido for 'P':
      Pisca_Ativo = HIGH;              // Ativa o pisca-alerta
      ApagaSetas();                    // Desativa as setas
      PiscaAlerta();                   // Ativa o pisca-alerta
      Serial.println(DadosRecebidos);  // Imprime o caractere recebido
      TempPiscaAlerta = millis();      // Armazena o tempo atual para controle do pisca-alerta
    }

    if (DadosRecebidos == 'p') {
      // Se o caractere recebido for 'p':
      Pisca_Ativo = LOW;               // Desativa o pisca-alerta
      ApagaSetas();                    // Desativa as setas
      Serial.println(DadosRecebidos);  // Imprime o caractere recebido
      TempPiscaAlerta = millis();      // Armazena o tempo atual para controle do pisca-alerta
    }

    if (Pisca_Ativo) {
      // Se o pisca-alerta estiver ativo:
      SetaD_Ativo = LOW;                     // Desativa a seta direita
      SetaE_Ativo = LOW;                     // Desativa a seta esquerda
      PiscaAlerta();                         // Ativa o pisca-alerta
      Serial.println("PISCA ALERTA ATIVO");  // Imprime uma mensagem indicando que o pisca-alerta está ativo
    }

    if (DadosRecebidos == 'H') {
      // Se o caractere recebido for 'H':
      SetaD_Ativo = !SetaD_Ativo;      // Inverte o estado da seta direita
      ApagaSetas();                    // Desativa as setas
      Serial.println(DadosRecebidos);  // Imprime o caractere recebido
      TempSetaDireita = millis();      // Armazena o tempo atual para controle da seta direita
    }

    if (SetaD_Ativo) {
      // Se a seta direita estiver ativa:
      SetaE_Ativo = LOW;               // Desativa a seta esquerda
      SetaDireita();                   // Ativa a seta direita
      Serial.println("SETA D ATIVA");  // Imprime uma mensagem indicando que a seta direita está ativa
    }

    if (DadosRecebidos == 'I') {
      // Se o caractere recebido for 'I':
      SetaE_Ativo = !SetaE_Ativo;      // Inverte o estado da seta esquerda
      ApagaSetas();                    // Desativa as setas
      Serial.println(DadosRecebidos);  // Imprime o caractere recebido
      TempSetaEsquerda = millis();     // Armazena o tempo atual para controle da seta esquerda
    }

    if (SetaE_Ativo) {
      // Se a seta esquerda estiver ativa:
      SetaD_Ativo = LOW;               // Desativa a seta direita
      SetaEsquerda();                  // Ativa a seta esquerda
      Serial.println("SETA E ATIVA");  // Imprime uma mensagem indicando que a seta esquerda está ativa
    }



    // Envio de dados para o Celular
    if (millis() - temp > 5000) {
      // Se passaram mais de 5000 milissegundos desde a última execução:
      readVcc();                                  // Chama a função que lê a tensão da bateria
      Serial.print("*T" + String(tensao) + "*");  // Envia via Bluetooth para o celular a Tensão da Bateria em um formato adequado para o aplicativo.

      int bateria = map((tensao * 10), 34, 42, 0, 100);  // Converte a tensão da bateria em porcentagem (3 volts igual a 0%, 4.2 volts igual a 100%).
      Serial.print("*Z" + String(bateria) + "*");        // Envia via Bluetooth para o celular o valor útil em porcentagem da bateria.

      temp = millis();  // Atualiza a variável temp com o tempo atual

      if (tensao > 3.8) {
        Serial.print("*LR0G255B0*");  // Envia via Bluetooth para o celular a cor para o indicador de bateria (verde), formato adequado para o aplicativo.
      } else if (tensao < 3.6) {
        Serial.print("*LR255G0B0*");  // Envia via Bluetooth para o celular a cor para o indicador de bateria (vermelho), formato adequado para o aplicativo.
      } else {
        Serial.print("*LR255G255B0*");  // Envia via Bluetooth para o celular a cor para o indicador de bateria (amarelo), formato adequado para o aplicativo.
      }
    }

    if (tensao < 3.6) {                                      // Verifica se a tensão da bateria é menor que 3.6 volts
      if (millis() - pisca_tensao > 10000) {                   // Se passaram mais de 10000 milissegundos desde o último pisca de alerta:
        Serial.print("*W*");                                 // Envia via Bluetooth para o celular um comando de alerta
        digitalWrite(9, HIGH);
        delay(500);
        digitalWrite(9, LOW);
        delay(500);
        digitalWrite(9, HIGH);
        delay(500);
        digitalWrite(9, LOW);
        delay(500);
        digitalWrite(9, HIGH);
        delay(500);
        digitalWrite(9, LOW);
        pisca_tensao = millis();  // Atualiza a variável pisca_tensao com o tempo atual
      }
    }
  }

  // Função para ler a tensão da alimentação da Bateria
  int readVcc() {
    // Configura o registrador ADMUX para medir a referência interna de 1.1V
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);

    delay(2);  // Aguarda 2 milissegundos (tempo de estabilização)

    ADCSRA |= _BV(ADSC);  // Inicia a conversão analógico-digital (AD)
    while (bit_is_set(ADCSRA, ADSC))
      ;  // Aguarda a conclusão da conversão

    uint8_t low = ADCL;   // Lê primeiro o registrador ADCL - trava ADCH
    uint8_t high = ADCH;  // Lê o registrador ADCH - destrava ADCH

    // Combina os valores lidos para obter o resultado da conversão
    tensao = (high << 8) | low;

    // Calcula a tensão em milivolts usando a fórmula: Vcc = 1125300 / tensao
    tensao = 1125300L / tensao;

    // Converte a tensão para volts dividindo por 1000
    tensao = tensao / 1000;

    // Limita a tensão máxima para 4.2V para evitar leituras incorretas
    if (tensao > 4.2) {
      tensao = 4.2;
    }

    // A leitura da tensão está disponível na variável global 'tensao'
    // Serial.println(tensao); // Ativação dessa linha imprimiria a tensão no console Serial (descomente se necessário)
  }


  // Função para acionar a seta direita
  void SetaDireita() {
    // Verifica se passaram mais de 500 milissegundos desde a última execução
    if (millis() - TempSetaDireita > 500) {
      // Inverte o estado dos LEDs conectados aos pinos 7 e 9 (seta direita)
      digitalWrite(7, !digitalRead(7));
      TempSetaDireita = millis();  // Atualiza a variável TempSetaDireita com o tempo atual
    }
  }

  // Função para acionar a seta esquerda
  void SetaEsquerda() {
    // Verifica se passaram mais de 500 milissegundos desde a última execução
    if (millis() - TempSetaEsquerda > 500) {
      // Inverte o estado dos LEDs conectados aos pinos 8 e 10 (seta esquerda)
      digitalWrite(8, !digitalRead(8));
      // Emite um breve tom no buzzer (o meu n tem buzzer)
      //tone(4, 30, 30);
      TempSetaEsquerda = millis();  // Atualiza a variável TempSetaEsquerda com o tempo atual
    }
  }

  // Função para acionar o pisca-alerta
  void PiscaAlerta() {
    // Verifica se passaram mais de 500 milissegundos desde a última execução
    if (millis() - TempPiscaAlerta > 500) {
      // Inverte o estado dos LEDs conectados aos pinos 7, 9, 8 e 10 (pisca-alerta)
      digitalWrite(7, !digitalRead(7));
      digitalWrite(8, !digitalRead(8));
      // Emite um breve tom no buzzer
      //tone(4, 30, 30);
      TempPiscaAlerta = millis();  // Atualiza a variável TempPiscaAlerta com o tempo atual
    }
  }

  // Função para apagar todas as setas
  void ApagaSetas() {
    // Desliga os LEDs conectados aos pinos 7, 9, 8 e 10 (todas as setas)
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }

  // FIM DO CÓDIGO
