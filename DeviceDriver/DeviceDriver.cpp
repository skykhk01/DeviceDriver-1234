#include "DeviceDriver.h"
#include <exception>
#include <windows.h>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware)
	: m_hardware(hardware)
{

}

int DeviceDriver::read(long address)
{
	int value = (int)(m_hardware->read(address));
	for (int readCnt = 1; readCnt < TOTAL_READ_COUNT; ++readCnt) {
		Sleep(READ_INTERVAL);
		if (value == (int)(m_hardware->read(address))) continue;
		throw std::exception("ReadFailException!");
	}
	return value;
}

void DeviceDriver::write(long address, int data)
{
	// TODO: implement this method
	m_hardware->write(address, (unsigned char)data);
}
