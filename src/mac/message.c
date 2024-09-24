#include "message.h"

int msg_build_dci_format_1_0(dci_format_1_0_t dci_format,
                             uint16_t rnti,
                             pdu_t* pdu)
{
    pdu->header.dl_transport_channel = PDCCH;
    pdu->dci_data_format_1_0_RA_RNTI.rnti = rnti;

    switch (dci_format)
    {
    case C_RNTI:
        break;
    case RA_RNTI:
        pdu->dci_data_format_1_0_RA_RNTI.dci_id = 1;
        pdu->dci_data_format_1_0_RA_RNTI.freq_resource = 10;
        pdu->dci_data_format_1_0_RA_RNTI.time_resource = 1;
        pdu->dci_data_format_1_0_RA_RNTI.vrb_to_prb_mapping = 1;
        pdu->dci_data_format_1_0_RA_RNTI.mod_cod_scheme = 16;
        break;
    case TC_RNTI:
        /* fill dci_allocated_resources struct here */
        break;    
    default:
        break;
    }

    return OGS_OK;   
}

int msg_build_rar_pdu(pdu_t* pdu, uint16_t ra_rnti)
{
    pdu->header.dl_transport_channel = PDSCH;

    pdu->rar.subheader.l8bit.r = 1;
    pdu->rar.subheader.l8bit.f = 1;
    pdu->rar.subheader.l8bit.lcid = 12;
    pdu->rar.subheader.l8bit.l = 6;

    pdu->rar.bi = 2;
    pdu->rar.rapid = 24;
    pdu->rar.timing_adv = 1024;
    pdu->rar.ul_grant = 900;
    pdu->rar.c_rnti = ra_rnti;

    return OGS_OK; 
}
