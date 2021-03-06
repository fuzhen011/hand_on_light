/* Includes *********************************************************** */
#include "native_gecko.h"

#undef SUB_MODULE_NAME
#define SUB_MODULE_NAME "self_config"
#include "lab.h"
#include "mesh_sensor_model_capi_types.h"
#include "mesh_lighting_model_capi_types.h"

/* Defines  *********************************************************** */
#define PRIMARY_SUBNET  0
#define SELF_CFG_ADDR 0x0005

#define TYPE_NETKEY 0
#define TYPE_APPKEY 1

#define AKI_BOUND_KEY 0x403a
/* Global Variables *************************************************** */
uint16_t appkey_index = 0xffff;

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
static void lc_sensors_start(void);

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
  mtgkc = gecko_cmd_mesh_test_get_key_count(TYPE_APPKEY); /* 1 for application key */
  BG_AST(mtgkc->result);
  if (mtgkc->count) {
    /* Already configured */
    LOGI("Already configured.\n");
    return;
  }

  /* Add appkey */
  BG_AST(gecko_cmd_mesh_test_add_local_key(TYPE_APPKEY,
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

void on_appkey_added(const struct gecko_msg_mesh_node_key_added_evt_t *evt)
{
  if (evt->type == TYPE_NETKEY) {
    return;
  }

  if (appkey_index == 0xFFFF) {
    struct gecko_msg_flash_ps_load_rsp_t *r = gecko_cmd_flash_ps_load(AKI_BOUND_KEY);
    if (r->result == bg_err_success) {
      memcpy(&appkey_index, r->value.data, 2);
      lc_sensors_start();
      return;
    }
  }

  BG_AST(gecko_cmd_mesh_test_bind_local_model_app(SENSOR_SERVER_MODEL_ELEMENT_INDEX,
                                                  evt->index,
                                                  0xFFFF,
                                                  MESH_SENSOR_SERVER_MODEL_ID)->result);
  LOGI("Appkey %u has been bound to sensor server model\n",
       evt->index);
  appkey_index = evt->index;
  BG_AST(gecko_cmd_flash_ps_save(AKI_BOUND_KEY, 2, (uint8_t *)&appkey_index)->result);
  lc_sensors_start();
}

void on_node_initialized(const struct gecko_msg_mesh_node_initialized_evt_t *evt)
{
  if (!evt->provisioned) {
    return;
  }

  if (appkey_index == 0xFFFF) {
    struct gecko_msg_flash_ps_load_rsp_t *r = gecko_cmd_flash_ps_load(AKI_BOUND_KEY);
    if (r->result == bg_err_success) {
      memcpy(&appkey_index, r->value.data, 2);
      lc_sensors_start();
    }
  }
}

static void lc_sensors_start(void)
{
  if (appkey_index == 0xFFFF) {
    return;
  }

  LOGI("LC Sensors Started\n");
  send_people_count();
  ambient_light_send(1);
}
