#include "rebar.h"



/**
 * Maps an input value linearly to an output value within specified input and output ranges. If value is outside input min/max, teh value
 * will get clamped to the min/max.
 *
 * @param input The input value to map
 * @param output Pointer to output mapped value
 * @param inputMin Minimum input value
 * @param inputMax Maximum input value
 * @param outputMin Minimum output value
 * @param outputMax Maximum output value
 * @return Error code
 */
Error Mapping_LinearMapInt32(int32_t input, int32_t *output,int32_t inputMin, int32_t inputMax, int32_t outputMin, int32_t outputMax)
{
    if (ILLEGAL_POINTER(output)) {
        return Error_IllegalPointer;
    }

    if ((inputMax <= inputMin) || (outputMax <= outputMin)) {
        return Error_BadParameter;
    }

    if (input < inputMin) {
        input = inputMin;
    }
    if (input > inputMax) {
        input = inputMax;
    }

    *output =  outputMin + (input - inputMin) * (outputMax - outputMin) / (inputMax - inputMin);
    return Error_None;
}

/**
 * Maps an input value linearly to an output value within specified input and output ranges.If value is outside input min/max, teh value
 * will get clamped to the min/max.
 *
 * @param input The input value to map
 * @param output Pointer to output mapped value
 * @param inputMin Minimum input value
 * @param inputMax Maximum input value
 * @param outputMin Minimum output value
 * @param outputMax Maximum output value
 * @return Error code
 */
Error Mapping_LinearMapInt16(int16_t input, int16_t *output,int16_t inputMin, int16_t inputMax, int16_t outputMin, int16_t outputMax)
{
    if (ILLEGAL_POINTER(output)) {
        return Error_IllegalPointer;
    }

    if ((inputMax == inputMin) || (outputMin == outputMax)) {
        return Error_BadParameter;
    }

    if (input < inputMin) {
        input = inputMin;
    }
    if (input > inputMax) {
        input = inputMax;
    }

    *output =  outputMin + (input - inputMin) * (outputMax - outputMin) / (inputMax - inputMin);
    return Error_None;
}


/**
 * Maps an input value linearly to an output value within specified input and output ranges.If value is outside input min/max, teh value
 * will get clamped to the min/max.
 *
 * @param input The input value to map
 * @param output Pointer to output mapped value
 * @param inputMin Minimum input value
 * @param inputMax Maximum input value
 * @param outputMin Minimum output value
 * @param outputMax Maximum output value
 * @return Error code
 */
Error Mapping_LinearMapInt8(int8_t input, int8_t *output,int8_t inputMin, int8_t inputMax, int8_t outputMin, int8_t outputMax)
{
    if (ILLEGAL_POINTER(output)) {
        return Error_IllegalPointer;
    }

    if ((inputMax == inputMin) || (outputMin == outputMax)) {
        return Error_BadParameter;
    }

    if (input < inputMin) {
        input = inputMin;
    }
    if (input > inputMax) {
        input = inputMax;
    }

    *output =  outputMin + (input - inputMin) * (outputMax - outputMin) / (inputMax - inputMin);
    return Error_None;
}


