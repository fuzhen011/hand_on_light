#ifndef LAB_H
#define LAB_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "native_gecko.h"
#include "logging/log.h"
#include "models/sensor_server.h"

/* #define AMBIENT_LUX_CTL */

#define SENSOR_SERVER_MODEL_ELEMENT_INDEX 0

void self_config(const struct gecko_msg_mesh_node_initialized_evt_t *evt);
void on_appkey_added(const struct gecko_msg_mesh_node_key_added_evt_t *evt);
void on_node_initialized(const struct gecko_msg_mesh_node_initialized_evt_t *evt);
#ifdef __cplusplus
}
#endif
#endif //LAB_H
