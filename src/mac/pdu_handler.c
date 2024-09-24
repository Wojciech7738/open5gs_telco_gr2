#include "mac_buffer.h"
#include "pdu_handler.h"
#include "encoder.h"

static uint16_t get_ra_rnti(uint8_t s_id, uint8_t t_id, uint8_t f_id, uint8_t ul_carrier_id);
static int handle_prach_msg(prach_pdu_t* prach_pdu);
static int handle_pusch_msg(pusch_pdu_t* pusch_pdu);

static uint16_t get_ra_rnti(uint8_t s_id, uint8_t t_id, uint8_t f_id, uint8_t ul_carrier_id)
{
    //RA-RNTI = 1 + s_id + 14 × t_id + 14 × 80 × f_id + 14 × 80 × 8 × ul_carrier_id
    //s_id = the index of the first OFDM symbol of the specified PRACH (0 <= s_id < 14)
    //t_id : the index of the first slot symbol of the specified PRACH  in a system frame (0 <= t_id < 80)
    //f_id : the index of the the specified PRACH in the frequency domain(0 <= s_id < 8)
    //ul_carrier_id : UL carrier used for Msg1 transmission (0 = normal carrier, 1 = SUL carrier)
    uint16_t ra_rnti = 1U + s_id + 14U * t_id + 14U * 80U * f_id + (14U * 80U * 8U * ul_carrier_id);

    return ra_rnti;
}

static int handle_prach_msg(prach_pdu_t* prach_pdu)
{
    pdu_t pdu = {0};

    uint16_t ra_rnti = get_ra_rnti(prach_pdu->first_OFDM_symbol_idx,
                                   prach_pdu->first_slot_symbol_idx,
                                   prach_pdu->PRACH_occasion_in_freq_domain_idx,
                                   prach_pdu->UL_carrier_type);
    
    msg_build_dci_format_1_0(RA_RNTI, ra_rnti, &pdu);
    encode_msg(mac_buffer_tx_get_ptr(), &pdu, sizeof(pdu_t));

    memset(&pdu, 0, sizeof(pdu));

    msg_build_rar_pdu(&pdu, ra_rnti);
    encode_msg(mac_buffer_tx_get_ptr(), &pdu, sizeof(pdu_t));

    return OGS_OK;
}

static int handle_pusch_msg(pusch_pdu_t* pusch_pdu)
{
    //metody pozwalajace na wkladanie do buffora?
    //tak
    //pusch_pdu->data
    //send_to_rlc();
    return 1;
}

int handle_uplink_pdu(pdu_t* pdu)
{
    switch (pdu->header.ul_transport_channel)
    {
    case PRACH:
        handle_prach_msg(&pdu->prach);
        break;
    case PUSCH:
        handle_pusch_msg(&pdu->pusch);
        break;
    case PUCCH:
        break;
    default:
        break;
    }

    return OGS_OK;
}