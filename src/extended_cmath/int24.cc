class int24 {
public:
    int24(unsigned long val) {
        data[0] = ( val        & 0xff);
        data[1] = ((val >> 8)  & 0xff);
        data[2] = ((val >> 16) & 0xff);
    }

    void operator=(unsigned long val) {
        data[0] = ( val        & 0xff);
        data[1] = ((val >> 8)  & 0xff);
        data[2] = ((val >> 16) & 0xff);
    }

    void operator=(int24 val) {
        this->data[0] = val.data[0];
        this->data[1] = val.data[1];
        this->data[2] = val.data[2];
    }

    unsigned long decode() const {
        unsigned long val;
        val = this->data[2];
        val <<= 8;
        val |= this->data[1];
        val <<= 8;
        val |= this->data[0];

        return val;
    }

private:
    unsigned char data[3];
};