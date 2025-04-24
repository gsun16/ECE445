import struct
import os

input_file = 'BT.raw'
output_file = 'BT_10s.c'

# Configuration
duration_seconds = 10        # seconds
sample_rate = 44100          # Hz
channels = 2                 # stereo
bytes_per_sample = 2         # 16-bit PCM

# Calculate byte limit
max_bytes = duration_seconds * sample_rate * channels * bytes_per_sample

# Read raw data
with open(input_file, 'rb') as f:
    data = f.read(max_bytes)

# Determine number of 16-bit samples
num_samples = len(data) // bytes_per_sample

# Unpack samples
samples = [samp for (samp,) in struct.iter_unpack('<h', data)]

# Write C file
with open(output_file, 'w') as f:
    f.write('#include <stdint.h>\n\n')
    f.write(f'const int16_t BT_10s_pcm[{num_samples}] = {{\n')
    for i, samp in enumerate(samples):
        if i % 8 == 0:
            f.write('    ')
        comma = ',' if i < num_samples - 1 else ''
        f.write(f'{samp}{comma} ')
        if (i + 1) % 8 == 0:
            f.write('\n')
    f.write('\n};\n\n')
    f.write(f'const unsigned int BT_10s_pcm_len = {num_samples};\n')

print(f"Saved C source to {output_file}")
