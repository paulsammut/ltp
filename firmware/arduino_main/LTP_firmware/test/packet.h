#pragma once

// Here we decode packets. We also encode packets. 
// We also check for data on the serial bus. 
// We use COBS as defined in this paper
// http://www.stuartcheshire.org/papers/cobsforton.pdf


void StuffData(const unsigned char *ptr, unsigned long length, unsigned char *dst);

void UnStuffData(const unsigned char *ptr, unsigned long length, unsigned char *dst);
