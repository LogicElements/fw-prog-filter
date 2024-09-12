/*
 * DevInit.c
 *
 *  Created on: 12. 9. 2024
 *      Author: evzen
 */


#include "configuration.h"
#include "DevInit.h"

void Dev_Init(void)
{
conf.fact.boot_revision = 1001;
conf.fact.device_id = 8753;
conf.fact.hw_revision = 1001;
conf.fact.serial_number = 24090000;

conf.firm.revision = 1;
conf.firm.assembly_info = 20240810;
}

