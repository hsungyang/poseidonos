#include <gmock/gmock.h>

#include <list>
#include <string>
#include <vector>

#include "src/volume/i_volume_manager.h"

namespace pos
{
class MockIVolumeManager : public IVolumeManager
{
public:
    using IVolumeManager::IVolumeManager;
    MOCK_METHOD(int, Create, (std::string name, uint64_t size, uint64_t maxiops, uint64_t maxbw), (override));
    MOCK_METHOD(int, Delete, (std::string name), (override));
    MOCK_METHOD(int, Mount, (std::string name, std::string subnqn), (override));
    MOCK_METHOD(int, Unmount, (std::string name), (override));
    MOCK_METHOD(int, UpdateQoS, (std::string name, uint64_t maxiops, uint64_t maxbw), (override));
    MOCK_METHOD(int, Rename, (std::string oldname, std::string newname), (override));
    MOCK_METHOD(int, Resize, (std::string name, uint64_t newsize), (override));
    MOCK_METHOD(int, UpdateVolumePolicy, (std::string volName, qos_vol_policy volPolicy), (override));
    MOCK_METHOD(qos_vol_policy, GetVolumePolicy, (std::string volName), (override));
    MOCK_METHOD(void, DetachVolumes, (), (override));
    MOCK_METHOD(bool, CheckVolumeIdle, (int volId), (override));
    MOCK_METHOD(int, VolumeName, (int volId, std::string& volName), (override));
    MOCK_METHOD(int, VolumeID, (std::string volName), (override));
    MOCK_METHOD(int, GetVolumeCount, (), (override));
    MOCK_METHOD(int, GetVolumeStatus, (int volId), (override));
    MOCK_METHOD(uint64_t, EntireVolumeSize, (), (override));
    MOCK_METHOD(int, GetVolumeSize, (int volId, uint64_t& volSize), (override));
    MOCK_METHOD(VolumeList*, GetVolumeList, (), (override));
    MOCK_METHOD(std::string, GetStatusStr, (VolumeStatus status), (override));
    MOCK_METHOD(int, IncreasePendingIOCount, (int volId, uint32_t ioCountToSubmit), (override));
    MOCK_METHOD(int, DecreasePendingIOCount, (int volId, uint32_t ioCountCompleted), (override));
    MOCK_METHOD(VolumeBase*, GetVolume, (int volId), (override));
};

} // namespace pos