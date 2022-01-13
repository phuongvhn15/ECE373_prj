    int raw = (angel+180)/0.01;printf("%08x\n",raw);
    uint8_t raw4 = raw & 0x000000FF;
    printf("%x\n",raw4);
    printf("\n");