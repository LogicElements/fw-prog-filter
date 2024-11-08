/**
 * @file       config_app.c
 * @brief      Application-specific configuration callback implementation
 * @addtogroup grConfig
 * @{
 */

/* Includes ------------------------------------------------------------------*/

#include "common.h"
#include "configuration.h"

/* Private defines -----------------------------------------------------------*/
/* Private macros  -----------------------------------------------------------*/

/* Private typedefs ----------------------------------------------------------*/

typedef struct
{
  uint32_t sn;
  uint32_t temp;
}ConfigApp_Private_t;

/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static ConfigApp_Private_t ca;

/* Public variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

Status_t Config_AppInit(void)
{
  Status_t ret = STATUS_OK;

  UNUSED(ca);

  return ret;
}


Status_t Config_Callback(uint32_t id)
{
  Status_t ret = STATUS_OK;

  /* Check if some value need further action to propagate */
  switch (CONF_BLOCK_ID(id))
  {
    case CONF_BLOCK_ID(CONF_COM_MB_BAUD_RATE):
      /* Upper saturation of modbus parameters */
#ifndef DEBUG
      SAT_UP(conf.com.mb_baud_rate, MB_BAUD_115200);
      SAT_UP(conf.com.mb_parity, MB_PARITY_ODD);
      SAT_UP(conf.com.mb_stop_bits, MB_STOP_2);
      SAT_UP(conf.com.mb_timeout, 7200);
#endif
      break;

    case CONF_BLOCK_ID(CONF_PF_CUTOFF_HP):
      SAT_UP_DN(conf.pf.cutoff_lp, 320, 20);
      SAT_UP_DN(conf.pf.cutoff_hp, 10000, 300);
      SAT_UP_DN(conf.pf.mode, PF_NP, 0);

      SAT_UP_DN(conf.pf.def_cutoff_lp, 320, 20);
      SAT_UP_DN(conf.pf.def_cutoff_hp, 10000, 300);
      SAT_UP_DN(conf.pf.def_mode, DEF_NP, 0);
      break;


    default:
      break;
  }
  return ret;
}


/* Private Functions ---------------------------------------------------------*/


/** @} */
