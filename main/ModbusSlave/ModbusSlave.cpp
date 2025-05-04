/**
 * Copyright (c) 2015, Yaacov Zamir <kobi.zamir@gmail.com>
 * Copyright (c) 2017, Andrew Voznytsa <andrew.voznytsa@gmail.com>, FC_WRITE_REGISTER and FC_WRITE_MULTIPLE_COILS support
 * Copyright (c) 2019, Soroush Falahati <soroush@falahai.net>, total communication rewrite, setUnitAddress(), FC_READ_EXCEPTION_STATUS support, general refactoring
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF  THIS SOFTWARE.
 */

#include <string.h>
#include "ModbusSlave.h"

/**
 * ---------------------------------------------------
 *                CONSTANTS AND MACROS
 * ---------------------------------------------------
 */

#define MODBUS_FRAME_SIZE 4
#define MODBUS_CRC_LENGTH 2

#define MODBUS_ADDRESS_INDEX 0
#define MODBUS_FUNCTION_CODE_INDEX 1
#define MODBUS_DATA_INDEX 2

#define MODBUS_BROADCAST_ADDRESS 0
#define MODBUS_ADDRESS_MIN 1
#define MODBUS_ADDRESS_MAX 247

#define MODBUS_HALF_SILENCE_MULTIPLIER 3
#define MODBUS_FULL_SILENCE_MULTIPLIER 7

#define readUInt16(arr, index) word(arr[index], arr[index + 1])
#define readCRC(arr, length) word(arr[(length - MODBUS_CRC_LENGTH) + 1], arr[length - MODBUS_CRC_LENGTH])

/**
 * ---------------------------------------------------
 *                  PUBLIC METHODS
 * ---------------------------------------------------
 */

/**
 * Initialize a modbus slave object.
 *
 * @param unitAddress The modbus slave unit address.
 */
ModbusSlave::ModbusSlave(uint8_t unitAddress)
{
    ModbusSlave::setUnitAddress(unitAddress);
}

/**
 * Get the modbus slaves unit address.
 */
uint8_t ModbusSlave::getUnitAddress()
{
    return _unitAddress;
}

/**
 * Sets the modbus slaves unit address.
 *
 * @param unitAddress The modbus slaves unit address.
 */
void ModbusSlave::setUnitAddress(uint8_t unitAddress)
{
    if (unitAddress < MODBUS_ADDRESS_MIN || unitAddress > MODBUS_ADDRESS_MAX)
    {
        return;
    }
    _unitAddress = unitAddress;
}

/**
 * Initialize the modbus object.
 *
 * @param unitAddress The modbus slave unit address.
 * @param transmissionControlPin The digital out pin to be used for RS485 transmission control.
 */
ModbusLib::ModbusLib(uint8_t unitAddress, int transmissionControlPin)
    : ModbusLib(Serial, unitAddress, transmissionControlPin)
{
}

/**
 * Initialize the modbus object.
 *
 * @param serialStream The serial stream used for the modbus communication.
 * @param unitAddress The modbus slave unit address.
 * @param transmissionControlPin The digital out pin to be used for RS485 transmission control.
 */
ModbusLib::ModbusLib(Stream &serialStream, uint8_t unitAddress, int transmissionControlPin)
    : _serialStream(serialStream)
{
    // Set modbus slave unit id.
    _slaves[0].setUnitAddress(unitAddress);
    cbVector = _slaves[0].cbVector;

    // Set transmission control pin for RS485 communication.
    _transmissionControlPin = transmissionControlPin;
}

/**
 * Initialize the modbus object.
 *
 * @param slaves Pointer to an array of ModbusSlaves.
 * @param numberOfSlaves The number of ModbusSlaves in the array.
 * @param transmissionControlPin The digital out pin to be used for RS485 transmission control.
 */
ModbusLib::ModbusLib(ModbusSlave *slaves, uint8_t numberOfSlaves, int transmissionControlPin)
    : ModbusLib(Serial, slaves, numberOfSlaves, transmissionControlPin)
{
}

/**
 * Initialize the modbus object.
 *
 * @param serialStream the serial stream used for the modbus communication.
 * @param slaves Pointer to an array of ModbusSlaves.
 * @param numberOfSlaves The number of ModbusSlaves in the array.
 * @param transmissionControlPin The digital out pin to be used for RS485 transmission control.
 */
ModbusLib::ModbusLib(Stream &serialStream, ModbusSlave *slaves, uint8_t numberOfSlaves, int transmissionControlPin)
    : _serialStream(serialStream)
{
    // Set the modbus slaves.
    _slaves = slaves;
    _numberOfSlaves = numberOfSlaves;
    cbVector = _slaves[0].cbVector;

    // Set transmission control pin for RS485 communication.
    _transmissionControlPin = transmissionControlPin;
}

/**
 * Sets the modbus slaves unit address.
 *
 * @param unitAddress The modbus slaves unit address.
 */
void ModbusLib::setUnitAddress(uint8_t unitAddress)
{
    _slaves[0].setUnitAddress(unitAddress);
}

/**
 * Enables communication.
 */
void ModbusLib::enable()
{
    _enabled = true;
}

/**
 * Disable communication.
 */
void ModbusLib::disable()
{
    _enabled = false;
}

/**
 * Gets the enable status.
 *
 * @return The enable state.
 */
bool ModbusLib::readEnabled()
{
    return _enabled;
}

/**
 * Gets the total number of bytes sent.
 *
 * @return The number of bytes.
 */
uint64_t ModbusLib::getTotalBytesSent()
{
    return _totalBytesSent;
}

/**
 * Gets the total number of bytes received.
 *
 * @return The number of bytes.
 */
uint64_t ModbusLib::getTotalBytesReceived()
{
    return _totalBytesReceived;
}

uint8_t ModbusLib::getRequestedAddress10()
{
    return requestAddress % 10;
}

/**
 * Begins initializing the serial stream and preparing to read request messages.
 *
 * @param baudrate The serial port baudrate.
 */
void ModbusLib::begin(uint64_t baudrate)
{
    // Initialize the transmission control pin and set it's state.
    if (_transmissionControlPin > MODBUS_CONTROL_PIN_NONE)
    {
        pinMode(_transmissionControlPin, OUTPUT);
        digitalWrite(_transmissionControlPin, LOW);
    }

    // Disable the serial stream timeout and clear the buffer.
    _serialStream.setTimeout(0);
    _serialStream.flush();
    _serialTransmissionBufferLength = _serialStream.availableForWrite();

    // Calculate the half char time based on the serial's baudrate.
    if (baudrate > 19200)
    {
        _halfCharTimeInMicroSecond = 250; // 0.5T.
    }
    else
    {
        _halfCharTimeInMicroSecond = 5000000 / baudrate; // 0.5T.
    }

    // Set the last received time to 3.5T in the future to ignore request currently in the middle of transmission.
    _lastCommunicationTime = micros() + (_halfCharTimeInMicroSecond * MODBUS_FULL_SILENCE_MULTIPLIER);

    // Sets the request buffer length to zero.
    _requestBufferLength = 0;
}

/**
 * Checks if we have a complete request, parses the request, executes the
 * corresponding registered callback and writes the response.
 *
 * @return The number of bytes written as response.
 */
uint8_t ModbusLib::poll()
{
     // Wait for one complete request packet.
    if (!ModbusLib::readRequest())
    {
        //Serial.println(__LINE__);
        return 0;
        
    }   

    
    // Validate the incoming request.
    if (!ModbusLib::validateRequest())
    {

        return 0;

    }

    // Execute the incoming request and create the response.
    uint8_t status = ModbusLib::createResponse();

    //Serial.printf("_responseBufferLength %d \n", _responseBufferLength );

    // Check if the callback execution succeeded.
    if (status != STATUS_OK)
    {

        return ModbusLib::reportException(status);

    }

    // Write the create response to the serial interface.

    return ModbusLib::writeResponse();
}

/**
 * Returns the current request message's function code.
 *
 * @return A byte containing the current request message function code.
 */
uint8_t ModbusLib::readFunctionCode()
{
    if (_requestBufferLength >= MODBUS_FRAME_SIZE && !_isRequestBufferReading)
    {
        return _requestBuffer[MODBUS_FUNCTION_CODE_INDEX];
    }
    return FC_INVALID;
}

/**
 * Returns the current request message's target unit address.
 *
 * @return A byte containing the current request message unit address.
 */
uint8_t ModbusLib::readUnitAddress()
{
    if ((_requestBufferLength >= MODBUS_FRAME_SIZE) && !_isRequestBufferReading)
    {
        return _requestBuffer[MODBUS_ADDRESS_INDEX];
    }
    return MODBUS_INVALID_UNIT_ADDRESS;
}

/**
 * Returns a boolean value indicating if the request currently being processed
 * is a broadcast message and therefore does not need a response.
 *
 * @return True if the current request message is a broadcase message; otherwise false.
 */
bool ModbusLib::isBroadcast()
{
    return ModbusLib::readUnitAddress() == MODBUS_BROADCAST_ADDRESS;
}

/**
 * Reads a coil state from input buffer.
 *
 * @param offset The offset from the first coil in the buffer.
 * @return The coil state from buffer (true / false).
 */
bool ModbusLib::readCoilFromBuffer(int offset)
{
    if (_requestBuffer[MODBUS_FUNCTION_CODE_INDEX] == FC_WRITE_COIL)
    {
        if (offset == 0)
        {
            // (2 x coilAddress, 1 x value).
            return readUInt16(_requestBuffer, MODBUS_DATA_INDEX + 2) == COIL_ON;
        }
        return false;
    }
    else if (_requestBuffer[MODBUS_FUNCTION_CODE_INDEX] == FC_WRITE_MULTIPLE_COILS)
    {
        // (2 x firstCoilAddress, 2 x coilsCount, 1 x valueBytes, n x values).
        uint16_t index = MODBUS_DATA_INDEX + 5 + (offset / 8);
        uint8_t bitIndex = offset % 8;

        // Check the offset.
        if (index < _requestBufferLength - MODBUS_CRC_LENGTH)
        {
            return bitRead(_requestBuffer[index], bitIndex);
        }
    }
    return false;
}

/**
 * Reads a register value from input buffer.
 *
 * @param offset The offset from the first register in the buffer.
 * @return The register value from buffer.
 */
uint16_t ModbusLib::readRegisterFromBuffer(int offset)
{
    if (_requestBuffer[MODBUS_FUNCTION_CODE_INDEX] == FC_WRITE_REGISTER)
    {
        if (offset == 0)
        {
            // (2 x coilAddress, 2 x value).
            return readUInt16(_requestBuffer, MODBUS_DATA_INDEX + 2);
        }
    }
    else if (_requestBuffer[MODBUS_FUNCTION_CODE_INDEX] == FC_WRITE_MULTIPLE_REGISTERS)
    {
        // (2 x firstRegisterAddress, 2 x registersCount, 1 x valueBytes, n x values).
        uint16_t index = MODBUS_DATA_INDEX + 5 + (offset * 2);

        // Check the offset.
        if (index < _requestBufferLength - MODBUS_CRC_LENGTH)
        {
            return readUInt16(_requestBuffer, index);
        }
    }
    return 0;
}

/**
 * Writes the exception status to the buffer.
 *
 * @param offset
 * @param status Exception status flag (true / false)
 */
uint8_t ModbusLib::writeExceptionStatusToBuffer(int offset, bool status)
{
    // Check the function code.
    if (_requestBuffer[MODBUS_FUNCTION_CODE_INDEX] != FC_READ_EXCEPTION_STATUS)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    // (1 x values).
    uint16_t index = MODBUS_DATA_INDEX;
    uint8_t bitIndex = offset % 8;

    // Check the offset.
    if (index >= _responseBufferLength - MODBUS_CRC_LENGTH)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    if (status)
    {
        bitSet(_responseBuffer[index], bitIndex);
    }
    else
    {
        bitClear(_responseBuffer[index], bitIndex);
    }

    return STATUS_OK;
}

/**
 * Writes the coil state to the output buffer.
 *
 * @param offset The offset from the first coil in the buffer.
 * @param state The state to write into the buffer (true / false).
 */
uint8_t ModbusLib::writeCoilToBuffer(int offset, bool state)
{
    // Check the function code.
    if (_requestBuffer[MODBUS_FUNCTION_CODE_INDEX] != FC_READ_DISCRETE_INPUT &&
        _requestBuffer[MODBUS_FUNCTION_CODE_INDEX] != FC_READ_COILS)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    // (1 x valueBytes, n x values).
    uint16_t index = MODBUS_DATA_INDEX + 1 + (offset / 8);
    uint8_t bitIndex = offset % 8;

    // Check the offset.
    if (index >= _responseBufferLength - MODBUS_CRC_LENGTH)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    if (state)
    {
        bitSet(_responseBuffer[index], bitIndex);
    }
    else
    {
        bitClear(_responseBuffer[index], bitIndex);
    }

    return STATUS_OK;
}

/**
 * Writes the digital input to output buffer.
 *
 * @param offset The offset from the first input in the buffer.
 * @param state The state to write into the buffer (true / false).
 */
uint8_t ModbusLib::writeDiscreteInputToBuffer(int offset, bool state)
{
    return ModbusLib::writeCoilToBuffer(offset, state);
}

/**
 * Writes the register value to the output buffer.
 *
 * @param offset The offset from the first register in the buffer.
 * @param value The register value to write into buffer.
 */
uint8_t ModbusLib::writeRegisterToBuffer(int offset, uint16_t value)
{
    // Check the function code.
    if (_requestBuffer[MODBUS_FUNCTION_CODE_INDEX] != FC_READ_HOLDING_REGISTERS &&
        _requestBuffer[MODBUS_FUNCTION_CODE_INDEX] != FC_READ_INPUT_REGISTERS)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    // (1 x valueBytes, n x values).
    uint16_t index = MODBUS_DATA_INDEX + 1 + (offset * 2);

    // Check the offset.
    if ((index + 2) > (_responseBufferLength - MODBUS_CRC_LENGTH))
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    _responseBuffer[index] = value >> 8;
    _responseBuffer[index + 1] = value & 0xFF;

    

    return STATUS_OK;
}

/**
 * Writes an uint8_t array to the output buffer.
 *
 * @param offset The offset from the first data register in the response buffer.
 * @param str The array to write into the response buffer.
 * @param length The length of the array.
 * @return STATUS_OK if succeeded, STATUS_ILLEGAL_DATA_ADDRESS if the data doesn't fit in the buffer.
 */
uint8_t ModbusLib::writeArrayToBuffer(int offset, uint16_t *str, uint8_t length)
{
    // Index to start writing from (1 x valueBytes, n x values (offset)).
    uint8_t index = MODBUS_DATA_INDEX + 1 + (offset * 2);

    // Check if the array fits in the remaining space of the response.
    if ((index + (length * 2)) > _responseBufferLength - MODBUS_CRC_LENGTH)
    {
        // If not return an exception.
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    for (int i = 0; i < length; i++)
    {
        _responseBuffer[index + (i * 2)] = str[i] >> 8;
        _responseBuffer[index + (i * 2) + 1] = str[i] & 0xFF;
    }

    return STATUS_OK;
}

/**
 * ---------------------------------------------------
 *                  PRIVATE METHODS
 * ---------------------------------------------------
 */

/**
 * Reads a new request from the serial stream and fills the request buffer.
 *
 * @return True if the buffer is filled with a request and is ready to be processed; otherwise false.
 */
uint16_t wiat3p5;
uint16_t oldLen=0;

bool ModbusLib::readRequest()
{
    // Read one data packet and report when it's received completely.
    //uint16_t length = _serialStream.available();
    uint16_t length=0;
    

    uart_get_buffered_data_len((uart_port_t)1, (size_t*)&length);

    _isRequestBufferReading = false;

    if(oldLen < length){
        wiat3p5 = millis();
        oldLen = length;
    }
    
    if(  ((millis()  - wiat3p5)  > 1 ) && (oldLen > 0)){        
        uart_get_buffered_data_len((uart_port_t)1, (size_t*)&length);
        uart_read_bytes((uart_port_t)1, _requestBuffer, length, 100);
        
        _requestBufferLength = length;
        _isRequestBufferReading = true;
        //Serial.println("go to read buf " + String(length));

        // for(int i = 0; i< length; i++)
        // {
        //     Serial.printf("%X ", _requestBuffer[i]);
        // }
        // Serial.println();

        oldLen = 0;
    }  

    return _isRequestBufferReading ;
}

/**
 * Returns true if one of the slaves listens to the given address.
 *
 * @param unitAddress The received address.
 */
bool ModbusLib::relevantAddress(uint8_t unitAddress)
{
    // Every device should listen to broadcast messages,
    // keep the check it local, since we provide the unitAddress
    if (unitAddress == MODBUS_BROADCAST_ADDRESS)
    {
        return true;
    }

    // Iterate over all the slaves and check if it listens to the given address, if so return true.
    for (uint8_t i = 0; i < _numberOfSlaves; ++i)
    {
        requestAddress = unitAddress;
        uint8_t address = (unitAddress / 10) * 10;         
        if (_slaves[i].getUnitAddress() == address)
        {   
            return true;
        }
    }

    return false;
}

/**
 * Validates the request message currently in the input buffer.
 *
 * @return True if the request is valid; otherwise false.
 */
bool ModbusLib::validateRequest()
{

    // Check that the message was addressed to us
    if (!ModbusLib::relevantAddress(_requestBuffer[MODBUS_ADDRESS_INDEX]))
    {
        //Serial.println(" error packet");
        return false;
    }
    // The minimum buffer size (1 x Address, 1 x Function, n x Data, 2 x CRC).
    uint16_t expected_requestBufferSize = MODBUS_FRAME_SIZE;
    bool report_illegal_function=false;

    // Check the validity of the data based on the function code.
    switch (_requestBuffer[MODBUS_FUNCTION_CODE_INDEX])
    {
        case FC_READ_EXCEPTION_STATUS:
            // Broadcast is not supported, so ignore this request.
            if (_requestBuffer[MODBUS_ADDRESS_INDEX] == MODBUS_BROADCAST_ADDRESS)
            {
                return false;
            }
            break;

        case FC_READ_COILS:             // Read coils (digital read).
        case FC_READ_DISCRETE_INPUT:    // Read input state (digital read).
        case FC_READ_HOLDING_REGISTERS: // Read holding registers (analog read).
        case FC_READ_INPUT_REGISTERS:   // Read input registers (analog read).
            // Broadcast is not supported, so ignore this request.
            if (_requestBuffer[MODBUS_ADDRESS_INDEX] == MODBUS_BROADCAST_ADDRESS)
            {
                return false;
            }
            // Add bytes to expected request size (2 x Index, 2 x Count).
            expected_requestBufferSize += 4;
            break;

        case FC_WRITE_COIL:     // Write coils (digital write).
        case FC_WRITE_REGISTER: // Write regosters (digital write).
            // Add bytes to expected request size (2 x Index, 2 x Count).
            expected_requestBufferSize += 4;
            break;

        case FC_WRITE_MULTIPLE_COILS:
        case FC_WRITE_MULTIPLE_REGISTERS:
            // Add bytes to expected request size (2 x Index, 2 x Count, 1 x Bytes).
            expected_requestBufferSize += 5;
            if (_requestBufferLength >= expected_requestBufferSize)
            {
                // Add bytes to expected request size (n x Bytes).
                expected_requestBufferSize += _requestBuffer[6];
            }
            break;

        default:
            // Unknown function code.
             report_illegal_function=true;
    }

    // If the received data is smaller than what we expect, ignore this request.
    if (_requestBufferLength < expected_requestBufferSize)
    {
        return false;
    }

    // Check the crc, and if it isn't correct ignore the request.
    uint16_t crc = readCRC(_requestBuffer, _requestBufferLength);
    if (ModbusLib::calculateCRC(_requestBuffer, _requestBufferLength - MODBUS_CRC_LENGTH) != crc)
    {
        //Serial.println(" error crc");
        return false;
    }

    // Prepare the output buffer.
    memset(_responseBuffer, 0, MODBUS_MAX_BUFFER);
    _responseBuffer[MODBUS_ADDRESS_INDEX] = _requestBuffer[MODBUS_ADDRESS_INDEX];
    _responseBuffer[MODBUS_FUNCTION_CODE_INDEX] = _requestBuffer[MODBUS_FUNCTION_CODE_INDEX];
    _responseBufferLength = MODBUS_FRAME_SIZE;

    // report_illegal_function after the CRC check, cheaper
    if (report_illegal_function)
    {
        ModbusLib::reportException(STATUS_ILLEGAL_FUNCTION);
        return false;
    }

    // Set the length to be read from the request to the calculated expected length.
    _requestBufferLength = expected_requestBufferSize;

    return true;
}

/**
 * Fills the output buffer with the response to the request from the input buffer.
 *
 * @return The status code representing the outcome of this operation.
 */
uint8_t ModbusLib::createResponse()
{
    uint16_t firstAddress;
    uint16_t addressesLength;
    uint8_t callbackIndex;
    uint16_t requestUnitAddress = _requestBuffer[MODBUS_ADDRESS_INDEX];

    // Match the function code with a callback and execute it and prepare the response buffer.
    switch (_requestBuffer[MODBUS_FUNCTION_CODE_INDEX])
    {
    case FC_READ_EXCEPTION_STATUS:
        // Reject broadcast read requests
        if (requestUnitAddress == MODBUS_BROADCAST_ADDRESS)
        {
            return STATUS_ILLEGAL_FUNCTION;
        }

        // Add the length of the response data to the length of the output.
        _responseBufferLength += 1;

        // Execute the callback and return the status code.
        return ModbusLib::executeCallback(requestUnitAddress, CB_READ_EXCEPTION_STATUS, 0, 8);

    case FC_READ_COILS:          // Read coils (digital out state).
    case FC_READ_DISCRETE_INPUT: // Read input state (digital in).
        // Reject broadcast read requests
        if (requestUnitAddress == MODBUS_BROADCAST_ADDRESS)
        {
            return STATUS_ILLEGAL_FUNCTION;
        }

        // Read the first address and the number of inputs.
        firstAddress = readUInt16(_requestBuffer, MODBUS_DATA_INDEX);
        addressesLength = readUInt16(_requestBuffer, MODBUS_DATA_INDEX + 2);

        // Calculate the length of the response data and add it to the length of the output buffer.
        _responseBuffer[MODBUS_DATA_INDEX] = (addressesLength / 8) + (addressesLength % 8 != 0);
        _responseBufferLength += 1 + _responseBuffer[MODBUS_DATA_INDEX];

        // Execute the callback and return the status code.
        callbackIndex = _requestBuffer[MODBUS_FUNCTION_CODE_INDEX] == FC_READ_COILS ? CB_READ_COILS : CB_READ_DISCRETE_INPUTS;
        return ModbusLib::executeCallback(requestUnitAddress, callbackIndex, firstAddress, addressesLength);

    case FC_READ_HOLDING_REGISTERS: // Read holding registers (analog out state)
    case FC_READ_INPUT_REGISTERS:   // Read input registers (analog in)
        // Reject broadcast read requests
        if (requestUnitAddress == MODBUS_BROADCAST_ADDRESS)
        {
            return STATUS_ILLEGAL_FUNCTION;
        }

        // Read the first address and the number of inputs.
        firstAddress = readUInt16(_requestBuffer, MODBUS_DATA_INDEX);
        addressesLength = readUInt16(_requestBuffer, MODBUS_DATA_INDEX + 2);

        // Calculate the length of the response data and add it to the length of the output buffer.
        _responseBuffer[MODBUS_DATA_INDEX] = 2 * addressesLength;
        _responseBufferLength += 1 + _responseBuffer[MODBUS_DATA_INDEX];

        // Execute the callback and return the status code.
        callbackIndex = _requestBuffer[MODBUS_FUNCTION_CODE_INDEX] == FC_READ_HOLDING_REGISTERS ? CB_READ_HOLDING_REGISTERS : CB_READ_INPUT_REGISTERS;
        return ModbusLib::executeCallback(requestUnitAddress, callbackIndex, firstAddress, addressesLength);

    case FC_WRITE_COIL: // Write one coil (digital out).
        // Read the address.
        firstAddress = readUInt16(_requestBuffer, MODBUS_DATA_INDEX);

        // Add the length of the response data to the length of the output.
        _responseBufferLength += 4;
        // Copy the parts of the request data that need to be in the response data.
        memcpy(_responseBuffer + MODBUS_DATA_INDEX, _requestBuffer + MODBUS_DATA_INDEX, _responseBufferLength - MODBUS_FRAME_SIZE);

        // Execute the callback and return the status code.
        return ModbusLib::executeCallback(requestUnitAddress, CB_WRITE_COILS, firstAddress, 1);

    case FC_WRITE_REGISTER: // Write one holding register (analog out).
        // Read the address.
        firstAddress = readUInt16(_requestBuffer, MODBUS_DATA_INDEX);

        // Add the length of the response data to the length of the output.
        _responseBufferLength += 4;
        // Copy the parts of the request data that need to be in the response data.
        memcpy(_responseBuffer + MODBUS_DATA_INDEX, _requestBuffer + MODBUS_DATA_INDEX, _responseBufferLength - MODBUS_FRAME_SIZE);

        // Execute the callback and return the status code.
        return ModbusLib::executeCallback(requestUnitAddress, CB_WRITE_HOLDING_REGISTERS, firstAddress, 1);

    case FC_WRITE_MULTIPLE_COILS: // Write multiple coils (digital out)
        // Read the first address and the number of outputs.
        firstAddress = readUInt16(_requestBuffer, MODBUS_DATA_INDEX);
        addressesLength = readUInt16(_requestBuffer, MODBUS_DATA_INDEX + 2);

        // Add the length of the response data to the length of the output.
        _responseBufferLength += 4;
        // Copy the parts of the request data that need to be in the response data.
        memcpy(_responseBuffer + MODBUS_DATA_INDEX, _requestBuffer + MODBUS_DATA_INDEX, _responseBufferLength - MODBUS_FRAME_SIZE);

        // Execute the callback and return the status code.
        return ModbusLib::executeCallback(requestUnitAddress, CB_WRITE_COILS, firstAddress, addressesLength);

    case FC_WRITE_MULTIPLE_REGISTERS: // Write multiple holding registers (analog out).
        // Read the first address and the number of outputs.
        firstAddress = readUInt16(_requestBuffer, MODBUS_DATA_INDEX);
        addressesLength = readUInt16(_requestBuffer, MODBUS_DATA_INDEX + 2);

        // Add the length of the response data to the length of the output.
        _responseBufferLength += 4;
        // Copy the parts of the request data that need to be in the response data.
        memcpy(_responseBuffer + MODBUS_DATA_INDEX, _requestBuffer + MODBUS_DATA_INDEX, _responseBufferLength - MODBUS_FRAME_SIZE);

        // Execute the callback and return the status code.
        return ModbusLib::executeCallback(requestUnitAddress, CB_WRITE_HOLDING_REGISTERS, firstAddress, addressesLength);

    default:
        return STATUS_ILLEGAL_FUNCTION;
    }
}

/**
 * Executes a callback.
 *
 * @return The status code representing the outcome of this operation.
 */
uint8_t ModbusLib::executeCallback(uint8_t slaveAddress, uint8_t callbackIndex, uint16_t address, uint16_t length)
{
    // Search for the correct slave to execute callback on.
    for (uint8_t i = 0; i < _numberOfSlaves; ++i)
    {
        ModbusCallback callback = _slaves[i].cbVector[callbackIndex];
        if (slaveAddress == MODBUS_BROADCAST_ADDRESS)
        {
            if (callback)
            {
                callback(ModbusLib::readFunctionCode(), address, length);
            }
        }
        else if (_slaves[i].getUnitAddress() == slaveAddress/10*10)
        {
            if (callback)
            {
                return callback(ModbusLib::readFunctionCode(), address, length);
            }
            else
            {
                return STATUS_ILLEGAL_FUNCTION;
            }
        }
    }
    // No return in loop for a Broadcast thus return here without error if it's a Broadcast!
    return slaveAddress == MODBUS_BROADCAST_ADDRESS ? STATUS_ACKNOWLEDGE : STATUS_ILLEGAL_FUNCTION;

}

/**
 * Writes the output buffer to the serial stream.
 *
 * @return The number of bytes written.
 */
uint16_t ModbusLib::writeResponse()
{
    /**
     * Validate
     */
    //Serial.println(__LINE__);
    // Check if there is a response created and that this is the first time it is written.
    if (_responseBufferWriteIndex == 0 && _responseBufferLength >= MODBUS_FRAME_SIZE)
    {
        // Start the writing.
        _isResponseBufferWriting = true;
    }
    //Serial.println(__LINE__);

    // If we are not writing or the address is the broadcast address, cleanup and return.
    if (!_isResponseBufferWriting || isBroadcast())
    {
        _isResponseBufferWriting = false;
        _responseBufferWriteIndex = 0;
        _responseBufferLength = 0;
        return 0;
    }
    //Serial.println(__LINE__);
    /**
     * Preparing
     */

    // If this is the first write.
    if (_responseBufferWriteIndex == 0)
    {
        // Check if we already passed 1.5T.
        if ((micros() - _lastCommunicationTime) <= (_halfCharTimeInMicroSecond * MODBUS_HALF_SILENCE_MULTIPLIER))
        {
            return 0;
        }

        // Calculate and add the CRC.
        uint16_t crc = ModbusLib::calculateCRC(_responseBuffer, _responseBufferLength - MODBUS_CRC_LENGTH);
        _responseBuffer[_responseBufferLength - MODBUS_CRC_LENGTH] = crc & 0xFF;
        _responseBuffer[(_responseBufferLength - MODBUS_CRC_LENGTH) + 1] = crc >> 8;

        // Start transmission mode for RS485.
        if (_transmissionControlPin > MODBUS_CONTROL_PIN_NONE)
        {
            digitalWrite(_transmissionControlPin, HIGH);
        }
    }
    //Serial.println(__LINE__);
    /**
     * Transmit
     */

    // Send the output buffer over the serial stream.
    

    //uint16_t length = 0;
    //if (_serialTransmissionBufferLength > 0)
    {
        // Check the maximum length of bytes to be send in one call.
        //Serial.println(__LINE__);
        uart_write_bytes((uart_port_t)1, _responseBuffer, _responseBufferLength);
        
    }    
    //Serial.println(__LINE__);

    return 0;
}

// uint16_t ModbusLib::writeResponse()
// {
//     /**
//      * Validate
//      */

//     // Check if there is a response created and that this is the first time it is written.
//     if (_responseBufferWriteIndex == 0 && _responseBufferLength >= MODBUS_FRAME_SIZE)
//     {
//         // Start the writing.
//         _isResponseBufferWriting = true;
//     }

//     // If we are not writing or the address is the broadcast address, cleanup and return.
//     if (!_isResponseBufferWriting || isBroadcast())
//     {
//         _isResponseBufferWriting = false;
//         _responseBufferWriteIndex = 0;
//         _responseBufferLength = 0;
//         return 0;
//     }

//     /**
//      * Preparing
//      */

//     // If this is the first write.
//     if (_responseBufferWriteIndex == 0)
//     {
//         // Check if we already passed 1.5T.
//         if ((micros() - _lastCommunicationTime) <= (_halfCharTimeInMicroSecond * MODBUS_HALF_SILENCE_MULTIPLIER))
//         {
//             return 0;
//         }

//         // Calculate and add the CRC.
//         uint16_t crc = ModbusLib::calculateCRC(_responseBuffer, _responseBufferLength - MODBUS_CRC_LENGTH);
//         _responseBuffer[_responseBufferLength - MODBUS_CRC_LENGTH] = crc & 0xFF;
//         _responseBuffer[(_responseBufferLength - MODBUS_CRC_LENGTH) + 1] = crc >> 8;

//         // Start transmission mode for RS485.
//         if (_transmissionControlPin > MODBUS_CONTROL_PIN_NONE)
//         {
//             digitalWrite(_transmissionControlPin, HIGH);
//         }
//     }

//     /**
//      * Transmit
//      */

//     // Send the output buffer over the serial stream.
//     uint16_t length = 0;
//     if (_serialTransmissionBufferLength > 0)
//     {
//         // Check the maximum length of bytes to be send in one call.
//         uint16_t length = min(
//             _serialStream.availableForWrite(),
//             _responseBufferLength - _responseBufferWriteIndex);

//         if (length > 0)
//         {
//             // Write the maximum length of bytes over the serial stream.
//             length = _serialStream.write(
//                 _responseBuffer + _responseBufferWriteIndex,
//                 length);

//             // Serial.print("write: ");
//             // for (int i = 0; i < length; ++i){
//             //     Serial.printf("%x ", _responseBuffer[i] );

//             // }
//             Serial.println();
//             _responseBufferWriteIndex += length;
//             _totalBytesSent += length;
//         }

//         // Check if all the data has been sent.
//         if (_serialStream.availableForWrite() < _serialTransmissionBufferLength)
//         {
//             _lastCommunicationTime = micros();
//             return length;
//         }

//         // If the serial stream reports empty, make sure it is.
//         // (`Serial` removes bytes from buffer before sending them).
//         _serialStream.flush();
//     }
//     else
//     {
//         // Compatibility mode for badly written software serials; aka AltSoftSerial.
//         length = _responseBufferLength - _responseBufferWriteIndex;

//         if (length > 0)
//         {
//             length = _serialStream.write(_responseBuffer, length);
//             _serialStream.flush();
//         }

//         _responseBufferWriteIndex += length;
//         _totalBytesSent += length;
//     }

//     // If all the data has been send and more than 1.5T has passed.
//     if (_responseBufferWriteIndex >= _responseBufferLength && (micros() - _lastCommunicationTime) > (_halfCharTimeInMicroSecond * MODBUS_HALF_SILENCE_MULTIPLIER))
//     {
//         // End the transmission.
//         if (_transmissionControlPin > MODBUS_CONTROL_PIN_NONE)
//         {
//             digitalWrite(_transmissionControlPin, LOW);
//         }

//         // And cleanup the variables.
//         _isResponseBufferWriting = false;
//         _responseBufferWriteIndex = 0;
//         _responseBufferLength = 0;
//     }

//     return length;
// }

/**
 * Fills the output buffer with an exception based on the request in the input buffer and writes the response over the serial stream.
 *
 * @param exceptionCode The status code to report.
 * @return The number of bytes written.
 */
uint16_t ModbusLib::reportException(uint8_t exceptionCode)
{
    // Broadcast is not supported, so ignore this request.
    if (isBroadcast())
    {
        return 0;
    }

    // Add the exception code to the output buffer.
    _responseBufferLength = MODBUS_FRAME_SIZE + 1;
    _responseBuffer[MODBUS_FUNCTION_CODE_INDEX] |= 0x80;
    _responseBuffer[MODBUS_DATA_INDEX] = exceptionCode;

    return ModbusLib::writeResponse();
}

/**
 * Calculate the CRC of the passed byte array from zero up to the passed length.
 *
 * @param buffer The byte array containing the data.
 * @param length The length of the byte array.
 *
 * @return The calculated CRC as an unsigned 16 bit integer.
 */

#ifndef CRC_LTABLE_CALC

uint16_t ModbusLib::calculateCRC(uint8_t *buffer, int length)
{
    int i, j;
    uint16_t crc = 0xFFFF;
    uint16_t tmp;

    // Calculate the CRC.
    for (i = 0; i < length; i++)
    {
        crc = crc ^ buffer[i];

        for (j = 0; j < 8; j++)
        {
            tmp = crc & 0x0001;
            crc = crc >> 1;
            if (tmp)
            {
                crc = crc ^ 0xA001;
            }
        }
    }
    return crc;
}

#else

// CRC over LookUp Table
inline uint16_t Modbus::calculateCRC(uint8_t *buffer, int length)
{
    uint16_t crc = 0xFFFF;
    uint8_t tmp;

    while (length--)
    {
        tmp = (*buffer++ ^ crc) & 0xFF;
        crc = (crc >> 8) ^ pgm_read_word(wCRCTable + tmp);
    }
    return crc;
}

#endif
