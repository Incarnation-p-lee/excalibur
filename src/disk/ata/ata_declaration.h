#ifndef SRC_DISK_ATA_DECLARATION_H
#define SRC_DISK_ATA_DECLARATION_H

static inline bool ata_device_status_busy_p(uint8 status);
static inline bool ata_device_status_device_ready_p(uint8 status);
static inline bool ata_device_status_error_p(uint8 status);
static inline bool ata_device_status_readable_p(uint8 status);
static inline s_ata_device_info_t * ata_device_information(void);
static inline uint16 ata_device_cylinder_read(uint16 status_port, uint16 port_low, uint16 port_high);
static inline void ata_device_drive_set(uint16 port, uint8 val);
static inline void ata_device_info_type_set(s_ata_device_info_t *dev_info, uint32 type);
static inline void ata_device_software_reset(uint16 port);
static inline void ata_device_type_detect(s_ata_device_info_t *dev_info);
void ata_device_detect(void);

#endif
