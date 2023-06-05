#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class MockDevice : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));

};

TEST(DeviceDriver, CheckReadFiveTimes)
{
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read)
		.Times(5);

	DeviceDriver device_driver(&mock_device);
	device_driver.read(0xA);
}

TEST(DeviceDriver, ReadFailException)
{
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(_))
		.WillOnce(Return(0x1))
		.WillOnce(Return(0x1))
		.WillOnce(Return(0x1))
		.WillOnce(Return(0x1))
		.WillOnce(Return(0x2));

	DeviceDriver device_driver(&mock_device);
	EXPECT_THROW(device_driver.read(0x1), std::exception);
}