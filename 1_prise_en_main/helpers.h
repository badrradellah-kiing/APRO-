#ifndef HELPERS_H
#define HELPERS_H

/*@ requires min <= max;
    ensures \result >= min && \result <= max;
    assigns \nothing;
*/
extern int nondet_int(int min, int max);

/*@ assigns \nothing; */
extern int nondet_any(void);

#endif
