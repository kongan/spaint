/**
 * spaint: UniformVoxelSampler_CUDA.cu
 */

#include "sampling/cuda/UniformVoxelSampler_CUDA.h"

#include "sampling/shared/UniformVoxelSampler_Shared.h"

namespace spaint {

//#################### CUDA KERNELS ####################

__global__ void ck_write_sampled_voxel_locations(size_t voxelsToSample, const Vector4f *raycastResultData, const int *sampledVoxelIndices, Vector3s *sampledVoxelLocations)
{
  int tid = threadIdx.x + blockDim.x * blockIdx.x;
  if(tid < static_cast<int>(voxelsToSample))
  {
    write_sampled_voxel_location(tid, raycastResultData, sampledVoxelIndices, sampledVoxelLocations);
  }
}

//#################### PRIVATE MEMBER FUNCTIONS ####################

void UniformVoxelSampler_CUDA::write_sampled_voxel_locations(const ITMFloat4Image *raycastResult, size_t voxelsToSample,
                                                             ORUtils::MemoryBlock<Vector3s>& sampledVoxelLocationsMB) const
{
  int threadsPerBlock = 256;
  int numBlocks = (static_cast<int>(voxelsToSample) + threadsPerBlock - 1) / threadsPerBlock;

  ck_write_sampled_voxel_locations<<<numBlocks,threadsPerBlock>>>(
    voxelsToSample,
    raycastResult->GetData(MEMORYDEVICE_CUDA),
    m_sampledVoxelIndicesMB.GetData(MEMORYDEVICE_CUDA),
    sampledVoxelLocationsMB.GetData(MEMORYDEVICE_CUDA)
  );
}

}
