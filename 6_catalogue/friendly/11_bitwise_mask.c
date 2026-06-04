/* manipulations de bits avec masques constants */

int main(void) {
    unsigned int x = 0xFFFFFFFFu;
    unsigned int low  = x & 0xFFu;
    unsigned int high = (x >> 24) & 0xFFu;

    /*@ assert low == 0xFF; */
    /*@ assert high == 0xFF; */

    unsigned int packed = (high << 24) | low;
    /*@ assert (packed & 0xFF) == 0xFF; */
    return (int)(low + high);
}
