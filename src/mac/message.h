#ifndef MESSAGE_H
#define MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/ogs-core.h"

#define MAX_PDUS_QUANTITY 16
#define MAX_PDU_LEN 256
#define DCI_NO_OF_PDUS  1
#define DCI_DL          1

/* FORWARD DECLARATION */
typedef struct dci_allocated_resources_s dci_allocated_resources_t;
typedef struct rar_data_s rar_data_t;

typedef enum {
    PDCCH,
    PDSCH,
} dl_transport_channel_e;

typedef enum {
    PRACH,
    PUSCH,
    PUCCH,
} ul_transport_channel_e;

typedef enum dci_format_1_0_e {
    C_RNTI,
    RA_RNTI,
    TC_RNTI
} dci_format_1_0_t;

typedef struct pdu_subheader_l8bit_s {
    uint8_t r : 1;
    uint8_t f : 1;
    uint8_t lcid : 6;
    uint8_t l : 8;
} __attribute__ ((packed)) pdu_subheader_l8bit_t;

typedef struct pdu_subheader_l16bit_s {
    uint8_t r : 1;
    uint8_t f : 1;
    uint8_t lcid : 6;
    uint16_t l : 16;
} __attribute__ ((packed)) pdu_subheader_l16bit_t;

typedef struct pdu_subheader_s {
    union {
        pdu_subheader_l8bit_t l8bit;
        pdu_subheader_l16bit_t l16bit;
    };
} __attribute__ ((packed)) pdu_subheader_t;

typedef struct rar_pdu_s {
    //TODO
    pdu_subheader_t subheader;
    uint32_t reserv_1 : 4;
    uint32_t bi : 4;
    uint32_t reserv_2 : 2;
    uint32_t rapid : 6;
    uint32_t reserv_3 : 1;
    uint32_t timing_adv : 13;
    uint32_t ul_grant : 27;
    uint32_t c_rnti : 16;
} __attribute__ ((packed)) rar_pdu_t;

typedef struct dci_data_format_1_0_RA_RNTI_s {
    uint16_t rnti;
    uint8_t dci_id : 1;
    uint8_t freq_resource : 4;
    uint8_t time_resource : 1;
    uint8_t vrb_to_prb_mapping : 1;
    uint8_t mod_cod_scheme : 5;
} dci_data_format_1_0_RA_RNTI_t;

typedef struct prach_pdu_s {
    pdu_subheader_t subheader;
    uint8_t first_OFDM_symbol_idx;
    uint8_t first_slot_symbol_idx;
    uint8_t PRACH_occasion_in_freq_domain_idx;
    uint8_t UL_carrier_type;
} __attribute__ ((packed)) prach_pdu_t;

typedef struct pusch_pdu_s {
    pdu_subheader_t subheader;
    uint8_t data[MAX_PDU_LEN];
} pusch_pdu_t;

typedef struct pdu_header_s {
    union {
        uint8_t dl_transport_channel : 3;
        uint8_t ul_transport_channel : 3;
    };
} __attribute__ ((packed)) pdu_header_t;

typedef struct pdu_s {
    pdu_header_t header;
    union {
        //uplink
        prach_pdu_t prach;
        pusch_pdu_t pusch;

        //downlink
        dci_data_format_1_0_RA_RNTI_t dci_data_format_1_0_RA_RNTI;
        rar_pdu_t rar;
    };
} __attribute__ ((packed)) pdu_t;

typedef struct msg_header_s {
    uint16_t size;
    uint16_t no_of_pdus;
} __attribute__ ((packed)) msg_header_t;

typedef struct message_s {
    msg_header_t header;
    pdu_t pdu[MAX_PDUS_QUANTITY];
} __attribute__ ((packed)) message_t;


int msg_build_dci_format_1_0(dci_format_1_0_t dci_format,
                             uint16_t rnti,
                             pdu_t* pdu);

int msg_build_rar_pdu(pdu_t* pdu, uint16_t ra_rnti);

#ifdef __cplusplus
}
#endif

#endif /* MESSAGE_H */