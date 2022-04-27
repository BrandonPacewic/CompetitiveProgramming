#include <memory>

class int24 {
public:
    int24(unsigned long val) : data(std::make_unique<unsigned char[]>(3)) {
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
        data[0] = this->data[0];
        data[1] = this->data[1];
        data[2] = this->data[2];
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
    std::unique_ptr<unsigned char[]> data;
};