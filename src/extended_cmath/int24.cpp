/* MIT License
 *
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

class int24 {
   public:
    int24(unsigned long val) {
        data[0] = (val & 0xff);
        data[1] = ((val >> 8) & 0xff);
        data[2] = ((val >> 16) & 0xff);
    }

    void operator=(unsigned long val) {
        data[0] = (val & 0xff);
        data[1] = ((val >> 8) & 0xff);
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