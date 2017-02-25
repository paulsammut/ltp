/* Copyright 2011, Jacques Fortier. All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted, with or without modification.
 */
#ifndef COBS_H
#define COBS_H

#include <stdint.h>
#include <stddef.h>



/**
 * Stuffs "length" bytes of data at the location pointed to by "input", writing the output to the 
 * location pointed to by "output". Returns the number of bytes written to "output". Does not add 0 
 * at the end. 
 * @param input byte array of data to encode
 * @param length length of byte array to encode
 * @param output output data that is encoded. 
 * @return length of encoded output data 
 */
size_t cobs_encode(const uint8_t * input, size_t length, uint8_t * output);

/**
 *  Unstuffs "length" bytes of data at the location pointed to by "input", writing the 
 *  output * to the location pointed to by "output". Returns the number of bytes written to "output" if
 *  "input" was successfully unstuffed, and 0 if there was an error unstuffing "input". Trim the end zero
 *  of the cobs string before sending it.
 * @param input uint8_t array contain the input byte array to be unstuffed
 * @param length of input array to be unstuffed
 * @param output location of unstuffed data
 * @return number of bytes if "input" was successfully unstuffed, 0 if there was an error unstuffing input
 */
size_t cobs_decode(const uint8_t * input, size_t length, uint8_t * output);

#endif
