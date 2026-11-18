#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD 16x2 - I2C 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte buttonAddTime = 3;   // Selecionar / +5 min / iniciar (segurar)
const byte buttonIncrease = 4;  // Sabotagem: +7 s; Dominacao: Amarelo
const byte buttonDecrease = 5;  // Sabotagem: -9 s; Dominacao: Azul
const byte buzzerPin = 6;

const unsigned long HOLD_MS = 2000;
const unsigned long DEBOUNCE_MS = 40;
const int MAX_SETUP_SECONDS = 99 * 60;

enum Mode { SABOTAGEM, DOMINACAO };
Mode currentMode = SABOTAGEM;

// Escreve uma linha inteira sem deixar caracteres da tela anterior.
void lcdLine(byte line, const char *message) {
  lcd.setCursor(0, line);
  byte i = 0;
  while (message[i] != '\0' && i < 16) {
    lcd.print(message[i++]);
  }
  while (i++ < 16) lcd.print(' ');
}

void showHome() {
  lcdLine(0, "       C4");
  lcdLine(1, "    AIRSOFT");
}

void showMode() {
  lcdLine(0, "      MODO");
  lcdLine(1, currentMode == SABOTAGEM ? "   SABOTAGEM" : "   DOMINACAO");
}

void formatTime(int totalSeconds, char out[6]) {
  unsigned int m = (unsigned int)totalSeconds / 60;
  unsigned int s = (unsigned int)totalSeconds % 60;
  snprintf(out, 6, "%02u:%02u", m, s);
}

void showSetup(int totalSeconds) {
  char t[6];
  formatTime(totalSeconds, t);
  lcdLine(0, "     TEMPO");
  char buffer[17];
  snprintf(buffer, sizeof(buffer), "     %s", t);
  lcdLine(1, buffer);
}

void showSabotagem(int remainingSeconds) {
  char t[6];
  formatTime(remainingSeconds, t);
  lcdLine(0, "   SABOTAGEM");
  char buffer[17];
  snprintf(buffer, sizeof(buffer), "     %s", t);
  lcdLine(1, buffer);
}

// Soltou os botoes: exibe modo e tempo.
// Segurou uma equipe: exibe TIME DOMINANDO e a cor.
void showDominacao(int remainingSeconds, byte teamHeld) {
  if (teamHeld == 1) {
    lcdLine(0, " TIME DOMINANDO");
    lcdLine(1, "    AMARELO");
  } else if (teamHeld == 2) {
    lcdLine(0, " TIME DOMINANDO");
    lcdLine(1, "      AZUL");
  } else {
    char t[6], buffer[17];
    formatTime(remainingSeconds, t);
    snprintf(buffer, sizeof(buffer), "     %s", t);
    lcdLine(0, "   DOMINACAO");
    lcdLine(1, buffer);
  }
}

void beepStart() {
  for (byte i = 0; i < 2; i++) {
    tone(buzzerPin, 959, 250);
    delay(350);
  }
  noTone(buzzerPin);
}

void beepFinish() {
  for (byte i = 0; i < 10; i++) {
    tone(buzzerPin, 959, 100);
    delay(180);
  }
  noTone(buzzerPin);
}

void waitRelease(byte pin) {
  while (digitalRead(pin) == LOW) delay(10);
  delay(DEBOUNCE_MS);
}

void waitForReset() {
  // Evita reinicio automatico se o botao ainda estava pressionado.
  waitRelease(buttonAddTime);
  while (digitalRead(buttonAddTime) == HIGH) delay(10);
  waitRelease(buttonAddTime);
}

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(buttonAddTime, INPUT_PULLUP);
  pinMode(buttonIncrease, INPUT_PULLUP);
  pinMode(buttonDecrease, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  showHome();
}

void loop() {
  // C4 AIRSOFT -> escolha do modo.
  showHome();
  while (digitalRead(buttonAddTime) == HIGH) delay(10);
  waitRelease(buttonAddTime);

  currentMode = SABOTAGEM;
  showMode();

  while (true) {
    if (digitalRead(buttonIncrease) == LOW) {
      currentMode = SABOTAGEM;
      showMode();
      waitRelease(buttonIncrease);
    }
    if (digitalRead(buttonDecrease) == LOW) {
      currentMode = DOMINACAO;
      showMode();
      waitRelease(buttonDecrease);
    }
    if (digitalRead(buttonAddTime) == LOW) {
      waitRelease(buttonAddTime);
      break;
    }
  }

  // A tela TEMPO aparece nos DOIS modos.
  int configuredSeconds = 0;
  showSetup(configuredSeconds);
  bool started = false;

  while (!started) {
    if (digitalRead(buttonAddTime) == LOW) {
      unsigned long pressedAt = millis();
      while (digitalRead(buttonAddTime) == LOW) {
        if (millis() - pressedAt >= HOLD_MS) {
          if (configuredSeconds > 0) {
            started = true;
          } else {
            lcdLine(0, "DEFINA O TEMPO");
            lcdLine(1, "ANTES DE INICIAR");
            waitRelease(buttonAddTime);
            showSetup(configuredSeconds);
          }
          break;
        }
        delay(10);
      }
      if (!started && digitalRead(buttonAddTime) == HIGH &&
          millis() - pressedAt < HOLD_MS) {
        // Toque curto: acrescenta 5 minutos.
        configuredSeconds += 5 * 60;
        if (configuredSeconds > MAX_SETUP_SECONDS)
          configuredSeconds = MAX_SETUP_SECONDS;
        showSetup(configuredSeconds);
        delay(DEBOUNCE_MS);
      }
      if (started) waitRelease(buttonAddTime);
    }
  }

  int remainingSeconds = configuredSeconds;
  unsigned long yellowMilliseconds = 0, blueMilliseconds = 0;
  byte displayedTeam = 0;

  beepStart();
  if (currentMode == SABOTAGEM) showSabotagem(remainingSeconds);
  else showDominacao(remainingSeconds, 0);

  unsigned long lastSecond = millis();
  unsigned long lastLoop = lastSecond;
  unsigned long lastAdjustment = 0;
  byte lastAdjustmentButton = 0;
  const unsigned long ADJUST_REPEAT_MS = 250; // repeticao ao manter pressionado

  while (remainingSeconds > 0) {
    unsigned long now = millis();
    bool inc = (digitalRead(buttonIncrease) == LOW);
    bool dec = (digitalRead(buttonDecrease) == LOW);
    bool changed = false;

    if (currentMode == DOMINACAO) {
      // So pontua enquanto UM botao de equipe estiver pressionado.
      // Se ambos estiverem pressionados, nao pontua para nenhum.
      byte teamHeld = (inc && !dec) ? 1 : ((!inc && dec) ? 2 : 0);
      unsigned long elapsed = now - lastLoop;
      if (displayedTeam == 1) yellowMilliseconds += elapsed;
      if (displayedTeam == 2) blueMilliseconds += elapsed;
      if (teamHeld != displayedTeam) {
        displayedTeam = teamHeld;
        changed = true;
      }
    } else {
      // Primeiro ajuste ao pressionar; repete enquanto mantem pressionado.
      byte adjustment = (inc && !dec) ? 1 : ((!inc && dec) ? 2 : 0);
      if (adjustment == 0) {
        lastAdjustmentButton = 0;
      } else if (adjustment != lastAdjustmentButton ||
                 now - lastAdjustment >= ADJUST_REPEAT_MS) {
        if (adjustment == 1) {
          remainingSeconds += 7;
          if (remainingSeconds > MAX_SETUP_SECONDS + 59)
            remainingSeconds = MAX_SETUP_SECONDS + 59;
        } else {
          remainingSeconds -= 9;
          if (remainingSeconds < 0) remainingSeconds = 0;
        }
        lastAdjustment = now;
        lastAdjustmentButton = adjustment;
        changed = true;
      }
    }
    lastLoop = now;

    while (remainingSeconds > 0 && now - lastSecond >= 1000UL) {
      lastSecond += 1000UL;
      remainingSeconds--;
      changed = true;
    }

    if (changed && remainingSeconds > 0) {
      if (currentMode == SABOTAGEM) showSabotagem(remainingSeconds);
      else showDominacao(remainingSeconds, displayedTeam);
    }
    delay(10);
  }

  // Finais conforme o fluxograma.
  if (currentMode == SABOTAGEM) {
    lcdLine(0, "      BOMBA");
    lcdLine(1, "    DETONADA!");
  } else {
    lcdLine(0, "DOMINACAO");
    lcdLine(1, "   CONCLUIDA");
  }
  beepFinish();

  if (currentMode == DOMINACAO) {
    delay(1400);
    lcdLine(0, "FIM DE JOGO");
    if (yellowMilliseconds > blueMilliseconds) lcdLine(1, "VENCEU: AMARELO");
    else if (blueMilliseconds > yellowMilliseconds) lcdLine(1, "VENCEU: AZUL");
    else lcdLine(1, "EMPATE");
  }

  waitForReset();
  // A proxima passagem pelo loop retorna a C4 AIRSOFT.
}
