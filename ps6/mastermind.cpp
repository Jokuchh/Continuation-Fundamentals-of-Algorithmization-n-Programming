#include <stdlib.h>
#include <stdio.h>
#include <Arduino.h>
#include "mastermind.h"
#include "lcd_wrapper.h"


char* generate_code(bool repeat, int length) {
  if (length < 1 || (length > 10 && !repeat)) 
    return NULL;
  srand(analogRead(A1));
  char* code = malloc(sizeof(char) * length + 1);
  if (repeat) {
    for (int i = 0; i < length; i++) 
      code[i] = rand() % 10 + '0';
    code[length] = '\0';
  }
  if (!repeat) {
    int rand_p, i = 0, k;
    int tmp[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    while (i < length) {
      rand_p = rand() % 10;
      for (k = 0; k < i; k++)
        if (tmp[k] == rand_p)
          break;
      if (k == i)
        tmp[i++] = rand_p;
    }
    for (i = 0; i < length; i++)
      code[i] = '0' + tmp[i];
    code[length] = '\0';
  }
  return code;
}





void play_game(char* secret) {
  bool state_enter_btn = 0, tmp_enter_btn = 0, enter_holding = 0, pressed_enter_btn = 0;
  bool state_1_btn = 0, state_2_btn = 0, state_3_btn = 0, state_4_btn = 0;
  bool tmp_1_btn = 0, tmp_2_btn = 0, tmp_3_btn = 0, tmp_4_btn = 0;
  bool pressed_1_btn = 0, pressed_2_btn = 0, pressed_3_btn = 0, pressed_4_btn = 0;
  int guess_n[] = {0, 0, 0, 0};
  int veiw_hist;
  unsigned long timer_hold = 0;
  int try_n = 0, a, b;
  char guess[4];
  char tmp_string[2];
  char** history =  malloc(sizeof(char*) * 10);
  for (int i = 0; i < 10; i++) {
    history[i] = malloc(4 * sizeof(char));
  }
  lcd_clear();
  lcd_print_at(0, 0, "Mastermind      ");
  lcd_print_at(0, 1, "GuessCombination");
  delay(2000);
  lcd_clear();
  lcd_print_at(0, 0, "Your try:");
  lcd_print_at(0, 1, "Your guess: 0000");
  while (1) {
    state_enter_btn = digitalRead(BTN_ENTER_PIN);
    if (state_enter_btn && !tmp_enter_btn) {
      tmp_enter_btn = true;
      timer_hold = millis();
    }
    if (!state_enter_btn && tmp_enter_btn  && millis() - timer_hold < 500) {
      tmp_enter_btn = false;
      pressed_enter_btn = true;
    }
    if (tmp_enter_btn && !enter_holding && millis() - timer_hold > 500 && try_n > 1) {
      enter_holding = true;
      veiw_hist = try_n - 1;
    }
    if (!state_enter_btn && tmp_enter_btn && millis() - timer_hold > 500) {
      pressed_1_btn = false;
      pressed_2_btn = false;
      pressed_3_btn = false;
      pressed_4_btn = false;
      tmp_1_btn = false;
      tmp_2_btn = false;
      tmp_3_btn = false;
      tmp_4_btn = false;
      
      render_history(secret, history, try_n - 1);
      tmp_enter_btn = false;
      enter_holding = false;
      timer_hold = millis();
    }

    if (pressed_enter_btn) {
      pressed_enter_btn = 0;
      for (int i = 0; i < 4; i++) {
        guess[i] = guess_n[i] + '0';
      }
      guess[5] = '\0';
      a = 0;
      b = 0;
      strcpy(history[try_n], guess);
      render_history(secret, history, try_n);
      get_score(secret, guess, &a, &b);
      if (a == 4) {
        turn_off_leds();
        lcd_print_at(0, 1, "Victory!!!      ");
        turn_off_leds();
        delay(3000);
        break;
      }
      if (try_n == 9 && a != 4) {
        lcd_print_at(0, 1, "Defeat:(        ");
        lcd_print_at(10, 1, secret);
        delay(3000);
        turn_off_leds();
        break;
      }
      try_n++;
    }

    if (enter_holding) {
      if (pressed_1_btn) {
        if (veiw_hist > 0) {
          veiw_hist--;
          render_history(secret, history, veiw_hist);
        }
        pressed_1_btn = 0;
      }
      if (pressed_2_btn) {
        if (veiw_hist < try_n - 1) {
          veiw_hist++;
          render_history(secret, history, veiw_hist);
        }
        pressed_2_btn = 0;
      }
    }

    state_1_btn = digitalRead(BTN_1_PIN);
    state_2_btn = digitalRead(BTN_2_PIN);
    state_3_btn = digitalRead(BTN_3_PIN);
    state_4_btn = digitalRead(BTN_4_PIN);

    if (state_1_btn && !tmp_1_btn) 
      tmp_1_btn = true;
    if (state_2_btn && !tmp_2_btn) 
      tmp_2_btn = true;
    if (state_3_btn && !tmp_3_btn) 
      tmp_3_btn = true;
    if (state_4_btn && !tmp_4_btn) 
      tmp_4_btn = true;
    
    if (!state_1_btn && tmp_1_btn) {
      tmp_1_btn = false;
      pressed_1_btn = true;
    }
    if (!state_2_btn && tmp_2_btn) {
      tmp_2_btn = false;
      pressed_2_btn = true;
    }
    if (!state_3_btn && tmp_3_btn) {
      tmp_3_btn = false;
      pressed_3_btn = true;
    }
    if (!state_4_btn && tmp_4_btn) {
      tmp_4_btn = false;
      pressed_4_btn = true;
    }


    if (pressed_1_btn && !enter_holding) {
      if (guess_n[0] == 9) guess_n[0] = -1;
      guess_n[0] = guess_n[0] + 1;
      sprintf(tmp_string, "%d", guess_n[0]);
      lcd_print_at(12, 1, tmp_string);
      pressed_1_btn = false;
    }
    if (pressed_2_btn && !enter_holding) {
      if (guess_n[1] == 9) guess_n[1] = -1;
      guess_n[1] = guess_n[1] + 1;
      sprintf(tmp_string, "%d", guess_n[1]);
      lcd_print_at(13, 1, tmp_string);
      pressed_2_btn = false;
    }    
    if (pressed_3_btn && !enter_holding) {
      if (guess_n[2] == 9) guess_n[2] = -1;
      guess_n[2] = guess_n[2] + 1;
      sprintf(tmp_string, "%d", guess_n[2]);
      lcd_print_at(14, 1, tmp_string);
      pressed_3_btn = false;
    }
    if (pressed_4_btn && !enter_holding) {
      if (guess_n[3] == 9) guess_n[3] = -1;
      guess_n[3] = guess_n[3] + 1;
      sprintf(tmp_string, "%d", guess_n[3]);
      lcd_print_at(15, 1, tmp_string);
      pressed_4_btn = false;
    }

  }
  free(history);
}





void render_leds(const int peg_a, const int peg_b) {
  int i = 0;
  int n = 0;
  turn_off_leds();
  if (i < peg_a) {
    digitalWrite(LED_RED_1, HIGH);
    i++;
  }
  if (i < peg_a) {
    digitalWrite(LED_RED_2, HIGH);
    i++;
  }
  if (i < peg_a) {
    digitalWrite(LED_RED_3, HIGH);
    i++;
  }
  if (i < peg_a) 
    digitalWrite(LED_RED_4, HIGH);
  

  if (n < peg_b) {
    digitalWrite(LED_BLUE_1 + peg_a * 2, HIGH);
    n++;
  }
  if (n < peg_b) {
    digitalWrite(LED_BLUE_2 + peg_a * 2, HIGH);
    n++;
  }
  if (n < peg_b) {
    digitalWrite(LED_BLUE_3 + peg_a * 2, HIGH);
    n++;
  }
  if (n < peg_b) 
    digitalWrite(LED_BLUE_4 + peg_a * 2, HIGH);
}



void render_history(char* secret, char** history, const int entry_nr) {
  int peg_a, peg_b;
  char tmp_buf[16];
  get_score(secret, history[entry_nr], &peg_a, &peg_b);
  render_leds(peg_a, peg_b);
  sprintf(tmp_buf, "%d: %s A%dB%d      ", entry_nr + 1, history[entry_nr], peg_a, peg_b);
  lcd_print_at(0, 0, tmp_buf);
}




void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b) {
  int temp1 = temp2 = 0, num;
  for (int i = 0; i < strlen(secret); i++) {
    if (secret[i] == guess[i])
      temp1++;
    else {
      for (int n = 0; n < strlen(secret); n++) {
        if (secret[i] == guess[n] && num != secret[i]) {
          temp2++;
          num = secret[i];
        }
      }
    }
  }
  *peg_a = temp1;
  *peg_b = temp2;
}
