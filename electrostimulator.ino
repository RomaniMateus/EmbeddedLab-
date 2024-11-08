// Definindo as entradas de cada componente do sistema
int BT1 = 7;
int BT2 = 2;
int RED_LED = 3;
int YELLOW_LED = 4;
int GREEN_LED = 5;
int WHITE_LED = 6;
int DEBOUNCE_DELAY = 200;

int lastDebounceTime = 0;
int stim_mode = -1;
unsigned long bt2PressStartTime = 0;
bool redLedOn = false;
bool bt2Held = false;

void setup()
{
    Serial.begin(9600);
  
    // Declarando os componentes como entrada e saída
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(WHITE_LED, OUTPUT);
    pinMode(BT1, INPUT);
    pinMode(BT2, INPUT);
}

void loop()
{
    int bt1_clicked = !digitalRead(BT1);
  	int currentMillis = millis();
  
    // Esta condicional é responsável pela eliminação do ruído ao clica em BT1
    if (bt1_clicked && (currentMillis - lastDebounceTime) > DEBOUNCE_DELAY)
    {   
      	
      	// Definindo qual LED será acesso conforme o clique em BT1
        stim_mode = (stim_mode+1) % 3;    
        switch(stim_mode)
        {
            case 0:
                digitalWrite(YELLOW_LED, HIGH);
                digitalWrite(GREEN_LED, LOW);
                digitalWrite(WHITE_LED, LOW);
                break;
          
            case 1:
                digitalWrite(YELLOW_LED, LOW);
                digitalWrite(GREEN_LED, HIGH);
                digitalWrite(WHITE_LED, LOW);
                break;
          
            case 2:
                digitalWrite(YELLOW_LED, LOW);
                digitalWrite(GREEN_LED, LOW);
                digitalWrite(WHITE_LED, HIGH);
                break;
          
            default:
                Serial.println("Something is wrong. Exiting...");
                break;
        }
        
        lastDebounceTime = currentMillis;  
    }
    
  
    // Lógica para BT2
    int bt2_state = !digitalRead(BT2);
  
    if (bt2_state)
    {
        // Esta condicional liga o LED vermelho apenas se o botão BT2 não estiver sendo pressionado
        if (!redLedOn && !bt2Held)
        {
            digitalWrite(RED_LED, HIGH); 
            redLedOn = true;
            bt2PressStartTime = millis();
        }
      
        // Esta condicional verifica o tempo que o botão BT2 foi mantido pressionado
        else if (millis() - bt2PressStartTime >= 3000)
        {
            digitalWrite(RED_LED, LOW);
            redLedOn = false;
            bt2Held = true;
        }
    }
    else
    {
        // Reiniciando a contagem para o caso do botão BT2 ser solto antes dos 3 segundos
        bt2Held = false;
        bt2PressStartTime = millis();
    }
}