#include "obv.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

obv_t *obv_init()
{
  obv_t *obv = (obv_t *)malloc(sizeof(obv_t));
  obv->value = 0;
  obv->ready = 0;
  return obv;
}

uint8_t obv_push_val(obv_t *obv, double open, double close, double volume)
{
  if (open > close)
  {
    obv->value -= volume;
  }
  else
  {
    obv->value += volume;
  }
  obv->ready = 1;
  return 0;
}
