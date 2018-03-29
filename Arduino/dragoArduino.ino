// Numeri di Pin programmati
int numled = 7;

// Dichiaraione dei numeri dei pin da programmare
int led[] = {3, 5, 6, 9, 10, 11, 13};

// Variabili per limiatare i dati da twitter (ricevendo i dati da Python)
int tweetnum = 0;       // Conteggio per il numero di tweet
boolean receivetweet = true;        // Booleana per checkare la ricezione dei dati su Twitter
int tweettimer = 0;         // Timer per stoppare per un determinato periodo di tempo la rcezione dei dati da Twitter

// Luminosità del led
float brightness = 0;    // Valore della pulsazione che verrà passata alla funzione sinusoidale
float basicPulse = 0.015;
float fadeAmount = 0.015;    // Velocità di pulsazione
int tweetlimit = 3;       // Numero massimo di Tweet da ricevere prima della pausa

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(led[i], OUTPUT);
  }

  // Inizializza la porta seriale
  Serial.begin(9600);
}

void loop() {
  // Applica la luminosità ad un valore cos, in modo da avere un respiro sinusoidale e non scalare
  float val = sin(brightness);
  float newval = val;

  val = abs(val);

  newval = abs(newval);

  if (val > 0.4 && val < 0.6) {
    newval = 0.5;
  }

  float newfade;

  if (newval < 0.5) {
    newfade = fadeAmount*1;
  } else {
    newfade = fadeAmount * 2;
  }

  // Se il valore scende sotto a 1 (lato negativo dell'onda)
  // Riporta quel valore al suo valore positivo
  /*if (val < 0.00) {
    val *= -1;
  }*/

  // Se il valore è prossimo allo 0, riportalo a 0
  if (val < 0.0075) {
    val = 0.00;
  }

  // Scrivi il valore della pulsazione sui pin PWM programmati
  for (int i = 0; i < 7; i++) {
    analogWrite(led[i], val*255);
  }

  // Se la porta seriale c'è
  if (Serial.available()) {
    // Leggi il char che arriva sulla porta seriale
    char c = Serial.read();
    // Se il valore ricevuto è uguale a '1' e la ricezione dei tweet è attiva
    // Allora aumenta la velocità di pulsazione e conta il tweet
    if (c == 'q' && receivetweet) {
      fadeAmount += 0.05;
      tweetnum++;
    }
  }

  // Dopo 3 tweet bloccane la ricezione
  if (tweetnum > 2) {
    receivetweet = false;
  }

  // Se smette di ricevere i tweet conta
  if (!receivetweet) {
    tweettimer++;
  }

  // A prescindere, se non riceve tweet per un periodo di tempo diminuisce il counter
  if (tweetnum > 0 && millis()%2000 == 0) {
    tweetnum--;
  }

  // Quando finsce il conteggio, riattiva il tweet e resetta il timer
  if (tweettimer > 500) {
    receivetweet = true;
    tweettimer = 0;
    tweetnum = 0;
  }

  // Invia i dati sulla porta seriale per Python
  int c = int(newval * 127);
  //Serial.print("newval: ");
  //Serial.print(newval);
  //Serial.print("c: " );
  Serial.println(c);
  Serial.println(newfade);
  //Serial.println(c);

  // Se la velocità di pulsazione è maggiore di quella regolare e passano 10 millisecondi
  // Rallenta la velocità di pulsazione
  if (fadeAmount > 0.015 && millis() % 5 == 0) {
    fadeAmount -= 0.01;
  }

  // Limita il valore della velocità di pulsazione, per evitare che pulsi troppo velocemente
  if (fadeAmount > 0.20) {
    fadeAmount = 0.19;
  }

  // Aggiungi alla luminosità di base la velocità di pulsazione
  brightness += newfade;

  // Se il valore di pulsazione è 0, aspetta mezzo secondo
  if (newval < 0.02) {
    delay(500);
  }

  // Diamo un delay qua così, per puro sfizio
  delay(30);
}

