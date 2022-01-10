
//Nguyen Cao Minh
//This function is taken directly from Arduino code and adding comments. 
//To use on Raspberry, modification is needed.

//FUNCTION[1]
//This function will call FUNCTION[2] as and API to read from registers RXB0 and RXB1
MCP2515::ERROR MCP2515::readMessage(struct can_frame *frame)
{
    ERROR rc;
    uint8_t stat = getStatus();

    if ( stat & STAT_RX0IF ) {
        rc = readMessage(RXB0, frame);
    } else if ( stat & STAT_RX1IF ) {
        rc = readMessage(RXB1, frame);
    } else {
        rc = ERROR_NOMSG;
    }

    return rc;
}

//FUNCTION[2]
//This function will read data directly from hardware buffer
MCP2515::ERROR MCP2515::readMessage(const RXBn rxbn, struct can_frame *frame)
{
    const struct RXBn_REGS *rxb = &RXB[rxbn];


    // Five bytes are used to store Standard and Extend Identifiers
    // Reading 5 bytes of Identifier to tbufdata
    uint8_t tbufdata[5];
    readRegisters(rxb->SIDH, tbufdata, 5); // <- This function is platform dependent
    //

    //Bit manipulation to obtain ID field in the message
    //Inside tbufdata[5] array there are registers:
    //      + [0] SIDH 
    //      + [1] SIDL
    //      + [2] EIDH
    //      + [3] EIDL
    //      + [4] DLC
    //ID has 11 bits in length
    uint32_t id = (tbufdata[MCP_SIDH]<<3) + (tbufdata[MCP_SIDL]>>5);

    //If extended standard id is used then modify id
    //In final project, we dont use extended id so this code can be removed with no effect. 
    if ( (tbufdata[MCP_SIDL] & TXB_EXIDE_MASK) ==  TXB_EXIDE_MASK ) {
        id = (id<<2) + (tbufdata[MCP_SIDL] & 0x03);
        id = (id<<8) + tbufdata[MCP_EID8];
        id = (id<<8) + tbufdata[MCP_EID0];
        id |= CAN_EFF_FLAG;
    }
    //

    //Data length (DLC) is obtained by masking DLC_MASK with tbufdata[4]
    //If data length is more then 8 then return error.
    //CAN_MAX_DLEN(maximum data length) is 8
    //DLC has 4 bit in length
    uint8_t dlc = (tbufdata[MCP_DLC] & DLC_MASK);
    if (dlc > CAN_MAX_DLEN) {
        return ERROR_FAIL;
    }

    //Read value of CTRL register
    //CTRL register has 8 bits, including RTR bit, IDE bit, Reserved bit, Data filtering bits. 
    uint8_t ctrl = readRegister(rxb->CTRL); // <- This function is platform dependent.
    if (ctrl & RXBnCTRL_RTR) // <- If RTR bit of CTRL register is 1 then 
    {
        id |= CAN_RTR_FLAG; // <- Switch the corresponding RTR bit in the id to 1
    }

    //Assigning value to frame struct
    frame->can_id = id;
    frame->can_dlc = dlc;

    //Reading data and assigning to frame data
    readRegisters(rxb->DATA, frame->data, dlc); // <- This function is platform dependent

    //????? Dont understand this function
    modifyRegister(MCP_CANINTF, rxb->CANINTF_RXnIF, 0); // <- This function is platform dependent

    return ERROR_OK;
}

