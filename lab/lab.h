#ifndef LAB_H
#define LAB_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "native_gecko.h"
#include "logging/log.h"
#include "models/sensor_server.h"

/*
 * TODO:
 *
 * Check how the difference in regulating the lightness between uncommenting and
 * commenting the below line.
 *
 *  - Comment the below line out - the sensor server won't send ambient light
 *    level data to the LC server. So, the LC server will only use the lightness
 *    settings to regulate the lightness of the lightbulbs.
 *  - Uncomment the below line - the sensor server will loopback the ambient
 *    light level data to the LC server, the PI regulator will output an
 *    expected lightness, the real lightness output is the higher value of the
 *    PI regulator output and the lightness setting.
 *
 * NOTE: the LC properties are stored in flash, when you change the below line,
 * you need to update the stored value as well. The easiest way for this lab
 * could be factory reset and re-provisioning.
 */
#define AMBIENT_LUX_CTL

#define SENSOR_SERVER_MODEL_ELEMENT_INDEX 0

void self_config(const struct gecko_msg_mesh_node_initialized_evt_t *evt);
void on_appkey_added(const struct gecko_msg_mesh_node_key_added_evt_t *evt);
void on_node_initialized(const struct gecko_msg_mesh_node_initialized_evt_t *evt);

#ifdef __cplusplus
}
#endif
#endif //LAB_H
