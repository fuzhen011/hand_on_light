#ifndef LAB_H
#define LAB_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "native_gecko.h"
#include "logging/log.h"
#include "models/sensor_server.h"

void self_config(const struct gecko_msg_mesh_node_initialized_evt_t *evt);
void on_appkey_added(const struct gecko_msg_mesh_node_key_added_evt_t *evt);
#ifdef __cplusplus
}
#endif
#endif //LAB_H
