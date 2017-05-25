#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shared.h"
#include "my_tasks.h"
#include "main.h"
#include "helpers.h"
#include "animations.h"

void animation_init(digit_animation* anime_struct)
{
  anime_struct->start_digit = DIGIT_NONE;
  anime_struct->end_digit = DIGIT_NONE;
  anime_struct->animation_start = 0;
  anime_struct->animation_type = ANIMATION_NO_ANIMATION;
  anime_struct->left_dot_status = 0;
  anime_struct->right_dot_status = 0;
  memset(anime_struct->pwm_status, 0, PWM_STATUS_SIZE);
}

void start_animation(digit_animation* anime_struct, uint8_t dest_digit, uint8_t anime_type)
{
  dest_digit %= 10;
  dest_digit == 0 ? dest_digit = DIGIT_0 : dest_digit;
  anime_struct->start_digit = anime_struct->end_digit;
  anime_struct->end_digit = dest_digit;
  anime_struct->animation_start = frame_counter;
  anime_struct->animation_type = anime_type;
}

void tube_print2(int8_t value, digit_animation* msa, digit_animation* lsa)
{
  msa->pwm_status[DIGIT_LEFT_DOT] = 0;
  if(value < 0)
  {
    msa->pwm_status[DIGIT_LEFT_DOT] = 255;
    value *= -1;
  }
  start_animation(lsa, value % 10, ANIMATION_CROSS_FADE);
  start_animation(msa, (value / 10) % 10, ANIMATION_CROSS_FADE);
}

void animation_handler(digit_animation* anime_struct)
{
  uint32_t current_frame = frame_counter - anime_struct->animation_start;
  if(anime_struct->start_digit == anime_struct->end_digit)
    return;
  if(anime_struct->animation_type == ANIMATION_NO_ANIMATION)
    return;
  else if(anime_struct->animation_type == ANIMATION_CROSS_FADE)
  {
    if(current_frame <= 30)
    {
      anime_struct->pwm_status[anime_struct->start_digit] = 255 - 8.5 * current_frame;
      anime_struct->pwm_status[anime_struct->end_digit] = 255 + 8.5 * current_frame;
    }
  }
}

