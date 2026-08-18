###########################################################
#
# RZ1_APP mission build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the RZ1_APP configuration
set(RZ1_APP_MISSION_CONFIG_FILE_LIST
  rz1_app_fcncode_values.h
  rz1_app_interface_cfg_values.h
  rz1_app_mission_cfg.h
  rz1_app_perfids.h
  rz1_app_msg.h
  rz1_app_msgdefs.h
  rz1_app_msgstruct.h
  rz1_app_tbl.h
  rz1_app_tbldefs.h
  rz1_app_tblstruct.h
  rz1_app_topicid_values.h
)

generate_configfile_set(${RZ1_APP_MISSION_CONFIG_FILE_LIST})

