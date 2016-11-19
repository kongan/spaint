/**
 * spaint: ExampleReservoirs.h
 * Copyright (c) Torr Vision Group, University of Oxford, 2016. All rights reserved.
 */

#ifndef H_SPAINT_EXAMPLERESERVOIRS
#define H_SPAINT_EXAMPLERESERVOIRS

#include "ITMLib/Utils/ITMMath.h"

#include "../../util/ITMMemoryBlockPtrTypes.h"
#include "../../features/interface/RGBDPatchFeature.h"
#include "../SCoReForestTypes.h"

namespace spaint
{
// Ugly, need to put it somewhere better
struct PositionColourExample
{
  Vector3f position;
  Vector3u colour;
};

template<typename ExampleType, typename FeatureType, typename LeafType>
class ExampleReservoirs
{
public:
  typedef ORUtils::Image<ExampleType> ExampleReservoirsImage;
  typedef boost::shared_ptr<ExampleReservoirsImage> ExampleReservoirsImage_Ptr;
  typedef boost::shared_ptr<const ExampleReservoirsImage> ExampleReservoirsImage_CPtr;

  typedef ORUtils::Image<FeatureType> FeatureImage;
  typedef boost::shared_ptr<FeatureImage> FeatureImage_Ptr;
  typedef boost::shared_ptr<const FeatureImage> FeatureImage_CPtr;

  typedef ORUtils::Image<LeafType> LeafImage;
  typedef boost::shared_ptr<LeafImage> LeafImage_Ptr;
  typedef boost::shared_ptr<const LeafImage> LeafImage_CPtr;

  ExampleReservoirs(size_t capacity, size_t nbLeaves, uint32_t rngSeed = 42);
  virtual ~ExampleReservoirs();

  ExampleReservoirsImage_CPtr get_reservoirs() const;

  ITMIntMemoryBlock_CPtr get_reservoirs_size() const;

  int get_reservoirs_count() const;

  int get_capacity() const;

  virtual void add_examples(const FeatureImage_CPtr &features,
      const LeafImage_CPtr &leafIndices) = 0;
  virtual void clear();

protected:
  ExampleReservoirsImage_Ptr m_data;
  ITMIntMemoryBlock_Ptr m_reservoirsSize;
  ITMIntMemoryBlock_Ptr m_reservoirsAddCalls;

  uint32_t m_reservoirCapacity;
  uint32_t m_rngSeed;
};

typedef ExampleReservoirs<PositionColourExample, RGBDPatchFeature, LeafIndices> PositionReservoir;
typedef boost::shared_ptr<PositionReservoir> PositionReservoir_Ptr;
typedef boost::shared_ptr<const PositionReservoir> PositionReservoir_CPtr;

}

#endif
