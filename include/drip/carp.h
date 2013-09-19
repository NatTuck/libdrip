#ifndef DRIP_CARP_H
#define DRIP_CARP_H

void drip_carp_real(const char* filename, const int line, const char* message);

#define carp(mm) drip_carp_real(__FILE__, __LINE__, (mm))

#endif
