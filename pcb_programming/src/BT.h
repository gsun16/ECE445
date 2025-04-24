// BT.h
#ifndef BT_H
#define BT_H

#include <stdint.h>

// the sample buffer (interleaved stereo), defined in BT.c
extern const int16_t BT_10s_pcm[];
// its length in *samples* (so 2×frames), defined in BT.c
extern const unsigned int BT_10s_pcm_len;

#endif  // BT_H
