extern int (*gDBCommTable[10])();

int fn_800AAB08(void* buf, int len) {
    int result = gDBCommTable[5](buf, len);
    return (result != 0) ? -1 : 0;
}

int fn_800AAB44(void* dst, int maxlen) {
    int result = gDBCommTable[4](dst, maxlen);
    return (result != 0) ? -1 : 0;
}

int fn_800AAB80(void) {
    return gDBCommTable[3]();
}
