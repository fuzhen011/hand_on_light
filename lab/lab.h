#ifndef LAB_H
#define LAB_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "native_gecko.h"
#include "logging/log.h"
#include "models/sensor_server.h"

#define SENSOR_SERVER_MODEL_ELEMENT_INDEX 0

/**
 * @brief self_config - provision the device into a network and configure it
 * locally. Not used in the lab, for debug ease.
 *
 * @param evt - @ref{struct gecko_msg_mesh_node_initialized_evt_t}
 */
void self_config(const struct gecko_msg_mesh_node_initialized_evt_t *evt);

/**
 * @brief on_appkey_added - Bind the added appkey to the sensor server model.
 *
 * @param evt - @ref{struct gecko_msg_mesh_node_key_added_evt_t}
 */
void on_appkey_added(const struct gecko_msg_mesh_node_key_added_evt_t *evt);

/**
 * @brief on_node_initialized - configure the node after initialized, start
 * sensors if needed
 *
 * @param evt - @ref{struct gecko_msg_mesh_node_initialized_evt_t}
 */
void on_node_initialized(const struct gecko_msg_mesh_node_initialized_evt_t *evt);
#ifdef __cplusplus
}
#endif
#endif //LAB_H
