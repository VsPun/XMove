
void WirelessInit();
void W_PutString() ;  //���߷�������
__interrupt void Port_1(void);


void RxWayConfig();
void SetStandbyMode();
void SetRFChannel(u8 ID);  //id  0-7;

extern u8 isSendMode;