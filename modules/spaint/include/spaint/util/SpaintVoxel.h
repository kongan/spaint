/**
 * spaint: SpaintVoxel.h
 */

#ifndef H_SPAINT_SPAINTVOXEL
#define H_SPAINT_SPAINTVOXEL

#include <ITMLib/Utils/ITMLibDefines.h>

namespace spaint {

//#################### VOXEL TYPE ####################

/**
 * \brief An instance of this struct represents a voxel in the reconstructed scene.
 */
struct SpaintVoxel
{
  typedef uchar Label;

  /**
   * \brief The values of this enumeration specify the possible groups in which a voxel label can reside.
   */
  enum LabelGroup
  {
    /** Labels in the "user" group are those that have been supplied directly by the user. They are assumed to be correct enough to use for training. */
    LG_USER,

    /** Labels in the "forest" group are those that have been predicted by the random forest. They are assumed to be unreliable, and ignored for training purposes. */
    LG_FOREST,
  };

  struct PackedLabel
  {
    LabelGroup group : 2;
    Label label : 6;

    _CPU_AND_GPU_CODE_
    PackedLabel()
    : group(LG_USER), label(0)
    {}

    _CPU_AND_GPU_CODE_
    PackedLabel(Label label_, LabelGroup group_)
    : group(group_), label(label_)
    {}

    _CPU_AND_GPU_CODE_
    bool operator==(const PackedLabel& rhs) const
    {
      return group == rhs.group && label == rhs.label;
    }
  };

  _CPU_AND_GPU_CODE_ static short SDF_initialValue() { return 32767; }
  _CPU_AND_GPU_CODE_ static float SDF_valueToFloat(float x) { return (float)(x) / 32767.0f; }
  _CPU_AND_GPU_CODE_ static short SDF_floatToValue(float x) { return (short)((x) * 32767.0f); }

#ifndef USE_LOW_POWER_MODE
  static const bool hasColorInformation = true;
#else
  static const bool hasColorInformation = false;
#endif

  /** Value of the truncated signed distance transformation. */
  short sdf;
  /** Number of fused observations that make up @p sdf. */
  uchar w_depth;

#ifndef USE_LOW_POWER_MODE
  /** RGB colour information stored for this voxel. */
  Vector3u clr;
  /** Number of observations that made up @p clr. */
  uchar w_color;
#endif

  /** Semantic label. */
  PackedLabel packedLabel;

  _CPU_AND_GPU_CODE_
  SpaintVoxel()
  {
    sdf = SDF_initialValue();
    w_depth = 0;
#ifndef USE_LOW_POWER_MODE
    clr = (uchar)0;
    w_color = 0;
#endif
    packedLabel = PackedLabel(0, LG_USER);
  }
};

//#################### COLOUR READING ####################

/**
 * \brief An instance of a specialisaton of this struct template can be used to read a voxel's colour in the scene (if available).
 */
template <bool hasColour> struct VoxelColourReader;

/**
 * \brief An instance of this struct can be used to return a default scene colour for a voxel when no colour information is available.
 */
template <>
struct VoxelColourReader<false>
{
  template <typename TVoxel>
  _CPU_AND_GPU_CODE_
  static Vector3u read(const TVoxel& voxel)
  {
    return Vector3u((uchar)0);
  }
};

/**
 * \brief An instance of this struct can be used to return a voxel's colour in the scene when colour information is available.
 */
template <>
struct VoxelColourReader<true>
{
  template <typename TVoxel>
  _CPU_AND_GPU_CODE_
  static Vector3u read(const TVoxel& voxel)
  {
    return voxel.clr;
  }
};

}

#endif
