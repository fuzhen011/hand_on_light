/*************************************************************************
    > File Name: self_config.c
    > Author: Kevin
    > Created Time: 2020-04-10
    > Description:
 ************************************************************************/

/* Includes *********************************************************** */
#undef SUB_MODULE_NAME
#define SUB_MODULE_NAME "self_config"
#include "lab.h"
#include "mesh_sensor_model_capi_types.h"
#include "mesh_lighting_model_capi_types.h"

/* Defines  *********************************************************** */
#define PRIMARY_SUBNET  0
#define SELF_CFG_ADDR 0x0005
/* Global Variables *************************************************** */

/* Static Variables *************************************************** */
/*
 * Network, application and device key all use below.
 */
static const aes_key_128 key = {
  .data = {
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
  }
};

typedef struct {
  uint16_t model;
  uint8_t elem_index;
}model_info_t;

static const model_info_t model_info[] = {
  { 0x130F, 1 },
  { 0x1310, 1 },
  { MESH_SENSOR_SERVER_MODEL_ID, 0 },
  { MESH_SENSOR_SETUP_SERVER_MODEL_ID, 0 }
};

static const int model_num = sizeof(model_info) / sizeof(model_info_t);

/* Static Functions Declaractions ************************************* */

void self_config(const struct gecko_msg_mesh_node_initialized_evt_t *evt)
{
  struct gecko_msg_mesh_test_get_key_count_rsp_t *mtgkc;
  if (!evt->provisioned) {
    /* Not provisioned yet, self-provisioning */
    BG_AST(gecko_cmd_mesh_node_set_provisioning_data(key,
                                                     key,
                                                     PRIMARY_SUBNET,
                                                     0,
                                                     SELF_CFG_ADDR,
                                                     0)->result);
    LOGI("Provisioned, reseting.\n");
    gecko_cmd_system_reset(0);
    return;
  }

  /*
   * Self Configuration
   *  - Add Appkey
   *  - Bind Appkey to Models
   *
   */
  mtgkc = gecko_cmd_mesh_test_get_key_count(1); /* 1 for application key */
  BG_AST(mtgkc->result);
  if (mtgkc->count) {
    /* Already configured */
    LOGI("Already configured.\n");
    return;
  }

  /* Add appkey */
  BG_AST(gecko_cmd_mesh_test_add_local_key(1,
                                           key,
                                           0,
                                           PRIMARY_SUBNET)->result);

  /* Bind appkey to models */
  for (int i = 0; i < model_num; i++) {
    BG_AST(gecko_cmd_mesh_test_bind_local_model_app(model_info[i].elem_index,
                                                    0,
                                                    0xFFFF,
                                                    model_info[i].model)->result);
  }
    LOGI("Configured.\n");
}
