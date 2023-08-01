//
// Created by gaome on 2023/7/18.
//
namespace IRCtrl
{
// generate arm_aapcs_vfpcc header for arm
#ifdef IRSW_ENABLE_ARM_AAPCS_VFPCC
bool IR_SWITCH_ENABLE_ARM_AAPCS_VFPCC = true;
#else
bool IR_SWITCH_ENABLE_ARM_AAPCS_VFPCC = false;
#endif

#ifdef IRSW_ENABLE_DSO_LOCAL
bool IR_SWITCH_ENABLE_DSO_LOCAL = true;
#else
bool IR_SWITCH_ENABLE_DSO_LOCAL       = false;
#endif

}   // namespace IRCtrl